#include <thread>
#include <string>
#include <iostream>
#include <algorithm>
#include <set>
#include <Eigen/Dense>
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

namespace msckf_vio{

    loop_closure::loop_closure()
    {
        string strSettingPath;
        string strVocFile;

        //Check settings file opencv 读取 配置 文件
	    cv::FileStorage fsSettings(strSettingPath.c_str(), cv::FileStorage::READ);
	    if(!fsSettings.isOpened())
	    {
			cerr << "打不开设置文件 :  " << strSettingPath << endl;
			exit(-1);
		}

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
	    else
		  bVocLoad = mpVocabulary->loadFromBinaryFile(strVocFile);//bin格式打开
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
		
		// 3. 创建地图对象   Map=============================================
	    mpMap = new Map();

		// 4. 创建地图显示 帧显示 两个显示窗口  Create Drawers. These are used by the Viewer
	    // mpFrameDrawer = new FrameDrawer(mpMap);//关键帧显示
	    // mpMapDrawer = new MapDrawer(mpMap, strSettingsFile);//地图显示
        // mpFrameDrawer = new FrameDrawer(mpMap, mpMapDrawer, strSettingsFile);//关键帧显示

        ROS_INFO("Object loop_closure created");
        return;
    }

    void loop_closure::updateImg(Mat img0, Mat img1, double timestamp){

		imgQueue.push_back(make_pair(make_pair(img0, img1), timestamp));
        
		return;
    }


    // /****************** vector2Mat *********************/
    // template<typename _Tp>
    // cv::Mat loop_closure::convertVector2Mat(vector<_Tp> v, int channels, int rows)
    // {
    //     cv::Mat mat = cv::Mat(v);//将vector变成单列的mat
    //     cv::Mat dest = mat.reshape(channels, rows).clone();
    //     return dest;
    // }


    void loop_closure::createFrame(pair<pair<Mat, Mat>, double> imgData)
    {
        *newFrame = Frame(imgData.first.first, imgData.first.second, imgData.second, 
			mpORBextractorLeft, mpORBextractorRight,mpORBVocabulary,mK,mDistCoef,mbf,mThDepth); 
		frameQueue.push_back(newFrame);
    }

    void loop_closure::KFInitialization()
	{
	    if(mCurrentFrame.N>500)
  		// 【0】找到的关键点个数 大于 500 时进行初始化将当前帧构建为第一个关键帧
	    {
		// Set Frame pose to the origin
       	//【1】 初始化 第一帧为世界坐标系原点 变换矩阵 对角单位阵 R = eye(3,3)   t=zero(3,1)
		// 步骤1：设定初始位姿
		mCurrentFrame.SetPose(cv::Mat::eye(4,4,CV_32F));

       	// 【2】创建第一帧为关键帧  Create KeyFrame  普通帧      地图       关键帧数据库
		// 加入地图 加入关键帧数据库
		// 步骤2：将当前帧构造为初始关键帧
		// mCurrentFrame的数据类型为Frame
		// KeyFrame包含Frame、地图3D点、以及BoW
		// KeyFrame里有一个mpMap，Tracking里有一个mpMap，而KeyFrame里的mpMap都指向Tracking里的这个mpMap
		// KeyFrame里有一个mpKeyFrameDB，Tracking里有一个mpKeyFrameDB，而KeyFrame里的mpMap都指向Tracking里的这个mpKeyFrameDB
		
		KeyFrame* pKFini = new KeyFrame(mCurrentFrame,mpMap,mpKeyFrameDB);
		// 地图添加第一帧关键帧 关键帧存入地图关键帧set集合里 Insert KeyFrame in the map
      
		// KeyFrame中包含了地图、反过来地图中也包含了KeyFrame，相互包含
		// 步骤3：在地图中添加该初始关键帧
		mpMap->AddKeyFrame(pKFini);// 地图添加 关键帧

		// Create MapPoints and asscoiate to KeyFrame
    	// 【3】创建地图点 并关联到 相应的关键帧  关键帧也添加地图点  地图添加地图点 地图点描述子 距离
		// 步骤4：为每个特征点构造MapPoint		
		for(int i=0; i<mCurrentFrame.N;i++)// 该帧的每一个关键点
		{
		    float z = mCurrentFrame.mvDepth[i];// 关键点对应的深度值  双目和 深度相机有深度值
		    if(z>0)// 有效深度 
		    {
		   	// 步骤4.1：通过反投影得到该特征点的3D坐标  
			cv::Mat x3D = mCurrentFrame.UnprojectStereo(i);// 投影到 在世界坐标系下的三维点坐标
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
			mCurrentFrame.mvpMapPoints[i]=pNewMP;//当前帧 添加地图点
		    }
		}
		cout << "新地图创建成功 new map ,具有 地图点数 : " << mpMap->MapPointsInMap() << "  地图点 points" << endl;
 		// 步骤5：在局部地图中添加该初始关键帧
		// 【4】局部建图添加关键帧  局部关键帧添加关键帧     局部地图点添加所有地图点
		mpLocalMapper->InsertKeyFrame(pKFini);
               // 记录
		mLastFrame = Frame(mCurrentFrame);// 上一个 普通帧
		mnLastKeyFrameId=mCurrentFrame.mnId;// id
	 	mpLastKeyFrame = pKFini;// 上一个关键帧
               // 局部
		mvpLocalKeyFrames.push_back(pKFini);// 局部关键帧 添加 关键帧
		mvpLocalMapPoints=mpMap->GetAllMapPoints();//局部地图点  添加所有地图点
		mpReferenceKF = pKFini;// 参考帧
		mCurrentFrame.mpReferenceKF = pKFini;//当前帧 参考关键帧
                // 地图
		mpMap->SetReferenceMapPoints(mvpLocalMapPoints);//地图 参考地图点
		mpMap->mvpKeyFrameOrigins.push_back(pKFini);// 地图关键帧
                // 可视化
		mpMapDrawer->SetCurrentCameraPose(mCurrentFrame.mTcw);
		mState=OK;// 跟踪正常
	    }
	}

    void loop_closure::run(){
        while(1){
            if(imgQueue.size()){
                createFrame(imgQueue.begin());
				imgQueue.erase(imgQueue.begin());
            }
        }
        return;
    }
}