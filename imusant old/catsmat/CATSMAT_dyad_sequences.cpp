//
//  CATSMAT_dyad_sequences.cpp
//  imusant
//
//  Created by Jason Stoessel on 12/06/2015.
//
//

#include "CATSMAT_dyad_sequences.hpp"
#include "IMUSANT_chord.h"

namespace CATSMAT
{
    
CATSMAT_dyad_sequences::CATSMAT_dyad_sequences(bool ignoreRepeatedDyads)
    : CATSMAT_dyad_sequences_base(ignoreRepeatedDyads)
{
    
}
    
CATSMAT_dyad_sequences::~CATSMAT_dyad_sequences()
{

}

void    CATSMAT_dyad_sequences::Visit(const CATSMAT_cp_matrix& matrix)
{
    //increase VectorInterval colection according to the formula of unique pairs n(n-1)/2
    unsigned long partCount = matrix.partCount();
    
    while (fVIntervalVector.size() < ( (partCount+1)*partCount/2 ) )
    {
        S_IMUSANT_interval_vector newIV = new_IMUSANT_interval_vector();
        newIV->setMaximum(1024);
        fVIntervalVector.push_back(newIV);
    }

    process(matrix.getCPmatrix());
}


/*   
 \brief CATSMAT_dyad_sequences::process
    
    Takes a list of chords (from CPMatrix)
    1. calculates all vertical intervals between voices
    
*/
    
void    CATSMAT_dyad_sequences::process(const list<S_IMUSANT_chord>& matrix)
{
    if (!matrix.empty())
    {
        for (auto chord = matrix.begin(); chord!=matrix.end(); chord++)
        {
            long i = 0;
            
            for (IMUSANT_vector<S_IMUSANT_note>::const_iterator note1 = (*chord)->getNotes().begin();
                 note1 != (*chord)->getNotes().end();
                 note1++)
            {
                
                
                for ( IMUSANT_vector<S_IMUSANT_note>::const_iterator note2 = note1;
                     ++note2 != (*chord)->getNotes().end(); /*nothing here!*/)
                {
                    //an interval is between two notes!
                    if ((*note1)->getType()!=IMUSANT_NoteType::rest && (*note2)->getType()!=IMUSANT_NoteType::rest )
                    {
                        IMUSANT_interval interval((*note2)->pitch(), (*note1)->pitch());
                        
                        interval.setLocation(i, (*note2)->getMeasureNum(), (*note2)->getNoteIndex(), (*note1)->getMeasureNum(), (*note1)->getNoteIndex());
                        
                        fVIntervalVector[i]->add(interval);
                    }
                    
                    i++;
                }
            }
            
            fSaveI = i;
        }
    }

}
    
void    CATSMAT_dyad_sequences::print(ostream& os) const
{
    for (vector<S_IMUSANT_interval_vector>::const_iterator iter = fVIntervalVector.begin();
         iter != fVIntervalVector.end() && (*iter) != NULL; iter++)
    {
        cout << "dyadic pair" << endl;
        cout << *iter;
    }
}

}//namespace CATSMAT