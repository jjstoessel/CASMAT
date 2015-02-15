/*
  Copyright © Grame 2003

  This library is free software; you can redistribute it and modify it under
  the terms of the GNU Library General Public License as published by the
  Free Software Foundation version 2 of the License, or any later version.

  This library is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public License
  for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

  Grame Research Laboratory, 9, rue du Garet 69001 Lyon - France
  grame@rd.grame.fr
  
*/

#ifndef __IMusicXMLReader__
#define __IMusicXMLReader__

#include "exports.h"

#include <iosfwd>
#include <map>
#include <string>

#include "TAttributes.h"
#include "TBackupForward.h"
#include "TBarline.h"
#include "TChord.h"
#include "TDirection.h"
#include "TIdentification.h"
#include "TNotation.h"
#include "TNote.h"
#include "TPitch.h"
#include "TScorePartwise.h"
#include "TScoreTimewise.h"
#include "TSound.h"
#include "TArpeggiate.h"
#include "TOtherDirections.h"
#include "TTechnical.h"
#include "TOrnaments.h"
#include "TFiguredBass.h"
#include "THarmony.h"
#include "TStaffDetails.h"

#include "conversions.h"

#include "Iexpat.h"


namespace MusicXML 
{

class TMusicXMLReader;

typedef void (*StartMethod) (TMusicXMLReader* reader, const char **attr, const char* tag);
typedef void (*EndMethod) (TMusicXMLReader* reader, const char* tag);

/* 
    Parser context :

    Whenever possible, objects being parsed are created and directly added to the MusicXML structure.
    Some fields (like fAttributes, fSound...) are used to keep objects beeing parsed that can not 
    be directly added to the MusicXML structure. When objects can appear at different places in 
    the MusicMXL tree, the place where they are going to be added depends of the parser context. 
    This will be handled in the correspondind EndXXX method.
    
    For example "midi-instrument" can appear in a "score-part" or in a "sound". The parser 
    is in "parse score-part" context when the fScorePart field is used, in this case the parsed 
    "midi-instrument" object (fMidiInstrument field) will be added the the "score-part" (fScorePart field)
    otherwise  the parsed "midi-instrument" object (fMidiInstrument field) will be added the the "sound" 
    (fSound field). The element just being parsed and used is always reset to NULL, so that the parser context 
    can be checked.
    
    Specific cases :
            
    "identification" can appear in a "score-part" or in a "score-header", managed in EndIdentification
    "midi-instrument" can appear in a "score-part" or in a "sound", managed in EndMidiInstrument
    "duration" can appear in "forward", in "backup" or in "note", managed in EndDuration
    "voice" can appear in "forward", in "note", in "editorial" or in "direction", managed in EndVoice
    "staff" can appear in "forward", in "note" or in "direction", managed in EndStaff
    "sound" can appear in "direction" or as an autonomous element
    "fermata" can appear in "notations"  of in "barline", managed in EndFermata
    "coda" can appear in "barline" or in "direction-type", managed in EndCoda
    "segno" can appear in "barline" or in "direction-type", managed in EndSegno
    "dynamic" can appear in "direction-type" or in "norartion", managed in EndDynamic
    addMusicData will add a TMusicDate in the measure (score-partwise) or in the part (score-timewise)
	"syllabic" and "text" can appear in lyric or in multi-lyric-part (elision)
	"wavy-line" can appear in "barline" or an "ornament", managed in StartWavyLine
	"accidental-mark" can appear in "notation" orf an "ornament", managed in EndAccidentalMark
	"string" an appear in "technical" or in "frame-note", managed in EndString
	"fret" an appear in "technical" or in "frame-note", managed in EndFret
    
    To finish :
    
    midi-device
    beat-type : traiter les cas complexes du genre 3+2/8
    sound fine : gestion de la valeur "yes"
    object graphics de baseNote toujours crée 
    
*/

/*!
\internal
\brief The MusicXML reader.
*/

class EXP TMusicXMLReader {

     private:
     
        // Parsing context
        SScorePartwise 		fPWScore;
        SScoreTimewise 		fTWScore;
        SScoreHeader		fScoreHeader;
        SScorePart 			fScorePart;
        SIdentification 	fIdentification; // it appears in TScorePart or TScoreHeader
        SCreator			fCreator;
        SRights				fRights;
        SScoreInstrument	fScoreInstrument;
        SMidiInstrument		fMidiInstrument; // it appears in TScorePart or TSound
        SPartGroup			fPartGroup;
        SPWPart				fPWPart;
        STWPart				fTWPart;
        SPWMeasure			fPWMeasure;
        STWMeasure			fTWMeasure;
        SAttributes			fAttributes;
        SSound				fSound;
        std::string			fBeat; // the parsed beat value for a timeSign
        SClef				fClef;
        SBackup				fBackup;
        SForward			fForward;
        SDirection 			fDirection;
        SDirectionType 		fDirectionType;
        SDirectionTypeElement fDirectionTypeElement;
        SChord				fChord;
        SNote				fNote;
        SBeam				fBeam;
        SNotation			fNotation;
        STieSlur			fTieSlur;
        STuplet				fTuplet;
        SArticulations		fArticulations;
        SArticulationElement fArticulationsElement;
        SBarline			fBarline;
        SFermata			fFermata; // used in notation or in barline
        SDynamic 			fDynamic;
        long				fLastNoteIndex;
        bool				fInChord;
		SLyric				fLyric;
		SMultipleLyricPart  fMultipleLyricPart;
		SOtherArticulation	fOtherArticulation;
		SRehearsal			fRehearsal;
		SOtherDirections	fOtherDirections;
		SOtherDirection		fOtherDirection;
		STechnicals			fTechnicals;
		STechnical			fTechnical;
		SHarmonic			fHarmonic;
		SHammerPull			fHammerPull;
		SBend				fBend;
		SBendWithBar		fBendWithBar;
		SOrnaments			fOrnaments;
		SOrnament			fOrnament;
		SAccidentalMark		fAccidentalmark;
		SFiguredBass		fFiguredBass;
		SFigure				fFigure;
		SHarmony			fHarmony;
		SHarmonyChord		fHarmonyChord;
		SRootFunction		fRootFunction;
		SDegree				fDegree;
		SFrameNote			fFrameNote;
		SFingering			fFingering;
		SStaffTuning		fStaffTuning;
		SMeasureStyleElement fMeasureStyleElement;
		TEditorial*			fEditorial;
	    
        std::string fDataString;
  
        //! The XML parser object.
        XML_Parser fParser; 
        //! An association table with tags and parser objects.
        std::map<std::string, StartMethod> fParserTable1;
        std::map<std::string, EndMethod> fParserTable2;
        
        SNote fPitchTable [128]; // handling of "tie" notes
        
        void AddParser(std::string tag, StartMethod start, EndMethod end);
		void ReplaceParser(string tag, StartMethod start, EndMethod end);
        void AddParser(std::string tag, StartMethod start);
        void AddParser(std::string tag, EndMethod end);
		void ReplaceParser(std::string tag, EndMethod end);
     
        static void CharacterDataHandler(void * userData, const XML_Char *s, int len);
        static void StartElementHandler(void * userData, const char *el, const char **attr); 
        static void EndElementHandler(void * userData, const char *el);
            
        std::string GetDataString() {return fDataString;}
        long GetDataLong() {return atoi(fDataString.c_str());}
        float GetDataFloat() {return (float)atof(fDataString.c_str());} // to be checked
        
        //static bool EqualStr(const char* s1, char* s2) { return strcmp(s1, s2) == 0; }
        static  bool  EqualStr(std::string s1, std::string s2) { return s1.compare(s2) == 0; }
    
        // score-partwise
        static void StartScorePartwise(TMusicXMLReader* reader, const char **attr, const char* tag);
        static void EndScorePartwise(TMusicXMLReader* reader, const char* tag); 
        // score-timewise
        static void StartScoreTimewise(TMusicXMLReader* reader, const char **attr, const char* tag);
        static void EndScoreTimewise(TMusicXMLReader* reader, const char* tag); 
        // part-list
        static void StartPartList(TMusicXMLReader* reader, const char **attr, const char* tag);
        // movement-title
        static void EndMovementTitle(TMusicXMLReader* reader, const char* tag); 
        // movement-number
        static void EndMovementNumber(TMusicXMLReader* reader, const char* tag); 
        // work
        static void StartWork(TMusicXMLReader* reader, const char **attr, const char* tag);
        // work-title
        static void EndWorkTitle(TMusicXMLReader* reader,const char* tag);
        // work-number
        static void EndWorkNumber(TMusicXMLReader* reader, const char* tag);
        // identification
        static void StartIdentification(TMusicXMLReader* reader, const char **attr, const char* tag);
        static void EndIdentification(TMusicXMLReader* reader, const char* tag);
        // creator
        static void StartCreator(TMusicXMLReader* reader, const char **attr, const char* tag);
        static void EndCreator(TMusicXMLReader* reader, const char* tag);
        // rights
        static void StartRights(TMusicXMLReader* reader, const char **attr, const char* tag);
        static void EndRights(TMusicXMLReader* reader, const char* tag);
        // encoding
        static void StartEncoding(TMusicXMLReader* reader, const char **attr, const char* tag);
        // software
        static void EndSoftware(TMusicXMLReader* reader, const char* tag);
        // encoding-date
        static void EndEncodingDate(TMusicXMLReader* reader, const char* tag);
        // encoder
        static void StartEncoder(TMusicXMLReader* reader, const char **attr, const char* tag);
        static void EndEncoder(TMusicXMLReader* reader, const char* tag);
        // encoding-description
        static void EndDescription(TMusicXMLReader* reader, const char* tag);
        // source
        static void EndSource(TMusicXMLReader* reader, const char* tag);
        // score-part
        static void StartScorePart(TMusicXMLReader* reader, const char **attr, const char* tag);
        static void EndScorePart(TMusicXMLReader* reader, const char* tag);
        // part-name
        static void EndPartName(TMusicXMLReader* reader, const char* tag);
        // part-abbreviation
        static void EndPartAbbreviation(TMusicXMLReader* reader, const char* tag);
        // midi-device // A FINIR
        static void StartMidiDevice(TMusicXMLReader* reader, const char **attr, const char* tag);
        // score-instrument
        static void StartScoreInstrument(TMusicXMLReader* reader, const char **attr, const char* tag);
        static void EndScoreInstrument(TMusicXMLReader* reader, const char* tag);
        // instrument-name
        static void EndInstrumentName(TMusicXMLReader* reader, const char* tag);
        // instrument-abbreviation
        static void EndInstrumentAbbrev(TMusicXMLReader* reader, const char* tag);
        // midi-instrument
        static void StartMidiInstrument(TMusicXMLReader* reader, const char **attr, const char* tag);
        static void EndMidiInstrument(TMusicXMLReader* reader, const char* tag);
        // midi-channel
        static void EndMidiChannel(TMusicXMLReader* reader, const char* tag);
        // midi-name
        static void EndMidiName(TMusicXMLReader* reader, const char* tag);
        // midi-bank
        static void EndMidiBank(TMusicXMLReader* reader, const char* tag);
        // midi-program
        static void EndMidiProgram(TMusicXMLReader* reader, const char* tag);
        // midi-unpitched
        static void EndMidiUnpitched(TMusicXMLReader* reader, const char* tag);
        // part-group
        static void StartPartGroup(TMusicXMLReader* reader, const char **attr, const char* tag);
        static void EndScorePartGroup(TMusicXMLReader* reader, const char* tag);
        // group-name
        static void EndGroupName(TMusicXMLReader* reader, const char* tag);
        // group-abbreviation
        static void EndGroupAbbrev(TMusicXMLReader* reader, const char* tag);
        // group-symbol
        static void EndGroupSymbol(TMusicXMLReader* reader, const char* tag);
        // part
        static void StartPart(TMusicXMLReader* reader, const char **attr, const char* tag);
        static void EndPart(TMusicXMLReader* reader, const char* tag);
        // measure
        static void StartMeasure(TMusicXMLReader* reader, const char **attr, const char* tag);
        static void EndMeasure(TMusicXMLReader* reader, const char* tag);
        // management of music data
        static long addMusicData(TMusicXMLReader* reader, SMusicData data); 
        static SMusicData& getMusicData(TMusicXMLReader* reader, long index);
        static void setMusicData(TMusicXMLReader* reader, SMusicData data, long index);
        // attributes
        static void StartAttributes(TMusicXMLReader* reader, const char **attr, const char* tag);
        static void EndAttributes(TMusicXMLReader* reader, const char* tag);
        // divisions
        static void EndDivisions(TMusicXMLReader* reader, const char* tag);
        // staves
        static void EndStaves(TMusicXMLReader* reader, const char* tag);
        // instruments
        static void EndInstruments(TMusicXMLReader* reader, const char* tag);
        // key
        static void StartKey(TMusicXMLReader* reader, const char **attr, const char* tag);
        // cancel
        static void EndCancel(TMusicXMLReader* reader, const char* tag);
        // fifths
        static void EndFifths(TMusicXMLReader* reader, const char* tag);
        // mode
        static void EndMode(TMusicXMLReader* reader, const char* tag);
        // time
        static void StartTime(TMusicXMLReader* reader, const char **attr, const char* tag);
        // beats
        static void EndBeats(TMusicXMLReader* reader, const char* tag);
        // beat-type // A FINIR traiter les cas complexes du genre 3+2/8
        static void EndBeatType(TMusicXMLReader* reader, const char* tag);
        // transpose
        static void StartTranspose(TMusicXMLReader* reader, const char **attr, const char* tag);
        // diatonic
        static void EndDiatonic(TMusicXMLReader* reader, const char* tag);
        // chromatic
        static void EndChromatic(TMusicXMLReader* reader, const char* tag);
        // octave-change
        static void EndOctaveChange(TMusicXMLReader* reader, const char* tag);
        // double
        static void EndDouble(TMusicXMLReader* reader, const char* tag);
        // directive
        static void StartDirective(TMusicXMLReader* reader, const char **attr, const char* tag);
        static void EndDirective(TMusicXMLReader* reader, const char* tag);
        // clef
        static void StartClef(TMusicXMLReader* reader, const char **attr, const char* tag);
        static void EndClef(TMusicXMLReader* reader, const char* tag);
        // sign
        static void EndSign(TMusicXMLReader* reader, const char* tag);
        // line
        static void EndLine(TMusicXMLReader* reader, const char* tag);
        // clef-octave-change
        static void EndClefOctaveChange(TMusicXMLReader* reader, const char* tag);
        // backup
        static void StartBackup(TMusicXMLReader* reader, const char **attr, const char* tag);
        static void EndBackup(TMusicXMLReader* reader, const char* tag);
        // forward
        static void StartForward(TMusicXMLReader* reader, const char **attr, const char* tag);
        static void EndForward(TMusicXMLReader* reader, const char* tag);
        // duration
        static void EndDuration(TMusicXMLReader* reader, const char* tag);
        // voice
        static void EndVoice(TMusicXMLReader* reader, const char* tag);
        // staff
        static void EndStaff(TMusicXMLReader* reader, const char* tag);
        // barline
        static void StartBarline(TMusicXMLReader* reader, const char **attr, const char* tag);
        static void EndBarline(TMusicXMLReader* reader, const char* tag);
        // bar-style
        static void EndBarStyle(TMusicXMLReader* reader, const char* tag);
         // wavy-line // A FINIR POSITIONABLE
        static void StartWavyLine(TMusicXMLReader* reader, const char **attr, const char* tag);
        // segno 
        static void StartSegno(TMusicXMLReader* reader, const char **attr, const char* tag);
        static void EndSegno(TMusicXMLReader* reader, const char* tag);
        // coda 
        static void StartCoda(TMusicXMLReader* reader, const char **attr, const char* tag);
        static void EndCoda(TMusicXMLReader* reader, const char* tag);
        // fermata 
        static void StartFermata(TMusicXMLReader* reader, const char **attr,const char* tag);
        static void EndFermata(TMusicXMLReader* reader, const char* tag);
        // ending
        static void StartEnding(TMusicXMLReader* reader, const char **attr, const char* tag);
        // repeat
        static void StartRepeat(TMusicXMLReader* reader, const char **attr, const char* tag);
        // sound
        static void StartSound(TMusicXMLReader* reader, const char **attr, const char* tag);
        static void EndSound(TMusicXMLReader* reader, const char* tag);
        // note
        static void StartNote(TMusicXMLReader* reader, const char **attr, const char* tag);
        // cue
        static void EndCueNote(TMusicXMLReader* reader, const char* tag);
        // grace
        static void StartGraceNote(TMusicXMLReader* reader, const char **attr, const char* tag);
        static void EndNote(TMusicXMLReader* reader, const char* tag);
        // instrument
        static void StartInstrument(TMusicXMLReader* reader, const char **attr, const char* tag);
        // chord
        static void EndChord(TMusicXMLReader* reader, const char* tag);
        // pitch
        static void StartPitch(TMusicXMLReader* reader, const char **attr, const char* tag);
        // step
        static void EndStep(TMusicXMLReader* reader, const char* tag);
        // alter
        static void EndAlter(TMusicXMLReader* reader, const char* tag);
        // octave
        static void EndOctave(TMusicXMLReader* reader, const char* tag);
        // unpitched
        static void StartUnpitched(TMusicXMLReader* reader, const char **attr, const char* tag);
        static void EndUnpitched(TMusicXMLReader* reader, const char* tag);
        // rest
        static void StartRest(TMusicXMLReader* reader, const char **attr, const char* tag);
        static void EndRest(TMusicXMLReader* reader, const char* tag);
        // tie
        static void StartTie(TMusicXMLReader* reader, const char **attr, const char* tag);
        // display-step
        static void EndDisplayStep(TMusicXMLReader* reader, const char* tag);
        // display-octave
        static void EndDisplayOctave(TMusicXMLReader* reader, const char* tag);
        // type
        static void StartType(TMusicXMLReader* reader, const char **attr, const char* tag);
        static void EndType(TMusicXMLReader* reader, const char* tag);
         // dot
        static void EndDot(TMusicXMLReader* reader, const char* tag);
        // stem
        static void EndStem(TMusicXMLReader* reader, const char* tag);
        // accidental
        static void StartAccidental(TMusicXMLReader* reader, const char **attr, const char* tag);
        static void EndAccidental(TMusicXMLReader* reader, const char* tag);
        // time-modification
        static void StartTimeModification(TMusicXMLReader* reader, const char **attr, const char* tag);// actual-notes
        // actual-notes
        static void EndActualNotes(TMusicXMLReader* reader, const char* tag);
        // normal-notes
        static void EndNormalNotes(TMusicXMLReader* reader, const char* tag);
        // normal-type
        static void EndNormalType(TMusicXMLReader* reader, const char* tag);
        // normal-dots
        static void EndNormalDots(TMusicXMLReader* reader, const char* tag);
        // notehead
        static void StartNoteHead(TMusicXMLReader* reader, const char **attr, const char* tag);
        static void EndNoteHead(TMusicXMLReader* reader, const char* tag);
        // beam
        static void StartBeam(TMusicXMLReader* reader, const char **attr, const char* tag);
        static void EndBeam(TMusicXMLReader* reader, const char* tag);
        // notations
        static void StartNotations(TMusicXMLReader* reader, const char **attr, const char* tag);
        static void EndNotations(TMusicXMLReader* reader, const char* tag);
        // tied
        static void StartTied(TMusicXMLReader* reader, const char **attr, const char* tag);
        static void EndTiedSlur(TMusicXMLReader* reader, const char* tag); // the same method is use for
        // slur
        static void StartSlur(TMusicXMLReader* reader, const char **attr, const char* tag);
        // tuplet
        static void StartTuplet(TMusicXMLReader* reader, const char **attr, const char* tag);
        static void EndTuplet(TMusicXMLReader* reader, const char* tag); // the same method is use for
        // tuplet-normal
        static void StartTupletNormal(TMusicXMLReader* reader, const char **attr, const char* tag);
        // tuplet-actual
        static void StartTupletActual(TMusicXMLReader* reader, const char **attr, const char* tag);
        // tuplet-type
        static void EndTupletType(TMusicXMLReader* reader, const char* tag); // the same method is use for normal and actual
        // tuplet-number
        static void EndTupletNumber(TMusicXMLReader* reader, const char* tag); // the same method is use for normal and actual	// tuplet-dot
        static void EndTupletDot(TMusicXMLReader* reader, const char* tag); // the same method is use for normal and actual
        // articulations
        static void StartArticulations(TMusicXMLReader* reader, const char **attr, const char* tag);
        static void EndArticulations(TMusicXMLReader* reader, const char* tag); 
          
        //  accent | strong-accent | staccato | tenuto |
        //  detached-legato | staccatissimo | spiccato |
        //  scoop | plop | doit | falloff | breath-mark | 
        //  caesura | other-articulation
        
        static void StartArticulationsElement(TMusicXMLReader* reader, const char **attr, const char* tag);
        static void EndArticulationsElement(TMusicXMLReader* reader, const char* tag); // the same method is use for all
        // strong-accent
        static void StartStrongAccent(TMusicXMLReader* reader, const char **attr, const char* tag);
        // direction
        static void StartDirection(TMusicXMLReader* reader, const char **attr, const char* tag);
        static void EndDirection(TMusicXMLReader* reader, const char* tag); 
        // offset
        static void EndOffset(TMusicXMLReader* reader, const char* tag); 
        // direction-type
        static void StartDirectionType(TMusicXMLReader* reader, const char **attr, const char* tag);
        static void EndDirectionType(TMusicXMLReader* reader, const char* tag); 
        // octave-shift
        static void StartOctaveShift(TMusicXMLReader* reader, const char **attr, const char* tag);
        // used for all DirectionTypeElement excepts "words" and "dynamcic"
        static void EndDirectionTypeElement(TMusicXMLReader* reader, const char* tag);          
        // bracket
        static void StartBracket(TMusicXMLReader* reader, const char **attr, const char* tag);
        // dashes
        static void StartDashes(TMusicXMLReader* reader, const char **attr, const char* tag);
        // words
        static void StartWords(TMusicXMLReader* reader, const char **attr, const char* tag);
        static void EndWords(TMusicXMLReader* reader, const char* tag);  
        // wedge
        static void StartWedge(TMusicXMLReader* reader, const char **attr, const char* tag);
        // dynamics
        static void StartDynamics(TMusicXMLReader* reader, const char **attr, const char* tag);
        static void EndDynamics(TMusicXMLReader* reader, const char* tag); 
        static void EndDynamicElement(TMusicXMLReader* reader, const char* tag);  
        // metronome
        static void StartMetronome(TMusicXMLReader* reader, const char **attr, const char* tag);
        // beat-unit
        static void EndBeatUnit(TMusicXMLReader* reader, const char* tag);  
        // beat-unit-dot
        static void EndBeatUnitDot(TMusicXMLReader* reader, const char* tag);  
        // per-minute
        static void EndPerMinute(TMusicXMLReader* reader, const char* tag);  
		// lyric
        static void StartLyric(TMusicXMLReader* reader, const char **attr, const char* tag);
		static void EndLyric(TMusicXMLReader* reader, const char* tag); 
		// syllabic
		static void EndSyllabic(TMusicXMLReader* reader, const char* tag); 
		// text
		static void EndText(TMusicXMLReader* reader, const char* tag); 
		// extend
		static void EndExtend(TMusicXMLReader* reader, const char* tag); 
		// laughing
		static void EndLaughing(TMusicXMLReader* reader, const char* tag); 
		// humming
		static void EndHumming(TMusicXMLReader* reader, const char* tag); 
		// end-line
		static void EndEndLine(TMusicXMLReader* reader, const char* tag); 
		// end-paragraph
		static void EndEndParagraph(TMusicXMLReader* reader, const char* tag); 
		// elision
		static void StartElision(TMusicXMLReader* reader, const char **attr, const char* tag);
		static void EndElision(TMusicXMLReader* reader, const char* tag); 
		// glissando
        static void StartGlissando(TMusicXMLReader* reader, const char **attr, const char* tag);
		// slide
        static void StartSlide(TMusicXMLReader* reader, const char **attr, const char* tag);
		// arpeggiate
        static void StartArpeggiate(TMusicXMLReader* reader, const char **attr, const char* tag);
		// non-arpeggiate
        static void StartNonArpeggiate(TMusicXMLReader* reader, const char **attr, const char* tag);
		// other-notation
        //static void StartOtherNotation(TMusicXMLReader* reader, const char **attr, const char* tag);
		// other-articulation
        static void StartOtherArticulation(TMusicXMLReader* reader, const char **attr, const char* tag);
		static void EndOtherArticulation(TMusicXMLReader* reader, const char* tag);
		// rehearsal
		static void StartRehearsal(TMusicXMLReader* reader, const char **attr, const char* tag);
		static void EndRehearsal(TMusicXMLReader* reader, const char* tag);
		// pedal
		static void StartPedal(TMusicXMLReader* reader, const char **attr, const char* tag);
		// damp,damp-all,eyeglasses
		static void StartOtherDirections(TMusicXMLReader* reader, const char **attr, const char* tag);
		static void EndOtherDirections(TMusicXMLReader* reader, const char* tag);
		// other-direction
		static void StartOtherDirection(TMusicXMLReader* reader, const char **attr, const char* tag);
		static void EndOtherDirection(TMusicXMLReader* reader, const char* tag);
		// print
		static void StartPrint(TMusicXMLReader* reader, const char **attr, const char* tag);
		// technicals
        static void StartTechnicals(TMusicXMLReader* reader, const char **attr, const char* tag);
		static void EndTechnicals(TMusicXMLReader* reader, const char* tag);
		// technical
        static void StartTechnical(TMusicXMLReader* reader, const char **attr, const char* tag);
		static void EndTechnical(TMusicXMLReader* reader, const char* tag);
		// harmonic
        static void StartHarmonic(TMusicXMLReader* reader, const char **attr, const char* tag);
		static void EndHarmonic(TMusicXMLReader* reader, const char* tag);
		// natural
		static void EndNatural(TMusicXMLReader* reader, const char* tag);
		// artificial
		static void EndArtificial(TMusicXMLReader* reader, const char* tag);
		// base-pitch
		static void EndBasePitch(TMusicXMLReader* reader, const char* tag);
		// touching-pitch
		static void EndTouchingPitch(TMusicXMLReader* reader, const char* tag);
		// sounding-pitch
		static void EndSoundingPitch(TMusicXMLReader* reader, const char* tag);
 
		// hammer_on, pull_off
        static void StartHammerPull(TMusicXMLReader* reader, const char **attr, const char* tag);
		static void StartPullOff(TMusicXMLReader* reader, const char **attr, const char* tag);
		static void EndHammerPull(TMusicXMLReader* reader, const char* tag);
		// fingering
        static void StartFingering(TMusicXMLReader* reader, const char **attr, const char* tag);
		static void EndFingering(TMusicXMLReader* reader, const char* tag);
		// string
		static void EndString(TMusicXMLReader* reader, const char* tag);
		// fret
		static void EndFret(TMusicXMLReader* reader, const char* tag);
		// bend
        static void StartBend(TMusicXMLReader* reader, const char **attr, const char* tag);
		static void EndBend(TMusicXMLReader* reader, const char* tag);
		// bend-alter
		static void EndBendAlter(TMusicXMLReader* reader, const char* tag);
		// pre-bend
		static void EndPreBend(TMusicXMLReader* reader, const char* tag);
		// release
		static void EndRelease(TMusicXMLReader* reader, const char* tag);
		// with-bar
        static void StartBendWithBar(TMusicXMLReader* reader, const char **attr, const char* tag);
		static void EndBendWithBar(TMusicXMLReader* reader, const char* tag);

		// ornaments
		static void StartOrnaments(TMusicXMLReader* reader, const char **attr, const char* tag);
		static void EndOrnaments(TMusicXMLReader* reader, const char* tag);

		// trill-mark
		static void StartTrillMark(TMusicXMLReader* reader, const char **attr, const char* tag);
		static void EndOrnament(TMusicXMLReader* reader, const char* tag);

		// mordent
		static void StartMordent(TMusicXMLReader* reader, const char **attr, const char* tag);
		// schleifer
		static void StartSchleifer(TMusicXMLReader* reader, const char **attr, const char* tag);
		// other-ornament
		static void StartOtherOrnament(TMusicXMLReader* reader, const char **attr, const char* tag);
		static void EndOtherOrnament(TMusicXMLReader* reader, const char* tag);
		// accidental-mark
		static void StartAccidentalMark(TMusicXMLReader* reader, const char **attr, const char* tag);
		static void EndAccidentalMark(TMusicXMLReader* reader, const char* tag);
		
		// figured-bass
		static void StartFiguredBass(TMusicXMLReader* reader, const char **attr, const char* tag);
		static void EndFiguredBass(TMusicXMLReader* reader, const char* tag);
		// figure
		static void StartFigure(TMusicXMLReader* reader, const char **attr, const char* tag);
		static void EndFigure(TMusicXMLReader* reader, const char* tag);
		// prefix
		static void EndPrefix(TMusicXMLReader* reader, const char* tag);
		// figure-number
		static void EndFigureNumber(TMusicXMLReader* reader, const char* tag);
		// suffix
		static void EndSuffix(TMusicXMLReader* reader, const char* tag);
		
		// harmony
		static void StartHarmony(TMusicXMLReader* reader, const char **attr, const char* tag);
		static void EndHarmony(TMusicXMLReader* reader, const char* tag);
		// root
		static void StartRoot(TMusicXMLReader* reader, const char **attr, const char* tag);
		static void EndRoot(TMusicXMLReader* reader, const char* tag);
		// root-step
		static void EndRootStep(TMusicXMLReader* reader, const char* tag);
		// root-alter
		static void EndRootAlter(TMusicXMLReader* reader, const char* tag);
		// function
		static void StartFunction(TMusicXMLReader* reader, const char **attr, const char* tag);
		static void EndFunction(TMusicXMLReader* reader, const char* tag);
		// kind
		static void EndKind(TMusicXMLReader* reader, const char* tag);
		// inversion
		static void EndInversion(TMusicXMLReader* reader, const char* tag);
		// bass
		static void StartBass(TMusicXMLReader* reader, const char **attr, const char* tag);
		static void EndBass(TMusicXMLReader* reader, const char* tag);
		// bass-step
		static void EndBassStep(TMusicXMLReader* reader, const char* tag);
		// bass-alter
		static void EndBassAlter(TMusicXMLReader* reader, const char* tag);
		// degree
		static void StartDegree(TMusicXMLReader* reader, const char **attr, const char* tag);
		static void EndDegree(TMusicXMLReader* reader, const char* tag);
		// degree-value
		static void EndDegreeValue(TMusicXMLReader* reader, const char* tag);
		// degree-alter
		static void EndDegreeAlter(TMusicXMLReader* reader, const char* tag);
		// degree-type
		static void EndDegreeType(TMusicXMLReader* reader, const char* tag);
		// frame
		static void StartFrame(TMusicXMLReader* reader, const char **attr, const char* tag);
		// frame-strings
		static void EndFrameStrings(TMusicXMLReader* reader, const char* tag);
		// frame-frets
		static void EndFrameFrets(TMusicXMLReader* reader, const char* tag);
		// frame-fret
		static void EndFrameFret(TMusicXMLReader* reader, const char* tag);
		// frame-note
		static void StartFrameNote(TMusicXMLReader* reader, const char **attr, const char* tag);
		static void EndFrameNote(TMusicXMLReader* reader, const char* tag);
		// staff-details
		static void StartStaffDetails(TMusicXMLReader* reader, const char **attr, const char* tag);
		// staff-type
		static void EndStaffType(TMusicXMLReader* reader, const char* tag);
		// staff-lines
		static void EndStaffLines(TMusicXMLReader* reader, const char* tag);
		// staff-tuning
		static void StartStaffTuning(TMusicXMLReader* reader, const char **attr, const char* tag);
		static void EndStaffTuning(TMusicXMLReader* reader, const char* tag);
		// tuning-step
		static void EndTuningStep(TMusicXMLReader* reader, const char* tag);
		// tuning-alter
		static void EndTuningAlter(TMusicXMLReader* reader, const char* tag);
		// tuning-octave
		static void EndTuningOctave(TMusicXMLReader* reader, const char* tag);
		// capo
		static void EndCapo(TMusicXMLReader* reader, const char* tag);
		// measure-style
		static void StartMeasureStyle(TMusicXMLReader* reader, const char **attr, const char* tag);
		// multiple-rest
		static void StartMultipleRest(TMusicXMLReader* reader, const char **attr, const char* tag);
		static void EndMultipleRest(TMusicXMLReader* reader, const char* tag);
		// measure-repeat
		static void StartMeasureRepeat(TMusicXMLReader* reader, const char **attr, const char* tag);
		static void EndMeasureRepeat(TMusicXMLReader* reader, const char* tag);
		// beat-repeat 
		static void StartBeatRepeat(TMusicXMLReader* reader, const char **attr, const char* tag);
		// slash 
		static void StartSlash(TMusicXMLReader* reader, const char **attr, const char* tag);
		// footnote
		static void EndFootNote(TMusicXMLReader* reader, const char* tag);
		// level
		static void StartLevel(TMusicXMLReader* reader, const char **attr, const char* tag);
		static void EndLevel(TMusicXMLReader* reader, const char* tag);
		// voice
		//static void EndVoice(TMusicXMLReader* reader, const char* tag);

    public:
    
        TMusicXMLReader();
        virtual ~TMusicXMLReader() {XML_ParserFree(fParser);}
        
        /*!
        \brief Read a MusicXML file and convert it in a score object.
        \param filename is the pathname of the file.
        \return The result is the score object.
        */
        SScore Read(std::iostream file);
        SScore Read(const char* file);
};


}
  
#endif
