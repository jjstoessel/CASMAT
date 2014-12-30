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

#include "TChord.h"
#include <algorithm>

using namespace MusicXML;

namespace MusicXML 
{

//______________________________________________________________________________
/*! \internal
*/
class ShortNoteLess {
	public:
		bool operator() (const SNote& n1, const SNote& n2);
};

/*! \internal
*/
class LowPitchLess {
	public:
		bool operator() (const SNote& n1, const SNote& n2);
};
//______________________________________________________________________________
// the new functions
//______________________________________________________________________________
SChord newChord() { TChord * o = new TChord(); assert(o!=0); return o; }
    
//______________________________________________________________________________
void TChord::accept(TScoreVisitor& visitor)
{
	SChord sptr (this);
	visitor.visite(sptr);
}

//______________________________________________________________________________
bool ShortNoteLess::operator() (const SNote& n1, const SNote& n2)
{
	return n1->getDuration() < n2->getDuration();
}

//______________________________________________________________________________
bool LowPitchLess::operator() (const SNote& n1, const SNote& n2)
{
	if (!(TPitch *)n1->pitch() || !(TPitch *)n2->pitch()) return false;
	return n1->pitch()->MIDIPitch() < n2->pitch()->MIDIPitch();
}

//______________________________________________________________________________
TNote::style TChord::getStyle () const
{
	vvector<SNote>::const_iterator note = fNotes.begin();
	if (note != fNotes.end()) return (*note)->getStyle();
	return TNote::normal;
}

//______________________________________________________________________________
long TChord::getVoice () const
{
	vvector<SNote>::const_iterator note = fNotes.begin();
	long voice = TGraphNote::undefined;
	
	if (note != fNotes.end() && (*note)->graphics())
		voice = (*note)->graphics()->getVoice();
	return voice;
}

//______________________________________________________________________________
long TChord::getStaff () const
{
	vvector<SNote>::const_iterator note = fNotes.begin();
	long staff = TGraphNote::undefined;
	
	if (note != fNotes.end() && (*note)->graphics())
		staff = (*note)->graphics()->getStaff();
	return staff;
}

//______________________________________________________________________________
unsigned long TChord::getDuration () const
{
	vvector<SNote>::const_iterator note = fNotes.begin();
	if (note == fNotes.end()) return 0;

	unsigned long duration = (*note)->getDuration();
	while (++note!=fNotes.end()) {
		if ((*note)->getDuration() < duration)
			duration = (*note)->getDuration();
	}
	return duration;
}

//______________________________________________________________________________
long TChord::add(const SNote& note) { 
	fNotes.push_back(note);
	return fNotes.size()-1;
}

//______________________________________________________________________________
void TChord::sort (sorttype type)
{
	switch (type) {
		case pitch:
			std::sort(fNotes.begin(), fNotes.end(), LowPitchLess());
			break;
		case duration:
			std::sort(fNotes.begin(), fNotes.end(), ShortNoteLess());
			break;
	}
}

}
