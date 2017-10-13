//
//  IMUSANT_t_repeated_substring.cpp
//  imusant
//
//  Created by Jason Stoessel on 20/05/2016.
//  Adapted from non-template interval implementation by Derrick Hill
//
//

#include "TRepeatedSubstring.h"

namespace CATSMAT
{
    ostream& operator<<(ostream& os, const TRepeatedSubstring<CATSMAT_TrigramSequences::Token>& substring)
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

}


