/*
 *  IMUSANT_element.h
 *  imusant - the Intertextual MUSic ANalysis Tool
 *	Project Supervisor: Dr Rex Eakins
 *
 *  Created by Jason Stoessel on 22/03/06.
 *
 *  Copyright 2006 Jason Stoessel. All rights reserved.
 *
 Notes:
 These are the internal data structures of IMUSANT
 Changes:
 4 May 2006: - After consulation with supervisor, it was decided that the model should implement an extensible
 hierarchical model for data containment.  Although some of the elements of MusicXML will be excluded
 from the present model, this represents the more complex but ultimately powerful implementation.
 - basic MusicXML parsing is being obtained from the Grame MusicXML Library via the TXML2IMUSANTVisitor class
 although heirarchical container class is still in coding phase.
 */

#ifndef __IMUSANT_element__
#define __IMUSANT_element__

#include "exports.h"
#include "smartpointer.h"
#include "IMUSANT_visitor.h"

#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <stack>

using namespace std;

namespace IMUSANT
{
    
    class IMUSANT_visitor;
    class IMUSANT_element;
    
    VEXP ostream& operator<< (ostream& os, const SMARTP<IMUSANT_element>& elt);
    
    
    /*!
     \brief A generic IMUSANT element base clase.
     
     */
    class VEXP IMUSANT_element : public smartable, public IMUSANT_visitable
    {
    public:
        
        virtual void print (ostream& os) const { os << "IMUSANT_element::print()" << endl;};
        virtual void print_short(ostream& os) const { os << "IMUSANT_element::print_short()" << endl;};
        
        virtual void accept(IMUSANT_visitor& visitor);
        
    protected:
        
        IMUSANT_element() {}
        virtual ~IMUSANT_element() {}
    };
    
    typedef SMARTP<IMUSANT_element> S_IMUSANT_element;
    
} //namespace IMUSANT
/*! @} */


#endif
