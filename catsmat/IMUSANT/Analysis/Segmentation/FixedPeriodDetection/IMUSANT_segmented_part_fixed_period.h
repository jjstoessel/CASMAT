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
#include <unordered_set>

#include "IMUSANT_note.h"
#include "IMUSANT_score.h"
#include "IMUSANT_segment.h"
#include "IMUSANT_duration.h"

#include "IMUSANT_partlist_ordered_by_part_entry.h"


using namespace std;

namespace IMUSANT
{
    typedef unordered_set<IMUSANT_segment, SegmentHash, SegmentComparator> SetOfSegments;

    
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
        // This method returns you the segments, as a set or as a vector.
        // REVISIT The number of segments in each will be different because the vector contains duplicates..
        //
        SetOfSegments getSegmentsSet();
        vector<S_IMUSANT_segment> getSegments();
        
        S_IMUSANT_duration getPeriodDurationForThisScore();
        
        friend ostream& operator<< (ostream& os, const IMUSANT_segmented_part_fixed_period& segmented_part);
        friend IMUSANT_SMARTP<IMUSANT_segmented_part_fixed_period> new_IMUSANT_segmented_part_fixed_period();
       

    private:
        S_IMUSANT_score fScore;
        double fErrorThreshold = 0;
        
        S_IMUSANT_duration fPeriodDuration;
        vector<S_IMUSANT_segment> fSegments;
        SetOfSegments fSegmentsSet;   //********* HERE *********
        
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
        S_IMUSANT_duration calculateEntryOffsetBetweenParts(IMUSANT_PartEntry& first_part, IMUSANT_PartEntry& second_part);
        
        bool errorRateIsAcceptable(double error_threshold, int num_non_matching_notes, long number_of_notes);
        bool partsEnterTogether(IMUSANT_PartEntry& first_part, IMUSANT_PartEntry& second_part);
    };
    
    typedef IMUSANT_SMARTP<IMUSANT_segmented_part_fixed_period> S_IMUSANT_segmented_part_fixed_period;
    IMUSANT_SMARTP<IMUSANT_segmented_part_fixed_period> new_IMUSANT_segmented_part_fixed_period();

}


#endif /* defined(__catsmat__IMUSANT_segmented_part_fixed_period__) */
