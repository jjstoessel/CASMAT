/*
 *  IMUSANT_note.h
 *  imusant - the Intertextual MUSic ANalysis Tool
 *	Project Supervisor: Dr Rex Eakins
 *
 *  Created by Jason Stoessel on 23/05/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef __IMUSANT_note__
#define __IMUSANT_note__

#include "IMUSANT_element.h"
#include "IMUSANT_types.h"
#include "IMUSANT_pitch.h"
#include "IMUSANT_duration.h"
#include "IMUSANT_conversions.h"

#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <list>

using namespace std;

namespace IMUSANT
{

//class IMUSANT_note;
//typedef SMARTP<IMUSANT_note> S_IMUSANT_note;

ostream& operator<< (ostream& os, const S_IMUSANT_note& elt );

/*!
\brief An IMUSANT note representation.

	A note is represented by its name, optional accidentals,
    duration (in the form of numerator/denominator) and optional dots.
*/
class VEXP IMUSANT_note : public IMUSANT_element 
{
        friend bool IMUSANT_pitch::operator> (const IMUSANT_pitch& pitch) const;
	public:
	
        VEXP friend SMARTP<IMUSANT_note> new_IMUSANT_note();
		
		void setPitch( const S_IMUSANT_pitch pitch ) { fPitch = pitch; }
		void setDuration( const S_IMUSANT_duration dur ) { fDuration = dur; }
		void setAccidental( const S_IMUSANT_accidental acc ) { fAccidental = acc; }
		void setMeasureNum (const long measureNum) { fMeasureNumber = measureNum; }
		void setNoteIndex (const long noteIndex) { fNoteIndex = noteIndex; }
		void setNextTieNote (const S_IMUSANT_note& next);
		void setPreviousTieNote (const S_IMUSANT_note& previous);
		void setStyle( IMUSANT_NoteStyle::type style ) { fStyle = style; }
		void setType( IMUSANT_NoteType::type aType ) { fType=aType; }
		
		const long getMeasureNum() const { return fMeasureNumber; }
		const long getNoteIndex () const { return fNoteIndex; }
		const IMUSANT_NoteStyle::type	getStyle() const { return fStyle; }
		const IMUSANT_NoteType::type	getType() const { return fType; }
		const S_IMUSANT_note&	getNextTieNote() const { return fTieNext; }
		const S_IMUSANT_note&	getPreviousTieNote() const { return fTiePrevious; }
		
		void addLyric(const S_IMUSANT_lyric lyric) { fLyrics.push_back(lyric); }
		
		bool isTiedPrevious() const { return fTiePrevious!=0; }
		bool isTiedNext() const { return fTieNext!=0; }
		bool isSingle() const { return !(isTiedPrevious() || isTiedNext()); }
		bool isTiedBothSides() const { return (isTiedPrevious() && isTiedNext()); }
		bool isNotNormal() const { return fStyle!=IMUSANT_NoteStyle::normal; }

        void accept(IMUSANT_visitor& visitor);
		
		void print(ostream& os) const;
		
		friend ostream& operator<< (ostream& os, const S_IMUSANT_note& elt );
		
		IMUSANT_vector<S_IMUSANT_lyric>		lyrics() const { return fLyrics; }
		const S_IMUSANT_pitch&		pitch() const { return fPitch; }
		const S_IMUSANT_duration&	duration() const  { return fDuration; }
		const S_IMUSANT_accidental&	accidental() const { return fAccidental; }
		const IMUSANT_duration		durationWithTies() const; //returns duration plus tied notes
		const IMUSANT_duration		getPreviousTiedDurations() const; //gets duration of all notes tied previously
		const IMUSANT_duration		getNextTiedDurations() const; //get duration of all notes tied next
		
		bool operator== (const IMUSANT_note& note) const;
        bool operator< (const IMUSANT_note& note) const;
    
        static bool higher(const IMUSANT_note& note1, const IMUSANT_note& note2);
    
        //bool operator() (const S_IMUSANT_note& note1, const S_IMUSANT_note& note2) { return higher(*note1, *note2);}

		IMUSANT_note()
            :
            fTieNext(NULL),
            fTiePrevious(NULL),
            fStyle(IMUSANT_NoteStyle::normal),
            fType(IMUSANT_NoteType::pitch)
        {}
    
		IMUSANT_note(S_IMUSANT_pitch& pitch, S_IMUSANT_duration& duration )
			: fPitch(pitch), fDuration(duration), fTieNext(NULL), fTiePrevious(NULL), fStyle(IMUSANT_NoteStyle::normal), fType(IMUSANT_NoteType::pitch) {}
		virtual ~IMUSANT_note(){}
    
	private:
			
		S_IMUSANT_pitch                 fPitch;
		S_IMUSANT_duration              fDuration;
		S_IMUSANT_accidental            fAccidental;
		IMUSANT_vector<S_IMUSANT_lyric>	fLyrics;
		IMUSANT_vector<S_IMUSANT_lyric>	fMSLyrics;		//for distinguising editorial underlay
		string                          fStem;			//not implemented
		string                          fStaff;			//staff name
		long                            fMeasureNumber;	//internal measure reference
		long                            fNoteIndex;		//index of note in measure
		S_IMUSANT_note                  fTieNext;
		S_IMUSANT_note                  fTiePrevious;
		IMUSANT_NoteStyle::type         fStyle;
		IMUSANT_NoteType::type          fType;
};
typedef SMARTP<IMUSANT_note> S_IMUSANT_note;

VEXP SMARTP<IMUSANT_note> new_IMUSANT_note();

} //namespace IMUSANT
#endif
