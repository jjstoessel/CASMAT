//
//  IMUSANT_set_of_segment.h
//  catsmat
//
//  Created by Derrick Hill on 28/1/17.
//
//

#ifndef IMUSANT_set_of_segment_h
#define IMUSANT_set_of_segment_h

#include <stdio.h>
#include <unordered_set>

#include "IMUSANT_segment.h"

namespace CATSMAT
{
    class IMUSANT_set_of_segment : public unordered_set<IMUSANT_segment, SegmentHash, SegmentComparator>
    {
        friend ostream& operator<< (ostream& os, const IMUSANT_set_of_segment& segment_set);
        
    public:
        virtual ~IMUSANT_set_of_segment() {}
        
        string printProperties(bool include_header_row);
        
    };
}

#endif /* IMUSANT_set_of_segment_h */
