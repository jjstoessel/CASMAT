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

#include "TTechnical.h"
#include <string>

using namespace MusicXML;
using namespace std;

namespace MusicXML 
{
//______________________________________________________________________________
// the new functions
//______________________________________________________________________________
STechnicals newTechnicals() { TTechnicals * o = new TTechnicals(); assert(o!=0); return o; }
STechnical newTechnical(TTechnical::type t)   { TTechnical * o = new TTechnical(t); assert(o!=0); return o; }
SHarmonic newHarmonic()		{ THarmonic * o = new THarmonic(); assert(o!=0); return o; }
SHammerPull newHammerPull(bool h) { THammerPull * o = new THammerPull(StartStop::undefined,h); assert(o!=0); return o; }
SBendWithBar newBendWithBar() { TBendWithBar * o = new TBendWithBar(); assert(o!=0); return o; }
SBend newBend()				{ TBend * o = new TBend(); assert(o!=0); return o; }
SFingering newFingering() { TFingering * o = new TFingering(); assert(o!=0); return o; }
//______________________________________________________________________________
TTechnical::type 
TTechnical::fTypeTbl[]	= { up_bow, down_bow, harmonic, open_string,
					thumb_position, fingering, double_tongue, triple_tongue, stopped, snap_pizzicato,
					fret, _string, hammer_on, pull_off, bend, tap, heel, toe, fingernails, 
					other_technical };
string TTechnical::fTypeStrings[]	= { 
				"up-bow", "down-bow", "harmonic", "open-string",
					"thumb-position", "fingering", "double-tongue", "triple-tongue", "stopped", "snap-pizzicato",
					"fret", "string", "hammer-on", "pull-off", "bend", "tap", "heel", "toe", "fingernails", 
					"other-technical" };
bimap<string, TTechnical::type> TTechnical::fType2String(fTypeStrings, fTypeTbl, last);

const string		TTechnical::xml (TTechnical::type d)	{ return fType2String[d]; }
TTechnical::type	TTechnical::xml (const string str)   { return fType2String[str]; }
void TTechnical::setType(TTechnical::type t)					{ fType = t; }
void TTechnicals::add(const STechnical& elt) { fTechnicals.push_back(elt); }

//______________________________________________________________________________
THarmonic::harmonict THarmonic::fHarmonicTbl[]	= { natural, artificial };
string THarmonic::fHarmonicStrings[]	= { "natural", "artificial" };
bimap<string, THarmonic::harmonict> THarmonic::fHarmonic2String(fHarmonicStrings, fHarmonicTbl, artificial);

THarmonic::pitch THarmonic::fPitchTbl[]	= { base_pitch, touching_pitch, sounding_pitch };
string THarmonic::fPitchStrings[]	= { "base-pitch", "touching-pitch", "sounding-pitch" };
bimap<string, THarmonic::pitch> THarmonic::fPitch2String(fPitchStrings, fPitchTbl, sounding_pitch);

const string		THarmonic::xmlHarmonic (harmonict d)			{ return fHarmonic2String[d]; }
THarmonic::harmonict THarmonic::xmlHarmonic (const string str)   { return fHarmonic2String[str]; }
const string		THarmonic::xmlPitch (pitch d)			{ return fPitch2String[d]; }
THarmonic::pitch	THarmonic::xmlPitch (const string str)  { return fPitch2String[str]; }

//______________________________________________________________________________
void TFingering::setSubstitution(YesNo::type sub)		{ fSubstitution = sub; }
void TFingering::setAlternate(YesNo::type alt)  		{ fAlternate = alt; }
void TFingering::setData(const std::string& data)		{ fData = data; }

//______________________________________________________________________________
void TTechnical::accept(TScoreVisitor& visitor)		{ STechnical sptr (this); visitor.visite(sptr); }
void TTechnicals::accept(TScoreVisitor& visitor)	{ STechnicals sptr (this); visitor.visite(sptr); }
void THarmonic::accept(TScoreVisitor& visitor)		{ SHarmonic sptr (this); visitor.visite(sptr); }
void THammerPull::accept(TScoreVisitor& visitor)	{ SHammerPull sptr (this); visitor.visite(sptr); }
void TBendWithBar::accept(TScoreVisitor& visitor)   { SBendWithBar sptr (this); visitor.visite(sptr); }
void TBend::accept(TScoreVisitor& visitor)			{ SBend sptr (this); visitor.visite(sptr); }
void TFingering::accept(TScoreVisitor& visitor)		{ SFingering sptr(this);visitor.visite (sptr); }

}
