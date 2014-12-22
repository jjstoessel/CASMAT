/*
 *  IMUSANT_conversions.cpp
 *  imusant
 *
 *  Created by Jason Stoessel on 13/06/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "IMUSANT_conversions.h"

#include <string>

using namespace std;

namespace IMUSANT
{

//NoteStyle type
IMUSANT_NoteStyle::type 	IMUSANT_NoteStyle::fTypeTbl[] = { hidden, normal, grace, cue };
string 	IMUSANT_NoteStyle::fTypeStrings[] = { "hidden", "normal", "grace", "cue" };  
bimap<string, IMUSANT_NoteStyle::type> IMUSANT_NoteStyle::fType2String(fTypeStrings, fTypeTbl, count);

const string	IMUSANT_NoteStyle::xml (IMUSANT_NoteStyle::type d) { return fType2String[d]; }
    //! convert a MusicXML string to a numeric start-stop value
IMUSANT_NoteStyle::type	IMUSANT_NoteStyle::xml (const string str) { return fType2String[str]; }

//NoteType type
IMUSANT_NoteType::type 	IMUSANT_NoteType::fTypeTbl[] = { pitch, rest, nonpitch };
string 	IMUSANT_NoteType::fTypeStrings[] = { "pitch", "rest", "nonpitch" };  
bimap<string, IMUSANT_NoteType::type> IMUSANT_NoteType::fType2String(fTypeStrings, fTypeTbl, count);

const string	IMUSANT_NoteType::xml (IMUSANT_NoteType::type d) { return fType2String[d]; }
//! convert a MusicXML string to a numeric start-stop value
IMUSANT_NoteType::type	IMUSANT_NoteType::xml (const string str) { return fType2String[str]; }


//=======================================================================================================
//IMUSANT_syllabic
					
IMUSANT_syllabic::type	IMUSANT_syllabic::fTypeTbl[] = { undefined, single, multisingle, begin, middle, end, 
						beginend, beginmiddle, middleend };						
string	IMUSANT_syllabic::fTypeStrings[] = { "undefined", "single", "multisingle", "begin", "middle", "end", 
						"beginend", "beginmiddle", "middleend" };
bimap<string, IMUSANT_syllabic::type>	IMUSANT_syllabic::fType2String(fTypeStrings, fTypeTbl, count);
//! convert a numeric start-stop value to a MusicXML string
const string IMUSANT_syllabic::xml (IMUSANT_syllabic::type type) { return fType2String[type]; }
//! convert a MusicXML string to a numeric value
IMUSANT_syllabic::type	IMUSANT_syllabic::xml (const string str) { return fType2String[str]; }

//convert TLyric Syllabic to IMUSANT_lyric syllabic
IMUSANT_syllabic::type	IMUSANT_syllabic::MusicXML2IMUSANTSyllabic(const TLyric::syllabic musicXMLType)
{
	type rType = undefined;
	
	switch (musicXMLType)
	{
		case TLyric::single:
			rType = single;
			break;
		case TLyric::begin:
			rType = begin;
			break;
		case TLyric::end:
			rType = end;
			break;
		case TLyric::middle:
			rType = middle;
			break;
	}
	
	return rType;
}

}//namespace IMUSANT