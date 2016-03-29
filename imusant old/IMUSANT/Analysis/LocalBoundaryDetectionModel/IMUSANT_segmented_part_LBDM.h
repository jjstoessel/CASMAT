//
//  IMUSANT_segmented_part_LBDM.h
//  imusant
//
//  Created by Derrick Hill on 19/03/2016.
//
//

#ifndef __imusant__IMUSANT_segmented_part_LBDM__
#define __imusant__IMUSANT_segmented_part_LBDM__

#include <stdio.h>
#include "IMUSANT_part.h"

using namespace std;

namespace IMUSANT
{
    
    class IMUSANT_interval_profile
    {
    public:
        void initialise(vector<float>::size_type number_of_elements);
        vector<float> intervals;
        vector<float> change_vector;
        vector<float> strength_vector;
        virtual void addProfileEntry(int index, IMUSANT_vector<S_IMUSANT_note> &notes) {};
        void calculateChangeVector();
        void calculateStrengthVector();
    };
    
    class IMUSANT_IOI_interval_profile : public IMUSANT_interval_profile
    {
    public:
        IMUSANT_IOI_interval_profile() {};
        void addProfileEntry(int index, IMUSANT_vector<S_IMUSANT_note> &notes);

    };
    
    class IMUSANT_pitch_interval_profile : public IMUSANT_interval_profile
    {
    public:
        IMUSANT_pitch_interval_profile() {};
        void addProfileEntry(int index, IMUSANT_vector<S_IMUSANT_note> &notes);
    };

    
    
    class IMUSANT_segmented_part_LBDM
    {
    public:
        
        IMUSANT_segmented_part_LBDM(S_IMUSANT_part the_part)
        {
            fPart = the_part;
        }
        
        IMUSANT_interval_profile getLocalBoundaryStrengthProfile();
        
        
    private:
        
        S_IMUSANT_part fPart;
        
        const float weight_interonset_interval = 0.5;
        const float weight_pitch = 0.25;
        const float weight_rest = 0.25;
        
        IMUSANT_interval_profile pitch_interval_profile;
        IMUSANT_IOI_interval_profile ioi_interval_profile;
        IMUSANT_interval_profile rest_interval_profile;
        
        // IOI's calculated using Duration.asAbsoluteNumeric() on each Note.
        // Pitch is calculated using a numeric representation of Pitch yet to be implemented.
        // Rests are calculated using the getType propererty of IMUSANT_note.
        void buildIntervalProfiles();
              
        void calculateChange();
        void calculateStrength();
        void calculateLocalBoundaries();
    };
}

#endif /* defined(__imusant__IMUSANT_segmented_part_LBDM__) */
