//
//  CATSMAT_TrigramSuffixTreeBuilder.cpp
//  catsmat
//
//  Created by Jason James Stoessel on 3/03/2017.
//
//

#include "CATSMAT_TrigramSuffixTreeBuilder.hpp"

namespace CATSMAT {
    
    void
    CATSMAT_TrigramSuffixTreeBuilder::
    Visit(const CATSMAT_TrigramSequences& trigrams)
    {
        if (!trigrams.get_tokens().empty())
            BuildVectorMap(trigrams.get_tokens());
        
        mTreePtr = buildSuffixTree(mID_vec_map);
    }
    
    void
    CATSMAT_TrigramSuffixTreeBuilder::
    BuildVectorMap(const CATSMAT_TrigramSequences::TokenVectors& tokens)
    {
        int ID = 0;
        
        for (auto i = tokens.begin(); i!=tokens.end(); i++)
        {
            ++ID;
            mID_vec_map[ID] = *i;
        }
    }
}