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
            findBasicDataFromPart(part);
        }
    }
    
    //Collect all basic data from part
    void
    CATSMAT_scoredata::findBasicDataFromPart(S_IMUSANT_part part)
    {
        //we could use IMUSANT_vector<S_IMUSANT_note> notes() to get all notes in a part if not interested in other elements
        for (S_IMUSANT_measure measure: part->measures() )
        {
            fNotesPerPart[part->getID()] = 0;
            
            for (S_IMUSANT_note note : measure->notes() )
            {
                if (note->getType()==IMUSANT_NoteType::pitch && (!note->isTiedPrevious() || !note->isTiedBothSides()))
                {
                    fNotesPerPart[part->getID()]=fNotesPerPart[part->getID()]+1;
                    fTotalNoteCount++;
                }
                else if (note->getType()==IMUSANT_NoteType::rest) {
                    fTotalRestCount++;
                }
            }
        }
    }
    
     
    void
    CATSMAT_scoredata::
    findContrapuntalData(CATSMAT_dyad_sequences& dyads)
    {
        
    }
}