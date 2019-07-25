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

using namespace std;
using namespace cv;

namespace msckf_vio{

    class Frame;

    class loop_closure{
        public:
            loop_closure();
            void run();
            void updateImg(Mat img0, Mat img1);
            void creatFrame(pair<pair<Mat, Mat>, double> imgData);
            void KFInitialization();

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

            Frame* newFrame;

            vector<Frame> frameQueue;
            vector<pair<pair<Mat, Mat>, double>> imgQueue;

            //New KeyFrame rules (according to fps)
            int mMinFrames;
            int mMaxFrames;
            // void getORBfeatures(const Mat& img, vector<KeyPoint>& orbKeyPoints);
            // Mat getImg();
            // vector<KeyPoint> getOrbKeyPoints();
            // // void task1(string msg);
            // Mat imgORB;
            // vector<KeyPoint> orbKeyPointsORB;

    };
}

#endif