/*

  MusicXML Library
  Copyright (C) 2004  Grame

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
  research@grame.fr

*/

#include "TStaffDetails.h"

using namespace MusicXML;

namespace MusicXML 
{

//______________________________________________________________________________
// the new functions
//______________________________________________________________________________
SStaffTuning newStaffTuning(int line)   { TStaffTuning * o = new TStaffTuning(line); assert(o!=0); return o; }
SStaffDetails newStaffDetails()			{ TStaffDetails * o = new TStaffDetails(); assert(o!=0); return o; }

//______________________________________________________________________________
TStaffDetails::type TStaffDetails::fTypeTbl[]	= { ossia, cue, editorial, regular, alternate };
string TStaffDetails::fTypeStrings[]	= { "ossia", "cue", "editorial", "regular", "alternate" };
bimap<string, TStaffDetails::type> TStaffDetails::fType2String(fTypeStrings, fTypeTbl, last);

const string TStaffDetails::xml (type d)					{ return fType2String[d]; }
TStaffDetails::type	TStaffDetails::xml (const string str)   { return fType2String[str]; }

//______________________________________________________________________________
void TStaffDetails::accept(TScoreVisitor& visitor) { SStaffDetails sptr(this); visitor.visite(sptr); }
void TStaffTuning::accept(TScoreVisitor& visitor) { SStaffTuning sptr(this); visitor.visite(sptr); }

void TStaffDetails::setType(type t)			{ fType = t; }
void TStaffDetails::setNumber(int n)		{ fNumber = n; }
void TStaffDetails::setShowFret(int t)		{ fShowFrets = t; }
void TStaffDetails::setLines(int n)			{ fLines = n; }
void TStaffDetails::setCapo(const string& capo)			{ fCapo = capo; }
void TStaffDetails::add(SStaffTuning st)	{ fTuning.push_back(st); }

}
