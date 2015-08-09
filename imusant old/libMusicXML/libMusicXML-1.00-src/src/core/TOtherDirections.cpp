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

#include "TOtherDirections.h"

using namespace MusicXML;

namespace MusicXML 
{
//______________________________________________________________________________
// the new functions
//______________________________________________________________________________
SOtherDirections newOtherDirections(TOtherDirections::type t)
{ TOtherDirections * o = new TOtherDirections(t); assert(o!=0); return o; }
SRehearsal newRehearsal() { TRehearsal * o = new TRehearsal(); assert(o!=0); return o; }
SOtherDirection newOtherDirection() { TOtherDirection * o = new TOtherDirection(); assert(o!=0); return o; }
SPedal newPedal(StartStop::type t) { TPedal * o = new TPedal(t); assert(o!=0); return o; }
SPrint newPrint() { TPrint * o = new TPrint(); assert(o!=0); return o; }
//______________________________________________________________________________
TOtherDirections::type TOtherDirections::fTypeTbl[]		= { damp, damp_all, eyeglasses };
string TOtherDirections::fTypeStrings[]					= { "damp", "damp-all", "eyeglasses" };
bimap<string, TOtherDirections::type> TOtherDirections::fType2String(fTypeStrings, fTypeTbl, last);

const string	TOtherDirections::xml (type d)						{ return fType2String[d]; }
TOtherDirections::type	TOtherDirections::xml (const string str) 	{ return fType2String[str]; }

//______________________________________________________________________________
void TOtherDirections::accept(TScoreVisitor& visitor)   { SOtherDirections sptr(this); visitor.visite(sptr); }
void TRehearsal::accept(TScoreVisitor& visitor)			{ SRehearsal sptr(this); visitor.visite(sptr); }
void TOtherDirection::accept(TScoreVisitor& visitor)	{ SOtherDirection sptr(this); visitor.visite(sptr); }
void TPedal::accept(TScoreVisitor& visitor)				{ SPedal sptr(this); visitor.visite(sptr); }
void TPrint::accept(TScoreVisitor& visitor)				{ SPrint sptr(this); visitor.visite(sptr); }

}
