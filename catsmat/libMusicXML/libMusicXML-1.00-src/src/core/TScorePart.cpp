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

#include "TScorePart.h"

using namespace MusicXML;

namespace MusicXML 
{
    
//______________________________________________________________________________
// the new function
//______________________________________________________________________________
SScorePart newScorePart(string id) { TScorePart * o = new TScorePart(id); assert(o!=0); return o; }
//______________________________________________________________________________
void TScorePart::setID(const string& id)				{ fID= id; }
void TScorePart::setPartName(const string& name)		{ fPartName = name; }
void TScorePart::setPartAbbrev(const string& abbrev) 	{ fPartAbbrev = abbrev; }
//______________________________________________________________________________
void TScorePart::accept(TScoreVisitor& visitor)
{
	SScorePart sptr(this);
	visitor.visite(sptr);
}

//______________________________________________________________________________
long TScorePart::add(const SScoreInstrument& instr)	{ 
	fScoreInstrumentList.push_back(instr); 
	return fScoreInstrumentList.size()-1;
}

long TScorePart::add(const SMidiInstrument& instr)	{ 
	fMidiInstrumentList.push_back(instr); 
	return fMidiInstrumentList.size()-1;
}

}
