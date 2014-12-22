/*
 *  IMUSANT_XMLVisitor.cpp
 *  imusant
 *
 *  Created by Jason Stoessel on 30/05/06.
 *  Copyright 2006 Jason Stoessel. All rights reserved.
 *
 *	This class utilises the visitor paradigm to create a custom internal XML representation that can be written
 *	to file using the standard out operator.
 */


#include "IMUSANT_XMLVisitor.h"
#include "IMUSANT_part.h"
#include "IMUSANT_partlist.h"
#include "IMUSANT_score.h"
#include "IMUSANT_measure.h"
#include "IMUSANT_chord.h"
#include "IMUSANT_note.h"
#include "IMUSANT_conversions.h"
#include "IMUSANT_barline.h"

#include "xml.h"

#include <vector>
#include <sstream>

namespace IMUSANT
{

//TAGS definitions
const char* IMUSANT_tags::accidental = "accidental";
const char* IMUSANT_tags::attributes = "attributes";
const char* IMUSANT_tags::barline = "barline";
const char* IMUSANT_tags::barline_style = "barline-style";
const char* IMUSANT_tags::chord = "chord"; //measure
const char* IMUSANT_tags::clef = "clef";
const char* IMUSANT_tags::clef_sign = "clef-sign"; //clef
const char* IMUSANT_tags::clef_line = "clef-line"; //clef
const char* IMUSANT_tags::clef_transpose = "clef-transpose"; //clef
const char* IMUSANT_tags::comment = "comment"; //header
const char* IMUSANT_tags::creator = "creator"; //composer, etc.
const char* IMUSANT_tags::date = "date"; //header
const char* IMUSANT_tags::dots = "dots"; //note
const char* IMUSANT_tags::duration = "duration"; //note
const char* IMUSANT_tags::duration_type = "type";
const char* IMUSANT_tags::editor = "editor";
const char* IMUSANT_tags::element = "element"; //??
const char* IMUSANT_tags::elision = "elision";
const char* IMUSANT_tags::ending = "ending";
const char* IMUSANT_tags::key = "key"; //measure
const char* IMUSANT_tags::key_fifths = "fifths";
const char* IMUSANT_tags::key_cancel = "cancel";
const char* IMUSANT_tags::lyric = "lyric";
const char* IMUSANT_tags::measure = "measure";
const char* IMUSANT_tags::mode = "mode"; //key
const char* IMUSANT_tags::movt_title = "movement-title"; //header
const char* IMUSANT_tags::movt_num = "movement-number"; //header
const char* IMUSANT_tags::note = "note";
//const char* IMUSANT_tags::octave = "OCT"; //note-pitch
const char* IMUSANT_tags::part = "part";
const char* IMUSANT_tags::partlist = "part-list";
const char* IMUSANT_tags::partname = "part-name"; //part
const char* IMUSANT_tags::partabbrev = "part-abbreviation"; //part
const char* IMUSANT_tags::partid = "part-id"; //part
const char* IMUSANT_tags::pitch = "pitch"; //note
const char* IMUSANT_tags::pitch_name = "name";
const char* IMUSANT_tags::pitch_alter = "alter";
const char* IMUSANT_tags::pitch_octave = "octave";
const char* IMUSANT_tags::repeat = "repeat";
const char* IMUSANT_tags::rights = "rights"; //header
const char* IMUSANT_tags::score = "IMUSANT-score"; 
const char* IMUSANT_tags::score_comments = "score-comments"; //header
const char* IMUSANT_tags::source = "source"; //header
const char* IMUSANT_tags::syllabic = "syllabic"; //lyric
const char* IMUSANT_tags::text = "text";
const char* IMUSANT_tags::tie = "tie";
const char* IMUSANT_tags::time = "time";
const char* IMUSANT_tags::time_numerator = "numerator";
const char* IMUSANT_tags::time_denominator = "denominator";
const char* IMUSANT_tags::time_modification = "time-modification"; //time
const char* IMUSANT_tags::transpose = "transpose"; //part
const char* IMUSANT_tags::voice = "voice"; //pitch
const char* IMUSANT_tags::work_title = "work-title"; //header
const char* IMUSANT_tags::work_num = "work-number"; //header

//Attributes definitions
const char* IMUSANT_attributes::start = "start";
const char* IMUSANT_attributes::end = "end";
const char* IMUSANT_attributes::notestyle = "note-style";
const char* IMUSANT_attributes::number = "number"; //measure
const char* IMUSANT_attributes::tie_type = "tie-type";
const char* IMUSANT_attributes::tie_to_measure = "to-measure";
const char* IMUSANT_attributes::tie_to_noteindex = "to-note";
const char* IMUSANT_attributes::tie_from_measure = "from-measure";
const char* IMUSANT_attributes::tie_from_noteindex = "from-note";
const char* IMUSANT_attributes::time_symbol = "symbol";
const char* IMUSANT_attributes::cautionary = "cautionary";
const char* IMUSANT_attributes::editorial = "editorial";
const char* IMUSANT_attributes::cancelling = "cancelling";
const char* IMUSANT_attributes::location = "location";
const char* IMUSANT_attributes::type = "type";
const char* IMUSANT_attributes::direction = "direction";
const char* IMUSANT_attributes::times = "times";

IMUSANT_XMLVisitor::IMUSANT_XMLVisitor()
{
	fInChord = false;
}

#pragma mark IMUSANT_attributes handler
void IMUSANT_XMLVisitor::visit ( S_IMUSANT_attributes& elt )
{
}

#pragma mark IMUSANT_barline handler
void IMUSANT_XMLVisitor::visit ( S_IMUSANT_barline& elt )
{
	if (elt->getBarStyle()!=IMUSANT_barline::none)
	{
		Sxmlelement xmlelt = new_xmlelement(IMUSANT_tags::barline);
		
		xmlelt->add(new_xmlattribute(IMUSANT_attributes::location, IMUSANT_barline::xmllocation(elt->getLocation())));
		xmlelt->add(new_xmlelement(IMUSANT_tags::barline_style, IMUSANT_barline::xmlstyle(elt->getBarStyle())));
		if (elt->ending()!=0)
		{
			Sxmlelement xmlending = new_xmlelement(IMUSANT_tags::ending);
			xmlending->add(new_xmlattribute(IMUSANT_attributes::number, elt->ending()->getNumber()));
			xmlending->add(new_xmlattribute(IMUSANT_attributes::type, IMUSANT_ending::xml(elt->ending()->getType())));
			xmlelt->add(xmlending);
		}
		if (elt->repeat()!=0)
		{
			Sxmlelement xmlrepeat = new_xmlelement(IMUSANT_tags::repeat);
			xmlrepeat->add(new_xmlattribute(IMUSANT_attributes::direction, IMUSANT_repeat::xml(elt->repeat()->getDirection())));
			if (elt->repeat()->getTimes()>1)
				xmlrepeat->add(new_xmlattribute(IMUSANT_attributes::times, elt->repeat()->getTimes()));
			xmlelt->add(xmlrepeat);
		}
		
		add(xmlelt);
	}
}

#pragma mark IMUSANT_chord handler
void IMUSANT_XMLVisitor::visit ( S_IMUSANT_chord& elt )
{
	Sxmlelement xmlelt = new_xmlelement(IMUSANT_tags::chord);
	push (xmlelt);
	fInChord = true;
	elt->getNotes().accept(*this);
	fInChord = false;
	pop();
}

#pragma mark IMUSANT_comment handler
void IMUSANT_XMLVisitor::visit ( S_IMUSANT_comment& elt )
{
	cout << "COMMENT" << endl;
}

#pragma mark IMUSANT_element handler
void IMUSANT_XMLVisitor::visit ( S_IMUSANT_element& elt )
{
	cout << "ELEMENT" << endl;
}

#pragma mark IMUSANT_lyric handler
//This is the only way to safely handle this type, don't try to handle in note.
void IMUSANT_XMLVisitor::visit ( S_IMUSANT_lyric& elt )
{
	Sxmlelement xmllyric = new_xmlelement(IMUSANT_tags::lyric);
	xmllyric->add(new_xmlattribute(IMUSANT_attributes::number, elt->getNumber()));
	//set syllabic flag
	xmllyric->add(new_xmlelement(IMUSANT_tags::syllabic, IMUSANT_syllabic::xml(elt->getSyllabic())));
	
	CONTAINER_TYPE::const_iterator syllable = elt->getSyllables().begin();
	//this picks up multisyllables - different structure to MusicXML library
	while (syllable!=elt->getSyllables().end())
	{
		xmllyric->add(new_xmlelement(IMUSANT_tags::text, *syllable));
		syllable++;
		if (syllable==elt->getSyllables().end()) break;
		else xmllyric->add(new_xmlelement(IMUSANT_tags::elision));
	} 
	//assume we are in note		
	add(xmllyric);
}

#pragma mark IMUSANT_measure handler
void IMUSANT_XMLVisitor::visit ( S_IMUSANT_measure& elt )
{
	Sxmlelement xmlmeasure = new_xmlelement(IMUSANT_tags::measure);
	
	xmlmeasure->add(new_xmlattribute(IMUSANT_attributes::number, elt->getMeasureNum()));
	push(xmlmeasure);
	//clef: only insert valid clefs
	if (elt->getClef().isDefined())
	{
		Sxmlelement xmlclef = new_xmlelement(IMUSANT_tags::clef);
		xmlclef->add(new_xmlelement(IMUSANT_tags::clef_sign, string(1, elt->getClef().getSign())));
		xmlclef->add(new_xmlelement(IMUSANT_tags::clef_line, elt->getClef().getLine()));
		xmlclef->add(new_xmlelement(IMUSANT_tags::clef_transpose, elt->getClef().getTransposition()));
		xmlmeasure->add(xmlclef);
	}
	//key
	if (elt->getKey().isDefined())
	{
		//only output non-default values
		Sxmlelement xmlkey = new_xmlelement(IMUSANT_tags::key);
		if (elt->getKey().getFifths())
			xmlkey->add(new_xmlelement(IMUSANT_tags::key_fifths, elt->getKey().getFifths()));
		if (elt->getKey().getMode()!=IMUSANT_key::generic)
			xmlkey->add(new_xmlelement(IMUSANT_tags::mode, IMUSANT_key::xmlmode(elt->getKey().getMode())));
		if (elt->getKey().getCancel())
			xmlkey->add(new_xmlelement(IMUSANT_tags::key_cancel, elt->getKey().getCancel()));
		xmlmeasure->add(xmlkey);
	}
	//time
	if (elt->getTime().isMeasured()) //no time sign output for unmeasured measures
	{
		Sxmlelement xmltime = new_xmlelement(IMUSANT_tags::time);
		if (elt->getTime().getSymbol()!=IMUSANT_time::undefined)
			xmltime->add(new_xmlattribute(IMUSANT_attributes::time_symbol, IMUSANT_time::xmlsymbol(elt->getTime().getSymbol())));
		stringstream s, t;
		vector<long>::const_iterator i;
		if (!elt->getTime().getNumerator().empty())
		{
			i=elt->getTime().getNumerator().begin();
			while (	i != elt->getTime().getNumerator().end() )
			{
				s << (*i);
				if (++i != elt->getTime().getNumerator().end()) s << "+";
			}
			xmltime->add(new_xmlelement(IMUSANT_tags::time_numerator, s.str()));
		}
		if (!elt->getTime().getDenominator().empty())
		{
			i = elt->getTime().getDenominator().begin();
			while (i != elt->getTime().getDenominator().end())
			{
				t << (*i);
				if (++i!=elt->getTime().getDenominator().end()) t << "+";
			}
			xmltime->add(new_xmlelement(IMUSANT_tags::time_denominator, t.str() ));
		}
		xmlmeasure->add(xmltime);
	}
	elt->elements().accept(*this);
	
	pop();
}

#pragma mark IMUSANT_note handler
void IMUSANT_XMLVisitor::visit ( S_IMUSANT_note& elt )
{
	Sxmlelement xmlelt = new_xmlelement(IMUSANT_tags::note);
	xmlelt->add(new_xmlattribute(IMUSANT_attributes::number, elt->getNoteIndex()));
	if (elt->isNotNormal())
		xmlelt->add(new_xmlattribute(IMUSANT_attributes::notestyle, IMUSANT_NoteStyle::xml(elt->getStyle())));
	
	//use internal type variable to set tag, then fill if pitch, otherwise will set as rest or unpitched.
	Sxmlelement xmlpitch = new_xmlelement(IMUSANT_NoteType::xml(elt->getType())); //IMUSANT_tags::pitch
	if (elt->getType()==IMUSANT_NoteType::pitch)
	{
		xmlpitch->add(new_xmlelement(IMUSANT_tags::pitch_name, IMUSANT_pitch::xml(elt->pitch()->name())));
		if (elt->pitch()->alteration()!=0)
			xmlpitch->add(new_xmlelement(IMUSANT_tags::pitch_alter, elt->pitch()->alteration()));
		xmlpitch->add(new_xmlelement(IMUSANT_tags::pitch_octave, elt->pitch()->octave()));
		if (elt->pitch()->voice()!=1) //voice 1 is default
			xmlpitch->add(new_xmlelement(IMUSANT_tags::voice, elt->pitch()->voice()));
	}
	xmlelt->add(xmlpitch);
	//accidental sign
	if(elt->accidental())
	{
		Sxmlelement xmlacc = new_xmlelement(IMUSANT_tags::accidental, elt->accidental()->xml(elt->accidental()->getAccident()));
		if (elt->accidental()->getCautionary() != YesNo::undefined)
			xmlacc->add (new_xmlattribute(IMUSANT_attributes::cautionary, YesNo::xml(elt->accidental()->getCautionary())));
		if (elt->accidental()->getEditorial() != YesNo::undefined)
			xmlacc->add (new_xmlattribute(IMUSANT_attributes::editorial, YesNo::xml(elt->accidental()->getEditorial())));
		if (elt->accidental()->getCancelling() != YesNo::undefined)
			xmlacc->add (new_xmlattribute(IMUSANT_attributes::cancelling, YesNo::xml(elt->accidental()->getCancelling())));

		xmlelt->add(xmlacc);
	}
	//add other elements as implemented; only non-default values written
	Sxmlelement xmldur = new_xmlelement(IMUSANT_tags::duration);
	xmldur->add(new_xmlelement(IMUSANT_tags::duration_type, IMUSANT_duration::xml(elt->duration()->fDuration)));
	if (elt->duration()->fDots)
		xmldur->add(new_xmlelement(IMUSANT_tags::dots, elt->duration()->fDots));
	if (elt->duration()->fTimeModification!=TRational(1,1))
		xmldur->add(new_xmlelement(IMUSANT_tags::time_modification, elt->duration()->fTimeModification.toString()));
	xmlelt->add(xmldur);
	
	if (!elt->isSingle())
	{
		Sxmlelement xmltie = new_xmlelement(IMUSANT_tags::tie);
		if (elt->isTiedNext()) 
		{
			xmltie->add(new_xmlattribute(IMUSANT_attributes::tie_type, IMUSANT_attributes::start));
			xmltie->add(new_xmlattribute(IMUSANT_attributes::tie_to_measure, elt->getNextTieNote()->getMeasureNum()));
			xmltie->add(new_xmlattribute(IMUSANT_attributes::tie_to_noteindex, elt->getNextTieNote()->getNoteIndex()));
		}
		
		if (elt->isTiedPrevious()) 
		{
			xmltie->add(new_xmlattribute(IMUSANT_attributes::tie_type, IMUSANT_attributes::end));
			xmltie->add(new_xmlattribute(IMUSANT_attributes::tie_from_measure, elt->getPreviousTieNote()->getMeasureNum()));
			xmltie->add(new_xmlattribute(IMUSANT_attributes::tie_from_noteindex, elt->getPreviousTieNote()->getNoteIndex()));
		}
		
		xmlelt->add(xmltie);
	}
	push(xmlelt);
	
	elt->lyrics().accept(*this);
	
	pop();
	
}

#pragma mark IMUSANT part handler
void IMUSANT_XMLVisitor::visit ( S_IMUSANT_part& elt )
{
	Sxmlelement xmlelt = new_xmlelement(IMUSANT_tags::part);
	
	xmlelt->add(new_xmlattribute(IMUSANT_tags::partid, elt->getID()));
	if (!elt->getPartName().empty())
		xmlelt->add(new_xmlelement(IMUSANT_tags::partname, elt->getPartName()));
	if (!elt->getPartAbbrev().empty())
		xmlelt->add(new_xmlelement(IMUSANT_tags::partabbrev, elt->getPartAbbrev()));
	push(xmlelt);
	
	elt->measures().accept(*this);
	
	pop();
}

#pragma mark IMUSANT_partlist handler	
void IMUSANT_XMLVisitor::visit ( S_IMUSANT_partlist& elt )
{
	Sxmlelement xmlelt = new_xmlelement(IMUSANT_tags::partlist);
	add(xmlelt);
	elt->parts().accept(*this);
}

#pragma mark IMUSANT_score handler	
void IMUSANT_XMLVisitor::visit ( S_IMUSANT_score& elt )
{
	Sxmlelement xmlelt = new_xmlelement(IMUSANT_tags::score);
	
	start(xmlelt);

	if (!elt->getWorkTitle().empty())
		xmlelt->add(new_xmlelement(IMUSANT_tags::work_title, elt->getWorkTitle()));
	if (!elt->getWorkNum().empty())
		xmlelt->add(new_xmlelement(IMUSANT_tags::work_num, elt->getWorkNum()));
	if (!elt->getMovementTitle().empty())
		xmlelt->add(new_xmlelement(IMUSANT_tags::movt_title, elt->getMovementTitle()));
	if (!elt->getMovementNum().empty())
		xmlelt->add(new_xmlelement(IMUSANT_tags::movt_num, elt->getMovementNum()));
	if (!elt->getCreator().empty())
	{
		STRPAIRVECTOR::const_iterator i;
		for (i=elt->getCreator().begin();i!=elt->getCreator().end();i++)
		{
			Sxmlelement xmlcreator = new_xmlelement(IMUSANT_tags::creator, i->second);
			xmlcreator->add(new_xmlattribute(IMUSANT_attributes::type, i->first));
			xmlelt->add(xmlcreator);
		}
	}
	if (!elt->getRights().empty())
	{
		STRPAIRVECTOR::const_iterator j;
		for (j=elt->getRights().begin();j!=elt->getRights().end();j++)
		{
			Sxmlelement xmlrights = new_xmlelement(IMUSANT_tags::rights, j->second);
			if (!j->first.empty()) xmlrights->add(new_xmlattribute(IMUSANT_attributes::type, j->first));
			xmlelt->add(xmlrights);
		}
	}
	if (!elt->getComments().empty())
		xmlelt->add(new_xmlelement(IMUSANT_tags::score_comments, elt->getComments()));
	if (!elt->getSource().empty())
		xmlelt->add(new_xmlelement(IMUSANT_tags::source, elt->getSource()));
	if (!elt->getEditor().empty())
		xmlelt->add(new_xmlelement(IMUSANT_tags::editor, elt->getEditor()));
	if (!elt->getDate().empty())
		xmlelt->add(new_xmlelement(IMUSANT_tags::date, elt->getDate()));
	
	if ((IMUSANT_partlist*)elt->partlist())
		elt->partlist()->accept(*this);
	
}

}//namespace IMUSANT
