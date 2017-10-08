//
//  I_SetOfSegment.h
//  catsmat
//
//  Created by Derrick Hill on 25/6/17.
//
//

#ifndef __I_SetOfSegment__
#define __I_SetOfSegment__

#include <stdio.h>
#include "I_Segment.h"

namespace CATSMAT
{
    class I_SetOfSegment
    {

    public:
        
        virtual void insertSegment(I_Segment segment) = 0;
        virtual void clearSegments() = 0;
        virtual string printProperties(bool include_header_row) = 0;
        
    };
}

#endif /* __I_SetOfSegment__ */
