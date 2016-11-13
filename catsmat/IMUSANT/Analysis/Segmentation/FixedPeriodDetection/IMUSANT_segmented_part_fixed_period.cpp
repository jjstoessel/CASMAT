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

        // RULE 1 - One part enters at the beginning, the others have rests.
        int num_parts_sounding = 0;
        string first_sounding_part_id;
        vector<string> non_sounding_part_ids;
        
        num_parts_sounding = separateSoundingPartsFromNonSoundingParts(first_sounding_part_id, non_sounding_part_ids, parts);
        
        if (num_parts_sounding > 1)
        {
            return ERR_MORE_THAN_ONE_PART_AT_BEGINNING;
        }
        
        // RULE 2 - find the entry point of the second part to join in...
        string second_sounding_part_id;
        int second_sounding_note_index = calculateSecondEntryNoteIndex(second_sounding_part_id, non_sounding_part_ids, the_score);
        
        // RULE 3 - The notes up to the second_part_entry_point repeated from that point on.
        
        IMUSANT_vector<S_IMUSANT_note> part_one_notes = the_score->partlist()->getPart(first_sounding_part_id)->notes();
        IMUSANT_vector<S_IMUSANT_note> part_two_notes = the_score->partlist()->getPart(second_sounding_part_id)->notes();
        
        float period_duration = calculatePeriodDuration(part_two_notes, second_sounding_note_index);
        fPeriodDuration = period_duration;
        
        int first_sounding_note_index = 0;
        int num_non_matching_notes = 0;
        float segment_duration = 0;
        S_IMUSANT_segment next_segment = new_IMUSANT_segment(fScore, the_score->partlist()->getPart(second_sounding_part_id));
        fSegments.push_back(next_segment);
        
        for (int p1_note_index = first_sounding_note_index, p2_note_index = second_sounding_note_index; p2_note_index < part_two_notes.size(); p1_note_index++, p2_note_index++)
        {
            S_IMUSANT_note n1 = part_one_notes[p1_note_index];
            S_IMUSANT_note n2 = part_two_notes[p2_note_index];
            
            segment_duration += n1->duration()->asAbsoluteNumeric();
            
            OUTPUT("Comparing " + n1->pretty_print() + " to " + n2->pretty_print());
           
            if (! (*n1 == *n2))
            {
                num_non_matching_notes++;
                OUTPUT(" ---  DIFFERENT --- ");
            }
            
            next_segment->addNote(n2);
            
            if (segment_duration == period_duration)
            {
                next_segment = new_IMUSANT_segment(fScore, the_score->partlist()->getPart(second_sounding_part_id));
                fSegments.push_back(next_segment);
                segment_duration =0;
            }
            
            OUTPUT(endl);
        }
        
        if (num_non_matching_notes > 0)
        {
            if (num_non_matching_notes / part_one_notes.size() > fErrorThreshold )
            {
                return ERR_PARTS_DONT_MATCH;
            }
        }
        
        // fPeriodLength = period_length;
        
        return SUCCESS;
        
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
    
    float
    IMUSANT_segmented_part_fixed_period::
    calculatePeriodDuration(IMUSANT_vector<S_IMUSANT_note>& second_sounding_part_notes , float second_sounding_note_index)
    {
        float period_duration = 0; //  new_IMUSANT_duration();
       
        for (int note_index = 0 ; note_index < second_sounding_note_index; note_index++)
        {
            period_duration += second_sounding_part_notes[note_index]->duration()->asAbsoluteNumeric();
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
