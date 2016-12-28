//
//  IMUSANT_partlist_ordered_by_part_entry.cpp
//  catsmat
//
//  Created by Derrick Hill on 28/12/16.
//
//

#include "IMUSANT_partlist_ordered_by_part_entry.h"
#include <algorithm>

using namespace std;


namespace IMUSANT
{
    bool
    IMUSANT_PartEntry::
    operator <(const IMUSANT_PartEntry &rhs) const
    {
        return *(this->EntryDurationOffset) < *(rhs.EntryDurationOffset);
    }
    
    vector<IMUSANT_PartEntry>
    IMUSANT_partlist_ordered_by_part_entry::
    getPartsInOrder(S_IMUSANT_score the_score)
    {
        vector<IMUSANT_PartEntry> ordered_part_list;
        
        vector<S_IMUSANT_part> parts = the_score->partlist()->parts();
        
        for (int index = 0 ; index < parts.size(); index++)
        {
            IMUSANT_PartEntry entry_point = findEntryPoint(parts[index]);
            ordered_part_list.push_back(entry_point);
        }
        
        sort(ordered_part_list.begin(), ordered_part_list.end());
        
        return ordered_part_list;
    }
    
    IMUSANT_PartEntry
    IMUSANT_partlist_ordered_by_part_entry::
    findEntryPoint(S_IMUSANT_part part)
    {
        vector<S_IMUSANT_note> notes = part->notes();
        S_IMUSANT_note next_note;
        
        IMUSANT_PartEntry entry_point;
        entry_point.Part = part;
        
        for (int index = 0; index < notes.size(); index++)
        {
            next_note = notes[index];
            if (next_note->isRest())
            {
                entry_point.EntryDurationOffset->operator+=(*(next_note->duration()));
            }
            else
            {
                entry_point.EntryMeasureNum = next_note->getMeasureNum();
                entry_point.EntryNoteIndex = next_note->getNoteIndex();
                break;
            }
        }
        return entry_point;
    }
    
    
    S_IMUSANT_partlist_ordered_by_part_entry new_IMUSANT_partlist_ordered_by_part_entry()
    {
        IMUSANT_partlist_ordered_by_part_entry* o = new IMUSANT_partlist_ordered_by_part_entry();
        assert (o!=0);
        return o;
    }
    
    
    
}
