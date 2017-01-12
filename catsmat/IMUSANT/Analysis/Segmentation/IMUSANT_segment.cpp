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
    getScore() const
    {
        return fScore;
    }
    
    S_IMUSANT_part
    IMUSANT_segment::
    getPart() const
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
    
    const vector<S_IMUSANT_note>
    IMUSANT_segment::
    notes() const
    {
        return fNotes;
    }
    
    void
    IMUSANT_segment::
    addNote(S_IMUSANT_note note)
    {
        fNotes.push_back(note);
    }
    
    S_IMUSANT_note
    IMUSANT_segment::
    getFirstNote() const
    {
//      if (! fNotes.empty())
            return fNotes.front();
    }
    
    S_IMUSANT_note
    IMUSANT_segment::
    getLastNote() const
    {
        //      if (! fNotes.empty())
        return fNotes.back();
    }
    
    long
    IMUSANT_segment::
    size() const
    {
        return fNotes.size();
    }
    
    void
    IMUSANT_segment::
    clear()
    {
        fNotes.clear();
    }
    
    const string &
    IMUSANT_segment::
    getAlgorithm() const
    {
        return fSegmentationAlgorithm;
    }
    
    bool
    IMUSANT_segment::
    operator== (const IMUSANT_segment& rhs) const
    {
        return
        (
         *(getScore()) == *(rhs.getScore())
         &&
         *(getPart()) == *(rhs.getPart())
         &&
         size() == rhs.size()
         &&
         getConfidence() == rhs.getConfidence()
         &&
         getAlgorithm() == rhs.getAlgorithm()
         &&
         getFirstNote()->getNoteIndex() == rhs.getFirstNote()->getNoteIndex()
         &&
         getFirstNote()->getMeasureNum() == rhs.getFirstNote()->getMeasureNum()
         &&
         getLastNote()->getNoteIndex() == rhs.getLastNote()->getNoteIndex()
         &&
         getLastNote()->getMeasureNum() == rhs.getLastNote()->getMeasureNum()
         );
    }
    
}
