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

//#define ORIGINAL
#define NEW

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
#ifdef ORIGINAL
        enum type {
            undefined=-1,
            C=0, D=5, E=10, F=14, G=19, A=24, B=29,
            last=B,
            diatonicSteps=7,
            big_undefined =0x4FFFFFFF};
#endif
#ifdef  NEW
        enum type {
            undefined=-1,
            C=0, D, E, F, G, A, B,
            last=B,
            diatonicSteps=7,
            big_undefined =0x4FFFFFFF};
        
        enum sign {
            double_flat = -2,
            flat = -1,
            natural = 0,
            sharp = 1,
            double_sharp = 2
        };
        
        typedef enum TPC// tonal pitch classes - C based.
        {
            tpcFbb=-15,
            tpcCbb=-14, tpcGbb=-13, tpcDbb=-12, tpcAbb=-11, tpcEbb=-10, tpcBbb=-9, tpcFb=-8,
            tpcCb=-7, tpcGb=-6, tpcDb=-5, tpcAb=-4, tpcEb=-3, tpcBb=-2, tpcF=-1,
            tpcC=0, tpcG=1, tpcD=2, tpcA=3, tpcE=4, tpcB=5, tpcFs=6,
            tpcCs=7, tpcGs=8, tpcDs=9, tpcAs=10, tpcEs=11, tpcBs=12, tpcFss=13,
            tpcCss=14, tpcGss=15, tpcDss=16, tpcAss=17, tpcEss=18, tpcBss=19, tpcUndefined=0x4FFFFFFF
        } TPC;
#endif

        
        VEXP friend SMARTP<IMUSANT_pitch> new_IMUSANT_pitch();
        
        IMUSANT_pitch() :
        fName(undefined),
        fMSName(undefined),
        fOctave(0),
        fInChord(false),
        fVoice(1),
        fAlteration(natural)
        {
        }
        
        IMUSANT_pitch(const IMUSANT_pitch& copy);
        
        virtual ~IMUSANT_pitch () {}
        
        void set(type name, unsigned short octave, unsigned short voice,
                 type ms_note, sign accidental=natural, bool is_chord=false);
        
        inline void set(type name, unsigned short octave, unsigned short voice,
                        sign accidental=natural, bool is_chord=false)
        {
            set(name,octave,voice,name,accidental,is_chord);
        }

        const type		name() const		{ return fName; }
        const sign      alteration() const	{ return fAlteration; }
        unsigned short 	octave() const		{ return fOctave; }
        const type		ms_name() const		{ return fMSName; }
        bool			in_chord() const	{ return fInChord; }
        unsigned short	voice() const       { return fVoice; }
#ifdef NEW
        int             getTPC() const         { return fTPC; }
#endif
        
        void			setName(const type name) { fName=name; }
        void            setName(const string name) { fName = xml(name); }
        void			setAlteration(const sign alter) { fAlteration = alter; }
        void            setAlteration(const string alter);   // A number of semitones with +ve being sharp and -ve being flat. No validation performed.
        void			setOctave( const unsigned short octave ) { fOctave = octave; }
        void			setOctave( const string octave );
        void			setMSName( const type msName ) { fMSName = msName; }
        void			setInChord (const bool inChord) { fInChord = inChord; }
        void			setVoice( const unsigned short voice )
        {
            fVoice = voice;
        }
        
        
        IMUSANT_pitch& operator= (const IMUSANT_pitch& pitch)
        {
            set(pitch.name(), pitch.octave(), pitch.voice(), pitch.ms_name(), pitch.alteration(), pitch.in_chord());
            return *this;
        }
        
        bool operator== (const IMUSANT_pitch& pitch) const;
        
        bool operator!= (const IMUSANT_pitch& pitch) const;
        
        //
        // "greater than" is interpreted to mean "of a higher pitch"
        //
        bool operator> (const IMUSANT_pitch& pitch) const;
        
        friend ostream& operator<< (ostream& os, const IMUSANT_pitch& elt );
        
        void	print (ostream& os) const;
        
        static const string	xml(type d);
        //! convert a string to a numeric pitch
        static type			xml(const string str);
#ifdef NEW
        void                setTonalPitchClass() { fTPC = GetTonalPitchClass(fName, fAlteration); }
        static  enum TPC     GetTonalPitchClass(type name, sign alt);
#endif
        static IMUSANT_pitch MakeUniquePitch();
        
    private:
        
        type			fName;
        sign            fAlteration;
        unsigned short	fOctave;
        type			fMSName;
        bool			fInChord;
        unsigned short	fVoice;
       
        
        static bimap<string, type> fPitch2String;
        static type 	fPitchTbl[];
        static string 	fPitchStrings[];
#ifdef NEW
        TPC             fTPC; //tonal pitch class storage, based on line of fifths
        int             fNPC; //non-tonal pitch class storage, i.e. C=0, C#/Db=1, etc.
        static int      fLineOf5ths[35][3];
#endif

    };
    
    typedef SMARTP<IMUSANT_pitch> S_IMUSANT_pitch;
    
    VEXP SMARTP<IMUSANT_pitch> new_IMUSANT_pitch();
    
} //namespace IMUSANT

#endif //__IMUSANT_PITCH__