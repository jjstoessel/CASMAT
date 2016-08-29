/*

  MusicXML Library
  Copyright (C) 2003  Grame

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  grame@grame.fr

*/

#include "TBarline.h"

using namespace MusicXML;

namespace MusicXML 
{
//______________________________________________________________________________
// the new functions
//______________________________________________________________________________
SEnding newEnding(long num, int type) { TEnding * o = new TEnding(num, type); assert(o!=0); return o; }
SRepeat newRepeat(int direction) { TRepeat * o = new TRepeat(direction); assert(o!=0); return o; }
SBarline newBarline() { TBarline * o = new TBarline(); assert(o!=0); return o; }


//______________________________________________________________________________
void TEnding::setNum (long num)		{ fNum = num; }
void TEnding::setType(int type)		{ fType = type; }
//______________________________________________________________________________
int TEnding::fTypeTbl[] 		= { start, stop, discontinue };
string TEnding::fTypeStrings[]	= { "start", "stop", "discontinue" };
bimap<string, int> TEnding::fType2String(fTypeStrings, fTypeTbl, last);

//______________________________________________________________________________
const string TEnding::xmltype (int d)		{ return fType2String[d]; }
int TEnding::xmltype (const string str)		{ return fType2String[str]; }

//______________________________________________________________________________
void TEnding::accept(TScoreVisitor& visitor)
{
	SEnding sptr(this);
	visitor.visite(sptr);
}

//______________________________________________________________________________
void TRepeat::setDirection(int dir)	{ fDirection = dir; }
void TRepeat::setTimes(int times)	{ fTimes = times; }
//______________________________________________________________________________
int TRepeat::fDirectionTbl[] 		= { backward, forward };
string TRepeat::fDirectionStrings[]	= { "backward", "forward" };
bimap<string, int> TRepeat::fDirection2String(fDirectionStrings, fDirectionTbl, last);

//______________________________________________________________________________
const string TRepeat::xmldirection (int d)		{ return fDirection2String[d]; }
int TRepeat::xmldirection (const string str)	{ return fDirection2String[str]; }

//______________________________________________________________________________
void TRepeat::accept(TScoreVisitor& visitor)
{
	SRepeat sptr(this);
	visitor.visite(sptr);
}

//______________________________________________________________________________
int TBarline::fLocationTbl[] 		= { right, left, middle };
string TBarline::fLocationStrings[]	= { "right", "left", "middle" };
bimap<string, int> TBarline::fLocation2String(fLocationStrings, fLocationTbl, lastloc);

int TBarline::fStyleTbl[] 			= { none, regular, dotted, heavy, light_light, 
                                        light_heavy, heavy_light, heavy_heavy };
string TBarline::fStyleStrings[]	= { "none", "regular", "dotted", "heavy", "light-light", 
                                        "light-heavy", "heavy-light", "heavy-heavy" };
bimap<string, int> TBarline::fStyle2String(fStyleStrings, fStyleTbl, last);

//______________________________________________________________________________
void TBarline::setLocation(int loc)		{ fLocation = loc; }
void TBarline::setBarStyle(int style)	{ fBarStyle = style; }
//______________________________________________________________________________
const string TBarline::xmllocation (int d) 		{ return fLocation2String[d]; }
int TBarline::xmllocation (const string str) 	{ return fLocation2String[str]; }
const string TBarline::xmlstyle (int d) 		{ return fStyle2String[d]; }
int TBarline::xmlstyle (const string str) 		{ return fStyle2String[str]; }

//______________________________________________________________________________
void TBarline::accept(TScoreVisitor& visitor)
{
	SBarline sptr(this);
	visitor.visite(sptr);
}

}
