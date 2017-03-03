//
//  CATSMAT_TrigramSequences.cpp
//  
//
//  Created by Jason Stoessel on 25/11/2016.
//


#include "CATSMAT_TrigramSequences.hpp"
#include "IMUSANT_generalised_interval.h"
#include "CATSMAT_exception.h"

namespace CATSMAT
{
    
    
    ostream& operator<<(ostream& os, const CATSMAT_TrigramSequences& sequences)
    {
        sequences.Print(os);
        
        return os;
    }

    void
    CATSMAT_TrigramSequences::Visit(const CATSMAT_cp_matrix& matrix)
    {
        matrix_ = &matrix;
        Process(matrix.getCPmatrix());
    }


    void CATSMAT_TrigramSequences::Process(const list<S_CATSMAT_chord> &matrix)
    {
        if (!matrix.empty())
        {
            //iterate through all chords
            for (auto chord = matrix.begin(), nextchord = chord; ++nextchord!=matrix.end(); chord++)
            {
                map<int, S_IMUSANT_note>::size_type chord_size = (**chord).size();
                if (vectors_.size()!=chord_size) vectors_.resize((chord_size)*(chord_size-1)/2);
                //get triple for each voice pair in chord
                //deref chord notes
                map<int, S_IMUSANT_note> chord_notes = **chord;
                map<int, S_IMUSANT_note> nextchord_notes = **nextchord;
                vector<Sentence>::iterator sentences_iter = vectors_.begin(); 
                
                
                for (int i = 0; i<chord_size; i++)
                {
                    for (int j=i; ++j<chord_size; /*nothing here*/)
                    {
                       
                        CATSMAT_TrigramSequences::Trigram triple = { 0, 0, 0 }; //default null triple - another value?
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
            vector<Sentence>::iterator sentences_iter=vectors_.begin();
            vector<Sentence>::size_type size = sentences_iter->size();
            
            //the index of sentence will always correspond to the index of CPMatrix
            //the index of sentences will always correspond to one pair of voices
            for ( ;sentences_iter!=vectors_.end();sentences_iter++ )             {
                if (size!=sentences_iter->size()) throw catsmat_runtime_error("Bad size count in NGram_sequences::process");
                if (size!=matrix.size()-1) throw catsmat_runtime_error("Bad size count in NGram_sequences::process");
            }
            
            ConvertSentences2Tokens();
        }

    }

    void
    CATSMAT_TrigramSequences::
    ConvertSentences2Tokens()
    {
        tokens_.resize(vectors_.size());//tokens_.resize(sentences_.size());
        
        auto j = tokens_.begin();
        
        for (auto i = vectors_.begin(); i!=vectors_.end(); i++, j++)
        {
            j->resize(i->size());
            for ( auto m = i->begin(); m!=i->end(); m++)
            {
                unsigned int token = Triple2Token(*m);
                j->push_back(token);
            }
        }
    }

    /*
        \brief function to convert at triple to a token
     
        bits 1-8 contain the first vertical interval
        bits 8-16 contain the second vertical interval
        bits 16-24 contains the lower melodic interval
        bits 25-32 are reserved (possibly for location data, but will need to be masked for comparison operators)
    */
    unsigned int
    CATSMAT_TrigramSequences::Triple2Token(const Trigram& triple)
    {
        //implicit assumption: signed ints use two's complement and there is no interval > 255 or < -256
        unsigned int token = 0;
        token = (triple[dyad1]&0x000000ff) | (triple[dyad2]&0x000000ff)<<8 | (triple[lowMelInterval]&0x000000ff)<<16;
        
#ifdef DEBUG
        Trigram test_triple = Token2Triple(token);
        if (test_triple!=triple) throw catsmat_logic_error("error in NGram::Triple2Token");
#endif
        
        return token;
    }

    CATSMAT_TrigramSequences::Trigram
    CATSMAT_TrigramSequences::
    Token2Triple(const unsigned long token)
    {
        Trigram triple = {0, 0, 0};
        signed char s_dyad1, s_dyad2, s_mel_interval;
        s_dyad1 = token & 0x000000ff;
        s_dyad2 = (token & 0x0000ff00) >> 8;
        s_mel_interval = (token & 0x00ff0000) >> 16;
        //implicit type conversion retains sign (as two's complement)
        triple[dyad1] = s_dyad1;
        triple[dyad2] = s_dyad2;
        triple[lowMelInterval] = s_mel_interval;
        return triple;
    }

    void
    CATSMAT_TrigramSequences::Print(ostream& os) const
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
    CATSMAT_TrigramSequences::FindRepeated(int min)
    {
        
    }
}
