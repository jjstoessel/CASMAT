//
//  IMUSANT_interval_processor.h
//  
//
//  Created by Jason Stoessel on 12/06/2016.
//
//

#ifndef ____IMUSANT_interval_processor__
#define ____IMUSANT_interval_processor__

#include <stdio.h>
#include "IMUSANT_processor.h"
#include "IMUSANT_interval.h"
#include "IMUSANT_t_repeated_substring.h"

namespace IMUSANT {
    
    class IMUSANT_interval_processor : public IMUSANT_processor<IMUSANT_interval,IMUSANT_processing>
    {
    public:
        typedef vector<IMUSANT_repeated_interval_substring> SUBSTR_VECTOR;
        
        IMUSANT_interval_processor();
        ~IMUSANT_interval_processor() {} 
        
        string          findAndPrintRepeatedIntervalSubstrings(int min_length=4);
        SUBSTR_VECTOR   findRepeatedIntervalSubstrings(int min_length=4);
        string          findAndPrintSupermaximalIntervals(int min_length=4, int min_percent=100);
        SUBSTR_VECTOR   findSupermaximalIntervals(int min_length=4, int min_percent=100);
        string          findAndPrintLcsPairsIntervals(bool consecutive=true, bool reverse_search=false, bool retrograde=false);
        SUBSTR_VECTOR   findLcsPairsIntervals(bool consecutive=true, bool reverse_search=false, bool retrograde=false);
        
        void            Visit(const IMUSANT_processing&);
        
    private:
        void            buildVectorMap(IMUSANT_processing::COLLECTIONMAP&);
        //_tree*  buildIntervalSuffixTree(IMUSANT_processing::COLLECTIONMAP&);
    };
}
#endif /* defined(____IMUSANT_interval_processor__) */
