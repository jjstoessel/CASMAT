/*
 *  IMUSANT_XMLReader.cpp
 *  imusant - the Intertextual MUsic ANalysis Tool
 *	Project Supervisor: Dr Rex Eakins
 *
 *  Created by Jason Stoessel on 4/06/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include <string>
#include <sstream>

#include "IMUSANT_XMLReader.h"
#include "IMUSANT_XMLVisitor.h"
#include "IMUSANT_conversions.h"

namespace IMUSANT
{

#define IMUSANTXMLReadDebug	0
#define IMUSANTXMLReadDebug2File 0

#if IMUSANTXMLReadDebugFile
#define DebugFile	"XMLReadDebug.txt"
#endif

#if IMUSANTXMLReadDebug
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

//static functions
void IMUSANT_XMLReader::CharacterDataHandler(void* userData, const XMLChar* s, int len)
{
	IMUSANT_XMLReader* reader = (IMUSANT_XMLReader*)userData;
	reader->fDataString += string(s,len);
}

void IMUSANT_XMLReader::StartElementHandler(void* userData, const char* el, const char**attr)
{
	IMUSANT_XMLReader* reader = (IMUSANT_XMLReader*)userData;
	map<string,StartFunction>::iterator iter = reader->fStartParserTable.find(el);
	
	//re-initialise datastring
	reader->fDataString = "";
	
	if (iter != reader->fStartParserTable.end())
		(iter->second)(reader,attr,el);
}

void IMUSANT_XMLReader::EndElementHandler(void* userData, const char* el)
{
	IMUSANT_XMLReader* reader = (IMUSANT_XMLReader*)userData;
	map<string,EndFunction>::iterator iter = reader->fEndParserTable.find(el);
	
	if (iter != reader->fEndParserTable.end())
		(iter->second)(reader,el);
}

#pragma mark element handlers
//IMUSANT_score
void IMUSANT_XMLReader::StartIMUSANT_score(IMUSANT_XMLReader* reader, const char** attr, const char* tag)
{
	DBUG(("StartScore\n"));
	assert(reader->fScore == 0);
	reader->fScore = new_IMUSANT_score();
}

void IMUSANT_XMLReader::EndIMUSANT_score(IMUSANT_XMLReader* reader, const char* tag)
{
	DBUG(("EndScore\n"));
	//do nothing for now.
}
//work title
void IMUSANT_XMLReader::EndIMUSANT_work_title(IMUSANT_XMLReader* reader, const char* tag)
{
	DBUG(("EndWorkTitle\n"));
	assert(reader->fScore);
	reader->fScore->setWorkTitle(reader->GetDataString());
}
//work number
void IMUSANT_XMLReader::EndIMUSANT_work_number(IMUSANT_XMLReader* reader, const char* tag)
{
	DBUG(("EndWorkNum\n"));
	assert(reader->fScore);
	reader->fScore->setWorkNum(reader->GetDataString());
}
//movement title
void IMUSANT_XMLReader::EndIMUSANT_movement_title(IMUSANT_XMLReader* reader, const char* tag)
{
	DBUG(("EndMovementTitle\n"));
	assert(reader->fScore);
	reader->fScore->setMovementTitle(reader->GetDataString());
}

//movement number
void IMUSANT_XMLReader::EndIMUSANT_movement_number(IMUSANT_XMLReader* reader, const char* tag)
{
	DBUG(("EndMovementNumber\n"));
	assert(reader->fScore);
	reader->fScore->setMovementNum(reader->GetDataString());
}

//creator
void IMUSANT_XMLReader::StartIMUSANT_creator(IMUSANT_XMLReader* reader, const char** attr, const char* tag)
{
	assert(reader->fScore);
	
	if (strcmp(IMUSANT_attributes::type, attr[0])==0)
		reader->fCreatorType = attr[1];
	
}

void IMUSANT_XMLReader::EndIMUSANT_creator(IMUSANT_XMLReader* reader, const char* tag)
{
	DBUG(("EndCreator\n"));
	assert(reader->fScore);
	assert(!reader->fCreatorType.empty());
	reader->fScore->addCreator(make_pair(reader->fCreatorType, reader->GetDataString()));
	reader->fCreatorType = "";
}

//rights
void IMUSANT_XMLReader::StartIMUSANT_rights(IMUSANT_XMLReader* reader, const char** attr, const char* tag)
{
	assert(reader->fScore);
	
	if (attr[0] && (strcmp(IMUSANT_attributes::type, attr[0])==0))
		reader->fRightType = attr[1];
	
}

void IMUSANT_XMLReader::EndIMUSANT_rights(IMUSANT_XMLReader* reader, const char* tag)
{
	DBUG(("EndRights\n"));
	assert(reader->fScore);
	//assert(!reader->fRightType.empty());
	reader->fScore->addRights(make_pair(reader->fRightType, reader->GetDataString()));
	reader->fRightType = "";
}

//source
void IMUSANT_XMLReader::EndIMUSANT_source(IMUSANT_XMLReader* reader, const char* tag)
{
	DBUG(("EndSource\n"));
	assert(reader->fScore);
	reader->fScore->setSource(reader->GetDataString());
}

void IMUSANT_XMLReader::StartIMUSANT_partlist(IMUSANT_XMLReader* reader, const char** attr, const char* tag)
{
	DBUG(("StartPartList\n"));
	reader->fPartList = reader->fScore->partlist();
}

void IMUSANT_XMLReader::EndIMUSANT_partlist(IMUSANT_XMLReader* reader, const char* tag)
{
	DBUG(("EndPartList\n"));
	reader->fPartList = 0;
}

//IMUSANT_part - attribute: ID
void IMUSANT_XMLReader::StartIMUSANT_part(IMUSANT_XMLReader* reader, const char** attr, const char* tag)
{
	DBUG(("StartPart\n"));
	reader->fPart = new_IMUSANT_part();
	reader->fPart->setID(attr[1]);
}

void IMUSANT_XMLReader::EndIMUSANT_part(IMUSANT_XMLReader* reader, const char* tag)
{
	DBUG(("EndPart\n"));
	assert(reader->fScore);
	assert(reader->fPart);
	reader->fScore->addPart(reader->fPart);
	reader->fPart=0;
}

//partname
void IMUSANT_XMLReader::EndIMUSANT_part_name(IMUSANT_XMLReader* reader, const char* tag)
{
	DBUG(("EndPartName\n"));
	assert(reader->fPart);
	reader->fPart->setPartName(reader->GetDataString());
}

//partabbrev
void IMUSANT_XMLReader::EndIMUSANT_part_abbrev(IMUSANT_XMLReader* reader, const char* tag)
{
	DBUG(("EndPartAbbrev\n"));
	assert(reader->fPart);
	reader->fPart->setPartAbbrev(reader->GetDataString());
}

//IMUSANT_measure
void IMUSANT_XMLReader::StartIMUSANT_measure(IMUSANT_XMLReader* reader, const char** attr, const char* tag)
{
	DBUG(("StartMeasure\n"));
	assert(reader->fMeasure==0);
	reader->fMeasure = new_IMUSANT_measure();
	reader->fMeasure->setMeasureNum(atoi(attr[1]));
}

void IMUSANT_XMLReader::EndIMUSANT_measure(IMUSANT_XMLReader* reader, const char* tag)
{
	DBUG(("EndMeasure\n"));
	if (reader->fScore && reader->fPart && reader->fMeasure)
	{
		reader->fPart->addMeasure(reader->fMeasure);
		reader->fMeasure=0;
	}
	
}

//clef
void IMUSANT_XMLReader::StartIMUSANT_clef(IMUSANT_XMLReader* reader, const char** attr, const char* tag)
{
	//clef is instantiated in fMeasure at present
}
void IMUSANT_XMLReader::EndIMUSANT_clef(IMUSANT_XMLReader* reader, const char* tag)
{

}
//clef sign
void IMUSANT_XMLReader::EndIMUSANT_clef_sign(IMUSANT_XMLReader* reader, const char* tag)
{
	DBUG(("EndClefSign\n"));
	assert (reader->fMeasure);
	reader->fMeasure->getClef().setSign(reader->GetDataString()[0]);
}

//clef line
void IMUSANT_XMLReader::EndIMUSANT_clef_line(IMUSANT_XMLReader* reader, const char* tag)
{
	DBUG(("EndClefLine\n"));
	assert (reader->fMeasure);
	reader->fMeasure->getClef().setLine(reader->GetDataLong());
}
//clef transpose
void IMUSANT_XMLReader::EndIMUSANT_clef_transpose(IMUSANT_XMLReader* reader, const char* tag)
{
	DBUG(("EndClefTranspose\n"));
	assert (reader->fMeasure);
	reader->fMeasure->getClef().setTransposition(reader->GetDataLong());
}

//time signature
void IMUSANT_XMLReader::StartIMUSANT_time(IMUSANT_XMLReader* reader, const char** attr, const char* tag)
{
	//time is instantiated by fMeasure at present.
	DBUG(("StartTime\n"));
	assert (reader->fMeasure);
	reader->fMeasure->getTime().setSymbol(IMUSANT_time::xmlsymbol(attr[1]));

}

void IMUSANT_XMLReader::EndIMUSANT_time(IMUSANT_XMLReader* reader, const char* tag)
{
	DBUG(("EndTime\n"));
}

//time symbol
void IMUSANT_XMLReader::EndIMUSANT_time_symbol(IMUSANT_XMLReader* reader, const char* tag)
{
}

//time numerator
void IMUSANT_XMLReader::EndIMUSANT_time_numerator(IMUSANT_XMLReader* reader, const char* tag)
{
	DBUG(("EndTimeNumerator\n"));
	assert (reader->fMeasure);
	int i = 0;
	while ( i<=reader->GetDataString().length())
	{
		stringstream ss;
		if (reader->GetDataString()[i]!='+')
		{
			ss << reader->GetDataString()[i];
		}
		else
		{
			reader->fMeasure->getTime().addNumerator((atoi(ss.str().c_str())));
		}	
		i++;
	}
	
}
	
//time denominator
void IMUSANT_XMLReader::EndIMUSANT_time_denominator(IMUSANT_XMLReader* reader, const char* tag)
{
	DBUG(("EndTimeDenominator\n"));
	assert (reader->fMeasure);
	int i = 0;
	while ( i<=reader->GetDataString().length())
	{
		stringstream ss;
		if (reader->GetDataString()[i]!='+')
		{
			ss << reader->GetDataString()[i];
		}
		else
		{
			reader->fMeasure->getTime().addDenominator(atoi(ss.str().c_str()));
		}	
		i++;
	}
}

//key signature
void IMUSANT_XMLReader::StartIMUSANT_key(IMUSANT_XMLReader* reader, const char** attr, const char* tag){}
void IMUSANT_XMLReader::EndIMUSANT_key(IMUSANT_XMLReader* reader, const char* tag){}

//key fifths
void IMUSANT_XMLReader::EndIMUSANT_fifths(IMUSANT_XMLReader* reader, const char* tag)
{
	DBUG(("EndFifths\n"));
	assert(reader->fMeasure);
	reader->fMeasure->getKey().setFifths(reader->GetDataLong());
}

//key mode
void IMUSANT_XMLReader::EndIMUSANT_mode(IMUSANT_XMLReader* reader, const char* tag)
{
	DBUG(("EndMode\n"));
	assert(reader->fMeasure);
	reader->fMeasure->getKey().setMode(IMUSANT_key::xmlmode(reader->GetDataString()));
}

//key cancel
void IMUSANT_XMLReader::EndIMUSANT_key_cancel(IMUSANT_XMLReader* reader, const char* tag)
{
	DBUG(("EndKeyCancel\n"));
	assert(reader->fMeasure);
	reader->fMeasure->getKey().setCancel(reader->GetDataLong());
}

//barlines -- to be implemented

//IMUSANT_chord
void IMUSANT_XMLReader::StartIMUSANT_chord(IMUSANT_XMLReader* reader, const char** attr, const char* tag)
{
	DBUG(("StartChord\n"));
	assert(reader->fMeasure);
	assert(reader->fChord==0);
	reader->fChord = new_IMUSANT_chord();
}
void IMUSANT_XMLReader::EndIMUSANT_chord(IMUSANT_XMLReader* reader, const char* tag)
{
	DBUG(("EndChord\n"));
	assert(reader->fMeasure && reader->fChord);
	reader->fMeasure->addElement(reader->fChord);
	reader->fChord = 0;
}

//IMUSANT_note - attributes NoteIndex
void IMUSANT_XMLReader::StartIMUSANT_note(IMUSANT_XMLReader* reader, const char** attr, const char* tag)
{
	DBUG(("StartNote\n"));
	assert(reader->fMeasure);
	assert(reader->fNote == 0);
	reader->fNote = new_IMUSANT_note();
	reader->fNote->setNoteIndex(atoi(attr[1])); //attr[0] contains tag
	reader->fNote->setMeasureNum(reader->fMeasure->getMeasureNum()); //measure nos must be set for ties to coordinate
	//at the moment only one attribute, number, is present. Addition attributes, eg. status=hidden
	//will need to be parsed.
}

void IMUSANT_XMLReader::EndIMUSANT_note(IMUSANT_XMLReader* reader, const char* tag)
{
	DBUG(("EndNote\n"));
	assert(reader->fMeasure && reader->fNote);
	if (reader->fChord) 
	{
		assert((IMUSANT_chord*)reader->fChord != 0);
		reader->fChord->add(reader->fNote);
	}
    else 
	{
		reader->fMeasure->addNote(reader->fNote);
    }
	
	reader->fNote=0;
}
	//pitch
void IMUSANT_XMLReader::StartIMUSANT_pitch(IMUSANT_XMLReader* reader, const char** attr, const char* tag)
{
	assert(reader->fNote);
	reader->fPitch = new_IMUSANT_pitch();
}

void IMUSANT_XMLReader::EndIMUSANT_pitch(IMUSANT_XMLReader* reader, const char* tag)
{
	assert(reader->fNote);
	reader->fNote->setPitch(reader->fPitch);
	reader->fPitch = 0;
}
		//pitchname
void IMUSANT_XMLReader::EndIMUSANT_pitch_name(IMUSANT_XMLReader* reader, const char* tag)
{
	DBUG(("EndPitchName\n"));
	if (reader->fPitch)
		reader->fPitch->setName(IMUSANT_pitch::xml(reader->GetDataString()));
}
		//accidental
void IMUSANT_XMLReader::EndIMUSANT_alteration(IMUSANT_XMLReader* reader, const char* tag)
{
	DBUG(("EndAlteration\n"));
	if (reader->fPitch)
		reader->fPitch->setAlteration(reader->GetDataLong());
}
		//octave
void IMUSANT_XMLReader::EndIMUSANT_octave(IMUSANT_XMLReader* reader, const char* tag)
{
	DBUG(("EndOctave\n"));
	if (reader->fPitch)
		reader->fPitch->setOctave(reader->GetDataLong());
}
		//voice
void IMUSANT_XMLReader::EndIMUSANT_voice(IMUSANT_XMLReader* reader, const char* tag)
{	
	DBUG(("EndVoice\n"));
	if (reader->fPitch)
		reader->fPitch->setVoice(reader->GetDataLong());
}
	//duration
void IMUSANT_XMLReader::StartIMUSANT_duration(IMUSANT_XMLReader* reader, const char** attr, const char* tag)
{
	assert(reader->fNote);
	reader->fDuration = new_IMUSANT_duration();
}

void IMUSANT_XMLReader::EndIMUSANT_duration(IMUSANT_XMLReader* reader, const char* tag)
{
	assert(reader->fDuration);
	reader->fNote->setDuration(reader->fDuration);
	reader->fDuration = 0;
}
		//type
void IMUSANT_XMLReader::EndIMUSANT_duration_type(IMUSANT_XMLReader* reader, const char* tag)
{
	DBUG(("EndDurationType\n"));
	if (reader->fDuration)
		reader->fDuration->fDuration = TRational(IMUSANT_duration::xmlv1(reader->GetDataString()));
}
		//dots
void IMUSANT_XMLReader::EndIMUSANT_dots(IMUSANT_XMLReader* reader, const char* tag)
{
	DBUG(("EndDots\n"));
	if (reader->fDuration)
		reader->fDuration->fDots = reader->GetDataLong();
}

void IMUSANT_XMLReader::StartIMUSANT_accidental(IMUSANT_XMLReader* reader, const char** attr, const char* tag)
{
	DBUG(("StartAccidental\n"));
    assert(reader->fNote);
    S_IMUSANT_accidental accidental = new_IMUSANT_accidental();
        
    for (int i=0; attr[i]; i+=2)
    {
        DBUG(("attr[i] %s %s\n", attr[i], attr[i+1]));
        if (strcmp(attr[i], IMUSANT_attributes::cautionary)==0) 
            accidental->setCautionary(YesNo::xml(attr[i+1]));
        else if (strcmp(attr[i], IMUSANT_attributes::editorial)==0) 
            accidental->setEditorial(YesNo::xml(attr[i+1]));
        else if (strcmp(attr[i], IMUSANT_attributes::cancelling)==0) 
            accidental->setCancelling(YesNo::xml(attr[i+1]));
    }
    
    reader->fNote->setAccidental(accidental);
}
void IMUSANT_XMLReader::EndIMUSANT_accidental(IMUSANT_XMLReader* reader, const char* tag) 
{
    DBUG(("EndAccidental\n"));
    assert(reader->fNote->accidental());
    reader->fNote->accidental()->setAccident(IMUSANT_accidental::xml(reader->GetDataString()));
}
		//timemod
void IMUSANT_XMLReader::EndIMUSANT_timemodification(IMUSANT_XMLReader* reader, const char* tag)
{
	DBUG(("EndTimeModification\n"));
	if (reader->fDuration)
		reader->fDuration->fTimeModification = TRational(reader->GetDataString());
}
	//lyric
void IMUSANT_XMLReader::StartIMUSANT_lyric(IMUSANT_XMLReader* reader, const char** attr, const char* tag)
{
	DBUG(("StartLyric\n"));
	assert(reader->fNote);
	reader->fLyric = new_IMUSANT_lyric();
	reader->fLyric->setNumber(atoi(attr[1]));
}

void IMUSANT_XMLReader::EndIMUSANT_lyric(IMUSANT_XMLReader* reader, const char* tag)
{
	DBUG(("EndLyric\n"));
	assert( reader->fLyric);
	assert( reader->fNote );
	reader->fNote->addLyric(reader->fLyric);
	reader->fLyric = 0;
}
		//lyric text
void IMUSANT_XMLReader::EndIMUSANT_text(IMUSANT_XMLReader* reader, const char* tag)
{
	DBUG(("EndText\n"));
	assert(reader->fLyric);
	reader->fLyric->addSyllable(reader->GetDataString());
	reader->fElided = false;
}
		//lyric elision
void IMUSANT_XMLReader::EndIMUSANT_elision(IMUSANT_XMLReader* reader, const char* tag)
{
	DBUG(("EndElision"));
	reader->fElided = true;
}

void IMUSANT_XMLReader::EndIMUSANT_syllabic(IMUSANT_XMLReader* reader, const char* tag)
{
	DBUG(("EndSyllabic\n"));
	assert(reader->fLyric);
	reader->fLyric->setSyllabic(IMUSANT_syllabic::xml(reader->GetDataString()));
}
	//tie
void IMUSANT_XMLReader::StartIMUSANT_tie(IMUSANT_XMLReader* reader, const char** attr, const char* tag)
{
	DBUG(("StartTie\n"));
	if (reader->fNote)
	{
		//attributes array terminated by empty element
		for (int i=0; attr[i]; i+=6)
		{
			if (strcmp(attr[i+1],IMUSANT_attributes::start) == 0)
			{
				S_IMUSANT_note* handle = new S_IMUSANT_note;
				*handle = reader->fNote;
				reader->fPreviousTieNoteList[make_pair(atoi(attr[i+3]),atoi(attr[i+5]))]=handle;
				break;
			}
			else if (strcmp(attr[i+1],IMUSANT_attributes::end) == 0)
			{  //link note to previous stored note handle with reference to this note
				S_IMUSANT_note* prevHandle = reader->fPreviousTieNoteList \
					[make_pair(reader->fNote->getMeasureNum(),reader->fNote->getNoteIndex())];
				if (prevHandle)
				{
					reader->fNote->setPreviousTieNote(*prevHandle);
					reader->fPreviousTieNoteList.erase(make_pair(atoi(attr[i+3]),atoi(attr[i+5])));
				}
				break;
			}
		}
	}
}

void IMUSANT_XMLReader::EndIMUSANT_tie(IMUSANT_XMLReader* reader, const char* tag)
{
	DBUG(("EndTie\n"));
}

void IMUSANT_XMLReader::EndIMUSANT_rest_or_nonpitch(IMUSANT_XMLReader* reader, const char* tag)
{
	DBUG(("EndRest\n"));
	if (reader->fNote)
		reader->fNote->setType(IMUSANT_NoteType::xml(tag));
}

//directions, etc. to be implemented

//barlines, repeats and endings
void IMUSANT_XMLReader::StartIMUSANT_barline(IMUSANT_XMLReader* reader, const char** attr, const char* tag)
{
	DBUG(("StartBarline"));
	assert(reader->fMeasure);
	reader->fBarline = new_IMUSANT_barline();
	if (strcmp(IMUSANT_attributes::location, attr[0])==0)
		reader->fBarline->setLocation(IMUSANT_barline::xmllocation(attr[1]));
	
}

void IMUSANT_XMLReader::EndIMUSANT_barline(IMUSANT_XMLReader* reader, const char* tag)
{
	DBUG(("EndBarline"));
	assert( reader->fBarline );
	assert( reader->fMeasure );
	reader->fMeasure->addElement(reader->fBarline);
	reader->fBarline = 0;
}

void IMUSANT_XMLReader::EndIMUSANT_barlinestyle(IMUSANT_XMLReader* reader, const char* tag)
{
	DBUG(("EndBarlineStyle"));
	assert(reader->fBarline);
	reader->fBarline->setBarStyle(IMUSANT_barline::xmlstyle(reader->GetDataString()));
}

void IMUSANT_XMLReader::StartIMUSANT_ending(IMUSANT_XMLReader* reader, const char** attr, const char* tag)
{
	DBUG(("StartEnding"));
	assert(reader->fBarline);
	
	S_IMUSANT_ending end = new_IMUSANT_ending();
	
	for (int i=0; attr[i]; i+=2)
    {
        DBUG(("attr[i] %s %s\n", attr[i], attr[i+1]));
        if (strcmp(attr[i], IMUSANT_attributes::number)==0) 
            end->setNumber(atoi(attr[i+1]));
        else if (strcmp(attr[i], IMUSANT_attributes::type)==0) 
            end->setType(IMUSANT_ending::xml(attr[i+1]));
	}
	reader->fBarline->setEnding(end);
}

void IMUSANT_XMLReader::StartIMUSANT_repeat(IMUSANT_XMLReader* reader, const char** attr, const char* tag)
{
	DBUG(("StartRepeat"));
	assert(reader->fBarline);
	
	S_IMUSANT_repeat repeat = new_IMUSANT_repeat();
	
	for (int i=0; attr[i]; i+=2)
    {
        DBUG(("attr[i] %s %s\n", attr[i], attr[i+1]));
        if (strcmp(attr[i], IMUSANT_attributes::direction)==0) 
            repeat->setDirection(IMUSANT_repeat::xml(attr[i+1]));
        else if (strcmp(attr[i], IMUSANT_attributes::times)==0) 
            repeat->setTimes(atoi(attr[i+1]));
	}
	reader->fBarline->setRepeat(repeat);
}
		
//IMUSANT_comment
void IMUSANT_XMLReader::StartIMUSANT_comment(IMUSANT_XMLReader* reader, const char** attr, const char* tag){}
void IMUSANT_XMLReader::EndIMUSANT_comment(IMUSANT_XMLReader* reader, const char* tag){}

#pragma mark non-static class methods

IMUSANT_XMLReader::IMUSANT_XMLReader()
{
	fXMLParser = XML_ParserCreate(0);
    
    if (!fXMLParser) {
        fprintf(stderr, "Couldn't allocate memory for parser\n");
        throw -1;
    }
    
    // Set start/end handler
    XML_SetElementHandler(fXMLParser, StartElementHandler, EndElementHandler);
    // Set the data handler
    XML_SetCharacterDataHandler(fXMLParser, CharacterDataHandler);
    // To get the parset in callbacks
    XML_SetUserData(fXMLParser, this);
    
    // Set tag handlers
	//score
	AddParser(IMUSANT_tags::score, StartIMUSANT_score, EndIMUSANT_score);
	AddParser(IMUSANT_tags::work_title, EndIMUSANT_work_title);
	AddParser(IMUSANT_tags::work_num, EndIMUSANT_work_number);
	AddParser(IMUSANT_tags::movt_title, EndIMUSANT_movement_title);
	AddParser(IMUSANT_tags::movt_num, EndIMUSANT_movement_number);
	AddParser(IMUSANT_tags::creator, StartIMUSANT_creator, EndIMUSANT_creator);
	AddParser(IMUSANT_tags::rights, StartIMUSANT_rights, EndIMUSANT_rights);
	AddParser(IMUSANT_tags::source, EndIMUSANT_source);
	//AddParser(IMUSANT_tags::score_comments, EndIMUSANT_score_comment);
	//IMUSANT_tags::date; //header
	//IMUSANT_tags::editor;
	
	//partlist
	AddParser(IMUSANT_tags::partlist, StartIMUSANT_partlist, EndIMUSANT_partlist);
	
	//parts - IMUSANT_tags::partid
	AddParser(IMUSANT_tags::part, StartIMUSANT_part, EndIMUSANT_part);
	AddParser(IMUSANT_tags::partname, EndIMUSANT_part_name);
	AddParser(IMUSANT_tags::partabbrev, EndIMUSANT_part_abbrev);
	//IMUSANT_tags::transpose; 
	//measure
	AddParser(IMUSANT_tags::measure, StartIMUSANT_measure, EndIMUSANT_measure);
	//IMUSANT_tags::attributes;
	//clef
	//AddParser(IMUSANT_tags::clef, StartIMUSANT_clef, EndIMUSANT_clef);
	AddParser(IMUSANT_tags::clef_sign, EndIMUSANT_clef_sign);
	AddParser(IMUSANT_tags::clef_line, EndIMUSANT_clef_line);
	AddParser(IMUSANT_tags::clef_transpose, EndIMUSANT_clef_transpose);
	//time
	AddParser(IMUSANT_tags::time, StartIMUSANT_time, EndIMUSANT_time);
	//AddParser(IMUSANT_tags::time_symbol, EndIMUSANT_time_symbol);
	AddParser(IMUSANT_tags::time_numerator, EndIMUSANT_time_numerator);
	AddParser(IMUSANT_tags::time_denominator, EndIMUSANT_time_denominator);
	//key
	//AddParser(IMUSANT_tags::key, StartIMUSANT_key, EndIMUSANT_key);
	AddParser(IMUSANT_tags::key_fifths, EndIMUSANT_fifths);
	AddParser(IMUSANT_tags::mode, EndIMUSANT_mode);
	AddParser(IMUSANT_tags::key_cancel, EndIMUSANT_key_cancel);
	//chord
	AddParser(IMUSANT_tags::chord, StartIMUSANT_chord, EndIMUSANT_chord);	
	//note
	AddParser(IMUSANT_tags::note, StartIMUSANT_note, EndIMUSANT_note);
	//attribute IMUSANT_tags::number;
	//pitch
	AddParser(IMUSANT_NoteType::xml(IMUSANT_NoteType::pitch), StartIMUSANT_pitch, EndIMUSANT_pitch); //IMUSANT_tags::pitch
	AddParser(IMUSANT_tags::pitch_name, EndIMUSANT_pitch_name);
	AddParser(IMUSANT_tags::pitch_alter, EndIMUSANT_alteration);
	AddParser(IMUSANT_tags::pitch_octave, EndIMUSANT_octave);
	AddParser(IMUSANT_tags::voice, EndIMUSANT_voice);
	
	//duration
	AddParser(IMUSANT_tags::duration, StartIMUSANT_duration, EndIMUSANT_duration);
	AddParser(IMUSANT_tags::duration_type, EndIMUSANT_duration_type);
	AddParser(IMUSANT_tags::dots, EndIMUSANT_dots);
	AddParser(IMUSANT_tags::time_modification, EndIMUSANT_timemodification);
	//accidental
	AddParser(IMUSANT_tags::accidental, StartIMUSANT_accidental, EndIMUSANT_accidental);
	//lyric
	AddParser(IMUSANT_tags::lyric, StartIMUSANT_lyric, EndIMUSANT_lyric);
	AddParser(IMUSANT_tags::text, EndIMUSANT_text);
	AddParser(IMUSANT_tags::elision, EndIMUSANT_elision);
	AddParser(IMUSANT_tags::syllabic, EndIMUSANT_syllabic);
	//ties
	AddParser(IMUSANT_tags::tie, StartIMUSANT_tie, EndIMUSANT_tie);
	//attributes: IMUSANT_tags::tie_type, IMUSANT_tags::tie_to_measure, IMUSANT_tags::tie_to_noteindex;
	//IMUSANT_tags::tie_from_measure, IMUSANT_tags::tie_from_noteindex;
	
	AddParser(IMUSANT_NoteType::xml(IMUSANT_NoteType::rest), EndIMUSANT_rest_or_nonpitch);
	AddParser(IMUSANT_NoteType::xml(IMUSANT_NoteType::nonpitch), EndIMUSANT_rest_or_nonpitch);
	
	//barlines, repeats and endings
	AddParser(IMUSANT_tags::barline, StartIMUSANT_barline, EndIMUSANT_barline );
	AddParser(IMUSANT_tags::barline_style, EndIMUSANT_barlinestyle);
	AddParser(IMUSANT_tags::ending, StartIMUSANT_ending);
	AddParser(IMUSANT_tags::repeat, StartIMUSANT_repeat);
	
	//comment
	AddParser(IMUSANT_tags::comment, StartIMUSANT_comment, EndIMUSANT_comment);
	
	// Initialise contextual variables/flags
	
	fScore = 0;
	fPart  = 0;
	fMeasure = 0;
	fChord = 0;
	fNote = 0;
	fComment = 0; //is variable necessary?
	fLyric = 0;
	fPitch = 0;
	fDuration = 0;
	fBarline = 0;
	fCreatorType = "";
	fRightType = "";
	fElided = false;
}

S_IMUSANT_score	IMUSANT_XMLReader::Read(ifstream& file)
{
	return 0;
}

S_IMUSANT_score IMUSANT_XMLReader::Read(const char* filename)
{
	if (fXMLParser && fXMLParser->read(filename))
	{
		if (fScore) return fScore;
	}
	
	return 0;
}

void IMUSANT_XMLReader::AddParser(string tag, StartFunction start, EndFunction end)
{
	AddParser(tag, start);
	AddParser(tag,end);
}

void IMUSANT_XMLReader::AddParser(string tag, StartFunction start)
{
	fStartParserTable.insert(make_pair(tag,start));
}

void IMUSANT_XMLReader::AddParser(string tag, EndFunction end)
{
	fEndParserTable.insert(make_pair(tag,end));
}

void IMUSANT_XMLReader::ReplaceParser(string tag, StartFunction start, EndFunction end)
{
	fStartParserTable[tag] = start;
	fEndParserTable[tag] = end;
}

void IMUSANT_XMLReader::ReplaceParser(string tag, EndFunction end)
{
	fEndParserTable[tag] = end;
}

} //namespace IMUSANT
