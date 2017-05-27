//
//  IMUSANT_pitch_processor.h
//  
//
//  Created by Jason James Stoessel on 13/06/2016.
//
//

#ifndef ____IMUSANT_PitchSuffixTreeBuilder__
#define ____IMUSANT_PitchSuffixTreeBuilder__

#include <stdio.h>
#include "IMUSANT_t_suffixtree_builder.h"
#include "IMUSANT_pitch.h"
#include "IMUSANT_t_repeated_substring.h"

namespace IMUSANT {
    
    class IMUSANT_PitchSuffixTreeBuilder : public IMUSANT_T_SuffixTreeBuilder<IMUSANT_pitch,IMUSANT_processing>
    {
    public:
                
        IMUSANT_PitchSuffixTreeBuilder() {}
        
        void    Visit(const IMUSANT_processing&);
        
    private:
        
        void    BuildVectorMap(IMUSANT_processing::COLLECTIONMAP&);
        IMUSANT_range   CalcRange(IMUSANT_pitch&) const;
    };
}

#endif /* defined(____IMUSANT_PitchSuffixTreeBuilder__) */
