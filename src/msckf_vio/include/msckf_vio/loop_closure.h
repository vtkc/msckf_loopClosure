#ifndef LOOP_CLOSURE_H
#define LOOP_CLOSURE_H

#include <vector>
#include <map>
#include <boost/shared_ptr.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/video.hpp>

#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/Image.h>
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <msckf_vio/ORBextractor.h>
#include <msckf_vio/ORBVocabulary.h>
#include <msckf_vio/Frame.h>
#include <msckf_vio/LocalMapping.h>
#include <msckf_vio/LoopClosing.h>
#include <msckf_vio/Map.h>
// #include <msckf_vio/FrameDrawer.h>
// #include <msckf_vio/MapDrawer.h>
// #include <msckf_vio/Viewer.h>
using namespace std;
using namespace cv;

namespace msckf_vio{

    class KeyFrameDatabase;
    class Map;
    class Frame;
    class LocalMapping;
    class LoopClosing;

    class loop_closure{
        public:
            enum eSensor{
                MONOCULAR=0,
                STEREO=1,
                RGBD=2
            };
        
        public:
            typedef pair<pair<Mat, Mat>, double> ImgData;
            loop_closure();
            loop_closure(ros::NodeHandle& n);
            loop_closure(const loop_closure&) = delete;
            loop_closure operator=(const loop_closure&) = delete;
            ~loop_closure();

            bool initialize();
            typedef boost::shared_ptr<loop_closure> Ptr;
            typedef boost::shared_ptr<const loop_closure> ConstPtr;

            void run();
            void updateImg(Mat img0, Mat img1);

            void createFrame(ImgData imgData);

            void creatKF();

            void KFInitialization();
            void updateImg(Mat img0, Mat img1, double timestamp);

        private:
            
            ////////////////////////////////
            ORBVocabulary* mpVocabulary;
            cv::Mat mK;
            cv::Mat mDistCoef;
            float mbf;
            float mThDepth;
            ////////////////////////////////
            double timestamp;
            ORBextractor* oe;
            ORBextractor* mpORBextractorLeft;
            ORBextractor* mpORBextractorRight;

            Frame newFrame;

            vector<Frame> frameQueue;
            vector<ImgData> imgQueue;
            vector<pair<Mat, double>> fPose;

            //New KeyFrame rules (according to fps)
            int mMinFrames;
            int mMaxFrames;
            // 地图对象指针  存储 关键帧 和 地图点
            Map* mpMap;
            KeyFrameDatabase* mpKeyFrameDatabase;

            // Local Mapper. It manages the local map and performs local bundle adjustment.
            // 建图对象 指针
            LocalMapping* mpLocalMapper;
            // void getORBfeatures(const Mat& img, vector<KeyPoint>& orbKeyPoints);
            // Mat getImg();
            // vector<KeyPoint> getOrbKeyPoints();
            // // void task1(string msg);
            // Mat imgORB;
            // vector<KeyPoint> orbKeyPointsORB;

            // // 可视化对象指针
            // Viewer* mpViewer;
            // // 画关键帧对象 指针
            // FrameDrawer* mpFrameDrawer;
            // // 画地图对象 指针
            // MapDrawer* mpMapDrawer;
            ros::NodeHandle nh;
            eSensor mSensor;
            LoopClosing* mpLoopCloser;

            std::thread* mptLocalMapping;
            std::thread* mptLoopClosing;


    };

    typedef loop_closure::Ptr LoopClosurePtr;
}

#endif