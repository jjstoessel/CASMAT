//
//  IMUSANT_contour_processor.cpp
//  
//
//  Created by Jason James Stoessel on 13/06/2016.
//
//

#include "IMUSANT_contour_processor.h"

namespace IMUSANT {
    
    void
    IMUSANT_contour_processor::Visit(const IMUSANT_processing& processing)
    {
        IMUSANT_processing::COLLECTIONMAP collections = processing.getCollections();
        
        mTreePtr = buildContourSuffixTree(collections);
    }
    
    string
    IMUSANT_contour_processor::
    findAndPrintRepeatedContourSubstrings(int min_length)
    {
        SUBSTR_VECTOR the_result;
        the_result = findRepeatedContourSubstrings(min_length);
        
        stringstream the_result_as_stringstream;
        for(int index = 0 ; index < the_result.size(); index++)
        {
            the_result_as_stringstream << the_result[index];
        }
        
        the_result_as_stringstream << endl;
        
        return the_result_as_stringstream.str();
    }
    
    IMUSANT_contour_processor::SUBSTR_VECTOR
    IMUSANT_contour_processor::
    findRepeatedContourSubstrings(int min_length)
    {
        SUBSTR_VECTOR ret_val;
        
        if (mTreePtr==NULL) {
            return ret_val;
        }
        
        vector<int> local_ids;
        for (auto cvm = mID_vec_map.begin(); cvm != mID_vec_map.end(); cvm++) {
            local_ids.push_back(cvm->first);
        }
        vector< pair<vector<_tree::number>, int> > mc_results;
        mc_results = mTreePtr->find_common_subsequences(local_ids, min_length);
        
        for (auto iter_mc=mc_results.begin();iter_mc!=mc_results.end(); iter_mc++)
        {
            IMUSANT_repeated_contour_substring repeated_contour_substring;
            vector< _tree::number >::const_iterator mc_c=iter_mc->first.begin();
            bool first_time = true;
            for (;mc_c!=iter_mc->first.end(); mc_c++)
            {
                if (first_time)
                {
                    for (_tree::size_type t = mc_c->second; t < mc_c->second+iter_mc->second; t++)
                    {
                        repeated_contour_substring.sequence.push_back(mID_vec_map[mc_c->first][t]);
                    }
                    
                    first_time=false;
                }
                
                IMUSANT_contour_symbol symbol = mID_vec_map[mc_c->first][mc_c->second];
                IMUSANT_range range=symbol.getLocation();
                repeated_contour_substring.add_occurrence( mc_c->first,
                                                          range.first.partID,
                                                          range.first.measure,
                                                          range.first.note_index );
                
            }
            ret_val.push_back(repeated_contour_substring);
        }
        
        return ret_val;
    }
    
    IMUSANT_contour_processor::_tree*
    IMUSANT_contour_processor::
    buildContourSuffixTree(IMUSANT_processing::COLLECTIONMAP& collections)
    {
        //get first part from first file
        _tree* tree = NULL;
        int ID = 0;
        
        for (auto i = collections.begin(); i!=collections.end(); i++)
        {
            IMUSANT_collection_visitor collection = i->second;
            for (auto j = collection.getPartwiseContourVectors().begin(); j!=collection.getPartwiseContourVectors().end(); j++)
            {
                ++ID;
                mID_vec_map[ID] = (*j)->getContours();
            }
        }
        
        tree = buildSuffixTree(mID_vec_map);
        
        return tree;
    }
    
    void
    IMUSANT_contour_processor::
    findSupermaximalsContours(int min_length, int min_percent)
    {
        //        if (IDs.size()>0)
        //        {
        //            contour_tree cont_tree(*(collection_visitors[*IDs.begin()].getMelodicContour()),*IDs.begin());
        //
        //            for (vector<int>::iterator j = IDs.begin()+1; j!=IDs.end(); j++)
        //            {
        //                cont_tree.add_sentence(*(collection_visitors[*j].getMelodicContour()),*j);
        //            }
        //
        //            repeats<vector<IMUSANT_contour_symbol> > rep(&cont_tree);
        //            list<repeats<vector<IMUSANT_contour_symbol> >::supermax_node*> supermaxs = rep.supermax_find(min_percent, min_length);
        //            list<repeats<vector<IMUSANT_contour_symbol> >::supermax_node*>::const_iterator q=supermaxs.begin();
        //            for (; q!=supermaxs.end(); q++)
        //            {
        //                for (repeats<vector<IMUSANT_contour_symbol> >::index t = (*q)->begin_i; t!=(*q)->end_i; t++)
        //                {
        //                    cout << *t;
        //                }
        //                cout << " ";
        //                cout << "Witnesses: " << (*q)->num_witness << " number of leaves: " << (*q)->num_leaves << " Percent: " << (*q)->percent << endl;
        //            }
        //        }
    }

}