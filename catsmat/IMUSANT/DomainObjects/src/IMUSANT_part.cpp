/*
 *  IMUSANT_part.cpp
 *  imusant
 *
 *  Created by Jason Stoessel on 23/05/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "IMUSANT_part.h"

namespace IMUSANT
{
    
    S_IMUSANT_part new_IMUSANT_part()
    {
        IMUSANT_part* o = new IMUSANT_part(); assert (o!=0); return o;
    }
    
    
    void
    IMUSANT_part::
    accept(IMUSANT_visitor& visitor)
    {
        S_IMUSANT_part sptr(this);
        visitor.visit(sptr);
    }
    
    
    IMUSANT_vector<S_IMUSANT_note>&
    IMUSANT_part::
    notes()
    {
        if (!notes_.empty()) return notes_;
        
        for (S_IMUSANT_measure measure : fMeasures)
        {
            notes_.append(measure->notes());
        }
        
        return notes_;
    }
    
    void IMUSANT_part::print(ostream& os)
    {
        os << "<PART>" << endl;
        os << "Part name: " << fPartName << endl;
        os << "Part abbrevavtion: " << fPartAbbrev << endl;
        os << "Part Id: " << fXMLID << endl;
        
        for (vector<S_IMUSANT_measure>::const_iterator measure=fMeasures.begin(); measure!=fMeasures.end(); measure++)
        {
            (*measure)->print(os);
        }
        
        os << "<\\PART>" << endl;
    }
    
    bool
    IMUSANT_part::
    operator==(const IMUSANT_part& rhs) const
    {
        bool ret_val = true;
        
        if (getNumMeasures() != rhs.getNumMeasures())
            ret_val = false;
        
        if (getPartName() != rhs.getPartName())
            ret_val = false;
        
        if (getID() != rhs.getID())
            ret_val = false;
        
        if (getDivisions() != rhs.getDivisions())
            ret_val = false;
        
        if (fDivisions != rhs.fDivisions)
            ret_val = false;
        
        if (fVoiceCount != rhs.fVoiceCount)
            ret_val = false;
            
        return ret_val;
    }
    
    
    
    
    
} //namespace IMUSANT
