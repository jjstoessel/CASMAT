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

#include "TScoreTimewise.h"

using namespace MusicXML;

namespace MusicXML 
{
//______________________________________________________________________________
// the new functions
//______________________________________________________________________________
STWPart newTWPart(string id) { TTWPart * o = new TTWPart(id); assert(o!=0); return o; }
STWMeasure newTWMeasure(string num) { TTWMeasure * o = new TTWMeasure(num); assert(o!=0); return o; }
STWMeasure newTWMeasure(long num)   { TTWMeasure * o = new TTWMeasure(num); assert(o!=0); return o; }
SScoreTimewise newScoreTimewise() { TScoreTimewise * o = new TScoreTimewise(); assert(o!=0); return o; }

//______________________________________________________________________________
void TTWMeasure::accept(TScoreVisitor& visitor)
{
	STWMeasure sptr (this);
	visitor.visite(sptr);
}

//______________________________________________________________________________
void TTWPart::accept(TScoreVisitor& visitor)
{
	STWPart sptr (this);
	visitor.visite(sptr);
}

//______________________________________________________________________________
TScoreTimewise::TScoreTimewise ()
{
	fHeader = new_xmlheader(xmlheader::timewise);
}

//______________________________________________________________________________
void TScoreTimewise::accept(TScoreVisitor& visitor)
{
	SScoreTimewise sptr (this);
	visitor.visite(sptr);
}

//______________________________________________________________________________
long TTWMeasure::add (const SMARTP<TTWPart>& part) { 
	fParts.push_back(part); 
	return fParts.size()-1;
}

//______________________________________________________________________________
long TTWPart::add (const SMusicData& data) { 
	fData.push_back(data); 
	return fData.size()-1;
}
//______________________________________________________________________________
long TScoreTimewise::add(const STWMeasure& part) { 
	fMeasureList.push_back (part); 
	return fMeasureList.size()-1;
}

}
