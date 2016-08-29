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

#include "TMeasureStyle.h"

using namespace MusicXML;

namespace MusicXML 
{
//______________________________________________________________________________
// the new functions
//______________________________________________________________________________
SMeasureStyle newMeasureStyle()		{ TMeasureStyle * o = new TMeasureStyle(); assert(o!=0); return o; }
SMultipleRest newMultipleRest()		{ TMultipleRest * o = new TMultipleRest(); assert(o!=0); return o; }
SMeasureRepeat newMeasureRepeat(StartStop::type t)  { TMeasureRepeat * o = new TMeasureRepeat(t); assert(o!=0); return o; }
SBeatRepeat newBeatRepeat(StartStop::type t)		{ TBeatRepeat * o = new TBeatRepeat(t); assert(o!=0); return o; }
SSlash newSlash(StartStop::type t)					{ TSlash * o = new TSlash(t); assert(o!=0); return o; }
//______________________________________________________________________________
void TMeasureStyleElement::accept(TScoreVisitor& visitor) { SMeasureStyleElement sptr(this); visitor.visite(sptr); }
void TMeasureStyle::accept(TScoreVisitor& visitor) { SMeasureStyle sptr(this); visitor.visite(sptr); }
void TMultipleRest::accept(TScoreVisitor& visitor) { SMultipleRest sptr(this); visitor.visite(sptr); }
void TMeasureRepeat::accept(TScoreVisitor& visitor) { SMeasureRepeat sptr(this); visitor.visite(sptr); }
void TBeatRepeat::accept(TScoreVisitor& visitor) { SBeatRepeat sptr(this); visitor.visite(sptr); }
void TSlash::accept(TScoreVisitor& visitor) { SSlash sptr(this); visitor.visite(sptr); }

}
