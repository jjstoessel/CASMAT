/*
 *  IMUSANT_pitch.cpp
 *  imusant
 *
 *  Created by Jason Stoessel on 30/08/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "IMUSANT_pitch.h"
#include <stdlib.h>

#define FLAGSPACE 0x2000

namespace IMUSANT
{
    
    S_IMUSANT_pitch new_IMUSANT_pitch() { IMUSANT_pitch* o = new IMUSANT_pitch(); assert (o!=0); return o; }
    
    //______________________________________________________________________________
    IMUSANT_pitch::type IMUSANT_pitch::fPitchTbl[] 	= { C, D, E, F, G, A, B };
    string IMUSANT_pitch::fPitchStrings[]			= { "C", "D", "E", "F", "G", "A", "B" };
    bimap<string, IMUSANT_pitch::type> IMUSANT_pitch::fPitch2String(fPitchStrings, fPitchTbl, diatonicSteps);
    //______________________________________________________________________________
    
    const string IMUSANT_pitch::xml(IMUSANT_pitch::type d) 	{ return fPitch2String[d]; }
    IMUSANT_pitch::type	IMUSANT_pitch::xml(const string str) 	{ return fPitch2String[str]; }
    
    ostream& operator<< (ostream& os, const IMUSANT_pitch& elt )
    {
        elt.print(os);
        return os;
    }
    
    //static member
    IMUSANT_pitch IMUSANT_pitch::MakeUniquePitch()
    {
        static int unique = big_undefined;
        
        IMUSANT_pitch out;
        
        out.fOctave = --unique;
        
        if (big_undefined-unique>FLAGSPACE)
            cerr << "Unique flag limit reached" << endl;
        
        return out;
    }
    //copy ctor
    IMUSANT_pitch::IMUSANT_pitch(const IMUSANT_pitch& copy)
    {
        this->set(copy.fName, copy.fOctave, copy.fVoice, copy.fMSName, copy.fAlteration, copy.fInChord);
    }
    
    
    void IMUSANT_pitch::set(type name, unsigned short octave, unsigned short voice, type ms_note, signed short alteration,
                            bool inChord)
    {
        fName = name;
        fAlteration = alteration;
        fOctave = octave;
        fMSName = name; //ms_note;
        fInChord = inChord;
        fVoice = voice;
    }
    
    void
    IMUSANT_pitch::
    setAlteration(const string alter)
    {
        // We are just assuming that the input string is a valid number.
        signed short alteration = atoi(alter.c_str());
        if (alteration == 0 && alter.compare("0") != 0)
        {
            throw "IMUSANT_pitch::setAlteration() - Unexpected value for alter.  Expected a number of semitones received " + alter;
        }
        fAlteration = alteration;
    }
    
    void
    IMUSANT_pitch::
    setOctave( const string octave )
    {
        unsigned short oct = 999; // invalid value will force an exception if atoi fails to return a valid value
        oct = atoi(octave.c_str());
        if (oct < 0 || oct > 9)
        {
            throw "IMUSANT_pitch::setOctave() - Unexpected value for octave.  Expected range 0-9 but received " + octave;
        }
        fOctave = oct;
    }
    
    bool
    IMUSANT_pitch::operator> (const IMUSANT_pitch& pitch) const
    {
        bool gt = false;
        
        if (fOctave > pitch.octave())   // this note is higher because it is in a higher octave.
        {
            gt = true;
        }
        
        if (fOctave == pitch.octave())
        {
            if (fName > pitch.name())   // this note is in the same octave, but is a higher note
            {
                gt = true;
            }
        }
        
        if (fOctave == pitch.octave()
            &&
            fName == pitch.name())
        {
            if (fAlteration > pitch.alteration())  // this note is the same note name and octave, but is sharper.
            {
                gt = true;
            }
        }
        
        return gt;
    }
    
    bool
    IMUSANT_pitch::operator== (const IMUSANT_pitch& pitch) const
    {
        return
        fName==pitch.name() &&
        fAlteration==pitch.alteration() &&
        fOctave==pitch.octave();
    }
    
    void IMUSANT_pitch::print (ostream& os) const
    {
        os << IMUSANT_pitch::xml(fName) << fAlteration << "@" << fOctave /*<< std::endl*/;
    }
    
} //namespace IMUSANT