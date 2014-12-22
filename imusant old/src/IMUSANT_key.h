/*
 *  IMUSANT_key.h
 *  imusant
 *
 *  Created by Jason Stoessel on 30/08/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __IMUSANT_KEY__
#define __IMUSANT_KEY__

#include <string>

#include "bimap.h"
#include "IMUSANT_pitch.h"

namespace IMUSANT
{

class IMUSANT_key;

VEXP ostream& operator<< (ostream& os, const IMUSANT_key& elt );

/*!
\brief An IMUSANT key representation.
*/
class VEXP IMUSANT_key
{
	public:
	
		enum { undefined=-1 };
        enum mode {  generic = 0, dorian=1, hypodorian, phrygian, hypophrygian, lydian, hypolydian, mixolydian, hypomixolydian, aeolian, 
                locrian, ionian, major, minor, last=minor};
				
		IMUSANT_key (long fifths=undefined, mode m=IMUSANT_key::generic, long cancel=undefined)
			: fFifths(fifths), fMode(m), fCancel(cancel) { }
			
		void operator=(const IMUSANT_key& key);
		bool operator==(const IMUSANT_key& key) const;
		bool operator!=(const IMUSANT_key& key) const;
	
		long	getFifths()	const	{ return fFifths; }
		mode	getMode() const		{ return fMode; }
		long	getCancel()	const	{ return fCancel; }
		
		void	setFifths(const long fifths) { fFifths = fifths; }
		void	setMode(const mode m) { fMode = m; }
		void	setCancel(const long cancel) { fCancel = cancel; }
		
		bool	isDefined() const { return (fMode != generic) && (fFifths!=undefined) && (fCancel!=undefined); }
		
		void	print(ostream& os) const;
		
		bool	PitchAlterInSignature(IMUSANT_pitch::type name, signed short alter);
		
	static const string	xmlmode (mode m);
		//! convert a string to a numeric value
	static       mode	xmlmode (const string str);
	
	static mode	ConvertXML2IMUSANTMode( const long xmlMode );
	
	
	
	private:
	
		void	CalcMode(); //function determines mode based on signature (fifths) and tonic (or finalis)
	
		long	fFifths; //+/- 0-11 (or more), -1 = F maj or D min
		mode	fMode;
		long	fCancel;
		
	static bimap<string, mode>	fMode2String;
	static mode					fmodeTbl[];
	static string				fModeStrings[];
	static pair<IMUSANT_pitch::type,signed short> fFlatFifthsTbl[];
	static pair<IMUSANT_pitch::type,signed short> fSharpFifthsTbl[];
	
};

} //namespace IMUSANT
#endif //__IMUSANT_KEY__