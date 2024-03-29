//
//  CATSMAT_TrigramSuffixTreeBuilder.hpp
//  catsmat
//
//  Created by Jason Stoessel on 3/03/2017.
//
//

#ifndef CATSMAT_TrigramSuffixTreeBuilder_hpp
#define CATSMAT_TrigramSuffixTreeBuilder_hpp

#include <stdio.h>
#include "TSuffixtreeBuilder.h"
#include "CATSMAT_TrigramSequences.h"

using namespace std;

namespace CATSMAT
{
    //implementation to take TrigramSequences, i.e. one score
    class CATSMAT_TrigramSuffixTreeBuilder : public TSuffixTreeBuilder<Token, CATSMAT_TrigramSequences>
    {
    public:
        
        CATSMAT_TrigramSuffixTreeBuilder() {}
        
        void    Visit(const CATSMAT_TrigramSequences&);
    private:
        void    BuildVectorMap(map<S_IMUSANT_score,IMUSANT_collection_visitor>&) {};
        void    BuildVectorMap(const CATSMAT_TrigramSequences::TokenVectors&);
        
        IMUSANT_range CalcRange(Token&) const;
    };
}
#endif /* CATSMAT_TrigramSuffixTreeBuilder_hpp */
