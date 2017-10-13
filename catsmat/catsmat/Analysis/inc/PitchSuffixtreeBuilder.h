//
//  IMUSANT_pitch_processor.h
//  
//
//  Created by Jason James Stoessel on 13/06/2016.
//
//

#ifndef ____PitchSuffixTreeBuilder__
#define ____PitchSuffixTreeBuilder__

#include <stdio.h>
#include "TSuffixtreeBuilder.h"
#include "IMUSANT_pitch.h"
#include "TRepeatedSubstring.h"

namespace CATSMAT {
    
    class PitchSuffixTreeBuilder : public TSuffixTreeBuilder<IMUSANT_pitch,IMUSANT_processing>
    {
    public:
                
        PitchSuffixTreeBuilder() {}
        
        void    Visit(const IMUSANT_processing&);
        
    private:
        
        void    BuildVectorMap(IMUSANT_processing::COLLECTIONMAP&);
        IMUSANT_range   CalcRange(IMUSANT_pitch&) const;
    };
}

#endif /* defined(____PitchSuffixTreeBuilder__) */
