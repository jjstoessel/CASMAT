/*
 *  IMUSANT_pitch.h
 *  imusant
 *
 *  Created by Jason Stoessel on 30/08/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef __IMUSANT_PITCH__
#define __IMUSANT_PITCH__

#include <iostream>
#include <string>

#include "smartpointer.h"
#include "bimap.h"

namespace IMUSANT 
{

class IMUSANT_pitch; //forward declaration

VEXP ostream& operator<< (ostream& os, const IMUSANT_pitch& elt );
/*!
\brief An IMUSANT pitch representation.
This class handles pitch representations
Currently incomplete since alteration only takes account of semitones, not quartertones
*/
class VEXP IMUSANT_pitch : public smartable
{
	public:
	
		enum type { undefined=-1, C=0, D=5, E=10, F=14, G=19, A=24, B=29, last=B, diatonicSteps=7, 
					big_undefined = 0x4FFFFFFF  };
		 
		VEXP friend SMARTP<IMUSANT_pitch> new_IMUSANT_pitch();		
				
				IMUSANT_pitch() :	fName(undefined), fMSName(undefined),\
									fOctave(0), fInChord(false), fVoice(1), fAlteration(0) {}
				IMUSANT_pitch(const IMUSANT_pitch& copy);
		virtual ~IMUSANT_pitch	() {}
		
		void set( type name, unsigned short octave, unsigned short voice, type ms_note , signed short accidental=0,
				bool is_chord=false );
        inline void set( type name, unsigned short octave, unsigned short voice, signed short accidental=0,
                    bool is_chord=false) { set(name,octave,voice,name,accidental,is_chord); }
		const type		name() const		{ return fName; }
		signed short	alteration() const	{ return fAlteration; }
		unsigned short 	octave() const		{ return fOctave; }
		const type		ms_name() const		{ return fMSName; }
		bool			in_chord() const	{ return fInChord; }
		unsigned short	voice() const	{ return fVoice; }
		
		void			setName(const type name) { fName=name; }
		void			setAlteration(const signed short alter) { fAlteration = alter; }
		void			setOctave( const unsigned short octave ) { fOctave = octave; }
		void			setMSName( const type msName ) { fMSName = msName; }
		void			setInChord (const bool inChord) { fInChord = inChord; }
		void			setVoice( const unsigned short voice ) { fVoice = voice; }
		
		
		IMUSANT_pitch& operator= (const IMUSANT_pitch& pitch) {
							fName = pitch.name(); fAlteration = pitch.alteration(); fOctave = pitch.octave();
							fMSName = pitch.ms_name(); fInChord = pitch.in_chord(); fVoice = pitch.voice();
							return *this;
						}
		bool operator== (const IMUSANT_pitch& pitch) const { return fName==pitch.name() && fAlteration==pitch.alteration() && fOctave==pitch.octave(); }
		bool operator!= (const IMUSANT_pitch& pitch) const;
		
		friend ostream& operator<< (ostream& os, const IMUSANT_pitch& elt );
		
		void	print (ostream& os) const;
		
		static const string	xml(type d);
		//! convert a string to a numeric pitch
		static type			xml(const string str);
		
		static IMUSANT_pitch MakeUniquePitch();
		
	private:
		
		type			fName;
		signed short	fAlteration;
		unsigned short	fOctave;
		type			fMSName;
		bool			fInChord;
		unsigned short	fVoice;
		
	static bimap<string, type> fPitch2String;
	static type 	fPitchTbl[];
	static string 	fPitchStrings[];
};
typedef SMARTP<IMUSANT_pitch> S_IMUSANT_pitch;

VEXP SMARTP<IMUSANT_pitch> new_IMUSANT_pitch();
    
} //namespace IMUSANT

#endif //__IMUSANT_PITCH__