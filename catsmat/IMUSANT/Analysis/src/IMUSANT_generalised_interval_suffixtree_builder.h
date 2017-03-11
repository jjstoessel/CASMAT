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
#include "IMUSANT_t_suffixtree_builder.h"
#include "IMUSANT_generalised_interval.h"
#include "IMUSANT_t_repeated_substring.h"

namespace IMUSANT {
    
    class IMUSANT_GeneralisedIntervalSuffixTreeBuilder : public IMUSANT_T_SuffixTreeBuilder<IMUSANT_generalised_interval,IMUSANT_processing>
    {
    public:
        
        IMUSANT_GeneralisedIntervalSuffixTreeBuilder();
        ~IMUSANT_GeneralisedIntervalSuffixTreeBuilder() {} 
        
        void            Visit(const IMUSANT_processing&);
        
    private:
        
        void            BuildVectorMap(IMUSANT_processing::COLLECTIONMAP&);
        IMUSANT_range   CalcRange(IMUSANT_generalised_interval&) const;
    };
}
#endif /* defined(____IMUSANT_GeneralisedIntervalSuffixTreeBuilder__) */
