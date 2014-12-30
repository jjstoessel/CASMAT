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

#include "TTimeSign.h"
#include <sstream>

using namespace MusicXML;

namespace MusicXML 
{
//______________________________________________________________________________
// the new function
//______________________________________________________________________________
STimeSign newTimeSign() { TTimeSign * o = new TTimeSign(); assert(o!=0); return o; }

//______________________________________________________________________________
int TTimeSign::fSymbolTbl[] 		= { common, cut, single_number, normal };
string TTimeSign::fSymbolStrings[]	= { "common", "cut", "single_number", "normal" };
bimap<string, int> TTimeSign::fSymbol2String(fSymbolStrings, fSymbolTbl, last);

//______________________________________________________________________________
const string TTimeSign::xmlsymbol (int d) 		{ return fSymbol2String[d]; }
int	TTimeSign::xmlsymbol (const string str) 	{ return fSymbol2String[str]; }

//______________________________________________________________________________
TRational TTimeSign::rational()
{
	vector<long>::const_iterator beat = getBeats().begin();
	vector<long>::const_iterator type = getBeatTypes().begin();

	if (!measured()) {
		TRational r(-1,1);
		return r;
	}

	TRational r(0,0);
	while (beat != getBeats().end()) {
		if (*type == TTimeSign::groupbeats) 
			r.setNumerator(r.getNumerator() + *beat);
		else { 
			TRational c(*beat,*type);
			r += c;
		}
		beat++; type++;
	}
	return r;
}

//______________________________________________________________________________
void TTimeSign::setSymbol(int symbol)		{ fSymbol = symbol; }
//______________________________________________________________________________
void TTimeSign::accept(TScoreVisitor& visitor)
{
	STimeSign sptr(this);
	visitor.visite(sptr);
}

//______________________________________________________________________________
long TTimeSign::add (long beat, long type) 	{ 
	fBeat.push_back(beat); 
	fBeatType.push_back(type);
	return fBeat.size()-1;
}

}
