
//
//  IMUSANT_GeneralisedIntervalSuffixTreeBuilder.cpp
//
//  Created by Jason Stoessel on 28/11/2016.
//


#include <utility>
#include "boost/multi_array.hpp"
#include "IMUSANT_generalised_interval_suffixtree_builder.h"
#include "repeats.h"



using namespace std;

namespace CATSMAT {

    IMUSANT_GeneralisedIntervalSuffixTreeBuilder
    ::IMUSANT_GeneralisedIntervalSuffixTreeBuilder()
    {
    }
    
    void
    IMUSANT_GeneralisedIntervalSuffixTreeBuilder
    ::Visit(const IMUSANT_processing& processing)
    {
        IMUSANT_processing::COLLECTIONMAP collections = processing.getCollections();
        
        BuildVectorMap(collections);
        
        tree_ptr_ = buildSuffixTree(id_vec_map_); //= buildIntervalSuffixTree(collections);
    }
    
    //Prepare list of interval strings and feed to template class to create actual tree
    void
    IMUSANT_GeneralisedIntervalSuffixTreeBuilder::
    BuildVectorMap(IMUSANT_processing::COLLECTIONMAP& collections)
    {
        int ID = 0;
        
        for (auto i = collections.begin(); i!=collections.end(); i++)
        {
            IMUSANT_collection_visitor collection = i->second;
            for (auto j = collection.getPartwiseIntervalVectors().begin(); j!=collection.getPartwiseIntervalVectors().end(); j++)
            {
                ++ID;
                id_vec_map_[ID] = reinterpret_cast<vector<IMUSANT_generalised_interval> const& >((*j)->getIntervals()); //UNSAFE!!!
                
            }
        }
    }
    
    
    /*string
    IMUSANT_GeneralisedIntervalSuffixTreeBuilder::findAndPrintLcsPairsIntervals(bool consecutive, bool reverse_search, bool retrograde)
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
    }
    
    // Find longest common subsequence of intervals for pairs of file/works
    // This example of dynamic programming is adapted from Crochemore and Lecroq,
    // Pattern MAtching and text compression algorithms, available from:
    // http://www-igm.univ-mlv.fr/~mac/REC/DOC/03-CRC.ps
    IMUSANT_GeneralisedIntervalSuffixTreeBuilder::SUBSTR_VECTOR
    IMUSANT_GeneralisedIntervalSuffixTreeBuilder::
    findLcsPairsIntervals(bool consecutive, bool reverse_search, bool retrograde)
    {
        SUBSTR_VECTOR ret_val;
        
        //if (mID_vec_map.size()==0) return ret_val;
        
        for (auto i = id_vec_map_.begin(); i!=id_vec_map_.end(); i++)
        {
            vector<IMUSANT_generalised_interval> x = i->second;
            if (reverse_search) {
                x.pop_back();
                reverse(x.begin(),x.end());
                retrograde = true; //switch for double reverse search
            }
            vector<IMUSANT_interval>::size_type m = x.size();
            auto j = i;
            for ( j++ ; j!=id_vec_map_.end(); j++) //will bail if only one element
            {
                
                vector<IMUSANT_generalised_interval> y = j->second;
                if (retrograde) {
                    y.pop_back();
                    reverse(y.begin(), y.end());
                }
                int a = 0, b = 0;
                vector<IMUSANT_interval>::size_type n = y.size();
                int_2d_array_t lcs(boost::extents[m][n]); //ints auto zeroed
                
                
                for (; a < m-1; a++)
                {
                    for (b=0; b<n-1; b++)
                    {
                        if (x[a]==y[b])
                        {
                            lcs[a+1][b+1]=lcs[a][b]+1;
                        }
                        else
                        {
                            lcs[a+1][b+1]=MAX(lcs[a+1][b],lcs[a][b+1]);
                        }
                    }
                }
                
                //now trace back to find lcs
                int limit_a = 0, limit_b = 0;
                if (reverse_search) limit_a = 1;
                if (retrograde) limit_b = 1;
                
                deque<pair<IMUSANT_generalised_interval,IMUSANT_generalised_interval> > z;
                while (a > limit_a && b > limit_b )
                {
                    if(lcs[a][b]==lcs[a-1][b-1]+1 && x[a-1]==y[b-1])
                    {
                        pair<IMUSANT_generalised_interval,IMUSANT_generalised_interval> p(x[a-1],y[b-1]);
                        z.push_front(p);
                        a--; b--;
                    }
                    else if (lcs[a-1][b] > lcs[a][b-1]) a--;
                    else b--;
                }
                
                IMUSANT_repeated_generalised_interval_substring repeated_interval_substring;
                bool first_loc_set = false;
                //cout << "Common subsequence: " << endl;
                for (deque<pair<IMUSANT_generalised_interval,IMUSANT_generalised_interval> >::iterator iv=z.begin(); iv!=z.end(); iv++)
                {
                    IMUSANT_range loc1 = iv->first.getLocation();
                    IMUSANT_range loc2 = iv->second.getLocation();
                    if (consecutive)
                    {
                        if (iv+1!=z.end())
                        {
                            repeated_interval_substring.sequence.push_back(iv->first);
                            if (!first_loc_set)
                            {
                                repeated_interval_substring.add_occurrence(i->first,
                                                                           loc1.first.partID,
                                                                           loc1.first.measure,
                                                                           loc1.first.note_index );
                                repeated_interval_substring.add_occurrence(j->first,
                                                                           loc2.first.partID,
                                                                           loc2.first.measure,
                                                                           loc2.first.note_index );
                                first_loc_set = true;
                            }
                        }
                    }
                    else
                    {
                        repeated_interval_substring.sequence.push_back(iv->first);
                        if (!first_loc_set)
                        {
                            repeated_interval_substring.add_occurrence(i->first,
                                                                       loc1.first.partID,
                                                                       loc1.first.measure,
                                                                       loc1.first.note_index );
                            repeated_interval_substring.add_occurrence(j->first,
                                                                       loc2.first.partID,
                                                                       loc2.first.measure,
                                                                       loc2.first.note_index );
                            first_loc_set = true;
                        }
                    }
                }
                ret_val.push_back(repeated_interval_substring);
            }
        }
        return ret_val;
    }*/
    
    IMUSANT_range
    IMUSANT_GeneralisedIntervalSuffixTreeBuilder::
    CalcRange(IMUSANT_generalised_interval& interval) const
    {
        return interval.getLocation();
    }

}
