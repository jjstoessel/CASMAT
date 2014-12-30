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
  grame@grame.fr
  
*/

#ifdef WIN32
#pragma warning (disable : 4390)		// inhibit warnings for empty instructions
#pragma warning (disable : 4312)		// inhibit warnings for SMARTP casts
#endif

#include "IMusicXMLReader.h"

#define BUFFSIZE 8192


#define XMLReadDebug	0
#define DebugFile	"XMLReadDebug.txt"

#if XMLReadDebug
#if defined(DebugFile)
#	include <fstream>
	ofstream debug(DebugFile,ios_base::trunc);
#	define dbgStream   debug
#else
#	define dbgStream   cout
#endif
#define DBUG(x) dbgStream << x
#else
#define DBUG(x)  /* PRINT(x) */
#endif

using namespace MusicXML;

namespace MusicXML 
{

void TMusicXMLReader::AddParser(string tag, StartMethod start, EndMethod end)
{	
    fParserTable1.insert(make_pair(tag, start));
    fParserTable2.insert(make_pair(tag, end));
}

void TMusicXMLReader::ReplaceParser(string tag, StartMethod start, EndMethod end)
{	
    fParserTable1[tag] = start;
    fParserTable2[tag] = end;
}

void TMusicXMLReader::AddParser(string tag, StartMethod start)
{	
    fParserTable1.insert(make_pair(tag, start));
}

void TMusicXMLReader::AddParser(string tag, EndMethod end)
{	
    fParserTable2.insert(make_pair(tag, end));
}

void TMusicXMLReader::ReplaceParser(string tag, EndMethod end)
{	
    fParserTable2[tag] = end;
}

TMusicXMLReader::TMusicXMLReader() 
{
    int i;
	fParser = XML_ParserCreate(0);
    
    if (!fParser) {
        fprintf(stderr, "Couldn't allocate memory for parser\n");
        throw -1;
    }
    
    // Set start/end handler
    XML_SetElementHandler(fParser, StartElementHandler, EndElementHandler);
    // Set the data handler
    XML_SetCharacterDataHandler(fParser, CharacterDataHandler);
    // To get the parset in callbacks
    XML_SetUserData(fParser, this);
    
    // Set tag handlers
    
    // score-partwise
    AddParser("score-partwise",StartScorePartwise,EndScorePartwise);
    // score-timewise
    AddParser("score-timewise",StartScoreTimewise,EndScoreTimewise);
    // part-list
    AddParser("part-list",StartPartList);
    // work
    AddParser("work",StartWork);
    // work-title
    AddParser("work-title",EndWorkTitle);
    // work-number
    AddParser("work-number",EndWorkNumber);
    // movement-title
    AddParser("movement-title",EndMovementTitle);
    // movement-number
    AddParser("movement-number",EndMovementNumber);
    // identification
    AddParser("identification",StartIdentification,EndIdentification);
     // creator
    AddParser("creator",StartCreator,EndCreator);
     // rights
    AddParser("rights",StartRights,EndRights);
    // encoding
    AddParser("encoding",StartEncoding);
    // software
    AddParser("software",EndSoftware);
    // encoding-date
    AddParser("encoding-date",EndEncodingDate);
    // encoder
    AddParser("encoder",StartEncoder,EndEncoder);
    // encoding-description
    AddParser("encoding-description",EndDescription);
    // source
    AddParser("source",EndSource);
    // part-list
    AddParser("part-list",StartPartList);
    // score-part
    AddParser("score-part",StartScorePart,EndScorePart);
    // part-name
    AddParser("part-name",EndPartName);
    // part-abbreviation
    AddParser("part-abbreviation",EndPartAbbreviation);
    // midi-device
    AddParser("midi-device",StartMidiDevice);
    // score-instrument
    AddParser("score-instrument",StartScoreInstrument,EndScoreInstrument);
    // instrument-name
    AddParser("instrument-name",EndInstrumentName);
    // instrument-abbreviation
    AddParser("instrument-abbreviation",EndInstrumentAbbrev);
    // midi-instrument
    AddParser("midi-instrument",StartMidiInstrument,EndMidiInstrument);
    // midi-channel
    AddParser("midi-channel",EndMidiChannel);
    // midi-name
    AddParser("midi-name",EndMidiName);
    // midi-bank
    AddParser("midi-bank",EndMidiBank);
    // midi-program
    AddParser("midi-program",EndMidiProgram);
    // midi-unpitched
    AddParser("midi-unpitched",EndMidiUnpitched);
    // part-group
    AddParser("part-group",StartPartGroup,EndScorePartGroup);
    // group-name
    AddParser("group-name",EndGroupName);
    // group-abbreviation
    AddParser("group-abbreviation",EndGroupAbbrev);
    // group-symbol
    AddParser("group-symbol",EndGroupSymbol);
    // part
    AddParser("part",StartPart,EndPart);
    // measure
    AddParser("measure",StartMeasure,EndMeasure);
    // attributes
    AddParser("attributes",StartAttributes,EndAttributes);
    // divisions
    AddParser("divisions",EndDivisions);
    // staves
    AddParser("staves",EndStaves);
    // instruments
    AddParser("instruments",EndInstruments);
    // key
    AddParser("key",StartKey);
    // cancel
    AddParser("cancel",EndCancel);
    // fifths
    AddParser("fifths",EndFifths);
    // mode
    AddParser("mode",EndMode);
    // time
    AddParser("time",StartTime);
    // beat
    AddParser("beats",EndBeats);
    // beat-type
    AddParser("beat-type",EndBeatType);
    // transpose
    AddParser("transpose",StartTranspose);
    // diatonic
    AddParser("diatonic",EndDiatonic);
    // chromatic
    AddParser("chromatic",EndChromatic);
    // octave-change
    AddParser("octave-change",EndOctaveChange);
    // double
    AddParser("double",EndDouble);
    // directive
    AddParser("directive",StartDirective,EndDirective);
     // clef
    AddParser("clef",StartClef,EndClef);
    // sign
    AddParser("sign",EndSign);
    // line
    AddParser("line",EndLine);
    // clef-octave-change
    AddParser("clef-octave-change",EndClefOctaveChange);
    // backup
    AddParser("backup",StartBackup,EndBackup);
    // forward
    AddParser("forward",StartForward,EndForward);
    // duration
    AddParser("duration",EndDuration);
    // voice
    AddParser("voice",EndVoice);
    // staff
    AddParser("staff",EndStaff);
    // barline
    AddParser("barline",StartBarline,EndBarline);
    // bar-style
    AddParser("bar-style",EndBarStyle);
     // wavy-line
    AddParser("wavy-line",StartWavyLine);
    // segno
    AddParser("segno",StartSegno,EndSegno);
    // coda
    AddParser("coda",StartCoda,EndCoda);
    // fermata
    AddParser("fermata",StartFermata,EndFermata);
    // ending
    AddParser("ending",StartEnding);
    // repeat
    AddParser("repeat",StartRepeat);
    // sound
    AddParser("sound",StartSound,EndSound);
    // note
    AddParser("note",StartNote,EndNote);
    // cue
    AddParser("cue",EndCueNote);
    // grace
    AddParser("grace",StartGraceNote);
    // instrument
    AddParser("instrument",StartInstrument);
    // chord
    AddParser("chord",EndChord);
    // pitch
    AddParser("pitch",StartPitch);
    // step
    AddParser("step",EndStep);
    // alter
    AddParser("alter",EndAlter);
    // octave
    AddParser("octave",EndOctave);
    // unpitched
    AddParser("unpitched",StartUnpitched,EndUnpitched);
    // rest
    AddParser("rest",StartRest,EndRest);
    // tie
    AddParser("tie",StartTie);
    // display-step
    AddParser("display-step",EndDisplayStep);
    // display-octave
    AddParser("display-octave",EndDisplayOctave);
    // type
    AddParser("type",StartType,EndType);
    // dot
    AddParser("dot",EndDot);
    // stem
    AddParser("stem",EndStem);
    // accidental
    AddParser("accidental",StartAccidental,EndAccidental);
    // time-modification
    AddParser("time-modification",StartTimeModification);
    // actual-notes
    AddParser("actual-notes",EndActualNotes);
    // normal-notes
    AddParser("normal-notes",EndNormalNotes);
    // normal-type
    AddParser("normal-type",EndNormalType);
    // normal-dots
    AddParser("normal-dots",EndNormalDots);
    // notehead
    AddParser("notehead",StartNoteHead,EndNoteHead);
    // beam
    AddParser("beam",StartBeam,EndBeam);
    // notations
    AddParser("notations",StartNotations,EndNotations);
    // tied
    AddParser("tied",StartTied,EndTiedSlur);
    // slur
    AddParser("slur",StartSlur,EndTiedSlur);
    // tuplet
    AddParser("tuplet",StartTuplet,EndTuplet);
    // tuplet-normal
    AddParser("tuplet-normal",StartTupletNormal);
    // tuplet-actual
    AddParser("tuplet-actual",StartTupletActual);
    // tuplet-type
    AddParser("tuplet-type",EndTupletType);
    // tuplet-number
    AddParser("tuplet-number",EndTupletNumber);
    // tuplet-dot
    AddParser("tuplet-dot",EndTupletDot);
    // articulations
    AddParser("articulations",StartArticulations,EndArticulations);
    
    // articulations elements (accent, strong_accent...)
    const string* articulationStrings = TArticulationElement::getArticulationStrings();
    for (i=0; i < TArticulationElement::last; i++) {
        AddParser(articulationStrings[i],StartArticulationsElement,EndArticulationsElement);
    }
    
    // strong-accent has a speficic start method
    AddParser("strong-accent",StartStrongAccent);
    // direction
    AddParser("direction",StartDirection,EndDirection);
    // offset
    AddParser("offset",EndOffset);
    // direction-type
    AddParser("direction-type",StartDirectionType,EndDirectionType);
    // octave-shift
    AddParser("octave-shift",StartOctaveShift,EndDirectionTypeElement);
    // bracket
    AddParser("bracket",StartBracket,EndDirectionTypeElement);
    // dashes
    AddParser("dashes",StartDashes,EndDirectionTypeElement);
    // words
    AddParser("words",StartWords,EndWords);
    // wedge
    AddParser("wedge",StartWedge,EndDirectionTypeElement);
    // metronome
    AddParser("metronome",StartMetronome,EndDirectionTypeElement);
    // beat-unit
    AddParser("beat-unit",EndBeatUnit);
    // beat-unit-dot
    AddParser("beat-unit-dot",EndBeatUnitDot);
    // per-minute
    AddParser("per-minute",EndPerMinute);
    // dynamics
    AddParser("dynamics",StartDynamics,EndDynamics);
    // dynamics values (pppp, ff...)
    const string* dynamicStrings = TDynamic::getDynamicStrings();
    for (i=0; i < TDynamic::last; i++) {
        AddParser(dynamicStrings[i],EndDynamicElement);
    }
	//lyric
    AddParser("lyric",StartLyric,EndLyric);
	//lyric
    AddParser("syllabic",EndSyllabic);
	// text
	AddParser("text",EndText);
	// extend
	AddParser("extend",EndExtend);
	// laughing
	AddParser("laughing",EndLaughing);
	// humming
	AddParser("end-line",EndEndLine);
	// humming
	AddParser("end-paragraph",EndEndParagraph);
	// elision
    AddParser("elision",StartElision,EndElision);
	// glissando
	AddParser("glissando",StartGlissando);
	// slide
	AddParser("slide",StartSlide);
	// arpeggiate
	AddParser("arpeggiate",StartArpeggiate);
	// non-arpeggiate
	AddParser("non-arpeggiate",StartNonArpeggiate);
	// other-notation
	//AddParser("other-notation",StartOtherNotation);
	// other-articulation
	AddParser("other-articulation",StartOtherArticulation,EndOtherArticulation);
	// rehearsal
	AddParser("rehearsal",StartRehearsal,EndRehearsal);
	// pedal
	AddParser("pedal",StartPedal);
	// damp
	AddParser("damp",StartOtherDirections,EndOtherDirections);
	// damp-all
	AddParser("damp-all",StartOtherDirections,EndOtherDirections);
	// eyeglasses
	AddParser("eyeglasses",StartOtherDirections,EndOtherDirections);
	// other-direction
	AddParser("other-direction",StartOtherDirection,EndOtherDirection);
	// print
	AddParser("print",StartPrint);
	// technicals
	AddParser("technical",StartTechnicals,EndTechnicals);
	
	// technical elements (up-bow, down_bow...)
    const string* technicalStrings = TTechnical::geTechnicalStrings();
    for (i=0; i < TTechnical::last; i++) {
        AddParser(technicalStrings[i],StartTechnical,EndTechnical);
    }
	
	// harmonic
	AddParser("harmonic",StartHarmonic,EndHarmonic);
	// natural
	AddParser("natural",EndNatural);
	// artificial
	AddParser("artificial",EndArtificial);
	// base-pitch
	AddParser("base-pitch",EndBasePitch);
	// touching-pitch
	AddParser("touching-pitch",EndTouchingPitch);
	// sounding-pitch
	AddParser("sounding-pitch",EndSoundingPitch);
	// hammer-on
	ReplaceParser("hammer_on",StartHammerPull,EndHammerPull);	// replace the generic method set in the previous loop
	// fingering
	ReplaceParser("fingering",StartFingering,EndFingering);	// replace the generic method set in the previous loop
	// pull-off
	ReplaceParser("pull-off",StartPullOff,EndHammerPull);	// replace the generic method set in the previous loop
	// bend
	ReplaceParser("bend",StartBend,EndBend);	// replace the generic method set in the previous loop
	// string
	ReplaceParser("string",EndString);	// replace the generic method set in the previous loop
	// fret
	ReplaceParser("fret",EndFret);	// replace the generic method set in the previous loop
	// bend-alter
	AddParser("bend-alter",EndBendAlter);
	// pre-bend
	AddParser("pre-bend",EndPreBend);
	// release
	AddParser("release",EndRelease);
	// with-bar
	AddParser("with-bar",StartBendWithBar,EndBendWithBar);
	
	// ornaments
	AddParser("ornaments",StartOrnaments,EndOrnaments);
	// trill-mark
	AddParser("trill-mark",StartTrillMark,EndOrnament);
	// turn
	AddParser("turn",StartTrillMark,EndOrnament);
	// delayed-turn
	AddParser("delayed-turn",StartTrillMark,EndOrnament);
	// shake
	AddParser("shake",StartTrillMark,EndOrnament);
	// mordent
	AddParser("mordent",StartMordent,EndOrnament);
	// inverted-mordent
	AddParser("inverted-mordent",StartMordent,EndOrnament);
	// schleifer
	AddParser("schleifer",StartSchleifer,EndOrnament);
	// other-ornament
	AddParser("other-ornament",StartOtherOrnament,EndOtherOrnament);
	// accidental-mark
	AddParser("accidental-mark",StartAccidentalMark,EndAccidentalMark);
	// figured-bass
	AddParser("figured-bass",StartFiguredBass,EndFiguredBass);
	// figure
	AddParser("figure",StartFigure,EndFigure);
	// prefix
	AddParser("figure",EndPrefix);
	// figure-number
	AddParser("figure-number",EndFigureNumber);
	// suffix
	AddParser("suffix",EndSuffix);
	// harmony
	AddParser("harmony",StartHarmony,EndHarmony);
	// root
	AddParser("root",StartRoot,EndRoot);
	// root-step
	AddParser("root-step",EndRootStep);
	// root-alter
	AddParser("root-alter",EndRootAlter);
	// function
	AddParser("function",StartFunction,EndFunction);
	// kind
	AddParser("kind",EndKind);
	// inversion
	AddParser("inversion",EndInversion);
	// bass
	AddParser("bass",StartBass,EndBass);
	// bass-step
	AddParser("bass-step",EndBassStep);
	// bass-alter
	AddParser("bass-alter",EndBassAlter);
	// degree
	AddParser("degree",StartDegree,EndDegree);
	// degree-value
	AddParser("degree-value",EndDegreeValue);
	// degree-alter
	AddParser("degree-alter",EndDegreeAlter);
	// degree-type
	AddParser("degree-type",EndDegreeType);
	// frame
	AddParser("frame",StartFrame);
	// frame-strings
	AddParser("frame-strings",EndFrameStrings);
	// frame-frets
	AddParser("frame-frets",EndFrameFrets);
	// degree-type
	AddParser("frame-fret",EndFrameFret);
	// frame-note
	AddParser("frame-note",StartFrameNote,EndFrameNote);
	
	// staff-details
	AddParser("staff-details",StartStaffDetails);
	// staff-type
	AddParser("staff-type",EndStaffType);
	// staff-lines
	AddParser("staff-lines",EndStaffLines);
	// staff-tuning
	AddParser("staff-tuning",StartStaffTuning,EndStaffTuning);
	// tuning-step
	AddParser("tuning-step",EndTuningStep);
	// tuning-alter
	AddParser("tuning-alter",EndTuningAlter);
	// tuning-octave
	AddParser("tuning-octave",EndTuningOctave);
	// capo
	AddParser("capo",EndCapo);
	// measure-style
	AddParser("measure-style",StartMeasureStyle);
	// multiple-rest
	AddParser("multiple-rest",StartMultipleRest,EndMultipleRest);
	// measure-repeat
	AddParser("measure-repeat",StartMeasureRepeat,EndMeasureRepeat);
	// beat-repeat 
	AddParser("beat-repeat",StartBeatRepeat);
	// slash
	AddParser("slash",StartSlash);
	// footnote
	AddParser("footnote",EndFootNote);
	// level
	AddParser("level",StartLevel,EndLevel);
	// voice
	AddParser("voice",EndVoice);

    // Init context
    fPWScore = 0;
    fTWScore = 0;
    fScoreHeader = 0;
    fScorePart = 0;
    fIdentification = 0;
    fCreator = 0;
    fRights = 0;     
    fScoreInstrument = 0;
    fMidiInstrument = 0;
    fPartGroup = 0;
    fPWPart = 0;
    fTWPart = 0;    
    fPWMeasure = 0;
    fTWMeasure = 0;
    fAttributes = 0;
    fSound = 0;
    fClef = 0;
    fBackup = 0;
    fForward = 0;
    fDirection = 0;  
    fDirectionType = 0;  
    fDirectionTypeElement = 0;  
    fChord = 0;  
    fNote = 0;  
    fBeam = 0;
    fNotation = 0;
    fTieSlur = 0;
    fTuplet = 0;
    fArticulations = 0;
    fArticulationsElement = 0;
    fBarline = 0;
    fFermata = 0;
    fDynamic = 0;
    fLastNoteIndex = -1;
    fInChord = false;
	fLyric = 0;
	fMultipleLyricPart = 0;
	fOtherArticulation = 0;
	fRehearsal = 0;
	fOtherDirections = 0;
	fOtherDirection = 0;
	fTechnicals = 0;
	fTechnical = 0;
	fHarmonic = 0;
	fHammerPull = 0;
	fBend = 0;
	fBendWithBar = 0;
	fOrnaments = 0;
	fOrnament = 0;
	fAccidentalmark = 0;
	fFiguredBass = 0; 
	fFigure = 0;
	fHarmony = 0;
	fHarmonyChord = 0;
	fRootFunction = 0;
	fDegree = 0;
	fFrameNote = 0;
	fFingering = 0;
	fStaffTuning = 0;
	fMeasureStyleElement = 0;
	fEditorial = 0;
    
    for (i = 0; i < 128 ; i++) { fPitchTable[i] = 0; }
 }

// score-partwise
void TMusicXMLReader::StartScorePartwise(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartScorePartwise\n"));
    assert(reader->fPWScore == 0);
    reader->fPWScore = newScorePartwise();
    assert(reader->fScoreHeader == 0);
    reader->fScoreHeader = newScoreHeader();
}

void TMusicXMLReader::EndScorePartwise(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndScorePartwise\n"));
    reader->fPWScore->scoreHeader() = reader->fScoreHeader;
    reader->fScoreHeader = 0;
}

// score-timewise
void TMusicXMLReader::StartScoreTimewise(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartScoreTimewise\n"));
    assert(reader->fTWScore == 0);
    reader->fTWScore = newScoreTimewise();
    assert(reader->fScoreHeader == 0);
    reader->fScoreHeader = newScoreHeader();
}

void TMusicXMLReader::EndScoreTimewise(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndScoreTimewise\n"));
    reader->fTWScore->scoreHeader() = reader->fScoreHeader;
    reader->fScoreHeader = 0;
}

// part-list
void TMusicXMLReader::StartPartList(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartPartList\n"));
    reader->fScoreHeader->partList() = newPartList();
}

// movement-title
void TMusicXMLReader::EndMovementTitle(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndMovementTitle\n"));
    assert(reader->fScoreHeader);
    reader->fScoreHeader->setMovementTitle(reader->GetDataString());
}

// movement-number
void TMusicXMLReader::EndMovementNumber(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndMovementNumber\n"));
    assert(reader->fScoreHeader);
    reader->fScoreHeader->setMovementNum(reader->GetDataString());
}

// work
void TMusicXMLReader::StartWork(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartWork\n"));
    assert(reader->fScoreHeader);
    reader->fScoreHeader->work() = newWork();
}

// work-title
void TMusicXMLReader::EndWorkTitle(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndWorkTitle\n"));
    assert(reader->fScoreHeader->work());
    reader->fScoreHeader->work()->setTitle(reader->GetDataString());
}

// work-number
void TMusicXMLReader::EndWorkNumber(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndWorkNumber\n"));
    assert(reader->fScoreHeader->work());
    reader->fScoreHeader->work()->setNum(reader->GetDataString());
}

// identification
void TMusicXMLReader::StartIdentification(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartIdentification\n"));
    assert(reader->fIdentification == 0);
    reader->fIdentification = newIdentification();
}

void TMusicXMLReader::EndIdentification(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndIdentification\n"));
    
    assert(reader->fIdentification);
    
    // needed because it appears in TScorePart or TScoreHeader
    if (reader->fScorePart) {
        reader->fScorePart->identification() = reader->fIdentification;
    }else if (reader->fScoreHeader) {
        reader->fScoreHeader->identification() = reader->fIdentification;
    }else{
        DBUG(("EndIdentification : value not used\n"));
        assert(false);
    }
    
    reader->fIdentification = 0;
}

// creator
void TMusicXMLReader::StartCreator(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartCreator\n"));
    assert(reader->fCreator == 0);
    reader->fCreator = newCreator();
    for (int i=0; attr[i]; i+=2)
    {
        DBUG(("attr[i] %s %s\n", attr[i], attr[i+1]));
    }
    if (attr[0]) 
		reader->fCreator->setType(attr[1]);
}

void TMusicXMLReader::EndCreator(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndCreator\n"));
    reader->fCreator->setName(reader->GetDataString());
    reader->fIdentification->add(reader->fCreator);
    reader->fCreator = 0;
}

// rights
void TMusicXMLReader::StartRights(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartRights\n"));
    assert(reader->fRights == 0);
    reader->fRights = newRights();
    for (int i=0; attr[i]; i+=2)
    {
        DBUG(("attr[i] %s %s\n", attr[i], attr[i+1]));
    }
    if (attr[0]) 
		reader->fRights->setType(attr[1]);
}
    
void TMusicXMLReader::EndRights(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndRights\n"));
    reader->fRights->setRights(reader->GetDataString());
    reader->fIdentification->add(reader->fRights);
    reader->fRights = 0;
}

// encoding
void TMusicXMLReader::StartEncoding(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartEncoding\n"));
    reader->fIdentification->encoding() = newEncoding();
}

// software
void TMusicXMLReader::EndSoftware(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndSoftware\n"));
    assert(reader->fIdentification->encoding());
    reader->fIdentification->encoding()->setSoftware(reader->GetDataString());
}

// encoding-date
void TMusicXMLReader::EndEncodingDate(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndEncodingDate\n"));
    assert(reader->fIdentification->encoding());
    reader->fIdentification->encoding()->setDate(reader->GetDataString());
}

// encoder
void TMusicXMLReader::StartEncoder(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartEncoder\n"));
    
    for (int i=0; attr[i]; i+=2)
    {
        DBUG(("attr[i] %s %s\n", attr[i], attr[i+1]));
    }
    
    assert(reader->fIdentification->encoding());
    if (attr[0]) 
		reader->fIdentification->encoding()->setEncoderType(attr[1]);
}

void TMusicXMLReader::EndEncoder(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndEncoder\n"));
    assert(reader->fIdentification->encoding());
    reader->fIdentification->encoding()->setEncoder(reader->GetDataString());
}

// encoding-description
void TMusicXMLReader::EndDescription(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndDescription\n"));
    assert(reader->fIdentification->encoding());
    reader->fIdentification->encoding()->setDescription(reader->GetDataString());
}

// source
void TMusicXMLReader::EndSource(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndSource\n"));
    assert(reader->fIdentification);
    reader->fIdentification->setSource(reader->GetDataString());
}
    
// score-part
void TMusicXMLReader::StartScorePart(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartScorePart\n"));
    
    for (int i=0; attr[i]; i+=2)
    {
        DBUG(("attr[i] %s %s\n", attr[i], attr[i+1]));
    }
    assert(reader->fScorePart == 0);
    reader->fScorePart = newScorePart(attr[1]);
}

void TMusicXMLReader::EndScorePart(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndScorePart\n"));
    assert(reader->fScoreHeader->partList());
    assert(reader->fScorePart);
    reader->fScoreHeader->partList()->add(reader->fScorePart);
    reader->fScorePart = 0;
}

// part-name
void TMusicXMLReader::EndPartName(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndPartName\n"));
    assert(reader->fScorePart);
    reader->fScorePart->setPartName(reader->GetDataString());
}

// part-abbreviation
void TMusicXMLReader::EndPartAbbreviation(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndPartAbbreviation\n"));
    assert(reader->fScorePart);
    reader->fScorePart->setPartAbbrev(reader->GetDataString());
}

// midi-device // A FINIR
void TMusicXMLReader::StartMidiDevice(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartMidiDevice\n"));
    assert(reader->fScorePart);
    reader->fScorePart->mididevice() = newMidiDevice();
}

// score-instrument
void TMusicXMLReader::StartScoreInstrument(TMusicXMLReader* reader, const char **attr, const char* tag) 
{
    DBUG(("StartScoreInstrument\n"));
    assert(reader->fScoreInstrument == 0);
    assert(attr[0]);
    reader->fScoreInstrument = newScoreInstrument(attr[1]);
}

void TMusicXMLReader::EndScoreInstrument(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndScoreInstrument\n"));
    assert(reader->fScorePart);
    assert(reader->fScoreInstrument);
    reader->fScorePart->add(reader->fScoreInstrument);
    reader->fScoreInstrument = 0;
}
    
// instrument-name
void TMusicXMLReader::EndInstrumentName(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndInstrumentName\n"));
    assert(reader->fScoreInstrument);
    reader->fScoreInstrument->setName(reader->GetDataString());
}

// instrument-abbreviation
void TMusicXMLReader::EndInstrumentAbbrev(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndInstrumentAbbrev\n"));
    assert(reader->fScoreInstrument);
    reader->fScoreInstrument->setAbbrev(reader->GetDataString());
}

// midi-instrument
void TMusicXMLReader::StartMidiInstrument(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StarMidiInstrument\n"));
    assert(reader->fMidiInstrument == 0);
    reader->fMidiInstrument = newMidiInstrument(attr[1]);
}

void TMusicXMLReader::EndMidiInstrument(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndMidiInstrument\n"));
    
    if(reader->fScorePart) { // parsing a "score-part" element
        reader->fScorePart->add(reader->fMidiInstrument);
    }else { // parsing a "sound" element
        reader->fSound->add(reader->fMidiInstrument);
    }
    
    reader->fMidiInstrument = 0;
}

// midi-channel
void TMusicXMLReader::EndMidiChannel(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndMidiChannel\n"));
    assert(reader->fMidiInstrument);
    reader->fMidiInstrument->setChannel(reader->GetDataLong());
}

// midi-name
void TMusicXMLReader::EndMidiName(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndMidiName\n"));
    assert(reader->fMidiInstrument);
    reader->fMidiInstrument->setName(reader->GetDataString());
}

// midi-bank
void TMusicXMLReader::EndMidiBank(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndMidiBank\n"));
    assert(reader->fMidiInstrument);
    reader->fMidiInstrument->setBank(reader->GetDataLong());
}

// midi-program
void TMusicXMLReader::EndMidiProgram(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndMidiProgram\n"));
    assert(reader->fMidiInstrument);
    reader->fMidiInstrument->setProgram(reader->GetDataLong());
}

// midi-unpitched
void TMusicXMLReader::EndMidiUnpitched(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndMidiUnpitched\n"));
    assert(reader->fMidiInstrument);
    reader->fMidiInstrument->setUnpitched(reader->GetDataLong());
}

// part-group
void TMusicXMLReader::StartPartGroup(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartPartGroup\n"));
    
    for (int i=0; attr[i]; i+=2)
    {
        DBUG(("attr[i] %s %s\n", attr[i], attr[i+1]));
    }
    assert(reader->fPartGroup == 0);
    reader->fPartGroup = newPartGroup(StartStop::xml(attr[1]));
    // number attribute
    if (attr[2]) reader->fPartGroup->setNumber(atoi(attr[3]));
}

void TMusicXMLReader::EndScorePartGroup(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndScoreParGroup\n"));
    assert(reader->fScoreHeader->partList());
    assert(reader->fPartGroup);
    reader->fScoreHeader->partList()->add(reader->fPartGroup);
    reader->fPartGroup = 0;
}

// group-name
void TMusicXMLReader::EndGroupName(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndGroupName\n"));
    assert(reader->fPartGroup);
    reader->fPartGroup->setGroupName(reader->GetDataString());
}

// group-abbreviation
void TMusicXMLReader::EndGroupAbbrev(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndGroupAbbrev\n"));
    assert(reader->fPartGroup);
    reader->fPartGroup->setGroupAbbrev(reader->GetDataString());
}

// group-symbol
void TMusicXMLReader::EndGroupSymbol(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndGroupSymbol\n"));
    reader->fPartGroup->setSymbol(TPartGroup::xmlsymbol(reader->GetDataString()));
}

// part
void TMusicXMLReader::StartPart(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartPart\n"));
    
    for (int i=0; attr[i]; i+=2)
    {
        DBUG(("attr[i] %s %s\n", attr[i], attr[i+1]));
    }
    
    if (reader->fPWScore) { // parsing score-partwise
        assert(reader->fPWPart == 0);
        reader->fPWPart = newPWPart(attr[1]);
    }else{ // parsing score-timewise
        assert(reader->fTWPart == 0);
        reader->fTWPart = newTWPart(attr[1]);
    }
}

void TMusicXMLReader::EndPart(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndPart\n"));
    
    if (reader->fPWScore) { // parsing score-partwise
        reader->fPWScore->add(reader->fPWPart);
        reader->fPWPart = 0;
    }else{ // parsing score-timewise
        reader->fTWMeasure->add(reader->fTWPart);
        reader->fTWPart = 0;
    }
}

// measure
void TMusicXMLReader::StartMeasure(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartMeasure\n"));
    
    if (reader->fPWScore) { // parsing score-partwise
        assert(reader->fPWMeasure == 0);
        reader->fPWMeasure = newPWMeasure(attr[1]);
        for (int i=0; attr[i]; i+=2)
        {
            DBUG(("attr[i] %s %s\n", attr[i], attr[i+1]));
            if (EqualStr(attr[i], "implicit")) 
                reader->fPWMeasure->setImplicit(YesNo::xml(attr[i+1]));
            else if (EqualStr(attr[i], "non-controling")) 
                reader->fPWMeasure->setNonControlling(YesNo::xml(attr[i+1]));
        }
    }else{ // parsing score-timewise
        assert(reader->fTWMeasure == 0);
        reader->fTWMeasure = newTWMeasure(attr[1]);
        for (int i=0; attr[i]; i+=2)
        {
            DBUG(("attr[i] %s %s\n", attr[i], attr[i+1]));
            if (EqualStr(attr[i], "implicit")) 
                reader->fTWMeasure->setImplicit(YesNo::xml(attr[i+1]));
            else if (EqualStr(attr[i], "non-controling")) 
                reader->fTWMeasure->setNonControlling(YesNo::xml(attr[i+1]));
        }
    }
    }

void TMusicXMLReader::EndMeasure(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndMeasure\n"));
    
    if (reader->fPWScore) { // parsing score-partwise
        reader->fPWPart->add(reader->fPWMeasure);
        reader->fPWMeasure = 0;
    }else{ // parsing score-timewise
        reader->fTWScore->add(reader->fTWMeasure);
        reader->fTWMeasure = 0;
    }
}

// management of music data
long TMusicXMLReader::addMusicData(TMusicXMLReader* reader, SMusicData data) 
{
    assert(data);
        
    if (reader->fPWScore) { // parsing score-partwise
        return reader->fPWMeasure->add(data);
    }else{ // parsing score-timewise
        return reader->fTWPart->add(data);
    }
}

// management of music data
void TMusicXMLReader::setMusicData(TMusicXMLReader* reader, SMusicData data, long index) 
{
    assert(data);
        
    if (reader->fPWScore) { // parsing score-partwise
        reader->fPWMeasure->data()[index] = data;
    }else{ // parsing score-timewise
        reader->fTWPart->data()[index] = data;
    }
}
// management of music data
SMusicData& TMusicXMLReader::getMusicData(TMusicXMLReader* reader, long index) 
{        
    if (reader->fPWScore) { // parsing score-partwise
        return reader->fPWMeasure->data()[index];
    }else{ // parsing score-timewise
        return reader->fTWPart->data()[index];
    }
}

// attributes
void TMusicXMLReader::StartAttributes(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartAttributes\n"));
    assert(reader->fAttributes == 0);
    reader->fAttributes = newAttributes();            
}

void TMusicXMLReader::EndAttributes(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndAttributes\n"));
    addMusicData(reader, reader->fAttributes);
    reader->fAttributes = 0;
}

// divisions
void TMusicXMLReader::EndDivisions(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndDivisions\n"));
    assert(reader->fAttributes);
    reader->fAttributes->setDivisions(reader->GetDataLong());
}

// staves
void TMusicXMLReader::EndStaves(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndStaves\n"));
    assert(reader->fAttributes);
    reader->fAttributes->setStaves(reader->GetDataLong());
}

// instruments
void TMusicXMLReader::EndInstruments(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndInstruments\n"));
    assert(reader->fAttributes);
    reader->fAttributes->setInstrument(reader->GetDataLong());
}

// key
void TMusicXMLReader::StartKey(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartKey\n"));
    assert(reader->fAttributes);
    reader->fAttributes->key() = newKey();            
}

// cancel
void TMusicXMLReader::EndCancel(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndCancel\n"));
    assert(reader->fAttributes->key());
    reader->fAttributes->key()->setCancel(reader->GetDataLong());
}

// fifths
void TMusicXMLReader::EndFifths(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndFifths\n"));
    assert(reader->fAttributes->key());
    reader->fAttributes->key()->setFifths(reader->GetDataLong());
}

// mode
void TMusicXMLReader::EndMode(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndMode\n"));
    assert(reader->fAttributes->key());
    reader->fAttributes->key()->setMode(TKey::xmlmode(reader->GetDataString()));
}

// time
void TMusicXMLReader::StartTime(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartTime\n"));
    assert(reader->fAttributes);
    for (int i=0; attr[i]; i+=2)
    {
        DBUG(("attr[i] %s %s\n", attr[i], attr[i+1]));
    }

    STimeSign timeSign = newTimeSign();
    if (attr[0]) 
		timeSign->setSymbol(TTimeSign::xmlsymbol(attr[1]));
    reader->fAttributes->timeSign() = timeSign;          
}

// beats
void TMusicXMLReader::EndBeats(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndBeats\n"));
    reader->fBeat = reader->GetDataString();
}

    // beat-type // A FINIR traiter les cas complexes du genre 3+2/8
void TMusicXMLReader::EndBeatType(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndBeatType\n"));
    //fstring fBeatType = reader->GetDataString();
    assert(reader->fAttributes->timeSign());
    reader->fAttributes->timeSign()->add(atoi(reader->fBeat.c_str()),reader->GetDataLong());
}

// transpose
void TMusicXMLReader::StartTranspose(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartTranspose\n"));
    assert(reader->fAttributes);
    reader->fAttributes->transpose() = newTranspose();          
}

// diatonic
void TMusicXMLReader::EndDiatonic(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndDiatonic\n"));
    assert(reader->fAttributes->transpose());
    reader->fAttributes->transpose()->setDiatonic(reader->GetDataLong());
}

// chromatic
void TMusicXMLReader::EndChromatic(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndChromatic\n"));
    assert(reader->fAttributes->transpose());
    reader->fAttributes->transpose()->setChromatic(reader->GetDataLong());
}

// octave-change
void TMusicXMLReader::EndOctaveChange(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndOctaveChange\n"));
    assert(reader->fAttributes->transpose());
    reader->fAttributes->transpose()->setOctaveChge(reader->GetDataLong());
}

// double
void TMusicXMLReader::EndDouble(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndDouble\n"));
    assert(reader->fAttributes->transpose());
    reader->fAttributes->transpose()->setDouble(reader->GetDataLong());
}

// directive
void TMusicXMLReader::StartDirective(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartDirective\n"));
    assert(reader->fAttributes);
	SDirective directive = newDirective();
	
    for (int i=0; attr[i]; i+=2)
    {
        DBUG(("attr[i] %s %s\n", attr[i], attr[i+1]));
		if (EqualStr(attr[i], "font-family")) 
            directive->font().setFamily(attr[i+1]);
		else if (EqualStr(attr[i], "font-style")) 
            directive->font().setStyle(attr[i+1]);
		else if (EqualStr(attr[i], "font-size")) 
            directive->font().setSize(attr[i+1]);
		else if (EqualStr(attr[i], "font-weight")) 
            directive->font().setWeight(attr[i+1]);
	}
  
    if (attr[0]) 
		directive->setLang(attr[1]);
    reader->fAttributes->directive() = directive;          
}

void TMusicXMLReader::EndDirective(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndDirective\n"));
    assert(reader->fAttributes->directive());
    reader->fAttributes->directive()->setValue(reader->GetDataString());
}

// clef
void TMusicXMLReader::StartClef(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartClef\n"));
    assert(reader->fAttributes);
    for (int i=0; attr[i]; i+=2)
    {
        DBUG(("attr[i] %s %s\n", attr[i], attr[i+1]));
    }
    assert(reader->fClef == 0);
    reader->fClef = newClef();
    if (attr[0])
		reader->fClef->setStaffNum(atoi(attr[1]));
}
    
void TMusicXMLReader::EndClef(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndClef\n"));
    assert(reader->fAttributes);
    reader->fAttributes->add(reader->fClef);
    reader->fClef = 0;
}

// sign
void TMusicXMLReader::EndSign(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndSign\n"));
    assert(reader->fClef);
    reader->fClef->setSign(TClef::xmlsign(reader->GetDataString()));
}

// line
void TMusicXMLReader::EndLine(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndLine\n"));
    assert(reader->fClef);
    reader->fClef->setLine(reader->GetDataLong());
}

// clef-octave-change
void TMusicXMLReader::EndClefOctaveChange(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndClefOctaveChange\n"));
    assert(reader->fClef);
    reader->fClef->setOctave(reader->GetDataLong());
}

// backup
void TMusicXMLReader::StartBackup(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartBackup\n"));
    assert(reader->fBackup == 0);
    reader->fBackup = newBackup();
}

void TMusicXMLReader::EndBackup(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndBackup\n"));
    addMusicData(reader, reader->fBackup);
    reader->fBackup = 0;
}

// forward
void TMusicXMLReader::StartForward(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartForward\n"));
    assert(reader->fForward == 0);
    reader->fForward = newForward();
}

void TMusicXMLReader::EndForward(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndForward\n"));
    addMusicData(reader, reader->fForward);
    reader->fForward  = 0;
}

// duration
void TMusicXMLReader::EndDuration(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndDuration\n"));
    
    if (reader->fBackup) { // parsing a "backup" element
        reader->fBackup->setDuration(reader->GetDataLong());
    }else if (reader->fForward) { // parsing a "forward" element
        reader->fForward->setDuration(reader->GetDataLong());
    }else if (reader->fNote){ // parsing a "note" element
        reader->fNote->setDuration(reader->GetDataLong());
    }else{
        DBUG(("EndDuration : value not used\n"));
        assert(false);
    }
}

// voice
void TMusicXMLReader::EndVoice(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndVoice\n"));
    
    if (reader->fForward) { // parsing a "forward" element
        reader->fForward->setVoice(reader->GetDataLong());
    }else if (reader->fDirection){ // parsing a "direction" element
        reader->fDirection->setVoice(reader->GetDataLong());
    }else if (reader->fNote){ // parsing a "note" element
		reader->fNote->graphics()->setVoice(reader->GetDataLong());
	}else if (reader->fEditorial){ // parsing a "note" element
		reader->fEditorial->voice()->setData(reader->GetDataString());
    }else{
        DBUG(("EndVoice : value not used\n"));
        assert(false);
    }
}

// staff
void TMusicXMLReader::EndStaff(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndStaff\n"));
    
    if (reader->fForward) { // parsing a "forward" element
        reader->fForward->setStaff(reader->GetDataLong());
    }else if (reader->fDirection){ // parsing a "direction" element
        reader->fDirection->setStaff(reader->GetDataLong());
    }else if (reader->fNote){ // parsing a "note" element
            reader->fNote->graphics()->setStaff(reader->GetDataLong());
    }else{
        DBUG(("EndStaff : value not used\n"));
        assert(false);
    }
}

// barline
void TMusicXMLReader::StartBarline(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("barline\n"));
    assert(reader->fBarline == 0);
    reader->fBarline = newBarline();
    for (int i=0; attr[i]; i+=2)
    {
        DBUG(("attr[i] %s %s\n", attr[i], attr[i+1]));
    }
    if (attr[0]) 
		reader->fBarline->setLocation(TBarline::xmllocation(attr[1]));
}

void TMusicXMLReader::EndBarline(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndBarline\n"));
    addMusicData(reader, reader->fBarline);
    reader->fBarline = 0;
}

// bar-style
void TMusicXMLReader::EndBarStyle(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndBarStyle\n"));
    reader->fBarline->setBarStyle(TBarline::xmlstyle(reader->GetDataString()));
}

// wavy-line // A FINIR POSITIONABLE
void TMusicXMLReader::StartWavyLine(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("wavy-line\n"));
	SWavyLine wavyline = newWavyLine();
	
	if (reader->fBarline) {
		reader->fBarline->wavyLine() = wavyline;
	} else {
		reader->fOrnament = wavyline;
	}
     
    for (int i=0; attr[i]; i+=2)
    {
        if (EqualStr(attr[i], "type")) 
			wavyline->setType(StartStop::xml(attr[i+1]));
        else if (EqualStr(attr[i], "number")) 
            wavyline->setNumber(atoi(attr[i+1]));
        else if (EqualStr(attr[i], "placement")) 
            wavyline->placement().set(TPlacement::xmlplace(attr[i+1]));
        else {
            wavyline->position().set(TPosition::xmlpos(attr[i]), atoi(attr[i+1]));
            if (TPosition::xmlpos(attr[i]) == 0) DBUG(("StartWavyLine %s\n",attr[i]));
        }
    }

	assert(wavyline->getType() != StartStop::undefined);
}
    
// segno 
void TMusicXMLReader::StartSegno(TMusicXMLReader* reader, const char **attr, const char* tag) 
{
    DBUG(("StartSegno\n"));
    SSegno segno = newSegno();
    
    for (int i=0; attr[i]; i+=2)
    {
        DBUG(("attr[i] %s %s\n", attr[i], attr[i+1]));
        segno->position().set(TPosition::xmlpos(attr[i]), atoi(attr[i+1]));
        if (TPosition::xmlpos(attr[i]) == 0) DBUG(("StartSegno %s\n",attr[i]));
    }
    
    if (reader->fBarline) { // parsing a "barline" element
        reader->fBarline->segno() = segno;
    } if (reader->fDirectionType) {// // parsing a "direction-type" element
        assert(reader->fDirectionTypeElement == 0);
        reader->fDirectionTypeElement = segno;
    }else {
        DBUG(("EndSegno : value not used\n"));
        assert(false);
    }
}

void TMusicXMLReader::EndSegno(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndSegno\n"));
   
    if (reader->fBarline) { // parsing a "barline" element
        if (!reader->fBarline->segno())  // add a Segno only for an end only tag
            reader->fBarline->segno() = newSegno();
    }else if (reader->fDirectionType){ // parsing a "direction-type" element
        if (reader->fDirectionTypeElement) { // add a Segno only for an end only tag
            reader->fDirectionType->add(reader->fDirectionTypeElement);
            reader->fDirectionTypeElement = 0;
        }else{
            reader->fDirectionType->add(newSegno());
        }
    }else{
        DBUG(("EndSegno : value not used\n"));
        assert(false);
    }
}

// coda 
void TMusicXMLReader::StartCoda(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartCoda\n"));
    SCoda coda = newCoda();
    
    for (int i=0; attr[i]; i+=2)
    {
        DBUG(("attr[i] %s %s\n", attr[i], attr[i+1]));
        coda->position().set(TPosition::xmlpos(attr[i]), atoi(attr[i+1]));
        if (TPosition::xmlpos(attr[i]) == 0) DBUG(("StartCoda %s\n",attr[i]));
    }
    
    if (reader->fBarline) { // parsing a "barline" element
        reader->fBarline->coda() = coda;
    } if (reader->fDirectionType) {// // parsing a "direction-type" element
        assert(reader->fDirectionTypeElement == 0);
        reader->fDirectionTypeElement = coda;
    }else {
        DBUG(("EndCoda : value not used\n"));
        assert(false);
    }
}

void TMusicXMLReader::EndCoda(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndCoda\n"));
   
    if (reader->fBarline) { // parsing a "barline" element
        if (!reader->fBarline->coda())  // add a Coda only for an end only tag
            reader->fBarline->coda() = newCoda();
    }else if (reader->fDirectionType){ // parsing a "direction-type" element
        if (reader->fDirectionTypeElement) { // add a Coda only for an end only tag
            reader->fDirectionType->add(reader->fDirectionTypeElement);
            reader->fDirectionTypeElement = 0;
        }else{
            reader->fDirectionType->add(newCoda());
        }
    }else{
        DBUG(("EndCoda : value not used\n"));
        assert(false);
    }
}

// fermata 
void TMusicXMLReader::StartFermata(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartFermata\n"));
    reader->fFermata = newFermata();
    
    for (int i=0; attr[i]; i+=2)
    {
        DBUG(("attr[i] %s %s\n", attr[i], attr[i+1]));
        if (EqualStr(attr[i], "type")) 
            reader->fFermata->setType(TFermata::xmltype(attr[i+1]));
        else{
            reader->fFermata->position().set(TPosition::xmlpos(attr[i]), atoi(attr[i+1]));
            if (TPosition::xmlpos(attr[i]) == 0) DBUG(("StartFermata %s\n",attr[i]));
        }
    }
}

void TMusicXMLReader::EndFermata(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndFermata\n"));
    
    assert(reader->fFermata);
    
    if (reader->fBarline) { // parsing a "barline" element
        reader->fBarline->fermata() = reader->fFermata;
    }else if (reader->fNotation) { // parsing a "notations" element
        reader->fNotation->add(reader->fFermata);
    }else{
        DBUG(("EndStaff : value not used\n"));
        assert(false);
    }
    reader->fFermata = 0;
}
    
// ending
void TMusicXMLReader::StartEnding(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartEnding\n"));
    assert(reader->fBarline);
    long num = 1;
    string type;
    
    for (int i=0; attr[i]; i+=2)
    {
        DBUG(("attr[i] %s %s\n", attr[i], attr[i+1]));
        if (EqualStr(attr[i], "type")) 
            type = attr[i+1];
        else if (EqualStr(attr[i], "number"))
            num = atoi(attr[i+1]);
        else{
            DBUG(("StartEnding : value not used\n"));
            assert(false);
        }
    }
    
    reader->fBarline->ending() = newEnding(num,TEnding::xmltype(type));
}

// repeat
void TMusicXMLReader::StartRepeat(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartRepeat\n"));
    assert(reader->fBarline);
    
    for (int i=0; attr[i]; i+=2)
    {
        DBUG(("attr[i] %s %s\n", attr[i], attr[i+1]));
    }
    
    SRepeat repeat = newRepeat(TRepeat::xmldirection(attr[1]));
    if (attr[2]) repeat->setTimes(atoi(attr[3]));
    reader->fBarline->repeat() = repeat;
}

// sound
void TMusicXMLReader::StartSound(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartSound\n"));
    assert(reader->fSound == 0);
    reader->fSound = newSound();
    
    for (int i=0; attr[i]; i+=2)
    {
        DBUG(("attr[i] %s %s\n", attr[i], attr[i+1]));
        if (EqualStr(attr[i], "tempo")) 
            reader->fSound->setTempo(atoi(attr[i+1]));
        else if (EqualStr(attr[i], "dynamics"))
            reader->fSound->setDynamics(atoi(attr[i+1]));
        else if (EqualStr(attr[i], "dacapo")) 
            reader->fSound->setDacapo(YesNo::xml(attr[i+1]));
        else if (EqualStr(attr[i], "segno")) 
            reader->fSound->setSegno(atoi(attr[i+1]));
        else if (EqualStr(attr[i], "dalsegno")) 
            reader->fSound->setDalsegno(atoi(attr[i+1]));
        else if (EqualStr(attr[i], "coda")) 
            reader->fSound->setCoda(atoi(attr[i+1]));
        else if (EqualStr(attr[i], "tocoda")) 
            reader->fSound->setTocoda(atoi(attr[i+1]));
        else if (EqualStr(attr[i], "divisions")) 
            reader->fSound->setDivisions(atoi(attr[i+1]));
        else if (EqualStr(attr[i], "forward-repeat")) 
            reader->fSound->setForwardRepeat(YesNo::xml(attr[i+1]));
        else if (EqualStr(attr[i], "fine")) 
            reader->fSound->setFine(atoi(attr[i+1]));
        else if (EqualStr(attr[i], "pizzicato")) 
            reader->fSound->setPizzicato(YesNo::xml(attr[i+1]));
/*
        else if (EqualStr(attr[i], "midi-channel")) 
            reader->fSound->setMidiChannel(atoi(attr[i+1]));
        else if (EqualStr(attr[i], "midi-instrument")) 
            reader->fSound->setMidiIntrument(atoi(attr[i+1]));
*/
    }
}

void TMusicXMLReader::EndSound(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndSound\n"));
    if (reader->fDirection) { // parsing a "direction" element
        reader->fDirection->sound() = reader->fSound;
    }else {
        addMusicData(reader, reader->fSound); // parsing a autonomous "sound" element
    }
    reader->fSound = 0;
}

// note
void TMusicXMLReader::StartNote(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartNote\n"));
    assert(reader->fNote == 0);
    reader->fNote = newNote();
    reader->fNote->graphics() = newGraphNote();  // toujours crée  A VERIFIER
    reader->fNote->setStyle(TNote::normal);
    reader->fNote->setType(TNote::pitched);
	reader->fInChord = false;
    
    SExpression expression = newExpression();
    bool flag = false;
    
    for (int i=0; attr[i]; i+=2)
    {
        DBUG(("attr[i] %s %s\n", attr[i], attr[i+1]));
        if (EqualStr(attr[i], "dynamics")) 
            {flag = true; expression->setDynamic(atoi(attr[i+1]));}
        else if (EqualStr(attr[i], "end-dynamics")) 
            {flag = true; expression->setEndDynamic(atoi(attr[i+1]));}
        else if (EqualStr(attr[i], "attack")) 
            {flag = true; expression->setAttack(atoi(attr[i+1]));}
        else if (EqualStr(attr[i], "release")) 
            {flag = true; expression->setRelease(atoi(attr[i+1]));}
        else if (EqualStr(attr[i], "pizzicato")) 
            {flag = true; expression->setPizzicato(YesNo::xml(attr[i+1]));}
		else if (EqualStr(attr[i], "print-object")) 
             reader->fNote->graphics()->printout().setPrintObject(YesNo::xml(attr[i+1]));
		else if (EqualStr(attr[i], "print-dot")) 
             reader->fNote->graphics()->printout().setPrintDot(YesNo::xml(attr[i+1]));
		else if (EqualStr(attr[i], "print-spacing")) 
             reader->fNote->graphics()->printout().setPrintSpacing(YesNo::xml(attr[i+1]));
		else{
            reader->fNote->position().set(TPosition::xmlpos(attr[i]), atoi(attr[i+1]));
            if (TPosition::xmlpos(attr[i]) == 0) DBUG(("StartNote %s\n",attr[i]));
        }
    }
    
    if (flag) reader->fNote->expression() = expression;
}
    
// cue
void TMusicXMLReader::EndCueNote(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("StartCueNote\n"));
    assert(reader->fNote);
    reader->fNote->setStyle(TNote::cue);
}

// grace
void TMusicXMLReader::StartGraceNote(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartGraceNote\n"));
    assert(reader->fNote);
    reader->fNote->setStyle(TNote::grace);
    SGraceNote gracenote = newGraceNote();
                
    for (int i=0; attr[i]; i+=2)
    {
        DBUG(("attr[i] %s %s\n", attr[i], attr[i+1]));
        if (EqualStr(attr[i], "steal-time-previous")) 
            gracenote->setStealPrevious(atoi(attr[i+1]));
        else if (EqualStr(attr[i], "steal-time-following")) 
            gracenote->setStealFollowing(atoi(attr[i+1]));
        else if (EqualStr(attr[i], "make-time")) 
            gracenote->setMakeTime(atoi(attr[i+1]));
        else if (EqualStr(attr[i], "slash")) 
            gracenote->setSlash(YesNo::xml(attr[i+1]));
    }
    
    reader->fNote->graceNote() = gracenote;
}

void TMusicXMLReader::EndNote(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndNote\n"));
	if (reader->fInChord) {
		assert((TChord*)reader->fChord != 0);
		reader->fChord->add(reader->fNote);
	}
    else {
		reader->fChord = 0;
		reader->fLastNoteIndex = addMusicData(reader, reader->fNote);
    }
	reader->fNote = 0;
}

// instrument
void TMusicXMLReader::StartInstrument(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartInstrument\n"));
    assert(attr[0]);
    reader->fNote->setInstrumentID(attr[1]);
}

// chord
void TMusicXMLReader::EndChord(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndChord\n"));
	if (!reader->fChord) {
		assert(reader->fLastNoteIndex>=0);
		reader->fChord = newChord();
		SNote last;
		SMusicData& md = getMusicData(reader, reader->fLastNoteIndex);
//		last = dynamic_cast<SNote*>((TMusicData *)md);
		last.cast((TMusicData *)md);
		reader->fChord->add(last);
		reader->setMusicData(reader, reader->fChord, reader->fLastNoteIndex);
    }
	reader->fInChord = true;
}

// pitch
void TMusicXMLReader::StartPitch(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartPitch\n"));
    assert(reader->fNote);
    reader->fNote->pitch() = newPitch();
}

// step
void TMusicXMLReader::EndStep(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndStep\n"));
    assert(reader->fNote->pitch());
    reader->fNote->pitch()->setStep(TPitch::xmlpitch(reader->GetDataString()));
}

// alter
void TMusicXMLReader::EndAlter(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndAlter\n"));
    assert(reader->fNote->pitch());
    reader->fNote->pitch()->setAlter(reader->GetDataFloat());
}

// octave
void TMusicXMLReader::EndOctave(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndOctave\n"));
    assert(reader->fNote->pitch());
    reader->fNote->pitch()->setOctave(reader->GetDataLong());
}

// unpitched
void TMusicXMLReader::StartUnpitched(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartUnpitched\n"));
    assert(reader->fNote);
    reader->fNote->pitch() = newUnpitched();
    reader->fNote->setType(TNote::unpitched);
}

void TMusicXMLReader::EndUnpitched(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndUnPitched\n"));
    assert(reader->fNote);
    if (reader->fNote->pitch() == 0) { // there was only the end tag
        reader->fNote->pitch() = newUnpitched();
		reader->fNote->setType(TNote::unpitched);
	}
}

// rest
void TMusicXMLReader::StartRest(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartRest\n"));
    assert(reader->fNote);
    reader->fNote->pitch() = newRest();
    reader->fNote->setType(TNote::rest);
}

void TMusicXMLReader::EndRest(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndRest\n"));
    assert(reader->fNote);
    if (reader->fNote->pitch() == 0) { // there was only the end tag
        reader->fNote->pitch() = newRest();
	    reader->fNote->setType(TNote::rest);
	}
}

// tie
void TMusicXMLReader::StartTie(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartTie\n"));
    DBUG(("attr[0] %s %s\n", attr[0], attr[1]));
    
    if (EqualStr(attr[0], "type")){ 
        if (EqualStr((attr[1]), "start")){
            assert(reader->fNote);
            // check that is no pending not at the same pitch
            assert(reader->fPitchTable[reader->fNote->pitch()->MIDIPitch()] == 0); 
            reader->fPitchTable[reader->fNote->pitch()->MIDIPitch()] = reader->fNote;
        }else if (EqualStr((attr[1]), "stop")){
            assert(reader->fNote);
            SNote previous = reader->fPitchTable[reader->fNote->pitch()->MIDIPitch()];
            // check that is a pending note at the same pitch
            assert(previous);  
            previous->tieNext() = reader->fNote; 
            reader->fNote->tiePrevious() = previous;
            reader->fPitchTable[reader->fNote->pitch()->MIDIPitch()] = 0;
        }
    }
}

// display-step
void TMusicXMLReader::EndDisplayStep(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndDisplayStep %ld\n",TPitch::xmlpitch(reader->GetDataString())));
    assert(reader->fNote->pitch());
    reader->fNote->pitch()->setStep(TPitch::xmlpitch(reader->GetDataString()));
}

// display-octave
void TMusicXMLReader::EndDisplayOctave(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndDisplayOctave %ld\n",reader->GetDataLong()));
    assert(reader->fNote->pitch());
    reader->fNote->pitch()->setOctave(reader->GetDataLong());
}

// type
void TMusicXMLReader::StartType(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StarType\n"));
    assert(reader->fNote->graphics());
        
    for (int i=0; attr[i]; i+=2)
    {
        DBUG(("attr[i] %s %s\n", attr[i], attr[i+1]));
    }
    
    if (attr[0]) 
		reader->fNote->graphics()->setSize(FullCue::xml(attr[1]));
}
    
void TMusicXMLReader::EndType(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndType\n"));
    assert(reader->fNote->graphics());
    reader->fNote->graphics()->setType(NoteType::xml(reader->GetDataString()));
}

// dot
void TMusicXMLReader::EndDot(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndDot\n"));
    assert(reader->fNote->graphics());
    reader->fNote->graphics()->setDots(reader->fNote->graphics()->getDots()+1);
}

// stem
void TMusicXMLReader::EndStem(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndStem\n"));
    assert(reader->fNote->graphics());
    reader->fNote->graphics()->setStem(TGraphNote::xmlstem(reader->GetDataString()));
}

// accidental
void TMusicXMLReader::StartAccidental(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartAccidental\n"));
    assert(reader->fNote->graphics());
    SAccidental accidental = newAccidental();
        
    for (int i=0; attr[i]; i+=2)
    {
        DBUG(("attr[i] %s %s\n", attr[i], attr[i+1]));
        if (EqualStr(attr[i], "cautionary")) 
            accidental->setCautionary(YesNo::xml(attr[i+1]));
        else if (EqualStr(attr[i], "editorial")) 
            accidental->setEditorial(YesNo::xml(attr[i+1]));
        else if (EqualStr(attr[i], "size")) 
            accidental->setSize(FullCue::xml(attr[i+1]));
    }
    
    reader->fNote->graphics()->accidental() = accidental;
}

void TMusicXMLReader::EndAccidental(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndAccidental\n"));
    assert(reader->fNote->graphics()->accidental());
    reader->fNote->graphics()->accidental()->setAccident(
	TAccidental::xmlaccidental(reader->GetDataString()));
}

// time-modification
void TMusicXMLReader::StartTimeModification(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartTimeModification\n"));
    assert(reader->fNote->graphics());
    reader->fNote->graphics()->timemodification() = newTimeModification();
}

// actual-notes
void TMusicXMLReader::EndActualNotes(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndActualNotes\n"));
    assert(reader->fNote->graphics()->timemodification());
    reader->fNote->graphics()->timemodification()->setActualNotes(reader->GetDataLong());
}

// normal-notes
void TMusicXMLReader::EndNormalNotes(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndNormalNotes\n"));
    assert(reader->fNote->graphics()->timemodification());
    reader->fNote->graphics()->timemodification()->setNormalNotes(reader->GetDataLong());
}

// normal-type
void TMusicXMLReader::EndNormalType(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndNormalType\n"));
    assert(reader->fNote->graphics()->timemodification());
    reader->fNote->graphics()->timemodification()->setNormalType(NoteType::xml(reader->GetDataString()));
}

// normal-dots
void TMusicXMLReader::EndNormalDots(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndNormalDots\n"));
    assert(reader->fNote->graphics()->timemodification());
    reader->fNote->graphics()->timemodification()->setNormalDots(
    reader->fNote->graphics()->timemodification()->getNormalDots()+1);
}

// notehead
void TMusicXMLReader::StartNoteHead(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartNoteHead\n"));
    assert(reader->fNote->graphics());
    SNoteHead notehead = newNoteHead();
        
    for (int i=0; attr[i]; i+=2)
    {
        DBUG(("attr[i] %s %s\n", attr[i], attr[i+1]));
        if (EqualStr(attr[i], "filled")) 
            notehead->setFilled(YesNo::xml(attr[i+1]));
        else if (EqualStr(attr[i], "parentheses")) 
            notehead->setParentheses(YesNo::xml(attr[i+1]));
    }
    
    reader->fNote->graphics()->notehead() = notehead;
}

void TMusicXMLReader::EndNoteHead(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndNoteHead\n"));
    assert(reader->fNote->graphics()->notehead());
    reader->fNote->graphics()->notehead()->setShape(
	TNoteHead::xmlnotehead(reader->GetDataString()));
}

// beam
void TMusicXMLReader::StartBeam(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartBeam\n"));
    assert(reader->fNote->graphics());
    assert(reader->fBeam == 0);
    
    reader->fBeam = newBeam();
        
    for (int i=0; attr[i]; i+=2)
    {
        DBUG(("attr[i] %s %s\n", attr[i], attr[i+1]));
        if (EqualStr(attr[i], "number")) 
            reader->fBeam->setNumber(atoi(attr[i+1]));
        else if (EqualStr(attr[i], "repeater")) 
            reader->fBeam->setRepeater(YesNo::xml(attr[i+1]));
    }
}
    
void TMusicXMLReader::EndBeam(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndBeam\n"));
    assert(reader->fBeam);
    //printf("EndBeam reader->GetDataString() %s\n",reader->GetDataString().c_str());
    reader->fBeam->setType(TBeam::xmlbeamtype(reader->GetDataString()));
    reader->fNote->graphics()->add(reader->fBeam);
    reader->fBeam = 0;
}

// notations
void TMusicXMLReader::StartNotations(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartNotations\n"));
    assert(reader->fNotation == 0);
    reader->fNotation = newNotation();

	/*  ????
    for (int i=0; attr[i]; i+=2)
    {
        DBUG(("attr[i] %s %s\n", attr[i], attr[i+1]));
        if (EqualStr(attr[i], "number")) 
            reader->fBeam->setNumber(atoi(attr[i+1]));
        else if (EqualStr(attr[i], "repeater")) 
            reader->fBeam->setRepeater(YesNo::xml(attr[i+1]));
    }
	*/
}

void TMusicXMLReader::EndNotations(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndNotations\n"));
    assert(reader->fNotation);
    reader->fNote->graphics()->add(reader->fNotation);
    reader->fNotation = 0;
}

// tied
void TMusicXMLReader::StartTied(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartTied\n"));
    assert(reader->fTieSlur == 0);
	reader->fTieSlur = newTie();
    
    for (int i=0; attr[i]; i+=2)
    {
        DBUG(("attr[i] %s %s\n", attr[i], attr[i+1]));
        if (EqualStr(attr[i], "type")) 
            reader->fTieSlur->setType(StartStop::xml(attr[i+1]));
        else if (EqualStr(attr[i], "number")) 
            reader->fTieSlur->setNumber(atoi(attr[i+1]));
        else if (EqualStr(attr[i], "line-type")) 
            reader->fTieSlur->setLineType(LineType::xml(attr[i+1]));
        else if (EqualStr(attr[i], "placement"))      
            reader->fTieSlur->placement().set(TPlacement::xmlplace(attr[i+1]));
        else if (EqualStr(attr[i], "orientation"))      
            reader->fTieSlur->orientation().set(TOrientation::xmlorientation(attr[i+1]));
        else {
            reader->fTieSlur->position().set(TPosition::xmlpos(attr[i]), atoi(attr[i+1]));
            if (TPosition::xmlpos(attr[i]) == 0) DBUG(("StartTied %s\n",attr[i]));
        }
    }

	assert(reader->fTieSlur->getType() != StartStop::undefined);
}

void TMusicXMLReader::EndTiedSlur(TMusicXMLReader* reader, const char* tag)  // the same method is use for
{
    DBUG(("EndTiedSlur\n"));
    assert(reader->fNotation);
    assert(reader->fTieSlur);
    reader->fNotation->add(reader->fTieSlur);
    reader->fTieSlur = 0;
}

// slur
void TMusicXMLReader::StartSlur(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartSlur\n"));
    assert(reader->fTieSlur == 0);
	reader->fTieSlur = newSlur();
    
    for (int i=0; attr[i]; i+=2)
    {
        DBUG(("attr[i] %s %s\n", attr[i], attr[i+1]));
        if (EqualStr(attr[i], "type")) 
			reader->fTieSlur->setType(StartStop::xml(attr[i+1]));
        else if (EqualStr(attr[i], "number")) 
            reader->fTieSlur->setNumber(atoi(attr[i+1]));
        else if (EqualStr(attr[i], "line-type")) 
            reader->fTieSlur->setLineType(LineType::xml(attr[i+1]));
        else if (EqualStr(attr[i], "placement"))      
            reader->fTieSlur->placement().set(TPlacement::xmlplace(attr[i+1]));
		else if (EqualStr(attr[i], "orientation"))      
            reader->fTieSlur->orientation().set(TOrientation::xmlorientation(attr[i+1]));
		else {
            reader->fTieSlur->position().set(TPosition::xmlpos(attr[i]), atoi(attr[i+1]));
            if (TPosition::xmlpos(attr[i]) == 0) DBUG(("StartSlur %s\n",attr[i]));
        }
    }

	assert(reader->fTieSlur->getType() != StartStop::undefined);
}

// tuplet
void TMusicXMLReader::StartTuplet(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartTuplet\n"));
    assert(reader->fTuplet == 0);
	reader->fTuplet = newTuplet();
    
    for (int i=0; attr[i]; i+=2)
    {
        DBUG(("attr[i] %s %s\n", attr[i], attr[i+1]));
        if (EqualStr(attr[i], "type")) 
			reader->fTuplet->setType(StartStop::xml(attr[i+1]));
        else if (EqualStr(attr[i], "number")) 
            reader->fTuplet->setNumber(atoi(attr[i+1]));
        else if (EqualStr(attr[i], "bracket")) 
            reader->fTuplet->setBracket(YesNo::xml(attr[i+1]));
        else if (EqualStr(attr[i], "show-number")) 
            reader->fTuplet->setShowNum(TTuplet::xmlshow(attr[i+1]));
        else if (EqualStr(attr[i], "show-type")) 
            reader->fTuplet->setShowType(TTuplet::xmlshow(attr[i+1]));
        else if (EqualStr(attr[i], "placement"))      
            reader->fTuplet->placement().set(TPlacement::xmlplace(attr[i+1]));
        else {
            reader->fTuplet->position().set(TPosition::xmlpos(attr[i]), atoi(attr[i+1]));
            if (TPosition::xmlpos(attr[i]) == 0) DBUG(("StartTuplet %s\n",attr[i]));
        }
    }

	assert( reader->fTuplet->getType() != StartStop::undefined);
}

void TMusicXMLReader::EndTuplet(TMusicXMLReader* reader, const char* tag)  // the same method is use for
{
    DBUG(("EndTuplet\n"));
    assert(reader->fNotation);
    assert(reader->fTuplet);
    reader->fNotation->add(reader->fTuplet);
    reader->fTuplet = 0;        
}

// tuplet-normal
void TMusicXMLReader::StartTupletNormal(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartTupletNormal\n"));
    assert(reader->fTuplet);
    reader->fTuplet->normalDesc() = newTupletNormal();
}

// tuplet-actual
void TMusicXMLReader::StartTupletActual(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartTupletNormal\n"));
    assert(reader->fTuplet);
    reader->fTuplet->normalDesc() = newTupletActual();
}

// tuplet-type
void TMusicXMLReader::EndTupletType(TMusicXMLReader* reader, const char* tag)  // the same method is use for normal and actual
{
    DBUG(("EndTupletType\n"));
    assert(reader->fTuplet->normalDesc());
    reader->fTuplet->normalDesc()->setType(reader->GetDataLong());
}

// tuplet-number
void TMusicXMLReader::EndTupletNumber(TMusicXMLReader* reader, const char* tag)  // the same method is use for normal and actual
{
    DBUG(("EndTupletNumber\n"));
    assert(reader->fTuplet->normalDesc());
    reader->fTuplet->normalDesc()->setNumber(reader->GetDataLong());
}

// tuplet-dot
void TMusicXMLReader::EndTupletDot(TMusicXMLReader* reader, const char* tag)  // the same method is use for normal and actual
{
    DBUG(("EndTupletDot\n"));
    assert(reader->fTuplet->normalDesc());
    reader->fTuplet->normalDesc()->setDots(reader->GetDataLong());
}

// articulations
void TMusicXMLReader::StartArticulations(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartArticulations\n"));
    assert(reader->fArticulations == 0);
    reader->fArticulations = newArticulations();
}

void TMusicXMLReader::EndArticulations(TMusicXMLReader* reader, const char* tag)  
{
    DBUG(("EndArticulations\n"));
    assert(reader->fArticulations);
    reader->fNotation->add(reader->fArticulations);
    reader->fArticulations = 0;
}

//  accent | strong-accent | staccato | tenuto |
//  detached-legato | staccatissimo | spiccato |
//  scoop | plop | doit | falloff | breath-mark | 
//  caesura | other-articulation

void TMusicXMLReader::StartArticulationsElement(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartArticulationsElement\n"));
    assert(reader->fArticulationsElement == 0);
    reader->fArticulationsElement = newArticulationElement(TArticulationElement::xmlname(tag));
    
    for (int i=0; attr[i]; i+=2)
    {
        DBUG(("attr[i] %s %s\n", attr[i], attr[i+1]));
        if (EqualStr(attr[i], "placement")) 
            reader->fArticulationsElement->placement().set(TPlacement::xmlplace(attr[i+1]));
        else {
            reader->fArticulationsElement->position().set(TPosition::xmlpos(attr[i]), atoi(attr[i+1]));
            if (TPosition::xmlpos(attr[i]) == 0) DBUG(("StartArticulationsElement %s\n",attr[i]));
        }
    }
}

void TMusicXMLReader::EndArticulationsElement(TMusicXMLReader* reader, const char* tag)  // the same method is use for all
{
    DBUG(("EndArticulationsElement\n"));
    assert(reader->fArticulations);
    if (reader->fArticulationsElement) { // articulation element with an attribute
        reader->fArticulations->add(reader->fArticulationsElement);
        reader->fArticulationsElement = 0;
    }else{
        reader->fArticulations->add(newArticulationElement(TArticulationElement::xmlname(tag)));
    }
}

// strong-accent
void TMusicXMLReader::StartStrongAccent(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartStrongAccent\n"));
    assert(reader->fArticulations);
    SStrongAccent strongaccent = newStrongAccent();
    
    for (int i=0; attr[i]; i+=2)
    {
        DBUG(("attr[i] %s %s\n", attr[i], attr[i+1]));
        if (EqualStr(attr[i], "type")) 
            strongaccent->setType(TStrongAccent::xmltype(attr[i+1]));
        else if (EqualStr(attr[i], "placement")) 
            strongaccent->placement().set(TPlacement::xmlplace(attr[i+1]));
    }

    reader->fArticulations->add(strongaccent);
}

// direction
void TMusicXMLReader::StartDirection(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartDirection\n"));
    assert(reader->fDirection == 0);
    reader->fDirection = newDirection();
    if (attr[0]) 
		reader->fDirection->placement().set(TPlacement::xmlplace(attr[1]));
}

void TMusicXMLReader::EndDirection(TMusicXMLReader* reader, const char* tag)  
{
    DBUG(("EndDirection\n"));
    assert(reader->fDirection);
    addMusicData(reader, reader->fDirection);
    reader->fDirection = 0;
}

// offset
void TMusicXMLReader::EndOffset(TMusicXMLReader* reader, const char* tag)  
{
    DBUG(("EndOffset\n"));
    assert(reader->fDirection);
    reader->fDirection->setOffset(reader->GetDataLong());
}

// direction-type
void TMusicXMLReader::StartDirectionType(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartDirectionType\n"));
    assert(reader->fDirection);
    assert(reader->fDirectionType == 0);
    reader->fDirectionType = newDirectionType();
}

void TMusicXMLReader::EndDirectionType(TMusicXMLReader* reader, const char* tag)  
{
    DBUG(("EndDirectionType\n"));
    assert(reader->fDirection);
    assert(reader->fDirectionType);
    reader->fDirection->add(reader->fDirectionType);
    reader->fDirectionType = 0;
}

// octave-shift
void TMusicXMLReader::StartOctaveShift(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartOctaveShift\n"));
    assert(reader->fDirectionTypeElement == 0);
    SOctaveShift octaveshift = newOctaveShift();
    
    for (int i=0; attr[i]; i+=2)
    {
        DBUG(("attr[i] %s %s\n", attr[i], attr[i+1]));
        if (EqualStr(attr[i], "type"))  
			octaveshift->setType(TOctaveShift::xmltype(attr[i+1]));
        else if (EqualStr(attr[i], "number")) 
            octaveshift->setNumber(atoi(attr[i+1]));
        else if (EqualStr(attr[i], "size")) 
            octaveshift->setSize(atoi(attr[i+1]));
        else{
            octaveshift->position().set(TPosition::xmlpos(attr[i]), atoi(attr[i+1]));
            if (TPosition::xmlpos(attr[i]) == 0) DBUG(("StartOctaveShift %s\n",attr[i]));
        }
    }
	assert(octaveshift->getType() != TOctaveShift::undefined);
    reader->fDirectionTypeElement = octaveshift;
}

// used for all DirectionTypeElement excepts "words" and "dynamic"
void TMusicXMLReader::EndDirectionTypeElement(TMusicXMLReader* reader, const char* tag)           
{
    DBUG(("EndDirectionTypeElement\n"));
    assert(reader->fDirectionTypeElement);
    assert(reader->fDirectionType);
    reader->fDirectionType->add(reader->fDirectionTypeElement);
    reader->fDirectionTypeElement = 0;
}

// bracket
void TMusicXMLReader::StartBracket(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartBracket\n"));
    assert(reader->fDirectionTypeElement == 0);
    SBracket bracket = newBracket();
    
    for (int i=0; attr[i]; i+=2)
    {
        DBUG(("attr[i] %s %s\n", attr[i], attr[i+1]));
        if (EqualStr(attr[i], "type"))  
			bracket->setType(StartStop::xml(attr[i+1]));
        else if (EqualStr(attr[i], "number"))
            bracket->setNumber(atoi(attr[i+1]));
        else if (EqualStr(attr[i], "line-end"))
            bracket->setLineEnd(TBracket::xmllineend(attr[i+1]));
        else if (EqualStr(attr[i], "line-type")) 
            bracket->setLineEnd(LineType::xml(attr[i+1]));
        else{ 
            bracket->position().set(TPosition::xmlpos(attr[i]), atoi(attr[i+1]));
            if (TPosition::xmlpos(attr[i]) == 0) DBUG(("StartBracket %s\n",attr[i]));
        }
    }
	assert(bracket->getType() != StartStop::undefined);
    reader->fDirectionTypeElement = bracket;
}

// dashes
void TMusicXMLReader::StartDashes(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartDashes\n"));
    assert(reader->fDirectionTypeElement == 0);
    SDashes dashes = newDashes();
    
    for (int i=0; attr[i]; i+=2)
    {
        DBUG(("attr[i] %s %s\n", attr[i], attr[i+1]));
        if (EqualStr(attr[i], "type")) 
            dashes->setType(StartStop::xml(attr[i+1]));
        else if (EqualStr(attr[i], "number")) 
            dashes->setNumber(atoi(attr[i+1]));
        else{ 
            dashes->position().set(TPosition::xmlpos(attr[i]), atoi(attr[i+1]));
            if (TPosition::xmlpos(attr[i]) == 0) DBUG(("StartDashes %s\n",attr[i]));
        }
    }
    
	assert(dashes->getType() != StartStop::undefined);
    reader->fDirectionTypeElement = dashes;
}

// words
void TMusicXMLReader::StartWords(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartWords\n"));
    assert(reader->fDirectionTypeElement == 0);
    
    SWords words = newWords();
    
    for (int i=0; attr[i]; i+=2)
    {
        DBUG(("attr[i] %s %s\n", attr[i], attr[i+1]));
        if (EqualStr(attr[i], "justify"))
            words->setJustify(TWords::xmljustify(attr[i+1]));
        else if (EqualStr(attr[i], "xml:lang")) 
            words->setLang(attr[i+1]);
		else if (EqualStr(attr[i], "font-family")) 
            words->font().setFamily(attr[i+1]);
		else if (EqualStr(attr[i], "font-style")) 
            words->font().setStyle(attr[i+1]);
		else if (EqualStr(attr[i], "font-size")) 
            words->font().setSize(attr[i+1]);
		else if (EqualStr(attr[i], "font-weight")) 
            words->font().setWeight(attr[i+1]);
        else {
            words->position().set(TPosition::xmlpos(attr[i]), atoi(attr[i+1]));
            if (TPosition::xmlpos(attr[i]) == 0) DBUG(("StartWords %s\n",attr[i]));
        }
    }
    
    reader->fDirectionTypeElement = words;
}

void TMusicXMLReader::EndWords(TMusicXMLReader* reader, const char* tag)   
{
    DBUG(("EndWords\n"));
    assert(reader->fDirectionTypeElement);
    assert(reader->fDirectionType);
    
    SWords words = dynamic_cast<TWords*>((TDirectionTypeElement*)reader->fDirectionTypeElement);
    assert(words);
    words->setValue(reader->GetDataString());
        
    //((SWords)reader->fDirectionTypeElement)->setValue(reader->GetDataString());
    reader->fDirectionType->add(reader->fDirectionTypeElement);
    reader->fDirectionTypeElement = 0;
}

// wedge
void TMusicXMLReader::StartWedge(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartWedge\n"));
    assert(reader->fDirectionTypeElement == 0);
    SWedge wedge = newWedge();
    
    for (int i=0; attr[i]; i+=2)
    {
        DBUG(("attr[i] %s %s\n", attr[i], attr[i+1]));
        if (EqualStr(attr[i], "type")) 
			wedge->setType(TWedge::xmltype(attr[i+1]));
        else if (EqualStr(attr[i], "number")) 
            wedge->setNumber(atoi(attr[i+1]));
        else if (EqualStr(attr[i], "spread")) 
            wedge->setSpread(atoi(attr[i+1]));
        else {
            wedge->position().set(TPosition::xmlpos(attr[i]), atoi(attr[i+1]));
            if (TPosition::xmlpos(attr[i]) == 0) DBUG(("StartWedge %s\n",attr[i]));
        }
    }
	assert(wedge->getType() != TWedge::undefined);
    reader->fDirectionTypeElement = wedge;
}

// dynamics
void TMusicXMLReader::StartDynamics(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartDynamics\n"));
    assert(reader->fDynamic == 0);
    reader->fDynamic = newDynamic();

    for (int i=0; attr[i]; i+=2)
    {
        DBUG(("attr[i] %s %s\n", attr[i], attr[i+1]));
        if (EqualStr(attr[i], "placement")) 
            reader->fDynamic->placement().set(TPlacement::xmlplace(attr[i+1]));
        else {
            reader->fDynamic->position().set(TPosition::xmlpos(attr[i]), atoi(attr[i+1]));
            if (TPosition::xmlpos(attr[i]) == 0) DBUG(("StartDynamics %s\n",attr[i]));
        }
    }
}

void TMusicXMLReader::EndDynamics(TMusicXMLReader* reader, const char* tag)  
{
    DBUG(("EndDynamics\n"));
    assert(reader->fDynamic);
    
    if (reader->fDirectionType) { // parsing a "direction-type" element
		assert(reader->fDirectionType);
		reader->fDirectionType->add(reader->fDynamic);
    }else{
		assert(reader->fNotation);
		reader->fNotation->add(reader->fDynamic); // parsing a "notation" element
    }
    
    reader->fDynamic = 0;
}

void TMusicXMLReader::EndDynamicElement(TMusicXMLReader* reader, const char* tag)   
{
    DBUG(("EndDynamicElement\n"));
    assert(reader->fDynamic);
    reader->fDynamic->add(TDynamic::xmldynamic(tag));
}

// metronome
void TMusicXMLReader::StartMetronome(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    assert(reader->fDirectionTypeElement == 0);
    SMetronome metronome = newMetronome();
    
    for (int i=0; attr[i]; i+=2)
    {
        DBUG(("attr[i] %s %s\n", attr[i], attr[i+1]));
        if (EqualStr(attr[i], "parentheses")) 
            metronome->setParentheses(YesNo::xml(attr[i+1]));
        else {
            metronome->position().set(TPosition::xmlpos(attr[i]), atoi(attr[i+1]));
            if (TPosition::xmlpos(attr[i]) == 0) DBUG(("StartMetronome %s\n",attr[i]));
        }
    }
    
    reader->fDirectionTypeElement = metronome;        
}

// beat-unit
void TMusicXMLReader::EndBeatUnit(TMusicXMLReader* reader, const char* tag)   
{
    DBUG(("EndBeatUnit\n"));
    assert(reader->fDirectionTypeElement);
    SMetronome metronome = dynamic_cast<TMetronome*>((TDirectionTypeElement*)reader->fDirectionTypeElement);
    assert(metronome);
    if (metronome->getBeat() == NoteType::undefined) { // first beat-unit
        metronome->setBeat(NoteType::xml(reader->GetDataString()));
    }else{ // second beat-unit
        metronome->equal() = newSymbolicNoteDuration(); 
        metronome->equal()->setBeat(NoteType::xml(reader->GetDataString()));
    }
}

// beat-unit-dot
void TMusicXMLReader::EndBeatUnitDot(TMusicXMLReader* reader, const char* tag)   
{
    DBUG(("EndBeatUnitDot\n"));
    assert(reader->fDirectionTypeElement);
    SMetronome metronome = dynamic_cast<TMetronome*>((TDirectionTypeElement*)reader->fDirectionTypeElement);
    assert(metronome);
    if (metronome->equal() == 0) { // first beat-unit-dot
        metronome->setDots(metronome->getDots()+1);
    }else{ // second beat-unit-dot
        assert(metronome->equal());
        metronome->equal()->setDots(metronome->equal()->getDots()+1);
    }
}

// per-minute
void TMusicXMLReader::EndPerMinute(TMusicXMLReader* reader, const char* tag)   
{
    DBUG(("EndPerMinute\n"));
    assert(reader->fDirectionTypeElement);
    SMetronome metronome = dynamic_cast<TMetronome*>((TDirectionTypeElement*)reader->fDirectionTypeElement);
    assert(metronome);
    metronome->setPerMinute(reader->GetDataString());
}

// lyric
void TMusicXMLReader::StartLyric(TMusicXMLReader* reader, const char **attr, const char* tag)
{
	DBUG(("StartLyric\n"));
	assert(reader->fLyric == 0);
    reader->fLyric = newLyric();
  
    for (int i=0; attr[i]; i+=2)
    {
        if (EqualStr(attr[i], "number")) 
            reader->fLyric->setNumber(atoi(attr[i+1]));
        else if (EqualStr(attr[i], "name")) 
            reader->fLyric->setName(attr[i+1]);
		else if (EqualStr(attr[i], "font-family")) 
			reader->fLyric->font().setFamily(attr[i+1]);
		else if (EqualStr(attr[i], "font-style")) 
			reader->fLyric->font().setStyle(attr[i+1]);
		else if (EqualStr(attr[i], "font-size")) 
			reader->fLyric->font().setSize(attr[i+1]);
		else if (EqualStr(attr[i], "font-weight")) 
			reader->fLyric->font().setWeight(attr[i+1]);	
    }
}

void TMusicXMLReader::EndLyric(TMusicXMLReader* reader, const char* tag)
{
	DBUG(("EndLyric\n"));
	assert(reader->fLyric);
	assert(reader->fNote);
	reader->fNote->add(reader->fLyric);
	reader->fLyric = 0;
}

// syllabic
void TMusicXMLReader::EndSyllabic(TMusicXMLReader* reader, const char* tag)
{
	DBUG(("syllabic\n"));
	assert(reader->fLyric);
	
	if (!reader->fLyric->getMultipleParts().empty()) { // elision case inserts first object
		if (reader->fMultipleLyricPart == 0)
			reader->fMultipleLyricPart = newMultipleLyricPart();
		reader->fMultipleLyricPart->setSyllabic(TLyric::xmlsyllabic(reader->GetDataString()));
	} else {	
		
		reader->fLyric->setSyllabic(TLyric::xmlsyllabic(reader->GetDataString()));
	}
}

// text
void TMusicXMLReader::EndText(TMusicXMLReader* reader, const char* tag)
{
	DBUG(("text\n"));
	assert(reader->fLyric); //JS
	
	if (!reader->fLyric->getMultipleParts().empty()) { // elision case inserts first object
		
		if (reader->fMultipleLyricPart == 0)
		{
			reader->fMultipleLyricPart = newMultipleLyricPart();
			reader->fLyric->add(reader->fMultipleLyricPart);
		}
		reader->fMultipleLyricPart->setText(reader->GetDataString());
		reader->fMultipleLyricPart = 0; //JS: need to dereference here
		
	} else {	
		//assert(reader->fLyric);
		reader->fLyric->setText(reader->GetDataString());
	}	
}

// extend
void TMusicXMLReader::EndExtend(TMusicXMLReader* reader, const char* tag)
{
	DBUG(("extend\n"));
	assert(reader->fLyric);
	reader->fLyric->setExtend(true);
}

// laughing
void TMusicXMLReader::EndLaughing(TMusicXMLReader* reader, const char* tag)
{
	DBUG(("EndLaughing\n"));
	assert(reader->fLyric);
	reader->fLyric->setLaughing(true);
}

// humming
void TMusicXMLReader::EndHumming(TMusicXMLReader* reader, const char* tag)
{
	DBUG(("humming\n"));
	assert(reader->fLyric);
	reader->fLyric->setHumming(true);
}

// end-line
void TMusicXMLReader::EndEndLine(TMusicXMLReader* reader, const char* tag)
{
	DBUG(("end-line\n"));
	assert(reader->fLyric);
	reader->fLyric->setEndLine(true);
}

// end-paragraph
void TMusicXMLReader::EndEndParagraph(TMusicXMLReader* reader, const char* tag)
{
	DBUG(("end-paragraph\n"));
	assert(reader->fLyric);
	reader->fLyric->setEndParagraph(true);
}

// elision
void TMusicXMLReader::StartElision(TMusicXMLReader* reader, const char **attr, const char* tag)
{
	DBUG(("StartElision\n"));
	assert(reader->fMultipleLyricPart == 0);
    reader->fMultipleLyricPart = newMultipleLyricPart();
	
	for (int i=0; attr[i]; i+=2)
    {
        DBUG(("attr[i] %s %s\n", attr[i], attr[i+1]));
		if (EqualStr(attr[i], "font-family")) 
            reader->fMultipleLyricPart->font().setFamily(attr[i+1]);
		else if (EqualStr(attr[i], "font-style")) 
            reader->fMultipleLyricPart->font().setStyle(attr[i+1]);
		else if (EqualStr(attr[i], "font-size")) 
            reader->fMultipleLyricPart->font().setSize(attr[i+1]);
		else if (EqualStr(attr[i], "font-weight")) 
            reader->fMultipleLyricPart->font().setWeight(attr[i+1]);
	}
}

void TMusicXMLReader::EndElision(TMusicXMLReader* reader, const char* tag)
{
	DBUG(("EndElision\n"));
	assert(reader->fMultipleLyricPart);
	assert(reader->fLyric);
	reader->fLyric->add(reader->fMultipleLyricPart);
	//reader->fMultipleLyricPart = 0; //JS 140606: moved to text handler
}

// glissando
void TMusicXMLReader::StartGlissando(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartGlissando\n"));
    SGlissando glissando = newGlissando();
    
    for (int i=0; attr[i]; i+=2)
    {
		if (EqualStr(attr[i], "type")) 
			glissando->setType(StartStop::xml(attr[i+1]));
        else if (EqualStr(attr[i], "number")) 
            glissando->setNumber(atoi(attr[i+1]));
		else if (EqualStr(attr[i], "line-type")) 
			glissando->setLineType(LineType::xml(attr[i+1]));
		else {
			glissando->position().set(TPosition::xmlpos(attr[i]), atoi(attr[i+1]));
            if (TPosition::xmlpos(attr[i]) == 0) DBUG(("StartGlissando %s\n",attr[i]));
		}
    }
	
	assert(glissando->getType() != StartStop::undefined);
	assert(reader->fNotation);
	reader->fNotation->add(glissando);
}

// slide
void TMusicXMLReader::StartSlide(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartSlide\n"));
    SSlide slide = newSlide();
    
    for (int i=0; attr[i]; i+=2)
    {
		if (EqualStr(attr[i], "type")) 
			slide->setType(StartStop::xml(attr[i+1]));
        else if (EqualStr(attr[i], "number")) 
            slide->setNumber(atoi(attr[i+1]));
		else if (EqualStr(attr[i], "line-type")) 
			slide->setLineType(LineType::xml(attr[i+1]));
		else {
			slide->position().set(TPosition::xmlpos(attr[i]), atoi(attr[i+1]));
            if (TPosition::xmlpos(attr[i]) == 0) DBUG(("StartSlide %s\n",attr[i]));
		}
    }
	
	assert(slide->getType() != StartStop::undefined);
	assert(reader->fNotation);
	reader->fNotation->add(slide);
}

// arpeggiate
void TMusicXMLReader::StartArpeggiate(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartArpeggiate\n"));
    SArpeggiate arpeggiate = newArpeggiate();
    
    for (int i=0; attr[i]; i+=2)
    {
		if (EqualStr(attr[i], "direction")) 
            arpeggiate->setDirection(TArpeggiate::direction(atoi(attr[i+1])));
        else if (EqualStr(attr[i], "number")) 
            arpeggiate->setNumber(atoi(attr[i+1]));
		else {
			arpeggiate->position().set(TPosition::xmlpos(attr[i]), atoi(attr[i+1]));
            if (TPosition::xmlpos(attr[i]) == 0) DBUG(("StartArpeggiate %s\n",attr[i]));
		}
    }

	assert(reader->fNotation);
	reader->fNotation->add(arpeggiate);
}

// non-arpeggiate
void TMusicXMLReader::StartNonArpeggiate(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartNonArpeggiate\n"));
    SNonArpeggiate nonarpeggiate = newNonArpeggiate();
    
    for (int i=0; attr[i]; i+=2)
    {
		if (EqualStr(attr[i], "type")) 
            nonarpeggiate->setType(TNonArpeggiate::type(atoi(attr[i+1])));
        else if (EqualStr(attr[i], "number")) 
            nonarpeggiate->setNumber(atoi(attr[i+1]));
		else {
			nonarpeggiate->position().set(TPosition::xmlpos(attr[i]), atoi(attr[i+1]));
            if (TPosition::xmlpos(attr[i]) == 0) DBUG(("StartNonArpeggiate %s\n",attr[i]));
		}
    }

	assert(reader->fNotation);
	reader->fNotation->add(nonarpeggiate);
}

// other-articulation
void TMusicXMLReader::StartOtherArticulation(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartOtherArticulation\n"));
	assert(reader->fOtherArticulation == 0);
	reader->fOtherArticulation = newOtherArticulation();
    
    for (int i=0; attr[i]; i+=2)
    {
		if (EqualStr(attr[i], "placement")) { 
            reader->fOtherArticulation->placement().set(TPlacement::xmlplace(attr[i+1]));
		}else{
			reader->fOtherArticulation->position().set(TPosition::xmlpos(attr[i]), atoi(attr[i+1]));
			if (TPosition::xmlpos(attr[i]) == 0) DBUG(("StartOtherArticulation %s\n",attr[i]));
		}
	}
}

void TMusicXMLReader::EndOtherArticulation(TMusicXMLReader* reader, const char* tag) 
{
    DBUG(("EndOtherArticulation\n"));
	assert(reader->fArticulations);
    assert(reader->fOtherArticulation);
   	reader->fOtherArticulation->setData(reader->GetDataString());
	reader->fArticulations->add(reader->fOtherArticulation);
	reader->fOtherArticulation = 0;
}

// rehearsal
void TMusicXMLReader::StartRehearsal(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartRehearsal\n"));
	assert(reader->fRehearsal == 0);
	reader->fRehearsal = newRehearsal();
    
    for (int i=0; attr[i]; i+=2)
    {
		if (EqualStr(attr[i], "font-family")) 
			reader->fRehearsal->font().setFamily(attr[i+1]);
		else if (EqualStr(attr[i], "font-style")) 
			reader->fRehearsal->font().setStyle(attr[i+1]);
		else if (EqualStr(attr[i], "font-size")) 
			reader->fRehearsal->font().setSize(attr[i+1]);
		else if (EqualStr(attr[i], "font-weight")) 
			reader->fRehearsal->font().setWeight(attr[i+1]);
		else {	
			reader->fRehearsal->position().set(TPosition::xmlpos(attr[i]), atoi(attr[i+1]));
			if (TPosition::xmlpos(attr[i]) == 0) DBUG(("StartRehearsal %s\n",attr[i]));
		}
	}
}

void TMusicXMLReader::EndRehearsal(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndRehearsal\n"));
    assert(reader->fRehearsal);
    assert(reader->fDirectionType);
	reader->fRehearsal->setData(reader->GetDataString());
    reader->fDirectionType->add(reader->fRehearsal);
    reader->fRehearsal = 0;
}

// pedal
void TMusicXMLReader::StartPedal(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartPedal\n"));
    SPedal pedal = newPedal();
    
    for (int i=0; attr[i]; i+=2)
    {
		if (EqualStr(attr[i], "type")) 
			pedal->setType(StartStop::xml(attr[i+1]));
        else if (EqualStr(attr[i], "line")) 
            pedal->setLine(YesNo::xml(attr[i+1]));
		else {
			pedal->position().set(TPosition::xmlpos(attr[i]), atoi(attr[i+1]));
            if (TPosition::xmlpos(attr[i]) == 0) DBUG(("StartPedal %s\n",attr[i]));
		}
    }

	assert(reader->fDirectionType);
	reader->fDirectionType->add(pedal);
}

// damp,damp-all,eyeglasses
void TMusicXMLReader::StartOtherDirections(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartOtherDirections\n"));
	assert(reader->fOtherDirections == 0);
    reader->fOtherDirections = newOtherDirections(TOtherDirections::damp); // "dummy" type, real type is set in EndOtherDirection
    
    for (int i=0; attr[i]; i+=2)
    {
		reader->fOtherDirections->position().set(TPosition::xmlpos(attr[i]), atoi(attr[i+1]));
		if (TPosition::xmlpos(attr[i]) == 0) DBUG(("StartOtherDirections %s\n",attr[i]));
	}
}

void TMusicXMLReader::EndOtherDirections(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndOtherDirections\n"));
    assert(reader->fOtherDirections);
    assert(reader->fDirectionType);
	reader->fOtherDirections->setType(TOtherDirections::xml(tag));
    reader->fDirectionType->add(reader->fOtherDirection);
    reader->fOtherDirections = 0;
}

// other-direction
void TMusicXMLReader::StartOtherDirection(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartOtherDirection\n"));
	assert(reader->fOtherDirection == 0);
    reader->fOtherDirection = newOtherDirection(); 
    
    for (int i=0; attr[i]; i+=2)
    {
		reader->fOtherDirection->position().set(TPosition::xmlpos(attr[i]), atoi(attr[i+1]));
		if (TPosition::xmlpos(attr[i]) == 0) DBUG(("StartOtherDirection %s\n",attr[i]));
	}
}

void TMusicXMLReader::EndOtherDirection(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndOtherDirection\n"));
    assert(reader->fOtherDirection);
    assert(reader->fDirectionType);
	reader->fOtherDirection->setData(reader->GetDataString());
    reader->fDirectionType->add(reader->fOtherDirection);
    reader->fOtherDirection = 0;
}

// print
void TMusicXMLReader::StartPrint(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartPrint\n"));
	SPrint print = newPrint(); 
    
    for (int i=0; attr[i]; i+=2)
    {
		if (EqualStr(attr[i], "staff-spacing")) 
            print->setStaffSpacing(atoi(attr[i+1]));
        else if (EqualStr(attr[i], "new-system")) 
            print->setNewSystem(YesNo::xml(attr[i+1]));
		else if (EqualStr(attr[i], "new-page")) 
            print->setNewPage(YesNo::xml(attr[i+1]));
	}
	
	addMusicData(reader, print);
}

// technicals
void TMusicXMLReader::StartTechnicals(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartTechnicals\n"));
	assert(reader->fTechnicals == 0);
	reader->fTechnicals = newTechnicals();
}

void TMusicXMLReader::EndTechnicals(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndTechnicals\n"));
    assert(reader->fTechnicals);
    assert(reader->fNotation);
	reader->fNotation->add(reader->fTechnicals);
	reader->fTechnicals = 0;
}

// technical
void TMusicXMLReader::StartTechnical(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartTechnical\n"));
	assert(reader->fTechnical == 0);
	reader->fTechnical = newTechnical(TTechnical::xml(tag));
	
	for (int i=0; attr[i]; i+=2)
    {
        DBUG(("attr[i] %s %s\n", attr[i], attr[i+1]));
        if (EqualStr(attr[i], "placement")) 
            //reader->fArticulationsElement->placement().set(TPlacement::xmlplace(attr[i+1]));
			//changed JS 240606
			reader->fTechnical->placement().set(TPlacement::xmlplace(attr[i+1]));
        else {
            //reader->fArticulationsElement->position().set(TPosition::xmlpos(attr[i]), atoi(attr[i+1]));
			//changed JS 240606
			reader->fTechnical->position().set(TPosition::xmlpos(attr[i]), atoi(attr[i+1]));
			//changed JS 240606
            if (TPosition::xmlpos(attr[i]) == 0) DBUG(("StartTechnical %s\n",attr[i]));
        }
    }
}

void TMusicXMLReader::EndTechnical(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndTechnical\n"));
    assert(reader->fTechnicals);
    assert(reader->fTechnical);
	reader->fTechnicals->add(reader->fTechnical);
	reader->fTechnical = 0;
}

// harmonic
void TMusicXMLReader::StartHarmonic(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartHarmonic\n"));
	assert(reader->fHarmonic == 0);
	reader->fHarmonic = newHarmonic();
	
	for (int i=0; attr[i]; i+=2)
    {
        DBUG(("attr[i] %s %s\n", attr[i], attr[i+1]));
        if (EqualStr(attr[i], "placement")) 
            reader->fHarmonic->placement().set(TPlacement::xmlplace(attr[i+1]));
        else {
            reader->fHarmonic->position().set(TPosition::xmlpos(attr[i]), atoi(attr[i+1]));
            if (TPosition::xmlpos(attr[i]) == 0) DBUG(("StartHarmonic %s\n",attr[i]));
        }
    }
}

void TMusicXMLReader::EndHarmonic(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndHarmonic\n"));
    assert(reader->fTechnicals);
    assert(reader->fHarmonic);
	reader->fTechnicals->add(reader->fHarmonic);
	reader->fHarmonic = 0;
}

void TMusicXMLReader::EndNatural(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndNatural\n"));
    assert(reader->fHarmonic);
	reader->fHarmonic->setHarmonic(THarmonic::xmlHarmonic(reader->GetDataString()));
}

void TMusicXMLReader::EndArtificial(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndArtificial\n"));
    assert(reader->fHarmonic);
	reader->fHarmonic->setHarmonic(THarmonic::xmlHarmonic(reader->GetDataString()));
}

void TMusicXMLReader::EndBasePitch(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndBasePitch\n"));
	assert(reader->fHarmonic);
	reader->fHarmonic->setPitch(THarmonic::xmlPitch(reader->GetDataString()));
}

void TMusicXMLReader::EndTouchingPitch(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndTouchingPitch\n"));
    assert(reader->fHarmonic);
	reader->fHarmonic->setPitch(THarmonic::xmlPitch(reader->GetDataString()));
}

void TMusicXMLReader::EndSoundingPitch(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndSoundingPitch\n"));
    assert(reader->fHarmonic);
	reader->fHarmonic->setPitch(THarmonic::xmlPitch(reader->GetDataString()));
}

// hammer-on
void TMusicXMLReader::StartHammerPull(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartHammerPull\n"));
	assert(reader->fHammerPull == 0);
	reader->fHammerPull = newHammerPull(true);
	
	for (int i=0; attr[i]; i+=2)
    {
        DBUG(("attr[i] %s %s\n", attr[i], attr[i+1]));
		if (EqualStr(attr[i], "type")) 
			reader->fHammerPull->setStartStop(StartStop::xml(attr[i+1]));
		else if (EqualStr(attr[i], "number")) 
             reader->fHammerPull->setNumber(atoi(attr[i+1]));
		else if (EqualStr(attr[i], "font-family")) 
			reader->fHammerPull->font().setFamily(attr[i+1]);
		else if (EqualStr(attr[i], "font-style")) 
			reader->fHammerPull->font().setStyle(attr[i+1]);
		else if (EqualStr(attr[i], "font-size")) 
			reader->fHammerPull->font().setSize(attr[i+1]);
		else if (EqualStr(attr[i], "font-weight")) 
			reader->fHammerPull->font().setWeight(attr[i+1]);
        else if (EqualStr(attr[i], "placement")) 
            reader->fHammerPull->placement().set(TPlacement::xmlplace(attr[i+1]));
        else {
            reader->fHammerPull->position().set(TPosition::xmlpos(attr[i]), atoi(attr[i+1]));
            if (TPosition::xmlpos(attr[i]) == 0) DBUG(("StartHammerPull %s\n",attr[i]));
        }
    }
}

// pull-off
void TMusicXMLReader::StartPullOff(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartPullOff\n"));
	assert(reader->fHammerPull == 0);
	reader->fHammerPull = newHammerPull(false);
	
	for (int i=0; attr[i]; i+=2)
    {
        DBUG(("attr[i] %s %s\n", attr[i], attr[i+1]));
		if (EqualStr(attr[i], "type"))
			reader->fHammerPull->setStartStop(StartStop::xml(attr[i+1]));
		else if (EqualStr(attr[i], "number")) 
             reader->fHammerPull->setNumber(atoi(attr[i+1]));
        else if (EqualStr(attr[i], "placement")) 
            reader->fHammerPull->placement().set(TPlacement::xmlplace(attr[i+1]));
        else {
            reader->fHammerPull->position().set(TPosition::xmlpos(attr[i]), atoi(attr[i+1]));
            if (TPosition::xmlpos(attr[i]) == 0) DBUG(("StartHammerPull %s\n",attr[i]));
        }
    }
}

void TMusicXMLReader::EndHammerPull(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndHammerPull\n"));
    assert(reader->fTechnicals);
    assert(reader->fHammerPull);
	reader->fHammerPull->setData(reader->GetDataString());
	reader->fTechnicals->add(reader->fHammerPull);
	reader->fHammerPull = 0;
}

// fingering
void TMusicXMLReader::StartFingering(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartFingering\n"));
	assert(reader->fFingering == 0);
	reader->fFingering = newFingering();
	
	for (int i=0; attr[i]; i+=2)
    {
        DBUG(("attr[i] %s %s\n", attr[i], attr[i+1]));
		if (EqualStr(attr[i], "substitution")) 
			reader->fFingering->setSubstitution(YesNo::xml(attr[i+1]));
		else if (EqualStr(attr[i], "alternate")) 
			reader->fFingering->setAlternate(YesNo::xml(attr[i+1]));
		else if (EqualStr(attr[i], "font-family")) 
			reader->fFingering->font().setFamily(attr[i+1]);
		else if (EqualStr(attr[i], "font-style")) 
			reader->fFingering->font().setStyle(attr[i+1]);
		else if (EqualStr(attr[i], "font-size")) 
			reader->fFingering->font().setSize(attr[i+1]);
		else if (EqualStr(attr[i], "font-weight")) 
			reader->fFingering->font().setWeight(attr[i+1]);
		else if (EqualStr(attr[i], "placement")) 
            reader->fFingering->placement().set(TPlacement::xmlplace(attr[i+1]));
        else {
            reader->fFingering->position().set(TPosition::xmlpos(attr[i]), atoi(attr[i+1]));
            if (TPosition::xmlpos(attr[i]) == 0) DBUG(("StartFingering %s\n",attr[i]));
        }
    }
}

void TMusicXMLReader::EndFingering(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndFingering\n"));
	if (reader->fFingering) {
		assert(reader->fFrameNote);
		reader->fFingering->setData(reader->GetDataString());
		reader->fFrameNote->fingering() = reader->fFingering;
		reader->fFingering = 0;
	} else {
		assert(reader->fTechnicals);
		assert(reader->fHammerPull);
		reader->fHammerPull->setData(reader->GetDataString());
		reader->fTechnicals->add(reader->fHammerPull);
		reader->fHammerPull = 0;
	}
}

// string
void TMusicXMLReader::EndString(TMusicXMLReader* reader, const char* tag)
{
	DBUG(("EndString\n"));
	if (reader->fTechnical) {
		assert(reader->fTechnicals);
		reader->fTechnical->setData(reader->GetDataString());
		reader->fTechnicals->add(reader->fTechnical);
		reader->fTechnical = 0;
	} else { // frame-note case
		reader->fFrameNote->setString(reader->GetDataString());
	}
 }

// fret
void TMusicXMLReader::EndFret(TMusicXMLReader* reader, const char* tag)
{
	DBUG(("EndFret\n"));
	if (reader->fTechnical) {
		assert(reader->fTechnicals);
		reader->fTechnical->setData(reader->GetDataString());
		reader->fTechnicals->add(reader->fTechnical);
		reader->fTechnical = 0;
	} else { // frame-note case
		reader->fFrameNote->setFret(reader->GetDataString());
	}
}

// bend
void TMusicXMLReader::StartBend(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartBend\n"));
	assert(reader->fBend == 0);
	reader->fBend = newBend();
	
	for (int i=0; attr[i]; i+=2)
    {
        DBUG(("attr[i] %s %s\n", attr[i], attr[i+1]));
		if (EqualStr(attr[i], "accelerate")) 
            reader->fBend->bendSound().setAccelerate(YesNo::xml(attr[i+1]));
		else if (EqualStr(attr[i], "beats")) 
            reader->fBend->bendSound().setBeat(atoi(attr[i+1]));
		else if (EqualStr(attr[i], "first-beat")) 
            reader->fBend->bendSound().setFirstBeat(atoi(attr[i+1]));
		else if (EqualStr(attr[i], "last-beat")) 
            reader->fBend->bendSound().setLastBeat(atoi(attr[i+1]));
		else {
            reader->fBend->position().set(TPosition::xmlpos(attr[i]), atoi(attr[i+1]));
            if (TPosition::xmlpos(attr[i]) == 0) DBUG(("StartBend %s\n",attr[i]));
        }
    }
}

void TMusicXMLReader::EndBend(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndBend\n"));
    assert(reader->fTechnicals);
    assert(reader->fBend);
	reader->fTechnicals->add(reader->fBend);
	reader->fBend = 0;
}

// bend-alter
void TMusicXMLReader::EndBendAlter(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndBendAlter\n"));
    assert(reader->fBend);
	reader->fBend->setAlter(reader->GetDataFloat());
}

// pre-bend
void TMusicXMLReader::EndPreBend(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndBendAlter\n"));
    assert(reader->fBend);
	reader->fBend->setPreBend(true);
}

// release
void TMusicXMLReader::EndRelease(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndRelease\n"));
    assert(reader->fBend);
	reader->fBend->setRelease(true);
}

// with-bar
void TMusicXMLReader::StartBendWithBar(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartBendWithBar\n"));
	assert(reader->fBendWithBar == 0);
	reader->fBendWithBar = newBendWithBar();
	
	for (int i=0; attr[i]; i+=2)
    {
		if (EqualStr(attr[i], "placement")) 
            reader->fBendWithBar->placement().set(TPlacement::xmlplace(attr[i+1]));
        else {
            reader->fBendWithBar->position().set(TPosition::xmlpos(attr[i]), atoi(attr[i+1]));
            if (TPosition::xmlpos(attr[i]) == 0) DBUG(("StartBendWithBar %s\n",attr[i]));
        }
    }
}

void TMusicXMLReader::EndBendWithBar(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndBendWithBar\n"));
	assert(reader->fBend);
    assert(reader->fBendWithBar);
	reader->fBendWithBar->setData(reader->GetDataString());
	reader->fBend->setWithBar(reader->fBendWithBar);
	reader->fBendWithBar = 0;
}


// ornaments
void TMusicXMLReader::StartOrnaments(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartOrnaments\n"));
	assert(reader->fOrnaments == 0);
	reader->fOrnaments = newOrnaments();
}

void TMusicXMLReader::EndOrnaments(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndOrnaments\n"));
	assert(reader->fOrnaments);
	assert(reader->fNotation);
	reader->fNotation->add(reader->fOrnaments);
	reader->fOrnaments = 0;
}

// trill-mark
void TMusicXMLReader::StartTrillMark(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartTrillMark\n"));
	assert(reader->fOrnament == 0);
	assert(tag);
	STrillOrnament ornament = newTrillOrnament(TOrnament::xml(tag));
	reader->fOrnament = ornament;
	
	for (int i=0; attr[i]; i+=2)
    {
		if (EqualStr(attr[i], "start-note")) 
            ornament->trill().setStartNote(TrillStart::xml(attr[i+1]));
		else if (EqualStr(attr[i], "trill-step")) 
            ornament->trill().setTrillStep(TrillStep::xml(attr[i+1]));
		else if (EqualStr(attr[i], "two-note-turn")) 
            ornament->trill().setTwoNoteTurn(TrillStep::xml(attr[i+1]));
		else if (EqualStr(attr[i], "accelerate")) 
            ornament->trill().setAccelerate(YesNo::xml(attr[i+1]));
		else if (EqualStr(attr[i], "beats")) 
            ornament->trill().setBeat(atoi(attr[i+1]));
		else if (EqualStr(attr[i], "second-beat")) 
            ornament->trill().setSecondBeat(atoi(attr[i+1]));
		else if (EqualStr(attr[i], "last-beat")) 
            ornament->trill().setLastBeat(atoi(attr[i+1]));
		else if (EqualStr(attr[i], "placement")) 
            ornament->placement().set(TPlacement::xmlplace(attr[i+1]));
        else {
            ornament->position().set(TPosition::xmlpos(attr[i]), atoi(attr[i+1]));
            if (TPosition::xmlpos(attr[i]) == 0) DBUG(("StartTrillMark %s\n",attr[i]));
        }
    }
}

void TMusicXMLReader::EndOrnament(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndOrnament\n"));
	assert(reader->fOrnaments);
	assert(reader->fOrnament);
	reader->fOrnaments->add(reader->fOrnament);
	reader->fOrnament = 0;
}

// mordent
void TMusicXMLReader::StartMordent(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartMordent\n"));
	assert(reader->fOrnament == 0);
	assert(tag);
	SMordentOrnament ornament = newMordentOrnament(TOrnament::xml(tag));
	reader->fOrnament = ornament;
	
	for (int i=0; attr[i]; i+=2)
    {
		if (EqualStr(attr[i], "start-note")) 
            ornament->setLong(YesNo::xml(attr[i+1]));
		else if (EqualStr(attr[i], "start-note")) 
            ornament->trill().setStartNote(TrillStart::xml(attr[i+1]));
		else if (EqualStr(attr[i], "trill-step")) 
            ornament->trill().setTrillStep(TrillStep::xml(attr[i+1]));
		else if (EqualStr(attr[i], "two-note-turn")) 
            ornament->trill().setTwoNoteTurn(TrillStep::xml(attr[i+1]));
		else if (EqualStr(attr[i], "accelerate")) 
            ornament->trill().setAccelerate(YesNo::xml(attr[i+1]));
		else if (EqualStr(attr[i], "beats")) 
            ornament->trill().setBeat(atoi(attr[i+1]));
		else if (EqualStr(attr[i], "second-beat")) 
            ornament->trill().setSecondBeat(atoi(attr[i+1]));
		else if (EqualStr(attr[i], "last-beat")) 
            ornament->trill().setLastBeat(atoi(attr[i+1]));
		else if (EqualStr(attr[i], "placement")) 
            ornament->placement().set(TPlacement::xmlplace(attr[i+1]));
        else {
            ornament->position().set(TPosition::xmlpos(attr[i]), atoi(attr[i+1]));
            if (TPosition::xmlpos(attr[i]) == 0) DBUG(("StartTrillMark %s\n",attr[i]));
        }
    }
}

// trill-mark
void TMusicXMLReader::StartSchleifer(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartSchleifer\n"));
	assert(reader->fOrnament == 0);
	assert(tag);
	reader->fOrnament = newOrnament(TOrnament::xml(tag));
	
	for (int i=0; attr[i]; i+=2)
    {
		if (EqualStr(attr[i], "placement")) 
            reader->fOrnament->placement().set(TPlacement::xmlplace(attr[i+1]));
        else {
            reader->fOrnament->position().set(TPosition::xmlpos(attr[i]), atoi(attr[i+1]));
            if (TPosition::xmlpos(attr[i]) == 0) DBUG(("StartTrillMark %s\n",attr[i]));
        }
    }
}

// other-ornament
void TMusicXMLReader::StartOtherOrnament(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartOtherOrnament\n"));
	assert(reader->fOrnament == 0);
	SOtherOrnament ornament = newOtherOrnament();
	reader->fOrnament = ornament;
	
	for (int i=0; attr[i]; i+=2)
    {
		if (EqualStr(attr[i], "placement")) 
            reader->fOrnament->placement().set(TPlacement::xmlplace(attr[i+1]));
        else {
            reader->fOrnament->position().set(TPosition::xmlpos(attr[i]), atoi(attr[i+1]));
            if (TPosition::xmlpos(attr[i]) == 0) DBUG(("StartTrillMark %s\n",attr[i]));
        }
    }
}

void TMusicXMLReader::EndOtherOrnament(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndOtherOrnament\n"));
	assert(reader->fOrnaments);
	assert(reader->fOrnament);
	(dynamic_cast<TOtherOrnament*>((TOrnament*)reader->fOrnament))->setData(reader->GetDataString());
	reader->fOrnaments->add(reader->fOrnament);
	reader->fOrnament = 0;
}

// accidental-mark
void TMusicXMLReader::StartAccidentalMark(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartAccidentalMark\n"));
	assert(reader->fAccidentalmark == 0);
	reader->fAccidentalmark = newAccidentalMark();
	
	for (int i=0; attr[i]; i+=2)
    {
		if (EqualStr(attr[i], "placement")) 
            reader->fAccidentalmark->placement().set(TPlacement::xmlplace(attr[i+1]));
        else {
            reader->fAccidentalmark->position().set(TPosition::xmlpos(attr[i]), atoi(attr[i+1]));
            if (TPosition::xmlpos(attr[i]) == 0) DBUG(("StartAccidentalMark %s\n",attr[i]));
        }
    }
}

void TMusicXMLReader::EndAccidentalMark(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndAccidentalMark\n"));
	assert(reader->fAccidentalmark);
	reader->fAccidentalmark->setData(reader->GetDataString());
	if (reader->fOrnaments) {
		// Use the latest ornament
		reader->fOrnaments->getLast()->add(reader->fAccidentalmark);
	} else if (reader->fNotation) {
		reader->fNotation->add(reader->fAccidentalmark);
	} else {
		assert(true); // error
	}
	reader->fAccidentalmark = 0;
}

// figured-bass
void TMusicXMLReader::StartFiguredBass(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartFiguredBass\n"));
	
	assert(reader->fFiguredBass == 0);
	reader->fFiguredBass = newFiguredBass();
	
	for (int i=0; attr[i]; i+=2)
    {
        DBUG(("attr[i] %s %s\n", attr[i], attr[i+1]));
		if (EqualStr(attr[i], "print-object")) 
			reader->fFiguredBass->printout().setPrintObject(YesNo::xml(attr[i+1]));
		else if (EqualStr(attr[i], "print-dot")) 
			reader->fFiguredBass->printout().setPrintDot(YesNo::xml(attr[i+1]));
		else if (EqualStr(attr[i], "print-spacing")) 
			reader->fFiguredBass->printout().setPrintSpacing(YesNo::xml(attr[i+1]));
		else {
			reader->fFiguredBass->position().set(TPosition::xmlpos(attr[i]), atoi(attr[i+1]));
			if (TPosition::xmlpos(attr[i]) == 0) DBUG(("StartFiguredBass %s\n",attr[i]));
		}
    }
}

void TMusicXMLReader::EndFiguredBass(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndFiguredBass\n"));
	assert(reader->fFiguredBass);
	addMusicData(reader, reader->fFiguredBass);
	reader->fFiguredBass = 0;
}

// figure
void TMusicXMLReader::StartFigure(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartFigure\n"));
	
	assert(reader->fFigure == 0);
	reader->fFigure = newFigure();
}

void TMusicXMLReader::EndFigure(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndFigure\n"));
	assert(reader->fFigure);
	assert(reader->fFiguredBass);
	reader->fFiguredBass->add(reader->fFigure);
	reader->fFigure = 0;
}

// prefix
void TMusicXMLReader::EndPrefix(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndPrefix\n"));
	assert(reader->fFigure);
	reader->fFigure->setPrefix(reader->GetDataString());
}

// figure-number
void TMusicXMLReader::EndFigureNumber(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndFigureNumber\n"));
	assert(reader->fFigure);
	reader->fFigure->setNumber(reader->GetDataString());
}

// suffix
void TMusicXMLReader::EndSuffix(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndSuffix\n"));
	assert(reader->fFigure);
	reader->fFigure->setSuffix(reader->GetDataString());
}

// harmony
void TMusicXMLReader::StartHarmony(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartHarmony\n"));
	assert(reader->fHarmony == 0);
	reader->fHarmony = newHarmony();
	
	for (int i=0; attr[i]; i+=2)
    {
		if (EqualStr(attr[i], "type")) 
            reader->fHarmony->setType(THarmony::xml(attr[i+1]));
		else if (EqualStr(attr[i], "print-object")) 
            reader->fHarmony->setPrintObject(YesNo::xml(attr[i+1]));
		else if (EqualStr(attr[i], "print-frame")) 
            reader->fHarmony->setPrintFrame(YesNo::xml(attr[i+1]));
		else if (EqualStr(attr[i], "placement")) 
            reader->fHarmony->placement().set(TPlacement::xmlplace(attr[i+1]));
        else {
            reader->fHarmony->position().set(TPosition::xmlpos(attr[i]), atoi(attr[i+1]));
            if (TPosition::xmlpos(attr[i]) == 0) DBUG(("StartHarmony %s\n",attr[i]));
        }
    }
}

void TMusicXMLReader::EndHarmony(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndHarmony\n"));
	assert(reader->fHarmony);
	assert(reader->fHarmonyChord);
	// We need to add the pending harmony-chord
	reader->fHarmony->add(reader->fHarmonyChord);
	addMusicData(reader, reader->fHarmony);
	reader->fHarmonyChord = 0;
	reader->fHarmony = 0;
}

// harmony-chord, root
void TMusicXMLReader::StartRoot(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartRoot\n"));
	if (reader->fHarmonyChord) { // We have a pending harmony-chord
		assert(reader->fHarmony);
		reader->fHarmony->add(reader->fHarmonyChord);
	} 
	
	assert(reader->fRootFunction == 0);
	reader->fHarmonyChord = newHarmonyChord();
	reader->fRootFunction = newRoot();
}

void TMusicXMLReader::EndRoot(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndRoot\n"));
	assert(reader->fRootFunction);
	reader->fHarmonyChord->setRootFunction(reader->fRootFunction);
	reader->fRootFunction = 0;
}

// root-step
void TMusicXMLReader::EndRootStep(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndRootStep\n"));
	assert(reader->fRootFunction);
	(dynamic_cast<TRoot*>((TRootFunction*)reader->fRootFunction))->setRoot(reader->GetDataString());
}

// root-alter
void TMusicXMLReader::EndRootAlter(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndRootAlter\n"));
	assert(reader->fRootFunction);
	(dynamic_cast<TRoot*>((TRootFunction*)reader->fRootFunction))->setAlter(reader->GetDataString());
}

// harmony-chord, function
void TMusicXMLReader::StartFunction(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartFunction\n"));
	if (reader->fHarmonyChord) { // We have a pending harmony-chord
		assert(reader->fHarmony);
		reader->fHarmony->add(reader->fHarmonyChord);
	} 
	
	assert(reader->fRootFunction == 0);
	reader->fHarmonyChord = newHarmonyChord();
	reader->fRootFunction = newFunction();
}

void TMusicXMLReader::EndFunction(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndFunction\n"));
	assert(reader->fRootFunction);
	(dynamic_cast<TFunction*>((TRootFunction*)reader->fRootFunction))->setFunction(reader->GetDataString());
	reader->fHarmonyChord->setRootFunction(reader->fRootFunction);
	reader->fRootFunction = 0;
}

// kind
void TMusicXMLReader::EndKind(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndKind\n"));
	assert(reader->fHarmonyChord);
	reader->fHarmonyChord->setKind(reader->GetDataString());
}

// inversion
void TMusicXMLReader::EndInversion(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndInversion\n"));
	assert(reader->fHarmonyChord);
	reader->fHarmonyChord->setInversion(reader->GetDataLong());
}

// bass
void TMusicXMLReader::StartBass(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartBass\n"));
	assert(reader->fRootFunction == 0);
	reader->fRootFunction = newBass();
}

void TMusicXMLReader::EndBass(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndBass\n"));
	assert(reader->fRootFunction);
	reader->fHarmonyChord->setBass((dynamic_cast<TBass*>((TRootFunction*)reader->fRootFunction)));
	reader->fRootFunction = 0;
}

// bass-step
void TMusicXMLReader::EndBassStep(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndBassStep\n"));
	assert(reader->fRootFunction);
	(dynamic_cast<TBass*>((TRootFunction*)reader->fRootFunction))->setRoot(reader->GetDataString());
}

// bass-alter
void TMusicXMLReader::EndBassAlter(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndBassAlter\n"));
	assert(reader->fRootFunction);
	(dynamic_cast<TBass*>((TRootFunction*)reader->fRootFunction))->setAlter(reader->GetDataString());
}

// degree
void TMusicXMLReader::StartDegree(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartDegree\n"));
	assert(reader->fDegree == 0);
	reader->fDegree = newDegree();
}

void TMusicXMLReader::EndDegree(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndDegree\n"));
	assert(reader->fDegree);
	assert(reader->fHarmonyChord);
	reader->fHarmonyChord->add(reader->fDegree);
	reader->fDegree = 0;
}

// degree-value
void TMusicXMLReader::EndDegreeValue(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndDegreeValue\n"));
	assert(reader->fDegree);
	reader->fDegree->setValue(reader->GetDataLong());
}

// degree-alter
void TMusicXMLReader::EndDegreeAlter(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndDegreeAlter\n"));
	assert(reader->fDegree);
	reader->fDegree->setAlter(reader->GetDataLong());
}

// degree-type
void TMusicXMLReader::EndDegreeType(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndDegreeType\n"));
	assert(reader->fDegree);
	reader->fDegree->setType(reader->GetDataString());
}

// frame
void TMusicXMLReader::StartFrame(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartFrame\n"));
	
	assert(reader->fHarmony);
	reader->fHarmony->frame() = newFrame();
}

// frame-strings
void TMusicXMLReader::EndFrameStrings(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndFrameStrings\n"));
	assert(reader->fHarmony);
	reader->fHarmony->frame()->setStrings(reader->GetDataLong());
}

// frame-frets
void TMusicXMLReader::EndFrameFrets(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndFrameFrets\n"));
	assert(reader->fHarmony);
	reader->fHarmony->frame()->setFrets(reader->GetDataLong());
}

// frame-fret
void TMusicXMLReader::EndFrameFret(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndFrameFret\n"));
	assert(reader->fHarmony);
	reader->fHarmony->frame()->setFirstFret(reader->GetDataLong());
}

// frame-note
void TMusicXMLReader::StartFrameNote(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartFrameNote\n"));
	assert(reader->fFrameNote == 0);
	reader->fFrameNote = newFrameNote();
}

void TMusicXMLReader::EndFrameNote(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndFrameNote\n"));
	assert(reader->fFrameNote);
	reader->fHarmony->frame()->add(reader->fFrameNote);
	reader->fFrameNote = 0;
}

// staff-details
void TMusicXMLReader::StartStaffDetails(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartStaffDetails\n"));
	assert(reader->fAttributes);
	reader->fAttributes->staffDetails() = newStaffDetails();
	
	for (int i=0; attr[i]; i+=2)
    {
		if (EqualStr(attr[i], "number")) 
            reader->fAttributes->staffDetails()->setNumber(atoi(attr[i+1]));
		else if (EqualStr(attr[i], "show-frets")) 
            reader->fAttributes->staffDetails()->setShowFret(atoi(attr[i+1])); //??
	}
}

// staff-type
void TMusicXMLReader::EndStaffType(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndStaffType\n"));
	assert(reader->fAttributes);
	reader->fAttributes->staffDetails()->setType(TStaffDetails::xml(reader->GetDataString()));
}

// staff-lines
void TMusicXMLReader::EndStaffLines(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndStaffLines\n"));
	assert(reader->fAttributes);
	reader->fAttributes->staffDetails()->setLines(reader->GetDataLong());
}

// staff-tuning
void TMusicXMLReader::StartStaffTuning(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartStaffTuning\n"));
	assert(reader->fStaffTuning == 0);
	
	for (int i=0; attr[i]; i+=2)
    {
		if (EqualStr(attr[i], "line")) 
           reader->fStaffTuning = newStaffTuning(atoi(attr[i+1]));
	}
}

void TMusicXMLReader::EndStaffTuning(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndStaffTuning\n"));
	assert(reader->fAttributes);
	assert(reader->fStaffTuning); 
	reader->fAttributes->staffDetails()->add(reader->fStaffTuning);
	reader->fStaffTuning = 0;
}

// tuning-step
void TMusicXMLReader::EndTuningStep(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndTuningStep\n"));
	assert(reader->fStaffTuning);
	reader->fStaffTuning->setStep(reader->GetDataString());
}

// tuning-alter
void TMusicXMLReader::EndTuningAlter(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndTuningAlter\n"));
	assert(reader->fStaffTuning);
	reader->fStaffTuning->setAlter(reader->GetDataFloat());
}

// tuning-octave
void TMusicXMLReader::EndTuningOctave(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndTuningOctave\n"));
	assert(reader->fStaffTuning);
	reader->fStaffTuning->setOctave(reader->GetDataLong());
}

// capo
void TMusicXMLReader::EndCapo(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndCapo\n"));
	assert(reader->fAttributes);
	reader->fAttributes->staffDetails()->setCapo(reader->GetDataString());
}

// measure-style
void TMusicXMLReader::StartMeasureStyle(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartMeasureStyle\n"));
	assert(reader->fAttributes);
	reader->fAttributes->measureStyle() = newMeasureStyle();
	
	for (int i=0; attr[i]; i+=2)
    {
		if (EqualStr(attr[i], "number")) 
            reader->fAttributes->measureStyle()->setNumber(atoi(attr[i+1]));
	}
}

// multiple-rest
void TMusicXMLReader::StartMultipleRest(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartMultipleRest\n"));
	assert(reader->fMeasureStyleElement == 0);
	SMultipleRest multiple_rest = newMultipleRest();
	
	for (int i=0; attr[i]; i+=2)
    {
		if (EqualStr(attr[i], "use-symbols")) 
            multiple_rest->setUseSymbol(YesNo::xml(attr[i+1]));
	}
	
	reader->fMeasureStyleElement = multiple_rest;
}

void TMusicXMLReader::EndMultipleRest(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndMultipleRest\n"));
	assert(reader->fAttributes);
	assert(reader->fMeasureStyleElement);
	(dynamic_cast<TMultipleRest*>((TMeasureStyleElement*)reader->fMeasureStyleElement))->setData(reader->GetDataString());
	reader->fAttributes->measureStyle()->setStyle(reader->fMeasureStyleElement);
	reader->fMeasureStyleElement = 0;
}

//measure-repeat
void TMusicXMLReader::StartMeasureRepeat(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartMeasureRepeat\n"));
	assert(reader->fMeasureStyleElement == 0);
	SMeasureRepeat measure_repeat = newMeasureRepeat();
	
	for (int i=0; attr[i]; i+=2)
    {
		if (EqualStr(attr[i], "type")) 
            measure_repeat->setStartStop(StartStop::xml(attr[i+1]));
		else if (EqualStr(attr[i], "slashes")) 
            measure_repeat->setSlashes(atoi(attr[i+1]));
	}
	assert(measure_repeat->getStartStop() != StartStop::undefined);
	reader->fMeasureStyleElement = measure_repeat;
}

void TMusicXMLReader::EndMeasureRepeat(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndMeasureRepeat\n"));
	assert(reader->fAttributes);
	assert(reader->fMeasureStyleElement);
	(dynamic_cast<TMeasureRepeat*>((TMeasureStyleElement*)reader->fMeasureStyleElement))->setData(reader->GetDataString());
	reader->fAttributes->measureStyle()->setStyle(reader->fMeasureStyleElement);
	reader->fMeasureStyleElement = 0;
}

// beat-repeat
void TMusicXMLReader::StartBeatRepeat(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartBeatRepeat\n"));
	SBeatRepeat beat_repeat = newBeatRepeat();
	
	for (int i=0; attr[i]; i+=2)
    {
		if (EqualStr(attr[i], "type")) 
            beat_repeat->setStartStop(StartStop::xml(attr[i+1]));
		else if (EqualStr(attr[i], "slashes")) 
            beat_repeat->setSlashes(atoi(attr[1]));
		else if (EqualStr(attr[i], "use-dots")) 
            beat_repeat->setSlashes(YesNo::xml(attr[i+1]));
	}
	
	assert(beat_repeat->getStartStop() != StartStop::undefined);
	reader->fMeasureStyleElement = beat_repeat;
	reader->fAttributes->measureStyle()->setStyle(reader->fMeasureStyleElement);
	reader->fMeasureStyleElement = 0;
}

// slash 
void TMusicXMLReader::StartSlash(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartSlash\n"));
	SSlash slash = newSlash();
	
	for (int i=0; attr[i]; i+=2)
    {
		if (EqualStr(attr[i], "type")) 
            slash->setStartStop(StartStop::xml(attr[i+1]));
		else if (EqualStr(attr[i], "use-dots")) 
            slash->setUseDots(YesNo::xml(attr[i+1]));
		else if (EqualStr(attr[i], "use-stems")) 
            slash->setUseStems(YesNo::xml(attr[i+1]));
	}
	
	assert(slash->getStartStop() != StartStop::undefined);
	reader->fMeasureStyleElement = slash;
	reader->fAttributes->measureStyle()->setStyle(reader->fMeasureStyleElement);
	reader->fMeasureStyleElement = 0;
}

// footnote
void TMusicXMLReader::EndFootNote(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndFootNote\n"));
	reader->fEditorial->footnote()->setData(reader->GetDataString());
}

// level
void TMusicXMLReader::StartLevel(TMusicXMLReader* reader, const char **attr, const char* tag)
{
    DBUG(("StartLevel\n"));
	
	// For all Editoriable elements
	
	if (reader->fAttributes) {
		reader->fEditorial = reader->fAttributes->editorialPtr();
	} else if (reader->fBackup) {
		reader->fEditorial = reader->fBackup->editorialPtr();
	} else if (reader->fBarline) {	
		reader->fEditorial = reader->fBarline->editorialPtr();
	} else if (reader->fDirection) {
		reader->fEditorial = reader->fDirection->editorialPtr();
	} else if (reader->fFiguredBass) {
		reader->fEditorial = reader->fFiguredBass->editorialPtr();
	} else if (reader->fHarmony) {
		reader->fEditorial = reader->fHarmony->editorialPtr();	
	} else if (reader->fPartGroup) {
		reader->fEditorial = reader->fPartGroup->editorialPtr();	
	}	
	for (int i=0; attr[i]; i+=2)
    {
		if (EqualStr(attr[i], "parentheses")) 
            reader->fEditorial->level()->setParentheses(YesNo::xml(attr[i+1]));
		else if (EqualStr(attr[i], "bracket")) 
            reader->fEditorial->level()->setBrackets(YesNo::xml(attr[i+1]));
        else if (EqualStr(attr[i], "size")) 
            reader->fEditorial->level()->setSize(FullCue::xml(attr[i+1]));
    }
}

void TMusicXMLReader::EndLevel(TMusicXMLReader* reader, const char* tag) 
{
	DBUG(("EndLevel\n"));
	reader->fEditorial->level()->setData(reader->GetDataString());
}


// Generic parsing methods

void TMusicXMLReader::StartElementHandler(void *userData, const char *el, const char **attr) 
{
    TMusicXMLReader * reader = (TMusicXMLReader*)userData;
    map<string, StartMethod>::iterator it = reader->fParserTable1.find(el); 
    
    // The string must be reinitialized since CharacterDataHandler will accumulate
    reader->fDataString = "";
    
    if (it == reader->fParserTable1.end()) {
        //printf("Start element not handled %s\n", el);
    }else{
        (it->second)(reader,attr,el);
    }
}		

void TMusicXMLReader::EndElementHandler(void *userData, const char *el)
{
    TMusicXMLReader * reader = (TMusicXMLReader*)userData;
    map<string, EndMethod>::iterator it = reader->fParserTable2.find(el); 
    
    if (it == reader->fParserTable2.end()) {
        //printf("End element not handled %s\n", el);
    }else{
        (it->second)(reader,el);
    }
}

void TMusicXMLReader::CharacterDataHandler(void *userData, const XML_Char *s, int len)
{
    TMusicXMLReader * reader = (TMusicXMLReader*)userData;
    // Accumulate the string since expat may cut a text in several call to CharacterDataHandler 
    reader->fDataString += string(s,len);
}

SScore TMusicXMLReader::Read(iostream filename) 
{
    //return fScore;
    return 0;
}

SScore TMusicXMLReader::Read(const char* filename) 
{
	if (fParser && fParser->read(filename)) {
		if (fPWScore) return fPWScore; else return fTWScore;
	}
	else return 0;
/*
	FILE* file = fopen(filename,"r");
    
    if (file) {
    
        for (;;) {
	  
            long bytes_read;
            void *buff = XML_GetBuffer(fParser, BUFFSIZE);
            
            if (buff == 0) {
                // handle error 
                fprintf(stderr,"XML_GetBuffer error\n");
                return 0;
            }
            
            bytes_read = fread(buff, 1, BUFFSIZE,file);
            
            if (bytes_read < 0) {
                // handle error 
                fprintf(stderr,"Read error %ld\n",bytes_read);
                return 0;
            }
            
            if (!XML_ParseBuffer(fParser, bytes_read, bytes_read == 0)) {
                // handle parse error 
                fprintf(stderr,"Parse error at line %d:\n%s\n",
                        XML_GetCurrentLineNumber(fParser),
                        XML_ErrorString(XML_GetErrorCode(fParser)));
                return 0;
            }
            
            if (bytes_read == 0) break;
        }

		fclose(file);
	  
    }else{
        fprintf(stderr, "File not found %s\n",filename);
        return 0;
    }
    if (fPWScore) return fPWScore; else return fTWScore;
*/
}




} // end of namespace

