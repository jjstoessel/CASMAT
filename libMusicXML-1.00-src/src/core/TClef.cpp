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

#include "TClef.h"

using namespace MusicXML;

namespace MusicXML 
{
//______________________________________________________________________________
// the new functions
//______________________________________________________________________________
SClef newClef() { TClef * o = new TClef(); assert(o!=0); return o; }
//______________________________________________________________________________
int TClef::fClefTbl[]			= { none, G, F, C, percussion, TAB };
string TClef::fClefStrings[]	= { "none", "G", "F", "C", "percussion", "TAB" };
bimap<string, int> TClef::fClef2String(fClefStrings, fClefTbl, last);

//______________________________________________________________________________
const string TClef::xmlsign (int d) 	{ return fClef2String[d]; }
int TClef::xmlsign (const string str) 	{ return fClef2String[str]; }

//______________________________________________________________________________
void TClef::setStaffNum 	(long num)	{ fNum = num; }
void TClef::setSign 		(long sign)	{ fSign = sign; }
void TClef::setLine 		(long line)	{ fLine = line; }
void TClef::setOctave 		(long oct)	{ fOctave = oct; }
//______________________________________________________________________________
void TClef::accept(TScoreVisitor& visitor)
{
	SClef sptr (this);
	visitor.visite(sptr);
}

}
