#include <thread>
#include <string>
#include <iostream>
#include <algorithm>
#include <set>
#include <Eigen/Dense>
#include <msckf_vio/map_points.h>
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


#include <msckf_vio/image_processor.h>


using namespace std;
using namespace cv;

namespace msckf_vio{

    map_points::map_points(const Mat& img, vector<KeyPoint>& orbKeyPoints)
    {
        imgORB = img;
        orbKeyPointsORB = orbKeyPoints;
        // ROS_INFO("Ran loop_closure()");
        // thread t1(task1, "Thread t1");
        // t1.join();
        // terminate();
        return;
    }

    void map_points::run(){
        ROS_INFO("Ran run()");
        // thread t2(task1, "Thread t2");
        // t2.join();
        // terminate();
        return;
    }

    Mat map_points::getImg(){
        return imgORB;
    }

    vector<KeyPoint> map_points::getOrbKeyPoints(){
        return orbKeyPointsORB;
    }    


    void map_points::getORBfeatures(const Mat& img, vector<KeyPoint>& orbKeyPoints){
        Mat desc;
        Ptr<ORB> orb = ORB::create();
        orb->detectAndCompute(img, Mat(), orbKeyPoints, desc);
        ROS_INFO("Ran getORBfeatures()");
        return;
    }
}