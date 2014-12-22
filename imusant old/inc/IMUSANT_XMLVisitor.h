/*
 *  IMUSANT_XMLVisitor.h
 *  imusant - the Intertextual MUSic ANalysis Tool
 *	Project Supervisor: Dr Rex Eakins
 *
 *  Created by Jason Stoessel on 30/05/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
 
#ifndef __IMUSANT_XMLVisitor__
#define __IMUSANT_XMLVisitor__

#include <stack>
#include <string>

#include "IMUSANT_visitor.h"
#include "xml.h"

using namespace std;
using namespace MusicXML;

namespace IMUSANT
{

class VEXP IMUSANT_XMLVisitor : public IMUSANT_visitor
{
	public:
					IMUSANT_XMLVisitor();
		virtual		~IMUSANT_XMLVisitor() {}
		
		void visit ( S_IMUSANT_attributes& elt );
		void visit ( S_IMUSANT_barline& );
		void visit ( S_IMUSANT_chord& elt );
		void visit ( S_IMUSANT_comment& elt );
		void visit ( S_IMUSANT_element& elt );
		void visit ( S_IMUSANT_lyric& elt );
		void visit ( S_IMUSANT_measure& elt );
		void visit ( S_IMUSANT_note& elt );
		void visit ( S_IMUSANT_part& elt );
		void visit ( S_IMUSANT_partlist& elt );
		void visit ( S_IMUSANT_score& elt );
		
		Sxmlelement& current ()			{ return fStack.top(); }

	protected:

		void add (Sxmlelement& elt)		{ fStack.top()->add(elt); }
		void start (Sxmlelement& elt)	{ fStack.push(elt); }
		void push (Sxmlelement& elt)	{ add(elt); fStack.push(elt); }
		void pop ()						{ fStack.pop(); }
		
	private:
		stack<Sxmlelement>	fStack;
		// global flag to denote chords writing
		bool				fInChord;
};


struct IMUSANT_tags
{
	static const char* accidental;
	static const char* attributes;
	static const char* barline;
	static const char* barline_style;
	static const char* chord; //measure
	static const char* clef;
	static const char* clef_sign; //clef
	static const char* clef_line; //clef
	static const char* clef_transpose; //clef
	static const char* comment; //header
	static const char* creator; //composer; etc.
	static const char* date; //header
	static const char* dots; //note
	static const char* duration; //note
	static const char* duration_type;
	static const char* editor;
	static const char* element; //??
	static const char* elision;
	static const char* ending;
	static const char* key; //measure
	static const char* key_fifths;
	static const char* key_cancel;
	static const char* lyric;
	static const char* measure;
	static const char* mode; //key
	static const char* movt_title; //header
	static const char* movt_num; //header
	static const char* note;
	//static const char* octave; //note-pitch
	static const char* part;
	static const char* partlist;
	static const char* partname; //part
	static const char* partabbrev; //part
	static const char* partid; //part
	static const char* pitch; //note
	static const char* pitch_name;
	static const char* pitch_alter;
	static const char* pitch_octave;
	static const char* repeat;
	static const char* rights; //header
	static const char* score; 
	static const char* score_comments; //header
	static const char* source; //header
	static const char* syllabic;
	static const char* text;
	static const char* tie;
	static const char* time;
	static const char* time_numerator;
	static const char* time_denominator;
	static const char* time_modification; //time
	static const char* transpose; //clef
	static const char* voice; //pitch
	static const char* work_title; //header
	static const char* work_num; //header
};

struct IMUSANT_attributes
{
	static const char* start;
	static const char* end;
	static const char* notestyle;
	static const char* number;
	static const char* tie_type;
	static const char* tie_to_measure;
	static const char* tie_to_noteindex;
	static const char* tie_from_measure;
	static const char* tie_from_noteindex;
	static const char* time_symbol;
	static const char* cautionary;
	static const char* editorial;
	static const char* cancelling;
	static const char* location;
	static const char* type;
	static const char* direction;
	static const char* times;
};

} //namespace IMUSANT
#endif
