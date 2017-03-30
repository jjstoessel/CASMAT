//
//  IMUSANT_T_SuffixTreeBuilder.h
//  Base class for suffix-tree based processors of IMUSANT collections
//
//  Created by Jason Stoessel on 12/06/2016.
//
//  Changes:
//  26 Feb 2017     templatised (virtual) visitor class for additional flexibility;
//
//  To do: refactor to class name IMUSANT_suffix_tree_builder to be
//

#ifndef ____IMUSANT_t_suffixtree_builder__
#define ____IMUSANT_t_suffixtree_builder__

#include <stdio.h>
#include "boost/multi_array.hpp"
#include "Loki/Visitor.h"
#include "suffixtree.h"
#include "IMUSANT_processing.h"
#include "IMUSANT_t_repeated_substring.h"
#include "IMUSANT_t_vectormap.hpp"
#include "repeats.h"

using namespace std;
using namespace ns_suffixtree;

//#define VERBOSE

namespace IMUSANT
{
    template <typename T, class C> //T is type for tree; C is the visited class that provides vectors of T
    class IMUSANT_T_SuffixTreeBuilder :
        public IMUSANT_T_VectorMap<T,C> //is visitor
    {
    public:
        typedef typename IMUSANT_T_RepeatedSubstring<T>::SUBSTR_VECTOR SUBSTR_VECTOR;
        typedef suffixtree< vector<T> >     stree;
        typedef typename stree::number      number;
        
        IMUSANT_T_SuffixTreeBuilder() : tree_ptr_(NULL) {}
        ~IMUSANT_T_SuffixTreeBuilder() { if (tree_ptr_!=NULL) delete tree_ptr_; }

        string          FindAndPrintRepeatedSubstrings(int min_length=4);
        string          FindAndPrintSupermaximals(int min_length=4, int min_percent=25);
        SUBSTR_VECTOR   FindRepeatedSubstrings(int min_length=4) const;
        SUBSTR_VECTOR   FindSupermaximals(int min_length=4, int min_percent=25);
    protected:
        virtual void    BuildVectorMap(map<S_IMUSANT_score,IMUSANT_collection_visitor>&) = 0;
        virtual IMUSANT_range CalcRange(T&) const = 0; //called in FindRepeatedSubstrings
        
        suffixtree< vector<T> >* buildSuffixTree(const map<int, vector<T> >& id_vec_map);
        
        stree*          tree_ptr_ = NULL;
    };
    
    //typedef boost::multi_array<int, 2> int_2d_array_t;
    
    /*!
       \brief builds suffix tree from a map of vectors with unique ID
     
     */
    template<typename T, class C>
    suffixtree< vector<T> >*
    IMUSANT_T_SuffixTreeBuilder<T,C>::
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
    string
    IMUSANT_T_SuffixTreeBuilder<T,C>::
    FindAndPrintRepeatedSubstrings(int min_length)
    {
        SUBSTR_VECTOR the_result;
        the_result = FindRepeatedSubstrings(min_length);
        
        stringstream the_result_as_stringstream;
        for(int index = 0 ; index < the_result.size(); index++)
        {
            the_result_as_stringstream << the_result[index];
        }
        
        the_result_as_stringstream << endl;
        
        return the_result_as_stringstream.str();
    }
    
    template<typename T, class C>
    string
    IMUSANT_T_SuffixTreeBuilder<T,C>::
    FindAndPrintSupermaximals(int min_length, int min_percent)
    {
        SUBSTR_VECTOR the_result;
        the_result = FindSupermaximals(min_length, min_percent);
        
        stringstream the_result_as_stringstream;
        for(int index = 0 ; index < the_result.size(); index++)
        {
            the_result_as_stringstream << the_result[index];
        }
        
        the_result_as_stringstream << endl;
        
        return the_result_as_stringstream.str();
    }


    template<typename T, class C>
    typename IMUSANT_T_SuffixTreeBuilder<T,C>::SUBSTR_VECTOR
    IMUSANT_T_SuffixTreeBuilder<T,C>::
    FindRepeatedSubstrings(int min_length) const
    {
        SUBSTR_VECTOR ret_val;
        
        //tree and ID_map must be built beforehand in a visit event
        if (tree_ptr_==NULL )  // No files have been added...
        {
            return ret_val;
        }
        
#ifdef VERBOSE
        tree_ptr_->print(cout);
#endif
        vector< pair<vector<typename stree::number>, int> > common_substrings_indexes;
        
        //get IDS from map of sentences
        vector<int> ids;
        map< int,typename stree::value_type> sentences = tree_ptr_->get_sentences(); //rather than call id_vec_map_;
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
            IMUSANT_T_RepeatedSubstring<T> repeat;
            bool sequence_added = false;
            
            //iterate through substring using indices
            for (auto csii = csi->first.begin(); csii != csi->first.end(); csii++)
            {
                vector<T> tt = sentences[csii->first]; // rather than id_vec_map_.at(csii->first);
                
                if (! sequence_added)
                {
                    // Add the interval sequence into the return value.
                    for ( typename stree::size_type t = csii->second;
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
    typename IMUSANT_T_SuffixTreeBuilder<T,C>::SUBSTR_VECTOR
    IMUSANT_T_SuffixTreeBuilder<T,C>::
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
                IMUSANT_T_RepeatedSubstring<T> maxy;
                
                for (typename repeats<vector<T> >::index t = (*q)->begin_i; t!=(*q)->end_i; t++)
                {
                    maxy.sequence.push_back(*t);
                }
                
                //cout << "Witnesses: " << (*q)->num_witness << " number of leaves: " << (*q)->num_leaves << " Percent: " << (*q)->percent << endl;
                //IMUSANT_range range = CalcRange((*q)->begin_i);
                //this is a dumb interim solution by JS at the moment.
                maxy.add_occurrence( 0, (*q)->num_witness, (*q)->num_leaves, (*q)->percent );
                //maxy.add_occurrence(0, range.first.partID, range.first.measure, range.first.note_index );
                
                ret_val.push_back(maxy);
            }
        }
        
        return ret_val;
    }
}
#endif /* defined(____IMUSANT_t_suffixtree_builder__) */
