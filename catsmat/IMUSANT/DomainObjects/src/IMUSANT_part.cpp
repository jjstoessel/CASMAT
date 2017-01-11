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
    { IMUSANT_part* o = new IMUSANT_part(); assert (o!=0); return o; }
    
    //______________________________________________________________________________
    IMUSANT_part::IMUSANT_part()
    {
    }
    
    //------------------------------------------------------------------------------
    // Acceptor function
    //------------------------------------------------------------------------------
    void IMUSANT_part::accept(IMUSANT_visitor& visitor)
    {
        S_IMUSANT_part sptr(this);
        visitor.visit(sptr);
    }
    
    
    IMUSANT_vector<S_IMUSANT_note>
    IMUSANT_part::
    notes()
    {
        IMUSANT_vector<S_IMUSANT_note> the_notes;
        
        for (S_IMUSANT_measure measure : fMeasures)
        {
            the_notes.append(measure->notes());
        }
        
        return the_notes;
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
    
} //namespace IMUSANT
