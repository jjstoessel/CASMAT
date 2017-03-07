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
        {
            BuildVectorMap(trigrams.get_tokens());
            tree_ptr_ = buildSuffixTree(id_vec_map_);
        }
    }
    
    void
    CATSMAT_TrigramSuffixTreeBuilder::
    BuildVectorMap(const CATSMAT_TrigramSequences::TokenVectors& tokens)
    {
        int ID = 0;
        
        for (std::vector<vector<CATSMAT_TrigramSequences::Token> >::const_iterator i = tokens.begin(); i!=tokens.end(); i++)
        {
            ++ID;
            id_vec_map_[ID] = *i;
            id_vec_map_[ID].push_back(ID<<24); //ad a unique value terminator
            
        }
    }
    
    //overrides virtual methond in base class
    IMUSANT_range
    CATSMAT_TrigramSuffixTreeBuilder::
    CalcRange(CATSMAT_TrigramSequences::Token& token) const
    {
        return IMUSANT_range(); //do nothing for now
    }
}
