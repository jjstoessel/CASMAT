/*
 *  IMUSANT_interval.cpp
 *  imusant
 *
 *  Created by Jason Stoessel on 24/06/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 *  Changes:
 *
 *  14 June 2015 getNumber() member function added; a littly flaky. A mathematical solution would be better.
 *  29 June 2015 getQuality() member function added
 */

#include "IMUSANT_interval.h"

#include <stdlib.h>

namespace IMUSANT
{

//binary operators required for + and -
IMUSANT_interval operator+( const IMUSANT_interval& lhs, const IMUSANT_interval& rhs )
{
	IMUSANT_interval ret(lhs);
	
	ret+=rhs;
	ret.check();
	
	return ret;
}

IMUSANT_interval operator-( const IMUSANT_interval& lhs, const IMUSANT_interval& rhs )
{
	IMUSANT_interval ret(lhs);
	
	ret -= rhs;
	ret.check();
	
	return ret;
}

ostream& operator<<( ostream& os, const IMUSANT_interval& i )
{
	if (i.fOctaves < IMUSANT_interval::undefined-FLAGSPACE) //don't try to print terminator elements.
	{
		os << IMUSANT_interval::xmlinterval(i.fInterval) << " "; 
		os << (((i.fDirection==-1)?("\\"):((i.fDirection==1)?("/"):("")))) << " ";
	}
	else
		os << "undefined ";
	
	return os;
}

istream& operator>>( istream& is, IMUSANT_interval& i )
{
	return is;
}

//ctor functions
S_IMUSANT_interval new_IMUSANT_interval() { IMUSANT_interval* o = new IMUSANT_interval(); assert(o!=0); return o; }
S_IMUSANT_interval new_IMUSANT_interval(const S_IMUSANT_pitch first, const S_IMUSANT_pitch second)
{
	IMUSANT_interval* o = new IMUSANT_interval(first, second);
	assert(o!=0);
	return o;
}

//lookups
int	IMUSANT_interval::fIntervalTbl[] = {	dim1, perf1, aug1, dim2, min2, maj2, aug2, dim3, min3, maj3, aug3, 
											dim4, per4, aug4, dim5, per5, aug5, dim6, min6, maj6, aug6, dim7, 
											min7, maj7, aug7, dim8, octave };
string	IMUSANT_interval::fIntervalStrings[] = { "dim1", "perf1", "aug1", "dim2", "min2", "maj2", "aug2", "dim3",
												"min3", "maj3", "aug3", "dim4", "per4", "aug4", "dim5", "per5", 
												"aug5", "dim6", "min6", "maj6", "aug6", "dim7", "min7", "maj7", 
												"aug7", "dim8", "octave" };
bimap<string, int>	IMUSANT_interval::fInterval2String( fIntervalStrings, fIntervalTbl, 27 );

//! convert a numeric value to string
const string IMUSANT_interval::xmlinterval (int iv) { return fInterval2String[iv]; }
//! convert a string to a numeric value
int	IMUSANT_interval::xmlinterval (const string str) { return fInterval2String[str]; }

IMUSANT_interval IMUSANT_interval::MakeUniqueInterval()
{
	static int unique = undefined;
	
	IMUSANT_interval out;
	
	out.fOctaves = --unique;
	
	if (undefined-unique>FLAGSPACE)
		cerr << "Unique flag limit reached" << endl;
	
	return out;
}
    
//protected ctor member
IMUSANT_interval::IMUSANT_interval(const S_IMUSANT_pitch first, const S_IMUSANT_pitch second)
{
	*this = calculate(first,second);
}
//record note locations that form interval
void
IMUSANT_interval::setLocation(long partID, long startMeasure, long startNoteIndex, long endMeasure, long endNoteIndex)
{
	fLocation.partID = partID;
	fLocation.first.measure = startMeasure;
	fLocation.first.note_index = startNoteIndex;
	fLocation.last.measure = endMeasure;
	fLocation.last.note_index = endNoteIndex;
}

//static function returns interval and direction for two notes
IMUSANT_interval IMUSANT_interval::calculate(const S_IMUSANT_pitch& first, const S_IMUSANT_pitch& second)
{
	IMUSANT_interval ret;
	
	if (first->name()!=IMUSANT_pitch::undefined && second->name()!=IMUSANT_pitch::undefined)
	{
		int first_absolute = (int)first->name()+first->alteration()+(first->octave()*base);
		int second_absolute = (int)second->name()+second->alteration()+(second->octave()*base);
		ret.fOctaves = 0;
		ret.fInterval = second_absolute - first_absolute;
		ret.check();
	}
	
	return ret;
}

//returns the interval numbers without quality
int IMUSANT_interval::getNumber()
{
    int ret;
    
    switch (this->simple())
    {
        case dim1:
        case perf1:
        case aug1:
            ret = 1;
            break;
        case dim2:
        case min2:
        case maj2:
        case aug2:
            ret = 2;
            break;
        case dim3:
        case min3:
        case maj3:
        case aug3:
            ret = 3;
            break;
        case dim4:
        case per4:
        case aug4:
            ret = 4;
            break;
        case dim5:
        case per5:
        case aug5:
            ret = 5;
            break;
        case dim6:
        case min6:
        case maj6:
        case aug6:
            ret = 6;
            break;
        case dim7:
        case min7:
        case maj7:
        case aug7:
            ret = 7;
            break;
        case octave:
            ret = 8;
            break;
        default:
            ret = undefined;
            break;
    }
    
    if (this->simple().fDirection==descending)
        ret *= -1;
    
    return ret;
}

int IMUSANT_interval::getQuality()
{
    int quality = 0;
    
    switch (this->simple())
    {
        case perf1:
        case per5:
        case octave:
            quality = perfect;
            break;
        case min3:
        case maj3:
        case min6:
        case maj6:
            quality = imperfect;
            break;
        case dim1:
        case aug1:
        case dim2:
        case min2:
        case maj2:
        case aug2:
        case dim3:
        case aug3:
        case dim4:
        case per4:
        case aug4:
        case dim5:
        case aug5:
        case dim6:
        case aug6:
        case dim7:
        case min7:
        case maj7:
        case aug7:
            quality = dissonant;
            break;
    }

    return quality;
}
    
//returns a non-compound interval
IMUSANT_interval IMUSANT_interval::simple()
{
	IMUSANT_interval ret(*this);
	
	ret.check();
	ret.fOctaves = 0;
	
	return ret;
}

//returns the literally inverted interval
IMUSANT_interval	IMUSANT_interval::inverted()
{
	IMUSANT_interval ret(*this);
	
	if (ret.fDirection==ascending)
		ret.fDirection = descending;
	else if (ret.fDirection==descending)
		ret.fDirection = ascending;
	
	return ret;
}

//calculates the diatonic inversion required for pre-20th century music
//NOT IMPLEMENTED!
IMUSANT_interval	IMUSANT_interval::inverted_diatonically(IMUSANT_key& key, IMUSANT_pitch::type first)
{
	IMUSANT_interval ret(*this);
	//determine whether pitches are diatonic and map inverted interval to diatonic key.
	//eg. CE->CA (maj3 transformed to min3)
	
	
	return ret;
}

//returns distance between intervals, hence 0 is equal, hence used in comparison operators
signed int	IMUSANT_interval::compare(const IMUSANT_interval& i) const
{
	return (signed int)*this-(signed int)i;
}

//private member function: checks interval is in correct form.
void IMUSANT_interval::check()
{
	//check that fInterval is positive except dim unison
	if (fInterval!=undefined)
	{
		if (fInterval!=0 && fInterval!=-1)
		{
			if (fInterval/abs(fInterval)==1)
				fDirection = ascending;
			else if (fInterval/abs(fInterval)==-1)
			{
				fDirection = descending;
				fInterval = abs(fInterval);
			}
		}
		
		//fInterval should have range -1 to base
		if (fInterval==0) 
			fDirection = unison;
		else if (fInterval>base)
		{
			fOctaves = fInterval/base;
			fInterval %= base;
		}
	}
	else
		cerr << "Check on undefined interval." << endl;
}

//operators
const IMUSANT_interval& IMUSANT_interval::operator=( const IMUSANT_interval& rhs )
{
	fInterval = rhs.fInterval;
	fOctaves = rhs.fOctaves;
	fDirection = rhs.fDirection;
	fLocation = rhs.fLocation;
	return *this;
}

const IMUSANT_interval& IMUSANT_interval::operator=( const signed int binv )
{
	fInterval = binv;
	check();
	
	return *this;
}


IMUSANT_interval& IMUSANT_interval::operator+=( const IMUSANT_interval& rhs )
{
	fInterval = (signed short)*this + (signed short)rhs;
	check();
	return *this;
}

IMUSANT_interval& IMUSANT_interval::operator-=( const IMUSANT_interval& rhs )
{
	fInterval = (signed short)*this - (signed short)rhs;
	check();
	return *this;
}

IMUSANT_interval& IMUSANT_interval::operator++() //prefix: returns &*this
{
	fInterval++;
	check();
	return *this;
}

const IMUSANT_interval IMUSANT_interval::operator++(int) //postfix: returns copy
{
	IMUSANT_interval ret(*this);
	
	ret.fInterval++;
	ret.check();
	
	return ret;
}

}//namespace IMUSANT
