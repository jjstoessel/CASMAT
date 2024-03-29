//
//  I_Segmented.h
//  catsmat
//
//  Created by Derrick Hill on 25/6/17.
//
//

#ifndef __I_Segmented__
#define __I_Segmented__

#include "SetOfSegment.h"


namespace CATSMAT
{
    class I_Segmented
    {
        
    public:
        
        I_Segmented(SetOfSegment & segmentation_result) : fSegmentationResult(segmentation_result)  {}
        
        //
        // This method returns you the segments, as a set (no duplicates).
        //
        virtual SetOfSegment & getSegmentsSet() = 0;
        
    protected:
        SetOfSegment &fSegmentationResult;
        
    };
}


#endif /* __I_Segmented__ */
