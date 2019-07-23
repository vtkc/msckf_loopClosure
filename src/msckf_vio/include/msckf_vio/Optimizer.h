#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include <msckf_vio/Map.h>
#include <msckf_vio/MapPoint.h>
#include <msckf_vio/KeyFrame.h>
#include <msckf_vio/LoopClosing.h>
#include <msckf_vio/Frame.h>

#include <../Thirdparty/g2o/g2o/types/types_seven_dof_expmap.h>

namespace msckf_vio {
    class LoopClosing;

    class Optimizer
    {
    public:
        void static BundleAdjustment(const std::vector<KeyFrame*> &vpKF, const std::vector<MapPoint*> &vpMP,
                                    int nIterations = 5, bool *pbStopFlag=NULL, const unsigned long nLoopKF=0,
                                    const bool bRobust = true);
        void static GlobalBundleAdjustemnt(Map* pMap, int nIterations=5, bool *pbStopFlag=NULL,
                                        const unsigned long nLoopKF=0, const bool bRobust = true);
        void static LocalBundleAdjustment(KeyFrame* pKF, bool *pbStopFlag, Map *pMap);
        int static PoseOptimization(Frame* pFrame);

        // if bFixScale is true, 6DoF optimization (stereo,rgbd), 7DoF otherwise (mono)
        void static OptimizeEssentialGraph(Map* pMap, KeyFrame* pLoopKF, KeyFrame* pCurKF,
                                        const LoopClosing::KeyFrameAndPose &NonCorrectedSim3,
                                        const LoopClosing::KeyFrameAndPose &CorrectedSim3,
                                        const map<KeyFrame *, set<KeyFrame *> > &LoopConnections,
                                        const bool &bFixScale);

        // if bFixScale is true, optimize SE3 (stereo,rgbd), Sim3 otherwise (mono)
        static int OptimizeSim3(KeyFrame* pKF1, KeyFrame* pKF2, std::vector<MapPoint *> &vpMatches1,
                                g2o::Sim3 &g2oS12, const float th2, const bool bFixScale);
    };
}

#endif