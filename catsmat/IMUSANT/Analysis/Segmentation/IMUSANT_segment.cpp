//
//  IMUSANT_segment.cpp
//  catsmat
//
//  Created by Derrick Hill on 8/11/2016.
//
//

#include "IMUSANT_segment.h"

namespace IMUSANT
{
    
    S_IMUSANT_segment new_IMUSANT_segment()
    {
        IMUSANT_segment* o = new IMUSANT_segment();
        assert (o!=0);
        return o;
    }
    
}
