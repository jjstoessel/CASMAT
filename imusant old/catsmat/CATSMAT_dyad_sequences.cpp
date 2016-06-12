//
//  CATSMAT_dyad_sequences.cpp
//  imusant
//
//  Created by Jason Stoessel on 12/06/2015.
//
//

#include "CATSMAT_dyad_sequences.hpp"
#include "IMUSANT_chord.h"


using namespace ns_suffixtree;

namespace CATSMAT
{
    
    CATSMAT_dyad_sequences::CATSMAT_dyad_sequences(bool ignoreRepeatedDyads)
    : CATSMAT_dyad_sequences_base(ignoreRepeatedDyads)
    {
        
    }
    
    CATSMAT_dyad_sequences::~CATSMAT_dyad_sequences()
    {
        
    }
    
    void
    CATSMAT_dyad_sequences::Visit(const CATSMAT_cp_matrix& matrix)
    {
        //increase VectorInterval colection according to the formula of unique pairs n(n-1)/2
        unsigned long partCount = matrix.partCount();
        
        while (fVIntervalVector.size() < ( (partCount)*(partCount-1)/2 ) )
        {
            fVIntervalVector.push_back(new_IMUSANT_interval_vector());
            fVIntervalVector.back()->setMaximum(1024);
        }
        
        process(matrix.getCPmatrix());
    }
    
    
    /*
     \brief CATSMAT_dyad_sequences::process
     
     Takes a list of chords (from CPMatrix)
     1. calculates all vertical intervals between voices
     
     */
    
    void
    CATSMAT_dyad_sequences::process(const list<S_CATSMAT_chord>& matrix)
    {
        if (!matrix.empty())
        {
#ifdef OLD
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
                        // cout << "Note 1: " << (*note1);
                        // cout << "Note 2: " << (*note2);
                        
                        //an interval is between two notes!
                        if ((*note1)->getType()!=IMUSANT_NoteType::rest && (*note2)->getType()!=IMUSANT_NoteType::rest )
                        {
                            IMUSANT_interval interval((*note2)->pitch(), (*note1)->pitch());
                            
                            // cout << "Interval: " << interval << std::endl;
                            
                            interval.setLocation(i,
                                                 (*note2)->getMeasureNum(),
                                                 (*note2)->getNoteIndex(),
                                                 (*note1)->getMeasureNum(),
                                                 (*note1)->getNoteIndex());
                            
                            //only insert interval if not a repeated interval
                            if (!((*note1)->isTiedPrevious() && (*note2)->isTiedPrevious())
                                &&
                                (interval.getQuality()!=IMUSANT_interval::dissonant))
                            {
                                fVIntervalVector[i]->add(interval);
                            }
                        }

                        i++;
                    }

                }
            
                fSaveI = i;
            }
#elif defined (NEW) //map structure implementation
            for (auto chord = matrix.begin(); chord!=matrix.end(); chord++) {
                map<int, S_IMUSANT_note>::size_type chord_size = (*(*chord)).size();
                
                int dyad_pair = 0;
                
                for (int i = 0; i<chord_size; i++)
                {
                    for (int j=i; ++j<chord_size; /*nothing here*/)
                    {
                        map<int, S_IMUSANT_note> chord_notes = *(*chord);
                        if (chord_notes[i]->getType()!=IMUSANT_NoteType::rest && chord_notes[j]->getType()!=IMUSANT_NoteType::rest)
                        {
                            IMUSANT_interval interval(chord_notes[j]->pitch(), chord_notes[i]->pitch());
                            
                            // cout << "Interval: " << interval << std::endl;
                            
                            interval.setLocation(i,
                                                 chord_notes[j]->getMeasureNum(),
                                                 chord_notes[j]->getNoteIndex(),
                                                 chord_notes[i]->getMeasureNum(),
                                                 chord_notes[i]->getNoteIndex());
                            
                            //only insert interval if not a repeated interval
                            if (!(chord_notes[i]->isTiedPrevious() && chord_notes[j]->isTiedPrevious())
                                &&
                                (interval.getQuality()!=IMUSANT_interval::dissonant))
                            {
                                fVIntervalVector[dyad_pair]->add(interval);
                            }
                        }
                        dyad_pair++;
                    }
                }
                
                fSaveI = dyad_pair;
            }
#endif
           
        }
    }
    
    
    void
    CATSMAT_dyad_sequences::find_repeated(int min)
    {
        if (fVIntervalVector.size()>0)
        {
            for (auto i = fVIntervalVector.begin(); i!=fVIntervalVector.end(); i++)
            {
                interval_tree* tree = new interval_tree((*i)->getIntervals(),1); //change last parameter to id for whole work tree.
                //cout << *tree;
                vector<pair<interval_tree::size_type, interval_tree::size_type> >* results = new vector<pair<interval_tree::size_type, interval_tree::size_type> >();
                find_repeated_substrings(*results, tree->root_node(), min);
                
                map<int, interval_tree::value_type > m = tree->get_sentences(); //const vector<IMUSANT_interval>& int_v = (*i)->getIntervals();
                interval_tree::value_type int_v = m[1];
                
                cout << "duet: " << int_v[0].getLocation().partID << endl;
                
                for (auto j=results->begin(); j!=results->end(); j++)
                {
                    cout << "Sequence: (";
                    
                    cout << int_v[j->first].getLocation().first.measure;
                    cout << ", " << int_v[j->first].getLocation().first.note_index << ") ";
                    
                    for (auto k = j->first; k<j->second+j->first; k++)
                    {
                        cout << int_v[k];
                    }
                    cout << endl;
                }
                
                delete results;
                delete tree;
            }
        }
    }
    
    //private recursive function - needs to be templated
    void
    CATSMAT_dyad_sequences::find_repeated_substrings(vector< pair<interval_tree::size_type,
                                                     interval_tree::size_type> >& results,
                                                     const interval_tree::node& n,
                                                     int min_length)
    {
        interval_tree::size_type prefix_length = n.path_label_length() - (n.end() - n.begin());
        
        if (n.children_size()==0)
        {
            if (prefix_length>=min_length)
            {
                pair<interval_tree::size_type, interval_tree::size_type> res;
                res.first=n.give_number().second; //give index of vector where branch starts
                res.second=prefix_length;
                results.push_back(res);
            }
        }
        
        vector<interval_tree::element_type> v = n.next_children();
        
        if (!v.empty())
        {
            for (vector<interval_tree::element_type>::const_iterator it=v.begin();it!=v.end();it++)
            {
                const interval_tree::node* m = n.find_child(*it);
                find_repeated_substrings(results, *m, min_length);
            }
        }
    }
    
    void
    CATSMAT_dyad_sequences::print(ostream& os) const
    {
        for (vector<S_IMUSANT_interval_vector>::const_iterator iter = fVIntervalVector.begin();
             iter != fVIntervalVector.end() && (*iter) != NULL;
             iter++)
        {
            os << "dyadic pair: " << *iter << endl;
        }
    }
    
} //namespace CATSMAT