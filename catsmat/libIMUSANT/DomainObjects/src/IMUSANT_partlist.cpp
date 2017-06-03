/*
 *  IMUSANT_partlist.cpp
 *  imusant
 *
 *  Created by Jason Stoessel on 23/05/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "IMUSANT_partlist.h"

namespace IMUSANT
{

S_IMUSANT_partlist new_IMUSANT_partlist() 
		{ IMUSANT_partlist* o = new IMUSANT_partlist(); assert (o!=0); return o; }

//------------------------------------------------------------------------------
// Stream out overloader		
ostream& operator<<(ostream& os, S_IMUSANT_partlist& partlist)
{
	partlist->print(os);
	
	return os;
}

//------------------------------------------------------------------------------
void IMUSANT_partlist::accept(IMUSANT_visitor& visitor)
{
	S_IMUSANT_partlist sptr(this);
	visitor.visit(sptr);
}

//------------------------------------------------------------------------------
S_IMUSANT_part&	IMUSANT_partlist::getPart(const string& ID)
{
	vector<S_IMUSANT_part>::iterator iter;
	
	for ( iter = fPartsList.begin(); iter != fPartsList.end(); iter++ )
	{
		if ( ID == (*iter)->getID() )
			break;
	}
	
	return *iter;
}

void IMUSANT_partlist::print(ostream& os)
{
	for (vector<S_IMUSANT_part>::const_iterator part=fPartsList.begin(); part !=fPartsList.end(); part++)
	{
		(*part)->print(os);
	}
}

} //namespace IMUSANT