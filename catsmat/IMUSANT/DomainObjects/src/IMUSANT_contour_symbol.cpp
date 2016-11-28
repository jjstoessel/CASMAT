/*
 *  IMUSANT_contour_symbol.cpp
 *  imusant
 *
 *  Created by Jason Stoessel on 16/08/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "IMUSANT_contour_symbol.h"

#include <stdlib.h>

namespace IMUSANT
{

S_IMUSANT_contour new_IMUSANT_contour() { IMUSANT_contour* o = new IMUSANT_contour(); assert(o!=0); return o; }

//binary operators required for + and -
IMUSANT_contour_symbol operator+( const IMUSANT_contour_symbol& lhs, const IMUSANT_contour_symbol& rhs )
{
	IMUSANT_contour_symbol ret(lhs);
	
	ret+=rhs;
	ret.check();
	
	return ret;
}

IMUSANT_contour_symbol operator-( const IMUSANT_contour_symbol& lhs, const IMUSANT_contour_symbol& rhs )
{
	IMUSANT_contour_symbol ret(lhs);
	
	ret -= rhs;
	ret.check();
	
	return ret;
}

ostream& operator<<( ostream& os, const IMUSANT_contour_symbol& i )
{
	if (i.fSymbol < IMUSANT_contour_symbol::undefined-FLAGSPACE) //don't try to print terminator elements.
		os << IMUSANT_contour_symbol::xmlinterval(i.fSymbol);
	else
		os << "undefined ";
	
	return os;
}

istream& operator>>( istream& is, IMUSANT_contour_symbol& i )
{
	return is;
}

//ctor functions
S_IMUSANT_contour_symbol new_IMUSANT_contour_symbol() { IMUSANT_contour_symbol* o = new IMUSANT_contour_symbol(); assert(o!=0); return o; }
    
S_IMUSANT_contour_symbol new_IMUSANT_contour_symbol(const S_IMUSANT_pitch first, const S_IMUSANT_pitch second)
{
	IMUSANT_contour_symbol* o = new IMUSANT_contour_symbol(first, second);
	assert(o!=0);
	return o;
}

//lookups
int	IMUSANT_contour_symbol::fSymbolTbl[] = {	dont_care_down, leap_down, step_down, unison, step_up, leap_up, 
												dont_care_up };
//string	IMUSANT_contour_symbol::fSymbolStrings[] = { "#", "-l", "-s", "u", "s", "l", "*" };
string	IMUSANT_contour_symbol::fSymbolStrings[] = { "#", "leapdown", "stepdown", "repeat", "stepup", "leapup", "*" };
bimap<string, int>	IMUSANT_contour_symbol::fSymbol2String( fSymbolStrings, fSymbolTbl, count );

//! convert a numeric value to string
const string IMUSANT_contour_symbol::xmlinterval (int iv) { return fSymbol2String[iv]; }
//! convert a string to a numeric value
int	IMUSANT_contour_symbol::xmlinterval (const string str) { return fSymbol2String[str]; }

IMUSANT_contour_symbol IMUSANT_contour_symbol::MakeUniqueSymbol()
{
	static int unique = undefined;
	
	IMUSANT_contour_symbol out;
	
	out.fSymbol = --unique;
	
	if (undefined-unique>FLAGSPACE)
		cerr << "Unique flag limit reached" << endl;
	
	return out;
}
//protected ctor member
IMUSANT_contour_symbol::IMUSANT_contour_symbol(const S_IMUSANT_pitch first, const S_IMUSANT_pitch second)
{
	*this = calculate(first,second);
}
//record note locations that form interval
void
IMUSANT_contour_symbol::setLocation(long startPartID, long startMeasure, long startNoteIndex, long endPartID, long endMeasure, long endNoteIndex)
{
	fLocation.first.partID = startPartID;
	fLocation.first.measure = startMeasure;
	fLocation.first.note_index = startNoteIndex;
    fLocation.last.partID = endPartID;
	fLocation.last.measure = endMeasure;
	fLocation.last.note_index = endNoteIndex;
}

//static function returns interval and direction for two notes
IMUSANT_contour_symbol IMUSANT_contour_symbol::calculate(const S_IMUSANT_pitch& first, const S_IMUSANT_pitch& second)
{
	IMUSANT_contour_symbol ret;
	IMUSANT_interval iv = IMUSANT_interval::calculate(first,second);
    IMUSANT_interval dim3(IMUSANT_interval::dim3);
    
	if (iv.getOctaves() == 0)
	{
        
		if (iv==IMUSANT_interval(IMUSANT_interval::unison))
		{
			ret.fSymbol = unison;
		}
		else if (iv.getDirection()==IMUSANT_interval::descending)
		{
			if (iv < dim3)
				ret.fSymbol = step_down;
			else
				ret.fSymbol = leap_down;
		}
		else if (iv.getDirection()==IMUSANT_interval::ascending)
		{
			if (iv < dim3)
				ret.fSymbol = step_up;
			else
				ret.fSymbol = leap_up;
		}
	}
	else
	{
		if (iv.getDirection()==IMUSANT_interval::descending)
		{
			ret.fSymbol = leap_down;
		}
		else if (iv.getDirection()==IMUSANT_interval::ascending)
		{
			ret.fSymbol = leap_up;
		}
	}
	return ret;
}


//returns the literally inverted interval
IMUSANT_contour_symbol	IMUSANT_contour_symbol::inverted()
{
	IMUSANT_contour_symbol ret(*this);
	
	ret.fSymbol = -1*ret.fSymbol;
	
	return ret;
}

//calculates the diatonic inversion required for pre-20th century music
IMUSANT_contour_symbol	IMUSANT_contour_symbol::inverted_diatonically(IMUSANT_key& key, IMUSANT_pitch::type first)
{
	IMUSANT_contour_symbol ret(*this);
	//determine whether pitches are diatonic and map inverted interval to diatonic key.
	//eg. CE->CA (maj3 transformed to min3)
	
	
	return ret;
}

//returns distance between intervals, hence 0 is equal, hence used in comparison operators
signed int	IMUSANT_contour_symbol::compare(const IMUSANT_contour_symbol& i) const
{
	signed int ret = (signed int)*this-(signed int)i;
	//don't care equivalence calculated
	if ((abs(fSymbol)==dont_care_up || abs(i.fSymbol)==dont_care_up) && (abs(ret)==1 || abs(ret)==2))
		ret = 0;
	
	return ret;
}

//private member function: checks interval is in correct form.
void IMUSANT_contour_symbol::check()
{
	if (fSymbol!=undefined)
	{
		if (fSymbol!=0)
		{
			if (fSymbol>leap_up)
				fSymbol = leap_up;
			else if (fSymbol<leap_down)
				fSymbol = leap_down;
		}
	}
	else
		cerr << "Check on undefined interval." << endl;
}

//operators
const IMUSANT_contour_symbol& IMUSANT_contour_symbol::operator=( const IMUSANT_contour_symbol& rhs )
{
	fSymbol = rhs.fSymbol;
	fLocation = rhs.fLocation;
	return *this;
}

const IMUSANT_contour_symbol& IMUSANT_contour_symbol::operator=( const signed int binv )
{
	fSymbol = binv;
	check();
	
	return *this;
}


IMUSANT_contour_symbol& IMUSANT_contour_symbol::operator+=( const IMUSANT_contour_symbol& rhs )
{
	fSymbol = (signed short)*this + (signed short)rhs;
	check();
	return *this;
}

IMUSANT_contour_symbol& IMUSANT_contour_symbol::operator-=( const IMUSANT_contour_symbol& rhs )
{
	fSymbol = (signed short)*this - (signed short)rhs;
	check();
	return *this;
}

IMUSANT_contour_symbol& IMUSANT_contour_symbol::operator++() //prefix: returns &*this
{
	fSymbol++;
	check();
	return *this;
}

const IMUSANT_contour_symbol IMUSANT_contour_symbol::operator++(int) //postfix: returns copy
{
	IMUSANT_contour_symbol ret(*this);
	
	ret.fSymbol++;
	ret.check();
	
	return ret;
}

}//namespace IMUSANT

