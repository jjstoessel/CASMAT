/*
 *  IMUSANT_contour_symbol.h
 *  imusant
 *
 *  Created by Jason Stoessel on 16/08/06.
 *  Copyright 2006 Jason Stoessel. All rights reserved.
 *
 *	This is the engine for generating and creating instances of contour symbols.  Several operators are provided for
 *	convenience and comparison.
 *	See E. Cambouropoulos, et al. "A Pattern exraction algorithm for abstract melodic representations that allow partial overlapping
 *	if intervallic categories", in Proceedings of the Sixth Inernational Conference on Music Information Retrieval (ISMIR 2005), London, 167-174.
 */

 
#ifndef __IMUSANT_CONTOUR_SYMBOL__
#define __IMUSANT_CONTOUR_SYMBOL__

#include <vector>

#include "smartpointer.h"
#include "IMUSANT_pitch.h"
#include "IMUSANT_key.h"
#include "bimap.h"
#include "IMUSANT_interval.h"

#define FLAGSPACE 0x2000

using namespace std;

namespace IMUSANT
{

class IMUSANT_contour_symbol : public smartable
{
	public:
		enum {	dont_care_down=-3, leap_down=-2, step_down=-1, unison=0, step_up=1, leap_up=2, 
				dont_care_up=3, count=7, undefined=0x4FFFFFFF }; //undefined is internal variable
		
	friend SMARTP<IMUSANT_contour_symbol> new_IMUSANT_contour_symbol();
	friend SMARTP<IMUSANT_contour_symbol> new_IMUSANT_contour_symbol(const S_IMUSANT_pitch previous, const S_IMUSANT_pitch current);
	
		//getter and setters
		void				setLocation(long partID, long startMeasure, 
								long startNoteIndex, long endMeasure, long endNoteIndex);
		IMUSANT_range		getLocation() const { return fLocation; }
		//returns the inverted interval
		IMUSANT_contour_symbol	inverted();
		//calculates the diatonic inversion required for pre-20th century music
		IMUSANT_contour_symbol	inverted_diatonically(IMUSANT_key& key, IMUSANT_pitch::type first);
		//returns distance between intervals, hence 0 is equal, hence used in comparison operators
		signed int			compare(const IMUSANT_contour_symbol& i) const;
		
		//operators
		inline bool operator==(const IMUSANT_contour_symbol& rhs) const	{ return (compare(rhs)==0); }
		inline bool operator!=(const IMUSANT_contour_symbol& rhs) const	{ return (compare(rhs)!=0); }
		inline bool operator<(const IMUSANT_contour_symbol& rhs) const	{ return (compare(rhs)<0); }
		inline bool operator>(const IMUSANT_contour_symbol& rhs) const	{ return (compare(rhs)>0); }
		inline bool operator<=(const IMUSANT_contour_symbol& rhs) const	{ return (compare(rhs)<=0); }
		inline bool operator>=(const IMUSANT_contour_symbol& rhs) const	{ return (compare(rhs)>=0); }
		void operator+(const IMUSANT_contour_symbol& rhs );	
		friend ostream& operator<<( ostream& os, const IMUSANT_contour_symbol& i );
		friend istream& operator>>( istream& is, IMUSANT_contour_symbol& i );
		const IMUSANT_contour_symbol& operator=( const IMUSANT_contour_symbol& rhs );
		//conversion operators
		const IMUSANT_contour_symbol& operator=( const signed int binv );
		inline operator signed int() const { return fSymbol; }
		//increment/decrement
		friend IMUSANT_contour_symbol operator+( const IMUSANT_contour_symbol& lhs, const IMUSANT_contour_symbol& rhs );
		friend IMUSANT_contour_symbol operator-( const IMUSANT_contour_symbol& lhs, const IMUSANT_contour_symbol& rhs );
		IMUSANT_contour_symbol& operator+=( const IMUSANT_contour_symbol& rhs );
		IMUSANT_contour_symbol& operator-=( const IMUSANT_contour_symbol& rhs );
		
		IMUSANT_contour_symbol& operator++(); //prefix: returns &*this
		const IMUSANT_contour_symbol operator++(int); //postfix: returns copy
	
	//static function returns interval and direction	
	static IMUSANT_contour_symbol calculate(const S_IMUSANT_pitch& first, const S_IMUSANT_pitch& second);
	//! convert a numeric value to string
	static const string	xmlinterval (int iv);
	//! convert a string to a numeric value
	static       int	xmlinterval (const string str);
	//! make a unique interval to append for suffix tree
	static IMUSANT_contour_symbol MakeUniqueSymbol();
	
    //protected:
		IMUSANT_contour_symbol() : fSymbol(undefined) {}
		IMUSANT_contour_symbol(const IMUSANT_contour_symbol& iv)\
			: fSymbol(iv.fSymbol), fLocation(iv.fLocation) {}
		IMUSANT_contour_symbol(const S_IMUSANT_pitch first, const S_IMUSANT_pitch second);
		IMUSANT_contour_symbol(signed short iv) : fSymbol(iv) { check(); }
		virtual ~IMUSANT_contour_symbol(){}
	private:
	
		void			check();
		
		int				fSymbol;
		IMUSANT_range	fLocation;
		
	static bimap<string, int>	fSymbol2String;
	static int	fSymbolTbl[];
	static string	fSymbolStrings[];
};
typedef SMARTP<IMUSANT_contour_symbol> S_IMUSANT_contour_symbol;


class IMUSANT_contour : public smartable, public vector<IMUSANT_contour_symbol> 
{
	public:
	
		friend SMARTP<IMUSANT_contour> new_IMUSANT_contour();
    
    vector<IMUSANT_contour_symbol>& getContours() { return *this; }
	
};
typedef SMARTP<IMUSANT_contour> S_IMUSANT_contour;

S_IMUSANT_contour new_IMUSANT_contour();
    S_IMUSANT_contour_symbol new_IMUSANT_contour_symbol();
} //namespace IMUSANT
#endif