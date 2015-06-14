//
//  CATSMAT_dyadtuple_sequences.cpp
//  imusant
//
//  Created by Jason Stoessel on 14/06/2015.
//
//

#include "CATSMAT_dyadtuple_sequences.hpp"
#include "boost/tuple/tuple_io.hpp"

using namespace boost;

namespace CATSMAT
{

void CATSMAT_dyadtuple_sequences::Visit(const CATSMAT_cp_matrix& matrix)
{
    if (!matrix.getCPmatrix().empty())
    {
        unsigned long partCount = matrix.partCount();
        
        for (int i = 0; i<(partCount+1)*partCount/2; i++)
        {
            fTupleVector.push_back(vector<boost::tuple<int,int,int,int> >());
        }

        for (auto chord = matrix.getCPmatrix().begin(), next_chord = std::next(chord); chord!=matrix.getCPmatrix().end() && next_chord!=matrix.getCPmatrix().end(); chord++, next_chord++)
        {
            int i = 0;
            
            auto note1 = (*chord)->getNotes().begin(), note3 = (*next_chord)->getNotes().begin();
            
            for (;
                 note1 != (*chord)->getNotes().end() && note3 != (*next_chord)->getNotes().end();
                 note1++, note3++)
            {
                int vint1 = 0, vint2 = 0, tophint = 0, bottomhint = 0;
                
                if ((*note1)->getType()!=IMUSANT_NoteType::rest || (*note3)->getType()!=IMUSANT_NoteType::rest )
                {
                    IMUSANT_interval topStep((*note1)->pitch(), (*note3)->pitch());
                    tophint = topStep.getNumber();
                    
                    auto note2 = note1, note4 = note3;
                    
                    for (; ++note2 != (*chord)->getNotes().end() && ++note4 != (*next_chord)->getNotes().end(); /*nothing here!*/)
                    {
                        //an interval is between two notes!
                        if ( (*note2)->getType()!=IMUSANT_NoteType::rest && (*note4)->getType()!=IMUSANT_NoteType::rest)
                        {
                            IMUSANT_interval vInterval1((*note2)->pitch(), (*note1)->pitch());
                            IMUSANT_interval vInterval2((*note4)->pitch(), (*note3)->pitch());
                            IMUSANT_interval bottomStep((*note2)->pitch(),(*note4)->pitch());

                            vint1 = vInterval1.getNumber();
                            vint2 = vInterval2.getNumber();
                            bottomhint = bottomStep.getNumber();
                            
                            {
                                boost::tuple<int,int,int,int> dyad_tuple(vint1, vint2, tophint, bottomhint);
                                fTupleVector[i].push_back(dyad_tuple);
                            }
                        }
                        i++;
                    }
                }
                
            }
            
            fSaveI = i;
        }
    }

}
    
void CATSMAT_dyadtuple_sequences::print(ostream& os) const
{
    for (auto iter1 = fTupleVector.begin(); iter1 != fTupleVector.end(); iter1++)
    {
        cout << "dyad tuple pair " << endl;
        
        for (auto iter2 = iter1->begin();
             iter2 != iter1->end(); iter2++)
        {
            cout << *iter2 << " ";
        }
        
        cout << endl;
    }
}

} //namespace CATSMAT