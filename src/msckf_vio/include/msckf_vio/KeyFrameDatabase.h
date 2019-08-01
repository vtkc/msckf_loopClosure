#ifndef KEYFRAMEDATABASE_H
#define KEYFRAMEDATABASE_H

#include <vector>
#include <list>
#include <set>

#include <msckf_vio/KeyFrame.h>
#include <msckf_vio/Frame.h>
#include <msckf_vio/ORBVocabulary.h>

#include<mutex>

namespace msckf_vio{
    class KeyFrame;
    class Frame;


    class KeyFrameDatabase{
        public:

            KeyFrameDatabase(const ORBVocabulary &voc);

            void add(KeyFrame* pKF);

            void erase(KeyFrame* pKF);

            void clear();

            std::vector<list<KeyFrame*>> getKFDB();

            void clearKFDB();

            // Loop Detection
            std::vector<KeyFrame *> DetectLoopCandidates(KeyFrame* pKF, float minScore);

            // Relocalization
            std::vector<KeyFrame*> DetectRelocalizationCandidates(Frame* F);

            protected:

            // Associated vocabulary
            const ORBVocabulary* mpVoc;

            // Inverted file
            std::vector<list<KeyFrame*> > mvInvertedFile;

            // Mutex
            std::mutex mMutex;
    };
}

#endif