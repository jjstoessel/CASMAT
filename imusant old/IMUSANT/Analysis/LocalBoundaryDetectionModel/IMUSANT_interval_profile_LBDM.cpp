//
//  IMUSANT_interval_profile_LBDM.cpp
//  imusant
//
//  Created by Derrick Hill on 14/04/2016.
//
//

#include "IMUSANT_interval_profile_LBDM.h"
#include "IMUSANT_note.h"

#include <math.h>

//
// INTERVAL PROFILES
//

namespace IMUSANT
{
    
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
        
        int index;
        for (index = 0; index < intervals.size() - 1; index++)
        {
            float interval_value = intervals[index];
            float preceding_change_value = change_vector[index];
            float succeeding_change_value = change_vector[index+1];
            
            float boundary_strength = interval_value * (preceding_change_value + succeeding_change_value);
            strength_vector.push_back(boundary_strength);
        }
        
        float last_value_ignoring_succeeding_change_value = intervals[index] * change_vector[index];
        
        strength_vector.push_back(last_value_ignoring_succeeding_change_value);
    }
    
    ostream&
    operator<< (ostream& os, const IMUSANT_interval_profile& profile)
    {
        os << "INTERVALS" << endl;
        profile.printFloatVector(os, profile.intervals);
        
        os << endl << "CHANGE VECTOR" << endl;
        profile.printFloatVector(os, profile.change_vector);
        
        os << endl << "STRENGTH VECTOR" << endl;
        profile.printFloatVector(os, profile.strength_vector);
        
        return os;
    }
    
    ostream&
    IMUSANT_interval_profile::
    printFloatVector(ostream& os, const vector<float>& the_vector) const
    {
        if (the_vector.size() == 0)
        {
            os << "Empty Vector" << endl;
        }
        else
        {
            os << the_vector[0];
            for (int index = 1 ; index < the_vector.size(); index++)
            {
                os << ", " << the_vector[index];
            }
            os << endl;
        }
        return os;
    }


    
    // ****** IOI Interval Profile ******** //
    
    void
    IMUSANT_IOI_interval_profile::
    addProfileEntry(int index, IMUSANT_vector<S_IMUSANT_note> &notes)
    {
        // Onset Interval Profile is just a vector containing the duration of each note.
        intervals[index] = notes[index]->duration()->asAbsoluteNumeric();
    }
  
    // ******** PITCH Interval Profile ******** //
    void
    IMUSANT_pitch_interval_profile::
    addProfileEntry(int index, IMUSANT_vector<S_IMUSANT_note> &notes)
    {
        // Pitch Interval Profile is a vector containing the pitch of each note.
        // REVISIT - error handling required - this code is not safe.
        
        //
        // The degree of change from a pitched note to an unpitched note (e.g a rest)
        // is the pitch of the pitched note.  For example, from C4 (Midi 60) to a rest
        // is a change of 60.
        //
        
        intervals[index] = 0; 
        S_IMUSANT_pitch pitch = notes[index]->pitch();
        
        if (pitch != NULL)
        {
            int midi_key_number = pitch->getMidiKeyNumber();
            intervals[index] = midi_key_number;
        }
    }
    
    // ******** REST Interval Profile ******** //
    void
    IMUSANT_rest_interval_profile::
    addProfileEntry(int index, IMUSANT_vector<S_IMUSANT_note> &notes)
    {
        // Rest Interval Profile is a vector containing the ???? of each rest.
        // REVISIT - error handling required - this code is not safe.
        
        if (notes[index]->getType() == IMUSANT_NoteType::rest)
        {
            intervals[index] = notes[index]->duration()->asAbsoluteNumeric();;
        }
        else
        {
            intervals[index] = 0;
        }
    }
    
}
