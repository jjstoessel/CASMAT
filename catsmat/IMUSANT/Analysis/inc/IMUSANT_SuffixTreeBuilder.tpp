//
//  IMUSANT_SuffixTreeBuilder.cpp
//  catsmat
//
//  Created by Jason Stoessel on 7/03/2017.
//
//

#include <stdio.h>
#include <utility>
#include "repeats.h"
#include "boost/multi_array.hpp"

#include "IMUSANT_SuffixTreeBuilder.h"

namespace IMUSANT
{

    //#include "IMUSANT_SuffixTreeBuilder.h"
    
    //explicit instantiations of classes
    
    //IMUSANT_SuffixTreeBuilder<IMUSANT_interval, IMUSANT_processing> IMUSANT_SuffixTreeBuilder;
    
    /*!
     \brief builds suffix tree from a map of vectors with unique ID
     
     */
    //template<typename T, class C>
    suffixtree< vector<T> >*
    IMUSANT_SuffixTreeBuilder<T,C>::
    buildSuffixTree(const map<int, vector<T> >& id_vec_map)
    {
        //get first part from first file
        suffixtree< vector<T> >* tree = NULL;
        
        for (auto i = id_vec_map.begin(); i!=id_vec_map.end(); i++)
        {
            
            if (tree==NULL) {
                tree=new suffixtree< vector<T> >(i->second, i->first);
            }
            else
                tree->add_sentence(i->second, i->first);
        }
        
        return tree;
    }
    
    template<typename T, class C>
    typename IMUSANT_SuffixTreeBuilder<T,C>::SUBSTR_VECTOR
    IMUSANT_SuffixTreeBuilder<T,C>::
    FindRepeatedSubstrings(int min_length) const
    {
        SUBSTR_VECTOR ret_val;
        
        //tree and ID_map must be built beforehand in a visit event
        if (tree_ptr_==NULL || id_vec_map_.size()==0)  // No files have been added...
        {
            return ret_val;
        }
        
#ifdef VERBOSE
        tree_ptr_->print(cout);
#endif
        vector< pair<vector<typename _tree::number>, int> > common_substrings_indexes;
        
        //get IDS from map of sentences
        vector<int> ids;
        map< int,typename _tree::value_type> sentences = tree_ptr_->get_sentences(); //rather than call id_vec_map_;
        for (auto ivm = sentences.begin(); ivm != sentences.end(); ivm++) {
            ids.push_back(ivm->first);
        }
        
        //find all repeats for each ID
        common_substrings_indexes = tree_ptr_->find_common_subsequences(ids, min_length);
        
        //iterate through substring indices results
        for (auto csi = common_substrings_indexes.begin();
             csi != common_substrings_indexes.end();
             csi++)
        {
            IMUSANT_t_repeated_substring<T> repeat;
            bool sequence_added = false;
            
            //iterate through substring using indices
            for (auto csii = csi->first.begin(); csii != csi->first.end(); csii++)
            {
                vector<T> tt = sentences[csii->first]; // rather than id_vec_map_.at(csii->first);
                
                if (! sequence_added)
                {
                    // Add the interval sequence into the return value.
                    for ( typename _tree::size_type t = csii->second;
                         t < csii->second + csi->second;
                         t++)
                    {
                        repeat.sequence.push_back(tt[t]);
                    }
                    
                    sequence_added = true;
                }
                
                // Add the loction of this repetition of the interval sequence into the return value.
                IMUSANT_range range = CalcRange(tt[csii->second]);
                repeat.add_occurrence(csii->first, range.first.partID, range.first.measure, range.first.note_index );
                
            }
            
            ret_val.push_back(repeat);
        }
        
        return ret_val;
    }
    
    template<typename T, class C>
     typename IMUSANT_SuffixTreeBuilder<T,C>::SUBSTR_VECTOR
     IMUSANT_SuffixTreeBuilder<T,C>::
     FindSupermaximals(int min_length, int min_percent)
     {
     SUBSTR_VECTOR ret_val;
     
                 if (tree_ptr_!=NULL)
                 {
                     repeats<vector<T> > rep(tree_ptr_);
     
                     list<typename repeats<vector<T> >::supermax_node*> supermaxs = rep.supermax_find(min_percent, min_length);
     
                     //list<typename repeats<vector<T> >::supermax_node*>::const_iterator
                     for (auto q=supermaxs.begin(); q!=supermaxs.end(); q++)
                     {
                         IMUSANT_t_repeated_substring<T> maxy;
     
                         for (typename repeats<vector<T> >::index t = (*q)->begin_i; t!=(*q)->end_i; t++)
                         {
                             maxy.sequence.push_back(*t);
                         }
     
                         //cout << "Witnesses: " << (*q)->num_witness << " number of leaves: " << (*q)->num_leaves << " Percent: " << (*q)->percent << endl;
     
                         //this is a dumb interim solution by JS at the moment.
                         maxy.add_occurrence( 0, (*q)->num_witness, (*q)->num_leaves, (*q)->percent );
     
                         ret_val.push_back(maxy);
                     }
                 }
                 
     return ret_val;
     }

} // namespace IMUSANT

