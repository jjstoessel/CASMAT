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

#include "TNotation.h"
#include <string>

using namespace MusicXML;

namespace MusicXML 
{
//______________________________________________________________________________
// the new functions
//______________________________________________________________________________
SNotation newNotation() { TNotation * o = new TNotation(); assert(o!=0); return o; }
STie newTie(StartStop::type type) { TTie * o = new TTie(type); assert(o!=0); return o; }
SSlur newSlur(StartStop::type type) { TSlur * o = new TSlur(type); assert(o!=0); return o; }
SArticulations newArticulations() { TArticulations * o = new TArticulations(); assert(o!=0); return o; }
SStrongAccent newStrongAccent() { TStrongAccent * o = new TStrongAccent(); assert(o!=0); return o; }
SArticulationElement newArticulationElement(TArticulationElement::articulation type) {
    TArticulationElement * o = new TArticulationElement(type); assert(o!=0); return o;
}
SOtherArticulation newOtherArticulation() { TOtherArticulation * o = new TOtherArticulation(); assert(o!=0); return o; }
STupletDesc newTupletActual() { TTupletActual * o = new TTupletActual(); assert(o!=0); return o; }
STupletDesc newTupletNormal() { TTupletNormal * o = new TTupletNormal(); assert(o!=0); return o; }
STuplet newTuplet(StartStop::type type)  { TTuplet * o = new TTuplet(type); assert(o!=0); return o; }
SGlissando newGlissando(StartStop::type type)  { TGlissando * o = new TGlissando(type); assert(o!=0); return o; }
SSlide newSlide(StartStop::type type)  { TSlide * o = new TSlide(type); assert(o!=0); return o; }
SOtherNotation newOtherNotation(StartStop::type type)  { TOtherNotation * o = new TOtherNotation(type); assert(o!=0); return o; }
//______________________________________________________________________________
TArticulationElement::articulation 
TArticulationElement::fArticulationTbl[]	= { accent, strong_accent, staccato, tenuto, detached_legato,
             staccatissimo, spiccato, scoop, plop, doit, falloff, breath_mark, caesura, other_articulation };
string TArticulationElement::fArticulationStrings[]	= { 
        "accent", "strong-accent", "staccato", "tenuto", "detached-legato",
        "staccatissimo", "spiccato", "scoop", "plop", "doit", "falloff", 
        "breath-mark", "caesura", "other-articulation"
};
bimap<string, TArticulationElement::articulation> 
TArticulationElement::fArticulation2String(fArticulationStrings, fArticulationTbl, last);

//______________________________________________________________________________
const string TArticulationElement::xmlname (articulation d)		
    { return fArticulation2String[d]; }
TArticulationElement::articulation	TArticulationElement::xmlname (const string str) 	
    { return fArticulation2String[str]; }

//______________________________________________________________________________
void TArticulationElement::accept(TScoreVisitor& visitor) { SArticulationElement sptr (this); visitor.visite(sptr); }
void TOtherArticulation::accept(TScoreVisitor& visitor) { SOtherArticulation sptr (this); visitor.visite(sptr); }

//______________________________________________________________________________
void TTieSlur::setType(StartStop::type type)	{ fType = type; }
void TTieSlur::setNumber(int num)				{ fNumber = num; }
void TTieSlur::setLineType(LineType::type type)	{ fLine = type; }
//______________________________________________________________________________
/*
void TTieSlur::accept(TScoreVisitor& visitor)
{
	STieSlur sptr (this);
	visitor.visite(sptr);
}
*/

//______________________________________________________________________________
void TTie::accept(TScoreVisitor& visitor)
{
	STie sptr (this);
	visitor.visite(sptr);
}

//______________________________________________________________________________
void TSlur::accept(TScoreVisitor& visitor)
{
	SSlur sptr (this);
	visitor.visite(sptr);
}

//______________________________________________________________________________
void TTupletDesc::setNumber (int num)	{ fNumber = num; }
void TTupletDesc::setType(int type)		{ fType = type; }
void TTupletDesc::setDots(int dots)		{ fDots = dots; }
//______________________________________________________________________________
void TTupletDesc::accept(TScoreVisitor& visitor)
{
	STupletDesc sptr (this);
	visitor.visite(sptr);
}

//______________________________________________________________________________
int TTuplet::fShowTbl[]			= { actual, both, none };
string TTuplet::fShowStrings[]	= { "actual", "both", "none" };
bimap<string, int> TTuplet::fShow2String(fShowStrings, fShowTbl, last);

//______________________________________________________________________________
const string TTuplet::xmlshow (int d) 		{ return fShow2String[d]; }
int	TTuplet::xmlshow (const string str) 	{ return fShow2String[str]; }

//______________________________________________________________________________
void TTuplet::setType(StartStop::type type)	{ fType = type; }
void TTuplet::setNumber(int num)		{ fNumber = num; }
void TTuplet::setBracket(YesNo::type bracket)	{ fBracket = bracket; }
void TTuplet::setShowNum(int sn)		{ fShowNum = sn; }
void TTuplet::setShowType(int st)		{ fShowType = st; }
//______________________________________________________________________________
void TTuplet::accept(TScoreVisitor& visitor)
{
	STuplet sptr (this);
	visitor.visite(sptr);
}

//______________________________________________________________________________
void TArticulations::accept(TScoreVisitor& visitor)
{
	SArticulations sptr (this);
	visitor.visite(sptr);
}

//______________________________________________________________________________
long TArticulations::add (const SArticulationElement& art) {
	fList.push_back(art); 
	return fList.size()-1;
}

//______________________________________________________________________________
void TArticulationElement::setArtType(articulation a) 	{ fArticulationType = a; }

//______________________________________________________________________________
int TStrongAccent::fTypeTbl[]			= { up, down };
string TStrongAccent::fTypeStrings[]	= { "up", "down" };
bimap<string, int> TStrongAccent::fType2String(fTypeStrings, fTypeTbl, last);

//______________________________________________________________________________
const string TStrongAccent::xmltype (int d) 	{ return fType2String[d]; }
int TStrongAccent::xmltype (const string str) 	{ return fType2String[str]; }

//______________________________________________________________________________
void TStrongAccent::setType(int type)	{ fType = type; }
//______________________________________________________________________________
void TStrongAccent::accept(TScoreVisitor& visitor)
{
	SStrongAccent sptr (this);
	visitor.visite(sptr);
}

//______________________________________________________________________________
void TNotation::accept(TScoreVisitor& visitor)
{
	SNotation sptr (this);
	visitor.visite(sptr);
}

//______________________________________________________________________________
long TNotation::add (const SNotationElement& elt) {
	fList.push_back(elt); 
	return fList.size()-1;
}

//______________________________________________________________________________
void TGlissando::accept(TScoreVisitor& visitor) {
	SGlissando sptr (this);
	visitor.visite(sptr);
}

//______________________________________________________________________________
void TOtherNotation::accept(TScoreVisitor& visitor) {
	SOtherNotation sptr (this);
	visitor.visite(sptr);
}

//______________________________________________________________________________
void TSlide::accept(TScoreVisitor& visitor) {
	SSlide sptr (this);
	visitor.visite(sptr);
}

void TGlissando::setType(StartStop::type type)		{ fType = type; }
void TGlissando::setNumber(int number)				{ fNumber = number; }
void TGlissando::setLineType(LineType::type type)   { fLineType = type; }

void TOtherNotation::setType(StartStop::type type)		{ fType = type; }
void TOtherNotation::setNumber(int number)				{ fNumber = number; }

}
