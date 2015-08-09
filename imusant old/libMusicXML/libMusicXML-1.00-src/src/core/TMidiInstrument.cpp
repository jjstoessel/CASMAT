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

#include "TMidiInstrument.h"

using namespace MusicXML;
using namespace std;

namespace MusicXML 
{
//______________________________________________________________________________
// the new functions
//______________________________________________________________________________
SMidiInstrument newMidiInstrument(std::string id) {
    TMidiInstrument * o = new TMidiInstrument(id); assert(o!=0); return o;
}
//______________________________________________________________________________
void TMidiInstrument::setID (const std::string& id)		{ fID = id; }
void TMidiInstrument::setChannel (long chan)			{ fMidiChannel = chan; }
void TMidiInstrument::setName (const std::string& name)	{ fMidiName = name; }
void TMidiInstrument::setBank (long bank)				{ fMidiBank = bank; }
void TMidiInstrument::setProgram (long prog)			{ fMidiProgram = prog; }
//______________________________________________________________________________
void TMidiInstrument::accept(TScoreVisitor& visitor)
{
	SMidiInstrument sptr(this);
	visitor.visite(sptr);
}

} // namespace
