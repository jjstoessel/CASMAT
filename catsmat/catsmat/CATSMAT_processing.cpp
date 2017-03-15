/*
 *  CATSMAT_processing.cpp
 *  catsmat
 *
 *  Created by Jason Stoessel on 12/03/15.
 *  Copyright 2015 the programmers. All rights reserved.
 *
 *  A file processing class for CATSMAT.
 */
#include <iostream>
#include <deque>
#include <boost/filesystem.hpp>

#include "CATSMAT_processing.hpp"

#include "CATSMAT_dyad_sequences.hpp"
// #include "CATSMAT_dyadtuple_sequences.hpp"
#include "CATSMAT_sonority_sequences.hpp"
#include "CATSMAT_score_profile.hpp"
#include "CATSMAT_TrigramSequences.hpp"
#include "CATSMAT_TrigramSuffixTreeBuilder.hpp"
#include "CATSMAT_canonic_techniques_tools.hpp"


using namespace std;
using namespace boost;



namespace CATSMAT
{
    
    void
    CATSMAT_processing::
    FindRepeatedDyadSequences(int min, bool ignoreDissonances, bool ignoreRepeatedDyads, bool across)
    {
        for (auto score : this->getScores())
        {
            CATSMAT_collection_visitor  score_to_matrix_translator;
            CATSMAT_dyad_sequences      dyads;
            
            //set internal parameters called within search functions
            dyads.set_ignore_dissonances(ignoreDissonances);
            dyads.set_ignore_repeated(ignoreRepeatedDyads);
            
            if (score!=NULL)
            {
                (*score).accept(score_to_matrix_translator);
                score_to_matrix_translator.getCPMatrix()->Accept(dyads);
                
                cout << "Repeated dyad sequences for each voice pair in " << (*score).getMovementTitle() << endl;
                if (across)
                    dyads.FindRepeatedAcross(min);
                else
                    dyads.FindRepeatedIn(min);
            }
            
        }
    }
    
    void
    CATSMAT_processing::
    FindRepeatedDyadtupleSequences(int min)
    {
        
    }
    
    void
    CATSMAT_processing::
    FindRepeatedSonoritySequences(int min)
    {
        for (auto score : this->getScores())
        {
            CATSMAT_collection_visitor      score_to_matrix_translator;
            CATSMAT_sonority_sequences      sonorities;
            
            if (score!=NULL)
            {
                (*score).accept(score_to_matrix_translator);
                score_to_matrix_translator.getCPMatrix()->Accept(sonorities);
                
                cout << "Repeated dyad sequences in " << (*score).getMovementTitle() << endl;
                sonorities.find_repeated(min);
            }
            
        }

    }
    
    void
    CATSMAT_processing::FindRepeatedTrigramSequences(int min, bool ignoreDissonances, bool ignoreRepeatedDyads)
    {
        for (auto score : this->getScores())
        {
            CATSMAT_collection_visitor      score_to_matrix_translator;
            CATSMAT_TrigramSequences        trigram_sequences;
            trigram_sequences.set_ignore_dissonances(ignoreDissonances);
            trigram_sequences.set_ignore_repeated(ignoreRepeatedDyads);
            
            if (score!=NULL)
            {
                (*score).accept(score_to_matrix_translator);
                if (!score_to_matrix_translator.getCPMatrix()->SelfTest())
                    catsmat_runtime_error("Problem in CP Matrix for " + score->getWorkTitle());
                score_to_matrix_translator.getCPMatrix()->Accept(trigram_sequences);
                CATSMAT_TrigramSuffixTreeBuilder trigram_tree;
                trigram_sequences.Accept(trigram_tree);
                cout << "Repeated trigram sequences in " << (*score).getMovementTitle() << endl;
                cout << trigram_tree.FindAndPrintRepeatedSubstrings().c_str();
            }
            
        }
    }
    
    //This method identifies canonic parts only, places them in a CP matrix and then looks for repeated sequences of trigrams
    void
    CATSMAT_processing::
    FindRepeatedTrigramSequencesCanonic(int min, bool ignoreDissonances, bool ignoreRepeatedDyads)
    {
        for (auto score : this->getScores())
        {
            S_CATSMAT_CanonicTechniquesTools tools = new_CATSMAT_object<CATSMAT_CanonicTechniquesTools>();
            tools->Initialise(score);
            for (auto canon : tools->GetCanonTypes())
            {
                CATSMAT_TrigramSequences        trigram_sequences;
                S_CATSMAT_cp_matrix matrix = new_CATSMAT_object<CATSMAT_cp_matrix>();
                
                trigram_sequences.set_ignore_dissonances(ignoreDissonances);
                trigram_sequences.set_ignore_repeated(ignoreRepeatedDyads);
                
                for (auto part : canon.parts_)
                    matrix->add(part);
                matrix->Accept(trigram_sequences);
                CATSMAT_TrigramSuffixTreeBuilder trigram_tree;
                trigram_sequences.Accept(trigram_tree);
                cout << "Repeated trigram sequences in " << (*score).getMovementTitle() << endl;
                cout << trigram_tree.FindAndPrintRepeatedSubstrings().c_str();
            }
        }
    }
    
    void
    CATSMAT_processing::
    FindTrigramCounts(bool ignoreDissonances, bool ignoreRepeatedDyads)
    {
        for (auto score : this->getScores())
        {
            CATSMAT_collection_visitor      score_to_matrix_translator;
            CATSMAT_TrigramSequences        trigram_sequences;
            CATSMAT_TrigramInformation      trigram_info;
            trigram_sequences.set_ignore_dissonances(ignoreDissonances);
            trigram_sequences.set_ignore_repeated(ignoreRepeatedDyads);
            
            score->accept(score_to_matrix_translator);
            score_to_matrix_translator.getCPMatrix()->Accept(trigram_sequences);
            trigram_sequences.Accept(trigram_info);
            
            cout << "Trigram counts in " << (*score).getMovementTitle() << endl;
            cout << trigram_info;
        }
    }
    
    /*!
     \fn CATSMAT_processing::FindSummativeTrigramCounts(bool ignoreDissonances, bool ignoreRepeatedDyads)
     
     \brief returns a table that collects all results from multiple scores
     
     */
    void
    CATSMAT_processing::
    FindSummativeTrigramCounts(bool ignoreDissonances, bool ignoreRepeatedDyads)
    {
        CATSMAT_score_profile<CATSMAT_TrigramSequences::Token> trigrams_profile("trigram");
        
        for (auto score : this->getScores())
        {
            CATSMAT_collection_visitor      score_to_matrix_translator;
            CATSMAT_TrigramSequences        trigram_sequences;
            CATSMAT_TrigramInformation      trigram_info;
            
            trigram_sequences.set_ignore_dissonances(ignoreDissonances);
            trigram_sequences.set_ignore_repeated(ignoreRepeatedDyads);
            score->accept(score_to_matrix_translator);
            score_to_matrix_translator.getCPMatrix()->Accept(trigram_sequences);
            trigram_sequences.Accept(trigram_info);
            map<CATSMAT_TrigramSequences::Token, int> score_tokens_by_count = trigram_info.token_count(); //CATSMAT_score_profile::PROFILE
            string part_name = score->getWorkTitle();
            if (part_name.empty())
            {
                part_name = score->getMovementTitle();
                if (part_name.empty()) throw catsmat_runtime_error("The work or movement lacks a name");
            }
            trigrams_profile.Accumulate(part_name, score_tokens_by_count);
        }
        
        cout << "Printing trigram table for inputed scores";
        
        cout << trigrams_profile;
        
        
    }

} //namespace CATSMAT
