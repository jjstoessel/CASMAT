/*
 *  IMUSANT_pitch.cpp
 *  imusant
 *
 *  Created by Jason Stoessel on 30/08/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 *  Changes:
 *
 *  14 Feb 2016 Implemented tonal pitch class based upon David Temperley's Line of Fifths Tonal Pitch class theory 
 *              see: Temperley, "The Line of Fifths," Music Analysis 19/iii (2000): 289–319.
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

    //The line of fifths is a linearisation of the spiral of fifths, where F = -1, C = 0, G = 1, etc.
    //used to obtain the Tonal Pitch Class (TPC) of a note
    //TO IMPLEMENT: PC (or Non-specific Pitch Class)
    int      IMUSANT_pitch::fLineOf5ths[35][3] =
    {
        {C, double_flat,    tpcCbb  },  //Cbb
        {C, flat,           tpcCb   },  //Cb
        {C, natural,        tpcC    },  //C
        {C, sharp,          tpcCs   },  //C#
        {C, double_sharp,   tpcCss  },  //C##
        {D, double_flat,    tpcDbb  },  //Dbb
        {D, flat,           tpcDb   },  //Db
        {D, natural,        tpcD    },  //D
        {D, sharp,          tpcDs   },  //D#
        {D, double_sharp,   tpcDss  },  //D##
        {E, double_flat,    tpcEbb  },  //Ebb
        {E, flat,           tpcEb   },  //Eb
        {E, natural,        tpcE    },  //E
        {E, sharp,          tpcEs   },  //E#
        {E, double_sharp,   tpcEss  },  //E##
        {F, double_flat,    tpcFbb  },  //Fbb
        {F, flat,           tpcFb   },  //Fb
        {F, natural,        tpcF    },  //F
        {F, sharp,          tpcFs   },  //F#
        {F, double_sharp,   tpcFss  },  //F##
        {G, double_flat,    tpcGbb  },  //Gbb
        {G, flat,           tpcGb   },  //Gb
        {G, natural,        tpcG    },  //G
        {G, sharp,          tpcGs   },  //G#
        {G, double_sharp,   tpcGss  },  //G##
        {A, double_flat,    tpcAbb  },  //Abb
        {A, flat,           tpcAb   },  //Ab
        {A, natural,        tpcA    },  //A
        {A, sharp,          tpcAs   },  //A#
        {A, double_sharp,   tpcAss  },  //A##
        {B, double_flat,    tpcBbb  },  //Bbb
        {B, flat,           tpcBb   },  //Bb
        {B, natural,        tpcB    },  //B
        {B, sharp,          tpcBs   },  //B#
        {B, double_sharp,   tpcBss  },  //B##
    };
    
    //static member: obtains the Line of Fifths index for a note from multidimensional array fLineOf5ths
    //name and alteration must be set.
    enum IMUSANT_pitch::TPC IMUSANT_pitch::CalcTonalPitchClass(type name, sign alt)
    {
        TPC tpc = tpcUndefined;
       
        for (int i = 0; i <= 35; i+=5 ) {
            if (fLineOf5ths[i][0]==name) {  //find pitch name
                for (int j=0; j<5; j++) {
                    if (alt==fLineOf5ths[i+j][1]) { //find alteration
                        tpc = static_cast<TPC>(fLineOf5ths[i+j][2]); //store TPC
                        break;
                    }
                }
                break;
            }
        }
        
        return tpc;
    }
    
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
    
    
    void IMUSANT_pitch::set(type name, unsigned short octave, unsigned short voice, type ms_note, sign alteration,
                            bool inChord)
    {
        fName = name;
        fAlteration = alteration;
        fOctave = octave;
        fMSName = name; //ms_note;
        fInChord = inChord;
        fVoice = voice;
        fPC = CalcPitchClass();
        fMidiKeyNumber = CalcMidiKeyNumber();
        
    }
    
    void
    IMUSANT_pitch::
    setAlteration(const string alter)
    {
        // We are just assuming that the input string is a valid number.
        sign alteration = (sign)atoi(alter.c_str());
        if (alteration == 0 && alter.compare("0") != 0)
        {
            throw "IMUSANT_pitch::setAlteration() - Unexpected value for alter.  Expected a number of semitones received " + alter;
        }
        fAlteration = alteration;
        fPC = CalcPitchClass();
        fMidiKeyNumber = CalcMidiKeyNumber();
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
        //reset midi code only
        fMidiKeyNumber = CalcMidiKeyNumber();
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
        //set other pitch representations
    }
    
    void IMUSANT_pitch::print (ostream& os) const
    {
        os << IMUSANT_pitch::xml(fName) << fAlteration << "@" << fOctave /*<< std::endl*/;
    }
    
    //Calculates the Pitch Class number as per traditional pitch class theory, octave agnostic
    //requires fName and fAlteration
    int
    IMUSANT_pitch::
    CalcPitchClass()
    {
        int pc = -1; //undefined
        
        if (fName!=undefined)
        {
            (fName < 3) ? pc = fName*2 : pc = fName*2 - 1;
            pc += fAlteration;
            if (pc<0) pc+=12;
        }
        
        return pc;
    }
    
    //Calculates the Midi Key number for a given pitch.
    //Requires fName, fAlteration, and fOctave
    //C4 (middle C) is midi key number 60; is limited to C0
    int
    IMUSANT_pitch::
    CalcMidiKeyNumber()
    {
        int midinumber = -1;
        
        if (fName!=undefined && fPC!=-1) {
            midinumber = fPC + (fOctave+1)*12;
        }
        return midinumber;
    }
    
} //namespace IMUSANT