//
//  IMUSANT_interval_profile_LBDM.cpp
//  imusant
//
//  Created by Derrick Hill on 14/04/2016.
//
//

#include "IMUSANT_interval_profile_LBDM.h"
#include "IMUSANT_note.h"

#include <iomanip>
#include <math.h>

//
// INTERVAL PROFILES
//

namespace CATSMAT
{
    
    void
    IMUSANT_interval_profile::
    initialise(vector<double>::size_type number_of_elements)
    {
        profile_vector.assign(number_of_elements, 0);
    }
    
    void
    IMUSANT_interval_profile::
    calculateChangeVector()
    {
        // The degree of change for the first interval is itself.
        //change_vector.push_back(profile_vector[0]);
        change_vector.push_back(calculateDegreeOfChange(0, profile_vector[0])); //equivalent to change_vector.push_back(1);
        
        // The degree of change for subsequent intervals is calculated.
        for (int index = 0; index < profile_vector.size() - 1; index++)
        {
            double degree_of_change = calculateDegreeOfChange(profile_vector[index], profile_vector[index + 1]);
            change_vector.push_back(degree_of_change);
        }
    }
    
    double
    IMUSANT_interval_profile::
    calculateDegreeOfChange(double value1, double value2)
    {
        double degree_of_change = 0;
        
        if (value1 + value2 != 0
            &&
            value1 >= 0
            &&
            value2 >= 0)
        {
            degree_of_change = fabs(value1 - value2)  / (value1 + value2);
        }
        
        return degree_of_change;
    }
    
    void
    IMUSANT_interval_profile::
    calculateStrengthVector()
    {
        strength_vector.clear();
        
        int index;
        for (index = 0; index < profile_vector.size() - 1; index++)
        {
            double boundary_strength = calculateBoundaryStrength(profile_vector[index], change_vector[index], change_vector[index+1]);
            strength_vector.push_back(boundary_strength);
        }
        
        double last_value_ignoring_succeeding_change_value = profile_vector[index] * change_vector[index];
        
        strength_vector.push_back(last_value_ignoring_succeeding_change_value);
    }
    
    double
    IMUSANT_interval_profile::
    calculateBoundaryStrength(double interval_value, double preceding_change_value, double succeeding_change_value)
    {
        double boundary_strength = interval_value * (preceding_change_value + succeeding_change_value);
        return boundary_strength;
    }

    
    ostream&
    operator<< (ostream& os, const IMUSANT_interval_profile& profile)
    {
        profile.printVectors(os);
        return os;
    }
    
    
#define COL_WIDTH 28
#define DATA_WIDTH 16
#define SEPARATOR ' '
// #define FILL left << setw(COL_WIDTH) << setfill(SEPARATOR)
#define FILL "\t"

    ostream&
    IMUSANT_interval_profile::
    printVectors(ostream& os) const
    {
    
        if (profile_vector.size() == 0)
        {
            os << "IMUSANT_interval_profile::printVectors() - NO VALUES" << endl;
        }
        else
        {
            os << FILL << "INDEX" << FILL << "PROFILE" << FILL << "CHANGE" << FILL << "STRENGTH" << endl;
            for (int index = 0 ; index < profile_vector.size(); index++)
            {
                os << FILL << index << FILL << profile_vector[index] << FILL << change_vector[index] << FILL << strength_vector[index] << endl;
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
        profile_vector[index] = notes[index]->duration()->AsAbsoluteNumeric();
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
        
        profile_vector[index] = 0;
        S_IMUSANT_pitch pitch = notes[index]->pitch();
        
        if (pitch->name() != IMUSANT_pitch::undefined)
        {
            int midi_key_number = pitch->getMidiKeyNumber();
            profile_vector[index] = midi_key_number;
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
            profile_vector[index] = notes[index]->duration()->AsAbsoluteNumeric();;
        }
        else
        {
            profile_vector[index] = 0;
        }
    }
    
}

