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

#include "libIMUSANT.h"

#include "I_Segmented.h"
#include "IMUSANT_segment.h"
#include "IMUSANT_set_of_segment.h"
#include "IMUSANT_partlist_ordered_by_part_entry.h"


using namespace std;

namespace CATSMAT
{
    class SegmentedScoreFixedPeriod : public smartable, I_Segmented
    {
    public:
        
        string SEGMENTATION_ALGORITHM = "IMUSANT_segmented_part_fixed_period";
        
        static const int SUCCESS = 0;
        static const int ERR_NOT_ENOUGH_PARTS = 1;
        
        SegmentedScoreFixedPeriod(IMUSANT_set_of_segment & segmentation_result) : I_Segmented(segmentation_result)
        {
        }
        
        virtual ~SegmentedScoreFixedPeriod() {}
        
        int initialise(S_IMUSANT_score the_score, double error_threshold = 0.1);
        
        //
        // This method returns you the segments, as a set (no duplicates).
        //
        IMUSANT_set_of_segment & getSegmentsSet();
        
        S_IMUSANT_duration getPeriodDurationForThisScore();
        
        friend ostream& operator<< (ostream& os, const SegmentedScoreFixedPeriod& segmented_part);
        friend IMUSANT_SMARTP<SegmentedScoreFixedPeriod> new_SegmentedScoreFixedPeriod();
       
        //these are not class dependent member functions of broader utility
        static S_IMUSANT_duration calculateEntryOffsetBetweenParts(IMUSANT_PartEntry& first_part, IMUSANT_PartEntry& second_part); //i.e. Interonset interval
        
        static bool errorRateIsAcceptable(double error_threshold, int num_non_matching_notes, long number_of_notes);
        bool partsEnterTogether(IMUSANT_PartEntry& first_part, IMUSANT_PartEntry& second_part);
        
    private:
        S_IMUSANT_score fScore;
        double fErrorThreshold = 0;
        
        S_IMUSANT_duration fPeriodDuration;
        
        void comparePartsForPeriodicSegments(IMUSANT_PartEntry& first_part, IMUSANT_PartEntry& second_part, double error_threshold);
        void extractPeriodicSegmentsFromParts(IMUSANT_PartEntry& first_part, IMUSANT_PartEntry& second_part, double error_threshold);
        int populateNextSegment(S_IMUSANT_segment next_segment,
                                IMUSANT_PartEntry& first_part,
                                IMUSANT_PartEntry& second_part,
                                int& first_part_index,
                                int& second_part_index,
                                S_IMUSANT_duration period_duration);
        
        int populateNextSegments(S_IMUSANT_segment first_part_segment,
                                 S_IMUSANT_segment second_part_segment,
                                 IMUSANT_PartEntry& first_part,
                                 IMUSANT_PartEntry& second_part,
                                 int& first_part_index,
                                 int& second_part_index,
                                 S_IMUSANT_duration period_duration);
        
        
        S_IMUSANT_segment makeNewSegment(const S_IMUSANT_part part);
        void clearSegments();
        void addSegment(S_IMUSANT_segment segment);
        
        void setPeriodDurationForThisScore(S_IMUSANT_duration period_duration);
        void clearPeriodDurationForThisScore();
        S_IMUSANT_duration getPeriodDurationForPartComparison(IMUSANT_PartEntry& first_part, IMUSANT_PartEntry& second_part);
        S_IMUSANT_duration calculatePeriodDurationForThisScore(IMUSANT_PartEntry_Vector& parts_in_entry_order);
        
    };
    
    typedef IMUSANT_SMARTP<SegmentedScoreFixedPeriod> S_SegmentedScoreFixedPeriod;
    IMUSANT_SMARTP<SegmentedScoreFixedPeriod> new_SegmentedScoreFixedPeriod(IMUSANT_set_of_segment & segmentation_results);

}


#endif /* defined(__catsmat__IMUSANT_segmented_part_fixed_period__) */
