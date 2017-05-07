//
//  IMUSANT_T_RepeatedSubstring.h
//  imusant
//
//  Created by Jason Stoessel on 20/05/2016.
//  Adapted from non-template interval implementation by Derrick Hill
//

#ifndef __imusant__IMUSANT_t_repeated_substring__
#define __imusant__IMUSANT_t_repeated_substring__

#include <stdio.h>
#include <iostream>
#include <vector>

#include "IMUSANT_interval.h"
#include "IMUSANT_contour_symbol.h"
#include "IMUSANT_generalised_interval.h"
#include "CATSMAT_TrigramSequences.hpp"

using namespace std;
using namespace CATSMAT;

namespace IMUSANT
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
    class IMUSANT_T_RepeatedSubstring
    {
    public:
        
        typedef vector<IMUSANT_T_RepeatedSubstring<T> > SUBSTR_VECTOR;
        
        IMUSANT_T_RepeatedSubstring() : sequence(), occurrences() {}
        virtual ~IMUSANT_T_RepeatedSubstring() {}
    
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
//        friend ostream& operator<<(ostream& os, const IMUSANT_T_RepeatedSubstring<T>& substring)
//        {
//            //os << substring.sequence;
//            os << "[";
//            for (typename vector<T>::const_iterator ii = substring.sequence.begin(); ii != substring.sequence.end(); ++ii)
//            {
//                os << " " << *ii;
//            }
//            os << " ] ";
//
//            for (int index = 0; index < substring.occurrences.size(); index++)
//            {
//                typename IMUSANT_T_RepeatedSubstring<T>::occurrence occ;
//                occ = substring.occurrences[index];
//                os << "("
//                << "MVT: " << occ.movement << ", "
//                << "VCE: " << occ.voice << ", "
//                << "MES: " << occ.measure << ", "
//                << "IDX: " << occ.note_index << ") ";
//            }
//
//            os << endl << endl;
//
//            return os;
//        }
    };
    
    //
    // Interval Sequence
    //
    template <typename T>
    unsigned long
    IMUSANT_T_RepeatedSubstring<T>::
    get_sequence_length()
    {
        return sequence->size();
    }
    
    //
    //  Occurrences
    //
    template <typename T>
    void
    IMUSANT_T_RepeatedSubstring<T>::
    add_occurrence(occurrence the_occurrence)
    {
        occurrences.push_back(the_occurrence);
    }
    
    template <typename T>
    void
    IMUSANT_T_RepeatedSubstring<T>::
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
//    const IMUSANT_T_RepeatedSubstring<T>&
//    IMUSANT_T_RepeatedSubstring<T>::operator=(const IMUSANT_t_repeated_substring<T> &rhs)
//    {
//        if (this == &rhs)
//            return *this;
//        sequence = rhs.sequence;
//        occurrences = rhs.occurrences;
//        
//        return *this;
//    }

    
    template <typename T>
    typename vector<typename IMUSANT_T_RepeatedSubstring<T>::occurrence>::size_type
    IMUSANT_T_RepeatedSubstring<T>::
    num_occurrences() const
    {
        return occurrences.size();
    }
    
    template <typename T>
    string
    IMUSANT_T_RepeatedSubstring<T>::
    output_operator_help()
    {
        string ret_val =
        "Override base template clase for custom operator help.";
        
        return ret_val;
    }

    //explicit instantiations
    
    class IMUSANT_repeated_interval_substring : public IMUSANT_T_RepeatedSubstring<IMUSANT_interval>
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
    
    class IMUSANT_repeated_generalised_interval_substring : public IMUSANT_T_RepeatedSubstring<IMUSANT_generalised_interval>
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

    
    class IMUSANT_repeated_contour_substring: public IMUSANT_T_RepeatedSubstring<IMUSANT_contour_symbol>
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
    
    class IMUSANT_repeated_pitch_substring: public IMUSANT_T_RepeatedSubstring<IMUSANT_pitch>
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
    
    class IMUSANT_repeated_trigram_token_substring : public IMUSANT_T_RepeatedSubstring<CATSMAT_TrigramSequences::Token>
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
        
        friend ostream& operator<<(ostream& os, const IMUSANT_T_RepeatedSubstring<CATSMAT_TrigramSequences::Token>& substring)
        {
            for (auto ii : substring.sequence)
            {
                CATSMAT_TrigramSequences::Trigram t = CATSMAT_TrigramSequences::Token2Triple(ii);
                //unable to invoke operator<<(os&, Trigam&) at present
                os << " " << "[" << t[CATSMAT_TrigramSequences::dyad1] << ", " << t[CATSMAT_TrigramSequences::dyad2] << ", " << t[CATSMAT_TrigramSequences::lowMelInterval] << "]";
            }
            
            for (int index = 0; index < substring.occurrences.size(); index++)
            {
                IMUSANT_repeated_trigram_token_substring::occurrence occ;
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
    
}

#endif /* defined(__imusant__IIMUSANT_t_repeated_substring__) */

