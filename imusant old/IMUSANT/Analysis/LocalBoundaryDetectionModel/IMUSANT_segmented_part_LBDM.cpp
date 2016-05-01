//
//  IMUSANT_segmented_part_LBDM.cpp
//  imusant
//
//  Created by Derrick Hill on 19/03/2016.
//
//

#include "IMUSANT_segmented_part_LBDM.h"

#include <iomanip>
#include <iostream>

namespace IMUSANT
{
    //
    // IMUSANT_segmented_part_LBDM
    //
    
    vector<float> &
    IMUSANT_segmented_part_LBDM::
    getOverallLocalBoundaryStrengthProfile()
    {
        buildIntervalProfiles();
        calculateOverallLocalBoundaryStrengthVector();
        return overall_local_boundary_strength_profile;
    }
    
    
    void
    IMUSANT_segmented_part_LBDM::
    buildIntervalProfiles()
    {
        IMUSANT_vector<S_IMUSANT_note> notes = fPart->notes();
        
        ioi_interval_profile.initialise(notes.size());
        pitch_interval_profile.initialise(notes.size());
        rest_interval_profile.initialise(notes.size());
        
        for (int index = 0; index < notes.size(); index++)
        {
            ioi_interval_profile.addProfileEntry(index, notes);
            pitch_interval_profile.addProfileEntry(index, notes);
            rest_interval_profile.addProfileEntry(index, notes);
        }
        
        ioi_interval_profile.calculateChangeVector();
        pitch_interval_profile.calculateChangeVector();
        rest_interval_profile.calculateChangeVector();
        
        ioi_interval_profile.calculateStrengthVector();
        pitch_interval_profile.calculateStrengthVector();
        rest_interval_profile.calculateStrengthVector();
        
    }
    
    void
    IMUSANT_segmented_part_LBDM::
    calculateOverallLocalBoundaryStrengthVector()
    {
        overall_local_boundary_strength_profile.clear();
        
        float weighted_avg_strength = 0;
        for (int index = 0; index < ioi_interval_profile.strength_vector.size(); index++)
        {
            weighted_avg_strength =
                (
                 (ioi_interval_profile.strength_vector[index] * WEIGHT_INTERONSET_INTERVAL)
                 +
                 (pitch_interval_profile.strength_vector[index] * WEIGHT_PITCH)
                 +
                 (rest_interval_profile.strength_vector[index] * WEIGHT_REST)
                )
                / 2;
            overall_local_boundary_strength_profile.push_back(weighted_avg_strength);
        }
    }
    
    
#define NOTE_WIDTH 28
#define DATA_WIDTH 16
#define SEPARATOR ' '
#define FILL_NOTE left << setw(NOTE_WIDTH) << setfill(SEPARATOR)
#define FILL_DATA right << setw(DATA_WIDTH) << setfill(SEPARATOR) << std::setprecision(2) << std::fixed           // Set the number of decimal places in the putput.
    
    ostream&
    operator<< (ostream& os, const IMUSANT_segmented_part_LBDM& segmented_part)
    {
        os << segmented_part.print(true);
        return os;
    }
    
    string
    IMUSANT_segmented_part_LBDM::
    printForTesting() const
    {
        return print(false);
    }
    
    string
    IMUSANT_segmented_part_LBDM::
    print(bool include_notes) const
    {
        IMUSANT_vector<S_IMUSANT_note> notes = fPart->notes();
        
        stringstream ret_val;
        
        ret_val << "PART NAME - " << fPart->getPartName() << endl;
        
        ret_val << "STRENGTH VECTORS" << endl;
        
        if (include_notes)
        {
            ret_val << FILL_NOTE << "NOTE1" << FILL_NOTE << "NOTE2";
        }
        
        ret_val << FILL_DATA << "PITCH" << FILL_DATA << "IOI" << FILL_DATA << "REST" << FILL_DATA << "WEIGHTED AVG" << endl;
        
        ret_val << "{" << endl ;
        
        for (int index = 0; index < pitch_interval_profile.strength_vector.size(); index++)
        {
            if (include_notes)
            {
                ret_val
                << FILL_NOTE << "{" + (index == 0 ? "-" : notes[index - 1]->pretty_print()) + ","
                << FILL_NOTE << notes[index]->pretty_print() + ",";
            }
            else
            {
                ret_val << "{";
            }
    
            ret_val
            << FILL_DATA << pitch_interval_profile.strength_vector[index] << ","
            << FILL_DATA << ioi_interval_profile.strength_vector[index] << ","
            << FILL_DATA << rest_interval_profile.strength_vector[index] << ","
            << FILL_DATA << overall_local_boundary_strength_profile[index]
            << "},"
            << FILL_DATA << "// " << index
            << endl;
        }
        
        ret_val << "}" << endl;
        
        return ret_val.str();
    }
    
    
    S_IMUSANT_segmented_part_LBDM new_IMUSANT_segmented_part_LBDM(S_IMUSANT_part the_part)
    {
        IMUSANT_segmented_part_LBDM* o = new IMUSANT_segmented_part_LBDM(the_part);
        assert (o!=0);
        return o;
    }
}