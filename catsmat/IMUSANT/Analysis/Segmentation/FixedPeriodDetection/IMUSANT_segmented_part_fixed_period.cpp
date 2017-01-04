//
//  IMUSANT_segmented_part_fixed_period.cpp
//  catsmat
//
//  Created by Derrick Hill on 29/10/2016.
//
//

#include "IMUSANT_segmented_part_fixed_period.h"


#define OUTPUT(s) cout << s;
// #define OUTPUT(s)


namespace IMUSANT
{
    
    const int IMUSANT_segmented_part_fixed_period::SUCCESS;
    const int IMUSANT_segmented_part_fixed_period::ERR_NOT_ENOUGH_PARTS;
        
    int
    IMUSANT_segmented_part_fixed_period::
    initialise(S_IMUSANT_score the_score, double error_threshold)
    {
        fScore = the_score;
        fErrorThreshold = error_threshold;
        
        IMUSANT_vector<S_IMUSANT_part>& parts = the_score->partlist()->parts();
        
        if (parts.size() <= 1)
        {
            return ERR_NOT_ENOUGH_PARTS;
        }
        
        fSegments.clear();   // We have no segments to start with.
        
        // Sort the parts in the order in which they enter...
        IMUSANT_partlist_ordered_by_part_entry part_sorter;
        vector<IMUSANT_PartEntry> parts_in_entry_order = part_sorter.getPartsInOrder(the_score);
        
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
        
        // fPeriodLength = period_length;
        
        return SUCCESS;
        
    }
    
    void
    IMUSANT_segmented_part_fixed_period::
    comparePartsForPeriodicSegments(IMUSANT_PartEntry& first_part, IMUSANT_PartEntry& second_part, double error_threshold)
    {
        OUTPUT("+++++  Comparing Part " +
               first_part.Part->getPartName() +
               " to Part " +
               second_part.Part->getPartName() +
               " +++++\n" +
               "Error Threshold = " +
               std::to_string(error_threshold) +
               "\n") ;
        
        S_IMUSANT_duration period_duration = calculatePeriodDuration(first_part, second_part);
 
        if (partsEnterTogether(period_duration))
        {
            return;  // The parts start at the same time so we are assuming that they are not in periodic cannon.
        }
        else
        {
            // The two parts are not starting at the same time, so they could be in cannon - keep going.
            extractPeriodicSegmentsFromParts(first_part, second_part, error_threshold, period_duration);
        }
    }
    
    void
    IMUSANT_segmented_part_fixed_period::
    extractPeriodicSegmentsFromParts(IMUSANT_PartEntry& first_part, IMUSANT_PartEntry& second_part, double error_threshold, S_IMUSANT_duration period_duration)
    {
        int first_part_index = first_part.EntryVectorIndexPosition;
        int second_part_index = second_part.EntryVectorIndexPosition;
        
        while(first_part_index < first_part.Part->notes().size()
              &&
              second_part_index < second_part.Part->notes().size())
        {
            OUTPUT("\n---  STARTING NEW SEGMENT ---\n");
            
            S_IMUSANT_segment next_segment = makeNewSegment(second_part.Part);

            int num_non_matching_notes = populateNextSegment(next_segment, first_part, second_part, first_part_index, second_part_index, period_duration);
            
            if (errorRateIsAcceptable(error_threshold, num_non_matching_notes, next_segment->size()))
            {
                fSegments.push_back(next_segment);   // We need to set the period duration on the first successful one of these.
            }
            else
            {
                OUTPUT(" *** Too many differences.  Ignoring this segment.\n");
                next_segment->clear();
            }
        }
    }
        
    int
    IMUSANT_segmented_part_fixed_period::
    populateNextSegment(S_IMUSANT_segment next_segment, IMUSANT_PartEntry& first_part, IMUSANT_PartEntry& second_part, int& first_part_index, int& second_part_index, S_IMUSANT_duration period_duration)
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
    
    
    bool
    IMUSANT_segmented_part_fixed_period::
    partsEnterTogether(S_IMUSANT_duration period_duration)
    {
        S_IMUSANT_duration no_duration = new_IMUSANT_duration(IMUSANT_duration::unmeasured);
        return (*period_duration == *no_duration);
    }
    
    
    S_IMUSANT_segment
    IMUSANT_segmented_part_fixed_period::
    makeNewSegment(S_IMUSANT_part part)
    {
        S_IMUSANT_segment next_segment = new_IMUSANT_segment(fScore, part, this->SEGMENTATION_ALGORITHM);
        return next_segment;
    };
    
    bool
    IMUSANT_segmented_part_fixed_period::
    errorRateIsAcceptable(double error_threshold, int num_non_matching_notes, long number_of_notes)
    {
        if (num_non_matching_notes == 0)
            return true;
        
        double error_rate = num_non_matching_notes / (double) number_of_notes;
        return (error_rate < error_threshold);
    }

    S_IMUSANT_duration
    IMUSANT_segmented_part_fixed_period::
    calculatePeriodDuration(IMUSANT_PartEntry& first_part, IMUSANT_PartEntry& second_part)
    {
        IMUSANT_duration part_one_duration_offset = *(first_part.EntryDurationOffset);
        IMUSANT_duration part_two_duration_offset = *(second_part.EntryDurationOffset);
        
        S_IMUSANT_duration period_duration = new_IMUSANT_duration();
        *period_duration = part_two_duration_offset - part_one_duration_offset;
        
        return period_duration;
    }
    
    
    vector<S_IMUSANT_segment>
    IMUSANT_segmented_part_fixed_period::
    getSegments()
    {
        return fSegments;
    }
    
    
    S_IMUSANT_segmented_part_fixed_period new_IMUSANT_segmented_part_fixed_period()
    {
        IMUSANT_segmented_part_fixed_period* o = new IMUSANT_segmented_part_fixed_period();
        assert (o!=0);
        return o;
    }
    
    
}
