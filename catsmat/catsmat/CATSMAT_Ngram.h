//
//  CATSMAT_Ngram.h
//  
//
//  Created by Jason Stoessel on 25/11/2016.
//
//
// This is a temporary file!!!

#ifndef ____CATSMAT_Ngram__
#define ____CATSMAT_Ngram__

#include <stdio.h>
#include <vector>
#include <array>
#include "CATSMAT_dyad_sequences.hpp"





using namespace std;

namespace CATSMAT
{
    class CATSMAT_NGram_sequences : public CATSMAT_dyad_sequences
    {
    public:
        typedef std::array<int,3>   word; //a word is the two vertical intervals and the step in the lower voice
        typedef std::vector<word>   sentence; // a sentence is a sequence of words for a voice pair
        enum wordmembers { dyad1, dyad2, lowMelInterval };
        
        friend ostream& operator<<(ostream& os, const CATSMAT_NGram_sequences& ngrams);
        
        void    Visit(const CATSMAT_cp_matrix& matrix);
        void    print(ostream& os) const;
    private:
        void    process(const list<S_CATSMAT_chord>& matrix); //overrides base class
        vector<sentence>    sentences;
    };
}


#endif /* defined(____CATSMAT_Ngram__) */
