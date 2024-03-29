//
//  IMUSANT_weighted_strength_vectors.h
//  catsmat
//
//  Created by Derrick Hill on 10/09/2016.
//
//

#ifndef __LBDM_WeightedStrengthVectors__
#define __LBDM_WeightedStrengthVectors__

#include <stdio.h>


#include "LBDM_ConsolidatedIntervalProfileVisitor.h"
#include "LBDM_ConsolidatedIntervalProfile.h"

using namespace std;

namespace CATSMAT
{
    typedef vector<double> IMUSANT_strength_vector;
    
    class LBDM_WeightedStrengthVectors : public LBDM_ConsolidatedIntervalProfileVisitor
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

#endif /* defined(__LBDM_WeightedStrengthVectors__) */
