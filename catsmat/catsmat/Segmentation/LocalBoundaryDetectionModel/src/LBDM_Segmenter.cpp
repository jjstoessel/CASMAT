//
//  IMUSANT_part_segmenter.cpp
//  imusant
//
//  Created by Jason Stoessel on 30/06/2016.
//
//

#include "LBDM_Segmenter.h"
#include "IMUSANT_score.h"

namespace CATSMAT {
    
    void
    LBDM_Segmenter::
    Visit(const IMUSANT_processing& processor)
    {
        sp = findMelodicSegments_LBDM(processor.getScores());
    }
    
    LBDM_Segmenter::PART_SEGS_VEC
    LBDM_Segmenter::
    findMelodicSegments_LBDM(const vector<S_IMUSANT_score>& scores)
    {
        PART_SEGS_VEC segmented_parts;
        
        // We have >1 score, each of which may have >1 part.
        for (vector<S_IMUSANT_score>::const_iterator scores_iter = scores.begin(); scores_iter != scores.end(); scores_iter++)
        {
            IMUSANT_vector<S_IMUSANT_part>& parts = (*scores_iter)->partlist()->parts();
            
            for(vector<S_IMUSANT_part>::iterator parts_iter = parts.begin(); parts_iter != parts.end(); parts_iter++)
            {
                S_IMUSANT_segmented_part_LBDM seg_part = new_IMUSANT_segmented_part_LBDM(fSegmentationResult);
                seg_part->initialise(*parts_iter);
                segmented_parts.push_back(seg_part);
            }
        }
        
        return segmented_parts;
    }

}
