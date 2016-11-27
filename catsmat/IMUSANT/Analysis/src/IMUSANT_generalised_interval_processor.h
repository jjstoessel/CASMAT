//
//  IMUSANT_generalised_interval_processor.h
//  
//
//  Created by Jason Stoessel on 28/11/2016.
//
//

#ifndef ____IMUSANT_generalised_interval_processor__
#define ____IMUSANT_generalised_interval_processor__

#include <stdio.h>
#include "IMUSANT_processor.h"
#include "IMUSANT_generalised_interval.h"
#include "IMUSANT_t_repeated_substring.h"

namespace IMUSANT {
    
    class IMUSANT_generalised_interval_processor : public IMUSANT_processor<IMUSANT_generalised_interval>
    {
    public:
        typedef vector<IMUSANT_repeated_generalised_interval_substring> SUBSTR_VECTOR;
        
        IMUSANT_generalised_interval_processor();
        ~IMUSANT_generalised_interval_processor() {} 
        //consider common base class for processors for generalised interval and interval
        string          findAndPrintRepeatedIntervalSubstrings(int min_length=4);
        SUBSTR_VECTOR   findRepeatedIntervalSubstrings(int min_length=4);
        string          findAndPrintSupermaximalIntervals(int min_length=4, int min_percent=100);
        SUBSTR_VECTOR   findSupermaximalIntervals(int min_length=4, int min_percent=100);
        string          findAndPrintLcsPairsIntervals(bool consecutive=true, bool reverse_search=false, bool retrograde=false);
        SUBSTR_VECTOR   findLcsPairsIntervals(bool consecutive=true, bool reverse_search=false, bool retrograde=false);
        
        void            Visit(const IMUSANT_processing&);
        
    private:
        
        _tree*  buildIntervalSuffixTree(IMUSANT_processing::COLLECTIONMAP&);
    };
}
#endif /* defined(____IMUSANT_generalised_interval_processor__) */
