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

#include "TSound.h"

using namespace MusicXML;

namespace MusicXML 
{
//______________________________________________________________________________
// the new functions
//______________________________________________________________________________
SSound newSound() { TSound * o = new TSound(); assert(o!=0); return o; }
//______________________________________________________________________________
void TSound::init ()
{
	fTempo = undefined;
	fDynamics = undefined;
	fDacapo = YesNo::undefined;
	fSegno = undefined;
	fDalsegno = undefined;
	fCoda = undefined;
	fTocoda = undefined;
	fDivisions = undefined;
	fForwardRepeat = YesNo::undefined;
	fFine = undefined;
	fTimeOnly = undefined;
	fPizzicato = YesNo::undefined;
//	fMidiChannel = undefined;
//	fMidiIntrument = undefined;
	fPan = undefined;
	fElevation = undefined;
	fDamperPedal = YesNo::undefined;
	fSoftPedal = YesNo::undefined;
	fSostenutoPedal = YesNo::undefined;
}

//______________________________________________________________________________
void TSound::setTempo(long tempo)				{ fTempo = tempo; }
void TSound::setDynamics(long dyn)				{ fDynamics = dyn; }
void TSound::setDacapo(YesNo::type yn)			{ fDacapo = yn; }
void TSound::setSegno(long segno)				{ fSegno = segno; }  
void TSound::setDalsegno(long ds)				{ fDalsegno = ds; }
void TSound::setCoda(long coda)					{ fCoda = coda; }
void TSound::setTocoda(long tc)					{ fTocoda = tc; }
void TSound::setDivisions(long div)				{ fDivisions = div; }
void TSound::setForwardRepeat(YesNo::type yn)	{ fForwardRepeat = yn; }
void TSound::setFine(long fine)					{ fFine = fine; }
void TSound::setTimeOnly(long time)				{ fTimeOnly = time; }
void TSound::setPizzicato(YesNo::type pizz)		{ fPizzicato = pizz; }
/*
void TSound::setMidiChannel(long chan)			{ fMidiChannel = chan; }
void TSound::setMidiIntrument(long instr)		{ fMidiIntrument = instr; }
*/
void TSound::setPan(long pan)					{ fPan = pan; }
void TSound::setElevation(long el)				{ fElevation = el; }
void TSound::setDamperPedal(YesNo::type yn)		{ fDamperPedal = yn; }
void TSound::setSoftPedal(YesNo::type yn)		{ fSoftPedal = yn; }
void TSound::setSostenutoPedal(YesNo::type yn)  { fSostenutoPedal = yn; }

//______________________________________________________________________________
void TSound::accept(TScoreVisitor& visitor)
{
	SSound sptr(this);
	visitor.visite(sptr);
}

//______________________________________________________________________________
long TSound::add(const SMidiInstrument& instr)	{ 
	fInstrumentList.push_back(instr);
	return fInstrumentList.size()-1;
}

}
