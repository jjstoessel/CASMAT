//
//  SegmentContext.h
//  catsmat
//
// SegmentContext is designed to be injected into a segment to identify where the segment came from.
//
// S_IMUSANT_score score
// The score in which the segment is found.
//
// S_IMUSANT_part part
// The part in which the segment is found
//
// string segmentation_algorithm
// The segmentation algorithm that identified the segment as a segment.
//

#ifndef __SegmentContext__
#define __SegmentContext__


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

#endif /* __SegmentContext__ */




