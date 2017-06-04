//
//  IMUSANT_interval_processor.h
//  
//
//  Created by Jason Stoessel on 12/06/2016.
//
//

#ifndef ____IMUSANT_IntervalSuffixTreeBuilder__
#define ____IMUSANT_IntervalSuffixTreeBuilder__

#include <stdio.h>
#include "IMUSANT_t_suffixtree_builder.h"
#include "IMUSANT_interval.h"
#include "IMUSANT_t_repeated_substring.h"

namespace CATSMAT {
    
    class IMUSANT_IntervalSuffixTreeBuilder : public IMUSANT_T_SuffixTreeBuilder<IMUSANT_interval,IMUSANT_processing>
    {
    public:
        
        IMUSANT_IntervalSuffixTreeBuilder();
        ~IMUSANT_IntervalSuffixTreeBuilder() {} 
        
        void            Visit(const IMUSANT_processing&);
        
    private:
        void            BuildVectorMap(IMUSANT_processing::COLLECTIONMAP&);
        IMUSANT_range   CalcRange(IMUSANT_interval&) const;
    };
}
#endif /* defined(____IMUSANT_IntervalSuffixTreeBuilder__) */
