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

#include "TBackupForward.h"
#include "TScorePartwise.h"
#include "TNote.h"
#include "TChord.h"

using namespace MusicXML;

namespace MusicXML 
{
//______________________________________________________________________________
// the new functions
//______________________________________________________________________________
SPWMeasure newPWMeasure(string num) { TPWMeasure * o = new TPWMeasure(num); assert(o!=0); return o; }
SPWMeasure newPWMeasure(long num)   { TPWMeasure * o = new TPWMeasure(num); assert(o!=0); return o; }
SPWPart newPWPart(string id) { TPWPart * o = new TPWPart(id); assert(o!=0); return o; }
SScorePartwise newScorePartwise() { TScorePartwise * o = new TScorePartwise(); assert(o!=0); return o; }

//______________________________________________________________________________
TPWMeasure::TPWMeasure(string num) : TMeasure(num) {}
TPWMeasure::TPWMeasure(long num) : TMeasure(num) {}
TPWMeasure::~TPWMeasure() {}
//______________________________________________________________________________
void TPWMeasure::accept(TScoreVisitor& visitor) {
	SPWMeasure sptr(this);
	visitor.visite(sptr);
}

//______________________________________________________________________________
unsigned long TPWMeasure::getDuration(long voice) {
	vvector<SMusicData>::const_iterator elt;
	unsigned long duration = 0; long currentVoice=-1;
	bool voiceset=false;
	
	for (elt=data().begin(); elt!=data().end(); elt++) {
		SNote note;
		SChord chord;
		SForward forw;
		chord.cast((TMusicData *)(*elt));
		note.cast((TMusicData *)(*elt));
		forw.cast((TMusicData *)(*elt));
		if (chord && ((voice==allVoices) || (chord->getVoice()==voice))) {
			if (chord->getStyle() != TNote::normal) continue;
			if (voiceset) {
				if (chord->getVoice() != currentVoice) continue;
				duration +=   chord->getDuration();
			}
			else {
				currentVoice = chord->getVoice();
				duration +=   chord->getDuration();
				voiceset = true;
			}
		}
		else if (note && ((voice==allVoices) || (note->getVoice()==voice))) {
			if (note->getStyle() != TNote::normal) continue;
			if (voiceset) {
				if (note->graphics() && (note->graphics()->getVoice() != currentVoice)) continue;
				duration +=   note->getDuration();				
			}
			else {
				if (note->graphics())
					currentVoice = note->graphics()->getVoice();
				duration +=   note->getDuration();				
				voiceset = true;
			}
		}
		else if (forw && ((voice==allVoices) || (forw->getVoice()==voice))) {
			duration +=  forw->getDuration();
		}
	}
	return duration;
}

//______________________________________________________________________________
TPWPart::TPWPart(const string& id) : TPart(id) {}
TPWPart::~TPWPart() {}
//______________________________________________________________________________
void TPWPart::accept(TScoreVisitor& visitor) {
	SPWPart sptr(this);
	visitor.visite(sptr);
}

//______________________________________________________________________________
TScorePartwise::TScorePartwise ()
{
	fHeader = new_xmlheader(xmlheader::partwise);
}
TScorePartwise::~TScorePartwise() {}

//______________________________________________________________________________
void TScorePartwise::accept(TScoreVisitor& visitor) {
	SScorePartwise sptr(this);
	visitor.visite(sptr);
}

//______________________________________________________________________________
long TScorePartwise::add(const SPWPart& part)
{ 
	fPartList.push_back (part); 
	return fPartList.size()-1;
}

//______________________________________________________________________________
long TPWPart::add (const SPWMeasure& measure) 
{ 
	fMeasures.push_back(measure); 
	return fMeasures.size()-1;
}

//______________________________________________________________________________
long TPWMeasure::add (const SMusicData& data) 
{ 
	fData.push_back(data); 
	return fData.size()-1;
}

}
