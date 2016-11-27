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

#include "IMUSANT_score.h"
#include "IMUSANT_note.h"

using namespace std;

namespace IMUSANT
{
    class IMUSANT_segment : public smartable
    {
    public:
       
        friend IMUSANT_SMARTP<IMUSANT_segment> new_IMUSANT_segment();
        
        IMUSANT_segment(S_IMUSANT_score score, S_IMUSANT_part part)
        {
            fScore = score;
            fPart = part;
        }
        
        virtual ~IMUSANT_segment() {}
        
        S_IMUSANT_score getScore();
        void setScore(S_IMUSANT_score score);
        
        S_IMUSANT_part getPart();
        void setPart(S_IMUSANT_part);
        
        vector<S_IMUSANT_note> notes();
        void addNote(S_IMUSANT_note note);
        
        long getConfidence() { return fConfidence; };
        void setConfidence(long confidence_level) { fConfidence = confidence_level; };
        
    private:
        S_IMUSANT_score fScore;
        S_IMUSANT_part fPart;
        vector<S_IMUSANT_note> fNotes;
        long fConfidence;
    };
    
    typedef IMUSANT_SMARTP<IMUSANT_segment> S_IMUSANT_segment;
    IMUSANT_SMARTP<IMUSANT_segment> new_IMUSANT_segment(S_IMUSANT_score score, S_IMUSANT_part part);
}

#endif /* IMUSANT_segment_hpp */
