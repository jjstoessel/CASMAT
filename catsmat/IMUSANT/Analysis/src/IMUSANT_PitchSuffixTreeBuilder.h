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
#include "IMUSANT_SuffixTreeBuilder.h"
#include "IMUSANT_pitch.h"
#include "IMUSANT_t_repeated_substring.h"

namespace IMUSANT {
    
    class IMUSANT_PitchSuffixTreeBuilder : public IMUSANT_SuffixTreeBuilder<IMUSANT_pitch,IMUSANT_processing>
    {
    public:
                
        IMUSANT_PitchSuffixTreeBuilder() {}
        
        void    Visit(const IMUSANT_processing&);
        string  findAndPrintLcsPairsPitches(bool consecutive=true);
        SUBSTR_VECTOR	findLcsPairsPitches(bool consecutive=true);
        
    private:
        
        void    BuildVectorMap(IMUSANT_processing::COLLECTIONMAP&);
    };
}

#endif /* defined(____IMUSANT_PitchSuffixTreeBuilder__) */
