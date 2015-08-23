//
//  IMUSANT_repeated_interval_substrings.h
//  imusant
//
//  Created by Derrick Hill on 12/08/2015.
//
//

#ifndef __imusant__IMUSANT_repeated_interval_substring__
#define __imusant__IMUSANT_repeated_interval_substring__

#include "IMUSANT_interval_vector.h"

#include <stdio.h>
#include <vector>

using namespace std;


namespace IMUSANT
{
    
    //
    // -- Interval Sequence --
    // maj2 \\  maj2 \\  maj2 /  maj2 /
    //
    // -- Occurrences --
    // --- (movement, voice, measure, note index) ---
    // (1,2,11,2)(1,3,18,2)(1,1,4,2)(2,1,89,1)(2,2,94,1)(2,3,61,1)(2,1,51,1)(2,2,56,1)
    //
    // -- Sequence Length: 4 --
    // -- Number of Occurences: 8 -- 
    //
    
    class IMUSANT_repeated_interval_substring
    {
    public:
        
        IMUSANT_repeated_interval_substring();
        virtual ~IMUSANT_repeated_interval_substring() {}
    
        //
        // Interval Sequence
        //
        S_IMUSANT_interval_vector interval_sequence;
        unsigned long get_interval_sequence_length();
        
        //
        //  Occurrences
        //
        struct occurrence {
            long movement;
            long voice;
            long measure;
            long note_index;
        };
        
        vector<occurrence> occurrences;
        void add_occurrence(occurrence the_occurrence);
        void add_occurrence(long movement, long voice, long measure, long note_index);

        vector<occurrence>::size_type num_occurrences();
        
        friend ostream& operator<<( ostream& os, const IMUSANT_repeated_interval_substring& substring);
    };
}


#endif /* defined(__imusant__IMUSANT_repeated_interval_substring__) */

