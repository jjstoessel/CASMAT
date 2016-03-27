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
    // INTERVAL PROFILES
    //
    
    void
    IMUSANT_interval_profile::
    initialise(vector<float>::size_type number_of_elements)
    {
        intervals.assign(number_of_elements, 0);
    }
    
    void
    IMUSANT_IOI_interval_profile::
    addProfileEntry(int index, IMUSANT_vector<S_IMUSANT_note> notes)
    {
        // Onset Interval Profile is just a vector containing the duration of each note.
        intervals[index] = notes[index]->duration()->asAbsoluteNumeric();
    }
    
    void
    IMUSANT_pitch_interval_profile::
    addProfileEntry(int index, IMUSANT_vector<S_IMUSANT_note> notes)
    {
        // Pitch Interval Profile is a vector containing the pitch of each note.
        // REVISIT - error handling required - this code is not safe.
        intervals[index] = notes[index]->pitch()->getTPC();
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
        
        for (int index = 0; index < notes.size(); index++)
        {
            ioi_interval_profile.addProfileEntry(index, notes);
            pitch_interval_profile.addProfileEntry(index, notes);
        }
    }
    
}