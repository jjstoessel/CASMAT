//
//  IMUSANT_segment.cpp
//  catsmat
//
//  Created by Derrick Hill on 8/11/2016.
//
//

#include "IMUSANT_segment.h"

namespace IMUSANT
{
    
    S_IMUSANT_segment new_IMUSANT_segment(S_IMUSANT_score score, S_IMUSANT_part part)
    {
        IMUSANT_segment* o = new IMUSANT_segment(score, part);
        assert (o!=0);
        return o;
    }
    
    S_IMUSANT_score
    IMUSANT_segment::
    get_score()
    {
        return fScore;
    }
    
    S_IMUSANT_part
    IMUSANT_segment::
    get_part()
    {
        return fPart;
    }
    
    void
    IMUSANT_segment::
    set_score(S_IMUSANT_score score)
    {
        fScore = score;
    }
    
    void
    IMUSANT_segment::
    set_part(S_IMUSANT_part part)
    {
        fPart = part;
    }
    
    vector<S_IMUSANT_note>
    IMUSANT_segment::
    notes()
    {
        return fNotes;
    }
    
    void
    IMUSANT_segment::
    add_note(S_IMUSANT_note note)
    {
        fNotes.push_back(note);
    }
    
}
