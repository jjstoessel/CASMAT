
#ifndef __PartlistOrderedByPartEntry__
#define __PartlistOrderedByPartEntry__

#include <stdio.h>

#include "libIMUSANT.h"

#include "Segment.h"

using namespace std;

namespace CATSMAT
{
    //
    // PartEntry
    //
    struct PartEntry
    {
    public:
        
        PartEntry()
        {
            EntryDurationOffset = new_IMUSANT_duration();
        }
        
        PartEntry(S_IMUSANT_part part,
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
        int EntryVectorIndexPosition;   // The vector index of the first non-rest note in the part.
        S_IMUSANT_duration EntryDurationOffset;
        
        
        bool operator <(const PartEntry &rhs) const;  // Required for std::sort() which is used for sorting vectors of these things.
    };
    
    typedef vector<PartEntry> IMUSANT_PartEntry_Vector;
    
    
    //
    // IMUSANT_partlist_ordered_by_part_entry
    //
    class PartlistOrderedByPartEntry : public smartable
    {
    public:
        
        PartlistOrderedByPartEntry()
        {
        }
        
        virtual ~PartlistOrderedByPartEntry() {}
        
        IMUSANT_PartEntry_Vector getPartsInOrder(S_IMUSANT_score the_score);
        
        // REVISIT - implement this
        friend ostream& operator<< (ostream& os, const PartlistOrderedByPartEntry& ordered_partlist);
        
        friend IMUSANT_SMARTP<PartlistOrderedByPartEntry> new_PartlistOrderedByPartEntry();
        
        
    private:
        IMUSANT_PartEntry_Vector fOrderedPartList;
        
        PartEntry findEntryPoint(S_IMUSANT_part part);
    };
    
    typedef IMUSANT_SMARTP<PartlistOrderedByPartEntry> S_PartlistOrderedByPartEntry;
    IMUSANT_SMARTP<PartlistOrderedByPartEntry> new_PartlistOrderedByPartEntry();
    
}

#endif /* __PartlistOrderedByPartEntry__ */
