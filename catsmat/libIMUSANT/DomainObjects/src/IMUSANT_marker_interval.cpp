//
//  IMUSANT_marker_interval.cpp
//  imusant
//
//  Created by Jason Stoessel on 5/05/2016.
//
//

#include "IMUSANT_marker_interval.h"

namespace IMUSANT {
        
    IMUSANT_marker_interval IMUSANT_marker_interval::MakeUniqueInterval()
    {
        static int unique = undefined;
        static int marker = 0;
        
        IMUSANT_marker_interval out(unique);
        
        out.setOctaves(unique);
        out.setMarkerID(marker);
        
        if (undefined-unique>FLAGSPACE)
            cerr << "Unique flag limit reached" << endl;
        
        unique--;
        marker++;
        
        return out;
    }
    
    const IMUSANT_marker_interval& IMUSANT_marker_interval::operator=( const IMUSANT_marker_interval& rhs )
    {
        (IMUSANT_interval)(*this) = (IMUSANT_interval)rhs;
        
        this->setWorkTitle(rhs.getWorkTitle());
        this->setMovementTitle(rhs.getMovementTitle());
        this->setPartID(rhs.getPartID());
        fMarkerID = rhs.getMarkerID();
        
        return *this;
    }
}