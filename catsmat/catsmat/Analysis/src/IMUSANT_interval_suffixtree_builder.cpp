/**
    \class      IMUSANT_IntervalSuffixTreeBuilder
    \file       IMUSANT_IntervalSuffixTreeBuilder.cpp
    \namespace  imusant
    \date       Created by Jason Stoessel on 12/06/2016.
    \author     Jason Stoessel
    \copyright  [add licence name]
    \brief      A class for processing IMUSANT_scores into a suffix tree
    
    IMUSANT_IntervalSuffixTreeBuilder is visitable by IMUSANT_processing. Visit builds a tree contain all interval strings contained in collections held by IMUSANT_processing. This tree is stored in memory and interogated by function calls:
      • findAndPrintRepeatedIntervalSubstrings - calls the following, but returns string rather than vector of vectors
      • findRepeatedIntervalSubstrings - returns from mTreePtr a vector of vector of intervals of repeated "strings" of
          intervals.
      • findSupermaximalsIntervals - find maximal repeats that are not substrings of any other maximal repeats
    mTreePtr belongs to the base class, and is destroyed in this classes destructor.
*/

#include <utility>
#include "boost/multi_array.hpp"
#include "IMUSANT_interval_suffixtree_builder.h"
#include "repeats.h"



using namespace std;

namespace IMUSANT {

    IMUSANT_IntervalSuffixTreeBuilder::
    IMUSANT_IntervalSuffixTreeBuilder()
    {
    }
    
    void
    IMUSANT_IntervalSuffixTreeBuilder::
    Visit(const IMUSANT_processing& processing)
    {
        IMUSANT_processing::COLLECTIONMAP collections = processing.getCollections();
        
        BuildVectorMap(collections);
        
        tree_ptr_ = buildSuffixTree(id_vec_map_);
    }
    
    //Prepare list of interval strings and feed to template class to create actual tree
    void
    IMUSANT_IntervalSuffixTreeBuilder::
    BuildVectorMap(IMUSANT_processing::COLLECTIONMAP& collections)
    {
        //get first part from first file
        int ID = 0;
        
        for (auto i = collections.begin(); i!=collections.end(); i++)
        {
            IMUSANT_collection_visitor collection = i->second;
            for (auto j = collection.getPartwiseIntervalVectors().begin(); j!=collection.getPartwiseIntervalVectors().end(); j++)
            {
                ++ID;
                id_vec_map_[ID] = (*j)->getIntervals();
            }
        }
    }
    
    
    IMUSANT_range
    IMUSANT_IntervalSuffixTreeBuilder::
    CalcRange(IMUSANT_interval& interval) const
    {
        return interval.getLocation();
    }
    
    /*string
    IMUSANT_IntervalSuffixTreeBuilder::
    findAndPrintLcsPairsIntervals(bool consecutive, bool reverse_search, bool retrograde)
    {
        SUBSTR_VECTOR the_result;
        the_result = findLcsPairsIntervals(consecutive,reverse_search,retrograde);
        
        stringstream the_result_as_stringstream;
        for(int index = 0 ; index < the_result.size(); index++)
        {
            the_result_as_stringstream << the_result[index];
        }
        
        the_result_as_stringstream << endl;
        
        return the_result_as_stringstream.str();
    }*/
    
}
