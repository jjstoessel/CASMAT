//
//  IMUSANT_segment.h
//  catsmat
//
//  Created by Derrick Hill on 8/11/2016.
//
//

#ifndef IMUSANT_segment_h
#define IMUSANT_segment_h

#include <stdio.h>

#include "libIMUSANT.h"
#include "I_Segment.h"

using namespace std;
using namespace IMUSANT;

namespace CATSMAT
{
    class IMUSANT_segment : public IMUSANT::smartable, I_Segment
    {
    public:
       
        friend IMUSANT_SMARTP<IMUSANT_segment> new_IMUSANT_segment(S_SegmentContext context);
        friend ostream& operator<< (ostream& os, const IMUSANT_segment& segment);
        
        IMUSANT_segment(S_SegmentContext context)
        : I_Segment(context)
        {
        }
        
        virtual ~IMUSANT_segment() {}
        
        S_SegmentContext getContext() const;
        
        S_IMUSANT_score getScore() const;
        S_IMUSANT_part getPart() const;
        const string getAlgorithm() const;

        const vector<S_IMUSANT_note> notes() const;
        void addNote(S_IMUSANT_note note);
        
        S_IMUSANT_note getFirstNote() const;
        S_IMUSANT_note getLastNote() const;
        
        long size() const;
        void clear();
        
        long getConfidence() const { return fConfidence; };
        void setConfidence(long confidence_level) { fConfidence = confidence_level; };
        
        bool operator== (const IMUSANT_segment& rhs) const;
        
        string printPropertiesHeaderRow() const;
        string printProperties() const;
        
    private:
        vector<S_IMUSANT_note> fNotes;
        long fConfidence = 0;
    };

    typedef IMUSANT_SMARTP<IMUSANT_segment> S_IMUSANT_segment;
    IMUSANT_SMARTP<IMUSANT_segment> new_IMUSANT_segment(S_SegmentContext context);
    
    struct SegmentComparator
    {
    public:
        bool operator()(const IMUSANT_segment& seg1, const IMUSANT_segment& seg2) const
        {
            
            return seg1 == seg2;
        }
    };
    
    struct SegmentHash
    {
    public:
        size_t operator()(const IMUSANT_segment& segment) const
        {
            long first_note_index = 0;
            long first_note_measure = 0;
            long last_note_index = 0;
            long last_note_measure = 0;
            
            long segment_size = segment.size();
            if (segment_size > 0)
            {
                first_note_index = segment.getFirstNote()->getNoteIndex();
                first_note_measure = segment.getFirstNote()->getMeasureNum();
                last_note_index = segment.getLastNote()->getNoteIndex();
                last_note_measure = segment.getLastNote()->getMeasureNum();
            }
            
            string segment_identifier = segment.getScore()->getWorkTitle()
                                        + segment.getPart()->getPartName()
                                        + to_string(segment_size)
                                        + to_string(segment.getConfidence())
                                        + to_string(first_note_index)
                                        + to_string(first_note_measure)
                                        + to_string(last_note_index)
                                        + to_string(last_note_measure);
            
            return std::hash<std::string>()(segment_identifier);
        }
    };
}

#endif /* IMUSANT_segment_hpp */
