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
#include "IMUSANT_interval_profile_LBDM.h"

using namespace std;

namespace IMUSANT
{
    class IMUSANT_segmented_part_LBDM : public smartable
    {
    public:

        friend SMARTP<IMUSANT_segmented_part_LBDM> new_IMUSANT_segmented_part_LBDM(S_IMUSANT_part the_part);
        
        IMUSANT_segmented_part_LBDM(S_IMUSANT_part the_part)
        {
            fPart = the_part;
        }
        
        virtual ~IMUSANT_segmented_part_LBDM() {}
        
        vector<float>& getOverallLocalBoundaryStrengthProfile();
        
        // This output operator produces output that can be extracted as an array initialisation for
        // the purposes of test case expected output. The format is as follows:
        //
        // PITCH		IOI             REST			WEIGHTED AVG
        // {5184,		65536,			0.0000,			17032},             // 0
        // {0,			0,              0.0000,			0},                 // 1
        // {0,			0,              0.0000,			0},                 // 2
        // ...
        //
        // Where:
        // PITCH = The value of the strength vector for the Pitch Interval Profile
        // IOI = The value of the strength vector for the IOI Interval Profile
        // REST = The value of the strength vector for the Rest Interval Profile
        // WEIGHTED AVG = The overall local boundary strength profile.
        //
        friend ostream& operator<< (ostream& os, const IMUSANT_segmented_part_LBDM& segmented_part);
 
    private:
        
        S_IMUSANT_part fPart;
        vector<float> overall_local_boundary_strength_profile;
        
        const float fWeightInteronsetInterval = 0.5;
        const float fWeightPitch = 0.25;
        const float fWeightRest = 0.25;
        
        IMUSANT_pitch_interval_profile pitch_interval_profile;
        IMUSANT_IOI_interval_profile ioi_interval_profile;
        IMUSANT_rest_interval_profile rest_interval_profile;
        
        // IOI's calculated using Duration.asAbsoluteNumeric() on each Note.
        // Pitch is calculated using a numeric representation of Pitch yet to be implemented.
        // Rests are calculated using the getType propererty of IMUSANT_note.
        void buildIntervalProfiles();
        
        void calculateOverallLocalBoundaryStrengthVector();
    };
    
    typedef SMARTP<IMUSANT_segmented_part_LBDM> S_IMUSANT_segmented_part_LBDM;
    SMARTP<IMUSANT_segmented_part_LBDM> new_IMUSANT_segmented_part_LBDM();
}

#endif /* defined(__imusant__IMUSANT_segmented_part_LBDM__) */
