//
//  I_SetOfSegment.h
//  catsmat
//
//  Created by Derrick Hill on 25/6/17.
//
//

#ifndef I_SetOfSegment_h
#define I_SetOfSegment_h

#include <stdio.h>

namespace CATSMAT
{
    class I_SetOfSegment
    {

    public:
        
        virtual insertSegment(I_Segment segment);
        virtual void clearSegments() = 0;
        virtual string printProperties(bool include_header_row) = 0;
        
    };
}

#endif /* IMUSANT_set_of_segment_h */


#endif /* I_SetOfSegment_h */
