//
//  IMUSANT_interval_processor.h
//  
//
//  Created by Jason Stoessel on 12/06/2016.
//
//

#ifndef ____IntervalSuffixTreeBuilder__
#define ____IntervalSuffixTreeBuilder__

#include <stdio.h>
#include "TSuffixtreeBuilder.h"
#include "IMUSANT_interval.h"
#include "TRepeatedSubstring.h"

namespace CATSMAT {
    
    class IntervalSuffixTreeBuilder : public TSuffixTreeBuilder<IMUSANT_interval,IMUSANT_processing>
    {
    public:
        
        IntervalSuffixTreeBuilder();
        ~IntervalSuffixTreeBuilder() {}
        
        void            Visit(const IMUSANT_processing&);
        
    private:
        void            BuildVectorMap(IMUSANT_processing::COLLECTIONMAP&);
        IMUSANT_range   CalcRange(IMUSANT_interval&) const;
    };
}
#endif /* defined(____IntervalSuffixTreeBuilder__) */
