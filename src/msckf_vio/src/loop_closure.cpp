#include <thread>
#include <string>
#include <iostream>
#include <algorithm>
#include <set>
#include <Eigen/Dense>
#include <tf_conversions/tf_eigen.h>
#include <eigen_conversions/eigen_msg.h>
#include <msckf_vio/loop_closure.h>
#include <msckf_vio/utils.h>
#include <vector>
#include <map>
#include <boost/shared_ptr.hpp>

// OpenCV Lib
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <opencv2/video.hpp>



// #include <msckf_vio/MapPoint.h>
#include <msckf_vio/image_processor.h>

#include <msckf_vio/Frame.h>
#include <msckf_vio/KeyFrame.h>
#include <iomanip>


using namespace std;
using namespace cv;
 
mutex loopLock;

namespace msckf_vio{

	bool has_suffix(const std::string &str, const std::string &suffix) 
	{
		std::size_t index = str.find(suffix, str.size() - suffix.size());
		return (index != std::string::npos);
	}

	bool loop_closure::createRosIO() {
		pose_pub = nh.advertise<nav_msgs::Odometry>(
			"correct_pose", 3);
		
		cam0_img_sub.subscribe(nh, "/rs2_ros/stereo/left/image_rect_raw", 100);
		cam1_img_sub.subscribe(nh, "/rs2_ros/stereo/right/image_rect_raw", 100);
		odom_sub.subscribe(nh, "/firefly_sbx/vio/odom",100);
		// process_sub.connectInput(cam0_img_sub, cam1_img_sub,odom_sub);
		// process_sub.registerCallback(&loop_closure::ProcessorCallback, this);
		sync_ = new  message_filters::Synchronizer<SyncPolicy>(SyncPolicy(60), cam0_img_sub, cam1_img_sub, odom_sub);  
		sync_->registerCallback(boost::bind(&loop_closure::ProcessorCallback, this, _1, _2,_3)); 

		return true;
	}
	void loop_closure::ProcessorCallback(const sensor_msgs::ImageConstPtr& cam0_img,
    								const sensor_msgs::ImageConstPtr& cam1_img,
    								const nav_msgs::Odometry::ConstPtr& odom_msg)
	{

			// Get the current image.
		cam0_curr_img_ptr = cv_bridge::toCvShare(cam0_img);
		cam1_curr_img_ptr = cv_bridge::toCvShare(cam1_img);
				
		cam0_img_input = cam0_curr_img_ptr->image;
		cam1_img_input = cam1_curr_img_ptr->image;
		timestamp = cam0_img->header.stamp.toSec();
		updateImg(cam0_img_input,cam1_img_input,timestamp);

		// ROS_INFO("=====================MileStone 1======================");
		//获得Msckf算出的位姿，设定Frame Pose
		//msg.pose.pose.orientation---->quaternion---->Rotation Matrix
		//msg.pose.pose.translation.x/y/z ---->Translation Matrix
		Eigen::Isometry3d T_b_w;
		Eigen::Quaterniond q (	odom_msg->pose.pose.orientation.w,
								odom_msg->pose.pose.orientation.x,
								odom_msg->pose.pose.orientation.y,
								odom_msg->pose.pose.orientation.z);
		Eigen::Translation3d t(	odom_msg->pose.pose.position.x,
							 	odom_msg->pose.pose.position.y,
								odom_msg->pose.pose.position.z);

		Eigen::Matrix3d R = q.toRotationMatrix(); 
		Eigen::Matrix4d T;
		cv::Mat T_c_w(4,4,CV_32F);
		T   << 	R(0,0),R(0,1),R(0,2),odom_msg->pose.pose.position.x,
				R(1,0),R(1,1),R(1,2),odom_msg->pose.pose.position.y,
				R(2,0),R(2,1),R(2,2),odom_msg->pose.pose.position.z,
				0,     0,     0,     1;
		T_c_w = converter.toCvMat(T);

		// ROS_INFO("=====================MileStone 2======================");

		tf::poseMsgToEigen(odom_msg->pose.pose,T_b_w); //得到Msckf 算出的位姿　用于构造KF　odom_msg.pose.pose－> T_b_w;
		// ROS_INFO("=====================MileStone 3======================");

		// T_c_w = converter.toCvMat(T_b_w);
	
		createFrame(imgQueue.back());

		// ROS_INFO("=====================MileStone 4======================");

		frameQueue.back().SetPose(T_c_w);

		// ROS_INFO("=====================MileStone 5======================");

		if (!mpKeyFrameDatabase->getKFDB().size())
		{
			// ROS_INFO("=====================Checkpoint 1======================");
			KFInitialization();
		}
		else
		{
			// ROS_INFO("=====================Checkpoint 2======================");
			creatKF();
		}
		// cout << "cam timestamp=" << timestamp << endl;
		// cout << "pose timestamp=" <<  odom_msg->header.stamp.toSec() << endl;
  		// cout << "Position-> x: " << odom_msg->pose.pose.position.x << "y: " << odom_msg->pose.pose.position.y << "z: " << odom_msg->pose.pose.position.z << endl;
  		// cout << "Orientation-> x: " << odom_msg->pose.pose.orientation.x << "y: " << odom_msg->pose.pose.orientation.y 
		//   << "z: " << odom_msg->pose.pose.orientation.z << "w: " << odom_msg->pose.pose.orientation.w << endl;
		
		
		return;
	}

	loop_closure::loop_closure(ros::NodeHandle& n):nh(n)
	{
		return;
	}

	loop_closure::~loop_closure() 
	{
		destroyAllWindows();
		return;
	}


	bool loop_closure::initialize() {
		string strSettingPath = "/home/vtkc/Desktop/tlab/orb_slam2_vanilla/ORB_SLAM2/Examples/Stereo/KITTI04-12.yaml";
        string strVocFile = "/home/vtkc/Desktop/tlab/orb_slam2_vanilla/ORB_SLAM2/Vocabulary/ORBvoc.txt";

        //Check settings file opencv 读取 配置 文件
	    cv::FileStorage fsSettings(strSettingPath.c_str(), cv::FileStorage::READ);
	    if(!fsSettings.isOpened())
	    {
			cerr << "打不开设置文件 :  " << strSettingPath << endl;
			exit(-1);
		}
		imgQueue.clear();
		cv::FileStorage fSettings(strSettingPath, cv::FileStorage::READ);//读取配置文件
		//【1】------------------ 相机内参数矩阵 K------------------------
	    //     |fx  0   cx|
	    // K = |0   fy  cy|
	    //     |0   0   1 |
	    float fx = fSettings["Camera.fx"];
	    float fy = fSettings["Camera.fy"];
	    float cx = fSettings["Camera.cx"];
	    float cy = fSettings["Camera.cy"];
	    cv::Mat K = cv::Mat::eye(3,3,CV_32F);// 初始化为 对角矩阵
	    K.at<float>(0,0) = fx;
	    K.at<float>(1,1) = fy;
	    K.at<float>(0,2) = cx;
	    K.at<float>(1,2) = cy;
	    K.copyTo(mK);// 拷贝到 类内变量 mK 为类内 可访问变量
	    
 		// 【2】-------畸变校正 参数----------------------------------------
	    cv::Mat DistCoef(4,1,CV_32F);// 相机畸变矫正 矩阵
	    DistCoef.at<float>(0) = fSettings["Camera.k1"];
	    DistCoef.at<float>(1) = fSettings["Camera.k2"];
	    DistCoef.at<float>(2) = fSettings["Camera.p1"];
	    DistCoef.at<float>(3) = fSettings["Camera.p2"];
	    const float k3 = fSettings["Camera.k3"];
	    if(k3!=0)
	    {
		DistCoef.resize(5);
		DistCoef.at<float>(4) = k3;
	    }
	    DistCoef.copyTo(mDistCoef);// 拷贝到 类内变量

	    mbf = fSettings["Camera.bf"];// 基线 * fx 
        
		//----------------拍摄 帧率---------------------------
	    float fps = fSettings["Camera.fps"];
	    if(fps==0)
		fps=30;

	    // Max/Min Frames to insert keyframes and to check relocalisation
	    // 关键帧 间隔
	    mMinFrames = 0;
	    mMaxFrames = fps;
		// 【3】------------------显示参数--------------------------
	    cout << endl << "相机参数  Camera Parameters: " << endl;
	    cout << "-- fx: " << fx << endl;
	    cout << "-- fy: " << fy << endl;
	    cout << "-- cx: " << cx << endl;
	    cout << "-- cy: " << cy << endl;
	    cout << "-- k1: " << DistCoef.at<float>(0) << endl;
	    cout << "-- k2: " << DistCoef.at<float>(1) << endl;
	    if(DistCoef.rows==5)
		cout << "-- k3: " << DistCoef.at<float>(4) << endl;
	    cout << "-- p1: " << DistCoef.at<float>(2) << endl;
	    cout << "-- p2: " << DistCoef.at<float>(3) << endl;
	    cout << "-- fps: " << fps << endl;
	    

		//【4】-----------载入 ORB特征提取参数  Load ORB parameters------------------------------------
	    // 每一帧提取的特征点数 1000
	    int nFeatures = fSettings["ORBextractor.nFeatures"];          //每张图像提取的特征点总数量 2000
	    // 图像建立金字塔时的变化尺度 1.2
	    float fScaleFactor = fSettings["ORBextractor.scaleFactor"]; //尺度因子1.2  图像金字塔 尺度因子 
	    // 尺度金字塔的层数 8
	    int nLevels = fSettings["ORBextractor.nLevels"];// 金字塔总层数 8
	    // 提取fast特征点的默认阈值 20
	    int fIniThFAST = fSettings["ORBextractor.iniThFAST"];// 快速角点提取 算法参数  阈值
	     // 如果默认阈值提取不出足够fast特征点，则使用最小阈值 8
	    int fMinThFAST = fSettings["ORBextractor.minThFAST"];//                                  最低阈值


        mThDepth = mbf*(float)fSettings["ThDepth"]/fx;//深度 阈值
		cout << endl << "深度图阈值 Depth Threshold (Close/Far Points): " << mThDepth << endl;
	    	    

        nFeatures=2000;
        fScaleFactor=1.2;
        nLevels=8;
        fIniThFAST=20;
        fMinThFAST=7;

        mpORBextractorLeft = new ORBextractor(nFeatures,fScaleFactor,nLevels,fIniThFAST,fMinThFAST);
        mpORBextractorRight = new ORBextractor(nFeatures,fScaleFactor,nLevels,fIniThFAST,fMinThFAST);
        oe = new ORBextractor(nFeatures,fScaleFactor,nLevels,fIniThFAST,fMinThFAST);

    	
	      
	    // 配置文件中读取 点云精度 设置 for point cloud resolution
	    // float resolution = fsSettings["PointCloudMapping.Resolution"];

	    //Load ORB Vocabulary
	    cout << endl << "加载 ORB词典. This could take a while..." << endl;

	    /*
	       使用 new创建对象   类似在 堆空间中申请内存 返回指针
	       使用完后需使用delete删除
	       
	    */
	  	//  打开字典文件
	  	/////// ////////////////////////////////////
	    clock_t tStart = clock();//时间开始
		
		// 1. 创建字典 mpVocabulary = new ORBVocabulary()；并从文件中载入字典=========================
	    mpVocabulary = new ORBVocabulary();//关键帧字典数据库
	    
		//bool bVocLoad = mpVocabulary->loadFromTextFile(strVocFile);
	    bool bVocLoad = false; //  bool量  打开字典flag
	    
		if (has_suffix(strVocFile, ".txt"))//
		  bVocLoad = mpVocabulary->loadFromTextFile(strVocFile);//txt格式打开  
		
		// -> 指针对象 的 解引用和 访问成员函数  相当于  (*mpVocabulary).loadFromTextFile(strVocFile);
	    // else
		//   bVocLoad = mpVocabulary->loadFromBinaryFile(strVocFile);//bin格式打开
	    if(!bVocLoad)
	    {
		cerr << "字典路径错误 " << endl;
		cerr << "打开文件错误: " << strVocFile << endl;
		exit(-1);
	    }
	    printf("数据库载入时间 Vocabulary loaded in %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);//显示文件载入时间 秒
	  	///////////////////////////////////////////


		// 2. 使用特征字典mpVocabulary 创建关键帧数据库 KeyFrameDatabase===================
	    mpKeyFrameDatabase = new KeyFrameDatabase(*mpVocabulary);
		mpKeyFrameDatabase->clearKFDB();
		
		// 3. 创建地图对象   Map=============================================
	    mpMap = new Map();

		// 4. 创建地图显示 帧显示 两个显示窗口  Create Drawers. These are used by the Viewer
	    // mpFrameDrawer = new FrameDrawer(mpMap);//关键帧显示
	    // mpMapDrawer = new MapDrawer(mpMap, strSettingsFile);//地图显示
        // mpFrameDrawer = new FrameDrawer(mpMap, mpMapDrawer, strSettingsFile);//关键帧显示

        // ROS_INFO("Object loop_closure created");

		//Initialize the Local Mapping thread and launch
		mpLocalMapper = new LocalMapping(mpMap, mSensor==MONOCULAR);
		mptLocalMapping = new thread(&msckf_vio::LocalMapping::Run,mpLocalMapper);

		//Initialize the Loop Closing thread and launch
		mpLoopCloser = new LoopClosing(nh, mpMap, mpKeyFrameDatabase, mpVocabulary, mSensor!=MONOCULAR);
		mptLoopClosing = new thread(&msckf_vio::LoopClosing::Run, mpLoopCloser);

		mpLocalMapper->SetLoopCloser(mpLoopCloser);
		mpLoopCloser->SetLocalMapper(mpLocalMapper);

		//////////////////////////////////////////////////////////
		if (!createRosIO()) return false;
 		ROS_INFO("===========================================");
 		ROS_INFO("Finish Initializing Loop_Closure");
		ROS_INFO("===========================================");
		//////////////////////////////////////////////////////////
		return true;
	}

    loop_closure::loop_closure()
    {
        return;
    }

    void loop_closure::updateImg(Mat img0, Mat img1, double timestamp){

		imgQueue.push_back(make_pair(make_pair(img0, img1), timestamp));
		// ROS_INFO("===========================================");
 		// ROS_INFO("Im at updateImg!!!!!!!!!!!!!!!!!!!!!!!!!!");
		// ROS_INFO("===========================================");
        
		return;
    }

    void loop_closure::createFrame(pair<pair<Mat, Mat>, double> imgData)
    {
		// unique_lock<mutex> lock(globalLock);
		// unique_lock<mutex> lock2(loopLock);
        newFrame = Frame(imgData.first.first, imgData.first.second, imgData.second, 
			mpORBextractorLeft, mpORBextractorRight,mpVocabulary,mK,mDistCoef,mbf,mThDepth); 
		frameQueue.push_back(newFrame);
		// ROS_INFO("===========================================");
 		// ROS_INFO("Im at CreateFrame!!!!!!!!!!!!!!!!!!!!!!!!!!");
		// ROS_INFO("===========================================");
		
    }

    void loop_closure::KFInitialization()
	{
	    if(frameQueue.back().N>500)
  		// 【0】找到的关键点个数 大于 500 时进行初始化将当前帧构建为第一个关键帧
	    {
		// Set Frame pose to the origin
       	//【1】 初始化 第一帧为世界坐标系原点 变换矩阵 对角单位阵 R = eye(3,3)   t=zero(3,1)
		// 步骤1：设定初始位姿
		frameQueue.back().SetPose(cv::Mat::eye(4,4,CV_32F));

       	// 【2】创建第一帧为关键帧  Create KeyFrame  普通帧      地图       关键帧数据库
		// 加入地图 加入关键帧数据库
		// 步骤2：将当前帧构造为初始关键帧
		// mCurrentFrame的数据类型为Frame
		// KeyFrame包含Frame、地图3D点、以及BoW
		// KeyFrame里有一个mpMap，Tracking里有一个mpMap，而KeyFrame里的mpMap都指向Tracking里的这个mpMap
		// KeyFrame里有一个mpKeyFrameDB，Tracking里有一个mpKeyFrameDB，而KeyFrame里的mpMap都指向Tracking里的这个mpKeyFrameDB
		
		KeyFrame* pKFini = new KeyFrame(frameQueue.back(),mpMap,mpKeyFrameDatabase);
		// 地图添加第一帧关键帧 关键帧存入地图关键帧set集合里 Insert KeyFrame in the map
      
		// KeyFrame中包含了地图、反过来地图中也包含了KeyFrame，相互包含
		// 步骤3：在地图中添加该初始关键帧
		mpMap->AddKeyFrame(pKFini);// 地图添加 关键帧

		// Create MapPoints and asscoiate to KeyFrame
    	// 【3】创建地图点 并关联到 相应的关键帧  关键帧也添加地图点  地图添加地图点 地图点描述子 距离
		// 步骤4：为每个特征点构造MapPoint		
		for(int i=0; i<frameQueue.back().N;i++)// 该帧的每一个关键点
		{
		    float z = frameQueue.back().mvDepth[i];// 关键点对应的深度值  双目和 深度相机有深度值
		    if(z>0)// 有效深度 
		    {
		   	// 步骤4.1：通过反投影得到该特征点的3D坐标  
			cv::Mat x3D = frameQueue.back().UnprojectStereo(i);// 投影到 在世界坐标系下的三维点坐标
		   	// 步骤4.2：将3D点构造为MapPoint	
			// 每个 具有有效深度 关键点 对应的3d点 转换到 地图点对象
			MapPoint* pNewMP = new MapPoint(x3D,pKFini,mpMap);
		  	// 步骤4.3：为该MapPoint添加属性：
			// a.观测到该MapPoint的关键帧
			// b.该MapPoint的描述子
			// c.该MapPoint的平均观测方向和深度范围
			
        	// a.表示该MapPoint可以被哪个KeyFrame的哪个特征点观测到
			pNewMP->AddObservation(pKFini,i);// 地图点添加 观测 参考帧 在该帧上可一观测到此地图点
			 // b.从众多观测到该MapPoint的特征点中挑选区分读最高的描述子
			pNewMP->ComputeDistinctiveDescriptors();// 地图点计算最好的 描述子
			// c.更新该MapPoint平均观测方向以及观测距离的范围
			// 该地图点平均观测方向与观测距离的范围，这些都是为了后面做描述子融合做准备。
			pNewMP->UpdateNormalAndDepth();
			// 更新 相对 帧相机中心 单位化相对坐标  金字塔层级 距离相机中心距离
		   	// 步骤4.4：在地图中添加该MapPoint
			mpMap->AddMapPoint(pNewMP);// 地图 添加 地图点
                   // 步骤4.5：表示该KeyFrame的哪个特征点可以观测到哪个3D点
			 pKFini->AddMapPoint(pNewMP,i);
		   	// 步骤4.6：将该MapPoint添加到当前帧的mvpMapPoints中
                        // 为当前Frame的特征点与MapPoint之间建立索引
			frameQueue.back().mvpMapPoints[i]=pNewMP;//当前帧 添加地图点
		    }
		}
		// cout << "新地图创建成功 new map ,具有 地图点数 : " << mpMap->MapPointsInMap() << "  地图点 points" << endl;



 		// 步骤5：在局部地图中添加该初始关键帧
		// 【4】局部建图添加关键帧  局部关键帧添加关键帧     局部地图点添加所有地图点
		mpLocalMapper->InsertKeyFrame(pKFini);
               // 记录
		// mLastFrame = Frame(mCurrentFrame);// 上一个 普通帧
		// mnLastKeyFrameId=mCurrentFrame.mnId;// id
	 	// mpLastKeyFrame = pKFini;// 上一个关键帧
               // 局部
		// mvpLocalKeyFrames.push_back(pKFini);// 局部关键帧 添加 关键帧
		// mvpLocalMapPoints=mpMap->GetAllMapPoints();//局部地图点  添加所有地图点
		// mpReferenceKF = pKFini;// 参考帧
		// newFrame.mpReferenceKF = pKFini;//当前帧 参考关键帧
                // 地图
		// mpMap->SetReferenceMapPoints(mvpLocalMapPoints);//地图 参考地图点
		mpMap->mvpKeyFrameOrigins.push_back(pKFini);// 地图关键帧
                // 可视化
		// mpMapDrawer->SetCurrentCameraPose(newFrame.mTcw);
		// mState=OK;// 跟踪正常
	    }
	}

	/**
 * @brief 创建新的关键帧
 *
 * 对于非单目的情况，同时创建新的MapPoints
 */
	void loop_closure::creatKF()
	{
	    // if(!mpLocalMapper->SetNotStop(true))
		// return;
	    // 关键帧 加入到地图 加入到 关键帧数据库
	    
// 步骤1：将当前帧构造成关键帧	    
	    KeyFrame* pKF = new KeyFrame(frameQueue.back(),mpMap,mpKeyFrameDatabase);
	    
// 步骤2：将当前关键帧设置为当前帧的参考关键帧
    // 在UpdateLocalKeyFrames函数中会将与当前关键帧共视程度最高的关键帧设定为当前帧的参考关键帧
	    // mpReferenceKF = pKF;
	    // newFrame.mpReferenceKF = pKF;
	    
    // 这段代码和UpdateLastFrame中的那一部分代码功能相同
// 步骤3：对于双目或rgbd摄像头，为当前帧生成新的MapPoints
	    // if(mSensor != System::MONOCULAR)
	    
	      // 根据Tcw计算mRcw、mtcw和mRwc、mOw
		frameQueue.back().UpdatePoseMatrices();

		// We sort points by the measured depth by the stereo/RGBD sensor.
		// We create all those MapPoints whose depth < mThDepth.
		// If there are less than 100 close points we create the 100 closest.
		// 双目 / 深度
     // 步骤3.1：得到当前帧深度小于阈值的特征点
               // 创建新的MapPoint, depth < mThDepth
		vector<pair<float,int> > vDepthIdx;
		vDepthIdx.reserve(frameQueue.back().N);
		for(int i=0; i<frameQueue.back().N; i++)
		{
		    float z = frameQueue.back().mvDepth[i];
		    if(z>0)
		    {
			vDepthIdx.push_back(make_pair(z,i));
		    }
		}

		if(!vDepthIdx.empty())
		{
	         // 步骤3.2：按照深度从小到大排序  
		    sort(vDepthIdx.begin(),vDepthIdx.end());
                 // 步骤3.3：将距离比较近的点包装成MapPoints
		    int nPoints = 0;
		    for(size_t j=0; j<vDepthIdx.size();j++)
		    {
			int i = vDepthIdx[j].second;

			bool bCreateNew = false;

			MapPoint* pMP = frameQueue.back().mvpMapPoints[i];
			if(!pMP)
			    bCreateNew = true;
			else if(pMP->Observations()<1)
			{
			    bCreateNew = true;
			    frameQueue.back().mvpMapPoints[i] = static_cast<MapPoint*>(NULL);
			}

			if(bCreateNew)
			{
			    cv::Mat x3D = frameQueue.back().UnprojectStereo(i);
			    MapPoint* pNewMP = new MapPoint(x3D,pKF,mpMap);
			    // 这些添加属性的操作是每次创建MapPoint后都要做的
			    pNewMP->AddObservation(pKF,i);
			    pKF->AddMapPoint(pNewMP,i);
			    pNewMP->ComputeDistinctiveDescriptors();
			    pNewMP->UpdateNormalAndDepth();
			    mpMap->AddMapPoint(pNewMP);

			    frameQueue.back().mvpMapPoints[i]=pNewMP;
			    nPoints++;
			}
			else
			{
			    nPoints++;
			}
                // 这里决定了双目和rgbd摄像头时地图点云的稠密程度
                // 但是仅仅为了让地图稠密直接改这些不太好，
                // 因为这些MapPoints会参与之后整个slam过程
			if(vDepthIdx[j].first>mThDepth && nPoints>100)
			    break;
		    }
		}
	    

	    mpLocalMapper->InsertKeyFrame(pKF);

	    mpLocalMapper->SetNotStop(false);


	    // mnLastKeyFrameId = newFrame.mnId;
	    // mpLastKeyFrame = pKF;
	}
	

    // void loop_closure::run(){
    //     while(1){
    //         if(imgQueue.size()){
    //             createFrame(*imgQueue.begin());
	// 			imgQueue.erase(imgQueue.begin());
	// 			if (!mpKeyFrameDatabase->getKFDB().size())
	// 			{
	// 				KFInitialization();
	// 			}
	// 			else
	// 			{
	// 				creatKF();
	// 			}
				
    //         }
    //     }
    //     return;
    // }
}