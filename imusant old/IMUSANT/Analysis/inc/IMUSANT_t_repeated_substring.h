//
//  IMUSANT_t_repeated_substring.h
//  imusant
//
//  Created by Jason Stoessel on 20/05/2016.
//  Adapted from non-template interval implementation by Derrick Hill
//

#ifndef __imusant__IMUSANT_t_repeated_substring__
#define __imusant__IMUSANT_t_repeated_substring__

#include <stdio.h>
#include <vector>

using namespace std;


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
    class IMUSANT_t_repeated_substring
    {
    public:
        
        IMUSANT_t_repeated_substring();
        virtual ~IMUSANT_t_repeated_substring() {}
    
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
        
        //vector<occurrence>::size_type num_occurrences();
        typename vector<occurrence>::size_type num_occurrences() const;
        
        static string output_operator_help();
        friend ostream& operator<<(ostream& os, const IMUSANT_t_repeated_substring<T>& substring)
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
                typename IMUSANT_t_repeated_substring<T>::occurrence occ;
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
    
    template <typename T>
    IMUSANT_t_repeated_substring<T>::
    IMUSANT_t_repeated_substring()
    {
        sequence.resize(10);
    }
    //
    // Interval Sequence
    //
    template <typename T>
    unsigned long
    IMUSANT_t_repeated_substring<T>::
    get_sequence_length()
    {
        return sequence->size();
    }
    
    //
    //  Occurrences
    //
    template <typename T>
    void
    IMUSANT_t_repeated_substring<T>::
    add_occurrence(occurrence the_occurrence)
    {
        occurrences.push_back(the_occurrence);
    }
    
    template <typename T>
    void
    IMUSANT_t_repeated_substring<T>::
    add_occurrence(long movement, long voice, long measure, long note_index)
    {
        occurrence occ;
        occ.movement = movement;
        occ.voice = voice;
        occ.measure = measure;
        occ.note_index = note_index;
        
        add_occurrence(occ);
    }
    
    template <typename T>
    typename vector<typename IMUSANT_t_repeated_substring<T>::occurrence>::size_type
    IMUSANT_t_repeated_substring<T>::
    num_occurrences() const
    {
        return occurrences.size();
    }
    
    template <typename T>
    string
    IMUSANT_t_repeated_substring<T>::
    output_operator_help()
    {
        string ret_val =
        "The output shows the discovered pattern in the following format \n" \
        "interval up/down (measure, index, part) \n" \
        "Followed by a list of occurrences in the format \n" \
        "(movement, voice, measure, index) \n";
        
        return ret_val;
    }
    
//    template <typename T>
//    ostream&
//    operator<< ( ostream& os, const IMUSANT_t_repeated_substring<T>& substring )
//    {
//        os << substring.sequence;
//        
//        for (int index = 0; index < substring.occurrences.size(); index++)
//        {
//            typename IMUSANT_t_repeated_substring<T>::occurrence occ;
//            occ = substring.occurrences[index];
//            os << "("
//            << "MVT: " << occ.movement << ", "
//            << "VCE: " << occ.voice << ", "
//            << "MES: " << occ.measure << ", "
//            << "IDX: " << occ.note_index << ") ";
//        }
//        
//        os << endl << endl;
//        
//        return os;
//    }

    class IMUSANT_repeated_interval_substring : public IMUSANT_t_repeated_substring<IMUSANT_interval> {};
    class IMUSANT_repeated_contour_substring: public IMUSANT_t_repeated_substring<IMUSANT_contour_symbol> {};
    
}

#endif /* defined(__imusant__IMUSANT_t_repeated_substring__) */

