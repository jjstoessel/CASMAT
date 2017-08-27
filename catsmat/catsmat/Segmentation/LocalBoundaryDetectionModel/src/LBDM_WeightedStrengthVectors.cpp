//
//  LBDM_WeightedStrengthVectors.cpp
//  catsmat
//
//  Created by Derrick Hill on 10/09/2016.
//
//

#include "LBDM_WeightedStrengthVectors.h"

#include <vector>


namespace CATSMAT {
    
    void
    LBDM_WeightedStrengthVectors::
    visit(IMUSANT_consolidated_interval_profile_LBDM *target)
    {
        if (target->isBoundary())
        {
            vector<double> next_segment;
            segments.push_back(next_segment);
            fCurrentSegmentIndex++;
        }
        
        segments[fCurrentSegmentIndex].push_back(target->getWeightedAverage());
    }
}

