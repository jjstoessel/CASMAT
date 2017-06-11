//
//  IMUSANT_segmented_note_vectors.cpp
//  catsmat
//
//  Created by Derrick Hill on 17/09/2016.
//
//

#include "IMUSANT_segmented_note_vectors.h"

namespace CATSMAT {
    
    void
    IMUSANT_segmented_note_vectors::
    visit(IMUSANT_consolidated_interval_profile_LBDM *target)
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
