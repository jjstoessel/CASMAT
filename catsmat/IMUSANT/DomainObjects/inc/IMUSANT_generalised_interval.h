//
//  IMUSANT_generalised_interval.h
//  
//
//  Created by Jason James Stoessel on 19/11/2016.
//
//

#ifndef ____IMUSANT_generalised_interval__
#define ____IMUSANT_generalised_interval__

#include <stdio.h>
#include "IMUSANT_interval.h"

namespace IMUSANT {
    class IMUSANT_generalised_interval : public IMUSANT_interval
    {
    public:
        
        IMUSANT_generalised_interval() : IMUSANT_interval() {}
        IMUSANT_generalised_interval(const IMUSANT_generalised_interval& iv) : IMUSANT_interval(iv){}
        IMUSANT_generalised_interval(const S_IMUSANT_pitch first, const S_IMUSANT_pitch second) : IMUSANT_interval(first,second) {}
        IMUSANT_generalised_interval(interval_type iv) : IMUSANT_interval(iv) {}
        //IMUSANT_generalised_interval(IMUSANT_interval& iv) : IMUSANT_interval(iv) {}
        
        
        operator int() const;
        interval_type getInterval(); //overrides base class function
    private:
        
    };
}

#endif /* defined(____IMUSANT_generalised_interval__) */
