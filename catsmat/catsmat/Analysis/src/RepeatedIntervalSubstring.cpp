//
//  RepeatedIntervalSubstring.cpp
//  imusant
//
//  Created by Derrick Hill on 12/08/2015.
//
//

#include "RepeatedIntervalSubstring.h"

namespace CATSMAT
{
    
    RepeatedIntervalSubstring::
    RepeatedIntervalSubstring()
    {
        interval_sequence = new_IMUSANT_interval_vector();
    }
    
    //
    // Interval Sequence
    //
    unsigned long
    RepeatedIntervalSubstring::
    get_interval_sequence_length()
    {
        return interval_sequence->getIntervals().size();
    }
    
    //
    //  Occurrences
    //
    void
    RepeatedIntervalSubstring::
    add_occurrence(occurrence the_occurrence)
    {
        occurrences.push_back(the_occurrence);
    }
    
    void
    RepeatedIntervalSubstring::
    add_occurrence(long movement, long voice, long measure, long note_index)
    {
        RepeatedIntervalSubstring::occurrence occ;
        occ.movement = movement;
        occ.voice = voice;
        occ.measure = measure;
        occ.note_index = note_index;
        
        add_occurrence(occ);
    }
    
    vector<RepeatedIntervalSubstring::occurrence>::size_type
    RepeatedIntervalSubstring::
    num_occurrences()
    {
        return occurrences.size();
    }
    
    string
    RepeatedIntervalSubstring::
    output_operator_help()
    {
        string ret_val =
                "The output shows the discovered pattern in the following format \n" \
                "interval up/down (measure, index, part) \n" \
                "Followed by a list of occurrences in the format \n" \
                "(movement, voice, measure, index) \n";
        
        return ret_val;
    }
    
    ostream& operator<<( ostream& os, const RepeatedIntervalSubstring& substring )
    {       
        os << substring.interval_sequence;

        for (int index = 0; index < substring.occurrences.size(); index++)
        {
            RepeatedIntervalSubstring::occurrence occ;
            occ = substring.occurrences[index];
            os << "("
                 << "MVT: " << occ.movement << ", "
                 << "VCE: " << occ.voice << ", "
                 << "MES: " << occ.measure << ", "
                 << "IDX: " << occ.note_index << ") ";
        }
        
        os << endl << endl;
        
        return os;
    }
    
}


