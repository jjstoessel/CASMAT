/*
 *  IMUSANT_chord.cpp
 *  imusant
 *
 *  Created by Jason Stoessel on 23/05/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "IMUSANT_chord.h"
#include "IMUSANT_note.h"
#include <iostream>

namespace IMUSANT
{
    
    S_IMUSANT_chord new_IMUSANT_chord()
    {
        IMUSANT_chord* o = new IMUSANT_chord(); assert(o!=0); return o;
    }
    

    void
    IMUSANT_chord::
    accept(IMUSANT_visitor& visitor)
    {
        S_IMUSANT_chord sptr(this);
        visitor.visit(sptr);
    }
    
    void
    IMUSANT_chord::
    print_short(ostream& os) const
    {
        os << "<CHORD/>" << endl;
    }
    
    void
    IMUSANT_chord::
    print(ostream& os) const
    {
        os << "<CHRD>" << endl;
        
        for (vector<S_IMUSANT_note>::const_iterator note=fChordNotes.begin(); note!=fChordNotes.end(); note++)
        {
            os << " ";
            (*note)->print_short(os);
        }
        
        os << "<\\CHRD>" << endl;
    }
    
    //sorts chord from bass up (i.e. lower note is first in vector)
    //use std::reverse(fChordNotes.begin(), fChordNotes.end()); to make top up
    void
    IMUSANT_chord::
    sort(sorttype type)
    {
        if (type == pitch)
        {
            sortstruct s(this);
            
            std::sort(fChordNotes.begin(), fChordNotes.end(), s); //result in a bottom up sort
        }
    }
    
}//namespace IMUSANT