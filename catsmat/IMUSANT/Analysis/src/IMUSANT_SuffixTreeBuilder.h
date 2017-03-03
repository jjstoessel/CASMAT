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
        
        IMUSANT_SuffixTreeBuilder() : mTreePtr(NULL) {}
        ~IMUSANT_SuffixTreeBuilder() { if (mTreePtr!=NULL) delete mTreePtr; }

        virtual void    Visit(const C&) = 0;
        SUBSTR_VECTOR   FindRepeatedIntervalSubstrings(int min_length) const;
        
    protected:
        virtual void  BuildVectorMap(map<S_IMUSANT_score,IMUSANT_collection_visitor>&) = 0;
        
        suffixtree< vector<T> >* buildSuffixTree(const map<int, vector<T> >& id_vec_map);
        
        _tree*       mTreePtr;
        ID_vec_map   mID_vec_map;
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
    FindRepeatedIntervalSubstrings(int min_length) const
    {
        SUBSTR_VECTOR ret_val;
        
        //tree and ID_map must be built beforehand in a visit event
        if (mTreePtr==NULL || mID_vec_map.size()==0)  // No files have been added...
        {
            return ret_val;
        }
        
#ifdef VERBOSE
        mTreePtr->print(cout);
#endif
        vector< pair<vector<typename _tree::number>, int> > common_substrings;
        
        //get IDS from map of ID to each interval_vector
        vector<int> local_ids;
        for (auto ivm = mID_vec_map.begin(); ivm != mID_vec_map.end(); ivm++) {
            local_ids.push_back(ivm->first);
        }
        //iterate tree for each ID
        common_substrings = mTreePtr->find_common_subsequences(local_ids, min_length);
    
        //iterate through substring results
        for (auto common_substrings_iter = common_substrings.begin();
             common_substrings_iter != common_substrings.end();
             common_substrings_iter++)
        {
            IMUSANT_t_repeated_substring<T> repeated_substring;
            bool int_sequence_added_to_ret_value = false;
            
            //iterate through substring
            for (auto substring_iter = common_substrings_iter->first.begin();
                 substring_iter != common_substrings_iter->first.end();
                 substring_iter++)
            {
                vector<T> tt = mID_vec_map.at(substring_iter->first); //rather than: vector<T> tt = mID_vec_map[substring_iter->first];
                if (! int_sequence_added_to_ret_value)
                {
                    // Add the interval sequence into the return value.
                    for ( typename _tree::size_type t = substring_iter->second;
                         t < substring_iter->second + common_substrings_iter->second;
                         t++)
                    {
                        repeated_substring.sequence.push_back(tt[t]);
                    }
                    
                    int_sequence_added_to_ret_value = true;
                }
                
                // Add the loction of this repetition of the interval sequence into the return value.
                //IMUSANT_interval interval = intervals[substring_iter->second];
                //IMUSANT_range range = interval.getLocation();
                //repeated_substring.add_occurrence(substring_iter->first, range.first.partID, range.first.measure, range.first.note_index );
                
            }
            
            ret_val.push_back(repeated_substring);
        }
        
        return ret_val;
    }
}
#endif /* defined(____IMUSANT_SuffixTreeBuilder__) */
