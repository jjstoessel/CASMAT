//
//  CATSMAT_Ngram.cpp
//  
//
//  Created by Jason Stoessel on 25/11/2016.
//



#include "CATSMAT_Ngram.h"
#include "IMUSANT_generalised_interval.h"

void
CATSMAT::CATSMAT_NGram_sequences::Visit(const CATSMAT_cp_matrix& matrix)
{
    //increase VectorInterval colection according to the formula of unique pairs n(n-1)/2
//    unsigned long partCount = matrix.partCount();
//    
//    while (fVIntervalVectors.size() < ( (partCount)*(partCount-1)/2 ) )
//    {
//        fVIntervalVectors.push_back(new_IMUSANT_interval_vector());
//        fVIntervalVectors.back()->setMaximum(1024);
//    }
    
    process(matrix.getCPmatrix());
}


void CATSMAT::CATSMAT_NGram_sequences::process(const list<S_CATSMAT_chord> &matrix)
{
    
    if (!matrix.empty())
    {
        
        for (auto chord = matrix.begin(), nextchord = chord; chord!=matrix.end(), ++nextchord!=matrix.end(); chord++)
        {
            map<int, S_IMUSANT_note>::size_type chord_size = (**chord).size();
            
            for (int i = 0, j = 1 ; j<chord_size; i++, j++)
            {
                //deref chord notes
                map<int, S_IMUSANT_note> chord_notes = **chord;
                map<int, S_IMUSANT_note> nextchord_notes = **nextchord;
                
                //only proceed if there are two intervals between voices
                if (chord_notes[i]->getType()!=IMUSANT_NoteType::rest &&
                    chord_notes[j]->getType()!=IMUSANT_NoteType::rest &&
                    nextchord_notes[i]->getType()!=IMUSANT_NoteType::rest &&
                    nextchord_notes[j]->getType()!=IMUSANT_NoteType::rest)
                {
                    IMUSANT_generalised_interval v1(chord_notes[j]->pitch(), chord_notes[i]->pitch());
                    IMUSANT_generalised_interval v2(nextchord_notes[j]->pitch(), nextchord_notes[i]->pitch());
                    IMUSANT_generalised_interval h(chord_notes[j]->pitch(), nextchord_notes[j]->pitch());
                    ostringstream s;
                    s << v1.getNumber() << v2.getNumber() << h.getNumber();
                    string word = s.str();
                }
            }
//            map<int, S_IMUSANT_note>::size_type chord_size = (*(*chord)).size();
//            
//            int dyad_pair = 0;
//            
//            for (int i = 0; i<chord_size; i++)
//            {
//                for (int j=i; ++j<chord_size; /*nothing here*/)
//                {
//                    map<int, S_IMUSANT_note> chord_notes = *(*chord);
//                    
//                    //only insert if there is a dyad present
//                    if (chord_notes[i]->getType()!=IMUSANT_NoteType::rest && chord_notes[j]->getType()!=IMUSANT_NoteType::rest)
//                    {
//                        IMUSANT_interval interval(chord_notes[j]->pitch(), chord_notes[i]->pitch());
//                        
//                        
//                        //only insert interval if not a repeated interval
//                        if (
//                            !(chord_notes[i]->isTiedPrevious() && chord_notes[j]->isTiedPrevious()) &&
//                            !((interval.getQuality()==IMUSANT_interval::dissonant) && (fIgnoreDissonances==true))
//                            )
//                        {
//                            fVIntervalVectors[dyad_pair]->add(interval);
//                        }
//                    }
//                    dyad_pair++; //complete iteration through one pair of voices
//                }
//                
//            }
//            
//            fSaveI = dyad_pair;
        }
    }

}
