//
//  TSuffixTreeBuilder.h
//  Base class for suffix-tree based processors of IMUSANT collections
//
//  Created by Jason Stoessel on 12/06/2016.
//
//  Changes:
//  26 Feb 2017     templatised (virtual) visitor class for additional flexibility;
//
//  To do: refactor to class name IMUSANT_suffix_tree_builder to be
//

#ifndef ____TSuffixTreeBuilder__
#define ____TSuffixTreeBuilder__

#include <stdio.h>
#include "boost/multi_array.hpp"
#include "Loki/Visitor.h"
#include "suffixtree.h"


#include "libIMUSANT.h"
#include "TRepeatedSubstring.h"
#include "TVectorMap.h"
#include "repeats.h"

using namespace std;
using namespace ns_suffixtree;
using namespace Loki;

//#define VERBOSE

#define NEW_REPEATS

namespace CATSMAT
{
    template <typename T, class C> //T is type for tree; C is the visited class that provides vectors of T
    class TSuffixTreeBuilder :
        public TVectorMap<T,C> //is visitor
    {
    public:
        typedef typename TRepeatedSubstring<T>::SUBSTR_VECTOR SUBSTR_VECTOR;
        typedef suffixtree< vector<T> >     stree;
        typedef typename stree::number      number;
        
        TSuffixTreeBuilder() {}
        ~TSuffixTreeBuilder() {}

        string          FindAndPrintRepeatedSubstrings(int min_length=4);
        string          FindAndPrintSupermaximals(int min_length=4, int min_percent=25);
        SUBSTR_VECTOR   FindRepeatedSubstrings(int min_length=4);
        SUBSTR_VECTOR   FindSupermaximals(int min_length=4, int min_percent=25);
    protected:
        virtual void    BuildVectorMap(map<S_IMUSANT_score,IMUSANT_collection_visitor>&) = 0;
        virtual IMUSANT_range CalcRange(T&) const = 0; //called in FindRepeatedSubstrings
        
        suffixtree< vector<T> >* buildSuffixTree(const map<int, vector<T> >& id_vec_map);
        suffixtree< vector<T> >* buildSuffixTree(const vector<T>& v1, const vector<T>& v2, int id1, int id2);

    };
    
    /*!
       \brief builds suffix tree from a map of vectors with unique ID
     
     */
    template<typename T, class C>
    suffixtree< vector<T> >*
    TSuffixTreeBuilder<T,C>::
    buildSuffixTree(const map<int, vector<T> >& id_vec_map)
    {
        //get first part from first file
        stree* tree = NULL;
        
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

    /*!
     * \brief builds suffix tree from two vectors with supplied IDS
     */
    template <typename T, typename C>
    suffixtree< vector<T> >*
    TSuffixTreeBuilder<T,C>::
    buildSuffixTree(const vector<T>& v1, const vector<T>& v2, int id1, int id2)
    {
        stree* tree = NULL;

        if (v1.empty() || v2.empty() || id1==id2) return tree;

        tree = new suffixtree<vector<T> > (v1, id1);
        tree->add_sentence(v2, id2);

        return tree;
    }


    template<typename T, class C>
    string
    TSuffixTreeBuilder<T,C>::
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
    TSuffixTreeBuilder<T,C>::
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

#ifdef NEW_REPEATS
    template<typename T, class C>
    typename TSuffixTreeBuilder<T,C>::SUBSTR_VECTOR
    TSuffixTreeBuilder<T,C>::
    FindRepeatedSubstrings(int min_length) {
        SUBSTR_VECTOR repeated_substrings;

        suffixtree< vector<T> >* tree = NULL;

        for (auto i = this->id_vec_map_.begin(); i!=this->id_vec_map_.end(); i++) //this-> for accessing inherited member variable
        {
            for (auto j = std::next(i); j!=this->id_vec_map_.end();j++)
            {
                tree = buildSuffixTree(i->second, j->second, i->first, j->first);

                if (tree)
                {
#ifdef VERBOSE
                    tree->print(cout);
#endif
                    vector< pair<vector<typename stree::number>, int> > common_substrings_indexes;
                    vector<int> ids;
                    ids.push_back(i->first);
                    ids.push_back(j->first);
                    //find all repeats for each ID
                    common_substrings_indexes = tree->find_common_subsequences(ids, min_length);

                    //iterate through substring indices results
                    for (auto csi = common_substrings_indexes.begin();
                         csi != common_substrings_indexes.end();
                         csi++) {
                        TRepeatedSubstring<T> repeat;
                        bool sequence_added = false;

                        //iterate through substring using indices
                        for (auto csii = csi->first.begin(); csii != csi->first.end(); csii++) {
                            vector<T> tt = this->id_vec_map_.at(csii->first);

                            if (!sequence_added) {
                                // Add the interval sequence into the return value.
                                for (typename stree::size_type t = csii->second;
                                     t < csii->second + csi->second;
                                     t++) {
                                    repeat.sequence.push_back(tt[t]);
                                }

                                sequence_added = true;
                            }

                            // Add the loction of this repetition of the interval sequence into the return value.
                            IMUSANT_range range = CalcRange(tt[csii->second]);
                            repeat.add_occurrence(csii->first, range.first.partID, range.first.measure,
                                                  range.first.note_index);
                        }

                        repeated_substrings.push_back(repeat);

                    }
                }
                delete tree;
            }
        }

        return repeated_substrings;
    }
#else
    template<typename T, class C>
    typename TSuffixTreeBuilder<T,C>::SUBSTR_VECTOR
    TSuffixTreeBuilder<T,C>::
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
            TRepeatedSubstring<T> repeat;
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
#endif
    
    template<typename T, class C>
    typename TSuffixTreeBuilder<T,C>::SUBSTR_VECTOR
    TSuffixTreeBuilder<T,C>::
    FindSupermaximals(int min_length, int min_percent)
    {
        SUBSTR_VECTOR ret_val;
        stree*        tree_ptr_;

        if (tree_ptr_!=NULL)
        {
            repeats<vector<T> > rep(tree_ptr_);
            
            list<typename repeats<vector<T> >::supermax_node*> supermaxs = rep.supermax_find(min_percent, min_length);
            
            //list<typename repeats<vector<T> >::supermax_node*>::const_iterator
            for (auto q=supermaxs.begin(); q!=supermaxs.end(); q++)
            {
                TRepeatedSubstring<T> maxy;
                
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
#endif /* defined(____TSuffixTreeBuilder__) */
