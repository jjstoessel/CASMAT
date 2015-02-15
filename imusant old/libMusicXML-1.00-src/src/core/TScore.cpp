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

#include "TScore.h"

using namespace MusicXML;

namespace MusicXML 
{
//______________________________________________________________________________
// the new functions
//______________________________________________________________________________
SFeature newFeature()						{ TFeature * o = new TFeature(); assert(o!=0); return o; }
SGrouping newGrouping(StartStop::type type) { TGrouping * o = new TGrouping(type); assert(o!=0); return o; }
    
void TFeature::setType (const string& type)		{ fType = type; }
void TFeature::setDate (const string& data)		{ fData = data; }
void TFeature::accept(TScoreVisitor& visitor)   { SFeature sptr(this); visitor.visite(sptr); }


void TGrouping::setType (StartStop::type type)  { fType = type; }
void TGrouping::setNumber (long number)			{ fNumber = number; }
void TGrouping::setMemberOf (const string& m)	{ fMemberOf = m; }
void TGrouping::add (const SFeature& feature)   { fFeatures.push_back (feature); }
void TGrouping::accept(TScoreVisitor& visitor)   { SGrouping sptr(this); visitor.visite(sptr); }


}
