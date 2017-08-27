
#ifndef __catsmat__IMUSANT_segmented_profile_vectors__
#define __catsmat__IMUSANT_segmented_profile_vectors__

#include <stdio.h>
#include <vector>

#include "LBDM_ConsolidatedIntervalProfileVisitor.h"
#include "LBDM_ConsolidatedIntervalProfile.h"

using namespace std;

namespace CATSMAT
{
    class LBDM_SegmentedProfileVectors : public LBDM_ConsolidatedIntervalProfileVisitor
    {
    public:

        LBDM_SegmentedProfileVectors() {}
        virtual ~LBDM_SegmentedProfileVectors() {}

        virtual void visit(LBDM_ConsolidatedIntervalProfile *target);
        
        vector<LBDM_ConsolidatedIntervalProfileVector> segments;
        
    private:
        
        
        int fCurrentSegmentIndex = -1;
    };
}

#endif /* defined(__catsmat__IMUSANT_segmented_profile_vectors__) */
