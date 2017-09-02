//
//  LBDM_SegmentedNoteVectors.cpp
//  catsmat
//
//  Created by Derrick Hill on 17/09/2016.
//
//

#include "LBDM_SegmentedNoteVectors.h"

namespace CATSMAT {
    
    void
    LBDM_SegmentedNoteVectors::
    visit(LBDM_ConsolidatedIntervalProfile *target)
    {
        if (target->isBoundary())
        {
            IMUSANT_note_vector next_segment;
            segments.push_back(next_segment);
            fCurrentSegmentIndex++;
        }
        
        segments[fCurrentSegmentIndex].push_back(target->getEndNote());
    }
}
