//
//  IMUSANT_contour_processor.cpp
//  
//
//  Created by Jason Stoessel on 13/06/2016.
//
//

#include "IMUSANT_contour_suffixtree_builder.h"
#include "repeats.h"

namespace IMUSANT {
    
    void
    IMUSANT_ContourSuffixTreeBuilder::Visit(const IMUSANT_processing& processing)
    {
        IMUSANT_processing::COLLECTIONMAP collections = processing.getCollections();
        
        BuildVectorMap(collections);
        
        tree_ptr_ = buildSuffixTree(id_vec_map_);
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
        
    
} // namespace IMUSANT
