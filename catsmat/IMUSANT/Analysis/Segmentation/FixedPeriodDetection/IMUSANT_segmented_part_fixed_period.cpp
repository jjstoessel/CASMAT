//
//  IMUSANT_segmented_part_fixed_period.cpp
//  catsmat
//
//  Created by Derrick Hill on 29/10/2016.
//
//

#include "IMUSANT_segmented_part_fixed_period.h"

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
        vector<string> non_sounding_parts;
        
        for (int part_index = 0; part_index < parts.size() ; part_index++ )
        {
            S_IMUSANT_note the_note = parts[part_index]->notes()[0];
            if (the_note->isRest())
            {
                non_sounding_parts.push_back(parts[part_index]->getID());
            }
            else
            {
                num_parts_sounding++;
                first_sounding_part_id = parts[part_index]->getID();
            }
        }
        
        if (num_parts_sounding > 1)
        {
            return ERR_MORE_THAN_ONE_PART_AT_BEGINNING;
        }
        
        
        // RULE 2 - find the entry point of the second part to join in...
        int period_length = (int) parts[0]->measures().size();       // We are going to count down to find the earliest of the entries...
        string second_sounding_part_id;
        
        for (int part_index = 0; part_index < non_sounding_parts.size(); part_index++)
        {
            IMUSANT_vector<S_IMUSANT_note> notes = the_score->partlist()->getPart(non_sounding_parts[part_index])->notes();
            
            bool found = false;
            for (int note_index = 0; note_index < notes.size() && !found; note_index++)
            {
                if (! notes[note_index]->isRest())
                {
                    if (note_index < period_length)
                    {
                        period_length = note_index;
                        second_sounding_part_id = non_sounding_parts[part_index];
                    }
                    found = true;
                }
            }
        }
        
        // RULE 3 - The notes up to the second_part_entry_point repeated from that point on.
        IMUSANT_vector<S_IMUSANT_note> part_one_notes = the_score->partlist()->getPart(first_sounding_part_id)->notes();
        IMUSANT_vector<S_IMUSANT_note> part_two_notes = the_score->partlist()->getPart(second_sounding_part_id)->notes();
        
        // REVISIT - The algorithm below is incorrect because it treats period_length as an index of notes, when in fact it is an index of measures.
        
        int num_non_matching_notes = 0;
        S_IMUSANT_segment next_segment;
        for (int note_index = period_length; note_index < part_two_notes.size(); note_index ++)
        {
            S_IMUSANT_note n1 = part_one_notes[note_index - period_length];
            S_IMUSANT_note n2 = part_two_notes[note_index];
            
            if (note_index % period_length == 0)
            {
                next_segment = new_IMUSANT_segment(fScore, the_score->partlist()->getPart(second_sounding_part_id));
                fSegments.push_back(next_segment);
            }
            
            cout << "Comparing " << n1->pretty_print() << " to " << n2->pretty_print();
            
            if (! (*n1 == *n2))
            {
                num_non_matching_notes++;
                cout << " ---  DIFFERENT --- " ;
            }
            
            next_segment->add_note(n2);
            
            cout << endl;
        }
        
        if (num_non_matching_notes > 0)
        {
            if (num_non_matching_notes / part_one_notes.size() > fErrorThreshold )
            {
                return ERR_PARTS_DONT_MATCH;
            }
        }
        
        fPeriodLength = period_length;
        
        return SUCCESS;
        
    }
    

    vector<S_IMUSANT_segment>
    IMUSANT_segmented_part_fixed_period::
    get_segments()
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
