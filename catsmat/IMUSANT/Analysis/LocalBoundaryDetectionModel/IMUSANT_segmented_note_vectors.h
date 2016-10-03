//
//  IMUSANT_segmented_note_vectors.h
//  catsmat
//
//  Created by Derrick Hill on 17/09/2016.
//
//

#ifndef __catsmat__IMUSANT_segmented_note_vectors__
#define __catsmat__IMUSANT_segmented_note_vectors__

#include <stdio.h>
#include <vector>

#include "IMUSANT_consolidated_interval_profile_LBDM_visitor.h"
#include "IMUSANT_consolidated_interval_profile_LBDM.h"

using namespace std;

namespace IMUSANT
{
    typedef vector<S_IMUSANT_note> IMUSANT_note_vector;
    
    class IMUSANT_segmented_note_vectors : public IMUSANT_consolidated_interval_profile_LBDM_visitor
    {
    public:
        
        IMUSANT_segmented_note_vectors() {}
        virtual ~IMUSANT_segmented_note_vectors() {}
        
        virtual void visit(IMUSANT_consolidated_interval_profile_LBDM *target);
        
        vector<IMUSANT_note_vector> segments;
        
    private:
        
        int fCurrentSegmentIndex = -1;
    };
}


#endif /* defined(__catsmat__IMUSANT_segmented_note_vectors__) */