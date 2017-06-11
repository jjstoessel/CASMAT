//
//  IMUSANT_fixed_period_segmenter.cpp
//  catsmat
//
//  Created by Derrick Hill on 28/1/17.
//
//

#include "IMUSANT_fixed_period_segmenter.h"
#include "IMUSANT_score.h"

namespace CATSMAT {
    
    void
    IMUSANT_fixed_period_segmenter::
    Visit(const IMUSANT_processing& processor)
    {
        sp = findMelodicSegmentsFixedPeriod(processor.getScores());
    }
    
    IMUSANT_fixed_period_segmenter::SetOfSegmentsVector
    IMUSANT_fixed_period_segmenter::
    findMelodicSegmentsFixedPeriod(const vector<S_IMUSANT_score>& scores)
    {
        SetOfSegmentsVector segments;
        
        for (vector<S_IMUSANT_score>::const_iterator scores_iter = scores.begin(); scores_iter != scores.end(); scores_iter++)
        {
            S_SegmentedScoreFixedPeriod seg_score = new_SegmentedScoreFixedPeriod();
            seg_score->initialise(*scores_iter);
            
            segments.push_back(seg_score->getSegmentsSet());
        }
        
        return segments;
    }
    
}
