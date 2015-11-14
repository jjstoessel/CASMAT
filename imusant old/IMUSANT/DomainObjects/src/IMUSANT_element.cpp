/*
 *  IMUSANT_element.cpp
 *  imusant
 *
 *  Created by Jason Stoessel on 22/03/06.
 *  Copyright 2006 Jason Stoessel. All rights reserved.
 *
 */

#include "IMUSANT_element.h"

namespace IMUSANT
{
    //______________________________________________________________________________
#pragma mark friend constructors
    
    //______________________________________________________________________________
#pragma mark stream operators
    ostream& operator<< (ostream& os, const S_IMUSANT_element& elt)
    {
        elt->print(os);
        return os;
    }
    
    //______________________________________________________________________________
    void IMUSANT_element::accept (IMUSANT_visitor& visitor)
    {
        S_IMUSANT_element ptr(this);
        visitor.visit(ptr);
    }
}
