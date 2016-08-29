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

#include "TOrnaments.h"
#include <string>

using namespace MusicXML;

namespace MusicXML 
{
//______________________________________________________________________________
// the new functions
//______________________________________________________________________________
SAccidentalMark newAccidentalMark()			{ TAccidentalMark * o = new TAccidentalMark(); assert(o!=0); return o; }
SOrnaments newOrnaments()					{ TOrnaments * o = new TOrnaments(); assert(o!=0); return o; }
SOrnament newOrnament(TOrnament::type t)	{ TOrnament * o = new TOrnament(t); assert(o!=0); return o; }
SOtherOrnament newOtherOrnament()			{ TOtherOrnament * o = new TOtherOrnament(); assert(o!=0); return o; }
STrillOrnament newTrillOrnament(TOrnament::type t)		{ TTrillOrnament * o = new TTrillOrnament(t); assert(o!=0); return o; }
SMordentOrnament newMordentOrnament(TOrnament::type t)  { TMordentOrnament * o = new TMordentOrnament(t); assert(o!=0); return o; }
SWavyLine newWavyLine(StartStop::type t)	{ TWavyLine * o = new TWavyLine(t); assert(o!=0); return o; }
//______________________________________________________________________________
TOrnament::type 
TOrnament::fTypeTbl[]	= { trill_mark, turn, delayed_turn, shake, wavy_line, mordent, 
				inverted_mordent, schleifer, other_ornament };
string TOrnament::fTypeStrings[]	= { 
				"trill-mark", "turn", "delayed-turn", "shake", "wavy-line", "mordent", 
				"inverted-mordent", "schleifer", "other-ornament" };
bimap<string, TOrnament::type> TOrnament::fType2String(fTypeStrings, fTypeTbl, last);

//______________________________________________________________________________
const string TOrnament::xml (type d)				{ return fType2String[d]; }
TOrnament::type	TOrnament::xml (const string str)   { return fType2String[str]; }
void TOrnament::setType(type t)					{ fType = t; }
void TOrnament::add(SAccidentalMark acc)		{ fAccidents.push_back(acc); }
void TOrnaments::add(SOrnament ornament)		{ fOrnaments.push_back(ornament); }

//______________________________________________________________________________
void TAccidentalMark::accept(TScoreVisitor& visitor) {
	SAccidentalMark sptr (this);
	visitor.visite(sptr);
}

//______________________________________________________________________________
void TOrnament::accept(TScoreVisitor& visitor) {
	SOrnament sptr (this);
	visitor.visite(sptr);
}

//______________________________________________________________________________
void TOtherOrnament::accept(TScoreVisitor& visitor) {
	SOtherOrnament sptr (this);
	visitor.visite(sptr);
}

//______________________________________________________________________________
void TTrillOrnament::accept(TScoreVisitor& visitor) {
	STrillOrnament sptr (this);
	visitor.visite(sptr);
}

//______________________________________________________________________________
void TMordentOrnament::accept(TScoreVisitor& visitor) {
	SMordentOrnament sptr (this);
	visitor.visite(sptr);
}

//______________________________________________________________________________
void TWavyLine::accept(TScoreVisitor& visitor) {
	SWavyLine sptr(this);
	visitor.visite (sptr);
}

//______________________________________________________________________________
void TOrnaments::accept(TScoreVisitor& visitor) {
	SOrnaments sptr (this);
	visitor.visite(sptr);
}

}
