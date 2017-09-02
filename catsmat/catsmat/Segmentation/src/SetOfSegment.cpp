//
//  SetOfSegment.cpp
//  catsmat
//
//  Created by Derrick Hill on 28/1/17.
//
//

#include "SetOfSegment.h"

namespace CATSMAT
{
    
    ostream& operator<< (ostream& os, const SetOfSegment& segment_set )
    {
        os << endl << "----- SEGMENTS -----" << endl;
        for (SetOfSegment::iterator it = segment_set.begin(); it != segment_set.end(); it++ )
        {
            os << *it << endl;
        }
        
        return os;
    }
    
    string
    SetOfSegment::
    printProperties(bool include_header_row)
    {
        stringstream buffer;
        
        bool first_time_round = true;
 
        for (SetOfSegment::iterator it = this->begin(); it != this->end(); it++ )
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
