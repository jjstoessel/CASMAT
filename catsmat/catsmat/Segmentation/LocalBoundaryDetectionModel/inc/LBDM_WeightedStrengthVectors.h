//
//  IMUSANT_weighted_strength_vectors.h
//  catsmat
//
//  Created by Derrick Hill on 10/09/2016.
//
//

#ifndef __catsmat__IMUSANT_weighted_strength_vectors__
#define __catsmat__IMUSANT_weighted_strength_vectors__

#include <stdio.h>


#include "IMUSANT_consolidated_interval_profile_LBDM_visitor.h"
#include "LBDM_ConsolidatedIntervalProfile.h"

using namespace std;

namespace CATSMAT
{
    typedef vector<double> IMUSANT_strength_vector;
    
    class LBDM_WeightedStrengthVectors : public IMUSANT_consolidated_interval_profile_LBDM_visitor
    {
    public:
        
        LBDM_WeightedStrengthVectors() {}
        virtual ~LBDM_WeightedStrengthVectors() {}
        
        virtual void visit(LBDM_ConsolidatedIntervalProfile *target);
        
        vector<IMUSANT_strength_vector> segments;
        
    private:
        
        
        int fCurrentSegmentIndex = -1;
    };
}

#endif /* defined(__catsmat__IMUSANT_weighted_strength_vectors__) */
