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
    IMUSANT_interval_profile::
    calculateChangeVector()
    {
        // The degree of change for the first interval is itself.
        change_vector.push_back(intervals[0]);
        
        // The degree of change for subsequent intervals is calculated.
        for (int index = 0; index < intervals.size() - 1; index++)
        {
            float value1 = intervals[index];
            float value2 = intervals[index + 1];
            float degree_of_change = 0;
            
            if (value1 + value2 != 0
                &&
                value1 >= 0
                &&
                value2 >= 0)
            {
                degree_of_change = fabs(value1 - value2)  / (value1 + value2);
            }
            
            change_vector.push_back(degree_of_change);
        }
    }
    
    void
    IMUSANT_interval_profile::
    calculateStrengthVector()
    {
        strength_vector.clear();
        
        for (int index = 0; index < intervals.size() - 1; index++)
        {
            float interval_value = intervals[index];
            float preceding_change_value = change_vector[index];
            float succeeding_change_value = change_vector[index+1];
            
            float boundary_strength = interval_value * (preceding_change_value + succeeding_change_value);
            strength_vector.push_back(boundary_strength);
        }
    }
    
    void
    IMUSANT_IOI_interval_profile::
    addProfileEntry(int index, IMUSANT_vector<S_IMUSANT_note> &notes)
    {
        // Onset Interval Profile is just a vector containing the duration of each note.
        intervals[index] = notes[index]->duration()->asAbsoluteNumeric();
    }
    
    void
    IMUSANT_pitch_interval_profile::
    addProfileEntry(int index, IMUSANT_vector<S_IMUSANT_note> &notes)
    {
        // Pitch Interval Profile is a vector containing the pitch of each note.
        // REVISIT - error handling required - this code is not safe.
        
        intervals[index] = IMUSANT_pitch::tpcUndefined;
        S_IMUSANT_pitch pitch = notes[index]->pitch();
        
        if (pitch != NULL)
        {
            int midi_key_number = pitch->getMidiKeyNumber();
            intervals[index] = midi_key_number;
        }
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
        pitch_interval_profile.initialise(notes.size());
        
        for (int index = 0; index < notes.size(); index++)
        {
            ioi_interval_profile.addProfileEntry(index, notes);
            pitch_interval_profile.addProfileEntry(index, notes);
        }
    }
    
}