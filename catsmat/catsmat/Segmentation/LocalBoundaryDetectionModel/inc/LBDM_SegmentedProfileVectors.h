
#ifndef __catsmat__IMUSANT_segmented_profile_vectors__
#define __catsmat__IMUSANT_segmented_profile_vectors__

#include <stdio.h>
#include <vector>

#include "IMUSANT_consolidated_interval_profile_LBDM_visitor.h"
#include "LBDM_ConsolidatedIntervalProfile.h"

using namespace std;

namespace CATSMAT
{
    class LBDM_SegmentedProfileVectors : public IMUSANT_consolidated_interval_profile_LBDM_visitor
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
