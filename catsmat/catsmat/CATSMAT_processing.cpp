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

using namespace std;
using namespace boost;

namespace CATSMAT
{
    
    void
    CATSMAT_processing::
    find_repeated_dyad_sequences(int min, bool ignoreDissonances, bool ignoreRepeatedDyads, bool across)
    {
        for (auto score : this->getScores())
        {
            CATSMAT_collection_visitor  score_to_matrix_translator;
            CATSMAT_dyad_sequences      dyads;
            
            //set internal parameters called within search functions
            dyads.ignoreDissonances(ignoreDissonances);
            dyads.ignoreRepeatedDyads(ignoreRepeatedDyads);
            
            if (score!=NULL)
            {
                (*score).accept(score_to_matrix_translator);
                score_to_matrix_translator.getCPMatrix()->Accept(dyads);
                
                cout << "Repeated dyad sequences for each voice pair in " << (*score).getMovementTitle() << endl;
                if (across)
                    dyads.find_repeated_across(min);
                else
                    dyads.find_repeated_in(min);
            }
            
        }
    }
    
    void
    CATSMAT_processing::
    find_repeated_dyadtuple_sequences(int min)
    {
        
    }
    
    void
    CATSMAT_processing::
    find_repeated_sonority_sequences(int min)
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
    
} //namespace CATSMAT