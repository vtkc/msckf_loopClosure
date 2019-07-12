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

#include <msckf_vio/map_points.h>
#include <msckf_vio/image_processor.h>


using namespace std;
using namespace cv;

namespace msckf_vio{

    loop_closure::loop_closure(Mat img, bool& refresh)
    {
        cam0_img = img;
        refreshPtr = &refresh;
        ROS_INFO("Object loop_closure created");
        return;
    }

    void loop_closure::update(Mat img, bool& refresh){
        cam0_img = img;
        refreshPtr = &refresh;
        ROS_INFO("img and refreshPtr Updated!");
        return;
    }


    void loop_closure::task1(string msg)
    {
        // getORBfeatures(const Mat& img, vector<KeyPoint>& orbKeyPoints);
        ROS_INFO("Ran task1");
        return;
    }

    void loop_closure::run(){
        while(1){
            if(*refreshPtr){
                ROS_INFO("Refresh == true");
                *refreshPtr = false;
            }
        }
        return;
    }
}