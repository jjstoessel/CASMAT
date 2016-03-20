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
        
    private:
        
        
    };
    
    class IMUSANT_segmented_part_LBDM
    {
    public:
        
        IMUSANT_segmented_part_LBDM(S_IMUSANT_part the_part)
        {
            _the_part = the_part;
        }
        
        IMUSANT_interval_profile getLocalBoundaryStrengthProfile();
        
        
    private:
        
        S_IMUSANT_part _the_part;
        
        const float weight_interonset_interval = 0.5;
        const float weight_pitch = 0.25;
        const float weight_rest = 0.25;
        
        // IOI's calculated using Duration on Note (numerator/denominator). So a semiquavor (1/16th note) is 0.0625.
        // Pitch is calculated using a numeric representation of Pitch yet to be implemented.
        // Rests are calculated using the getType propererty of IMUSANT_note.
        void buildIntervalProfiles();
        
        IMUSANT_interval_profile pitch_interval_profile;
        IMUSANT_interval_profile ioi_interval_profile;
        IMUSANT_interval_profile rest_interval_profile;
        
        void calculateChange();
        void calculateStrength();
        void calculateLocalBoundaries();
    };
}

#endif /* defined(__imusant__IMUSANT_segmented_part_LBDM__) */
