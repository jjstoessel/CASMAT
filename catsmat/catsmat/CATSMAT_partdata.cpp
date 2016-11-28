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
    
    
    CATSMAT_partdata::CATSMAT_partdata()
    {
        fLastPitch = new_IMUSANT_pitch();
    }
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
                    fNoteCount++; //probably pointless since the result can be summed from the pitch profile
                    int currentCount = fPitchProfile[*note->pitch()];
                    fPitchProfile[*note->pitch()] =  currentCount + 1;
                    //see there is a last pitch stored and create melodic interval
                    if (*fLastPitch==IMUSANT_pitch())
                    {
                        *fLastPitch = *note->pitch();
                    }
                    else
                    {
                        IMUSANT_interval interval(fLastPitch, note->pitch());
                        int currentIntervalCount = fHIntervalProfile[interval];
                        fHIntervalProfile[interval] = currentIntervalCount + 1;
                    }
                }
                else if (note->getType()==IMUSANT_NoteType::rest)
                {
                    fRestCount++;
                    *fLastPitch = IMUSANT_pitch(); //set to an undefined pitch event
                    //could collect rest profiles here
                }
                
            }
        }
    }
    
    void
    CATSMAT_partdata::print(ostream& os)
    {
        ostringstream intervals;
        ostringstream interval_counts;
        
        for (auto i: fHIntervalProfile )
        {
            intervals << i.first << "\t";
            interval_counts << i.second << "\t";
        }
        os << intervals.str() << std::endl;
        os << interval_counts.str() << std::endl;
    }

}