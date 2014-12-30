/*
  Copyright © Grame 2003

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

    Grame Research Laboratory, 9, rue du Garet 69001 Lyon - France
    grame@grame.fr

*/

#include "TScanVisitor.h"
#include "LibMusicXML.h"


#define debug	 // cout << "visite " << __LINE__ << endl; fflush(stdout);


//________________________________________________________________________
SPartSummary newPartSummary(const string & id)	{ TPartSummary * o = new TPartSummary(id); assert(o!=0); return o; }

TPartSummary::TPartSummary(const string& id) : fID(id) {}
TPartSummary::~TPartSummary() {}


//________________________________________________________________________
long TPartSummary::getStaff (long index) const
{
	long staff = 0;
	map<long, long>::const_iterator v = fIndexes.begin();
	do {
		if (v == fIndexes.end()) return 0;
		staff = v->first;
		v++;
	} while (index--);
	return staff;
}

//________________________________________________________________________
long TPartSummary::getMainStaff (long voice)
{
	long mainstaff = 0, n = 0;
    long staves = countStaves();
    for (long i=0; i<staves; i++) {
        long staff = getStaff(i);
        long count = countNotes(voice, staff);
        if (count > n) {
            n = count;
            mainstaff = staff;
        }
    }
	return mainstaff;
}

//________________________________________________________________________
long TPartSummary::getVoice (long index) const
{
	long voice = 0;
	map<long, map<long,long> >::const_iterator v = fVoices.begin();
	do {
		if (v == fVoices.end()) return 0;
		voice = v->first;
		v++;
	} while (index--);
	return voice;
}

//________________________________________________________________________
long TPartSummary::countVoices (long staff) 
{
    long voices = 0;
	map<long, map<long,long> >::iterator v;
	for (v=fVoices.begin(); v!=fVoices.end(); v++) {
        if (v->second[staff])
            voices++;
    }
	return voices;
}

//________________________________________________________________________
long TPartSummary::countVoiceNotes (long voice)
{
    long count = 0;
	map<long, long>& smap = fVoices[voice];
	map<long, long>::const_iterator s;
	for (s=smap.begin(); s!=smap.end(); s++) {
        count += s->second;
    }
	return count;
}

//________________________________________________________________________
long TPartSummary::countStaffNotes (long staff)
{
    long count = 0;
	map<long, map<long,long> >::iterator v;
	for (v=fVoices.begin(); v!=fVoices.end(); v++) {
            count += v->second[staff];
    }
	return count;
}

//________________________________________________________________________
TScanVisitor::TScanVisitor() : fCurrentStaffIndex(0) {}
TScanVisitor::~TScanVisitor() {}
//________________________________________________________________________
void TScanVisitor::visite ( SPWPart& elt )
{
debug
	string id = elt->getID();
	SPartSummary ps = newPartSummary(id);
	fParts[id] = ps;
	fCurrent = ps;
	TRoutedVisitor::visite (elt);
}

//________________________________________________________________________
void TScanVisitor::visite ( SNote& elt ) 
{
debug
	long voice = TGraphNote::undefined;
	int staff  = TGraphNote::undefined;
	if (elt->graphics()) {
		voice = elt->graphics()->getVoice();
		staff  = elt->graphics()->getStaff();
	}

	if (elt->getStyle() == TNote::normal) {
		fCurrent->incVoice (voice, staff);
		if (!fCurrent->getStaffIndex(staff)) 
			fCurrent->setStaff(staff, ++fCurrentStaffIndex);
	}
	else if (elt->getStyle() == TNote::cue) {
		fCurrent->incCue(staff);
	}
}
