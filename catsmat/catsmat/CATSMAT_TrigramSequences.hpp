/*!
    CATSMAT_Ngram
    =============
    \file       CATSMAT_Ngram.h
    \brief      Class to calculate N-grams for dyad sequences
    \details    The CATSMAT N-gram class is an adaption of the N-gram contrapuntal word method proposed by
                Schubert, Peter, and Julie Cumming. "Another Lesson from Lassus: Using Computers to Analyse Counterpoint." Early Music 43, no. 4 (November 1, 2015 2015): 577-86.
                It relies upon CATSMAT_CPmatrix and IMUSANT_generalised_interval
                Class takes CP_Matrix and convert to a series of trigrams for each voice pair. The number of trigrams for each pair will be equal to the number of columns in CP Matrix
    \author     Jason Stoessel
    \author
    \version
    \date       Created by Jason Stoessel on 25/11/2016
    \bug        1 Mar 2017 - representation does not currently consider tied dyads created by the split function in CP matrix. These can be eliminated later where dyad1 = dyad2 and lowMelInterval = 0
    \warning
    \copyright
 */


#ifndef ____CATSMAT_Ngram__
#define ____CATSMAT_Ngram__

#include <stdio.h>
#include <vector>
#include <array>
#include "CATSMAT_dyad_sequences_base.hpp"

using namespace std;

namespace CATSMAT
{
    using Trigram = std::array<signed int,3>;
    using Sentence = std::vector<Trigram>;
    
    class CATSMAT_TrigramSequences : public CATSMAT_dyad_sequences_base<Sentence>
    {
    public:
        typedef std::array<signed int,3>    Trigram; //a word is the two vertical intervals and the step in the lower voice
        typedef std::vector<Trigram>        Sentence; // a sentence is a sequence of words for a voice pair
        typedef unsigned int                Token;
        typedef std::vector<vector<Token> > TokenVectors;
        enum    TrigramMembers { dyad1, dyad2, lowMelInterval };
        
        friend  ostream& operator<<(ostream& os, const CATSMAT_TrigramSequences& sequences);
        
        CATSMAT_TrigramSequences() : CATSMAT_dyad_sequences_base<Sentence>() {};
        ~CATSMAT_TrigramSequences() {};
        
        void    Visit(const CATSMAT_cp_matrix& matrix);
        void    Print(ostream& os) const;
        
        TokenVectors   get_tokens() const { return tokens_; }
        
        void           FindRepeated(int min);
        
    private:
        TokenVectors        tokens_;
        
        void                Process(const list<S_CATSMAT_chord>& matrix); //overrides base class
        void                ConvertSentences2Tokens();
        void                PostprocessTokens();
        unsigned int        Triple2Token(const Trigram& triple);
        Trigram             Token2Triple(const unsigned long token);
    };
    
}



#endif /* defined(____CATSMAT_Ngram__) */
