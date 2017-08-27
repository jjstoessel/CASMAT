
#ifndef __LBDM_SegmentedProfileVectors__
#define __LBDM_SegmentedProfileVectors__

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

#endif /* defined(__LBDM_SegmentedProfileVectors__) */
