//
//  SegmentContext.h
//  catsmat
//
//  Created by Derrick Hill on 25/6/17.
//
//

#ifndef SegmentContext_h
#define SegmentContext_h


#include <stdio.h>

#include "libIMUSANT.h"

using namespace IMUSANT;

namespace CATSMAT
{
    class SegmentContext : public smartable
    {
    public:
        
        SegmentContext(S_IMUSANT_score score, S_IMUSANT_part part, string segmentation_algorithm)
        {
            fScore = score;
            fPart = part;
            fSegmentationAlgorithm = segmentation_algorithm;
        }
        
        virtual ~SegmentContext() {}
        
        S_IMUSANT_score getScore();
        S_IMUSANT_part getPart();
        string getSegmentationAlgorithm();
        
    private:
        S_IMUSANT_score fScore;
        S_IMUSANT_part fPart;
        string fSegmentationAlgorithm;
        
    };
    
    typedef IMUSANT_SMARTP<SegmentContext> S_SegmentContext;
    IMUSANT_SMARTP<SegmentContext> new_SegmentContext(S_IMUSANT_score score, S_IMUSANT_part part, string &segmentation_algorithm);
}

#endif /* SegmentContext_h */




