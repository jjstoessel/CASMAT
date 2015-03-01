/*
 *  IMUSANT_duration.cpp
 *  imusant
 *
 *  Created by Jason Stoessel on 30/08/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */


#include "IMUSANT_duration.h"

namespace IMUSANT
{

//static strings of durations
TRational IMUSANT_duration::unmeasured(0,1);
TRational IMUSANT_duration::maxima(8,1);
TRational IMUSANT_duration::longa(4,1);
TRational IMUSANT_duration::breve(2,1);
TRational IMUSANT_duration::semibreve(1,1);
TRational IMUSANT_duration::minim(1,2);
TRational IMUSANT_duration::crochet(1,4);
TRational IMUSANT_duration::quaver(1,8);
TRational IMUSANT_duration::semiquaver(1,16); //16th
TRational IMUSANT_duration::demisemiquaver(1,32); //32nd
TRational IMUSANT_duration::hemidemisemiquaver(1,64); //64th
TRational IMUSANT_duration::hundredandtwentyeighth(1,128);  //unmentionable duration

//ctor functions
S_IMUSANT_duration new_IMUSANT_duration() { IMUSANT_duration* o = new IMUSANT_duration(); assert (o!=0); return o; }

//______________________________________________________________________________
TRational IMUSANT_duration::fDurationTbl[] = {	unmeasured, maxima, longa, breve, semibreve, minim, crochet, quaver, 
												semiquaver, demisemiquaver, hemidemisemiquaver, hundredandtwentyeighth };
string IMUSANT_duration::fDurationStrings[]	= { "unmeasured", "maxima", "longa", "breve", "semibreve", "minim", "crochet", "quaver",\
										"semiquaver", "demisemiquaver", "hemidemisemiquaver", "hundredandtwentyeighth" };
bimap<string, TRational> IMUSANT_duration::fDuration2String(fDurationStrings, fDurationTbl, 12);

//______________________________________________________________________________
const string IMUSANT_duration::xml(TRational d) 	{ return fDuration2String[d]; }
TRational	IMUSANT_duration::xml(const string str) { return fDuration2String[str]; }

ostream& operator<< (ostream& os, const IMUSANT_duration& elt )
{
	elt.print(os);
    return os;
}

//--
//takes durations and reduces them to simplest form
long IMUSANT_duration::NormaliseDuration(TRational& dur)
{
	dur.rationalise();
	
	long dots = 0;
	/*long n = dur.getNumerator();
	long d = dur.getDenominator();
	while ( n > d )
	{
		n/=2;
		d/=2;
		dots++;
		dur -= TRational(dots, dur.getDenominator());
	}*/
    TRational sesquialtera(3,2);
    
    while   (
             dur.getNumerator()!=0 && \
            (dur.getNumerator() > dur.getDenominator() || \
             dur.getDenominator()%dur.getNumerator()==1 || \
             dur.getDenominator()%dur.getNumerator()==2 )
            )
    {
        dots++;
        dur /= sesquialtera;
    }
	
	dur.rationalise();
	
	return dots;
}

//--
//Comparision operators
//these also test for equality/inequality of simplified durations: see getSimplifiedDuration.
bool IMUSANT_duration::operator!= (const IMUSANT_duration& dur) const	
{ 
	return (fDuration!=dur.fDuration) || (fDots!=dur.fDots) || (fTimeModification!=dur.fTimeModification)
	  || (getSimplifiedDuration().fDuration!=dur.getSimplifiedDuration().fDuration); 
}

bool IMUSANT_duration::operator== (const IMUSANT_duration& dur) const	
{ 
	return ((fDuration==dur.fDuration) && (fDots!=dur.fDots) && (fTimeModification==dur.fTimeModification)) 
	|| (getSimplifiedDuration().fDuration==dur.getSimplifiedDuration().fDuration); 
}
//--
//Adds two durations, resulting in an absolute duration without dots or time modification
//To do: check for simple relationships (dots and time modification) in resulting float
IMUSANT_duration	IMUSANT_duration::operator+(const IMUSANT_duration& right)
{
	IMUSANT_duration out;
	
	TRational r = TRational(IMUSANT_duration::xml(getSimplifiedDuration().fDuration)) \
				+ TRational(IMUSANT_duration::xml(right.getSimplifiedDuration().fDuration));
	out.fDots = NormaliseDuration(r);
	out.fDuration = IMUSANT_duration::xml(r.toString());
	out.fTimeModification=1; 
				
	return out; 
}

void	IMUSANT_duration::operator+=(const IMUSANT_duration& rhs)
{
    *this = *this + rhs;
}

//--
//Subtracts two durations, resulting in an absolute duration without dots or time modification
//To do: check for simple relationships (dots and time modification) in resulting float
IMUSANT_duration	IMUSANT_duration::operator-(const IMUSANT_duration& right)
{
    IMUSANT_duration out;
    TRational simple_left = getSimplifiedDuration().fDuration;
    TRational simple_right = right.getSimplifiedDuration().fDuration;
    
    TRational r = simple_left - simple_right;
    out.fDots = NormaliseDuration(r);
    out.fDuration = r;
    out.fTimeModification=1;
    
    return out;
}

void	IMUSANT_duration::operator-=(const IMUSANT_duration& rhs)
{
    *this = *this - rhs;
}

bool IMUSANT_duration::operator >(const IMUSANT_duration &dur) const
{
    return (getSimplifiedDuration().fDuration > dur.getSimplifiedDuration().fDuration);
}

bool IMUSANT_duration::operator <(const IMUSANT_duration &dur) const
{
    return (getSimplifiedDuration().fDuration < dur.getSimplifiedDuration().fDuration);
}

//--
//Simplifies durations with dots and/or time proportions to simple float in fDuration w/o dots & time mods
IMUSANT_duration	IMUSANT_duration::getSimplifiedDuration() const
{
	IMUSANT_duration out;
	
	TRational dotsmultiplier(1,1);
	TRational index(1,1);
	
	for (int i = 1; i <= fDots; i++)
	{
		index *= TRational(1,2);
		dotsmultiplier += index;
	}
	
	out.fDuration = fDuration * dotsmultiplier * fTimeModification;
    out.fDots = 0;
	out.fTimeModification=1; 
				
	return out; 
}




} //namespace IMUSANT