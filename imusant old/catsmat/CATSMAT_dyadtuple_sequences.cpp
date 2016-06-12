//
//  CATSMAT_dyadtuple_sequences.cpp
//  imusant
//
//  Created by Jason Stoessel on 14/06/2015.
//
//

#include <vector>
#include <iostream>
#include "CATSMAT_dyadtuple_sequences.hpp"
#include "boost/tuple/tuple_io.hpp"
#include "suffixtree.h"

using namespace std;
using namespace boost;
using namespace ns_suffixtree;

namespace CATSMAT
{
    /*!
     \brief CATSMAT_dyadtuple_sequences::Visit
     
     A visitor function to iterate through a cp_matrix and extract a quadruple of each dyad
     that includes the two vertical interval formed between each part and the two melodic 
     intervals in both parts.
     
     */
    void
    CATSMAT_dyadtuple_sequences::Visit(const CATSMAT_cp_matrix& matrix)
    {
        if (!matrix.getCPmatrix().empty())
        {
            unsigned long partCount = matrix.partCount();
            
            for (int i = 0; i<(partCount)*(partCount-1)/2; i++)
            {
                fTupleVector.push_back(quadruple_int_vector());
            }
            
            for (auto chord = matrix.getCPmatrix().begin(), next_chord = std::next(chord);
                 chord!=matrix.getCPmatrix().end() && next_chord!=matrix.getCPmatrix().end();
                 chord++, next_chord++)
            {
                int i = 0;
                //  note 1 --- note 3
                //   |          |
                //  note 2 --- note 4
                for (; i<matrix.partCount(); i++)
                {
                    S_IMUSANT_note note_1 = (**chord)[i];
                    S_IMUSANT_note note_3 = (**next_chord)[i];
                    
                    assert(note_1!=NULL && note_3!=NULL);
                    
                    if (note_1->getType()!=IMUSANT_NoteType::rest || note_3->getType()!=IMUSANT_NoteType::rest)
                    {
                        IMUSANT_interval topStep(note_1->pitch(), note_3->pitch());
                        int tophint = topStep.getNumber();
                        
                        for (int j = i+1; j<matrix.partCount(); j++) {
                            S_IMUSANT_note note_2 = (**chord)[j];
                            S_IMUSANT_note note_4 = (**next_chord)[j];
                            
                            assert(note_2!=NULL && note_4!=NULL);
                            
                            if ( note_2->getType()!=IMUSANT_NoteType::rest && note_4->getType()!=IMUSANT_NoteType::rest)
                            {
                                int vint1 = 0, vint2 = 0, bottomhint = 0;
                                
                                IMUSANT_interval vInterval1(note_2->pitch(), note_1->pitch());
                                IMUSANT_interval vInterval2(note_4->pitch(), note_3->pitch());
                                IMUSANT_interval bottomStep(note_2->pitch(), note_4->pitch());
                                
                                vint1 = vInterval1.getNumber();
                                vint2 = vInterval2.getNumber();
                                bottomhint = bottomStep.getNumber();

                                quadruple_int dyad_tuple(vint1, vint2, tophint, bottomhint);
                                fTupleVector[i].push_back(dyad_tuple);                            

                            }
                            
                        }
                    }
                }
                
                fSaveI = i;
            }
        }
        
    }
    
    //void CATSMAT_dyadtuple_sequences::find_repeated_tuplet_sequences(int min)
    //{
    //    if (fTupleVector.size()>0)
    //    {
    //        int id = 0;
    //        vector<int> ids;
    //        ids.push_back(id);
    //
    //        suffixtree<quadruple_int_vector> tuple_tree(*fTupleVector.begin(),id);
    //
    //        for (auto i=fTupleVector.begin(); i!=fTupleVector.end();i++,++id)
    //        {
    //            tuple_tree.add_sentence(*i, id);
    //            ids.push_back(id);
    //        }
    //
    //        vector< pair<vector<suffixtree<quadruple_int_vector>::number>, int> > results;
    //        results = tuple_tree.find_common_subsequences(ids);
    //        vector< pair<vector<suffixtree<quadruple_int_vector>::number>, int> >::iterator j=results.begin();
    //
    //        for (; j!=results.end(); j++)
    //        {
    //            cout << "Sequence:";
    //            vector<suffixtree<quadruple_int_vector>::number>::const_iterator k=j->first.begin();
    //            bool first = true;
    //            for (; k!=j->first.end(); k++) {
    //
    //                first = false;
    //                cout << k->first;
    //
    //            }
    //            cout << endl;
    //            cout << "Length: " << j->second << " Occurrences: " << j->first.size() << endl;
    //        }
    //    }
    //}
    
    void
    CATSMAT_dyadtuple_sequences::find_repeated_tuplet_sequences(int min)
    {
        if (fTupleVector.size()>0)
        {
            int id = 0;
            vector<int> ids;
            ids.push_back(id);
            
            suffixtree<quadruple_int_vector> tuple_tree(*fTupleVector.begin(),id);
            
            cout << tuple_tree;
        }
        
    }
    
    void
    CATSMAT_dyadtuple_sequences::print(ostream& os) const
    {
        for (auto iter1 = fTupleVector.begin(); iter1 != fTupleVector.end(); iter1++)
        {
            os << "dyad tuple pair: ";
            
            for (auto iter2 = iter1->begin();
                 iter2 != iter1->end(); iter2++)
            {
                os << *iter2 << " "; //uses tuple print member function
            }
        }
    }
    
} //namespace CATSMAT