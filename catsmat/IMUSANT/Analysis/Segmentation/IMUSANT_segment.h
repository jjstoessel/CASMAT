//
//  IMUSANT_segment.h
//  catsmat
//
//  Created by Derrick Hill on 8/11/2016.
//
//

#ifndef IMUSANT_segment_h
#define IMUSANT_segment_h

#include <stdio.h>

#include "IMUSANT_note.h"

using namespace std;

namespace IMUSANT
{
    class IMUSANT_segment : public smartable
    {
    public:
       
        friend IMUSANT_SMARTP<IMUSANT_segment> new_IMUSANT_segmente();
        
        
        IMUSANT_segment()
        {
        }
        
        virtual ~IMUSANT_segment() {}

    };
    
    typedef IMUSANT_SMARTP<IMUSANT_segment> S_IMUSANT_segment;
    IMUSANT_SMARTP<IMUSANT_segment> new_IMUSANT_segment();
}

#endif /* IMUSANT_segment_hpp */
