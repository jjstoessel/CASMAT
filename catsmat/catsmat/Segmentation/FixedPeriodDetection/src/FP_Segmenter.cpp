//
//  IMUSANT_fixed_period_segmenter.cpp
//  catsmat
//
//  Created by Derrick Hill on 28/1/17.
//
//

#include "FP_Segmenter.h"
#include "IMUSANT_score.h"

namespace CATSMAT {
    
    void
    FP_Segmenter::
    Visit(const IMUSANT_processing& processor)
    {
        sp = findMelodicSegmentsFixedPeriod(processor.getScores());
    }

    FP_Segmenter::SetOfSegmentsVector
    FP_Segmenter::
    findMelodicSegmentsFixedPeriod(const vector<S_IMUSANT_score>& scores)
    {
        SetOfSegmentsVector segments;
        
        for (vector<S_IMUSANT_score>::const_iterator scores_iter = scores.begin(); scores_iter != scores.end(); scores_iter++)
        {
            S_FP_SegmentedScore seg_score = new_SegmentedScoreFixedPeriod(fSegmentationResult);
            seg_score->initialise(*scores_iter);
            
           segments.push_back(seg_score->getSegmentsSet());
        }
        
        return segments;
    }
    
}
