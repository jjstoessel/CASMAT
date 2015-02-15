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

#include "TIdentification.h"

using namespace MusicXML;
using namespace std;

namespace MusicXML 
{
//______________________________________________________________________________
// the new functions
//______________________________________________________________________________
SMiscField newMiscField(string name) { TMiscField * o = new TMiscField(name); assert(o!=0); return o; }
SMiscId newMiscId() { TMiscId * o = new TMiscId(); assert(o!=0); return o; }
SCreator newCreator() { TCreator * o = new TCreator(); assert(o!=0); return o; }
SRights newRights() { TRights * o = new TRights(); assert(o!=0); return o; }
SEncoding newEncoding() { TEncoding * o = new TEncoding(); assert(o!=0); return o; }
SIdentification newIdentification() { TIdentification * o = new TIdentification(); assert(o!=0); return o; }
SSupport newSupport(YesNo::type t, const string& element) { TSupport * o = new TSupport(t, element); assert(o!=0); return o; }
//______________________________________________________________________________
void TMiscField::accept(TScoreVisitor& visitor) { SMiscField sptr(this); visitor.visite(sptr); }
void TMiscId::accept(TScoreVisitor& visitor) { SMiscId sptr(this); visitor.visite(sptr); }
void TCreator::accept(TScoreVisitor& visitor) { SCreator sptr(this); visitor.visite(sptr); }
void TSupport::accept(TScoreVisitor& visitor) { SSupport sptr(this); visitor.visite(sptr); }

//______________________________________________________________________________
void TMiscField::setData(const string& data) 	{ fData = data; }
void TMiscField::setName(const string& name) 	{ fName = name; }
void TMiscId::add(SMiscField field)				{ fFields.push_back(field); }

//______________________________________________________________________________
void TCreator::setType(const string& type) 	{ fType = type; }
void TCreator::setName(const string& name) 	{ fName = name; }

//______________________________________________________________________________
void TSupport::setType(YesNo::type t)			{ fType = t; }
void TSupport::setElement(const string& elt) 	{ fElement = elt; }

//______________________________________________________________________________
void TRights::setType(const string& type) 		{ fType = type; }
void TRights::setRights(const string& rights) 	{ fRights = rights; }
//______________________________________________________________________________
void TRights::accept(TScoreVisitor& visitor) {
	SRights sptr(this);
	visitor.visite(sptr);
}

//______________________________________________________________________________
void TEncoding::setDate (const string& date) 			{ fDate = date; }
void TEncoding::setEncoder (const string& encoder) 		{ fEncoder = encoder; }
void TEncoding::setEncoderType (const string& etype) 	{ fEncoderType = etype; }
void TEncoding::setSoftware (const string& soft) 		{ fSoftware = soft; }
void TEncoding::setDescription (const string& desc) 	{ fDescription = desc; }
void TEncoding::add (SSupport support)					{ fSupport.push_back(support); }
//______________________________________________________________________________
void TEncoding::accept(TScoreVisitor& visitor) {
	SEncoding sptr(this);
	visitor.visite(sptr);
}

//______________________________________________________________________________
void TIdentification::setSource (const string& src) 			{ fSource = src; }
//______________________________________________________________________________
void TIdentification::accept(TScoreVisitor& visitor) {
	SIdentification sptr(this);
	visitor.visite(sptr);
}

//______________________________________________________________________________
long TIdentification::add (const SCreator& creator) { 
	fCreatorList.push_back(creator); 
	return fCreatorList.size()-1;
}
long TIdentification::add (const SRights& rights) { 
	fRightsList.push_back(rights); 
	return fRightsList.size()-1;
}

}
