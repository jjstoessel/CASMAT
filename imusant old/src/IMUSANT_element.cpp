/*
 *  IMUSANT_element.cpp
 *  imusant
 *
 *  Created by Jason Stoessel on 22/03/06.
 *  Copyright 2006 Jason Stoessel. All rights reserved.
 *
 */

#include "IMUSANT_element.h"
#include "IMUSANT_note.h"
#include "IMUSANT_chord.h"
#include "IMUSANT_comment.h"

namespace IMUSANT
{
//______________________________________________________________________________
#pragma mark friend constructors
//S_IMUSANT_element new_IMUSANT_element()	
//		{ IMUSANT_element * o = new IMUSANT_element(); assert(o!=0); return o; }

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

void IMUSANT_element::print(ostream& os) const
{
	if (dynamic_cast<const IMUSANT_note*>(this)) 
	{
		S_IMUSANT_note note;
		note.cast((IMUSANT_note*)this);
		note->print(os);
	}
	
	if (dynamic_cast<const IMUSANT_chord*>(this)) 
	{
		S_IMUSANT_chord chord;
		chord.cast((IMUSANT_chord*)this);
		chord->print(os);
	}
	
	if (dynamic_cast<const IMUSANT_comment*>(this))
	{
		S_IMUSANT_comment comment;
		comment.cast((IMUSANT_comment*)this);
		comment->print(os);
	}
}

}
