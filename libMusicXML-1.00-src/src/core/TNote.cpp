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

#include "TNote.h"
#include "math.h"

using namespace MusicXML;

namespace MusicXML 
{
//______________________________________________________________________________
// the new functions
//______________________________________________________________________________

SMultipleLyricPart newMultipleLyricPart() { TMultipleLyricPart * o = new TMultipleLyricPart(); assert(o!=0); return o; }
SLyric newLyric() { TLyric * o = new TLyric(); assert(o!=0); return o; }
SExpression newExpression() { TExpression * o = new TExpression(); assert(o!=0); return o; }
SAccidental newAccidental() { TAccidental * o = new TAccidental(); assert(o!=0); return o; }
SNoteHead newNoteHead() { TNoteHead * o = new TNoteHead(); assert(o!=0); return o; }
SBeam newBeam() { TBeam * o = new TBeam(); assert(o!=0); return o; }
SGraphNote newGraphNote() { TGraphNote * o = new TGraphNote(); assert(o!=0); return o; }
SGraceNote newGraceNote() { TGraceNote * o = new TGraceNote(); assert(o!=0); return o; }
SNote newNote() { TNote * o = new TNote(); assert(o!=0); return o; }
//______________________________________________________________________________
TLyric::syllabic TLyric::fSyllabicTbl[]		= { single, begin, end, middle };
string TLyric::fSyllabicStrings[] 			= { "single", "begin", "end", "middle" };
bimap<string, TLyric::syllabic> TLyric::fSyllabic2String(fSyllabicStrings, fSyllabicTbl, last);

//______________________________________________________________________________
TAccidental::accident TAccidental::fAccidentTbl[]		
	= { sharp, natural, flat, double_sharp, sharp_sharp, flat_flat,
		natural_sharp, natural_flat, quarter_flat, quarter_sharp,
		three_quarters_flat, three_quarters_sharp };
string TAccidental::fAccidentStrings[]
	= { "sharp", "natural", "flat", "double-sharp", "sharp-sharp", "flat-flat",
	"natural-sharp", "natural-flat", "quarter-flat", "quarter-sharp",
	"three-quarters-flat", "three-quarters-sharp"
};
bimap<string, TAccidental::accident> TAccidental::fAccident2String(fAccidentStrings, fAccidentTbl, last);

//______________________________________________________________________________
void TMultipleLyricPart::accept (TScoreVisitor& visitor) {
	SMultipleLyricPart sptr (this);
	visitor.visite(sptr);
}
void TMultipleLyricPart::setText (const string text)			{ fText = text; }
void TMultipleLyricPart::setSyllabic (TLyric::syllabic syll)	{ fSyllabic = syll; }

//______________________________________________________________________________
void TLyric::accept (TScoreVisitor& visitor) {
	SLyric sptr (this);
	visitor.visite(sptr);
}
void TLyric::setText (const string text)		{ fText = text; }
void TLyric::setSyllabic (syllabic syll)		{ fSyllabic = syll; }
void TLyric::setName(const string name)			{ fName = name; }
void TLyric::setNumber(int number)				{ fNumber = number; }
void TLyric::setExtend(bool extend)				{ fExtend = extend; }
void TLyric::setEndLine(bool el)				{ fEndLine = el; }
void TLyric::setEndParagraph(bool ep)			{ fEndParagraph = ep; }
void TLyric::add (SMultipleLyricPart part)		{ fMultiple.push_back (part); }
void TLyric::setLaughing(bool laugh) {
    if (laugh) fExtend =  fHumming = false; 
    fLaughing = laugh;
}
void TLyric::setHumming(bool hum) {
    if (hum) fExtend =  fLaughing = false; 
    fHumming = hum;
}
 
const string	TLyric::xmlsyllabic (syllabic d)			{ return fSyllabic2String[d]; }
TLyric::syllabic TLyric::xmlsyllabic (const string str)		{ return fSyllabic2String[str]; }

//______________________________________________________________________________
void TExpression::setDynamic(long dyn)		{ fDynamic = dyn; }
void TExpression::setEndDynamic(long dyn) 	{ fEndDynamic = dyn; }
void TExpression::setAttack(long attack)	{ fAttack = attack; }
void TExpression::setRelease(long rel)		{ fRelease = rel; }
void TExpression::setPizzicato(YesNo::type pizz) { fPizzicato = pizz; }


//______________________________________________________________________________
const string TAccidental::xmlaccidental (accident d) 				{ return fAccident2String[d]; }
TAccidental::accident TAccidental::xmlaccidental (const string str) { return fAccident2String[str]; }

//______________________________________________________________________________
void TAccidental::setAccident(accident acc) 		{ fAccident = acc; }
void TAccidental::setCautionary(YesNo::type yn) 	{ fCautionary = yn; }
void TAccidental::setEditorial(YesNo::type yn) 	{ fEditorial = yn; }
void TAccidental::setSize(FullCue::type size) 	{ fSize = size; }
//______________________________________________________________________________
void TAccidental::accept(TScoreVisitor& visitor)
{
	SAccidental sptr (this);
	visitor.visite(sptr);
}

//______________________________________________________________________________
TNoteHead::notehead TNoteHead::fNoteHeadTbl[]		
	= { slash, triangle, diamond, square, cross, x, circle_x, normal, none };
string TNoteHead::fNoteHeadStrings[]
	= { "slash", "triangle", "diamond", "square", "cross", "x", "circle_x", "normal", "none" };
bimap<string, TNoteHead::notehead> TNoteHead::fNoteHead2String(fNoteHeadStrings, fNoteHeadTbl, last);

//______________________________________________________________________________
const string TNoteHead::xmlnotehead (notehead d) 				{ return fNoteHead2String[d]; }
TNoteHead::notehead TNoteHead::xmlnotehead (const string str) 	{ return fNoteHead2String[str]; }

//______________________________________________________________________________
void TNoteHead::setShape(notehead shape)			{ fShape = shape; }
void TNoteHead::setFilled(YesNo::type filled)		{ fFilled = filled; }
void TNoteHead::setParentheses(YesNo::type par)		{ fParentheses = par; }
//______________________________________________________________________________
void TNoteHead::accept(TScoreVisitor& visitor)
{
	SNoteHead sptr (this);
	visitor.visite(sptr);
}

//______________________________________________________________________________
TBeam::beamtype TBeam::fBeamTbl[]	= { beambegin, beamcontinue, beamend, beamforward, beambackward };
string TBeam::fBeamStrings[]		= { "begin", "continue", "end", "forward hook", "backward hook" };
bimap<string, TBeam::beamtype> TBeam::fBeam2String(fBeamStrings, fBeamTbl, last);

//______________________________________________________________________________
const string TBeam::xmlbeamtype (beamtype d) 			{ return fBeam2String[d]; }
TBeam::beamtype	TBeam::xmlbeamtype (const string str) 	{ return fBeam2String[str]; }

//______________________________________________________________________________
void TBeam::setType(beamtype type)		{ fType = type; }
void TBeam::setNumber(int num)			{ fNumber = num; }
void TBeam::setRepeater(YesNo::type r)	{ fRepeater = r; }
//______________________________________________________________________________
void TBeam::accept(TScoreVisitor& visitor)
{
	SBeam sptr (this);
	visitor.visite(sptr);
}

//______________________________________________________________________________
void TExpression::accept(TScoreVisitor& visitor)
{
	SExpression sptr (this);
	visitor.visite(sptr);
}

//______________________________________________________________________________
/*
void TNote::setDuration(unsigned long duration, unsigned unit, unsigned div)
{
	fDuration = duration;
	int basetype = 8 - (int)(log((double)unit)/log((double)2));
	NoteType::type t;
	if (duration >= div) {
		t = (NoteType::type)(1 << (basetype + (duration / div) - 1));
	}
	else {
		t = (NoteType::type)(1 << (basetype - (int)(log((double)(div/ duration))/log((double)2))));
	}
	fGraphNote->setType(t);
}
*/

//________________________________________________________________________
long TNote::getVoice() const
{
	return fGraphNote ? fGraphNote->getVoice() : -1;
}

//________________________________________________________________________
unsigned long TNote::getFullDuration() 
{
    if (isSingle()){ // Normal note : no previous or next "tie"
        return fDuration;
    }else if (isTie()){ // First "tie" note
        unsigned long duration = 0;
        SNote tieNote = this;
        while (tieNote) {
            duration += tieNote->getDuration();
            tieNote = tieNote->tieNext();
        }	
        return duration;
    }
    return fDuration;
}

//______________________________________________________________________________
int TGraphNote::fStemTbl[]				= { stemdown, stemup, stemnone, stemdouble };
string TGraphNote::fStemStrings[]		= { "down", "up", "none", "double" };
bimap<string, int> TGraphNote::fStem2String(fStemStrings, fStemTbl, last);

//______________________________________________________________________________
const string TGraphNote::xmlstem (int d)		{ return fStem2String[d]; }
int	TGraphNote::xmlstem (const string str)		{ return fStem2String[str]; }

//______________________________________________________________________________
void TGraphNote::setVoice(long voice)			{ fVoice = voice; }
void TGraphNote::setType(NoteType::type type) 	{ fType = type; }
void TGraphNote::setSize(FullCue::type size)	{ fSize = size; }
void TGraphNote::setDots(unsigned long dots)	{ fDots = dots; }
void TGraphNote::setStem(long stem)				{ fStem = stem; }
void TGraphNote::setStaff(long staff)			{ fStaff = staff; }
//______________________________________________________________________________
void TGraphNote::accept(TScoreVisitor& visitor)
{
	SGraphNote sptr (this);
	visitor.visite(sptr);
}

//______________________________________________________________________________
void TNote::setDuration (unsigned long dur)	{ fDuration = dur; }
void TNote::setInstrumentID(string id)		{ fInstrumentID = id; }
void TNote::setStyle(style t) 				{ fStyle = t; }
void TNote::setType(type t) 				{ fType = t; }
void TNote::add(SLyric lyric)				{ fLyrics.push_back(lyric); }

//______________________________________________________________________________
void TNote::accept(TScoreVisitor& visitor)
{
	SNote sptr (this);
	visitor.visite(sptr);
}

//______________________________________________________________________________
long TGraphNote::add(const SBeam& beam) { 
	fBeamList.push_back (beam);
	return fBeamList.size()-1;
}
long TGraphNote::add(const SNotation& notation) { 
	fNotationList.push_back (notation);
	return fNotationList.size()-1;
}

//______________________________________________________________________________
void TGraceNote::setStealPrevious(int v)	{ fStealPrevious = v; }
void TGraceNote::setStealFollowing(int v)	{ fStealFollowing = v; }
void TGraceNote::setMakeTime(int v)			{ fMakeTime = v; }
void TGraceNote::setSlash(YesNo::type v)	{ fSlash = v; }
//______________________________________________________________________________
void TGraceNote::accept(TScoreVisitor& visitor)
{
	SGraceNote sptr (this);
	visitor.visite(sptr);
}

}
