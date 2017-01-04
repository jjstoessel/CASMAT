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
        
        void comparePartsForPeriodicSegments(IMUSANT_PartEntry& first_part, IMUSANT_PartEntry& second_part, double error_threshold);
        
        S_IMUSANT_duration calculatePeriodDuration(IMUSANT_PartEntry& first_part, IMUSANT_PartEntry& second_part);
        
        S_IMUSANT_segment makeNewSegment(const S_IMUSANT_part part);
        
        bool errorRateIsAcceptable(double error_threshold, int num_non_matching_notes, long number_of_notes);
    };
    
    typedef IMUSANT_SMARTP<IMUSANT_segmented_part_fixed_period> S_IMUSANT_segmented_part_fixed_period;
    IMUSANT_SMARTP<IMUSANT_segmented_part_fixed_period> new_IMUSANT_segmented_part_fixed_period();

}


#endif /* defined(__catsmat__IMUSANT_segmented_part_fixed_period__) */
