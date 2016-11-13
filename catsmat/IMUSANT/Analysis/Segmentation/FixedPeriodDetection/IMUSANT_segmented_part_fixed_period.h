//
//  IMUSANT_segmented_part_fixed_period.h
//  catsmat
//
//  Created by Derrick Hill on 29/10/2016.
//
//

#ifndef __catsmat__IMUSANT_segmented_part_fixed_period__
#define __catsmat__IMUSANT_segmented_part_fixed_period__

#include <stdio.h>

#include "IMUSANT_note.h"
#include "IMUSANT_score.h"
#include "IMUSANT_segment.h"

using namespace std;

namespace IMUSANT
{
    class IMUSANT_segmented_part_fixed_period : public smartable
    {
    public:
        
        static const int SUCCESS = 0;
        static const int ERR_NOT_ENOUGH_PARTS = 1;
        static const int ERR_MORE_THAN_ONE_PART_AT_BEGINNING = 2;
        static const int ERR_PARTS_DONT_MATCH = 3;
        
        IMUSANT_segmented_part_fixed_period()
        {
        }
        
        virtual ~IMUSANT_segmented_part_fixed_period() {}
        
        int initialise(S_IMUSANT_score the_score, double error_threshold = 0.1);
        
        //
        // This method returns you the segments.
        //
        vector<S_IMUSANT_segment> getSegments();
        
        int getPeriodDuration() { return fPeriodDuration; };
        
        friend ostream& operator<< (ostream& os, const IMUSANT_segmented_part_fixed_period& segmented_part);
        friend IMUSANT_SMARTP<IMUSANT_segmented_part_fixed_period> new_IMUSANT_segmented_part_fixed_period();
       

    private:
        S_IMUSANT_score fScore;
        
        vector<S_IMUSANT_segment> fSegments;
        
        int fPeriodDuration = 0;
        double fErrorThreshold = 0;
        
        int separateSoundingPartsFromNonSoundingParts(string &first_sounding_part_id,
                                                            vector<string> &non_sounding_part_ids,
                                                            IMUSANT_vector<S_IMUSANT_part>& parts);
        
        // This method returns the index position of the second entry within the notes vector of the second sounding part.
        int calculateSecondEntryNoteIndex(string &second_sounding_part_id, vector<string>& non_sounding_part_ids, S_IMUSANT_score score);
        
        float calculatePeriodDuration(IMUSANT_vector<S_IMUSANT_note>& second_sounding_part_notes, float second_sounding_note_index);

        
    };
    
    typedef IMUSANT_SMARTP<IMUSANT_segmented_part_fixed_period> S_IMUSANT_segmented_part_fixed_period;
    IMUSANT_SMARTP<IMUSANT_segmented_part_fixed_period> new_IMUSANT_segmented_part_fixed_period();
}


#endif /* defined(__catsmat__IMUSANT_segmented_part_fixed_period__) */
