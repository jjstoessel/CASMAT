//
//  IMUSANT_set_of_segment.cpp
//  catsmat
//
//  Created by Derrick Hill on 28/1/17.
//
//

#include "IMUSANT_set_of_segment.h"

namespace CATSMAT
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
    
    string
    IMUSANT_set_of_segment::
    printProperties(bool include_header_row)
    {
        stringstream buffer;
        
        bool first_time_round = true;
 
        for (IMUSANT_set_of_segment::iterator it = this->begin(); it != this->end(); it++ )
        {
            if (first_time_round && include_header_row)
            {
                buffer << it->printPropertiesHeaderRow();
                first_time_round = false;
            }
            
            buffer << it->printProperties();
        }
        
        return buffer.str();
    }
    

}
