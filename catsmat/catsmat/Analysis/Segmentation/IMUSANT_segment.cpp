//
//  IMUSANT_segment.cpp
//  catsmat
//
//  Created by Derrick Hill on 8/11/2016.
//
//

#include "IMUSANT_segment.h"

namespace CATSMAT
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
    
    
    ostream& operator<< (ostream& os, const IMUSANT_segment& segment )
    {
        os
//        << "Score: " << segment.getScore()->getMovementTitle() << endl
//        << "Part: " << segment.getPart()->getPartName() << endl
//        << "First note: " << "Measure: " << segment.getFirstNote()->getMeasureNum() << ", Note Index: " << segment.getFirstNote()->getNoteIndex() << endl
//        << "Last note: " << "Measure: " << segment.getLastNote()->getMeasureNum() << ", Note Index: " << segment.getLastNote()->getNoteIndex() << endl
//        << "Size: " << segment.size() << "\t"
//        << "Confidence: " << segment.getConfidence() << "\t"
//        << "Algorithm: " << segment.getAlgorithm() << endl;
        << segment.getScore()->getMovementTitle() << ":"
        << segment.getPart()->getPartName() << ":"
        << segment.getFirstNote()->getMeasureNum() << ":" << segment.getFirstNote()->getNoteIndex() << ":"
        << segment.getLastNote()->getMeasureNum() << ":" << segment.getLastNote()->getNoteIndex() << ":"
        << segment.size() << ":"
        << segment.getConfidence() << ":"
        << segment.getAlgorithm();
        
        return os;
    }
    
    string
    IMUSANT_segment::
    printPropertiesHeaderRow() const
    {
        std::stringstream buffer;
        char delimiter = ':';
        
        buffer << "Segment" << delimiter << "Num notes" << delimiter << "Num measures" << delimiter << "First duration" << delimiter << "First pitch" << delimiter << "Last duration" << delimiter << "Last pitch" << endl;
        
        return buffer.str();
    }
    
    string
    IMUSANT_segment::
    printProperties() const
    {
        std::stringstream buffer;
        char delimiter = ':';
        
        float first_duration = getFirstNote()->duration()->AsAbsoluteNumeric();
        int first_pitch = getFirstNote()->pitch()->getMidiKeyNumber();
        long first_measure = getFirstNote()->getMeasureNum();
        long first_note_index = getFirstNote()->getNoteIndex();
        long last_measure = getLastNote()->getMeasureNum();
        long last_note_index = getLastNote()->getNoteIndex();
        
        float last_duration = getLastNote()->duration()->AsAbsoluteNumeric();
        int last_pitch = getLastNote()->pitch()->getMidiKeyNumber();
        long number_of_measures = getLastNote()->getMeasureNum() - getFirstNote()->getMeasureNum();
        
       buffer   // Segment identifier...
                << getScore()->getMovementTitle() << "." << getPart()->getPartName() << "." << first_measure << "." << first_note_index << "." << last_measure << "." << last_note_index <<  delimiter
                // Data...
                << size() << delimiter
                << to_string(number_of_measures) << delimiter
                << to_string(first_duration) << delimiter
                << to_string(first_pitch) << delimiter
                << to_string(last_duration) << delimiter
                << to_string(last_pitch)
                << endl;
        
        return buffer.str();
    }
    
    
    
    
}
