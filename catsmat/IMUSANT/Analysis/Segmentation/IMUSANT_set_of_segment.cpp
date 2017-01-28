//
//  IMUSANT_set_of_segment.cpp
//  catsmat
//
//  Created by Derrick Hill on 28/1/17.
//
//

#include "IMUSANT_set_of_segment.h"

namespace IMUSANT
{
    
    ostream& operator<< (ostream& os, const IMUSANT_set_of_segment& segment_set )
    {
        os << endl << "----- SEGMENTS -----" << endl;
        for (IMUSANT_set_of_segment::iterator it = segment_set.begin(); it != segment_set.end(); it++ )
        {
            os << *it << endl;
        }
        
        return os;
    }
    

}
