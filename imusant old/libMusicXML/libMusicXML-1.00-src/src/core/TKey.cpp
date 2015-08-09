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

#include "TKey.h"

using namespace MusicXML;

namespace MusicXML 
{
//______________________________________________________________________________
// the new function
//______________________________________________________________________________
SKey newKey() { TKey * o = new TKey(); assert(o!=0); return o; }
//______________________________________________________________________________
int TKey::fModeTbl[] = { major, minor, dorian, phrygian, lydian, mixolydian, aeolian, ionian, locrian };
string TKey::fModeStrings[]	= { 
    "major", "minor", "dorian", "phrygian", "lydian", "mixolydian", "aeolian", "ionian", "locrian" 
};
bimap<string, int> TKey::fMode2String(fModeStrings, fModeTbl, last);

//______________________________________________________________________________
const string TKey::xmlmode (int d) 		{ return fMode2String[d]; }
int	TKey::xmlmode (const string str) 	{ return fMode2String[str]; }

//______________________________________________________________________________
void TKey::setCancel(long cancel)		{ fCancel = cancel; }
void TKey::setFifths(long fifths)		{ fFifths = fifths; }
void TKey::setMode(long mode)			{ fMode = mode; }
//______________________________________________________________________________
void TKey::accept(TScoreVisitor& visitor)
{
	SKey sptr(this);
	visitor.visite(sptr);
}

}
