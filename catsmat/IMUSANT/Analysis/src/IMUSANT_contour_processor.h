//
//  IMUSANT_contour_processor.h
//  
//
//  Created by Jason Stoessel on 13/06/2016.
//
//

#ifndef ____IMUSANT_contour_processor__
#define ____IMUSANT_contour_processor__

#include <stdio.h>
#include "IMUSANT_processor.h"
#include "IMUSANT_contour_symbol.h"
#include "IMUSANT_t_repeated_substring.h"
#include <vector>
#include <map>

namespace IMUSANT {
    
    class IMUSANT_contour_processor : public IMUSANT_processor<IMUSANT_contour_symbol,IMUSANT_processing>
    {
    public:
        typedef std::vector<IMUSANT_repeated_contour_substring> SUBSTR_VECTOR;
        typedef std::map<int, map<pair<IMUSANT_contour_symbol, IMUSANT_contour_symbol>, int> > CONTOUR_TABLE;
        
        IMUSANT_contour_processor() {}
        
        void            Visit(const IMUSANT_processing&);
        
        string          findAndPrintRepeatedContourSubstrings(int min_length=5);
        SUBSTR_VECTOR   findRepeatedContourSubstrings(int min_length=5);
        string          findAndPrintSupermaximalContours(int min_length, int min_percent);
        SUBSTR_VECTOR   findSupermaximalsContours(int min_length, int min_percent);
        CONTOUR_TABLE   entabulateMelodicDirectionPairs();
        string          entabulateAndPrintMelodicDirectionPairs();
    private:
        
        void            buildVectorMap(IMUSANT_processing::COLLECTIONMAP&);
        //_tree*  buildContourSuffixTree(IMUSANT_processing::COLLECTIONMAP&);
    };
}

#endif /* defined(____IMUSANT_contour_processor__) */
