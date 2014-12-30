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

#include "common.h"

using namespace std;
using namespace MusicXML;


namespace MusicXML 
{
//______________________________________________________________________________
// the new functions
//______________________________________________________________________________
SFermata newFermata() { TFermata * o = new TFermata(); assert(o!=0); return o; }
SSegno newSegno() { TSegno * o = new TSegno(); assert(o!=0); return o; }
SCoda newCoda() { TCoda * o = new TCoda(); assert(o!=0); return o; }
SDynamic newDynamic() { TDynamic * o = new TDynamic(); assert(o!=0); return o; }

SPCData newPCData(const std::string eltname)  { TPCData * o = new TPCData(eltname); assert(o!=0); return o; }
SFootnote newFootnote()		{ TFootnote * o = new TFootnote(); assert(o!=0); return o; }
SVoice newVoice()			{ TVoice * o = new TVoice(); assert(o!=0); return o; }
SLevel newLevel()			{ TLevel * o = new TLevel(); assert(o!=0); return o; }

TPrintout::TPrintout() : fObject(YesNo::undefined), fDot(YesNo::undefined), fSpacing(YesNo::undefined) {}
TBezier::TBezier() : fOffset(undefined), fOffset2(undefined),
fX(undefined), fY(undefined), fX2(undefined), fY2(undefined) {}

//--------------------------------------------------------------------------------
// static declarations, used to provide conversion between strings and constants
//--------------------------------------------------------------------------------
TDynamic::dynamic TDynamic::fDynamicTbl[] ={ 	
	pppppp, ppppp, pppp, ppp, pp, p,
	mp, mf,
	f, ff, fff, ffff, fffff, ffffff, 
	sf, sfp, sfpp, fp, rf, rfz, sfz, sffz, fz
};
string TDynamic::fDynamicStrings[] = {
	"pppppp", "ppppp", "pppp", "ppp", "pp", "p",
	"mp", "mf",
	"f", "ff", "fff", "ffff", "fffff", "ffffff", 
	"sf", "sfp", "sfpp", "fp", "rf", "rfz", "sfz", "sffz", "fz"
};
bimap<string, TDynamic::dynamic> TDynamic::fDynamic2String(fDynamicStrings, fDynamicTbl, last);

const string TDynamic::xmldynamic (dynamic d) { return fDynamic2String[d]; }
TDynamic::dynamic TDynamic::xmldynamic (const string str) { return fDynamic2String[str]; }

//______________________________________________________________________________
int TPosition::fPosTbl[] = { defaultx, defaulty, relativex, relativey };
string 	TPosition::fPosStrings[] = {
    "default-x", "default-y", "relative-x", "relative-y"
};
bimap<string, int> TPosition::fPos2String(fPosStrings, fPosTbl, last);

const string TPosition::xmlpos (int d) 			{ return fPos2String[d]; }
int	TPosition::xmlpos (const string str)		{ return fPos2String[str]; }

//______________________________________________________________________________
int TPlacement::fPlaceTbl[]			= { above, below };
string TPlacement::fPlaceStrings[]	= { "above", "below" };
bimap<string, int> TPlacement::fPlace2String(fPlaceStrings, fPlaceTbl, last);

const string TPlacement::xmlplace (int d) 		{ return fPlace2String[d]; }
int	TPlacement::xmlplace (const string str) 	{ return fPlace2String[str]; }

//______________________________________________________________________________
int TOrientation::fOrTbl[]			= { over, under };
string TOrientation::fOrStrings[]	= { "over", "under" };
bimap<string, int> TOrientation::fOr2String(fOrStrings, fOrTbl, last);

const string TOrientation::xmlorientation (int d) 		{ return fOr2String[d]; }
int TOrientation::xmlorientation (const string str) 	{ return fOr2String[str]; }

//______________________________________________________________________________
int TFermata::fTypeTbl[]			= { upright, inverted };
string TFermata::fTypeStrings[]		= { "upright", "inverted" };
bimap<string, int> TFermata::fType2String(fTypeStrings, fTypeTbl, last);

const string TFermata::xmltype (int d) 		{ return fType2String[d]; }
int	TFermata::xmltype (const string str) 	{ return fType2String[str]; }

//______________________________________________________________________________
void TTrillSound::setStartNote (TrillStart::type start) { fStartNote = start; }
void TTrillSound::setTrillStep (TrillStep::type step)   { fTrillStep = step; }
void TTrillSound::setTwoNoteTurn (TrillStep::type tnt)  { fTwoNoteTurn = tnt; }
void TTrillSound::setAccelerate (YesNo::type yn)		{ fAccelerate = yn; }
void TTrillSound::setBeat (int beat)			{ fBeats = beat; }
void TTrillSound::setSecondBeat (int beat)		{ fSecondBeat = beat; }
void TTrillSound::setLastBeat (int beat)		{ fLastBeat = beat; }

//______________________________________________________________________________
void TBendSound::setAccelerate (YesNo::type yn){ fAccelerate = yn; }
void TBendSound::setBeat (int beat)				{ fBeats = beat; }
void TBendSound::setFirstBeat (int beat)		{ fFirstBeat = beat; }
void TBendSound::setLastBeat (int beat)			{ fLastBeat = beat; }

//______________________________________________________________________________
void TPosition::accept(TScoreVisitor& visitor)  {	visitor.visite (this); }
void TPlacement::accept(TScoreVisitor& visitor) {	visitor.visite (this); }
void TOrientation::accept(TScoreVisitor& visitor) {	visitor.visite (this); }
void TTrillSound::accept(TScoreVisitor& visitor) {	visitor.visite (this); }
void TBendSound::accept(TScoreVisitor& visitor) {	visitor.visite (this); }
void TFont::accept(TScoreVisitor& visitor)		{	visitor.visite (this); }
void TPrintout::accept(TScoreVisitor& visitor)  { visitor.visite (this); }
void TEditorial::accept(TScoreVisitor& visitor) { visitor.visite (this); }
void TBezier::accept(TScoreVisitor& visitor)	{ visitor.visite (this); }

void TPCData::accept(TScoreVisitor& visitor)	{ SPCData sptr(this); visitor.visite (sptr); }
void TFootnote::accept(TScoreVisitor& visitor)	{ SFootnote sptr(this); visitor.visite (sptr); }
void TVoice::accept(TScoreVisitor& visitor)		{ SVoice sptr(this); visitor.visite (sptr); }
void TLevel::accept(TScoreVisitor& visitor)		{ SLevel sptr(this); visitor.visite (sptr); }

//______________________________________________________________________________
void TFermata::accept(TScoreVisitor& visitor) {
	SFermata sptr(this);
	visitor.visite (sptr);
}

//______________________________________________________________________________
void TSegno::accept(TScoreVisitor& visitor) {
	SSegno sptr(this);
	visitor.visite (sptr);
}

//______________________________________________________________________________
void TCoda::accept(TScoreVisitor& visitor) {
	SCoda sptr(this);
	visitor.visite (sptr);
}

//______________________________________________________________________________
void TDynamic::accept(TScoreVisitor& visitor) {
	SDynamic sptr(this);
	visitor.visite (sptr);
}

//______________________________________________________________________________
long TDynamic::add (dynamic d) { 
	fDynamic.push_back(d); 
	return fDynamic.size()-1;
}

}


