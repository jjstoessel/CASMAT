/*
 *  IMUSANT_measure.cpp
 *  imusant
 *
 *  Created by Jason Stoessel on 23/05/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "IMUSANT_measure.h"
#include "IMUSANT_types.h"
#include "IMUSANT_note.h"
#include "IMUSANT_element.h"

namespace IMUSANT
{
    
    S_IMUSANT_measure new_IMUSANT_measure()
    { IMUSANT_measure* o = new IMUSANT_measure(); assert (o!=0); return o; }
    
    //------------------------------------------------------------------------------
    // Acceptor function
    //------------------------------------------------------------------------------
    void IMUSANT_measure::accept(IMUSANT_visitor& visitor)
    {
        S_IMUSANT_measure sptr(this);
        visitor.visit(sptr);
    }
    
    void IMUSANT_measure::print(ostream& os)
    {
        os << "<MEAS>" << "=" << fMeasNum << endl;
        os << fClef;
        os << fTime;
        os << fKey;
        
        for (vector<S_IMUSANT_element>::iterator element=fElements.begin(); element!=fElements.end(); element++)
        {
            ((S_IMUSANT_element)*element)->print(os);
        }
        
        os << "<\\MEAS>" << endl;
    }
    
    IMUSANT_vector<S_IMUSANT_element>&
    IMUSANT_measure::
    elements()
    {
        return fElements;
    }
    
    void
    IMUSANT_measure::
    addElement (const S_IMUSANT_element& element)
    {
        fElements.push_back(element);
    }
    
    IMUSANT_vector<S_IMUSANT_note>&
    IMUSANT_measure::
    notes()
    {
        return fNotes;
    }

    void
    IMUSANT_measure::
    addNote(const S_IMUSANT_note& note)
    {
        addElement(note);
        fNotes.push_back(note);
    }

    IMUSANT_vector<S_IMUSANT_barline>&
    IMUSANT_measure::
    barlines()
    {
        return fBarlines;
    }
    
    void
    IMUSANT_measure::
    addBarline(const S_IMUSANT_barline& barline)
    {
        addElement(barline);
        fBarlines.push_back(barline);
    }
    
} //namespace IMUSANT