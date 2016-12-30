//
//  IMUSANT_segmented_part_fixed_period.cpp
//  catsmat
//
//  Created by Derrick Hill on 29/10/2016.
//
//

#include "IMUSANT_segmented_part_fixed_period.h"


// #define OUTPUT(s) cout << s;
#define OUTPUT(s)


namespace IMUSANT
{
    
    const int IMUSANT_segmented_part_fixed_period::SUCCESS;
    const int IMUSANT_segmented_part_fixed_period::ERR_NOT_ENOUGH_PARTS;
    const int IMUSANT_segmented_part_fixed_period::ERR_MORE_THAN_ONE_PART_AT_BEGINNING;
    const int IMUSANT_segmented_part_fixed_period::ERR_PARTS_DONT_MATCH;
        
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
        
        // This loop compares each part against each other part (e.g. for 4 parts 1 against 2, 1 against 3, 1 against 4, 2 against 3, 2 against 4, 3 against 4.
        // REVISIT - This algorithm fails to extract the segments in the last part.
        // REVISIT - this algorithm adds a lot of duplicate segments (e.g. part 3 segments are added both for comparison with Part 1 and Part 2).
        for (int first_part_index = 0 ; first_part_index < parts_in_entry_order.size() - 1; first_part_index++)
        {
            for (int second_part_index = first_part_index + 1; second_part_index < parts_in_entry_order.size() ; second_part_index++)
            {
                OUTPUT("+++++  Comparing Part " +
                       parts_in_entry_order[first_part_index].Part->getPartName() +
                       " to Part " +
                       parts_in_entry_order[second_part_index].Part->getPartName() +
                       " +++++\n") ;
                
                S_IMUSANT_duration period_duration = calculatePeriodDuration(parts_in_entry_order, first_part_index, second_part_index);
                
                S_IMUSANT_duration no_duration = new_IMUSANT_duration(IMUSANT_duration::unmeasured);
                if (*period_duration != *no_duration)
                {
                    // The two parts are not starting at the same time, so they could be in cannon - keep going.
                    
                    IMUSANT_vector<S_IMUSANT_note> part_one_notes = parts_in_entry_order[first_part_index].Part->notes();
                    IMUSANT_vector<S_IMUSANT_note> part_two_notes = parts_in_entry_order[second_part_index].Part->notes();
                    
                    int n1_index = parts_in_entry_order[first_part_index].EntryVectorIndexPosition;
                    int n2_index = parts_in_entry_order[second_part_index].EntryVectorIndexPosition;
                    
                    S_IMUSANT_note n1;
                    S_IMUSANT_note n2;
                    
                    S_IMUSANT_segment next_segment = makeNewSegment(parts_in_entry_order[second_part_index].Part);
                    
                    int num_non_matching_notes = 0;
                    
                    S_IMUSANT_duration segment_duration = new_IMUSANT_duration();
                    
                    // fPeriodDuration = &period_duration; // REVISIT - does period duration make sense globally???
                    
                    while(n1_index < part_one_notes.size()
                          &&
                          n2_index < part_two_notes.size())
                    {
                        n1 = part_one_notes[n1_index++];
                        n2 = part_two_notes[n2_index++];
                        
                        next_segment->addNote(n2);
                        
                        OUTPUT("Comparing " + n1->pretty_print() + " to " + n2->pretty_print());
                        
                        if (! (*n1 == *n2))
                        {
                            num_non_matching_notes++;
                            OUTPUT(" ---  DIFFERENT --- ");
                        }
                        
                        *segment_duration += *n2->duration();
                        
                        if (*segment_duration >= *period_duration)
                        {
                            // We have reached the end of the segment as defined by the oeriod_duration.
                            segment_duration = new_IMUSANT_duration();
                            
                            if (errorRateIsAcceptable(error_threshold, num_non_matching_notes, next_segment->size()))
                            {
                                fSegments.push_back(next_segment);
                                next_segment = makeNewSegment(parts_in_entry_order[second_part_index].Part);
                            }
                            else
                            {
                                OUTPUT("\n Too many differences.  Ignoring this segment.");
                                next_segment->clear();
                            }
                            
                            OUTPUT("\n---  STARTING NEW SEGMENT ---");
                        }
                        
                        OUTPUT(endl);
                    }
                }  // if (*period_duration != *no_duration)
            }
        }
        
        
        // fPeriodLength = period_length;
        
        return SUCCESS;
        
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

    
    int
    IMUSANT_segmented_part_fixed_period::
    separateSoundingPartsFromNonSoundingParts(string &first_sounding_part_id, vector<string> &non_sounding_part_ids, IMUSANT_vector<S_IMUSANT_part>& parts)
    {
        int num_parts_sounding = 0;
        for (int part_index = 0; part_index < parts.size() ; part_index++ )
        {
            S_IMUSANT_note the_note = parts[part_index]->notes()[0];
            if (the_note->isRest())
            {
                non_sounding_part_ids.push_back(parts[part_index]->getID());
            }
            else
            {
                num_parts_sounding++;
                first_sounding_part_id = parts[part_index]->getID();
            }
        }
        
        return num_parts_sounding;
    }
    
    
    void separateSoundingPartsFromNonSoundingParts(IMUSANT_vector<S_IMUSANT_part> &all_parts,
                                                   int at_note_index,
                                                   vector<S_IMUSANT_part> &sounding_parts,
                                                   vector<S_IMUSANT_part> &non_sounding_parts)
    {
        for (int part_index = 0; part_index < all_parts.size() ; part_index++ )
        {
            S_IMUSANT_note the_note = all_parts[part_index]->notes()[at_note_index];
            if (the_note->isRest())
            {
                non_sounding_parts.push_back(all_parts[part_index]);
            }
            else
            {
                sounding_parts.push_back(all_parts[part_index]);
            }
        }
    }
    
    
    int
    IMUSANT_segmented_part_fixed_period::
    calculateSecondEntryNoteIndex(string &second_sounding_part_id, vector<string>& non_sounding_part_ids, S_IMUSANT_score score)
    {
        // REVISIT - this is a really dumb implementation - fix it...
        
        IMUSANT_vector<S_IMUSANT_part>& parts = score->partlist()->parts();
        S_IMUSANT_part second_sounding_part;
        int second_sounding_part_note_index = (int) parts[0]->measures().size();       // We are going to count down to find the earliest of the entries...
        
        for (int part_index = 0; part_index < non_sounding_part_ids.size(); part_index++)
        {
            IMUSANT_vector<S_IMUSANT_note> notes = score->partlist()->getPart(non_sounding_part_ids[part_index])->notes();
            
            bool found = false;
            for (int note_index = 0; note_index < notes.size() && !found; note_index++)
            {
                if (! notes[note_index]->isRest())
                {
                    if (note_index < second_sounding_part_note_index)
                    {
                        second_sounding_part_note_index = note_index;
                        second_sounding_part_id = non_sounding_part_ids[part_index];
                        second_sounding_part = score->partlist()->getPart(second_sounding_part_id);
                    }
                    found = true;
                }
            }
        }
         return second_sounding_part_note_index;
    }
    

    S_IMUSANT_duration
    IMUSANT_segmented_part_fixed_period::
    calculatePeriodDuration(IMUSANT_PartEntry_Vector& parts_in_entry_order, int first_part_index, int second_part_index)
    {
        IMUSANT_duration part_one_duration_offset = *(parts_in_entry_order[first_part_index].EntryDurationOffset);
        IMUSANT_duration part_two_duration_offset = *(parts_in_entry_order[second_part_index].EntryDurationOffset);
        
        S_IMUSANT_duration period_duration = new_IMUSANT_duration();
        *period_duration = part_two_duration_offset - part_one_duration_offset;
        
        return period_duration;
    
    }
    
    
    S_IMUSANT_duration
    IMUSANT_segmented_part_fixed_period::
    calculatePeriodDuration(IMUSANT_vector<S_IMUSANT_note>& second_sounding_part_notes , float second_sounding_note_index)
    {
        S_IMUSANT_duration period_duration = new_IMUSANT_duration();
        
        for (int note_index = 0 ; note_index < second_sounding_note_index; note_index++)
        {
            *period_duration += *(second_sounding_part_notes[note_index]->duration());
        }
        
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
