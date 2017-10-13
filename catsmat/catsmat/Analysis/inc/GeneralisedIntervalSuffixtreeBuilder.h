//
//  GeneralisedIntervalSuffixTreeBuilder.h
//  
//
//  Created by Jason Stoessel on 28/11/2016.
//
//

#ifndef ____GeneralisedIntervalSuffixTreeBuilder__
#define ____GeneralisedIntervalSuffixTreeBuilder__

#include <stdio.h>
#include "TSuffixtreeBuilder.h"
#include "IMUSANT_generalised_interval.h"
#include "TRepeatedSubstring.h"

namespace CATSMAT {
    
    class GeneralisedIntervalSuffixTreeBuilder : public TSuffixTreeBuilder<IMUSANT_generalised_interval,IMUSANT_processing>
    {
    public:
        
        GeneralisedIntervalSuffixTreeBuilder();
        ~GeneralisedIntervalSuffixTreeBuilder() {}
        
        void            Visit(const IMUSANT_processing&);
        
    private:
        
        void            BuildVectorMap(IMUSANT_processing::COLLECTIONMAP&);
        IMUSANT_range   CalcRange(IMUSANT_generalised_interval&) const;
    };
}
#endif /* defined(____GeneralisedIntervalSuffixTreeBuilder__) */
