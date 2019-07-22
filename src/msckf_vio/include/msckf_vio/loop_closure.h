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

using namespace std;
using namespace cv;

namespace msckf_vio{
    class loop_closure{
        public:
            loop_closure(Mat img, bool& refresh);
            void run();
            void task1(string msg);
            void update(Mat img, bool& refresh);
            void getFAST(Mat& mask, vector<KeyPoint>& allPoints);
        private:
            bool* refreshPtr;
            Mat cam0_img;
            ORBextractor* oe;
            // void getORBfeatures(const Mat& img, vector<KeyPoint>& orbKeyPoints);
            // Mat getImg();
            // vector<KeyPoint> getOrbKeyPoints();
            // // void task1(string msg);
            // Mat imgORB;
            // vector<KeyPoint> orbKeyPointsORB;
    };
}

#endif