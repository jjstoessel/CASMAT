/*
 *  IMUSANT_key.cpp
 *  imusant
 *
 *  Created by Jason Stoessel on 30/08/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "IMUSANT_key.h"
#include "TKey.h"

using namespace MusicXML;

namespace IMUSANT 
{


//IMUSANT_key consts
IMUSANT_key::mode IMUSANT_key::fmodeTbl[] = { generic, dorian, hypodorian, phrygian, hypophrygian, lydian, hypolydian, 
												mixolydian, hypomixolydian, aeolian, locrian, ionian, major, minor };
string IMUSANT_key::fModeStrings[] = { "generic", "dorian", "hypodorian", "phrygian", "hypophrygian", "lydian", 
										"hypolydian", "mixolydian", "hypomixolydian", "aeolian", "locrian", "ionian", 
										"major", "minor" };
bimap<string, IMUSANT_key::mode> IMUSANT_key::fMode2String(fModeStrings, fmodeTbl, last);

const string IMUSANT_key::xmlmode (mode m) { return fMode2String[m]; }
		//! convert a string to a numeric value
IMUSANT_key::mode IMUSANT_key::xmlmode (const string str) { return fMode2String[str]; }
//0 to fFifth-1 gives containing accidentals
pair<IMUSANT_pitch::type,signed short> IMUSANT_key::fFlatFifthsTbl[] = 
{ 
	make_pair(IMUSANT_pitch::B,-1), make_pair(IMUSANT_pitch::E,-1), make_pair(IMUSANT_pitch::A,-1), make_pair(IMUSANT_pitch::D,-1), 
	make_pair(IMUSANT_pitch::G,-1), make_pair(IMUSANT_pitch::C,-1), make_pair(IMUSANT_pitch::F,-1), make_pair(IMUSANT_pitch::B,-2), 
	make_pair(IMUSANT_pitch::E,-2), make_pair(IMUSANT_pitch::A,-2)
};
pair<IMUSANT_pitch::type,signed short> IMUSANT_key::fSharpFifthsTbl[] = 
{ 
	make_pair(IMUSANT_pitch::F,1), make_pair(IMUSANT_pitch::C,1), make_pair(IMUSANT_pitch::G,1), make_pair(IMUSANT_pitch::D,1), 
	make_pair(IMUSANT_pitch::A,1), make_pair(IMUSANT_pitch::E,1), make_pair(IMUSANT_pitch::B,1), make_pair(IMUSANT_pitch::F,2),
	make_pair(IMUSANT_pitch::C,2), make_pair(IMUSANT_pitch::G,2)
};

ostream& operator<< (ostream& os, const IMUSANT_key& elt )
{
	elt.print(os); return os;
}

IMUSANT_key::mode IMUSANT_key::ConvertXML2IMUSANTMode( const long xmlMode )
{
	mode IMUSANT_mode = IMUSANT_key::generic;
	
	switch (xmlMode)
	{
		case TKey::major:
			IMUSANT_mode = IMUSANT_key::major;
			break;
		case TKey::minor: 
			IMUSANT_mode = IMUSANT_key::minor;
			break;
		case TKey::dorian:
			IMUSANT_mode = IMUSANT_key::dorian;
			break;
		case TKey::phrygian:
			IMUSANT_mode = IMUSANT_key::phrygian;
			break;
		case TKey::lydian:
			IMUSANT_mode = IMUSANT_key::lydian;
			break;
		case TKey::mixolydian:
			IMUSANT_mode = IMUSANT_key::mixolydian;
			break;
		case TKey::aeolian:
			IMUSANT_mode = IMUSANT_key::aeolian;
			break;
		case TKey::ionian:
			IMUSANT_mode = IMUSANT_key::ionian;
			break;
		case TKey::locrian:
			IMUSANT_mode = IMUSANT_key::locrian;
			break;
		//Music XML only appears to store authentic modes.
	}
	
	return IMUSANT_mode;
}

bool IMUSANT_key::PitchAlterInSignature(IMUSANT_pitch::type name, signed short alter)
{
	pair<IMUSANT_pitch::type, signed short> inflectedPitch(name,alter);
	bool keyInflection = false;
	if (fFifths<0)
	{
		for (int i = 0; i>fFifths; i--)
		{
			if (fFlatFifthsTbl[i]==inflectedPitch) 
			{
				keyInflection=true;
				break;
			}
		}
	}
	else if (fFifths>0)
	{
		for (int j = 0; j<fFifths; j++)
		{
			if (fSharpFifthsTbl[j]==inflectedPitch) 
			{
				keyInflection=true;
				break;
			}
		}
	}

	return keyInflection;
}

void IMUSANT_key::print(ostream& os) const
{
	os << "<KEY>" << fFifths << ", mode: " << fMode << "<\\KEY>" << endl;
}
//------------------------------------------------------------------------------
void IMUSANT_key::CalcMode ()
{
	//determine mode from tonic/finalis and key
}

void IMUSANT_key::operator=(const IMUSANT_key& key)
{
	fFifths = key.getFifths();
	fMode = key.getMode();
	fCancel = key.getCancel();
}

bool IMUSANT_key::operator==(const IMUSANT_key& key) const
{
	return ((fFifths == key.getFifths()) && (fMode == key.getMode()) && (fCancel == key.getCancel()));
}

bool IMUSANT_key::operator!=(const IMUSANT_key& key) const
{
	return ((fFifths != key.getFifths()) || (fMode != key.getMode()) || (fCancel != key.getCancel()));
}



} //namespace IMUSANT