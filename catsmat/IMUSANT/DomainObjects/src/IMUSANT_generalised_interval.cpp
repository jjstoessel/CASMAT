//
//  IMUSANT_generalised_interval.cpp
//  
//
//  Created by Jason James Stoessel on 19/11/2016.
//
//

#include "IMUSANT_generalised_interval.h"

namespace IMUSANT {
    
    IMUSANT_interval::interval_type IMUSANT_generalised_interval::getInterval()
    {
       //calculate generic interval type
       return getNumber();
    }
    
    //overrides base class int() function which is used in compare routine
    IMUSANT_generalised_interval::operator int() const
    {
        int r = 0;
        
        //no need to handle unisons
        if (abs(fInterval)>0)
        {
            r = getNumber();
            
            //inverted negative intervals
            if (r<0) r+=7;
        }
        
        r+=7*fOctaves; //convert to a compound interval
        
        return r;
    }
}