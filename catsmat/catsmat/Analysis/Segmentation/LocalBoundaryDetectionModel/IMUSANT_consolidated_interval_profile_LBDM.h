//
//  IMUSANT_consolidated_profiles_LBDM.h
//  imusant
//
//  Created by Derrick Hill on 10/07/2016.
//
//

#ifndef __imusant__IMUSANT_consolidated_profiles_LBDM__
#define __imusant__IMUSANT_consolidated_profiles_LBDM__

#include <stdio.h>

#include "IMUSANT_consolidated_interval_profile_LBDM_visitor.h"
#include "libIMUSANT.h"

using namespace std;
using namespace IMUSANT;

namespace CATSMAT
{
    // Where:
    // StartNote = The first note in the interval from which change was calculated.
    // EndNote = The second note in the interval.
    // Pitch = The value of the strength vector for the Pitch Interval Profile
    // IOI = The value of the strength vector for the IOI Interval Profile
    // Rest = The value of the strength vector for the Rest Interval Profile
    // Weighted Avg = The overall local boundary strength profile for the interval.
    // Is Boundary = Is this interval on a segment boundary.
    
    class IMUSANT_consolidated_interval_profile_LBDM
    {
    public:
        
        IMUSANT_consolidated_interval_profile_LBDM() {};
        
        IMUSANT_consolidated_interval_profile_LBDM(S_IMUSANT_note start_note,
                                                   S_IMUSANT_note end_note,
                                                   double pitch,
                                                   double ioi,
                                                   double rest,
                                                   double weighted_avg_strength)
        {
            fStartNote = start_note;
            fEndNote = end_note;
            fPitch = pitch;
            fIOI = ioi;
            fRest = rest;
            fWeightedAvgStrength = weighted_avg_strength;
        }
        
        void setStartNote(S_IMUSANT_note the_note)
        {
            fStartNote = the_note;
        }
        
        S_IMUSANT_note getStartNote()
        {
            return fStartNote;
        }
        
        
        void setEndNote(S_IMUSANT_note the_note)
        {
            fEndNote = the_note;
        }
        
        S_IMUSANT_note getEndNote()
        {
            return fEndNote;
        }
        
        
        void setPitch(double the_pitch)
        {
            fPitch = the_pitch;
        }
        
        double getPitch()
        {
            return fPitch;
        }
        
        void setIOI(double the_IOI)
        {
            fIOI = the_IOI;
        }
        
        double getIOI()
        {
            return fIOI;
        }
        
        void setRest(double the_rest)
        {
            fRest = the_rest;
        }
        
        double getRest()
        {
            return fRest;
        }
        
        void setWeightedAverage(double the_weighted_avg)
        {
            fWeightedAvgStrength = the_weighted_avg;
        }
        
        double getWeightedAverage()
        {
            return fWeightedAvgStrength;
        }
        
        void isBoundary(bool is_boundary)
        {
            fIsBoundary = is_boundary;
        }
        
        bool isBoundary()
        {
            return fIsBoundary;
        }
        
        void accept(IMUSANT_consolidated_interval_profile_LBDM_visitor& visitor)
        {
            visitor.visit(this);
        }
        
        
    private:
        S_IMUSANT_note fStartNote;
        S_IMUSANT_note fEndNote;
        double fPitch = 0;
        double fIOI = 0;
        double fRest = 0;
        double fWeightedAvgStrength = 0;
        bool fIsBoundary = false;
    };
    
    class IMUSANT_consolidated_interval_profile_vector_LBDM : public vector <IMUSANT_consolidated_interval_profile_LBDM>
    {

    };
}

#endif /* defined(__imusant__IMUSANT_consolidated_profiles_LBDM__) */