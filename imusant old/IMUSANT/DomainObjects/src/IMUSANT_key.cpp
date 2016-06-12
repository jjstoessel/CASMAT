/*
 *  IMUSANT_key.cpp
 *  imusant
 *
 *  Created by Jason Stoessel on 30/08/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "IMUSANT_key.h"

namespace IMUSANT
{   
    IMUSANT_key::mode
    IMUSANT_key::
    fModeTbl[] = { generic, dorian, hypodorian, phrygian, hypophrygian, lydian, hypolydian,
                   mixolydian, hypomixolydian, aeolian, locrian, ionian, major, minor };
    
    string
    IMUSANT_key::
    fModeStrings[] = { "generic", "dorian", "hypodorian", "phrygian", "hypophrygian", "lydian", "hypolydian",
                       "mixolydian", "hypomixolydian", "aeolian", "locrian", "ionian", "major", "minor" };
       
    const string
    IMUSANT_key::
    xmlmode (mode m)
    {
        bool found = false;
        int index = 0;
        while (index < fModeTbl_Length && !found)
        {
            if (fModeTbl[index] == m)
            {
                found = true;
            }
            index++;
        }
        
        if (found)
        {
            return fModeStrings[index-1];
        }
        else
        {
            throw "Input value not matched in IMUSANT_key::xmlmode";
        }
    }
    
    IMUSANT_key::mode
    IMUSANT_key::
    xmlmode (const string str)
    {
        bool found = false;
        int index = 0;
        while (index < fModeTbl_Length && !found)
        {
            if (str.compare(fModeStrings[index]) == 0)
            {
                found = true;
            }
            index++;
        }
        
        if (found)
        {
            return fModeTbl[index-1];
        }
        else
        {
            throw "Input value not matched in IMUSANT_key::xmlmode - received " + str;
        }
    }
    
    //0 to fFifth-1 gives containing accidentals
    pair<IMUSANT_pitch::type,signed short>
    IMUSANT_key::
    fFlatFifthsTbl[] =
    {
        make_pair(IMUSANT_pitch::B,-1), make_pair(IMUSANT_pitch::E,-1), make_pair(IMUSANT_pitch::A,-1), make_pair(IMUSANT_pitch::D,-1),
        make_pair(IMUSANT_pitch::G,-1), make_pair(IMUSANT_pitch::C,-1), make_pair(IMUSANT_pitch::F,-1), make_pair(IMUSANT_pitch::B,-2),
        make_pair(IMUSANT_pitch::E,-2), make_pair(IMUSANT_pitch::A,-2)
    };
    
    pair<IMUSANT_pitch::type,signed short>
    IMUSANT_key::
    fSharpFifthsTbl[] =
    {
        make_pair(IMUSANT_pitch::F,1), make_pair(IMUSANT_pitch::C,1), make_pair(IMUSANT_pitch::G,1), make_pair(IMUSANT_pitch::D,1),
        make_pair(IMUSANT_pitch::A,1), make_pair(IMUSANT_pitch::E,1), make_pair(IMUSANT_pitch::B,1), make_pair(IMUSANT_pitch::F,2),
        make_pair(IMUSANT_pitch::C,2), make_pair(IMUSANT_pitch::G,2)
    };
    
    ostream& operator<< (ostream& os, const IMUSANT_key& elt )
    {
        elt.print(os); return os;
    }
    
    bool
    IMUSANT_key::
    PitchAlterInSignature(IMUSANT_pitch::type name, signed short alter)
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
    
    void
    IMUSANT_key::
    operator=(const IMUSANT_key& key)
    {
        fFifths = key.getFifths();
        fMode = key.getMode();
        fCancel = key.getCancel();
    }
    
    bool
    IMUSANT_key::
    operator==(const IMUSANT_key& key) const
    {
        return ((fFifths == key.getFifths()) && (fMode == key.getMode()) && (fCancel == key.getCancel()));
    }
    
    bool
    IMUSANT_key::
    operator!=(const IMUSANT_key& key) const
    {
        return ((fFifths != key.getFifths()) || (fMode != key.getMode()) || (fCancel != key.getCancel()));
    }
    
    
    
} //namespace IMUSANT