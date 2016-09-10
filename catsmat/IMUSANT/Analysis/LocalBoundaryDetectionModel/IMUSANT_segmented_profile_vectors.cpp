//
//  IMUSANT_segmented_profile_vectors.cpp
//  catsmat
//
//  Created by Derrick Hill on 10/09/2016.
//
//

#include "IMUSANT_segmented_profile_vectors.h"

namespace IMUSANT {
    
    void
    IMUSANT_segmented_profile_vectors::
    visit(IMUSANT_consolidated_interval_profile_LBDM *target)
    {
        if (target->isBoundary())
        {
            IMUSANT_consolidated_interval_profile_vector_LBDM next_segment;
            segments.push_back(next_segment);
            fCurrentSegmentIndex++;
        }
        
        segments[fCurrentSegmentIndex].push_back(*target);
    }
}
