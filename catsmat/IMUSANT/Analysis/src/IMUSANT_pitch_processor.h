//
//  IMUSANT_pitch_processor.h
//  
//
//  Created by Jason James Stoessel on 13/06/2016.
//
//

#ifndef ____IMUSANT_pitch_processor__
#define ____IMUSANT_pitch_processor__

#include <stdio.h>
#include "IMUSANT_processor.h"
#include "IMUSANT_pitch.h"
#include "IMUSANT_t_repeated_substring.h"

namespace IMUSANT {
    
    class IMUSANT_pitch_processor : public IMUSANT_processor<IMUSANT_pitch,IMUSANT_processing>
    {
    public:
        typedef vector<IMUSANT_repeated_pitch_substring> SUBSTR_VECTOR;
        
        IMUSANT_pitch_processor() {}
        
        void    Visit(const IMUSANT_processing&);
        string  findAndPrintLcsPairsPitches(bool consecutive=true);
        SUBSTR_VECTOR	findLcsPairsPitches(bool consecutive=true);
        
    private:
        
        void    buildVectorMap(IMUSANT_processing::COLLECTIONMAP&);
        //_tree*  buildPitchSuffixTree(IMUSANT_processing::COLLECTIONMAP&);
    };
}

#endif /* defined(____IMUSANT_pitch_processor__) */
