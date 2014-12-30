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

#include "THarmony.h"

using namespace MusicXML;
using namespace std;

namespace MusicXML 
{
//______________________________________________________________________________
// the new functions
//______________________________________________________________________________
SFunction   newFunction()		{ TFunction * o = new TFunction(); assert(o!=0); return o; }
SRoot		newRoot()			{ TRoot * o = new TRoot(); assert(o!=0); return o; }
SBass		newBass()			{ TBass * o = new TBass(); assert(o!=0); return o; }
SDegree		newDegree()			{ TDegree * o = new TDegree(); assert(o!=0); return o; }
SHarmonyChord newHarmonyChord() { THarmonyChord * o = new THarmonyChord(); assert(o!=0); return o; }
SFrame		newFrame()			{ TFrame * o = new TFrame(); assert(o!=0); return o; }
SFrameNote  newFrameNote()		{ TFrameNote * o = new TFrameNote(); assert(o!=0); return o; }
SHarmony	newHarmony()		{ THarmony * o = new THarmony(); assert(o!=0); return o; }
//______________________________________________________________________________
THarmony::type THarmony::fTypeTbl[]		= { kexplicit, implied, alternate };
string THarmony::fTypeStrings[]			= { "explicit", "implied", "alternate" };
bimap<string, THarmony::type> THarmony::fType2String(fTypeStrings, fTypeTbl, last);

//______________________________________________________________________________
const string   THarmony::xml (THarmony::type t) 	{ return fType2String[t]; }
THarmony::type THarmony::xml (const string str) 	{ return fType2String[str]; }

//______________________________________________________________________________
void TFunction::setFunction(const string& f){ fFunction = f; }
void TRoot::setRoot(const string& root)		{ fRoot = root; }
void TRoot::setAlter(const string& alter)   { fAlter = alter; }
//______________________________________________________________________________
void TDegree::setValue(int val)			{ fValue = val; }
void TDegree::setAlter(int val)			{ fAlter = val; }
void TDegree::setType(const string& t)  { fType = t; }
//______________________________________________________________________________
void THarmonyChord::setKind(const string kind)  { fKind = kind; }
void THarmonyChord::setInversion(int n)			{ fInversion = n; }
void THarmonyChord::setRootFunction(SRootFunction function)			{ fRootFunction = function; }
void THarmonyChord::setBass(SBass bass)			{ fBass = bass; }
void THarmonyChord::add(SDegree degree)			{ fDegrees.push_back(degree); }
//______________________________________________________________________________
void TFrame::setStrings(int n)		{ fStrings = n; }
void TFrame::setFrets(int n)		{ fFrets = n; }
void TFrame::setFirstFret(int n)	{ fFirstFret = n; }
void TFrame::add(SFrameNote fn)		{ fFrameNotes.push_back(fn); }
//______________________________________________________________________________
void TFrameNote::setString(const string str)   { fString = str; }
void TFrameNote::setFret(const string str)		{ fFret = str; }
//______________________________________________________________________________
void THarmony::setType(type t)					{ fType = t; }
void THarmony::setPrintObject(YesNo::type yn)   { fPrintObject = yn; }
void THarmony::setPrintFrame(YesNo::type yn)	{ fPrintFrame = yn; }
void THarmony::add(SHarmonyChord hc)			{ fHarmonyChord.push_back(hc); }
//______________________________________________________________________________
void THarmony::accept(TScoreVisitor& visitor)		{ SHarmony sptr (this); visitor.visite(sptr); }
void TFrameNote::accept(TScoreVisitor& visitor)		{ SFrameNote sptr (this); visitor.visite(sptr); }
void TFrame::accept(TScoreVisitor& visitor)			{ SFrame sptr (this); visitor.visite(sptr); }
void THarmonyChord::accept(TScoreVisitor& visitor)  { SHarmonyChord sptr (this); visitor.visite(sptr); }
void TDegree::accept(TScoreVisitor& visitor)		{ SDegree sptr (this); visitor.visite(sptr); }
void TRoot::accept(TScoreVisitor& visitor)			{ SRoot sptr (this); visitor.visite(sptr); }
void TBass::accept(TScoreVisitor& visitor)			{ SBass sptr (this); visitor.visite(sptr); }
void TFunction::accept(TScoreVisitor& visitor)		{ SFunction sptr (this); visitor.visite(sptr); }

}
