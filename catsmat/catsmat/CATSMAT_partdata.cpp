//
//  CATSMAT_partdata.cpp
//  catsmat
//
//  Created by Jason Stoessel on 25/09/2016.
//
//

#include "CATSMAT_partdata.h"
#include "IMUSANT_note.h"

namespace CATSMAT {
    
    //Collect all basic data from part
    //map<IMUSANT_pitch,int>      fPitchProfile;
    //map<IMUSANT_duration,int>   fDurationProfile;
    //map<IMUSANT_interval, int>  fIntervalProfile;
    void
    CATSMAT_partdata::findBasicDataFromPart(S_IMUSANT_part part)
    {
        //we could use IMUSANT_vector<S_IMUSANT_note> notes() to get all notes in a part if not interested in other elements
        for (S_IMUSANT_measure measure: part->measures() )
        {
            for (S_IMUSANT_note note : measure->notes() )
            {
                if (note->getType()==IMUSANT_NoteType::pitch && (!note->isTiedPrevious() || !note->isTiedBothSides()))
                {
                    fNoteCount++;
                    int currentCount = fPitchProfile[*note->pitch()];
                    fPitchProfile[*note->pitch()] =  currentCount + 1;
                }
                else if (note->getType()==IMUSANT_NoteType::rest) {
                    fRestCount++;
                }
                
                //get melodic intervals
                //for first note of a part, need to store; operate only for n>=1
                if (fPreviousNote==NULL) {
                    fPreviousNote = note;
                }
                else if (note->getType()==IMUSANT_NoteType::pitch && (!note->isTiedPrevious() || !note->isTiedBothSides()))
                {
                    IMUSANT_interval interval(fPreviousNote->pitch(), note->pitch());
                    int currentIntervalCount = fHIntervalProfile[interval];
                    fHIntervalProfile[interval] = currentIntervalCount + 1;
                    
                }
            
                
            }
        }
    }

}