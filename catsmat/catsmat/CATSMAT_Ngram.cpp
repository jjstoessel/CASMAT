//
//  CATSMAT_Ngram.cpp
//  
//
//  Created by Jason Stoessel on 25/11/2016.
//


#include "CATSMAT_Ngram.hpp"
#include "IMUSANT_generalised_interval.h"
#include "CATSMAT_exception.h"

namespace CATSMAT
{
    
    
    ostream& operator<<(ostream& os, const CATSMAT_NGramSequences& sequences)
    {
        sequences.Print(os);
        
        return os;
    }

    void
    CATSMAT_NGramSequences::Visit(const CATSMAT_cp_matrix& matrix)
    {
        matrix_ = &matrix;
        Process(matrix.getCPmatrix());
    }


    void CATSMAT_NGramSequences::Process(const list<S_CATSMAT_chord> &matrix)
    {
        if (!matrix.empty())
        {
            //iterate through all chords
            for (auto chord = matrix.begin(), nextchord = chord; ++nextchord!=matrix.end(); chord++)
            {
                map<int, S_IMUSANT_note>::size_type chord_size = (**chord).size();
                if (vectors_.size()!=chord_size) vectors_.resize((chord_size)*(chord_size-1)/2);//if (sentences_.size()!=chord_size) sentences_.resize((chord_size)*(chord_size-1)/2);
                //get triple for each voice pair in chord
                //deref chord notes
                map<int, S_IMUSANT_note> chord_notes = **chord;
                map<int, S_IMUSANT_note> nextchord_notes = **nextchord;
                vector<Sentence>::iterator sentences_iter = vectors_.begin(); //vector<Sentence>::iterator sentences_iter = sentences_.begin();
                
                
                for (int i = 0; i<chord_size; i++)
                {
                    for (int j=i; ++j<chord_size; /*nothing here*/)
                    {
                       
                        CATSMAT_NGramSequences::Word triple = { 0, 0, 0 }; //default null triple - another value?
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
            vector<Sentence>::iterator sentences_iter=vectors_.begin();//vector<Sentence>::iterator sentences_iter=sentences_.begin();
            vector<Sentence>::size_type size = sentences_iter->size();
            
            //the index of sentence will always correspond to the index of CPMatrix
            //the index of sentences will always correspond to one pair of voices
            for ( ;sentences_iter!=vectors_.end();sentences_iter++ ) //for ( ;sentences_iter!=sentences_.end();sentences_iter++ )
            {
                if (size!=sentences_iter->size()) throw catsmat_runtime_error("Bad size count in NGram_sequences::process");
                if (size!=matrix.size()-1) throw catsmat_runtime_error("Bad size count in NGram_sequences::process");
            }
            
            ConvertSentences2Tokens();
        }

    }

    void
    CATSMAT_NGramSequences::
    ConvertSentences2Tokens()
    {
        tokens_.resize(vectors_.size());//tokens_.resize(sentences_.size());
        
        auto j = tokens_.begin();
        
        for (auto i = vectors_.begin(); i!=vectors_.end(); i++, j++)//for (auto i = sentences_.begin(); i!=sentences_.end(); i++, j++)
        {
            j->resize(i->size());
            for ( auto m = i->begin(); m!=i->end(); m++)
            {
                unsigned long token = Triple2Token(*m);
                j->push_back(token);
            }
        }
    }

    /*
        \brief function to convert at triple to a token
     
        bits 1-8 contain the first vertical interval
        bits 8-16 contain the second vertical interval
        bits 16-24 contains the lower melodic interval
        bits 25-32 are reserved (possibly for location data, but will need to be masked for comparison operators
    */
    unsigned long
    CATSMAT_NGramSequences::Triple2Token(const Word& triple)
    {
        long token = triple[dyad1] | triple[dyad2]<<8 | triple[lowMelInterval]<<16;
        
        return token;
    }

    CATSMAT_NGramSequences::Word
    CATSMAT_NGramSequences::
    Token2Triple(const unsigned long token)
    {
        Word triple = {0, 0, 0};
        
        triple[dyad1] = token & 0x000000ff;
        triple[dyad2] = (token & 0x0000ff00) >> 8;
        triple[lowMelInterval] = (token & 0x00ff0000) >> 16;
        
        return triple;
    }

    void
    CATSMAT_NGramSequences::Print(ostream& os) const
    {
        int i = 1;
        for (auto triples : vectors_)//for (auto triples : sentences_)
        {
            os << "Voice pair " << i << ": ";
            for (auto triple : triples)
            {
                os << "[" << triple[dyad1] << ", " << triple[dyad2] << ", " << triple[lowMelInterval] << "]";
                os << ", ";
            }
            os << std::endl;
            i++;
        }
    }
    
    void
    CATSMAT_NGramSequences::FindRepeated(int min)
    {
        
    }
}
