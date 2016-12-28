//
//  IMUSANT_partlist_ordered_by_part_entry.h
//  catsmat
//
//  Created by Derrick Hill on 28/12/16.
//
//

#ifndef IMUSANT_partlist_ordered_by_part_entry_h
#define IMUSANT_partlist_ordered_by_part_entry_h

#include <stdio.h>

#include "IMUSANT_note.h"
#include "IMUSANT_score.h"
#include "IMUSANT_segment.h"
#include "IMUSANT_duration.h"

using namespace std;

namespace IMUSANT
{
    //
    // IMUSANT_PartEntry
    //
    struct IMUSANT_PartEntry
    {
    public:
        
        IMUSANT_PartEntry()
        {
            EntryDurationOffset = new_IMUSANT_duration();
        }
        
        IMUSANT_PartEntry(S_IMUSANT_part part,
                          long entry_note_index,
                          long entry_measure_num,
                          S_IMUSANT_duration entry_duration_offset)
        {
            Part = part;
            EntryNoteIndex = entry_note_index;
            EntryMeasureNum = entry_measure_num;
            EntryDurationOffset = entry_duration_offset;
        }
        
        S_IMUSANT_part Part;
        long EntryNoteIndex;
        long EntryMeasureNum;
        S_IMUSANT_duration EntryDurationOffset;
        
        bool operator <(const IMUSANT_PartEntry &rhs) const;  // Required for std::sort() which is used for sorting vectors of these things.
    };
    
    typedef vector<IMUSANT_PartEntry> IMUSANT_PartEntry_Vector;
    
    
    //
    // IMUSANT_partlist_ordered_by_part_entry
    //
    class IMUSANT_partlist_ordered_by_part_entry : public smartable
    {
    public:
        
        IMUSANT_partlist_ordered_by_part_entry()
        {
        }
        
        virtual ~IMUSANT_partlist_ordered_by_part_entry() {}
        
        IMUSANT_PartEntry_Vector getPartsInOrder(S_IMUSANT_score the_score);
        
        // REVISIT - implement this
        friend ostream& operator<< (ostream& os, const IMUSANT_partlist_ordered_by_part_entry& ordered_partlist);
        
        friend IMUSANT_SMARTP<IMUSANT_partlist_ordered_by_part_entry> new_IMUSANT_partlist_ordered_by_part_entry();
        
        
    private:
        IMUSANT_PartEntry_Vector fOrderedPartList;
        
        IMUSANT_PartEntry findEntryPoint(S_IMUSANT_part part);
    };
    
    typedef IMUSANT_SMARTP<IMUSANT_partlist_ordered_by_part_entry> S_IMUSANT_partlist_ordered_by_part_entry;
    IMUSANT_SMARTP<IMUSANT_partlist_ordered_by_part_entry> new_IMUSANT_partlist_ordered_by_part_entry();
    
}

#endif /* IMUSANT_partlist_ordered_by_part_entry_h */
