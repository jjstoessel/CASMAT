//
//  IMUSANT_set_of_segment.h
//  catsmat
//
//  Created by Derrick Hill on 28/1/17.
//
//

#ifndef __SetOfSegment__
#define __SetOfSegment__

#include <stdio.h>
#include <unordered_set>

#include "Segment.h"

namespace CATSMAT
{
    class SetOfSegment : public unordered_set<Segment, SegmentHash, SegmentComparator>
    {
        friend ostream& operator<< (ostream& os, const SetOfSegment& segment_set);
        
    public:
        virtual ~SetOfSegment() {}
        
        string printProperties(bool include_header_row);
        
    };
}

#endif /* __SetOfSegment__ */
