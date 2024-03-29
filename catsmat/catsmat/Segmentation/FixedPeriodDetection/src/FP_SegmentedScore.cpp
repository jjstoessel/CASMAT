//
//  FP_SegmentedScore.cpp
//  catsmat
//
//  Created by Derrick Hill on 29/10/2016.
//
//

#include "FP_SegmentedScore.h"


// #define OUTPUT(s) cout << s;
#define OUTPUT(s)


namespace CATSMAT
{
    
    const int FP_SegmentedScore::SUCCESS;
    const int FP_SegmentedScore::ERR_NOT_ENOUGH_PARTS;
    
    int
    FP_SegmentedScore::
    initialise(S_IMUSANT_score the_score, double error_threshold)
    {
        fScore = the_score;
        fErrorThreshold = error_threshold;
        clearSegments();   // We have no segments to start with.
        clearPeriodDurationForThisScore();
        
        IMUSANT_vector<S_IMUSANT_part>& parts = the_score->partlist()->parts();
        
        if (parts.size() <= 1)
        {
            return ERR_NOT_ENOUGH_PARTS;
        }
        
        // Sort the parts in the order in which they enter...
        PartlistOrderedByPartEntry part_sorter;
        vector<PartEntry> parts_in_entry_order = part_sorter.getPartsInOrder(the_score);
        
        // This loop compares each part against each other part (e.g. for 4 parts -  1 against 2, 1 against 3, 1 against 4, 2 against 3, 2 against 4, 3 against 4.
        // REVISIT - This algorithm fails to extract the segments in the last part.
        // REVISIT - this algorithm adds a lot of duplicate segments (e.g. part 3 segments are added both for comparison with Part 1 and Part 2).
        for (int first_part_index = 0 ; first_part_index < parts_in_entry_order.size() - 1; first_part_index++)
        {
            for (int second_part_index = first_part_index + 1; second_part_index < parts_in_entry_order.size() ; second_part_index++)
            {
                comparePartsForPeriodicSegments(parts_in_entry_order[first_part_index], parts_in_entry_order[second_part_index], error_threshold);
            }
        }
        return SUCCESS;
    }
    
    void
    FP_SegmentedScore::
    comparePartsForPeriodicSegments(PartEntry& first_part, PartEntry& second_part, double error_threshold)
    {
        OUTPUT("+++++  Comparing Part " +
               first_part.Part->getPartName() +
               " to Part " +
               second_part.Part->getPartName() +
               " +++++\n" +
               "Error Threshold = " +
               std::to_string(error_threshold) +
               "\n") ;
 
        if (partsEnterTogether(first_part, second_part))
        {
            return;  // The parts start at the same time so we are assuming that they are not in periodic cannon.  Skip this pair.
        }
        else
        {
            // The two parts are not starting at the same time, so they could be in cannon - keep going.
            extractPeriodicSegmentsFromParts(first_part, second_part, error_threshold);
        }
    }
    
    void
    FP_SegmentedScore::
    extractPeriodicSegmentsFromParts(PartEntry& first_part, PartEntry& second_part, double error_threshold)
    {
        int first_part_index = first_part.EntryVectorIndexPosition;
        int second_part_index = second_part.EntryVectorIndexPosition;
        
        while(first_part_index < first_part.Part->notes().size()
              &&
              second_part_index < second_part.Part->notes().size())
        {
            OUTPUT("\n---  STARTING NEW SEGMENT ---\n");
            
            S_Segment first_part_segment = makeNewSegment(first_part.Part);
            S_Segment second_part_segment = makeNewSegment(second_part.Part);
            
            S_IMUSANT_duration period_duration = getPeriodDurationForPartComparison(first_part, second_part);
            
            int num_non_matching_notes = populateNextSegments(first_part_segment, second_part_segment, first_part, second_part, first_part_index, second_part_index, period_duration);
            
            if (errorRateIsAcceptable(error_threshold, num_non_matching_notes, first_part_segment->size()))
            {
                addSegment(first_part_segment);
                addSegment(second_part_segment);
                setPeriodDurationForThisScore(period_duration);
            }
            else
            {
                OUTPUT(" *** Too many differences.  Ignoring this segment.\n");
            }
        }
    }
        
    int
    FP_SegmentedScore::
    populateNextSegment(S_Segment next_segment,
                        PartEntry& first_part,
                        PartEntry& second_part,
                        int& first_part_index,
                        int& second_part_index,
                        S_IMUSANT_duration period_duration)
    {
        IMUSANT_vector<S_IMUSANT_note> part_one_notes = first_part.Part->notes();
        IMUSANT_vector<S_IMUSANT_note> part_two_notes = second_part.Part->notes();
        
        S_IMUSANT_note n1;
        S_IMUSANT_note n2;
        
        int num_non_matching_notes = 0;
        
        S_IMUSANT_duration segment_duration = new_IMUSANT_duration();
        
        while (*segment_duration < *period_duration
               &&
               first_part_index < part_one_notes.size()
               &&
               second_part_index < part_two_notes.size())
        {
            n1 = part_one_notes[first_part_index++];
            n2 = part_two_notes[second_part_index++];
            
            next_segment->addNote(n2);
            
            OUTPUT("Comparing " + n1->pretty_print() + " to " + n2->pretty_print());
            
            if (! (*n1 == *n2))
            {
                num_non_matching_notes++;
                OUTPUT(" ---  DIFFERENT --- ");
            }
            
            *segment_duration += *n2->duration();
            OUTPUT(endl);
            
        }
        
        return num_non_matching_notes;
    }
    
    int
    FP_SegmentedScore::
    populateNextSegments(S_Segment first_part_segment,
                         S_Segment second_part_segment,
                         PartEntry& first_part,
                         PartEntry& second_part,
                         int& first_part_index,
                         int& second_part_index,
                         S_IMUSANT_duration period_duration)
    {
        IMUSANT_vector<S_IMUSANT_note> part_one_notes = first_part.Part->notes();
        IMUSANT_vector<S_IMUSANT_note> part_two_notes = second_part.Part->notes();
        
        S_IMUSANT_note n1;
        S_IMUSANT_note n2;
        
        int num_non_matching_notes = 0;
        
        S_IMUSANT_duration segment_duration = new_IMUSANT_duration();
        
        while (*segment_duration < *period_duration
               &&
               first_part_index < part_one_notes.size()
               &&
               second_part_index < part_two_notes.size())
        {
            n1 = part_one_notes[first_part_index++];
            n2 = part_two_notes[second_part_index++];
            
            first_part_segment->addNote(n1);
            second_part_segment->addNote(n2);
            
            OUTPUT("Comparing " + n1->pretty_print() + " to " + n2->pretty_print());
            
            if (! (*n1 == *n2))
            {
                num_non_matching_notes++;
                OUTPUT(" ---  DIFFERENT --- ");
            }
            
            *segment_duration += *n2->duration();
            OUTPUT(endl);
            
        }
        
        return num_non_matching_notes;
    }
    
    bool
    FP_SegmentedScore::
    partsEnterTogether(PartEntry& first_part, PartEntry& second_part)
    {
        S_IMUSANT_duration part_entry_difference = calculateEntryOffsetBetweenParts(first_part, second_part);
        
        S_IMUSANT_duration no_duration = new_IMUSANT_duration(IMUSANT_duration::unmeasured);
        return (*part_entry_difference == *no_duration);
    }
    
    void
    FP_SegmentedScore::
    addSegment(S_Segment segment)
    {
        fSegmentationResult.insert(*segment);
    }
    
    S_Segment
    FP_SegmentedScore::
    makeNewSegment(S_IMUSANT_part part)
    {
        S_SegmentContext context = new_SegmentContext(fScore, part, this->SEGMENTATION_ALGORITHM);
        S_Segment next_segment = new_Segment(context);
        return next_segment;
    };
    
    bool
    FP_SegmentedScore::
    errorRateIsAcceptable(double error_threshold, int num_non_matching_notes, long number_of_notes)
    {
        bool ret_val = false;
        double error_rate = 0;
    
        if (num_non_matching_notes == 0)
        {
            ret_val = true;
        }
        else {
            error_rate = num_non_matching_notes / (double) number_of_notes;
            ret_val = error_rate < error_threshold;
        }
      
        OUTPUT("Error Rate: = " + to_string(error_rate) + "\n");
        
        return ret_val;
    }
    
    void
    FP_SegmentedScore::
    setPeriodDurationForThisScore(S_IMUSANT_duration period_duration)
    {
        fPeriodDuration = period_duration;
    }
    
    void
    FP_SegmentedScore::
    clearPeriodDurationForThisScore()
    {
        fPeriodDuration = NULL;
    }
    
    S_IMUSANT_duration
    FP_SegmentedScore::
    getPeriodDurationForThisScore()
    {
        return fPeriodDuration;
    }
    
    S_IMUSANT_duration
    FP_SegmentedScore::
    getPeriodDurationForPartComparison(PartEntry& first_part, PartEntry& second_part)
    {
        if (! fPeriodDuration)
        {
            S_IMUSANT_duration candidate_period_duration = calculateEntryOffsetBetweenParts(first_part, second_part);
            return candidate_period_duration;
        }
        else
        {
            return fPeriodDuration;
        }
    }

    S_IMUSANT_duration
    FP_SegmentedScore::
    calculatePeriodDurationForThisScore(IMUSANT_PartEntry_Vector& parts_in_entry_order)
    {
        for (int index = 0; index < parts_in_entry_order.size() - 1; index++)
        {
            for (int jdex = 1; jdex < parts_in_entry_order.size(); jdex++)
            {
                if (! partsEnterTogether(parts_in_entry_order[index], parts_in_entry_order[jdex]))
                {
                    return calculateEntryOffsetBetweenParts(parts_in_entry_order[index], parts_in_entry_order[jdex]);
                }
            }
        }
        return new_IMUSANT_duration();
    }
    
    S_IMUSANT_duration
    FP_SegmentedScore::
    calculateEntryOffsetBetweenParts(PartEntry& first_part, PartEntry& second_part)
    {
        IMUSANT_duration part_one_duration_offset = *(first_part.EntryDurationOffset);
        IMUSANT_duration part_two_duration_offset = *(second_part.EntryDurationOffset);
        
        S_IMUSANT_duration period_duration = new_IMUSANT_duration();
        *period_duration = part_two_duration_offset - part_one_duration_offset;
        
        return period_duration;
    }
    
    void
    FP_SegmentedScore::
    clearSegments()
    {
        fSegmentationResult.clear();
    }
    
    SetOfSegment &
    FP_SegmentedScore::
    getSegmentsSet()
    {
        return fSegmentationResult;
    }
    
    
    S_FP_SegmentedScore new_SegmentedScoreFixedPeriod(SetOfSegment & segmentation_results)
    {
        FP_SegmentedScore* o = new FP_SegmentedScore(segmentation_results);
        assert (o!=0);
        return o;
    }
    
    
}
