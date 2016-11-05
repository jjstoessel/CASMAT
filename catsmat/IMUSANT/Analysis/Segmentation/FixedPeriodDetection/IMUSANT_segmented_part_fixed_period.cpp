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
    initialise(S_IMUSANT_score the_score)
    {
        fScore = the_score;
        
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
        int second_part_entry_point = (int) parts[0]->measures().size();       // We are going to count down to find the earliest of the entries...
        string second_sounding_part_id;
        
        for (int part_index = 0; part_index < non_sounding_parts.size(); part_index++)
        {
            IMUSANT_vector<S_IMUSANT_note> notes = the_score->partlist()->getPart(non_sounding_parts[part_index])->notes();
            
            bool found = false;
            for (int note_index = 0; note_index < notes.size() && !found; note_index++)
            {
                if (! notes[note_index]->isRest())
                {
                    if (note_index < second_part_entry_point)
                    {
                        second_part_entry_point = note_index;
                        second_sounding_part_id = non_sounding_parts[part_index];
                    }
                    found = true;
                }
            }
        }
        
        // RULE 3 - The notes up to the second_part_entry_point repeated from that point on.
        IMUSANT_vector<S_IMUSANT_note> part_one_notes = the_score->partlist()->getPart(first_sounding_part_id)->notes();
        IMUSANT_vector<S_IMUSANT_note> part_two_notes = the_score->partlist()->getPart(second_sounding_part_id)->notes();
        
        for (int note_index = 0; note_index < second_part_entry_point; note_index ++)
        {
            S_IMUSANT_note n1 = part_one_notes[note_index];
            S_IMUSANT_note n2 = part_two_notes[note_index + second_part_entry_point];
            
            if (! (*n1 == *n2))
            {
                return ERR_PARTS_DONT_MATCH;
            }
        }
        
        fPeriodLength = second_part_entry_point;
        
        return SUCCESS;
        
    }
    
    //
    // This method returns you segments in the form of note vectors.  Each element of the
    // returned vector is a segment.
    //
    vector<IMUSANT_note_vector> getSegmentsAsNoteVectors()
    {
        throw "Not Implemented Yet...";
    }
    
    S_IMUSANT_segmented_part_fixed_period new_IMUSANT_segmented_part_fixed_period()
    {
        IMUSANT_segmented_part_fixed_period* o = new IMUSANT_segmented_part_fixed_period();
        assert (o!=0);
        return o;
    }
    
    
}