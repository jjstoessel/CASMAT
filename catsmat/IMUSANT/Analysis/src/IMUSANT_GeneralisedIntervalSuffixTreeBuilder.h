//
//  IMUSANT_generalised_interval_processor.h
//  
//
//  Created by Jason Stoessel on 28/11/2016.
//
//

#ifndef ____IMUSANT_GeneralisedIntervalSuffixTreeBuilder__
#define ____IMUSANT_GeneralisedIntervalSuffixTreeBuilder__

#include <stdio.h>
#include "IMUSANT_SuffixTreeBuilder.h"
#include "IMUSANT_generalised_interval.h"
#include "IMUSANT_t_repeated_substring.h"

namespace IMUSANT {
    
    class IMUSANT_GeneralisedIntervalSuffixTreeBuilder : public IMUSANT_SuffixTreeBuilder<IMUSANT_generalised_interval,IMUSANT_processing>
    {
    public:
        
        IMUSANT_GeneralisedIntervalSuffixTreeBuilder();
        ~IMUSANT_GeneralisedIntervalSuffixTreeBuilder() {} 
        //consider common base class for processors for generalised interval and interval
        string          findAndPrintRepeatedIntervalSubstrings(int min_length=4);
        SUBSTR_VECTOR   findRepeatedIntervalSubstrings(int min_length=4);
        string          findAndPrintSupermaximalIntervals(int min_length=4, int min_percent=100);
        SUBSTR_VECTOR   findSupermaximalIntervals(int min_length=4, int min_percent=100);
        string          findAndPrintLcsPairsIntervals(bool consecutive=true, bool reverse_search=false, bool retrograde=false);
        SUBSTR_VECTOR   findLcsPairsIntervals(bool consecutive=true, bool reverse_search=false, bool retrograde=false);
        
        void            Visit(const IMUSANT_processing&);
        
    private:
        
        void            BuildVectorMap(IMUSANT_processing::COLLECTIONMAP&);
        //_tree*  buildIntervalSuffixTree(IMUSANT_processing::COLLECTIONMAP&);
    };
}
#endif /* defined(____IMUSANT_GeneralisedIntervalSuffixTreeBuilder__) */