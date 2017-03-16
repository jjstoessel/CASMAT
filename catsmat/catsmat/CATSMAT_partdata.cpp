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
                    int currentPCount = fPitchProfile[*note->pitch()];
                    fPitchProfile[*note->pitch()] =  ++currentPCount;
                    int currentDCount = fDurationProfile[*note->duration()];
                    fDurationProfile[*note->duration()] = ++currentDCount;
                    //see if there is a last pitch stored and create melodic interval
                    if (*fLastPitch==IMUSANT_pitch()) //last element was not pitched
                    {
                        *fLastPitch = *note->pitch();
                        fLastContour = IMUSANT_contour_symbol(); //undefined
                    }
                    else
                    {
                        //add interval to interval profile
                        IMUSANT_interval interval(fLastPitch, note->pitch());
                        int currentIntervalCount = fHIntervalProfile[interval];
                        fHIntervalProfile[interval] = currentIntervalCount + 1;
                        
                        //add contour to contour profile
                        IMUSANT_contour_symbol contour_symbol(fLastPitch, note->pitch());
                        fContourSymbolProfile[contour_symbol] = fContourSymbolProfile[contour_symbol] + 1;
                        
                        //add contour duple to contour duple profile
                        if (fLastContour!=IMUSANT_contour_symbol())
                        {
                            std::pair<IMUSANT_contour_symbol,IMUSANT_contour_symbol> contour_pair = std::make_pair(fLastContour, contour_symbol);
                            fContourSymbolDupleProfile[contour_pair] = fContourSymbolDupleProfile[contour_pair] + 1;
                            
                        }
                        
                        fLastContour = contour_symbol;
                        *fLastPitch=*note->pitch();
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
        print_interval_profile(os);
        print_duration_profile(os);
        print_pitch_profile(os);
    }
    
    void
    CATSMAT_partdata::print_interval_profile(ostream& os)
    {
        ostringstream intervals;
        ostringstream interval_counts;
        
        for (auto i: fHIntervalProfile )
        {
            intervals << i.first << "\t"; //interval names
            interval_counts << i.second << "\t"; //melodic interval count
        }
        os << intervals.str() << std::endl;
        os << interval_counts.str() << std::endl;
    }
    
    void
    CATSMAT_partdata::print_duration_profile(ostream& os)
    {
        
    }
    
    void
    CATSMAT_partdata::print_pitch_profile(ostream& os)
    {
        
    }

}
