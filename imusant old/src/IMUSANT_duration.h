/*
 *  IMUSANT_duration.h
 *  imusant
 *
 *  Created by Jason Stoessel on 30/08/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __IMUSANT_DURATION__
#define __IMUSANT_DURATION__

#include <string>
#include <iostream>

#include "smartpointer.h"
#include "TRational.h"
#include "bimap.h"

namespace IMUSANT 
{

class IMUSANT_duration;

VEXP ostream& operator<< (ostream& os, const IMUSANT_duration& elt );

class VEXP IMUSANT_duration : public smartable
{
	public:
        
		/*enum type {	unmeasured = 0, maxima = 1, longa, breve, semibreve, crochet, quaver, semiquaver, demisemiquaver,
			hemidemisemiquaver, hundredandtwentyeighth, last=hundredandtwentyeighth }; */
			
		friend SMARTP<IMUSANT_duration> new_IMUSANT_duration();
			
        const IMUSANT_duration& operator= (const IMUSANT_duration& dur)	
            {	
				fDuration=dur.fDuration; fDots=dur.fDots; 
				fTimeModification=dur.fTimeModification;
				return *this; 
			}
			
		void set( TRational dur, long dots, TRational timemod) { fDuration=dur; fDots=dots, fTimeModification=timemod; }
		
        bool operator!= (const IMUSANT_duration& dur) const;
		bool operator== (const IMUSANT_duration& dur) const;
		
		IMUSANT_duration	getSimplifiedDuration() const;
		
		IMUSANT_duration	operator+(const IMUSANT_duration& right);
		void				operator+=(const IMUSANT_duration& rhs);
        IMUSANT_duration    operator-(const IMUSANT_duration& right);
        void				operator-=(const IMUSANT_duration& rhs);
    
        bool operator >(const IMUSANT_duration &dur) const;
        bool operator >=(const IMUSANT_duration &dur) const 	{return !(*this < dur);}
        bool operator <(const IMUSANT_duration &dur) const;
        bool operator <=(const IMUSANT_duration &dur) const 	{return !(*this > dur);}
		
		friend ostream& operator<< (ostream& os, const IMUSANT_duration& elt );
		
		void	print (ostream& os) const
		{
		}
    
		//checks that TRational type is actually dotted note, return dots and changes dur
        static long	NormaliseDuration(TRational& dur);
		
        static const string	xml(TRational d);
		//! convert a string to a numeric pitch
	
        static TRational	xml(const string str);
		
        TRational		fDuration;
		long		fDots;
		TRational	fTimeModification;
		
		static TRational
			unmeasured,
			maxima,
			longa,
			breve,
			semibreve,
			minim,
			crochet,
			quaver,
			semiquaver, //16th
			demisemiquaver, //32nd
			hemidemisemiquaver, //64th
			hundredandtwentyeighth;  //unmentionalble duration	
			
			IMUSANT_duration(): fDuration(IMUSANT_duration::unmeasured), fDots(0), fTimeModification("1/1") {}
            //copy ctor
            IMUSANT_duration(const IMUSANT_duration& duration) { *this = duration; }
			virtual ~IMUSANT_duration() {}
	protected:
			
			
	static bimap<string, TRational>	fDuration2String;
	static TRational				fDurationTbl[];
	static string					fDurationStrings[];
	
	
};

typedef SMARTP<IMUSANT_duration> S_IMUSANT_duration;
    
SMARTP<IMUSANT_duration> new_IMUSANT_duration();

}
#endif //namespace IMUSANT