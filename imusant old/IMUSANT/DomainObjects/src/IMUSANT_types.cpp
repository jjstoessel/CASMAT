/*
 *  IMUSANT_types.cpp
 *  imusant
 *
 *  Created by Jason Stoessel on 9/05/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "IMUSANT_types.h"
#include "TTimeSign.h"
#include "IMUSANT_pitch.h"

using namespace MusicXML;

namespace IMUSANT
{

//ctor functions
S_IMUSANT_lyric new_IMUSANT_lyric() { IMUSANT_lyric* o = new IMUSANT_lyric(); assert (o!=0); return o; }
S_IMUSANT_accidental new_IMUSANT_accidental()
	{ IMUSANT_accidental* o = new IMUSANT_accidental(); assert(o!=0); return o; }


//______________________________________________________________________________
IMUSANT_accidental::accident IMUSANT_accidental::fAccidentTbl[]		
	= { undefined, sharp, natural, flat, double_sharp, sharp_sharp, flat_flat,
		natural_sharp, natural_flat, quarter_flat, quarter_sharp,
		three_quarters_flat, three_quarters_sharp };
string IMUSANT_accidental::fAccidentStrings[]
	= { "undefine", "sharp", "natural", "flat", "double-sharp", "sharp-sharp", "flat-flat",
		"natural-sharp", "natural-flat", "quarter-flat", "quarter-sharp",
		"three-quarters-flat", "three-quarters-sharp"
};
bimap<string, IMUSANT_accidental::accident> IMUSANT_accidental::fAccident2String(fAccidentStrings, fAccidentTbl, last);

const string IMUSANT_accidental::xml( accident d ) { return fAccident2String[d]; }
IMUSANT_accidental::accident IMUSANT_accidental::xml (const string str) { return fAccident2String[str]; }

IMUSANT_accidental::accident IMUSANT_accidental::AlterToAccident(signed short alter)
{
	accident acc = undefined;
	
	switch (alter)
	{
		case 0:
			acc = natural;
			break;
		case 1:
			acc = sharp;
			break;
		case -1:
			acc = flat;
			break;
		case 2:
			acc = double_sharp; //could be sharp_sharp
			break;
		case -2:
			acc = flat_flat;
			break;
			
	};
	
	return acc;
}
    
    
    void
    IMUSANT_accidental::
    print(ostream& os) const
    {
        os << xml(fAccident);

//        accident 	fAccident;
//        YesNo::type		fCautionary;
//        YesNo::type		fEditorial;
//        YesNo::type		fCancelling;
            }


//IMUSANT_time consts
IMUSANT_time::symbol	IMUSANT_time::fSymbolTbl[] = {	undefined, common, cut, single_number, normal, composite, multiple,
														C, O, Cdot, Odot, cutC, cutO, cutOdot, cutCdot, C2, O2, C3, O3 };
string	IMUSANT_time::fSymbolStrings[] = {  "undefined", "common", "cut", "single_number", 
											"normal", "composite", "multiple", "C", "O", "Cdot", "Odot", "cutC",
											"cutO", "cutOdot", "cutCdot", "C2", "O2", "C3", "O3" };
bimap<string, IMUSANT_time::symbol>	IMUSANT_time::fType2String(fSymbolStrings, fSymbolTbl, last);
const string	IMUSANT_time::xmlsymbol (symbol sym) { return fType2String[sym]; }
IMUSANT_time::symbol	IMUSANT_time::xmlsymbol (const string str) { return fType2String[str]; }
IMUSANT_time::symbol IMUSANT_time::ConvertXML2IMUSANTSymbol( const int xmltime )
{
	symbol sym = undefined;
	
	switch (xmltime)
	{
		case TTimeSign::undefined:
			break;
		case TTimeSign::common:
			sym = IMUSANT_time::common;
			break;
		case TTimeSign::cut:
			sym = IMUSANT_time::cut;
			break;
		case TTimeSign::single_number:
			sym = IMUSANT_time::single_number;
			break;
		case TTimeSign::normal:
			sym = IMUSANT_time::normal;
			break;
	};
	
	return sym;
}

ostream& operator<< (ostream& os, const IMUSANT_clef& elt )
{
	elt.print(os); return os;
}

ostream& operator<< (ostream& os, const IMUSANT_time& elt )
{
	elt.print(os); return os;
}

void IMUSANT_lyric::accept (IMUSANT_visitor& visitor)
{
	S_IMUSANT_lyric ptr(this);
	visitor.visit(ptr);
}

//Constructor for simple time signature
/*IMUSANT_time::IMUSANT_time(long num, long denom, int symbol)
{
	fBeatNum.push_back(num);
	fBeatDenom.push_back(denom);
	fSymbol=symbol;
}*/

void IMUSANT_time::addNumerator(const long num)
{ 
	fBeatNum.push_back(num);
	//monitor symbol status
	if (fBeatNum.size()>1)
	{
		if (fBeatDenom.size()>1)
			fSymbol = multiple;
		else
			fSymbol = composite;
	}
}

void IMUSANT_time::addDenominator(const long denom) 
{ 
	fBeatDenom.push_back(denom); 
	//monitor symbol status
	if (fBeatDenom.size()>1)
	{
		fSymbol = multiple;
	}
}
		
void IMUSANT_time::operator=(const IMUSANT_time& time)
{
	fBeatNum = time.getNumerator();
	fBeatDenom = time.getDenominator();
	fSymbol = time.getSymbol();
}

IMUSANT_clef& IMUSANT_clef::operator= (const IMUSANT_clef& clef)
{
	fSign = clef.getSign();
	fLine = clef.getLine();
	fOctaveChange = clef.getTransposition();
	
	return *this;
}

bool IMUSANT_clef::operator!= (const IMUSANT_clef& clef) const
{
	return (fSign != clef.getSign() || fLine != clef.getLine() || fOctaveChange != clef.getTransposition());
}

bool IMUSANT_clef::operator== (const IMUSANT_clef& clef) const
{
	return (fSign == clef.getSign() && fLine == clef.getLine() && fOctaveChange == clef.getTransposition());
}


void	IMUSANT_time::print(ostream& os) const
{
	os << "<TIME>";
	vector<long>::const_iterator num=fBeatNum.begin(); 
	while (num!=fBeatNum.end())
	{
		os << *num;
		num++;
		if (num!=fBeatNum.end()) os << "+";
	}
	
	os << "/";
	
	vector<long>::const_iterator denom=fBeatDenom.begin(); 
	while (denom!=fBeatDenom.end())
	{
		os << *denom;
		denom++;
		if (denom!=fBeatDenom.end()) os << "+";
	}
	
	os << "<\\TIME>" << endl;
}

}


		
