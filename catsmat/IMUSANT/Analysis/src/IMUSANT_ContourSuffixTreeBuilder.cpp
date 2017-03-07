//
//  IMUSANT_contour_processor.cpp
//  
//
//  Created by Jason Stoessel on 13/06/2016.
//
//

#include "IMUSANT_ContourSuffixTreeBuilder.h"
#include "repeats.h"

namespace IMUSANT {
    
    void
    IMUSANT_ContourSuffixTreeBuilder::Visit(const IMUSANT_processing& processing)
    {
        IMUSANT_processing::COLLECTIONMAP collections = processing.getCollections();
        
        BuildVectorMap(collections);
        
        tree_ptr_ = buildSuffixTree(id_vec_map_);
    }
    
    string
    IMUSANT_ContourSuffixTreeBuilder::
    findAndPrintRepeatedContourSubstrings(int min_length)
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
    
    IMUSANT_range
    IMUSANT_ContourSuffixTreeBuilder::
    CalcRange(IMUSANT_contour_symbol& symbol) const
    {
        return symbol.getLocation();
    }
    
    void
    IMUSANT_ContourSuffixTreeBuilder::
    BuildVectorMap(IMUSANT_processing::COLLECTIONMAP& collections)
    {
        //get first part from first file
        int ID = 0;
        
        for (auto i = collections.begin(); i!=collections.end(); i++)
        {
            IMUSANT_collection_visitor collection = i->second;
            for (auto j = collection.getPartwiseContourVectors().begin(); j!=collection.getPartwiseContourVectors().end(); j++)
            {
                ++ID;
                id_vec_map_[ID] = (*j)->getContours();
            }
        }
    }
    
    string
    IMUSANT_ContourSuffixTreeBuilder::
    findAndPrintSupermaximalContours(int min_length, int min_percent)
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

    
    /*IMUSANT_ContourSuffixTreeBuilder::SUBSTR_VECTOR
    IMUSANT_ContourSuffixTreeBuilder::
    findSupermaximalsContours(int min_length, int min_percent)
    {
        SUBSTR_VECTOR ret_val;
        
        if (tree_ptr_==NULL || id_vec_map_.empty())
        {
            return ret_val;
        }
        
        repeats<vector<IMUSANT_contour_symbol> > rep(tree_ptr_);
        list<repeats<vector<IMUSANT_contour_symbol> >::supermax_node*> supermaxs = rep.supermax_find(min_percent, min_length);
        //MEMO auto = list<repeats<vector<IMUSANT_contour_symbol> >::supermax_node*>::const_iterator
        for (auto q = supermaxs.begin(); q!=supermaxs.end(); q++)
        {
            IMUSANT_repeated_contour_substring repeated_substr;
            
            for (repeats<vector<IMUSANT_contour_symbol> >::index t = (*q)->begin_i; t!=(*q)->end_i; t++)
            {
                repeated_substr.sequence.push_back(*t);
            }
            
            repeated_substr.add_occurrence( 0,
                                           (*q)->num_witness,
                                           (*q)->num_leaves,
                                           (*q)->percent );
            ret_val.push_back(repeated_substr);
        }
        
        return ret_val;
    }*/
    
    IMUSANT_ContourSuffixTreeBuilder::CONTOUR_TABLE
    IMUSANT_ContourSuffixTreeBuilder::entabulateMelodicDirectionPairs()
    {
        CONTOUR_TABLE table;
        
        for (auto cvm = id_vec_map_.begin(); cvm != id_vec_map_.end(); cvm++)
        {
            vector<IMUSANT_contour_symbol> contours = cvm->second;
            map<pair<IMUSANT_contour_symbol, IMUSANT_contour_symbol>, int> row;
            auto cnt1 = contours.begin(), cnt2 = cnt1+1;
            do
            {
                pair<IMUSANT_contour_symbol,IMUSANT_contour_symbol> cnt_pair = std::make_pair(*cnt1, *cnt2);
                int count = row[cnt_pair];
                row[cnt_pair] = ++count;
                cnt1++;
                cnt2++;
            } while (cnt2!=contours.end());
            table[cvm->first] = row;
        }
        
        return table;
    }
    
    string
    IMUSANT_ContourSuffixTreeBuilder::entabulateAndPrintMelodicDirectionPairs()
    {
        CONTOUR_TABLE table = entabulateMelodicDirectionPairs();
        ostringstream out;

        for (auto row : table)
        {
            ostringstream s,c;
            for (auto c_pair: row.second)
            {
                pair<IMUSANT_contour_symbol,IMUSANT_contour_symbol> cnt_pair = c_pair.first;
                s << "\"" << cnt_pair.first << "—" << cnt_pair.second << "\"" << "\t";
                c << c_pair.second << "\t";
            }
            out << s.str() << std::endl;
            out << c.str() << std::endl;
        }
        
        return out.str();
    }
    
} // namespace IMUSANT
