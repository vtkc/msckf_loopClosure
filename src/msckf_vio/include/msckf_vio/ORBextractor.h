#ifndef ORBextractor_H
#define ORBextractor_H

#include <vector>
#include <list>
#include <opencv/cv.h>

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

    class ORBextractor{
        public:
            ORBextractor(int nfeatures, float scaleFactor, int nlevels,
                 int iniThFAST, int minThFAST);
            ~ORBextractor(){}
            void operator()(InputArray image, InputArray mask,
                            vector<KeyPoint>& keypoints,
                            OutputArray descriptors);
            vector<cv::Mat> mvImagePyramid;
            int inline GetLevels(){
                return nlevels;}

            float inline GetScaleFactor(){
                return scaleFactor;}

            vector<float> inline GetScaleFactors(){
                return mvScaleFactor;
            }

            vector<float> inline GetInverseScaleFactors(){
                return mvInvScaleFactor;
            }

            vector<float> inline GetScaleSigmaSquares(){
                return mvLevelSigma2;
            }

            vector<float> inline GetInverseScaleSigmaSquares(){
                return mvInvLevelSigma2;
            }
            // void getFASTonly(InputArray _image, InputArray _mask, vector<KeyPoint>& _keypoints);
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

            vector<Point> pattern;
            
            vector<int> mnFeaturesPerLevel;

            vector<int> umax;

            vector<float> mvScaleFactor;
            vector<float> mvInvScaleFactor;    
            vector<float> mvLevelSigma2;
            vector<float> mvInvLevelSigma2;

    };
}
#endif