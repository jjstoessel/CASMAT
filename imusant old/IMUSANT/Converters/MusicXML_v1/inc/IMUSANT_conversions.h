/*
 *  IMUSANT_conversions.h
 *  imusant
 *
 *  Created by Jason Stoessel on 13/06/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

/*!
\brief provides conversions between numeric line types and strings
*/

#ifndef __IMUSANT_Conversions__
#define __IMUSANT_Conversions__

#include <string>

#include "bimap.h"
#include "TNote.h"

using namespace MusicXML;
using namespace std;

namespace IMUSANT
{

    // TODO - this class seems to contain dependencies om MusicXML v1.
class IMUSANT_NoteStyle 
{
    public:
	enum type { hidden = 0, normal=1, grace=2, cue=3, count=4 };

    //! convert a numeric start-stop value to a MusicXML string
    static const string	xml (type d);
    //! convert a MusicXML string to a numeric value
    static       type	xml (const string str);

    private:
	static bimap<string, type> fType2String;
	static type 	fTypeTbl[];
	static string 	fTypeStrings[];        
};

class IMUSANT_NoteType 
{
    public:
	enum type { pitch, rest, nonpitch, count=3 };

    //! convert a numeric start-stop value to a MusicXML string
    static const string	xml (type d);
    //! convert a MusicXML string to a numeric value
    static       type	xml (const string str);

    private:
	static bimap<string, type> fType2String;
	static type 	fTypeTbl[];
	static string 	fTypeStrings[];        
};

class IMUSANT_syllabic
{
	public:
		//because a IMUSANT lyric can be multisyllabic, bitwise flags are employed.
		enum type { undefined = 0, single=1, multisingle=1<<1, begin=1<<2, middle=1<<3, end=1<<4, 
					beginend=begin|end, beginmiddle=begin|middle, middleend=middle|end, count=9 };
		 //! convert a numericvalue to a string
		static const string	xml (type syll);
		//! convert a string to a numeric value
		static       type	xml (const string str);
		//convert MusicXML syllabic type to IMUSANT syllabic type
		static		 type	MusicXML2IMUSANTSyllabic(const TLyric::syllabic musicXMLType);
		
	private:
		//could add laughing, humming, etc.
		static bimap<string, type>	fType2String;
		static type	fTypeTbl[];
		static string	fTypeStrings[];
};

} //namespace IMUSANT
#endif