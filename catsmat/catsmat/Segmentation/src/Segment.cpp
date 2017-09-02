//
//  Segment.cpp
//  catsmat
//
//  Created by Derrick Hill on 8/11/2016.
//
//

#include "Segment.h"

namespace CATSMAT
{
    
    S_Segment new_Segment(S_SegmentContext context)
    {
        Segment* o = new Segment(context);
        assert (o!=0);
        return o;
    }
    
    S_IMUSANT_score
    Segment::
    getScore() const
    {
        return fSegmentContext->getScore();
    }
    
    S_IMUSANT_part
    Segment::
    getPart() const
    {
        return fSegmentContext->getPart();
    }
    
    const vector<S_IMUSANT_note>
    Segment::
    notes() const
    {
        return fNotes;
    }
    
    void
    Segment::
    addNote(S_IMUSANT_note note)
    {
        fNotes.push_back(note);
    }
    
    S_IMUSANT_note
    Segment::
    getFirstNote() const
    {
//      if (! fNotes.empty())
            return fNotes.front();
    }
    
    S_IMUSANT_note
    Segment::
    getLastNote() const
    {
        //      if (! fNotes.empty())
        return fNotes.back();
    }
    
    long
    Segment::
    size() const
    {
        return fNotes.size();
    }
    
    void
    Segment::
    clear()
    {
        fNotes.clear();
    }
    
    const string
    Segment::
    getAlgorithm() const
    {
        return fSegmentContext->getSegmentationAlgorithm();
    }
    
    bool
    Segment::
    operator== (const Segment& rhs) const
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
    
    
    ostream& operator<< (ostream& os, const Segment& segment )
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
    Segment::
    printPropertiesHeaderRow() const
    {
        std::stringstream buffer;
        char delimiter = ':';
        
        buffer << "Segment" << delimiter << "Num notes" << delimiter << "Num measures" << delimiter << "First duration" << delimiter << "First pitch" << delimiter << "Last duration" << delimiter << "Last pitch" << endl;
        
        return buffer.str();
    }
    
    string
    Segment::
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
