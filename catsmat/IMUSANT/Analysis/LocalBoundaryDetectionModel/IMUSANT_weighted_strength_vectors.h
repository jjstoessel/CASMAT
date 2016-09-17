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
#include "IMUSANT_consolidated_interval_profile_LBDM.h"

using namespace std;

namespace IMUSANT
{
    typedef vector<double> IMUSANT_strength_vector;
    
    class IMUSANT_weighted_strength_vectors : public IMUSANT_consolidated_interval_profile_LBDM_visitor
    {
    public:
        
        IMUSANT_weighted_strength_vectors() {}
        virtual ~IMUSANT_weighted_strength_vectors() {}
        
        virtual void visit(IMUSANT_consolidated_interval_profile_LBDM *target);
        
        vector<IMUSANT_strength_vector> segments;
        
    private:
        
        
        int fCurrentSegmentIndex = -1;
    };
}

#endif /* defined(__catsmat__IMUSANT_weighted_strength_vectors__) */
