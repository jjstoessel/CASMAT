//
//  IMUSANT_segmented_part_LBDM.cpp
//  imusant
//
//  Created by Derrick Hill on 19/03/2016.
//
//

#include "IMUSANT_segmented_part_LBDM.h"
#include "math.h"

namespace IMUSANT
{
    
    //
    // IMUSANT_IOI_interval_profile
    //
    
    void
    IMUSANT_IOI_interval_profile::
    initialise(vector<float>::size_type number_of_elements)
    {
        onsets.reserve(number_of_elements);
        intervals.reserve(number_of_elements);
        onsets[0] = 0;
    }
    
    void
    IMUSANT_IOI_interval_profile::
    addProfileEntry(int index, IMUSANT_vector<S_IMUSANT_note> notes)
    {
        float next_duration = 0;
        next_duration += notes[index]->duration()->asAbsoluteNumeric();
        onsets[index] = onsets[index-1] + next_duration;
        
        intervals[index] = fabs(onsets[index+1] - onsets[index]);
    }
    
    //
    // IMUSANT_segmented_part_LBDM
    //
    
    
    void
    IMUSANT_segmented_part_LBDM::
    buildIntervalProfiles()
    {
        IMUSANT_vector<S_IMUSANT_note> notes = fPart->notes();
        ioi_interval_profile.initialise(notes.size());
        
        for (int index = 1; index < notes.size(); index++)
        {
            ioi_interval_profile.addProfileEntry(index, notes);
            
        }
    }
    
}