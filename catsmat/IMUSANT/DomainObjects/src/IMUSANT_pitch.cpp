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
#include "IMUSANT_transposer.h"

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
    const int NUM_FIFTHS = 35;
    const int FIFTHS_NOTE_TYPE_FIELD = 0;
    const int FIFTHS_NOTE_INFLECTION_FIELD = 1;
    const int FIFTHS_NOTE_TPC_FIELD = 2;
    
    int      IMUSANT_pitch::fLineOf5ths[NUM_FIFTHS][3] =
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
    enum IMUSANT_pitch::TPC
    IMUSANT_pitch::
    CalcTonalPitchClass(type name, inflection alt)
    {
        TPC tpc = tpcUndefined;
       
        for (int i = 0; i <= NUM_FIFTHS; i+=5 ) {
            if (fLineOf5ths[i][0]==name) {  //find pitch name
                for (int j=0; j<5; j++) {
                    if (alt==fLineOf5ths[i+j][1]) { //find alteration
                        tpc = static_cast<TPC>(fLineOf5ths[i+j][FIFTHS_NOTE_TPC_FIELD]); //store TPC
                        break;
                    }
                }
                break;
            }
        }
        
        return tpc;
    }
    
    
    IMUSANT_pitch::type
    IMUSANT_pitch::
    GetNameFromTPC(IMUSANT_pitch::TPC tpc)
    {
        IMUSANT_pitch::type ret_val = undefined;
        
        for (int index = 0 ; index <= NUM_FIFTHS; index++)
        {
            if (fLineOf5ths[index][FIFTHS_NOTE_TPC_FIELD] == tpc)
            {
                ret_val = static_cast<IMUSANT_pitch::type>(fLineOf5ths[index][FIFTHS_NOTE_TYPE_FIELD]);
                break;
            }
        }
        
        return ret_val;
    }
    
    IMUSANT_pitch::inflection
    IMUSANT_pitch::
    GetInflectionFromTPC(IMUSANT_pitch::TPC tpc)
    {
        IMUSANT_pitch::inflection ret_val = natural;
        
        for (int index = 0 ; index <= NUM_FIFTHS; index++)
        {
            if (fLineOf5ths[index][FIFTHS_NOTE_TPC_FIELD] == tpc)
            {
                ret_val = static_cast<IMUSANT_pitch::inflection>(fLineOf5ths[index][FIFTHS_NOTE_INFLECTION_FIELD]);
                break;
            }
        }
        
        return ret_val;
        
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
        
        out.fOctaveAsWritten = unique;
        out.fOctaveSounding = unique;
        unique--;
        
        if (big_undefined-unique>FLAGSPACE)
            cerr << "Unique flag limit reached" << endl;
        
        return out;
    }
    
    //copy ctor
    IMUSANT_pitch::IMUSANT_pitch(const IMUSANT_pitch& copy)
    {
        this->fTransposeChromatic = copy.fTransposeChromatic;
        this->fTransposeDiatonic = copy.fTransposeDiatonic;
        this->fTransposeDoubled = copy.fTransposeDoubled;
        this->fTransposeOctaveChange = copy.fTransposeOctaveChange;
        
        this->set(copy.fNameAsWritten, copy.fOctaveAsWritten, copy.fVoice, copy.fMSNameAsWritten, copy.fAlterationAsWritten, copy.fInChord);
    }
    
    
    void IMUSANT_pitch::set(type name_as_written,
                            unsigned short octave_as_written,
                            unsigned short voice,
                            type ms_note_as_written,
                            inflection alteration_as_written,
                            bool inChord)
    {
        fNameAsWritten = name_as_written;
        fAlterationAsWritten = alteration_as_written;
        fOctaveAsWritten = octave_as_written;
        fMSNameAsWritten = ms_note_as_written;
        fInChord = inChord;
        fVoice = voice;
        
        transpose();
    }
    
    void
    IMUSANT_pitch::
    setAlteration(const string alteration_as_written)
    {
        // We are just assuming that the input string is a valid number.
        inflection alteration = (inflection)atoi(alteration_as_written.c_str());
        if (alteration == 0 && alteration_as_written.compare("0") != 0)
        {
            throw "IMUSANT_pitch::setAlteration() - Unexpected value for alter.  Expected a number of semitones received " + alteration_as_written;
        }
        fAlterationAsWritten = alteration;
        transpose();
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
        fOctaveAsWritten = oct;
        transpose();
    }
    
    
    IMUSANT_pitch&
    IMUSANT_pitch::
    operator= (const IMUSANT_pitch& pitch)
    {
        S_IMUSANT_pitch input_as_written = pitch.asWritten();
        
        set(input_as_written->name(), input_as_written->octave(), input_as_written->voice(), input_as_written->ms_name(), input_as_written->getInflection(), input_as_written->in_chord());
        
        transpose(pitch.fTransposeDiatonic, pitch.fTransposeChromatic, pitch.fTransposeOctaveChange, pitch.fTransposeDoubled);
        
        return *this;
    }
    
    bool
    IMUSANT_pitch::operator> (const IMUSANT_pitch& pitch) const
    {
        bool gt = false;
        
        if (octave() > pitch.octave())   // this note is higher because it is in a higher octave.
        {
            gt = true;
        }
       
        if (octave() == pitch.octave())
        {
            if (name() > pitch.name())   // this note is in the same octave, but is a higher note
            {
                gt = true;
            }
        }
        
        if (octave() == pitch.octave()
            &&
            name() == pitch.name())
        {
            if (getInflection() > pitch.getInflection() )  // this note is the same note name and octave, but is sharper.
            {
                gt = true;
            }
        }
        
        return gt;
    }
    
    bool
    IMUSANT_pitch::operator< (const IMUSANT_pitch& pitch) const
    {
        return pitch>*this;
    }

    bool
    IMUSANT_pitch::operator== (const IMUSANT_pitch& pitch) const
    {
        return
            name() == pitch.name() &&
            getInflection() == pitch.getInflection() &&
            octave() == pitch.octave();
    }
    
    void IMUSANT_pitch::print (ostream& os) const
    {
        os << IMUSANT_pitch::xml(fNameSounding) << fAlterationSounding << "@" << fOctaveSounding /*<< std::endl*/;
    }
    
    //Calculates the Pitch Class number as per traditional pitch class theory, octave agnostic
    //requires fName and fAlteration
    int
    IMUSANT_pitch::
    CalcPitchClass() const
    {
        int pc = -1; //undefined
        type name = fNameSounding;
        
        if (name!=undefined)
        {
            (name < 3) ? pc = name*2 : pc = name*2 - 1;
            pc += fAlterationSounding;
            if (pc<0) pc+=12;
        }
        
        return pc;
    }
    
    //Calculates the Midi Key number for a given pitch.
    //Requires fName, fAlteration, and fOctave
    //C4 (middle C) is midi key number 60; is limited to C0
    int
    IMUSANT_pitch::
    CalcMidiKeyNumber() const
    {
        int midinumber = -1;
        int pc = CalcPitchClass();
        type name = fNameSounding;
        
        if (name!=undefined && pc!=-1) {
            midinumber = pc + (fOctaveSounding+1)*12;
        }
        return midinumber;
    }
    
   
#define ENHARMONIC_TRANSPOSE_IMPLEMENTATION
    
    void
    IMUSANT_pitch::
    transpose(int diatonic, int chromatic, int octave_change, bool doubled)
    {
        fTransposeDiatonic = diatonic;
        fTransposeChromatic = chromatic;
        fTransposeOctaveChange = octave_change;
        fTransposeDoubled = doubled;
        
#ifdef TPC_TRANSPOSE_IMPLEMENTATION
        
        S_IMUSANT_transposer transposer = new_IMUSANT_transposer();
        IMUSANT_pitch::TPC transposed_note_TPC = transposer->transpose(getTPC(), diatonic, chromatic, octave_change);
        
        // REVISIT - We need to factor in the diatonic value.  The algorithm in transposer->transpose() uses the
        // chromatic value to find an interval, but does not account for diatonic values. (e.g C to D# would
        // be treated as a minor third instead of as an augmented second.
        
        fNameSounding = GetNameFromTPC(transposed_note_TPC);
        fAlterationSounding = GetInflectionFromTPC(transposed_note_TPC);
        
        fOctaveSounding = fOctaveAsWritten;
        
        EnharmonicsTable etbl;
        if (chromatic > 0)   // Going up;
        {
            type counter = fNameAsWritten;
            while (counter != fNameSounding)
            {
                counter = etbl.addPitchSteps(counter, 1);
                if (counter == C)
                {
                    fOctaveSounding++;
                }
            }
        }
        else if (chromatic < 0)   // Going down;
        {
            type counter = fNameAsWritten;
            while (counter != fNameSounding)
            {
                counter = etbl.addPitchSteps(counter, -1);
                if (counter == B)
                {
                    fOctaveSounding--;
                }
            }
        }
        
#endif
        
#ifdef ENHARMONIC_TRANSPOSE_IMPLEMENTATION
        
        EnharmonicsTable transposer;
        EnharmonicsTable::note transposed_note = transposer.transpose(fNameAsWritten, fAlterationAsWritten, fOctaveAsWritten, diatonic, chromatic);
        
        fNameSounding = transposed_note.note_name;
        fAlterationSounding = transposed_note.alteration;
        fOctaveSounding = transposed_note.octave;
#endif
        
        // Handle any explicit octave change.
        fOctaveSounding += octave_change;
        
        fMSNameSounding = fMSNameAsWritten;  // REVISIT
    }

    
    void
    IMUSANT_pitch::
    transpose()
    {
        if (fTransposeChromatic == 0
            &&
            fTransposeDiatonic == 0
            &&
            fTransposeOctaveChange == 0)
        {
            fOctaveSounding = fOctaveAsWritten;
            fNameSounding = fNameAsWritten;
            fAlterationSounding = fAlterationAsWritten;
        }
        else
        {
            transpose(fTransposeDiatonic, fTransposeChromatic, fTransposeOctaveChange, fTransposeDoubled);
        }
    }
    
    S_IMUSANT_pitch
    IMUSANT_pitch::
    asWritten() const
    {
        S_IMUSANT_pitch ret_val = new_IMUSANT_pitch();
        ret_val->set(fNameAsWritten, fOctaveAsWritten, fVoice, ms_name(), fAlterationAsWritten, in_chord());
        return ret_val;
    }
    
    // --------------------  ENHARMONICS TABLE ------------------------
    
    EnharmonicsTable::note
    EnharmonicsTable::
    transpose(IMUSANT_pitch::type written_note_name, IMUSANT_pitch::inflection written_alteration, unsigned short written_octave, int diatonic_steps, int chromatic_steps)
    {
        note transposed_note;
        
        transposed_note.note_name = addPitchSteps(written_note_name, diatonic_steps);
        transposed_note.alteration = addChromaticSteps(written_note_name, written_alteration, transposed_note.note_name, chromatic_steps);
        
        transposed_note.octave = written_octave;
        transposed_note.octave += calcImplicitOctaveChange(chromatic_steps, written_note_name, transposed_note.note_name);
        
        return transposed_note;
    }
    
    int
    EnharmonicsTable::
    calcImplicitOctaveChange(int chromatic_steps, IMUSANT_pitch::type written_note_name, IMUSANT_pitch::type sounding_note_name)
    {
        IMUSANT_pitch::type next_note_in_scale = written_note_name;
        
        int number_of_octaves = 0;
        
        if (chromatic_steps > 0)   // Going up;
        {
            while (next_note_in_scale != sounding_note_name)
            {
                next_note_in_scale = addPitchSteps(next_note_in_scale, 1);
                if (next_note_in_scale == IMUSANT_pitch::C)
                {
                    number_of_octaves++;
                }
            }
        }
        else if (chromatic_steps < 0)   // Going down;
        {
            while (next_note_in_scale != sounding_note_name)
            {
                next_note_in_scale = addPitchSteps(next_note_in_scale, -1);
                if (next_note_in_scale == IMUSANT_pitch::B)
                {
                    number_of_octaves--;
                }
            }
        }
        
        return number_of_octaves;
    }
    
    
    
    IMUSANT_pitch::inflection
    EnharmonicsTable::
    addChromaticSteps(IMUSANT_pitch::type written_note_name, IMUSANT_pitch::inflection written_alteration, IMUSANT_pitch::type sounding_note_name, int chromatic_steps)
    {
        int group = findGroup(written_note_name, written_alteration);
        
        int transpose_group = addChromaticStepsToGroup(group, chromatic_steps);
        
        note found_note = findNote(transpose_group, sounding_note_name);
        return found_note.alteration;
    }
    
    //
    // This method handles wrapping the index around the EnharmionicsTable.
    // For example, if group is 1 and the chromatic steps
    // is -2 then we need to move backwards int the table
    // until we reach the lowest group, and then wrap back
    // to the highest group.
    //
    int
    EnharmonicsTable::
    addChromaticStepsToGroup(int group, int chromatic_steps)
    {
        int new_group = group;

        while (chromatic_steps > 0)
        {
            int next_group = new_group + 1;
            
            if (next_group > HIGHEST_ENHARMONIC_GROUP)
            {
                next_group = LOWEST_ENHARMONIC_GROUP;
            }
            
            new_group = next_group;
            chromatic_steps--;
        }
        
        while (chromatic_steps < 0)
        {
            int next_group = new_group - 1;
            
            if (next_group < LOWEST_ENHARMONIC_GROUP)
            {
                next_group = HIGHEST_ENHARMONIC_GROUP;
            }
            
            new_group = next_group;
            chromatic_steps++;
        }
        
        return new_group;
    }
    
    int
    EnharmonicsTable::
    findGroup(IMUSANT_pitch::type note_name, IMUSANT_pitch::inflection alteration)
    {
        for (int index=0 ; index < NUM_PITCH_SPELLINGS; index++)
        {
            if (enharmonic_groups[index].note_name == note_name && enharmonic_groups[index].alteration == alteration)
            {
                return enharmonic_groups[index].group;
            }
        }
        return -1;
    }
    
    
    EnharmonicsTable::note
    EnharmonicsTable::
    findNote(int group, IMUSANT_pitch::type note_name)
    {
        for (int index=0 ; index < NUM_PITCH_SPELLINGS; index++)
        {
            if (enharmonic_groups[index].note_name == note_name && enharmonic_groups[index].group == group)
            {
                return enharmonic_groups[index];
            }
        }
        return note(IMUSANT_pitch::undefined, IMUSANT_pitch::natural, -1);
        
    }
    
    IMUSANT_pitch::type
    EnharmonicsTable::
    addPitchSteps(IMUSANT_pitch::type note_name, int num_pitch_steps)
    {
        const int i = static_cast<int>(note_name);
        
        while (num_pitch_steps < 0)
        {
            num_pitch_steps += IMUSANT_pitch::diatonicSteps;
        }
        
        int calculated_note_value = (i + num_pitch_steps) % IMUSANT_pitch::diatonicSteps;
        note_name = static_cast<IMUSANT_pitch::type>(calculated_note_value);
        
        return note_name;
    }
    
    
} //namespace IMUSANT