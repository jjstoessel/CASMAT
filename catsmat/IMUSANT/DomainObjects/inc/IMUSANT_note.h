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
    ostream& operator<< (ostream& os, const S_IMUSANT_note& elt );
    
    typedef vector<S_IMUSANT_note> IMUSANT_note_vector;
    
    /*!
     \brief An IMUSANT note representation.
     
     A note is represented by its name, optional accidentals,
     duration (in the form of numerator/denominator) and optional dots.
     */
    class VEXP IMUSANT_note : public IMUSANT_element
    {
        friend bool IMUSANT_pitch::operator> (const IMUSANT_pitch& pitch) const;
        
    public:
        
        VEXP friend IMUSANT_SMARTP<IMUSANT_note> new_IMUSANT_note();
        
        IMUSANT_note();
        IMUSANT_note(S_IMUSANT_pitch& pitch, S_IMUSANT_duration& duration );
        IMUSANT_note(const IMUSANT_note& note);
        
        ~IMUSANT_note();
        
        void setPitch( const IMUSANT_pitch& pitch ) { *fPitch = pitch; }
        void setDuration( const IMUSANT_duration& dur ) { *fDuration = dur; }
        void setAccidental( const IMUSANT_accidental& acc ) { *fAccidental = acc; }
        void setMeasureNum (const long measureNum) { fMeasureNumber = measureNum; }
        void setNoteIndex (const long noteIndex) { fNoteIndex = noteIndex; }
        void setNextTieNote (const S_IMUSANT_note& next);
        void setPreviousTieNote (const S_IMUSANT_note& previous);
        void setStyle( IMUSANT_NoteStyle::type style ) { fStyle = style; }
        void setType( IMUSANT_NoteType::type aType ) { fType=aType; }
        void setVoice (int voice ) { fVoice=voice; }
        void setFermata(bool hasFermata) { fHasFermata = hasFermata; }
        
        const long getMeasureNum() const { return fMeasureNumber; }
        const long getNoteIndex () const { return fNoteIndex; }
        const IMUSANT_NoteStyle::type	getStyle() const { return fStyle; }
        const IMUSANT_NoteType::type	getType() const { return fType; }
        const S_IMUSANT_note&	getNextTieNote() const { return fTieNext; }
        const S_IMUSANT_note&	getPreviousTieNote() const { return fTiePrevious; }
        const int getVoice() const { return fVoice; }
        
        void addLyric(const S_IMUSANT_lyric lyric) { fLyrics.push_back(lyric); }
        
        bool isTiedPrevious() const { return fTiePrevious!=NULL; }
        bool isTiedNext() const { return fTieNext!=NULL; }
        bool isSingle() const { return !(isTiedPrevious() || isTiedNext()); }
        bool isTiedBothSides() const { return (isTiedPrevious() && isTiedNext()); }
        bool isNotNormal() const { return fStyle!=IMUSANT_NoteStyle::normal; }
        bool hasFermata() const { return fHasFermata; }
        bool isRest() const { return fType == IMUSANT_NoteType::rest ; }
                
        void accept(IMUSANT_visitor& visitor);
        
        void print(ostream& os) const;
        void print_short(ostream& os) const;
        ostream& pretty_print(ostream& os) const;
        string pretty_print() const;
        
        friend ostream& operator<< (ostream& os, const S_IMUSANT_note& elt );
        
        IMUSANT_vector<S_IMUSANT_lyric>		lyrics() const { return fLyrics; }
        const S_IMUSANT_pitch		pitch() const { return fPitch; }
        const S_IMUSANT_duration	duration() const  { return fDuration; }
        const S_IMUSANT_accidental	accidental() const { return fAccidental; }
        const IMUSANT_duration		durationWithTies() const; //returns duration plus tied notes
        const IMUSANT_duration		getPreviousTiedDurations() const; //gets duration of all notes tied previously
        const IMUSANT_duration		getNextTiedDurations() const; //get duration of all notes tied next
        
        IMUSANT_note& operator= (const IMUSANT_note& rhs);
        bool operator== (const IMUSANT_note& note) const;
        bool operator< (const IMUSANT_note& note) const;
        
        static bool higher(const IMUSANT_note& note1, const IMUSANT_note& note2);

        
    private:
        
        void    initialize();
        
        S_IMUSANT_pitch                 fPitch;
        S_IMUSANT_duration              fDuration;
        S_IMUSANT_accidental            fAccidental;
        IMUSANT_vector<S_IMUSANT_lyric>	fLyrics;
        IMUSANT_vector<S_IMUSANT_lyric>	fMSLyrics;		//for distinguising editorial underlay
        string                          fStem;			//not implemented
        string                          fStaff;			//staff name
        long                            fMeasureNumber;	//internal measure reference
        long                            fNoteIndex;		//index of note in measure
        S_IMUSANT_note                  fTieNext = NULL;
        S_IMUSANT_note                  fTiePrevious = NULL;
        IMUSANT_NoteStyle::type         fStyle;
        IMUSANT_NoteType::type          fType;
        int                             fVoice;
        bool                            fHasFermata = false;
        
    };
    typedef IMUSANT_SMARTP<IMUSANT_note> S_IMUSANT_note;
    
    VEXP IMUSANT_SMARTP<IMUSANT_note> new_IMUSANT_note();
    
} //namespace IMUSANT
#endif
