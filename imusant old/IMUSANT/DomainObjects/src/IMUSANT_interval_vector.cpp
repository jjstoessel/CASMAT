/*
 *  IMUSANT_interval_vector.cpp
 *  imusant
 *
 *  Created by Jason Stoessel on 24/06/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "IMUSANT_interval_vector.h"

namespace IMUSANT
{
    
    S_IMUSANT_interval_vector new_IMUSANT_interval_vector()
    { IMUSANT_interval_vector* o = new IMUSANT_interval_vector(); assert(o!=0); return o; }
    
    ostream& operator<< (ostream& os, const S_IMUSANT_interval_vector& elt )
    {
        elt->print(os);
        
        return os;
    }
    
    IMUSANT_interval_vector::IMUSANT_interval_vector()
    : fMinimumIntervals(3), fMaximumIntervals(12)
    {
        fIntervals.reserve(fMinimumIntervals);
    }
    
    bool	IMUSANT_interval_vector::add(const IMUSANT_interval& interval)
    {
        if ( fIntervals.size()<fMaximumIntervals)
        {
            //copies interval
            fIntervals.push_back(interval);
            return true;
        }
        //If reached here, then vector is maxed out.
        return false;
    }
    
#ifdef ORIGINAL
    void IMUSANT_interval_vector::print(ostream& os)
    {
        for ( vector<IMUSANT_interval>::const_iterator interval = fIntervals.begin();
             interval != fIntervals.end();
             interval++ )
        {
            os << (*interval) << ", ";
        }
        os << endl;
    }
#endif
    
#ifdef NEW
    void IMUSANT_interval_vector::print(ostream& os)
    {
        for ( vector<IMUSANT_interval>::const_iterator interval = fIntervals.begin();
             interval != fIntervals.end();
             interval++ )
        {
            os << (*interval) <<  "(" << interval->getLocation() << ")" <<  ", ";
        }
        os << endl;
    }
#endif
    
}//namespace IMUSANT
