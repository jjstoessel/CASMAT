//
//  IMUSANT_segmented_part_LBDM.cpp
//  imusant
//
//  Created by Derrick Hill on 19/03/2016.
//
//

#include "IMUSANT_segmented_part_LBDM.h"

#include <iomanip>

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
                 (ioi_interval_profile.strength_vector[index] * fWeightInteronsetInterval)
                 +
                 (pitch_interval_profile.strength_vector[index] * fWeightPitch)
                 +
                 (rest_interval_profile.strength_vector[index] * fWeightRest)
                )
                / 2;
            overall_local_boundary_strength_profile.push_back(weighted_avg_strength);
        }
    }
    
    ostream&
    operator<< (ostream& os, const IMUSANT_segmented_part_LBDM& segmented_part)
    {
        IMUSANT_pitch_interval_profile pitch_profile = segmented_part.pitch_interval_profile;
        IMUSANT_IOI_interval_profile ioi_profile = segmented_part.ioi_interval_profile;
        IMUSANT_rest_interval_profile rest_profile = segmented_part.rest_interval_profile;
        
        string space = "\t\t\t";
        
        os.width(10);
        
        os << "STRENGTH VECTORS" << endl;
        os << "{" << endl ;
        os << "//" << space << "PITCH" << space << "IOI" << space << "REST" << space << "WEIGHTED AVG" << endl;
        
        for (int index = 0; index < segmented_part.pitch_interval_profile.strength_vector.size(); index++)
        {
            os  << std::setprecision(5) << std::fixed
                << space << "{"
                << pitch_profile.strength_vector[index] << "," << space
                << ioi_profile.strength_vector[index] << "," << space
                << rest_profile.strength_vector[index] << "," << space   
                << segmented_part.overall_local_boundary_strength_profile[index]
                << "}," << space
                << "// " << index
                << endl;
        }
        
        os << "}" << endl;
        
        return os;
    }
    
    S_IMUSANT_segmented_part_LBDM new_IMUSANT_segmented_part_LBDM(S_IMUSANT_part the_part)
    {
        IMUSANT_segmented_part_LBDM* o = new IMUSANT_segmented_part_LBDM(the_part);
        assert (o!=0);
        return o;
    }

    
}