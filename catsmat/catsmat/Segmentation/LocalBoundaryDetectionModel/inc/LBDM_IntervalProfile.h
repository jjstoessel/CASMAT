//
//  IMUSANT_interval_profile_LBDM.h
//  imusant
//
//  Created by Derrick Hill on 14/04/2016.
//
//

#ifndef __LBDM_IntervalProfile__
#define __LBDM_IntervalProfile__

#include <stdio.h>
#include <vector>
#include "IMUSANT_visitor.h"

using namespace std;
using namespace IMUSANT;

namespace CATSMAT
{
    class LBDM_IntervalProfile
    {
    public:
        void initialise(vector<float>::size_type number_of_elements);
        vector<double> profile_vector;
        vector<double> change_vector;
        vector<double> strength_vector;
        virtual void addProfileEntry(int index, IMUSANT_vector<S_IMUSANT_note> &notes) {};
        void calculateChangeVector();
        void calculateStrengthVector();
        
        friend ostream& operator<< (ostream& os, const LBDM_IntervalProfile& profile);
        
    private:
        ostream& printVectors(ostream& os) const;
        
        double calculateDegreeOfChange(double value1, double value2);
        double calculateBoundaryStrength(double interval_value, double preceding_change_value, double succeeding_change_value);
        
    };
    
    class LBDM_IOI_IntervalProfile : public LBDM_IntervalProfile
    {
    public:
        LBDM_IOI_IntervalProfile() {};
        void addProfileEntry(int index, IMUSANT_vector<S_IMUSANT_note> &notes);
    };
    
    class LBDM_PitchIntervalProfile : public LBDM_IntervalProfile
    {
    public:
        LBDM_PitchIntervalProfile() {};
        void addProfileEntry(int index, IMUSANT_vector<S_IMUSANT_note> &notes);
    };

    class LBDM_RestIntervalProfile : public LBDM_IntervalProfile
    {
    public:
        LBDM_RestIntervalProfile() {};
        void addProfileEntry(int index, IMUSANT_vector<S_IMUSANT_note> &notes);
    };
}


#endif /* defined(__LBDM_IntervalProfile__) */
