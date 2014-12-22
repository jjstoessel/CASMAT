/*
 *  IMUSANT_comment.cpp
 *  imusant
 *
 *  Created by Jason Stoessel on 23/05/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "IMUSANT_comment.h"

namespace IMUSANT
{

S_IMUSANT_comment new_IMUSANT_comment(string name) 
		{ IMUSANT_comment* o = new IMUSANT_comment(name); assert (o!=0); return o; }
		
//______________________________________________________________________________
void IMUSANT_comment::accept (IMUSANT_visitor& visitor)
{
	S_IMUSANT_comment ptr(this);
	visitor.visit(ptr);
}

void IMUSANT_comment::print(ostream& os)
{
	os << "<COM>" << fComment << "<\\COM>" << endl;
}

} //namespace IMUSANT
