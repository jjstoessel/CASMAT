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
        }
        
        virtual ~IMUSANT_segment() {}
        
        S_IMUSANT_score get_score();
        S_IMUSANT_part get_part();
        
        void set_score(S_IMUSANT_score score);
        void set_part(S_IMUSANT_part);
        
        vector<S_IMUSANT_note> notes();
        void add_note(S_IMUSANT_note note); 
        
        long confidence() { return fConfidence; };
        
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
