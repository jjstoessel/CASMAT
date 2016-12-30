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
    
    S_IMUSANT_segment new_IMUSANT_segment(S_IMUSANT_score score, S_IMUSANT_part part, string &segmentation_algorithm)
    {
        IMUSANT_segment* o = new IMUSANT_segment(score, part, segmentation_algorithm);
        assert (o!=0);
        return o;
    }
    
    S_IMUSANT_score
    IMUSANT_segment::
    getScore()
    {
        return fScore;
    }
    
    S_IMUSANT_part
    IMUSANT_segment::
    getPart()
    {
        return fPart;
    }
    
    void
    IMUSANT_segment::
    setScore(S_IMUSANT_score score)
    {
        fScore = score;
    }
    
    void
    IMUSANT_segment::
    setPart(S_IMUSANT_part part)
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
    addNote(S_IMUSANT_note note)
    {
        fNotes.push_back(note);
    }
    
    long
    IMUSANT_segment::
    size()
    {
        return fNotes.size();
    }
    
    void
    IMUSANT_segment::
    clear()
    {
        fNotes.clear();
    }
    
    string &
    IMUSANT_segment::
    getAlgorithm()
    {
        return fSegmentationAlgorithm;
    }
    
}
