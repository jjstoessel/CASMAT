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

S_IMUSANT_chord new_IMUSANT_chord() { IMUSANT_chord* o = new IMUSANT_chord(); assert(o!=0); return o; }

//------------------------------------------------------------------------------
// Acceptor function
//------------------------------------------------------------------------------
void IMUSANT_chord::accept(IMUSANT_visitor& visitor)
{
	S_IMUSANT_chord sptr(this);
	visitor.visit(sptr);
}

void IMUSANT_chord::print(ostream& os)
{
	os << "<CHRD>" << endl;
	
	for (vector<S_IMUSANT_note>::const_iterator note=fChordNotes.begin(); note!=fChordNotes.end(); note++)
	{
		(*note)->print(os);
	}
	
	os << "<\\CHRD>" << endl;
}

}//namespace IMUSANT