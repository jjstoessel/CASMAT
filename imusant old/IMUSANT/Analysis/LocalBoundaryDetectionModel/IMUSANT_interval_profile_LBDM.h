//
//  IMUSANT_interval_profile_LBDM.h
//  imusant
//
//  Created by Derrick Hill on 14/04/2016.
//
//

#ifndef __imusant__IMUSANT_interval_profile_LBDM__
#define __imusant__IMUSANT_interval_profile_LBDM__

#include <stdio.h>
#include <vector>
#include "IMUSANT_visitor.h"

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
        
        friend ostream& operator<< (ostream& os, const IMUSANT_interval_profile& profile);
        
    private:
        ostream& printFloatVector(ostream& os, const vector<float>& the_vector) const;
        
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

    class IMUSANT_rest_interval_profile : public IMUSANT_interval_profile
    {
    public:
        IMUSANT_rest_interval_profile() {};
        void addProfileEntry(int index, IMUSANT_vector<S_IMUSANT_note> &notes);
    };
}


#endif /* defined(__imusant__IMUSANT_interval_profile_LBDM__) */
