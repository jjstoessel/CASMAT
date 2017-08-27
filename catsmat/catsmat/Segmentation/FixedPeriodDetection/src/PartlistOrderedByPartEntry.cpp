//
//  IMUSANT_partlist_ordered_by_part_entry.cpp
//  catsmat
//
//  Created by Derrick Hill on 28/12/16.
//
//

#include "PartlistOrderedByPartEntry.h"
#include <algorithm>

using namespace std;


namespace CATSMAT
{
    bool
    PartEntry::
    operator <(const PartEntry &rhs) const
    {
        return *(this->EntryDurationOffset) < *(rhs.EntryDurationOffset);
    }
    
    vector<PartEntry>
    PartlistOrderedByPartEntry::
    getPartsInOrder(S_IMUSANT_score the_score)
    {
        vector<PartEntry> ordered_part_list;
        
        vector<S_IMUSANT_part> parts = the_score->partlist()->parts();
        
        for (int index = 0 ; index < parts.size(); index++)
        {
            PartEntry entry_point = findEntryPoint(parts[index]);
            ordered_part_list.push_back(entry_point);
        }
        
        sort(ordered_part_list.begin(), ordered_part_list.end());
        
        return ordered_part_list;
    }
    
    PartEntry
    PartlistOrderedByPartEntry::
    findEntryPoint(S_IMUSANT_part part)
    {
        vector<S_IMUSANT_note> notes = part->notes();
        S_IMUSANT_note next_note;
        
        PartEntry entry_point;
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
                entry_point.EntryVectorIndexPosition = index;
                break;
            }
        }
        return entry_point;
    }
    
    
    S_PartlistOrderedByPartEntry new_PartlistOrderedByPartEntry()
    {
        PartlistOrderedByPartEntry* o = new PartlistOrderedByPartEntry();
        assert (o!=0);
        return o;
    }
    
    
    
}
