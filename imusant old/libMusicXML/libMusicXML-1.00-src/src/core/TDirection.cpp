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

#include "TDirection.h"
#include <sstream>

using namespace MusicXML;

namespace MusicXML 
{
//______________________________________________________________________________
// the new functions
//______________________________________________________________________________
SOctaveShift newOctaveShift(int type) { TOctaveShift * o = new TOctaveShift(type); assert(o!=0); return o; }
SBracket newBracket(StartStop::type t) { TBracket * o = new TBracket(t); assert(o!=0); return o; }
SDashes newDashes(StartStop::type t) { TDashes * o = new TDashes(t); assert(o!=0); return o; }
SWords newWords() { TWords * o = new TWords(); assert(o!=0); return o; }
SWedge newWedge(int type) { TWedge * o = new TWedge(type); assert(o!=0); return o; }
SSymbolicNoteDuration newSymbolicNoteDuration()
{ TSymbolicNoteDuration * o = new TSymbolicNoteDuration(); assert(o!=0); return o; }
SMetronome newMetronome() { TMetronome * o = new TMetronome(); assert(o!=0); return o; }
SDirectionType newDirectionType() { TDirectionType * o = new TDirectionType(); assert(o!=0); return o; }
SDirection newDirection() { TDirection * o = new TDirection(); assert(o!=0); return o; }
//______________________________________________________________________________
int TOctaveShift::fTypeTbl[]		= { up, down, stop };
string TOctaveShift::fTypeStrings[]	= { "up", "down", "stop" };
bimap<string, int> TOctaveShift::fType2String(fTypeStrings, fTypeTbl, last);

//______________________________________________________________________________
const string	TOctaveShift::xmltype (int d) 		{ return fType2String[d]; }
int	TOctaveShift::xmltype (const string str) 	{ return fType2String[str]; }

//______________________________________________________________________________
void TOctaveShift::setType(int type)	{ fType = type; }
void TOctaveShift::setNumber(int num)	{ fNumber = num; }
void TOctaveShift::setSize(int size)	{ fSize = size; }
//______________________________________________________________________________
void TOctaveShift::accept(TScoreVisitor& visitor)
{
	SOctaveShift sptr(this);
	visitor.visite(sptr);
}

//______________________________________________________________________________
int TBracket::fLEndTbl[]		= { up, down, both, arrow, none };
string TBracket::fLEndStrings[]	= { "up", "down", "both", "arrow", "none" };
bimap<string, int> TBracket::fLEnd2String(fLEndStrings, fLEndTbl, last);

//______________________________________________________________________________
const string	TBracket::xmllineend (int d) 	{ return fLEnd2String[d]; }
int TBracket::xmllineend (const string str) 	{ return fLEnd2String[str]; }

//______________________________________________________________________________
void TBracket::setType(StartStop::type type) 	{ fType = type; }
void TBracket::setNumber(int num)				{ fNumber = num; }
void TBracket::setLineEnd(int lend)				{ fLineEnd = lend; }
void TBracket::setLineType(LineType::type t)	{ fLineType = t; }
//______________________________________________________________________________
void TBracket::accept(TScoreVisitor& visitor)
{
	SBracket sptr(this);
	visitor.visite(sptr);
}

//______________________________________________________________________________
void TDashes::setType(StartStop::type t)	{ fType = t; }
void TDashes::setNumber(int num)			{ fNumber = num; }
//______________________________________________________________________________
void TDashes::accept(TScoreVisitor& visitor)
{
	SDashes sptr(this);
	visitor.visite(sptr);
}

//______________________________________________________________________________
int TWords::fJustTbl[]			= { left, center, right };
string TWords::fJustStrings[]	= { "left", "center", "right" };
bimap<string, int> TWords::fJust2String(fJustStrings, fJustTbl, last);

//______________________________________________________________________________
const string TWords::xmljustify (int d) 	{ return fJust2String[d]; }
int	TWords::xmljustify (const string str) 	{ return fJust2String[str]; }

//______________________________________________________________________________
int TWedge::fTypeTbl[]			= { crescendo, diminuendo, stop };
string TWedge::fTypeStrings[]	= { "crescendo", "diminuendo", "stop" };
bimap<string, int> TWedge::fType2String(fTypeStrings, fTypeTbl, last);

//______________________________________________________________________________
const string TWedge::xmltype (int d) 	{ return fType2String[d]; }
int	TWedge::xmltype (const string str) 	{ return fType2String[str]; }

//______________________________________________________________________________
void TWedge::setType (int type)	{ fType = type; }
void TWedge::setNumber(int num)	{ fNumber = num; }
void TWedge::setSpread(int sp)	{ fSpread = sp; }
//______________________________________________________________________________
void TWedge::accept(TScoreVisitor& visitor)
{
	SWedge sptr(this);
	visitor.visite(sptr);
}

//______________________________________________________________________________
void TWords::setJustify (int just)			{ fJustify = just; }
void TWords::setLang (const string& lang)	{ fLang = lang; }
void TWords::setValue(const string& value)	{ fValue = value; }
//______________________________________________________________________________
void TWords::accept(TScoreVisitor& visitor)
{
	SWords sptr(this);
	visitor.visite(sptr);
}

//______________________________________________________________________________
void TSymbolicNoteDuration::setBeat (NoteType::type beatUnit)	{ fBeatUnit=beatUnit; }
void TSymbolicNoteDuration::setDots (unsigned dots)				{ fDots=dots; }

//______________________________________________________________________________
void TMetronome::setParentheses (YesNo::type val)	{ fParentheses = val; }
void TMetronome::setPerMinute (string pm) 			{ fPerMinute = pm; }
//______________________________________________________________________________
void TMetronome::setPerMinute (long permin) {
	stringstream s;
	s << permin;
	s >> fPerMinute;
}

//______________________________________________________________________________
void TMetronome::accept(TScoreVisitor& visitor)
{
	SMetronome sptr(this);
	visitor.visite(sptr);
}

//______________________________________________________________________________
void TDirectionType::accept(TScoreVisitor& visitor)
{
	SDirectionType sptr(this);
	visitor.visite(sptr);
}

//______________________________________________________________________________
long TDirectionType::add (const SDirectionTypeElement& elt) {
	fElements.push_back(elt); 
	return fElements.size()-1;
}

//______________________________________________________________________________
void TDirection::setOffset(long offset)					{ fOffset=offset; }
void TDirection::setVoice(long voice)					{ fVoice=voice; }
void TDirection::setStaff(long staff)					{ fStaff=staff; }
//______________________________________________________________________________
void TDirection::accept(TScoreVisitor& visitor)
{
	SDirection sptr(this);
	visitor.visite(sptr);
}

//______________________________________________________________________________
long TDirection::add(const SDirectionType& dir) {
	fTypeList.push_back(dir); 
	return fTypeList.size()-1;
}

}
