#ifndef ORBEXTRACTOR_H
#define ORBEXTRACTOR_H

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

using namespace std;
using namespace cv;

namespace msckf_vio{
    class ExtractorNode
    {
        public:
            ExtractorNode():bNoMore(false){}

            void DivideNode(ExtractorNode &n1, ExtractorNode &n2, ExtractorNode &n3, ExtractorNode &n4);

            std::vector<cv::KeyPoint> vKeys;
            cv::Point2i UL, UR, BL, BR;
            std::list<ExtractorNode>::iterator lit;
            bool bNoMore;
    };

    class ORBExtractor{
        public:
            ORBExtractor();
            ~ORBExtractor(){}
            void operator()(InputArray image, InputArray mask,
                            vector<cv::KeyPoint>& keypoints,
                            OutputArray descriptors);
            vector<cv::Mat> mvImagePyramid;
        protected:
            void ComputePyramid(Mat image);
            void ComputeKeyPointsOctTree(vector<vector<KeyPoint>>& allKeypoints);
            vector<KeyPoint> DistributeOctTree(const vector<KeyPoint>& vToDistributeKeys, const int &minX,
                                           const int &maxX, const int &minY, const int &maxY, const int &nFeatures, const int &level);
            int nfeatures;
            double scaleFactor;
            int nlevels;
            int iniThFAST;
            int minThFAST;
            
            vector<int> mnFeaturesPerLevel;

            vector<int> umax;

            vector<float> mvScaleFactor;
            vector<float> mvInvScaleFactor;    
            vector<float> mvLevelSigma2;
            vector<float> mvInvLevelSigma2;

    };
}
#endif