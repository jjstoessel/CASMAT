/*

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

#include "guido.h"

//______________________________________________________________________________
Sguidoparam new_guidoparam(string value, bool quote)
{ guidoparam * o = new guidoparam(value, quote); assert(o!=0); return o; }
Sguidoparam new_guidoparam(long value, bool quote)
{ guidoparam * o = new guidoparam(value, quote); assert(o!=0); return o; }

Sguidoelement new_guidoelement(string name, string sep)
{  guidoelement * o = new guidoelement(name, sep); assert(o!=0); return o; }
Sguidonote new_guidonote(unsigned short voice, string name, char oct, guidonoteduration& dur, string acc)
{ guidonote * o = new guidonote (voice, name, oct, dur, acc); assert(o!=0); return o; }
Sguidoseq new_guidoseq()			{ guidoseq* o = new guidoseq(); assert(o!=0); return o;}
Sguidochord new_guidochord()		{ guidochord* o = new guidochord(); assert(o!=0); return o;}
Sguidotag new_guidotag(string name)	{ guidotag* o = new guidotag(name); assert(o!=0); return o;}

//______________________________________________________________________________
guidonotestatus* guidonotestatus::fInstances[kMaxInstances] = { 0 };
guidonotestatus* guidonotestatus::get (unsigned short voice)
{ 
    if (voice < kMaxInstances) {
        if (!fInstances[voice]) 
            fInstances[voice] = new guidonotestatus; 
        return fInstances[voice];
    }
    return 0;
}

void guidonotestatus::resetall ()
{ 
    for (int i=0; i<kMaxInstances; i++) {
        if (fInstances[i]) fInstances[i]->reset();
    }
}

//______________________________________________________________________________
void guidoparam::set (string value, bool quote)
{
	fValue = value;
	fQuote = quote;
}

//______________________________________________________________________________
void guidoparam::set (long value, bool quote)
{
	stringstream s;
	s << value;
	s >> fValue;
	fQuote = quote;
}

//______________________________________________________________________________
long guidoelement::add (Sguidoelement& elt)	{ 
	fElements.push_back(elt); 
	return fElements.size()-1;
}
long guidoelement::add (Sguidoparam& param) { 
	fParams.push_back(param); 
	return fParams.size()-1;
}
#ifndef WIN32
long guidoelement::add (Sguidoparam param) { 
	fParams.push_back(param); 
	return fParams.size()-1;
}
#endif

//______________________________________________________________________________
void guidoelement::print(ostream& os)
{
    os << fName;

    // print the optional parameters section
    if (!fParams.empty()) {
        os << "<";
        vector<Sguidoparam>::const_iterator param;
        for (param = fParams.begin(); param != fParams.end(); ) {
            if ((*param)->quote())
				os << "\"" << (*param)->get() << "\"";
			else
				os << (*param)->get();
            if (++param != fParams.end())
                os << ", ";
        }
        os << ">";
    }

    bool isSeq = dynamic_cast<const guidoseq *>(this) != 0;
    bool isChord = dynamic_cast<const guidochord *>(this) != 0;
    bool prevNote = false;
    bool prevSeq = false;
    // print the optional contained elements
    if (!fElements.empty()) {
        os << fStartList;
        vector<Sguidoelement>::const_iterator ielt;
        for (ielt = fElements.begin(); ielt != fElements.end(); ielt++) {
            Sguidoseq seq;
            seq.cast((guidoelement *)(*ielt));
            Sguidonote note;
            note.cast((guidoelement *)(*ielt));

            if (isChord) {
                if (note) {
                    os << (prevNote ? ", " : " ");
                    prevNote = true;
                }
                else if (seq) {
                    os << (prevSeq ? ", " : " ");
                    prevSeq = true;
                }
                else os << " ";
            }
            else os << " ";
            os << *ielt;            
        }
       os << fEndList;
    }
	if (isSeq) os << std::endl;
}

//______________________________________________________________________________
ostream& operator<< (ostream& os, const Sguidoelement& elt)
{
    elt->print(os);
    return os;
}

//______________________________________________________________________________
void guidonote::set (unsigned short voice, string name, char octave, guidonoteduration& dur, string acc)
{
    guidonotestatus * status = guidonotestatus::get(voice);
    stringstream s;
    long dots = dur.fDots;
    
 	fNote = name;
	fAccidental = acc;
	fOctave = octave;
	fDuration = dur;
	
	s << name;
    // octave is ignored in case of rests
	if (name[0] != '_') {
		if (!acc.empty())
			s << acc;
		if (name != "empty") {
			if (!status)
				s << (int)octave;
			else if (status->fOctave != octave) {
				s << (int)octave;
				status->fOctave = octave;
			}
		}
    }
	if (!status || (*status != dur)) {
        if (dur.fNum != 1) {
            s << "*" << (int)dur.fNum;
        }
        s << "/" << (int)dur.fDenom;
        if (status) *status = dur;
    }
    while (dots-- > 0)
        s << ".";
    s >> fName;
}

//______________________________________________________________________________
guidoelement::guidoelement(string name, string sep) : fName(name), fSep(sep) {}
guidoelement::~guidoelement() {}
//______________________________________________________________________________
void guidoelement::accept (guidovisitor& visitor)
{
	Sguidoelement ptr(this);
	visitor.visite(ptr);
}

//______________________________________________________________________________
guidoparam::guidoparam(string value, bool quote) : fValue(value), fQuote(quote) {}
guidoparam::guidoparam(long value, bool quote)   { set(value, quote); }
guidoparam::~guidoparam () {}
//______________________________________________________________________________
void guidoparam::accept (guidovisitor& visitor)
{
	Sguidoparam ptr(this);
	visitor.visite(ptr);
}

//______________________________________________________________________________
guidonote::guidonote(unsigned short voice, string name, char octave, 
                    guidonoteduration& dur, string acc) 
            : guidoelement(""), fDuration(1,4) { set(voice, name, octave, dur, acc); }
guidonote::~guidonote() {}
//______________________________________________________________________________
void guidonote::accept (guidovisitor& visitor)
{
	Sguidonote ptr(this);
	visitor.visite(ptr);
}

//______________________________________________________________________________
guidoseq::guidoseq() : guidoelement("") { fStartList="["; fEndList=" ]"; }
guidoseq::~guidoseq() {}
//______________________________________________________________________________
void guidoseq::accept (guidovisitor& visitor)
{
	Sguidoseq ptr(this);
	visitor.visite(ptr);
}

//______________________________________________________________________________
guidochord::guidochord () : guidoelement("", ", ") 
	{ fStartList="{"; fEndList=" }"; }
guidochord::~guidochord() {}
//______________________________________________________________________________
void guidochord::accept (guidovisitor& visitor)
{
	Sguidochord ptr(this);
	visitor.visite(ptr);
}

//______________________________________________________________________________
guidotag::guidotag(string name) : guidoelement("\\"+name) 
	{ fStartList="("; fEndList=")"; }
guidotag::~guidotag() {}
//______________________________________________________________________________
void guidotag::accept (guidovisitor& visitor)
{
	Sguidotag ptr(this);
	visitor.visite(ptr);
}
