//
//  LBDM_SegmentedNoteVectors.h
//  catsmat
//
//  Created by Derrick Hill on 17/09/2016.
//
//

#ifndef __LBDM_SegmentedNoteVectors__
#define __LBDM_SegmentedNoteVectors__

#include <stdio.h>
#include <vector>

#include "IMUSANT_note.h"
#include "LBDM_ConsolidatedIntervalProfileVisitor.h"
#include "LBDM_ConsolidatedIntervalProfile.h"

using namespace std;

namespace CATSMAT
{
    class LBDM_SegmentedNoteVectors : public LBDM_ConsolidatedIntervalProfileVisitor
    {
    public:
        
        LBDM_SegmentedNoteVectors() {}
        virtual ~LBDM_SegmentedNoteVectors() {}
        
        virtual void visit(LBDM_ConsolidatedIntervalProfile *target);
        
        vector<IMUSANT_note_vector> segments;
        
    private:
        
        int fCurrentSegmentIndex = -1;
    };
}


#endif /* defined(__LBDM_SegmentedNoteVectors__) */
