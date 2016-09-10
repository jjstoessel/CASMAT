//
//  IMUSANT_weighted_strength_vectors.cpp
//  catsmat
//
//  Created by Derrick Hill on 10/09/2016.
//
//

#include "IMUSANT_weighted_strength_vectors.h"

#include <vector>


namespace IMUSANT {
    
    void
    IMUSANT_weighted_strength_vectors::
    visit(IMUSANT_consolidated_interval_profile_LBDM *target)
    {
        if (target->isBoundary())
        {
            vector<float> next_segment;
            segments.push_back(next_segment);
            fCurrentSegmentIndex++;
        }
        
        segments[fCurrentSegmentIndex].push_back(target->getWeightedAverage());
    }
}

