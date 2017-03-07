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
#include "IMUSANT_SuffixTreeBuilder.h"
#include "IMUSANT_contour_symbol.h"
#include "IMUSANT_t_repeated_substring.h"
#include <vector>
#include <map>

namespace IMUSANT {
    
    class IMUSANT_ContourSuffixTreeBuilder : public IMUSANT_SuffixTreeBuilder<IMUSANT_contour_symbol,IMUSANT_processing>
    {
    public:
        typedef std::map<int, map<pair<IMUSANT_contour_symbol, IMUSANT_contour_symbol>, int> > CONTOUR_TABLE;
        
        IMUSANT_ContourSuffixTreeBuilder() {}
        
        void            Visit(const IMUSANT_processing&);
        
        string          findAndPrintRepeatedContourSubstrings(int min_length=5);
        string          findAndPrintSupermaximalContours(int min_length, int min_percent);
        SUBSTR_VECTOR   findSupermaximalsContours(int min_length, int min_percent);
        CONTOUR_TABLE   entabulateMelodicDirectionPairs();
        string          entabulateAndPrintMelodicDirectionPairs();
    private:
        
        void            BuildVectorMap(IMUSANT_processing::COLLECTIONMAP&);
        IMUSANT_range   CalcRange(IMUSANT_contour_symbol&) const;
    };
}

#endif /* defined(____IMUSANT_contour_processor__) */
