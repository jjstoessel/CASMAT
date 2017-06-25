//
//  SegmentContext.cpp
//  catsmat
//
//  Created by Derrick Hill on 25/6/17.
//
//

#include <stdio.h>

#include "SegmentContext.h"

namespace CATSMAT
{
    IMUSANT_SMARTP<SegmentContext> new_SegmentContext(S_IMUSANT_score score, S_IMUSANT_part part, string &segmentation_algorithm)
    {
        SegmentContext* o = new SegmentContext(score, part, segmentation_algorithm);
        assert (o!=0);
        return o;
    }
    
    S_IMUSANT_score
    SegmentContext::
    getScore()
    {
        return fScore;
    }
    
    
    S_IMUSANT_part
    SegmentContext::
    getPart()
    {
        return fPart;
    }
    
    string
    SegmentContext::
    getSegmentationAlgorithm()
    {
        return fSegmentationAlgorithm;
    }
    
}
