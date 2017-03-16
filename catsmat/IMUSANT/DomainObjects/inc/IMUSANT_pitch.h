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
    typedef IMUSANT_SMARTP<IMUSANT_pitch> S_IMUSANT_pitch;
    VEXP IMUSANT_SMARTP<IMUSANT_pitch> new_IMUSANT_pitch();
    
    VEXP ostream& operator<< (ostream& os, const IMUSANT_pitch& elt );
    /*!
     \brief An IMUSANT pitch representation.
     This class handles pitch representations
     Currently only takes account of semitones
     */
    
    class VEXP IMUSANT_pitch : public smartable
    {
        
    public:
        enum type {
            undefined=-1,
            C=0, D, E, F, G, A, B,
            last=B,
            diatonicSteps=7,
            big_undefined =0x4FFFFFFF};
        
        enum inflection {
            double_flat = -2,
            flat = -1,
            //quarterflat = -0.5, //needs to change series of consts in a struct/class influence to admit quartertones
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

        
        VEXP friend IMUSANT_SMARTP<IMUSANT_pitch> new_IMUSANT_pitch();
        
        IMUSANT_pitch() :
            fNameSounding(undefined),
            fNameAsWritten(undefined),
            fMSNameSounding(undefined),
            fMSNameAsWritten(undefined),
            fOctaveSounding(0),
            fOctaveAsWritten(0),
            fAlterationSounding(natural),
            fAlterationAsWritten(natural),
            fInChord(false),
            fVoice(1),
            fTransposeDiatonic(0),
            fTransposeChromatic(0),
            fTransposeOctaveChange(0),
            fTransposeDoubled(false)
        {
        }
        
        IMUSANT_pitch(const IMUSANT_pitch& copy);
        
        virtual ~IMUSANT_pitch () {}
        
        void set(type name_as_written, unsigned short octave_as_written, unsigned short voice,
                 type ms_note_as_written, inflection accidental_as_written=natural, bool is_chord=false);
        
        inline void set(type name_as_written, unsigned short octave_as_written, unsigned short voice,
                        inflection accidental_as_written=natural, bool is_chord=false)
        {
            set(name_as_written, octave_as_written, voice, name_as_written, accidental_as_written, is_chord);
        }

        //getters
        const type		name() const		{ return fNameSounding; }
        const inflection getInflection() const	{ return fAlterationSounding; }
        unsigned short 	octave() const		{ return fOctaveSounding; }
        const type		ms_name() const		{ return fMSNameSounding; }
        bool			in_chord() const	{ return fInChord; }
        unsigned short	voice() const       { return fVoice; }
        enum IMUSANT_pitch::TPC getTPC()            { return CalcTonalPitchClass(fNameSounding, fAlterationSounding); }
        int             getPC() const       { return CalcPitchClass(); }         //returns pitch class
        int             getMidiKeyNumber() const { return CalcMidiKeyNumber(); }   //returns midi key number
        
        //setters
        void			setName(const type name_as_written) { fNameAsWritten = name_as_written; transpose(); }
        void            setName(const string name_as_written) { fNameAsWritten = xml(name_as_written); transpose(); }
        void			setAlteration(const inflection alteration_as_written) { fAlterationAsWritten = alteration_as_written; transpose(); }
        void            setAlteration(const string alteration_as_written);   // A number of semitones with +ve being sharp and -ve being flat. No validation performed.
        void			setOctave( const unsigned short octave_as_written ) { fOctaveAsWritten = octave_as_written; transpose(); }
        void			setOctave( const string octave_as_written );
        void			setMSName( const type msName_as_written ) { fMSNameAsWritten = msName_as_written; transpose();}
        void			setInChord (const bool inChord) { fInChord = inChord; }
        void			setVoice( const unsigned short voice )
        {
            fVoice = voice;
        }
        
        // Transposition.
        // This class should always be initialised with the written pitch.
        //
        // If the transpose() method is called, all subsequent calls to the getters on this class will
        // return the sounding pitch (accounting for the transposition) rather than the written pitch.
        //
        // The asWritten() method returns a pitch with any transposition removed.  The getters will return the
        // written, rather than sounding pitch.
        void                transpose(int diatonic, int chromatic, int octave_change, bool doubled = false);
        S_IMUSANT_pitch    asWritten() const;
        
        IMUSANT_pitch& operator= (const IMUSANT_pitch& pitch);
        
        bool operator== (const IMUSANT_pitch& pitch) const;
        
        bool operator!= (const IMUSANT_pitch& pitch) const;
        
        //
        // "greater than" is interpreted to mean "of a higher pitch"
        //
        bool operator> (const IMUSANT_pitch& pitch) const;
        bool operator< (const IMUSANT_pitch& pitch) const;
        
        friend ostream& operator<< (ostream& os, const IMUSANT_pitch& elt );
        
        void	print (ostream& os) const;
        
        static const string	xml(type d);
        //! convert a string to a numeric pitch
        static type			xml(const string str);

        static IMUSANT_pitch MakeUniquePitch();
        
    private:
        
        //alternative pitch representation calculators
        enum TPC        CalcTonalPitchClass(type name, inflection alt);
        type            GetNameFromTPC(IMUSANT_pitch::TPC tpc);
        inflection      GetInflectionFromTPC(IMUSANT_pitch::TPC tpc);
        
        int             CalcPitchClass() const;
        int             CalcMidiKeyNumber() const;
        
        void transpose();
        int fTransposeDiatonic;
        int fTransposeChromatic;
        int fTransposeOctaveChange;
        bool fTransposeDoubled;
        
        type			fNameSounding;
        inflection      fAlterationSounding;
        unsigned short	fOctaveSounding;
        type			fMSNameSounding;
        
        type			fNameAsWritten;
        inflection      fAlterationAsWritten;
        unsigned short	fOctaveAsWritten;
        type			fMSNameAsWritten;
       
        bool			fInChord;
        unsigned short	fVoice;
        
        static bimap<string, type> fPitch2String;
        static type 	fPitchTbl[];
        static string 	fPitchStrings[];
        static int      fLineOf5ths[35][3];
        
    };
    

    
    class EnharmonicsTable
    {
    public:
        
        class note
        {
        public:
            
            note(IMUSANT_pitch::type            note_name,
                 IMUSANT_pitch::inflection      alteration,
                 int                            group)
            :
                note_name(note_name),
                alteration(alteration),
                octave(0),
                group(group)
            {};
            
            note()
            :
                note_name(IMUSANT_pitch::undefined),
                alteration(IMUSANT_pitch::natural),
                octave(0),
                group(-1)
            {};
            
            IMUSANT_pitch::type         note_name;
            IMUSANT_pitch::inflection   alteration;
            unsigned short              octave;
            int                         group;
        };
        
        note transpose(IMUSANT_pitch::type written_note_name, IMUSANT_pitch::inflection written_alteration, unsigned short written_octave, int diatonic_steps, int chromatic_steps);
        IMUSANT_pitch::type addPitchSteps(IMUSANT_pitch::type note_name, int num_pitch_steps);
        
        
    private:
        
        static const int NUM_PITCH_SPELLINGS = 35;
        static const int HIGHEST_ENHARMONIC_GROUP = 12;
        static const int LOWEST_ENHARMONIC_GROUP = 1;
        const note enharmonic_groups[NUM_PITCH_SPELLINGS] =
        {
            note(IMUSANT_pitch::C, IMUSANT_pitch::natural, LOWEST_ENHARMONIC_GROUP),
            note(IMUSANT_pitch::B, IMUSANT_pitch::sharp, LOWEST_ENHARMONIC_GROUP),
            note(IMUSANT_pitch::D, IMUSANT_pitch::double_flat, LOWEST_ENHARMONIC_GROUP),
            
            note(IMUSANT_pitch::C, IMUSANT_pitch::sharp, 2),
            note(IMUSANT_pitch::D, IMUSANT_pitch::flat, 2),
            note(IMUSANT_pitch::B, IMUSANT_pitch::double_flat, 2),
            
            note(IMUSANT_pitch::D, IMUSANT_pitch::natural, 3),
            note(IMUSANT_pitch::C, IMUSANT_pitch::double_sharp, 3),
            note(IMUSANT_pitch::E, IMUSANT_pitch::double_flat, 3),
            
            note(IMUSANT_pitch::D, IMUSANT_pitch::sharp, 4),
            note(IMUSANT_pitch::E, IMUSANT_pitch::flat, 4),
            note(IMUSANT_pitch::F, IMUSANT_pitch::double_flat, 4),
            
            note(IMUSANT_pitch::E, IMUSANT_pitch::natural, 5),
            note(IMUSANT_pitch::F, IMUSANT_pitch::flat, 5),
            note(IMUSANT_pitch::D, IMUSANT_pitch::double_sharp, 5),
            
            note(IMUSANT_pitch::F, IMUSANT_pitch::natural, 6),
            note(IMUSANT_pitch::E, IMUSANT_pitch::sharp, 6),
            note(IMUSANT_pitch::G, IMUSANT_pitch::double_flat, 6),
            
            note(IMUSANT_pitch::F, IMUSANT_pitch::sharp, 7),
            note(IMUSANT_pitch::G, IMUSANT_pitch::flat, 7),
            note(IMUSANT_pitch::E, IMUSANT_pitch::double_sharp, 7),
            
            note(IMUSANT_pitch::G, IMUSANT_pitch::natural, 8),
            note(IMUSANT_pitch::F, IMUSANT_pitch::double_sharp, 8),
            note(IMUSANT_pitch::A, IMUSANT_pitch::double_flat, 8),
            
            note(IMUSANT_pitch::G, IMUSANT_pitch::sharp, 9),
            note(IMUSANT_pitch::A, IMUSANT_pitch::flat, 9),
            
            note(IMUSANT_pitch::A, IMUSANT_pitch::natural, 10),
            note(IMUSANT_pitch::G, IMUSANT_pitch::double_sharp, 10),
            note(IMUSANT_pitch::B, IMUSANT_pitch::double_flat, 10),
            
            note(IMUSANT_pitch::A, IMUSANT_pitch::sharp, 11),
            note(IMUSANT_pitch::B, IMUSANT_pitch::flat, 11),
            note(IMUSANT_pitch::C, IMUSANT_pitch::double_flat, 11),
            
            note(IMUSANT_pitch::B, IMUSANT_pitch::natural, 12),
            note(IMUSANT_pitch::C, IMUSANT_pitch::flat, 12),
            note(IMUSANT_pitch::A, IMUSANT_pitch::double_sharp, 12)
        };

        IMUSANT_pitch::inflection addChromaticSteps(IMUSANT_pitch::type written_note_name,
                                                    IMUSANT_pitch::inflection written_alteration,
                                                    IMUSANT_pitch::type sounding_note_name,
                                                    int chromatic_steps);
        
        
        
        int addChromaticStepsToGroup(int group, int chromatic_steps);
        
        int calcImplicitOctaveChange(int chromatic_steps, IMUSANT_pitch::type written_note_name, IMUSANT_pitch::type sounding_note_name);
        
        int findGroup(IMUSANT_pitch::type note_name, IMUSANT_pitch::inflection alteration);
        
        note findNote(int group, IMUSANT_pitch::type note_name);
        
    };
    
} //namespace IMUSANT

#endif //__IMUSANT_PITCH__
