//
//  CATSMAT_scoredata.cpp
//  catsmat
//
//  Created by Jason Stoessel on 22/09/2016.
//
//

#include "CATSMAT_scoredata.h"

namespace CATSMAT {
   
//    VEXP
//    IMUSANT_SMARTP<CATSMAT_scoredata>
//    new_CATSMAT_scoredata()
//    {
//        IMUSANT_score* o = new CATSMAT_scoredata();
//        if (o==0) throw catsmat_runtime_error("Unable to allocate CATSMAT_scoredata");
//        return o;
//    }
    
    void
    CATSMAT_scoredata::
    findBasicDataFromScore(S_IMUSANT_score score)
    {
        //Collect basic metadata for score
        fWorkTitle = score->getWorkTitle();
        fWorkNum = score->getWorkNum();
        fMovementTitle = score->getMovementTitle();
        fMovementNum = score->getMovementNum();
        fCreator = score->getCreator();
        fRights = score->getRights();
        fScoreComments = score->getComments();
        fSource = score->getSource();
        fEditor = score->getEditor();
        fDate = score->getDate();
        
        //cycle through each part collecting data about music notation
        for (auto part : score->partlist()->parts())
        {
            
        }
    }
    
    void
    CATSMAT_scoredata::
    findCountrapuntalData(CATSMAT_dyad_sequences& dyads)
    {
        
    }
}