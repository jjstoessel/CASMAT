/*
 *  IMUSANT_XMLReader.h
 *  imusant - the Intertextual MUsic ANalysis Tool
 *	Project Supervisor: Dr Rex Eakins
 *
 *  Created by Jason Stoessel on 4/06/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __IMUSANT_XMLREADER__
#define __IMUSANT_XMLREADER__

#include <map>
#include <vector>
#include <string>
#include <fstream>

#include "IMUSANT_score.h"
#include "IMUSANT_part.h"
#include "IMUSANT_measure.h"
#include "IMUSANT_partlist.h"
#include "IMUSANT_chord.h"
#include "IMUSANT_note.h"
#include "IMUSANT_comment.h"
#include "IMUSANT_barline.h"

#include "Iexpat.h"

using namespace std;

namespace IMUSANT
{

//class IMUSANT_XMLReader;
//typedef void (*StartFunction) (IMUSANT_XMLReader* reader, const char **attr, const char* tag);
//typedef void (*EndFunction) (IMUSANT_XMLReader* reader, const char* tag);

typedef char XMLChar;
typedef map<pair<long,long>,S_IMUSANT_note*> measureHandleMap;

class EXP IMUSANT_XMLReader
{
	public:
		typedef void (*StartFunction) (IMUSANT_XMLReader* reader, const char **attr, const char* tag);
		typedef void (*EndFunction) (IMUSANT_XMLReader* reader, const char* tag);
		
				IMUSANT_XMLReader();
		virtual	~IMUSANT_XMLReader() { delete fXMLParser;/*XMLParserFree(fXMLParser);*/ }
		
		S_IMUSANT_score	Read(ifstream& file);
		S_IMUSANT_score Read(const char* filename);
		
	private:
	
		static void CharacterDataHandler(void* userData, const XMLChar* s, int len);
		static void StartElementHandler(void* userData, const char* el, const char**attr);
		static void EndElementHandler(void* userData, const char* el);
		
		void		AddParser(string tag, StartFunction start, EndFunction end);
		void		AddParser(string tag, StartFunction start);
		void		AddParser(string tag, EndFunction end);
		void		ReplaceParser(string tag, StartFunction start, EndFunction end);
		void		ReplaceParser(string tag, EndFunction end);
	
		//getter/setters
		const string&	GetDataString() { return fDataString; }
		long		GetDataLong() { return atoi(fDataString.c_str()); }
		
		//IMUSANT_score
		static void StartIMUSANT_score(IMUSANT_XMLReader* reader, const char** attr, const char* tag);
		static void EndIMUSANT_score(IMUSANT_XMLReader* reader, const char* tag);
		//work title
		static void EndIMUSANT_work_title(IMUSANT_XMLReader* reader, const char* tag);
		//work number
		static void EndIMUSANT_work_number(IMUSANT_XMLReader* reader, const char* tag);
		//movement title
		static void EndIMUSANT_movement_title(IMUSANT_XMLReader* reader, const char* tag);
		//movement number
		static void EndIMUSANT_movement_number(IMUSANT_XMLReader* reader, const char* tag);
		//creator
		static void StartIMUSANT_creator(IMUSANT_XMLReader* reader, const char** attr, const char* tag);
		static void EndIMUSANT_creator(IMUSANT_XMLReader* reader, const char* tag);
		//rights
		static void StartIMUSANT_rights(IMUSANT_XMLReader* reader, const char** attr, const char* tag);
		static void EndIMUSANT_rights(IMUSANT_XMLReader* reader, const char* tag);
		//source
		static void EndIMUSANT_source(IMUSANT_XMLReader* reader, const char* tag);
		
		//partlist
		static void StartIMUSANT_partlist(IMUSANT_XMLReader* reader, const char** attr, const char* tag);
		static void EndIMUSANT_partlist(IMUSANT_XMLReader* reader, const char* tag);
		//IMUSANT_part - attribute: ID
		static void StartIMUSANT_part(IMUSANT_XMLReader* reader, const char** attr, const char* tag);
		static void EndIMUSANT_part(IMUSANT_XMLReader* reader, const char* tag);
		//partname
		static void EndIMUSANT_part_name(IMUSANT_XMLReader* reader, const char* tag);
		//partabbrev
		static void EndIMUSANT_part_abbrev(IMUSANT_XMLReader* reader, const char* tag);
		
		//IMUSANT_measure
		static void StartIMUSANT_measure(IMUSANT_XMLReader* reader, const char** attr, const char* tag);
		static void EndIMUSANT_measure(IMUSANT_XMLReader* reader, const char* tag);
		//clef
		static void StartIMUSANT_clef(IMUSANT_XMLReader* reader, const char** attr, const char* tag);
		static void EndIMUSANT_clef(IMUSANT_XMLReader* reader, const char* tag);
		//clef sign
		static void EndIMUSANT_clef_sign(IMUSANT_XMLReader* reader, const char* tag);
		//clef line
		static void EndIMUSANT_clef_line(IMUSANT_XMLReader* reader, const char* tag);
		//clef transpose
		static void EndIMUSANT_clef_transpose(IMUSANT_XMLReader* reader, const char* tag);
		
		//time signature
		static void StartIMUSANT_time(IMUSANT_XMLReader* reader, const char** attr, const char* tag);
		static void EndIMUSANT_time(IMUSANT_XMLReader* reader, const char* tag);
		//time symbol
		static void EndIMUSANT_time_symbol(IMUSANT_XMLReader* reader, const char* tag);
		//time numerator
		static void EndIMUSANT_time_numerator(IMUSANT_XMLReader* reader, const char* tag);
		//time denominator
		static void EndIMUSANT_time_denominator(IMUSANT_XMLReader* reader, const char* tag);
		
		//key signature
		static void StartIMUSANT_key(IMUSANT_XMLReader* reader, const char** attr, const char* tag);
		static void EndIMUSANT_key(IMUSANT_XMLReader* reader, const char* tag);
		//key fifths
		static void EndIMUSANT_fifths(IMUSANT_XMLReader* reader, const char* tag);
		//key mode
		static void EndIMUSANT_mode(IMUSANT_XMLReader* reader, const char* tag);
		//key cancel
		static void EndIMUSANT_key_cancel(IMUSANT_XMLReader* reader, const char* tag);
		
		//barlines -- to be implemented
		
		//IMUSANT_chord
		static void StartIMUSANT_chord(IMUSANT_XMLReader* reader, const char** attr, const char* tag);
		static void EndIMUSANT_chord(IMUSANT_XMLReader* reader, const char* tag);
		
		//IMUSANT_note - attributes NoteIndex
		static void StartIMUSANT_note(IMUSANT_XMLReader* reader, const char** attr, const char* tag);
		static void EndIMUSANT_note(IMUSANT_XMLReader* reader, const char* tag);
			//pitch
		static void StartIMUSANT_pitch(IMUSANT_XMLReader* reader, const char** attr, const char* tag);
		static void EndIMUSANT_pitch(IMUSANT_XMLReader* reader, const char* tag);
				//pitchname
		static void EndIMUSANT_pitch_name(IMUSANT_XMLReader* reader, const char* tag);
				//alteration
		static void EndIMUSANT_alteration(IMUSANT_XMLReader* reader, const char* tag);
				//octave
		static void EndIMUSANT_octave(IMUSANT_XMLReader* reader, const char* tag);
				//voice
		static void EndIMUSANT_voice(IMUSANT_XMLReader* reader, const char* tag);
			//duration
		static void StartIMUSANT_duration(IMUSANT_XMLReader* reader, const char** attr, const char* tag);
		static void EndIMUSANT_duration(IMUSANT_XMLReader* reader, const char* tag);
				//type
		static void EndIMUSANT_duration_type(IMUSANT_XMLReader* reader, const char* tag);
				//dots
		static void EndIMUSANT_dots(IMUSANT_XMLReader* reader, const char* tag);		
				//timemod
		static void EndIMUSANT_timemodification(IMUSANT_XMLReader* reader, const char* tag);
			//accidental
		static void StartIMUSANT_accidental(IMUSANT_XMLReader* reader, const char** attr, const char* tag);
		static void EndIMUSANT_accidental(IMUSANT_XMLReader* reader, const char* tag);
			//lyric
		static void StartIMUSANT_lyric(IMUSANT_XMLReader* reader, const char** attr, const char* tag);
		static void EndIMUSANT_lyric(IMUSANT_XMLReader* reader, const char* tag);
				//lyric text
		static void EndIMUSANT_text(IMUSANT_XMLReader* reader, const char* tag);
				//lyric elision
		static void EndIMUSANT_elision(IMUSANT_XMLReader* reader, const char* tag);
				//lyric syllabic
		static void EndIMUSANT_syllabic(IMUSANT_XMLReader* reader, const char* tag);
			//tie
		static void StartIMUSANT_tie(IMUSANT_XMLReader* reader, const char** attr, const char* tag);
		static void EndIMUSANT_tie(IMUSANT_XMLReader* reader, const char* tag);
		
		static void EndIMUSANT_rest_or_nonpitch(IMUSANT_XMLReader* reader, const char* tag);
		//directions, etc. to be implemented
		
		//barlines, repeats and endings
		static void StartIMUSANT_barline(IMUSANT_XMLReader* reader, const char** attr, const char* tag);
		static void EndIMUSANT_barline(IMUSANT_XMLReader* reader, const char* tag);
		static void EndIMUSANT_barlinestyle(IMUSANT_XMLReader* reader, const char* tag);
		static void StartIMUSANT_ending(IMUSANT_XMLReader* reader, const char** attr, const char* tag);
		static void StartIMUSANT_repeat(IMUSANT_XMLReader* reader, const char** attr, const char* tag);
		
		//IMUSANT_comment
		static void StartIMUSANT_comment(IMUSANT_XMLReader* reader, const char** attr, const char* tag);
		static void EndIMUSANT_comment(IMUSANT_XMLReader* reader, const char* tag);
		
		//XML parser
		XML_Parser	fXMLParser;
		
		string		fDataString;
		//tables of tags and associated parser objects
		map<string, StartFunction>	fStartParserTable;
		map<string, EndFunction>	fEndParserTable;
		
		//internal contextal objects/flags
		S_IMUSANT_score		fScore;
		S_IMUSANT_partlist	fPartList;
		S_IMUSANT_part		fPart;
		S_IMUSANT_measure	fMeasure;
		S_IMUSANT_chord		fChord;
		S_IMUSANT_note		fNote;
		S_IMUSANT_comment	fComment;
		S_IMUSANT_lyric		fLyric;
		S_IMUSANT_pitch		fPitch;
		S_IMUSANT_duration	fDuration;
		S_IMUSANT_barline	fBarline;
		string				fCreatorType;
		string				fRightType;
		bool				fElided;
		measureHandleMap	fPreviousTieNoteList;
};

} //namespace IMUSANT
#endif