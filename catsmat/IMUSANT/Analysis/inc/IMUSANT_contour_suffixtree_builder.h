//
//  IMUSANT_contour_processor.h
//  
//
//  Created by Jason Stoessel on 13/06/2016.
//
//

#ifndef ____IMUSANT_ContourSuffixTreeBuilder__
#define ____IMUSANT_ContourSuffixTreeBuilder__

#include <stdio.h>
#include <vector>
#include <map>
#include "IMUSANT_t_suffixtree_builder.h"
#include "IMUSANT_contour_symbol.h"
#include "IMUSANT_t_repeated_substring.h"

namespace IMUSANT {
    
    class IMUSANT_ContourSuffixTreeBuilder : public IMUSANT_T_SuffixTreeBuilder<IMUSANT_contour_symbol,IMUSANT_processing>
    {
    public:
        typedef std::map<int, map<pair<IMUSANT_contour_symbol, IMUSANT_contour_symbol>, int> > CONTOUR_TABLE;
        
        IMUSANT_ContourSuffixTreeBuilder() {}
        
        void            Visit(const IMUSANT_processing&);
    
    private:
        
        void            BuildVectorMap(IMUSANT_processing::COLLECTIONMAP&);
        IMUSANT_range   CalcRange(IMUSANT_contour_symbol&) const;
    };
}

#endif /* defined(____IMUSANT_contour_processor__) */
