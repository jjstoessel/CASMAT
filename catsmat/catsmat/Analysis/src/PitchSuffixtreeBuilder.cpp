//
//  PitchSuffixTreeBuilder.cpp
//  
//
//  Created by Jason Stoessel on 13/06/2016.
//
//

#include "PitchSuffixtreeBuilder.h"

namespace CATSMAT {
    
    void
    PitchSuffixTreeBuilder::Visit(const IMUSANT_processing& processing)
    {
        IMUSANT_processing::COLLECTIONMAP collections = processing.getCollections();
        
        BuildVectorMap(collections);
    }
    
    void
    PitchSuffixTreeBuilder::
    BuildVectorMap(IMUSANT_processing::COLLECTIONMAP& collections)
    {
        //get first part from first file
        int ID = 0;
        
        for (auto i = collections.begin(); i!=collections.end(); i++)
        {
            IMUSANT_collection_visitor collection = i->second;
            for (auto j = collection.getPartwisePitchVectors().begin(); j!=collection.getPartwisePitchVectors().end(); j++)
            {
                ++ID;
                id_vec_map_[ID] = (*j)->getPitches();
            }
        }
    }

    
    
    IMUSANT_range
    PitchSuffixTreeBuilder::
    CalcRange(IMUSANT_pitch& pitch) const
    {
        return IMUSANT_range(); //nothing for now
    }
   

}
