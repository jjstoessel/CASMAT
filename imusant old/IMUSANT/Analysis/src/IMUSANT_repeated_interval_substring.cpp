//
//  IMUSANT_repeated_interval_substring.cpp
//  imusant
//
//  Created by Derrick Hill on 12/08/2015.
//
//

#include "IMUSANT_repeated_interval_substring.h"

namespace IMUSANT
{
    
    IMUSANT_repeated_interval_substring::
    IMUSANT_repeated_interval_substring()
    {
        interval_sequence = new_IMUSANT_interval_vector();
    }
    
    //
    // Interval Sequence
    //
    unsigned long
    IMUSANT_repeated_interval_substring::
    get_interval_sequence_length()
    {
        return interval_sequence->getIntervals().size();
    }
    
    //
    //  Occurrences
    //
    void
    IMUSANT_repeated_interval_substring::
    add_occurrence(occurrence the_occurrence)
    {
        occurrences.push_back(the_occurrence);
    }
    
    void
    IMUSANT_repeated_interval_substring::
    add_occurrence(long movement, long voice, long measure, long note_index)
    {
        IMUSANT_repeated_interval_substring::occurrence occ;
        occ.movement = movement;
        occ.voice = voice;
        occ.measure = measure;
        occ.note_index = note_index;
        
        add_occurrence(occ);
    }
    
    vector<IMUSANT_repeated_interval_substring::occurrence>::size_type
    IMUSANT_repeated_interval_substring::
    num_occurrences()
    {
        return occurrences.size();
    }
    
    ostream& operator<<( ostream& os, const IMUSANT_repeated_interval_substring& substring )
    {
        //os << "Sequence: ";
        os << substring.interval_sequence;
        // os << (substring.occurrences.size() ? "Occurrences: " : "None.");
        
        for (int index = 0; index < substring.occurrences.size(); index++)
        {
            IMUSANT_repeated_interval_substring::occurrence occ;
            occ = substring.occurrences[index];
            os << "("
                 << occ.movement << ", "
                 << occ.voice << ", "
                 << occ.measure << ", "
                 << occ.note_index << ") ";
        }
        
        os << endl << endl;
        
        return os;
    }
    
}


