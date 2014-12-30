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

#include "TPitch.h"

using namespace MusicXML;

namespace MusicXML 
{

static short step2pitch [] = { 0, 2, 4, 5, 7, 9, 11 };
//______________________________________________________________________________
// the new functions
//______________________________________________________________________________
SPitch newPitch() { TPitch * o = new TPitch(); assert(o!=0); return o; }
SRest newRest() { TRest * o = new TRest(); assert(o!=0); return o; }
SUnpitched newUnpitched() { TUnpitched * o = new TUnpitched(); assert(o!=0); return o; }
    
//______________________________________________________________________________
int TPitch::fPitchTbl[] 			= { C, D, E, F, G, A, B };
string TPitch::fPitchStrings[] 		= { "C", "D", "E", "F", "G", "A", "B" };
bimap<string, int> TPitch::fPitch2String(fPitchStrings, fPitchTbl, last);

//______________________________________________________________________________
const string TPitch::xmlpitch (int d) 		{ return fPitch2String[d]; }
int	TPitch::xmlpitch (const string str) 	{ return fPitch2String[str]; }

//______________________________________________________________________________
TPitch& TPitch::operator+= (int v)
{
	if (v >= 0) *this+=(unsigned int)v;
	else *this-=(unsigned int)(-v);
	return *this;
}

//______________________________________________________________________________
TPitch& TPitch::operator-= (int v)
{
	if (v >= 0) *this-=(unsigned int)v;
	else *this+=(unsigned int)(-v);
	return *this;
}

//______________________________________________________________________________
TPitch& TPitch::operator+= (unsigned int v)
{
    while (v >= diatonicSteps) {
        fOctave += 1;
        v-=7;
    }
    fStep += v;
    if (fStep > B) {
        fOctave += 1;
        fStep -= diatonicSteps;
    }
	return *this;
}

//______________________________________________________________________________
TPitch&	TPitch::operator-= (unsigned int v)
{
    while (v >= diatonicSteps) {
        if (fOctave > 0) fOctave -= 1;
        v-=7;
    }
    fStep -= v;
    if (fStep < C) {
        if (fOctave > 0) {
            fOctave -= 1;
            fStep += diatonicSteps;
        }
        else fStep = C;
    }
	return *this;
}

//______________________________________________________________________________
unsigned short TPitch::MIDIPitch () const
{
    unsigned short pitch = (unsigned short)(((fOctave+1) * 12) + step2pitch[fStep-1]);
    short alter = (short)fAlter;
    float r = fAlter - alter;
    if (r > 0.5) alter++;
    else if (r < -0.5) alter--;
    return (unsigned short)(pitch + alter);
}

//______________________________________________________________________________
void TPitch::setStep(int step)		{ fStep = step; }
void TPitch::setAlter(float alter)	{ fAlter = alter; }
void TPitch::setOctave(int oct)		{ fOctave = oct; }
//______________________________________________________________________________
void TPitch::accept(TScoreVisitor& visitor)
{
	SPitch sptr (this);
	visitor.visite(sptr);
}

//______________________________________________________________________________
void TUnpitched::accept(TScoreVisitor& visitor)
{
	SUnpitched sptr (this);
	visitor.visite(sptr);
}

//______________________________________________________________________________
void TRest::accept(TScoreVisitor& visitor)
{
	SRest sptr (this);
	visitor.visite(sptr);
}

}
