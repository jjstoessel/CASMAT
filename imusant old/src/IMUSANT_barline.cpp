/*
 *  IMUSANT_barline.cpp
 *  imusant
 *
 *  Created by Jason Stoessel on 18/06/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "IMUSANT_barline.h"
namespace IMUSANT
{
//ctor functions
S_IMUSANT_ending new_IMUSANT_ending()
		{ IMUSANT_ending* o = new IMUSANT_ending(); assert (o!=0); return o; }
S_IMUSANT_repeat new_IMUSANT_repeat()
		{ IMUSANT_repeat* o = new IMUSANT_repeat(); assert (o!=0); return o; }
S_IMUSANT_barline new_IMUSANT_barline() 
		{ IMUSANT_barline* o = new IMUSANT_barline(); assert(o!=0); return o; }

//===========================================================================+
//IMUSANT_ending
					
IMUSANT_ending::type	IMUSANT_ending::fTypeTbl[] = { undefined, start, stop };						
string	IMUSANT_ending::fTypeStrings[] = { "undefined", "start", "stop" };
bimap<string, IMUSANT_ending::type>	IMUSANT_ending::fType2String(fTypeStrings, fTypeTbl, last);
//! convert a numeric start-stop value to a MusicXML string
const string IMUSANT_ending::xml (IMUSANT_ending::type d) { return fType2String[d]; }
//! convert a MusicXML string to a numeric value
IMUSANT_ending::type	IMUSANT_ending::xml (const string str) { return fType2String[str]; }

//==============================================================================
//IMUSANT_repeat
					
IMUSANT_repeat::direction	IMUSANT_repeat::fDirectionTbl[] = { undefined, forward, backward };						
string	IMUSANT_repeat::fDirectionStrings[] = { "undefined", "forward", "backward" };
bimap<string, IMUSANT_repeat::direction>	IMUSANT_repeat::fDirection2String(fDirectionStrings, fDirectionTbl, last);
//! convert a numeric start-stop value to a MusicXML string
const string IMUSANT_repeat::xml (IMUSANT_repeat::direction d) { return fDirection2String[d]; }
//! convert a MusicXML string to a numeric value
IMUSANT_repeat::direction	IMUSANT_repeat::xml (const string str) { return fDirection2String[str]; }

//==============================================================================
//IMUSANT_barline

IMUSANT_barline::location IMUSANT_barline::fLocationTbl[] 		= { right, left, middle };
string IMUSANT_barline::fLocationStrings[]	= { "right", "left", "middle" };
bimap<string, IMUSANT_barline::location> IMUSANT_barline::fLocation2String(fLocationStrings, fLocationTbl, lastloc);

IMUSANT_barline::type IMUSANT_barline::fStyleTbl[] 			= { none, regular, dotted, heavy, light_light, 
                                        light_heavy, heavy_light, heavy_heavy };
string IMUSANT_barline::fStyleStrings[]	= { "none", "regular", "dotted", "heavy", "light-light", 
                                        "light-heavy", "heavy-light", "heavy-heavy" };
bimap<string, IMUSANT_barline::type> IMUSANT_barline::fStyle2String(fStyleStrings, fStyleTbl, last);

//______________________________________________________________________________
void IMUSANT_barline::setLocation(location loc)		{ fLocation = loc; }
void IMUSANT_barline::setBarStyle(type style)	{ fBarStyle = style; }
//______________________________________________________________________________
const string IMUSANT_barline::xmllocation (location d) 		{ return fLocation2String[d]; }
IMUSANT_barline::location IMUSANT_barline::xmllocation (const string str) 	{ return fLocation2String[str]; }
const string IMUSANT_barline::xmlstyle (type d) 		{ return fStyle2String[d]; }
IMUSANT_barline::type IMUSANT_barline::xmlstyle (const string str) 		{ return fStyle2String[str]; }

//______________________________________________________________________________
void IMUSANT_barline::accept(IMUSANT_visitor& visitor)
{
	S_IMUSANT_barline sptr(this);
	visitor.visit(sptr);
}

}//namespace IMUSANT
