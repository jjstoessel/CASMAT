//
//  IMUSANT_segmented_profile_vectors.h
//  catsmat
//
//  Created by Derrick Hill on 10/09/2016.
//
//

#ifndef __catsmat__IMUSANT_segmented_profile_vectors__
#define __catsmat__IMUSANT_segmented_profile_vectors__

#include <stdio.h>
#include <vector>

#include "IMUSANT_consolidated_interval_profile_LBDM_visitor.h"
#include "IMUSANT_consolidated_interval_profile_LBDM.h"

using namespace std;

namespace IMUSANT
{
    class IMUSANT_segmented_profile_vectors : public IMUSANT_consolidated_interval_profile_LBDM_visitor
    {
    public:
        
        IMUSANT_segmented_profile_vectors() {}
        virtual ~IMUSANT_segmented_profile_vectors() {}

        virtual void visit(IMUSANT_consolidated_interval_profile_LBDM *target);
        
        vector<IMUSANT_consolidated_interval_profile_vector_LBDM> segments;
        
    private:
        
        
        int fCurrentSegmentIndex = -1;
    };
}

#endif /* defined(__catsmat__IMUSANT_segmented_profile_vectors__) */
