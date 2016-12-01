//
//  CATSMAT_Ngram.h
//  
//
//  Created by Jason Stoessel on 25/11/2016.
//
//  The CATSMAT N-gram class is an adaption of the N-gram contrapuntal word method proposed by
//  Schubert, Peter, and Julie Cumming. "Another Lesson from Lassus: Using Computers to Analyse Counterpoint." Early Music 43, no. 4 (November 1, 2015 2015): 577-86.
//
// This is a temporary file!!!

#ifndef ____CATSMAT_Ngram__
#define ____CATSMAT_Ngram__

#include <stdio.h>
#include <vector>
//#include <boost/tuple/tuple.hpp> //included in the following two headers
#include <boost/tuple/tuple_comparison.hpp>
#include <boost/tuple/tuple_io.hpp>
#include "CATSMAT_dyad_sequences.hpp"


typedef boost::tuple<int,int,int> word; //a word is the two vertical intervals and the step in the lower voice
typedef std::vector<word>  sentence; // a sentence is a sequence of words for a voice pair

using namespace std;

namespace CATSMAT
{
    class CATSMAT_NGram_sequences : public CATSMAT_dyad_sequences
    {
    public:
        void    Visit(const CATSMAT_cp_matrix& matrix);
    private:
        void    process(const list<S_CATSMAT_chord>& matrix); //overrides base class
        //vector<string>    sentences;
    };
}


#endif /* defined(____CATSMAT_Ngram__) */
