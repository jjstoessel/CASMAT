//
//  ContourSuffixTreeBuilder.h
//  
//
//  Created by Jason Stoessel on 13/06/2016.
//
//

#ifndef ____ContourSuffixTreeBuilder__
#define ____ContourSuffixTreeBuilder__

#include <stdio.h>
#include <vector>
#include <map>
#include "TSuffixtreeBuilder.h"
#include "IMUSANT_contour_symbol.h"
#include "TRepeatedSubstring.h"

using namespace IMUSANT;

namespace CATSMAT {
    
    class ContourSuffixTreeBuilder : public TSuffixTreeBuilder<IMUSANT_contour_symbol,IMUSANT_processing>
    {
    public:
        typedef std::map<int, map<pair<IMUSANT_contour_symbol, IMUSANT_contour_symbol>, int> > CONTOUR_TABLE;
        
        ContourSuffixTreeBuilder() {}
        
        void            Visit(const IMUSANT_processing&);
    
    private:
        
        void            BuildVectorMap(IMUSANT_processing::COLLECTIONMAP&);
        IMUSANT_range   CalcRange(IMUSANT_contour_symbol&) const;
    };
}

#endif /* defined(____ContourSuffixTreeBuilder__) */
