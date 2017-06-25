//
//  I_Segmented.h
//  catsmat
//
//  Created by Derrick Hill on 25/6/17.
//
//

#ifndef I_Segmented_h
#define I_Segmented_h

#include "IMUSANT_set_of_segment.h"


namespace CATSMAT
{
    class I_Segmented
    {
        
    public:
        
        I_Segmented(IMUSANT_set_of_segment & segmentation_result) : fSegmentationResult(segmentation_result)  {}
        
        //
        // This method returns you the segments, as a set (no duplicates).
        //
        virtual IMUSANT_set_of_segment & getSegmentsSet() = 0;
        
    protected:
        IMUSANT_set_of_segment &fSegmentationResult;
        
    };
}


#endif /* I_Segmented_h */
