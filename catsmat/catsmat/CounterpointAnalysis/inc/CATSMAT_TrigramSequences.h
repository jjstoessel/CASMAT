/*!
    CATSMAT_TrigramSequences
    =============
    \file       CATSMAT_TrigramSequences.h
    \brief      Class to calculate N-grams for dyad sequences
    \details    The CATSMAT_TrigramSequences class is an adaption of the N-gram contrapuntal word method proposed by
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


#ifndef ____CATSMAT_TrigramSequences__
#define ____CATSMAT_TrigramSequences__

#include <stdio.h>
#include <vector>
#include <array>
#include "CATSMAT_dyad_sequences_base.h"

using namespace std;

namespace CATSMAT
{
    
    using Sentence = std::vector<std::array<signed int,3> >;
    
    class CATSMAT_TrigramSequences : public CATSMAT_dyad_sequences_base<Sentence>, public BaseVisitable<void, DefaultCatchAll, true>
    {
    public:
        
        typedef unsigned int                Token;
        typedef std::array<signed int,3>    Trigram; //a word is the two vertical intervals and the step in the lower voice
        typedef std::vector<Trigram>        Sentence; // a sentence is a sequence of words for a voice pair
        typedef std::vector<vector<Token> > TokenVectors;
        enum    TrigramMembers { dyad1, dyad2, lowMelInterval };
        
        friend  ostream& operator<<(ostream& os, const CATSMAT_TrigramSequences& sequences);
        friend  ostream& operator<<(ostream& os, const Trigram&);
        friend  ostream& operator<<(ostream& os, Trigram&);
        friend  ostream& operator<<(ostream& os, const Token&);
        friend  ostream& operator<<(ostream& os, Token&);
        
        void    Accept(::Loki::BaseVisitor& guest) const { return AcceptImpl(*this, guest); }
        static  Trigram             Token2Triple(Token token);
        static  Token               Triple2Token(const Trigram& triple);
        
        CATSMAT_TrigramSequences() : CATSMAT_dyad_sequences_base<Sentence>() {}
        ~CATSMAT_TrigramSequences() {}
        
        void    Visit(const CATSMAT_cp_matrix& matrix);
        
        void    Print(ostream& os) const;
        
        TokenVectors   get_tokens() const { return tokens_; }
        
    private:
        TokenVectors        tokens_;
        
        void                Process(const list<S_CATSMAT_chord>& matrix); //overrides base class
        void                ConvertSentences2Tokens();
        void                PostprocessTokens();
        static bool         IsRepeatedIntervalToken(const Token token);
        static bool         IsZero(Token token1, Token token2);
        static Token        TransformTokenUnaryOp(const Token& token);
        bool                TokenContainsDissonantDyad(const Token& token, TrigramMembers& dissonant_dyad_index);
    };
    
    //Visitor class to Trigram Sequences to extract trigram profile as all tokens from all sequences
    class CATSMAT_TrigramInformation : public BaseVisitor, public Visitor<CATSMAT_TrigramSequences, void, true>
    {
    public:
        typedef map<CATSMAT_TrigramSequences::Token,int> PROFILE;
        
        friend  ostream& operator<< (ostream& os, const CATSMAT_TrigramInformation& trigram_info );
        
        CATSMAT_TrigramInformation() {}
        ~CATSMAT_TrigramInformation() {}
        
        void Visit(const CATSMAT_TrigramSequences& sequences);
        void Print(ostream& os) const;
        PROFILE& token_count() { return token_count_; }
        
    private:
        PROFILE token_count_;
    };
    
    ostream& operator<<(ostream& os, const CATSMAT_TrigramSequences& sequences);
    ostream& operator<<(ostream& os, const CATSMAT_TrigramSequences::Trigram&);
    ostream& operator<<(ostream& os, CATSMAT_TrigramSequences::Trigram&);
    
}



#endif /* defined(____CATSMAT_TrigramSequences__) */
