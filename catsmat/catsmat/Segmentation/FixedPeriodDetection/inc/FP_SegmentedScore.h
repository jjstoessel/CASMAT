
#ifndef __FP_SegmentedScore__
#define __FP_SegmentedScore__

#include <stdio.h>

#include "libIMUSANT.h"

#include "I_Segmented.h"
#include "Segment.h"
#include "SetOfSegment.h"
#include "PartlistOrderedByPartEntry.h"


using namespace std;

namespace CATSMAT
{
    class FP_SegmentedScore : public smartable, I_Segmented
    {
    public:
        
        string SEGMENTATION_ALGORITHM = "FP_SegmentedScore";
        
        static const int SUCCESS = 0;
        static const int ERR_NOT_ENOUGH_PARTS = 1;
        
        FP_SegmentedScore(SetOfSegment & segmentation_result) : I_Segmented(segmentation_result)
        {
        }
        
        virtual ~FP_SegmentedScore() {}
        
        int initialise(S_IMUSANT_score the_score, double error_threshold = 0.1);
        
        //
        // This method returns you the segments, as a set (no duplicates).
        //
        SetOfSegment & getSegmentsSet();
        
        S_IMUSANT_duration getPeriodDurationForThisScore();
        
        friend ostream& operator<< (ostream& os, const FP_SegmentedScore& segmented_part);
        friend IMUSANT_SMARTP<FP_SegmentedScore> new_SegmentedScoreFixedPeriod();
       
        //these are not class dependent member functions of broader utility
        static S_IMUSANT_duration calculateEntryOffsetBetweenParts(PartEntry& first_part, PartEntry& second_part); //i.e. Interonset interval
        
        static bool errorRateIsAcceptable(double error_threshold, int num_non_matching_notes, long number_of_notes);
        bool partsEnterTogether(PartEntry& first_part, PartEntry& second_part);
        
    private:
        S_IMUSANT_score fScore;
        double fErrorThreshold = 0;
        
        S_IMUSANT_duration fPeriodDuration;
        
        void comparePartsForPeriodicSegments(PartEntry& first_part, PartEntry& second_part, double error_threshold);
        void extractPeriodicSegmentsFromParts(PartEntry& first_part, PartEntry& second_part, double error_threshold);
        int populateNextSegment(S_Segment next_segment,
                                PartEntry& first_part,
                                PartEntry& second_part,
                                int& first_part_index,
                                int& second_part_index,
                                S_IMUSANT_duration period_duration);
        
        int populateNextSegments(S_Segment first_part_segment,
                                 S_Segment second_part_segment,
                                 PartEntry& first_part,
                                 PartEntry& second_part,
                                 int& first_part_index,
                                 int& second_part_index,
                                 S_IMUSANT_duration period_duration);
        
        
        S_Segment makeNewSegment(const S_IMUSANT_part part);
        void clearSegments();
        void addSegment(S_Segment segment);
        
        void setPeriodDurationForThisScore(S_IMUSANT_duration period_duration);
        void clearPeriodDurationForThisScore();
        S_IMUSANT_duration getPeriodDurationForPartComparison(PartEntry& first_part, PartEntry& second_part);
        S_IMUSANT_duration calculatePeriodDurationForThisScore(IMUSANT_PartEntry_Vector& parts_in_entry_order);
        
    };
    
    typedef IMUSANT_SMARTP<FP_SegmentedScore> S_SegmentedScoreFixedPeriod;
    IMUSANT_SMARTP<FP_SegmentedScore> new_SegmentedScoreFixedPeriod(SetOfSegment & segmentation_results);

}


#endif /* defined(__FP_SegmentedScore__) */
