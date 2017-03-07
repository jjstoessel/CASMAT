//
//  IMUSANT_SuffixTreeBuilder.h
//  Base class for suffix-tree based processors of IMUSANT collections
//
//  Created by Jason Stoessel on 12/06/2016.
//
//  Changes:
//  26 Feb 2017     templatised (virtual) visitor class for additional flexibility;
//
//  To do: refactor to class name IMUSANT_suffix_tree_builder to be
//

#ifndef ____IMUSANT_SuffixTreeBuilder__
#define ____IMUSANT_SuffixTreeBuilder__

#include <stdio.h>
#include "boost/multi_array.hpp"
#include "Loki/Visitor.h"
#include "suffixtree.h"
#include "IMUSANT_processing.h"
#include "IMUSANT_t_repeated_substring.h"

using namespace std;
using namespace ns_suffixtree;

#define MAX(X,Y) ( (X>Y)? (X) : (Y) ) //move to general macros header
//#define VERBOSE

namespace IMUSANT
{
    template <typename T, class C> //T is type for tree; C is the visited class that provides vectors of T
    class IMUSANT_SuffixTreeBuilder :
        public Loki::BaseVisitor,
        public Loki::Visitor<C, void, true>
    {
    public:
        typedef vector<IMUSANT_t_repeated_substring<T> > SUBSTR_VECTOR;
        typedef suffixtree< vector<T> >  _tree;
        typedef typename _tree::number number;
        typedef map<int, vector<T> > ID_vec_map;
        
        IMUSANT_SuffixTreeBuilder() : tree_ptr_(NULL) {}
        ~IMUSANT_SuffixTreeBuilder() { if (tree_ptr_!=NULL) delete tree_ptr_; }

        virtual void    Visit(const C&) = 0;
        SUBSTR_VECTOR   FindRepeatedSubstrings(int min_length=4) const;
        
    protected:
        virtual void    BuildVectorMap(map<S_IMUSANT_score,IMUSANT_collection_visitor>&) = 0;
        virtual IMUSANT_range CalcRange(T&) const = 0; //called in FindRepeatedIntervalSubstrings
        
        suffixtree< vector<T> >* buildSuffixTree(const map<int, vector<T> >& id_vec_map);
        
        _tree*          tree_ptr_ = NULL;
        ID_vec_map      id_vec_map_;
    };
    
    typedef boost::multi_array<int, 2> int_2d_array_t;
    
    /*!
       \brief builds suffix tree from a map of vectors with unique ID
     
     */
    template<typename T, class C>
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
}
#endif /* defined(____IMUSANT_SuffixTreeBuilder__) */
