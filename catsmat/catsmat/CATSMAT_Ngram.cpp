//
//  CATSMAT_Ngram.cpp
//  
//
//  Created by Jason Stoessel on 25/11/2016.
//
/*!
    CATSMAT_Ngram
    =============
    \file       CATSMAT_Ngram.cpp
    \brief      Class to calculate N-grams for dyad sequences
    \details    The CATSMAT N-gram class is an adaption of the N-gram contrapuntal word method proposed by
                Schubert, Peter, and Julie Cumming. "Another Lesson from Lassus: Using Computers to Analyse Counterpoint." Early Music 43, no. 4 (November 1, 2015 2015): 577-86.
                It relies upon CATSMAT_CPmatrix and IMUSANT_generalised_interval
    \author     Jason Stoessel
    \author
    \version
    \date       Created by Jason Stoessel on 25/11/2016
    \bug
    \warning
    \copyright
 */


#include "CATSMAT_Ngram.h"
#include "IMUSANT_generalised_interval.h"
#include "CATSMAT_exception.h"

using namespace CATSMAT;

ostream& operator<<(ostream& os, const CATSMAT_NGram_sequences& ngrams)
{
    ngrams.print(os);
    
    return os;
}

void
CATSMAT_NGram_sequences::Visit(const CATSMAT_cp_matrix& matrix)
{
    process(matrix.getCPmatrix());
}


void CATSMAT_NGram_sequences::process(const list<S_CATSMAT_chord> &matrix)
{
    if (!matrix.empty())
    {
        //iterate through all chords
        for (auto chord = matrix.begin(), nextchord = chord; ++nextchord!=matrix.end(); chord++)
        {
            map<int, S_IMUSANT_note>::size_type chord_size = (**chord).size();
            if (sentences.size()!=chord_size) sentences.resize((chord_size)*(chord_size-1)/2);
            //get triple for each voice pair in chord
            //deref chord notes
            map<int, S_IMUSANT_note> chord_notes = **chord;
            map<int, S_IMUSANT_note> nextchord_notes = **nextchord;
            vector<sentence>::iterator sentences_iter = sentences.begin();
            
            for (int i = 0; i<chord_size; i++)
            {
                
                for (int j=i; ++j<chord_size; /*nothing here*/)
                {
                   
                    CATSMAT_NGram_sequences::word triple = { 0, 0, 0 }; //default null triple - another value?
                    //only proceed if there are two intervals between voices
                    if (chord_notes[i]->getType()!=IMUSANT_NoteType::rest &&
                        chord_notes[j]->getType()!=IMUSANT_NoteType::rest &&
                        nextchord_notes[i]->getType()!=IMUSANT_NoteType::rest &&
                        nextchord_notes[j]->getType()!=IMUSANT_NoteType::rest)
                    {
                        IMUSANT_generalised_interval v1(chord_notes[j]->pitch(), chord_notes[i]->pitch());
                        IMUSANT_generalised_interval v2(nextchord_notes[j]->pitch(), nextchord_notes[i]->pitch());
                        IMUSANT_generalised_interval h(chord_notes[j]->pitch(), nextchord_notes[j]->pitch());
                        triple = { v1.getNumber(),v2.getNumber(),h.getNumber() };
                        
                    }
                    
                    sentences_iter->push_back(triple);
                    sentences_iter++;
                }
            }
        }
        
        //error checking - rows of tuples should be the same length
        vector<sentence>::iterator sentences_iter=sentences.begin();
        vector<sentence>::size_type size = sentences_iter->size();
        
        for ( ;sentences_iter!=sentences.end();sentences_iter++ )
        {
            if (size!=sentences_iter->size()) throw catsmat_runtime_error("Bad size count in CPMatrix");
        }
    }

}

void
CATSMAT_NGram_sequences::print(ostream& os) const
{
    for (auto triples : sentences)
    {
        for (auto triple : triples)
        {
            os << "[" << triple[dyad1] << ", " << triple[dyad2] << ", " << triple[lowMelInterval];
            os << ", ";
        }
        os << std::endl;
    }
}
