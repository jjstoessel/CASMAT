//
//  CATSMAT_scoredatacollector.cpp
//  catsmat
//
//  Created by Jason Stoessel on 22/09/2016.
//
//

#include "CATSMAT_scoredatacollector.h"
#include "CATSMAT_collection_visitor.h"

namespace CATSMAT {
    
    void CATSMAT_scoredatacollector::Visit(const CATSMAT_processing& processor)
    {
        for (auto score : processor.getScores())
        {
            //get basic data like note, interval, etc. counts
            //S_CATSMAT_scoredata scoredata = new_CATSMAT_scoredata();
            S_CATSMAT_scoredata scoredata = new_CATSMAT_object<CATSMAT_scoredata>();
            
            scoredata->findBasicDataFromScore(score);
            
            //get contrapuntal data, ie. from CP_Matrix
            CATSMAT_collection_visitor  score_to_matrix_translator;
            CATSMAT_dyad_sequences      dyads;
            
            score->accept(score_to_matrix_translator);
            score_to_matrix_translator.getCPMatrix()->Accept(dyads);
            
            scoredata->findCountrapuntalData(dyads);
            
            scoresdata.push_back(scoresdata);
            
        }
    }
    
    void CATSMAT_scoredatacollector::print(ostream& os)
    {
        for (auto scoredata : scoresdata)
        {
            scoredata->print(os);
        }
    }
    
    ostream& operator<< (ostream& os, const CATSMAT_scoredatacollector& elt )
    {
        elt.print(os);
        
        return os;
    }
    
}