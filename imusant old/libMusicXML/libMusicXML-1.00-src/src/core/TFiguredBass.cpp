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

#include "TFiguredBass.h"

using namespace MusicXML;

namespace MusicXML 
{
    
//______________________________________________________________________________
// the new functions
//______________________________________________________________________________
SFigure newFigure()			{ TFigure * o = new TFigure(); assert(o!=0); return o; }
SFiguredBass newFiguredBass() { TFiguredBass * o = new TFiguredBass(); assert(o!=0); return o; }

//______________________________________________________________________________
void TFigure::accept(TScoreVisitor& visitor)
{
	SFigure sptr (this);
	visitor.visite(sptr);
}

//______________________________________________________________________________
void TFiguredBass::accept(TScoreVisitor& visitor)
{
	SFiguredBass sptr (this);
	visitor.visite(sptr);
}

//______________________________________________________________________________
long TFiguredBass::add(const SFigure& figure) { 
	fFigures.push_back(figure);
	return fFigures.size()-1;
}

}
