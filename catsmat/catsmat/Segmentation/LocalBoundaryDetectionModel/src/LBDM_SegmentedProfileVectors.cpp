//
//  LBDM_SegmentedProfileVectors.cpp
//  catsmat
//
//  Created by Derrick Hill on 10/09/2016.
//
//

#include "LBDM_SegmentedProfileVectors.h"

namespace CATSMAT {
    
    void
    LBDM_SegmentedProfileVectors::
    visit(LBDM_ConsolidatedIntervalProfile *target)
    {
        if (target->isBoundary())
        {
            LBDM_ConsolidatedIntervalProfileVector next_segment;
            segments.push_back(next_segment);
            fCurrentSegmentIndex++;
        }
        
        segments[fCurrentSegmentIndex].push_back(*target);
    }
}
