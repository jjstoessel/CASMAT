//
//  IMUSANT_contour_processor.cpp
//  
//
//  Created by Jason Stoessel on 13/06/2016.
//
//

#include "ContourSuffixtreeBuilder.h"
#include "repeats.h"

namespace CATSMAT {
    
    void
    ContourSuffixTreeBuilder::Visit(const IMUSANT_processing& processing)
    {
        IMUSANT_processing::COLLECTIONMAP collections = processing.getCollections();
        
        BuildVectorMap(collections);
        
        //tree_ptr_ = buildSuffixTree(id_vec_map_);
    }
    
    
    IMUSANT_range
    ContourSuffixTreeBuilder::
    CalcRange(IMUSANT_contour_symbol& symbol) const
    {
        return symbol.getLocation();
    }
    
    void
    ContourSuffixTreeBuilder::
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
