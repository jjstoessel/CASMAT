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

#include "TPartGroup.h"

using namespace MusicXML;

namespace MusicXML 
{
//______________________________________________________________________________
// the new function
//______________________________________________________________________________
SPartGroup newPartGroup(StartStop::type type) { TPartGroup * o = new TPartGroup(type); assert(o!=0); return o; }
//______________________________________________________________________________
TPartGroup::symbol TPartGroup::fSymbolTbl[]			= { none, brace, line, bracket };
string TPartGroup::fSymbolStrings[]					= { "none", "brace", "line", "bracket" };
bimap<string, TPartGroup::symbol> TPartGroup::fSymbol2String(fSymbolStrings, fSymbolTbl, last);

//______________________________________________________________________________
const string TPartGroup::xmlsymbol (symbol d) 	{ return fSymbol2String[d]; }
TPartGroup::symbol TPartGroup::xmlsymbol (const string str) 	{ return fSymbol2String[str]; }

//______________________________________________________________________________
void TPartGroup::setType (StartStop::type type) { fType = type; }
void TPartGroup::setNumber(int num)				{ fNumber = num; }
void TPartGroup::setGroupName(string name)		{ fGroupName = name; }
void TPartGroup::setGroupAbbrev(string abbrev)	{ fGroupAbbrev = abbrev; }
void TPartGroup::setGroupBarline(string barline){ fGroupBarline = barline; }
void TPartGroup::setSymbol(symbol sym)			{ fSymbol = sym; }
//______________________________________________________________________________
void TPartGroup::accept(TScoreVisitor& visitor)
{
	SPartGroup sptr(this);
	visitor.visite(sptr);
}

}
