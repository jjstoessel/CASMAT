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
#include "IMUSANT_duration.h"

#include "IMUSANT_partlist_ordered_by_part_entry.h"


using namespace std;

namespace IMUSANT
{
    class IMUSANT_segmented_part_fixed_period : public smartable
    {
    public:
        
        string SEGMENTATION_ALGORITHM = "IMUSANT_segmented_part_fixed_period";
        
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
        
        S_IMUSANT_duration getPeriodDuration() { return fPeriodDuration; };
        
        friend ostream& operator<< (ostream& os, const IMUSANT_segmented_part_fixed_period& segmented_part);
        friend IMUSANT_SMARTP<IMUSANT_segmented_part_fixed_period> new_IMUSANT_segmented_part_fixed_period();
       

    private:
        S_IMUSANT_score fScore;
        
        vector<S_IMUSANT_segment> fSegments;
        
        S_IMUSANT_duration fPeriodDuration;
        double fErrorThreshold = 0;
        
        vector<S_IMUSANT_part> sortPartsByEntryOrder(IMUSANT_vector<S_IMUSANT_part>& parts);

        
        int separateSoundingPartsFromNonSoundingParts(string &first_sounding_part_id,
                                                      vector<string> &non_sounding_part_ids,
                                                      IMUSANT_vector<S_IMUSANT_part>& parts);
        
        void separateSoundingPartsFromNonSoundingParts(IMUSANT_vector<S_IMUSANT_part> &all_parts,
                                                       int at_note_index,
                                                       vector<S_IMUSANT_part> &sounding_parts,
                                                       vector<S_IMUSANT_part> &non_sounding_parts);
        
        // This method returns the index position of the second entry within the notes vector of the second sounding part.
        int calculateSecondEntryNoteIndex(string &second_sounding_part_id, vector<string>& non_sounding_part_ids, S_IMUSANT_score score);
        
        S_IMUSANT_duration calculatePeriodDuration(IMUSANT_vector<S_IMUSANT_note>& second_sounding_part_notes, float second_sounding_note_index);
        
        S_IMUSANT_duration calculatePeriodDuration(IMUSANT_PartEntry_Vector parts_in_entry_order);
        
        S_IMUSANT_segment makeNewSegment(const S_IMUSANT_part part);
    
    };
    
    typedef IMUSANT_SMARTP<IMUSANT_segmented_part_fixed_period> S_IMUSANT_segmented_part_fixed_period;
    IMUSANT_SMARTP<IMUSANT_segmented_part_fixed_period> new_IMUSANT_segmented_part_fixed_period();

}


#endif /* defined(__catsmat__IMUSANT_segmented_part_fixed_period__) */
