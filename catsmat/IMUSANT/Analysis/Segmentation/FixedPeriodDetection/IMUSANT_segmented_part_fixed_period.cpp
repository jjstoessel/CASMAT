//
//  IMUSANT_segmented_part_fixed_period.cpp
//  catsmat
//
//  Created by Derrick Hill on 29/10/2016.
//
//

#include "IMUSANT_segmented_part_fixed_period.h"

namespace IMUSANT
{
    
    void
    IMUSANT_segmented_part_fixed_period::
    initialise(S_IMUSANT_score the_score)
    {
        
        
    }
    
    //
    // This method returns you segments in the form of note vectors.  Each element of the
    // returned vector is a segment.
    //
//    vector<IMUSANT_note_vector> getSegmentsAsNoteVectors()
//    {
//        vector<IMUSANT_note_vector> v;
//        return v;
//    }
    
    S_IMUSANT_segmented_part_fixed_period new_IMUSANT_segmented_part_fixed_period()
    {
        IMUSANT_segmented_part_fixed_period* o = new IMUSANT_segmented_part_fixed_period();
        assert (o!=0);
        return o;
    }
    
    
}