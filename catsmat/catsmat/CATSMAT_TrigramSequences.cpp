//
//  CATSMAT_TrigramSequences.cpp
//  
//
//  Created by Jason Stoessel on 25/11/2016.
//


#include "CATSMAT_TrigramSequences.hpp"
#include "IMUSANT_generalised_interval.h"
#include "CATSMAT_exception.h"
#include "CATSMAT_score_profile.hpp"

namespace CATSMAT
{
    
    //friendly print operators for trigram sequence, trigrams and tokens
    ostream& operator<<(ostream& os, const CATSMAT_TrigramSequences& sequences)
    {
        sequences.Print(os);
        
        return os;
    }

    ostream& operator<<(ostream& os, const CATSMAT_TrigramSequences::Trigram& trigram)
    {
        os << "[" << trigram[CATSMAT_TrigramSequences::dyad1] << ", " << trigram[CATSMAT_TrigramSequences::dyad2] << ", " << trigram[CATSMAT_TrigramSequences::lowMelInterval] << "] ";
        
        return os;
    }
    
    ostream& operator<<(ostream& os, CATSMAT_TrigramSequences::Trigram& trigram)
    {
        os << "[" << trigram[CATSMAT_TrigramSequences::dyad1] << ", " << trigram[CATSMAT_TrigramSequences::dyad2] << ", " << trigram[CATSMAT_TrigramSequences::lowMelInterval] << "] ";
        
        return os;
    }
    
    ostream& operator<<(ostream& os, const CATSMAT_TrigramSequences::Token& token)
    {
        os << CATSMAT_TrigramSequences::Token2Triple(token);
        return os;
    }
    
    ostream& operator<<(ostream& os, CATSMAT_TrigramSequences::Token& token)
    {
        os << CATSMAT_TrigramSequences::Token2Triple(token);
        return os;
    }
    
    void
    CATSMAT_TrigramSequences::
    Visit(const CATSMAT_cp_matrix& matrix)
    {
        matrix_ = &matrix;
        Process(matrix.getCPmatrix());
    }


    void CATSMAT_TrigramSequences::
    Process(const list<S_CATSMAT_chord> &matrix)
    {
        if (!matrix.empty())
        {
            //iterate through all chords
            for (auto chord = matrix.begin(); chord!=matrix.end(); chord++ )
            {
                auto nextchord = std::next(chord);
                if (nextchord==matrix.end()) break;
                
                map<int, S_IMUSANT_note>::size_type chord_size = (**chord).size();
                map<int, S_IMUSANT_note>::size_type next_chord_size = (**nextchord).size();
                if (vectors_.size()!=chord_size) vectors_.resize((chord_size)*(chord_size-1)/2);
                //get triple for each voice pair in chord
                //deref chord notes
                map<int, S_IMUSANT_note> chord_notes = **chord;
                map<int, S_IMUSANT_note> nextchord_notes = **nextchord;
                vector<Sentence>::iterator sentences_iter = vectors_.begin(); 
                
                
                for (int i = 0; i<chord_size; i++)
                {
                    for (int j=i; ++j<next_chord_size; /*nothing here*/)
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
                
                nextchord++;
            }

#ifdef _DEBUG
            //error checking - rows of tuples should be the same length
            vector<Sentence>::iterator sentences_iter=vectors_.begin();
            vector<Sentence>::size_type size = sentences_iter->size();
            
            //the index of sentence will always correspond to the index of CPMatrix
            //the index of sentences will always correspond to one pair of voices

            for ( ;sentences_iter!=vectors_.end();sentences_iter++ )             {
                if (size!=sentences_iter->size()) throw catsmat_runtime_error("Bad size count in NGram_sequences::process");
                if (size!=matrix.size()-1) throw catsmat_runtime_error("Bad size count in NGram_sequences::process");
            }
#endif
            
            ConvertSentences2Tokens();
            PostprocessTokens();
        }

    }

    void
    CATSMAT_TrigramSequences::
    ConvertSentences2Tokens()
    {
        tokens_.resize(vectors_.size());
        
        vector<vector<CATSMAT_TrigramSequences::Token> >::iterator tokens = tokens_.begin();
        
        for (vector<Sentence>::iterator i = vectors_.begin(); i != vectors_.end(); i++)
        {
            for (Sentence::iterator j = i->begin(); j!=i->end(); j++) {
                Trigram trigram = *j;
                CATSMAT_TrigramSequences::Token token = Triple2Token(trigram);
                tokens->push_back(token);
                assert(Token2Triple(token)==trigram);
            }
            tokens++;
        }
    }

    void
    CATSMAT_TrigramSequences::
    PostprocessTokens()
    {
        
        if (ignore_dissonances_)
        {
            //simplest way is to look at token as triple and exclude and token that contains a vertical dissonance. Yet, this will require the removal of at least two tokens and replacement by a single one
            for ( vector<vector<Token> >::iterator tokens = tokens_.begin(); tokens != tokens_.end(); tokens++)
            {
                //find and transform all trigram tokens that contain a dissonance. NB. won't work for consecutive dissonances.
                //eg. [7,6,1],[6,5,1] becomes [7,5,2], i.e. octave to sixth by third step in bass
                
                std::vector<Token> without_dissonances;
                
                for (std::vector<Token>::iterator token = tokens->begin();
                     token!=tokens->end();
                     token++)
                {
                    TrigramMembers token_dissonant_dyad_index, next_dissonant_dyad_index;
                    if (TokenContainsDissonantDyad(*token, token_dissonant_dyad_index))
                    {
                        if (token_dissonant_dyad_index == TrigramMembers::dyad2)
                        {
                            std::vector<Token>::iterator next_token = std::next(token);
                            if (next_token!=tokens->end())
                            {
                                if (TokenContainsDissonantDyad(*next_token,next_dissonant_dyad_index))
                                {
                                    if (next_dissonant_dyad_index == TrigramMembers::dyad1)
                                    {
                                        Trigram trigram = Token2Triple(*token);
                                        Trigram next_trigram = Token2Triple(*next_token);
                                        Trigram new_trigram = { trigram[TrigramMembers::dyad1], next_trigram[TrigramMembers::dyad2], trigram[TrigramMembers::lowMelInterval]+next_trigram[TrigramMembers::lowMelInterval] };
                                        Token new_token = Triple2Token(new_trigram);
                                        without_dissonances.push_back(new_token);
                                    }
                                }
                            }
                        }
                    }
                    else
                        without_dissonances.push_back(*token);
                    
                }
                
                //finally, remove the adjacent repeated tokens
                *tokens = without_dissonances;
            }
        }
        
        if (ignore_repeated_) //remove repeated trigrams (often caused by split in CPMatrix)
        {
            for ( vector<vector<Token> >::iterator tokens = tokens_.begin(); tokens != tokens_.end(); tokens++)
            {
                //remove consecutive interval tokens and resize
                std::vector<Token>::iterator it;
                it = std::remove_if(tokens->begin(), tokens->end(), IsRepeatedIntervalToken);
                tokens->resize( std::distance(tokens->begin(),it) );
                //remove consecutive zero tokens and resize
                it = std::unique(tokens->begin(), tokens->end(), IsZero);
                tokens->resize( std::distance(tokens->begin(),it) );
            }
        }
    }
    
    //unary function (predicate) for removing trigrams of repeated intervals with std::remove_if
    bool
    CATSMAT_TrigramSequences::
    IsRepeatedIntervalToken(const Token token)
    {
        Trigram trigram = Token2Triple(token);
        return ((trigram[dyad1]==trigram[dyad2] && trigram[dyad1]!=0) && (trigram[lowMelInterval]==0));
    }
    
    //unary function (predicate) for removing repeats of trigrams of [0,0,0]
    bool
    CATSMAT_TrigramSequences::
    IsZero(Token token1, Token token2)
    {
        return (token1==0 && token2==0);
    }
    
    CATSMAT_TrigramSequences::Token
    CATSMAT_TrigramSequences::TransformTokenUnaryOp(const Token& token)
    {
        Trigram trigram = Token2Triple(token);
        
        //assume for now that only one dyad is possibly dissonant
        if (trigram[TrigramMembers::dyad1]==2
            || trigram[TrigramMembers::dyad1]==4
            || trigram[TrigramMembers::dyad1]==7)
        {
            trigram[TrigramMembers::dyad1] = trigram[TrigramMembers::dyad2];
        }
        else if (trigram[TrigramMembers::dyad2]==2
                 || trigram[TrigramMembers::dyad2]==4
                 || trigram[TrigramMembers::dyad2]==7)
        {
            trigram[TrigramMembers::dyad2] = trigram[TrigramMembers::dyad1];
        }
        
        return Triple2Token(trigram);
    }
    
    bool
    CATSMAT_TrigramSequences::
    TokenContainsDissonantDyad(const Token& token, TrigramMembers& dissonant_dyad_index)
    {
        bool contains_dissonance = false;
        
        Trigram trigram = Token2Triple(token);
        
        //assume for now that only one dyad is possibly dissonant
        if (trigram[TrigramMembers::dyad1]==IMUSANT_interval::basic::second
            || trigram[TrigramMembers::dyad1]==IMUSANT_interval::basic::fourth
            || trigram[TrigramMembers::dyad1]==IMUSANT_interval::basic::seventh)
        {
            dissonant_dyad_index = TrigramMembers::dyad1;
            contains_dissonance = true;
        }
        else if (trigram[TrigramMembers::dyad2]==IMUSANT_interval::basic::second
                 || trigram[TrigramMembers::dyad2]==IMUSANT_interval::basic::fourth
                 || trigram[TrigramMembers::dyad2]==IMUSANT_interval::basic::seventh)
        {
            dissonant_dyad_index = TrigramMembers::dyad2;
            contains_dissonance = true;
        }
        
        return contains_dissonance;
    }
    /*
        \brief function to convert at triple to a token
     
        bits 1-8 contain the first vertical interval
        bits 8-16 contain the second vertical interval
        bits 16-24 contains the lower melodic interval
        bits 25-32 are reserved (possibly for location data, but will need to be masked for comparison operators)
        
        static member function
    */
    
    CATSMAT_TrigramSequences::Token
    CATSMAT_TrigramSequences::
    Triple2Token(const Trigram& triple)
    {
        //implicit assumption: signed ints use two's complement and there is no interval > 255 or < -256
        unsigned int token = 0;
        token = (triple[dyad1]&0x000000ff) | (triple[dyad2]&0x000000ff)<<8 | (triple[lowMelInterval]&0x000000ff)<<16;
        assert(triple==Token2Triple(token));
        return token;
        
        /*std::ostringstream str;
        str << triple[lowMelInterval] << triple[dyad2] << triple[dyad1];
        Token token_hash = std::hash<std::string>{}(str.str());
    
        return token_hash;*/
    }
    
    //static member function
    CATSMAT_TrigramSequences::Trigram
    CATSMAT_TrigramSequences::
    Token2Triple(Token token)
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
    CATSMAT_TrigramSequences::
    Print(ostream& os) const
    {
        int i = 1;
        for (auto triples : vectors_)//for (auto triples : sentences_)
        {
            os << "Voice pair " << i << ": ";
            for (auto triple : triples)
            {
                os << triple;
            }
            os << std::endl;
            i++;
        }
    }
    
    ostream& operator<< (ostream& os, const CATSMAT_TrigramInformation& trigram_info )
    {
        trigram_info.Print(os);
        return os;
    }
    
    void
    CATSMAT_TrigramInformation::Visit(const CATSMAT_TrigramSequences& sequences)
    {
        CATSMAT_TrigramSequences::TokenVectors token_vectors = sequences.get_tokens();
        
        for (auto token_vector : token_vectors)
        {
            for (auto token : token_vector)
            {
                token_count_[token] = token_count_[token] + 1 ;
            }
        }
    }
    
    void
    CATSMAT_TrigramInformation::Print(ostream& os) const
    {
        for (auto token_count_pair : token_count_ )
        {
            os << CATSMAT_TrigramSequences::Token2Triple(token_count_pair.first) << ": " << token_count_pair.second << endl;
        }
    }
    
    //Specialisation of CATSMAT_score_profile::print for CATSMAT_TrigramSequences::Token
    //required to ensure that trigram is printed (operator<<) rather than token
    template<>
    void
    CATSMAT_score_profile<CATSMAT_TrigramSequences::Token>::
    print(ostream& os) const
    {
        ostringstream header,lines,total;
        header << fType << fDelimiter;
        total << "Total" << fDelimiter;
        
        for (std::pair<CATSMAT_TrigramSequences::Token, int> data : fProfile)
        {
            CATSMAT_TrigramSequences::Trigram trigram = CATSMAT_TrigramSequences::Token2Triple(data.first);
            //add pitch name to header
            header << trigram << fDelimiter;
            total << data.second << fDelimiter;
        }
        
        for (auto s : fPartNames)
        {
            ostringstream line;
            line << s.c_str() << fDelimiter;
            
            for (auto data : fProfile)
            {
                CATSMAT_TrigramSequences::Token t = data.first; //pitch type
                //search table for occurrences of pitch in part
                auto it = std::find_if(fTable.begin(), fTable.end(), [&s,&t](const TABLE_TUPLE& item)
                                       {
                                           return s == get<0>(item) && t == get<1>(item);
                                       }); //returns iterator
                if (it!=fTable.end())
                    line << get<2>(*it) << fDelimiter;
                else //not found
                    line << "0" << fDelimiter;
                
            }
            
            lines << line.str() << endl;
        }
        
        header << endl;
        
        os << header.str();
        os << lines.str();
        os << total.str() << endl;
    }
    
}
