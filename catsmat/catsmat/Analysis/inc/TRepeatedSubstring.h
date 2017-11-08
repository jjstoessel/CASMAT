//
//  TRepeatedSubstring.h
//  imusant
//
//  Created by Jason Stoessel on 20/05/2016.
//  Adapted from non-template interval implementation by Derrick Hill
//

#ifndef __TRepeatedSubstring__
#define __TRepeatedSubstring__

#include <stdio.h>
#include <iostream>
#include <vector>

#include "IMUSANT_interval.h"
#include "IMUSANT_contour_symbol.h"
#include "IMUSANT_generalised_interval.h"
#include "CATSMAT_TrigramSequences.h"

using namespace std;
using namespace CATSMAT;

namespace CATSMAT
{
    
    //
    // -- Sequence of Type T --
    // defaults to type print fnction
    //
    // -- Occurrences --
    // --- (movement, voice, measure, note index) ---
    // (1,2,11,2)(1,3,18,2)(1,1,4,2)(2,1,89,1)(2,2,94,1)(2,3,61,1)(2,1,51,1)(2,2,56,1)
    //
    // -- Sequence Length: 4 --
    // -- Number of Occurences: 8 -- 
    //
    
    template <typename T>
    class TRepeatedSubstring
    {
    public:
        
        typedef vector<TRepeatedSubstring<T> > SUBSTR_VECTOR;
        
        TRepeatedSubstring() : sequence(), occurrences() {}
        virtual ~TRepeatedSubstring() {}
    
        //
        // Interval Sequence
        //
        vector<T> sequence;
        unsigned long get_sequence_length();
        
        //
        //  Occurrences
        //
        typedef struct {
            long movement;
            long voice;
            long measure;
            long note_index;
        } occurrence;
        
        vector<occurrence> occurrences;
        void add_occurrence(occurrence the_occurrence);
        void add_occurrence(long movement, long voice, long measure, long note_index);
        //IMUSANT_t_repeated_substring& operator=(const IMUSANT_t_repeated_substring &rhs) const;
        
        typename vector<occurrence>::size_type num_occurrences() const;
        
        static string output_operator_help();

        friend ostream& operator<<(ostream& os, const TRepeatedSubstring<T>& substring)
        {
            //os << substring.sequence;
            os << "[";
            for (typename vector<T>::const_iterator ii = substring.sequence.begin(); ii != substring.sequence.end(); ++ii)
            {
                os << " " << *ii;
            }
            os << " ] ";

            for (int index = 0; index < substring.occurrences.size(); index++)
            {
                typename TRepeatedSubstring<T>::occurrence occ;
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
    };
    
    //
    // Interval Sequence
    //
    template <typename T>
    unsigned long
    TRepeatedSubstring<T>::
    get_sequence_length()
    {
        return sequence->size();
    }
    
    //
    //  Occurrences
    //
    template <typename T>
    void
    TRepeatedSubstring<T>::
    add_occurrence(occurrence the_occurrence)
    {
        occurrences.push_back(the_occurrence);
    }
    
    template <typename T>
    void
    TRepeatedSubstring<T>::
    add_occurrence(long movement, long voice, long measure, long note_index)
    {
        occurrence occ;
        occ.movement = movement;
        occ.voice = voice;
        occ.measure = measure;
        occ.note_index = note_index;
        
        add_occurrence(occ);
    }
    
//    template <typename T>
//    const TRepeatedSubstring<T>&
//    TRepeatedSubstring<T>::operator=(const IMUSANT_t_repeated_substring<T> &rhs)
//    {
//        if (this == &rhs)
//            return *this;
//        sequence = rhs.sequence;
//        occurrences = rhs.occurrences;
//        
//        return *this;
//    }

    
    template <typename T>
    typename vector<typename TRepeatedSubstring<T>::occurrence>::size_type
    TRepeatedSubstring<T>::
    num_occurrences() const
    {
        return occurrences.size();
    }
    
    template <typename T>
    string
    TRepeatedSubstring<T>::
    output_operator_help()
    {
        string ret_val =
        "Override base template clase for custom operator help.";
        
        return ret_val;
    }

    //explicit instantiations
    
    class RepeatedIntervalSubstring : public TRepeatedSubstring<IMUSANT_interval>
    {
    public:
        static string  output_operator_help()
        {
            string ret_val =
            "The output shows the discovered pattern in the following format \n" \
            "interval up/down (measure, index, part) \n" \
            "Followed by a list of occurrences in the format \n" \
            "(movement, voice, measure, index) \n";
            
            return ret_val;
        }
    };
    
    class RepeatedGeneralisedIntervalSubstring : public TRepeatedSubstring<IMUSANT_generalised_interval>
    {
    public:
        static string  output_operator_help()
        {
            string ret_val =
            "The output shows the discovered pattern in the following format \n" \
            "interval up/down (measure, index, part) \n" \
            "Followed by a list of occurrences in the format \n" \
            "(movement, voice, measure, index) \n";
            
            return ret_val;
        }
    };

    
    class RepeatedContourSubstring: public TRepeatedSubstring<IMUSANT_contour_symbol>
    {
    public:
        static string  output_operator_help()
        {
            string ret_val =
            "The output shows the discovered pattern in the following format \n" \
            "step, leap or large leap (+/- up/down) (measure, index, part) \n" \
            "Followed by a list of occurrences in the format \n" \
            "(movement, voice, measure, index) \n";
            
            return ret_val;
        }

    };
    
    class RepeatedPitchSubstring: public TRepeatedSubstring<IMUSANT_pitch>
    {
    public:
        static string  output_operator_help()
        {
            string ret_val =
            "The output shows the discovered pattern in the following format \n" \
            "pitch name,alteration, octave (measure, i&ndex, part) \n" \
            "Followed by a list of occurrences in the format \n" \
            "(movement, voice, measure, index) \n";
            
            return ret_val;
        }
        
    };
    
    class RepeatedTrigramTokenSubstring : public TRepeatedSubstring<unsigned int>
    {
    public:
        static string  output_operator_help()
        {
            string ret_val =
            "The output shows the discovered pattern in the following format \n" \
            "pitch name,alteration, octave (measure, index, part) \n" \
            "Followed by a list of occurrences in the format \n" \
            "(movement, voice, measure, index) \n";
            
            return ret_val;
        }
        friend ostream& operator<<(ostream& os, const std::array<signed int,3>& trigram);
        
        friend ostream& operator<<(ostream& os, const TRepeatedSubstring<unsigned int>& substring);
    };
    
}

#endif /* defined(__TRepeatedSubstring__) */

