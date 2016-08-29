/*
  Copyright © Grame 2003

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.
    
    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.
    
    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Grame Research Laboratory, 9, rue du Garet 69001 Lyon - France
    grame@grame.fr

*/

#ifdef WIN32
#pragma warning (disable : 4786)
#endif

#include <sstream>
#include <iostream>

#define debug	// cout << "visite " << __LINE__ << endl; fflush(stdout);

#include "IMusicXMLVisitor.h"
#include "LibMusicXML.h"
#include "xml.h"

using namespace MusicXML;

namespace MusicXML 
{

//________________________________________________________________________
TMusicXMLVisitor::TMusicXMLVisitor() { fInChord = false; }

//________________________________________________________________________
/*!
	The MusicXMl definition of an \e accidental element is as follow:
\n \verbatim
<!ELEMENT accidental (#PCDATA)>
<!ATTLIST accidental
    cautionary %yes-no; #IMPLIED
    editorial %yes-no; #IMPLIED
    size (full | cue) #IMPLIED
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SAccidental& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("accidental", elt->xmlaccidental(elt->getAccident()));
	if (elt->getCautionary() != YesNo::undefined)
		xmlelt->add (new_xmlattribute("cautionary", YesNo::xml(elt->getCautionary())));
	if (elt->getEditorial() != YesNo::undefined)
		xmlelt->add (new_xmlattribute("editorial", YesNo::xml(elt->getEditorial())));
	if (elt->getSize() != FullCue::undefined)
		xmlelt->add (new_xmlattribute("size", FullCue::xml(elt->getSize())));
	add(xmlelt);
}

//________________________________________________________________________
/*!
	The MusicXML description of an \e arpeggiate element is as follow:
\n \verbatim
<!ELEMENT arpeggiate EMPTY>
<!ATTLIST arpeggiate
    number %number-level; #IMPLIED
    direction %up-down; #IMPLIED
    %position; 
    %placement; 
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SArpeggiate& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("arpeggiate");
	push(xmlelt);
	if (elt->getNumber() != TArpeggiate::undefined)
		xmlelt->add (new_xmlattribute("number", elt->getNumber()));
	switch (elt->getDirection()) {
		case TArpeggiate::up:
			xmlelt->add (new_xmlattribute("direction", "up"));
			break;
		case TArpeggiate::down:
			xmlelt->add (new_xmlattribute("direction", "down"));
			break;
		default:
			;
	}
	elt->position().accept(*this);
	elt->placement().accept(*this);
	pop();
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e non-arpeggiate element is as follow:
\n \verbatim
<!ELEMENT non-arpeggiate EMPTY>
<!ATTLIST non-arpeggiate
    type %top-bottom; #REQUIRED
    number %number-level; #IMPLIED
    %position; 
    %placement; 
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SNonArpeggiate& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("non-arpeggiate");
	push(xmlelt);
	switch (elt->getType()) {
		case TNonArpeggiate::top:
			xmlelt->add (new_xmlattribute("type", "top"));
			break;
		case TNonArpeggiate::bottom:
			xmlelt->add (new_xmlattribute("type", "bottom"));
			break;
		default:
			;
	}
	if (elt->getNumber() != TNonArpeggiate::undefined)
		xmlelt->add (new_xmlattribute("number", elt->getNumber()));
	elt->position().accept(*this);
	elt->placement().accept(*this);
	pop();
}

//________________________________________________________________________
void TMusicXMLVisitor::visite ( SArticulationElement& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement(elt->xmlname(elt->getArtType()));
	push(xmlelt);
	elt->position().accept(*this);
	elt->placement().accept(*this);
	pop();
}

//________________________________________________________________________
/*!
	The MusicXML description of an \e articulations element is as follow:
\n \verbatim
<!ELEMENT articulations
	((accent | strong-accent | staccato | tenuto |
	  detached-legato | staccatissimo | spiccato |
	  scoop | plop | doit | falloff | breath-mark | 
	  caesura | other-articulation)*)>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SArticulations& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("articulations");
	push(xmlelt);
	elt->articulations().accept(*this);
	pop();
}

//________________________________________________________________________
/*!
	The MusicXML description of an \e attributes element is as follow:
\n \verbatim
<!ELEMENT attributes (%editorial;, divisions?, key?, time?,
	staves?, instruments?, clef*, staff-details*, transpose?,
	directive*, measure-style*)>
\endverbatim
\note editorial information is ignored
*/
void TMusicXMLVisitor::visite ( SAttributes& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("attributes");
	push(xmlelt);
	elt->editorial().accept(*this);

    if (elt->getDivision() != TAttributes::undefined)
        xmlelt->add (new_xmlelement("divisions", elt->getDivision()));

    if ((TKey *)elt->key()) 			elt->key()->accept(*this);
    if ((TTimeSign*)elt->timeSign()) 	elt->timeSign()->accept(*this);

    if (elt->getStaves() != TAttributes::undefined)
        xmlelt->add (new_xmlelement("staves", elt->getStaves()));
	if (elt->getInstrument() != 1)
        xmlelt->add (new_xmlelement("instruments", elt->getInstrument()));

    elt->clefs().accept(*this);
    if ((TStaffDetails *)elt->staffDetails()) 	elt->staffDetails()->accept(*this);
    if ((TTranspose *)elt->transpose()) 	elt->transpose()->accept(*this);
    if ((TDirective *)elt->directive()) 	elt->directive()->accept(*this);
    if ((TMeasureStyle *)elt->measureStyle()) 	elt->measureStyle()->accept(*this);
    pop();
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e backup element is as follow:
\n \verbatim
<!ELEMENT backup (duration, %editorial;)>
\endverbatim
\note editorial information is ignored
*/
void TMusicXMLVisitor::visite ( SBackup& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("backup");
    xmlelt->add (new_xmlelement("duration", elt->getDuration()));
	push(xmlelt);
	elt->editorial().accept(*this);
	pop();
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e barline element is as follow:
\n \verbatim
<!ELEMENT barline (bar-style?, %editorial;, wavy-line?, segno?,
	coda?, (fermata, fermata?)?, ending?, repeat?)>
<!ATTLIST barline
    location (right | left | middle) "right"
>
\endverbatim
\note \e editorial entity is ignored
*/
void TMusicXMLVisitor::visite ( SBarline& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("barline");
    xmlelt->add (new_xmlattribute("location", elt->xmllocation(elt->getLocation())));
    if (elt->getBarStyle() != TBarline::undefined) 
        xmlelt->add (new_xmlelement("bar-style", elt->xmlstyle(elt->getBarStyle())));

	push(xmlelt);
	elt->editorial().accept(*this);
    if ((TWavyLine*)elt->wavyLine()) 	elt->wavyLine()->accept(*this);
    if ((TSegno *)elt->segno()) 		elt->segno()->accept(*this);
    if ((TCoda *)elt->coda()) 			elt->coda()->accept(*this);
    if ((TFermata *)elt->fermata()) 	elt->fermata()->accept(*this);
    if ((TEnding *)elt->ending()) 		elt->ending()->accept(*this);
    if ((TRepeat *)elt->repeat()) 		elt->repeat()->accept(*this);
	pop();
}

//________________________________________________________________________
void TMusicXMLVisitor::noteAttributes ( SNote& elt ) { debug
	// adds the note position
	elt->position().accept(*this);
	if (elt->graphics())
		elt->graphics()->printout().accept(*this);
	// adds the remaining attributes to the element
	if ((TExpression *)elt->expression())
		elt->expression()->accept(*this);
}

//________________________________________________________________________
void TMusicXMLVisitor::normalNote ( SNote& note ) { debug
	addFullNote(note);
	addDuration(note);
	addTies(note);
}

//________________________________________________________________________
void TMusicXMLVisitor::cueNote ( SNote& note ) { debug
	Sxmlelement xml = new_xmlelement("cue");
	add (xml);
	addFullNote(note);
	addDuration(note);
}

//________________________________________________________________________
void TMusicXMLVisitor::graceNote ( SNote& note ) { debug
	if ((TGraceNote *)note->graceNote())
		note->graceNote()->accept(*this);
	addFullNote(note);
	addTies(note);
}

//______________________________________________________________________________
/*!
	The MusicXMl definition of the \e full-note entity is as follow:
\n \verbatim
<!ENTITY % full-note "(chord?, (pitch | unpitched | rest))">
\endverbatim
*/
void TMusicXMLVisitor::addFullNote (SNote& note) { debug
	if (fInChord) {
		Sxmlelement xml = new_xmlelement("chord");
		add (xml);
	}
	// unpitched and rest classes inherit from TPitch and thus specific xml output
	// is covered by the overloaded xml method.
	if((TPitch *)note->pitch()) note->pitch()->accept (*this);
}

//______________________________________________________________________________
void TMusicXMLVisitor::addDuration (SNote& note) { debug
	Sxmlelement xml = new_xmlelement("duration", note->getDuration());
	add (xml);
}

//______________________________________________________________________________
void TMusicXMLVisitor::addTies (SNote& note) { debug
	Sxmlelement tie;
	if ((TNote*)note->tiePrevious()) {
		tie = new_xmlelement("tie");
		tie->add (new_xmlattribute("type", "stop"));
		add (tie);
	}
	if ((TNote*)note->tieNext()) {
		tie = new_xmlelement("tie");
		tie->add (new_xmlattribute("type", "start"));
		add (tie);
	}
}

//______________________________________________________________________________
/*!
	Parts common to grace, normal and cue notes are as follow:
\n \verbatim
<!ELEMENT note 
   (...,
	instrument?, %editorial-voice;, type?, dot*,
	accidental?, time-modification?, stem?, notehead?,
	staff?, beam*, notations*, lyric*)
>
\endverbatim
\todo lyric support
*/
void TMusicXMLVisitor::addCommon (SNote& note) { debug
	string id = note->getInstrumentID();
	if (!id.empty()) {
		Sxmlelement xml = new_xmlelement("instrument");
		xml->add(new_xmlattribute("id", id));
		add(xml);
	}
	// remaining parts are in charge of SGraphNote
	if ((TGraphNote *)note->graphics())
		note->graphics()->accept (*this);
}

//________________________________________________________________________
/*!
	The MusicXMl definition of an \e beam element is as follow:
\n \verbatim
<!ELEMENT beam (#PCDATA)>
<!ATTLIST beam
    number %beam-level; "1"
    repeater %yes-no; #IMPLIED
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SBeam& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("beam", elt->xmlbeamtype(elt->getType()));

	if (elt->getNumber() != TBeam::undefined)
		xmlelt->add (new_xmlattribute("number", elt->getNumber()));
	if (elt->getRepeater() != YesNo::undefined)
		xmlelt->add (new_xmlattribute("repeater", YesNo::xml(elt->getRepeater())));
	add(xmlelt);
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e bracket element is as follow:
\n \verbatim
<!ELEMENT bracket EMPTY>
<!ATTLIST bracket
    type %start-stop; #REQUIRED
    number %beam-level; #IMPLIED
    line-end (up | down | both | arrow | none) #REQUIRED
    %line-type;
    %position; 
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SBracket& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("bracket");
	push(xmlelt);

    xmlelt->add(new_xmlattribute ("type", StartStop::xml(elt->getType())));
    if (elt->getNumber() != TBracket::undefined)
        xmlelt->add(new_xmlattribute ("number", elt->getNumber()));
    xmlelt->add(new_xmlattribute ("line-end", elt->xmllineend(elt->getLineEnd())));
    if (elt->getLineType() != LineType::undefined)
        xmlelt->add(new_xmlattribute ("line-type", LineType::xml(elt->getLineType())));
    elt->position().accept (*this);
	pop();
}

//________________________________________________________________________
/*!
	Chord is not a MusicXML element. It is denoted by individual note
	membership.
\endverbatim
*/
void TMusicXMLVisitor::visite ( SChord& elt ) { debug
	elt->sort(TChord::duration);
	vvector<SNote>::const_iterator note = elt->notes().begin();
	if (note == elt->notes().end()) return;
	(*note)->accept(*this);
	fInChord = true;
	for (note++; note!=elt->notes().end(); note++) {
		(*note)->accept(*this);
	}
	fInChord = false;
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e clef element is as follow:
\n \verbatim
<!ELEMENT clef (sign, line?, clef-octave-change?)>
<!ATTLIST clef
	number CDATA #IMPLIED
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SClef& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("clef");
	add(xmlelt);
    if (elt->getStaffNum() != TClef::undefined)
        xmlelt->add (new_xmlattribute("number", elt->getStaffNum()));
    xmlelt->add (new_xmlelement("sign", elt->xmlsign(elt->getSign())));
    if (elt->getLine() != TClef::undefined)
        xmlelt->add (new_xmlelement("line", elt->getLine()));
    if (elt->getOctave())
        xmlelt->add (new_xmlelement("clef-octave-change", elt->getOctave()));
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e coda element is as follow:
\n \verbatim
<!ELEMENT coda EMPTY>
<!ATTLIST coda %position; >
\endverbatim
*/
void TMusicXMLVisitor::visite ( SCoda& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("coda");
	push(xmlelt);
    elt->position().accept (*this);
	pop();
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e creator element is as follow:
\n \verbatim
<!ELEMENT creator (#PCDATA)>
<!ATTLIST creator
    type CDATA #IMPLIED
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SCreator& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("creator", elt->getName());
    string type = elt->getType();
	if (!type.empty())
        xmlelt->add (new_xmlattribute("type", type));
	add(xmlelt);
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e dashes element is as follow:
\n \verbatim
<!ELEMENT dashes EMPTY>
<!ATTLIST dashes
    type %start-stop; #REQUIRED
    number %beam-level; #IMPLIED
    %position; 
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SDashes& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("dashes");
	push(xmlelt);
    xmlelt->add(new_xmlattribute ("type", StartStop::xml(elt->getType())));
    if (elt->getNumber() != TDashes::undefined)
        xmlelt->add(new_xmlattribute ("number", elt->getNumber()));
    elt->position().accept (*this);
	pop();
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e degree element is as follow:
\n \verbatim
<!ELEMENT degree (degree-value, degree-alter, degree-type)>
<!ELEMENT degree-value (#PCDATA)>
<!ELEMENT degree-alter (#PCDATA)>
<!ELEMENT degree-type (#PCDATA)>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SDegree& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("degree");
	push(xmlelt);
	xmlelt = new_xmlelement("degree-value", elt->getValue());
	add(xmlelt);
	xmlelt = new_xmlelement("degree-alter", elt->getAlter());
	add(xmlelt);
	xmlelt = new_xmlelement("degree-type", elt->getType());
	add(xmlelt);
	pop();
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e direction element is as follow:
\n \verbatim
<!ELEMENT direction (direction-type+, offset?,
	%editorial-voice;, staff?, sound?)>
<!ATTLIST direction
    %placement; 
>
\endverbatim
\note only voice is supported from the \e editorial-voice entity
*/
void TMusicXMLVisitor::visite ( SDirection& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("direction");
	push(xmlelt);

    elt->placement().accept(*this);
	elt->types().accept(*this);

	if (elt->getOffset() != 0)
        xmlelt->add (new_xmlelement("offset", elt->getOffset()));
	elt->editorial().accept(*this);
    if (elt->getVoice() != TDirection::undefined)
        xmlelt->add (new_xmlelement("voice", elt->getVoice()));
    if (elt->getStaff() != TDirection::undefined)
        xmlelt->add (new_xmlelement("staff", elt->getStaff()));
    if ((TSound *)elt->sound())
        elt->sound()->accept(*this);
	pop();
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e direction-type element is as follow:
\n \verbatim
<!ELEMENT direction-type (rehearsal+ | segno+ | words+ |
	coda+ | wedge | dynamics+ | dashes | bracket | pedal | 
	metronome | octave-shift | damp | damp-all | 
	eyeglasses | other-direction)>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SDirectionType& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("direction-type");
	push(xmlelt);
	elt->elements().accept(*this);
	pop();
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e directive element is as follow:
\n \verbatim
<!ELEMENT directive (#PCDATA)>
<!ATTLIST directive
	%font;
	xml:lang NMTOKEN #IMPLIED
>
\endverbatim
\todo support of the \e font entity
*/
void TMusicXMLVisitor::visite ( SDirective& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("directive", elt->getValue());
	push(xmlelt);
	elt->font().accept(*this);
	string str = elt->getLang();
    if (!str.empty())
        xmlelt->add (new_xmlattribute("xml:lang", str));
	pop();
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e dynamics element is as follow:
\n \verbatim
<!ELEMENT dynamics ((p | pp | ppp | pppp | ppppp | pppppp |
	f | ff | fff | ffff | fffff | ffffff | mp | mf | sf |
	sfp | sfpp | fp | rf | rfz | sfz | sffz | fz | 
	other-dynamics)*)>
<!ATTLIST dynamics
    %position; 
    %placement; 
    %font;
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SDynamic& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("dynamics");
	push(xmlelt);
    elt->position().accept (*this);
    elt->placement().accept (*this);
    elt->font().accept (*this);

    vector<TDynamic::dynamic>::const_iterator iter;
    for (iter = elt->dynamics().begin(); iter != elt->dynamics().end(); iter++) {
        xmlelt->add(new_xmlelement(elt->xmldynamic(*iter)));
    }
	pop();
}

//________________________________________________________________________
/*!
	The MusicXML description of an \e encoding element is as follow:
\n \verbatim
<!ELEMENT encoding ((encoding-date | encoder | software |
	encoding-description | supports)*)>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SEncoding& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("encoding");
	push(xmlelt);
	
	string str;
	str = elt->getDate();
    if (!str.empty()) {
		Sxmlelement xml = new_xmlelement("encoding-date", str);
		add (xml);
	}
	str = elt->getEncoder();
    if (!str.empty()) {
        Sxmlelement encoder = new_xmlelement("encoder", str);
		str = elt->getEncoderType();
        if (!str.empty())
            encoder->add (new_xmlattribute("type", str));
        add (encoder);
    }

	str = elt->getSoftware();
    if (!str.empty())  {
		Sxmlelement xml = new_xmlelement("software", str);
		add (xml);
	}
	str = elt->getDescription();
    if (!str.empty()) {
		Sxmlelement xml = new_xmlelement("encoding-description", str);	
		add (xml);	
	}
	elt->support().accept(*this);
	pop();
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e ending element is as follow:
\n \verbatim
<!ELEMENT ending EMPTY>
<!ATTLIST ending
    number CDATA #REQUIRED
    type (start | stop | discontinue) #REQUIRED
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SEnding& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("ending");
    xmlelt->add (new_xmlattribute("number", elt->getNum()));
    xmlelt->add (new_xmlattribute("type", elt->xmltype(elt->getType())));
	add(xmlelt);
}

//________________________________________________________________________
/*!
	This method handles a subset of a \e note element attributes.
	They are defined as follow:
\n \verbatim
<!ATTLIST note
    %position; 				// ignored by the method
    %printout; 				// ignored by the method
    dynamics CDATA #IMPLIED
    end-dynamics CDATA #IMPLIED
    attack CDATA #IMPLIED
    release CDATA #IMPLIED
    pizzicato %yes-no; #IMPLIED
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SExpression& elt ) { debug
	if (elt->getDynamic() != TExpression::undefined)
		current()->add (new_xmlattribute("dynamics", elt->getDynamic()));
	if (elt->getEndDynamic() != TExpression::undefined)
		current()->add (new_xmlattribute("end-dynamics", elt->getEndDynamic()));
	if (elt->getAttack() != TExpression::undefined)
		current()->add (new_xmlattribute("attack", elt->getAttack()));
	if (elt->getRelease() != TExpression::undefined)
		current()->add (new_xmlattribute("release", elt->getRelease()));
	if (elt->getPizzicato() != YesNo::undefined)
		current()->add (new_xmlattribute("pizzicato", YesNo::xml(elt->getPizzicato())));
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e feature element is as follow:
\n \verbatim
<!ELEMENT feature (#PCDATA)>
<!ATTLIST feature
    type CDATA #IMPLIED
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SFeature& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("feature", elt->getData());
    if (!elt->getType().empty())
        xmlelt->add (new_xmlattribute ("type", elt->getType()));
	add(xmlelt);
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e grouping element is as follow:
\n \verbatim
<!ELEMENT grouping ((feature)*)>
<!ATTLIST grouping
    type %start-stop; #REQUIRED
    number CDATA "1"
    member-of CDATA #IMPLIED
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SGrouping& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("grouping");
	xmlelt->add (new_xmlattribute ("type", StartStop::xml(elt->getType())));
    if (elt->getNumber() != TGrouping::undefined)
        xmlelt->add (new_xmlattribute ("number", elt->getNumber()));
    if (!elt->getMemberOf().empty())
        xmlelt->add (new_xmlattribute ("member-of", elt->getMemberOf()));
	push(xmlelt);
    elt->getFeatures().accept (*this);
	pop();
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e fermata element is as follow:
\n \verbatim
<!ELEMENT fermata EMPTY>
<!ATTLIST fermata
    type (upright | inverted) #IMPLIED
    %position; 
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SFermata& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("fermata");
	int type = elt->getType();
    if (type != TFermata::undefined)
        xmlelt->add (new_xmlattribute ("type", elt->xmltype(type)));
	push(xmlelt);
    elt->position().accept (*this);
	pop();
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e figure element is as follow:
\n \verbatim
<!ELEMENT figure (prefix?, figure-number?, suffix?)>
<!ELEMENT prefix (#PCDATA)>
<!ELEMENT figure-number (#PCDATA)>
<!ELEMENT suffix (#PCDATA)>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SFigure& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("figure");
    if (!elt->getPrefix().empty())
        xmlelt->add (new_xmlelement ("prefix", elt->getPrefix()));
    if (!elt->getNumber().empty())
        xmlelt->add (new_xmlelement ("figure-number", elt->getNumber()));
    if (!elt->getSuffix().empty())
        xmlelt->add (new_xmlelement ("suffix", elt->getSuffix()));
	add(xmlelt);
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e figured-bass element is as follow:
\n \verbatim
<!ELEMENT figured-bass (figure+, duration?, %editorial;)>
<!ATTLIST figured-bass
    %position; 
    %printout;
>
\endverbatim
\todo editorial support
*/
void TMusicXMLVisitor::visite ( SFiguredBass& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("figured-bass");
	push(xmlelt);
    elt->position().accept (*this);
	elt->printout().accept (*this);
	elt->figures().accept (*this);
	long d = elt->getDuration();
	if (d != TFiguredBass::undefined)
		xmlelt->add (new_xmlelement("duration", d));
	elt->editorial().accept(*this);
	pop();
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e fingering element is as follow:
\n \verbatim
<!ELEMENT fingering (#PCDATA)>
<!ATTLIST fingering
    substitution (yes | no) #IMPLIED
    alternate (yes | no) #IMPLIED
    %position; 
    %placement;
    %font;
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SFingering& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("fingering", elt->getData());
	push (xmlelt);
	if (elt->getSubstitution() != YesNo::undefined)
		xmlelt->add (new_xmlattribute("substitution", YesNo::xml(elt->getSubstitution())));
	if (elt->getAlternate() != YesNo::undefined)
		xmlelt->add (new_xmlattribute("alternate", YesNo::xml(elt->getAlternate())));
	elt->position().accept(*this);
	elt->placement().accept(*this);
	elt->font().accept(*this);
	pop();
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e forward element is as follow:
\n \verbatim
<!ELEMENT forward (duration, %editorial-voice;, staff?)>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SForward& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("forward");

	push(xmlelt);
    xmlelt->add (new_xmlelement("duration", elt->getDuration()));
	elt->editorial().accept(*this);
    if (elt->getVoice() != TForward::undefined)
        xmlelt->add (new_xmlelement("voice", elt->getVoice()));
    if (elt->getStaff() != TForward::undefined)
        xmlelt->add (new_xmlelement("staff", elt->getStaff()));
	pop();
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e frame element is as follow:
\n \verbatim
<!ELEMENT frame 
	(frame-strings, frame-frets, first-fret?, frame-note+)>
<!ELEMENT frame-strings (#PCDATA)>
<!ELEMENT frame-frets (#PCDATA)>
<!ELEMENT first-fret (#PCDATA)>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SFrame& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("frame");
	push(xmlelt);
	xmlelt = new_xmlelement("frame-strings", elt->getStrings());
	add(xmlelt);
	xmlelt = new_xmlelement("frame-frets", elt->getFrets());
	add(xmlelt);
	if (elt->getFirstFret() != TFrame::undefined) {
		xmlelt = new_xmlelement("first-fret", elt->getFirstFret());
		add(xmlelt);
	}
	elt->frameNotes().accept(*this);
	pop();
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e frame-note element is as follow:
\n \verbatim
<!ELEMENT frame-note (string, fret, fingering?)>
<!ELEMENT fret (#PCDATA)>
<!ELEMENT string (#PCDATA)>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SFrameNote& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("frame-note");
	push(xmlelt);
	xmlelt = new_xmlelement("string", elt->getString());
	add(xmlelt);
	xmlelt = new_xmlelement("fret", elt->getFret());
	add(xmlelt);
	if (elt->fingering()) elt->fingering()->accept(*this);
	pop();
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e function element is as follow:
\n \verbatim
<!ELEMENT function (#PCDATA)>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SFunction& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("function", elt->getFunction());
	add(xmlelt);
}

//________________________________________________________________________
/*!
	The MusicXMl definition of an \e grace note element is as follow:
\n \verbatim
<!ELEMENT note 
   (grace, %full-note;, (tie, tie?)?,
    ... )
>
<!ELEMENT grace EMPTY>
<!ATTLIST grace
    steal-time-previous CDATA #IMPLIED
    steal-time-following CDATA #IMPLIED
    make-time CDATA #IMPLIED
    slash %yes-no; #IMPLIED
>
\endverbatim
It ends with elements common to normal, grace and cue notes.
*/
void TMusicXMLVisitor::visite ( SGraceNote& elt ) { debug
	Sxmlelement grace = new_xmlelement("grace");
	if (elt->getStealPrevious() != TGraceNote::undefined)
		grace->add (new_xmlattribute("steal-time-previous", elt->getStealPrevious()));
	if (elt->getStealFollowing() != TGraceNote::undefined)
		grace->add (new_xmlattribute("steal-time-following", elt->getStealFollowing()));
	if (elt->getMakeTime() != TGraceNote::undefined)
		grace->add (new_xmlattribute("make-time", elt->getMakeTime()));
	if (elt->getSlash() != YesNo::undefined)
		grace->add (new_xmlattribute("slash", YesNo::xml(elt->getSlash())));
	add (grace);
}

//________________________________________________________________________
/*!
	The MusicXMl definition of a \e glissando element is as follow:
\n \verbatim
<!ELEMENT glissando EMPTY>
<!ATTLIST glissando
    type %start-stop; #REQUIRED
    number %number-level; "1"
    %line-type; 
    %position; 
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SGlissando& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("glissando");
	push(xmlelt);
    xmlelt->add (new_xmlattribute("type", StartStop::xml(elt->getType())));
	xmlelt->add (new_xmlattribute("number", elt->getNumber()));
    if (elt->getLineType() != LineType::undefined)
        xmlelt->add (new_xmlattribute("line-type", LineType::xml(elt->getLineType())));
    elt->position().accept(*this);
	pop();
}

//________________________________________________________________________
/*!
	The MusicXMl definition of an \e othe-notation element is as follow:
\n \verbatim
<!ELEMENT other-notation (#PCDATA)>
<!ATTLIST other-notation
    type %start-stop; #REQUIRED
    number %number-level; "1"
    %position; 
    %placement;
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SOtherNotation& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("other-notation");
	push(xmlelt);
    xmlelt->add (new_xmlattribute("type", StartStop::xml(elt->getType())));
	xmlelt->add (new_xmlattribute("number", elt->getNumber()));
    elt->position().accept(*this);
    elt->placement().accept(*this);
	pop();
}

//________________________________________________________________________
/*!
	The MusicXMl definition of an \e slide element is as follow:
\n \verbatim
<!ELEMENT slide EMPTY>
<!ATTLIST slide
    type %start-stop; #REQUIRED
    number %number-level; "1"
    %line-type; 
    %position; 
    %bend-sound;
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SSlide& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("slide");
	push(xmlelt);
    xmlelt->add (new_xmlattribute("type", StartStop::xml(elt->getType())));
	xmlelt->add (new_xmlattribute("number", elt->getNumber()));
    if (elt->getLineType() != LineType::undefined)
        xmlelt->add (new_xmlattribute("line-type", LineType::xml(elt->getLineType())));
    elt->position().accept(*this);
    elt->bendSound().accept(*this);
	pop();
}

//________________________________________________________________________
/*!
	This method adds all the elements related to the graphic notation of a note
	ie:
\n \verbatim
<!ELEMENT note 
    ... %editorial-voice;, type?, dot*,
	accidental?, time-modification?, stem?, notehead?,
	staff?, beam*, notations*, lyric*)
>
\endverbatim
\note only \e voice is supported in the \e editorial-voice entity.
*/
void TMusicXMLVisitor::visite ( SGraphNote& elt ) { debug
	Sxmlelement xml;
	elt->editorial().accept(*this);
	if (elt->getVoice() != TGraphNote::undefined) {
		xml = new_xmlelement("voice", elt->getVoice());
		add (xml);
	}
    
    if (elt->getType() != NoteType::undefined) {
        xml = new_xmlelement ("type", NoteType::xml(elt->getType()));
        if (elt->getSize() != FullCue::undefined) 
            xml->add (new_xmlattribute ("size", FullCue::xml(elt->getSize())));
        add (xml);
    }

	unsigned int dots = elt->getDots();	
	while (dots--) {
		xml = new_xmlelement("dot");
		add (xml);
	}

	if ((TAccidental *)elt->accidental())				elt->accidental()->accept (*this);
	if ((TTimeModification *)elt->timemodification())	elt->timemodification()->accept (*this);
	if (elt->getStem() != TGraphNote::undefined) {
		xml = new_xmlelement("stem", elt->xmlstem(elt->getStem()));
		add(xml);
	}
	if ((TNoteHead *)elt->notehead())			elt->notehead()->accept (*this);
	if (elt->getStaff() != TGraphNote::undefined) {
        xml = new_xmlelement("staff", elt->getStaff());
		add(xml);
	}
	elt->beamList().accept(*this);
	elt->notationList().accept(*this);
}

//________________________________________________________________________
/*!
	The MusicXML description of an \e identification element is as follow:
\n \verbatim
<!ELEMENT identification (creator*, rights*, encoding?, source?, miscellaneous?)>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SIdentification& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("identification");
	push(xmlelt);
	elt->creators().accept(*this);
	elt->rights().accept(*this);
    if ((TEncoding *)elt->encoding())
		elt->encoding()->accept(*this);
	string source = elt->getSource();
    if (!source.empty()) {
        Sxmlelement xml = new_xmlelement("source", source);
        add (xml);
	}
	pop();
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e key element is as follow:
\n \verbatim
<!ELEMENT key ((cancel?, fifths, mode?) |
	((key-step, key-alter)*))>
\endverbatim
\todo support of arbitrary keys using key-step and key-alter
*/
void TMusicXMLVisitor::visite ( SKey& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("key");
    if (elt->getCancel())
        xmlelt->add (new_xmlelement("cancel", elt->getCancel()));
    xmlelt->add (new_xmlelement("fifths", elt->getFifths()));
    if (elt->getMode() != TKey::undefined)
        xmlelt->add (new_xmlelement("mode", elt->xmlmode(elt->getMode())));
	add(xmlelt);
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e lyric element is as follow:
\verbatim
<!ELEMENT lyric
	((((syllabic?, text),
	   (elision, syllabic?, text)*, extend?) |
	   extend | laughing | humming),
	  end-line?, end-paragraph?, %editorial;)>
<!ATTLIST lyric
    number NMTOKEN #IMPLIED!= 
    name CDATA #IMPLIED
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SLyric& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("lyric");
	push(xmlelt);
	if (elt->getNumber() != TLyric::undefined)
        xmlelt->add (new_xmlattribute ("number", elt->getNumber()));
	if (!elt->getName().empty())
        xmlelt->add (new_xmlattribute ("name", elt->getName()));

	if (!elt->getText().empty()) {
		if (elt->getSyllabic() != TLyric::undefined)
			xmlelt->add (new_xmlelement("syllabic", TLyric::xmlsyllabic(elt->getSyllabic())));
		Sxmlelement text = new_xmlelement("text", elt->getText());
		push(text);
		elt->font().accept(*this);
		pop();
		elt->getMultipleParts().accept (*this);
		if (elt->getExtend())
			xmlelt->add (new_xmlelement("extend"));
	} else if (elt->getLaughing())
        xmlelt->add (new_xmlelement("laughing"));
	else if (elt->getHumming())
        xmlelt->add (new_xmlelement("humming"));
	else if (elt->getExtend())
        xmlelt->add (new_xmlelement("extend"));
	
	if (elt->getEndLine())
        xmlelt->add (new_xmlelement("end-line"));
	if (elt->getEndParagraph())
        xmlelt->add (new_xmlelement("end-paragraph"));
	elt->editorial().accept(*this);
	pop();
}

//________________________________________________________________________
/*! Multiple lyrics on a single note.

	They are included in the \e lyric element as follow:
\verbatim
	   (elision, syllabic?, text)*
\endverbatim
*/
void TMusicXMLVisitor::visite ( SMultipleLyricPart& elt ) { debug
	current()->add (new_xmlelement("elision"));
	if (elt->getSyllabic() != TLyric::undefined)
		current()->add (new_xmlelement("syllabic", TLyric::xmlsyllabic(elt->getSyllabic())));
	Sxmlelement text = new_xmlelement("text", elt->getText());
	push(text);
	elt->font().accept(*this);
	pop();
}

//________________________________________________________________________
/*!  Multiple rests. 
	They are included in the \e measure-style element as follow:
\verbatim
<!ELEMENT multiple-rest (#PCDATA)>
<!ATTLIST multiple-rest
    use-symbols %yes-no; #IMPLIED
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SMultipleRest& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("multiple-rest", elt->getData());
	if (elt->getUseSymbol() != YesNo::undefined)
		xmlelt->add (new_xmlattribute("use-symbols", YesNo::xml(elt->getUseSymbol())));
	add (xmlelt);
}

//________________________________________________________________________
/*!  Measure repeat element:
\verbatim
<!ELEMENT measure-repeat (#PCDATA)>
<!ATTLIST measure-repeat
    type %start-stop; #REQUIRED
    slashes NMTOKEN #IMPLIED
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SMeasureRepeat& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("measure-repeat", elt->getData());
    xmlelt->add (new_xmlattribute("type", StartStop::xml(elt->getStartStop())));
	if (elt->getSlashes() != TMeasureRepeat::undefined)
		xmlelt->add (new_xmlattribute("slashes", elt->getSlashes()));
	add (xmlelt);
}

//________________________________________________________________________
/*!  Beat repeat element:
\verbatim
<!ELEMENT beat-repeat EMPTY>
<!ATTLIST beat-repeat
    type %start-stop; #REQUIRED
    slashes NMTOKEN #IMPLIED
    use-dots %yes-no; #IMPLIED
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SBeatRepeat& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("beat-repeat");
    xmlelt->add (new_xmlattribute("type", StartStop::xml(elt->getStartStop())));
	if (elt->getSlashes() != TBeatRepeat::undefined)
		xmlelt->add (new_xmlattribute("slashes", elt->getSlashes()));
	if (elt->getUseDots() != YesNo::undefined)
		xmlelt->add (new_xmlattribute("use-dots", YesNo::xml(elt->getUseDots())));
	add (xmlelt);
}

//________________________________________________________________________
/*!  Slash element:
\verbatim
<!ELEMENT slash EMPTY>
<!ATTLIST slash
    type %start-stop; #REQUIRED
    use-dots %yes-no; #IMPLIED
    use-stems %yes-no; #IMPLIED
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SSlash& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("slash");
    xmlelt->add (new_xmlattribute("type", StartStop::xml(elt->getStartStop())));
	if (elt->getUseDots() != YesNo::undefined)
		xmlelt->add (new_xmlattribute("use-dots", YesNo::xml(elt->getUseDots())));
	if (elt->getUseStems() != YesNo::undefined)
		xmlelt->add (new_xmlattribute("use-stems", YesNo::xml(elt->getUseStems())));
	add (xmlelt);
}

//________________________________________________________________________
/*!  Measure style:
\verbatim
<!ELEMENT measure-style (multiple-rest | 
	measure-repeat | beat-repeat | slash)>
<!ATTLIST measure-style
    number CDATA #IMPLIED
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SMeasureStyle& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("measure-style");
	if (elt->getNumber() != TMeasureStyle::undefined)
		xmlelt->add (new_xmlattribute("number", elt->getNumber()));
    push(xmlelt);
    SMeasureStyleElement style = elt->getStyle();
    if (style) style->accept (*this);
    pop();
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e metronome element is as follow:
\n \verbatim
<!ELEMENT metronome (beat-unit, beat-unit-dot*, 
	(per-minute | (beat-unit, beat-unit-dot*)))>
<!ATTLIST metronome
    %position;
    parentheses %yes-no; #IMPLIED
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SMetronome& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("metronome");
	push(xmlelt);
	
	elt->position().accept(*this);
    unsigned dots = elt->getDots();
    if (elt->getParentheses() != YesNo::undefined)
        xmlelt->add (new_xmlattribute ("parentheses", YesNo::xml(elt->getParentheses())));
    xmlelt->add (new_xmlelement ("beat-unit", NoteType::xml(elt->getBeat())));
    if (dots > 0) {
        while (dots--)
            xmlelt->add (new_xmlelement("beat-unit-dot"));
    }

    string str = elt->getPerMinute();
    if ((TSymbolicNoteDuration *)elt->equal()) {
        xmlelt->add (new_xmlelement ("beat-unit", NoteType::xml(elt->equal()->getBeat())));
        dots = elt->equal()->getDots();
        if (dots > 0) {
            while (dots--)
                xmlelt->add (new_xmlelement("beat-unit-dot"));
        }
    }
	else xmlelt->add (new_xmlelement ("per-minute", str));
	pop();
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e midi-device is as follow:
\n \verbatim
<!ELEMENT midi-device (#PCDATA)>
<!ATTLIST midi-device
	port CDATA #IMPLIED
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SMidiDevice& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("midi-device", elt->getName());
	add(xmlelt);
    if (elt->getPort() != TMidiDevice::undefined)
        xmlelt->add (new_xmlattribute("port", elt->getPort()));
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e miscellaneous element is as follow:
\n \verbatim
<!ELEMENT miscellaneous (miscellaneous-field*)>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SMiscId& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("miscellaneous");
	push(xmlelt);
    elt->getFields().accept(*this);
	pop();
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e miscellaneous-field element is as follow:
\n \verbatim
<!ELEMENT miscellaneous-field (#PCDATA)>
<!ATTLIST miscellaneous-field
    name CDATA #REQUIRED
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SMiscField& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("miscellaneous-field", elt->getData());
    xmlelt->add (new_xmlattribute("name", elt->getName()));
	add(xmlelt);
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e midi-instrument element is as follow:
\n \verbatim
<!ELEMENT midi-instrument
	(midi-channel?, midi-name?, midi-bank?, midi-program?,
	 midi-unpitched?)>
<!ATTLIST midi-instrument
    id IDREF #REQUIRED
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SMidiInstrument& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("midi-instrument");
    xmlelt->add (new_xmlattribute("id", elt->getID()));

	long p = elt->getChannel();
    if (p != TMidiInstrument::undefined)
        xmlelt->add (new_xmlelement("midi-channel", p));

	string str = elt->getName();
    if (!str.empty())
        xmlelt->add (new_xmlelement("midi-name", str));

	p = elt->getBank();
    if (p != TMidiInstrument::undefined)
        xmlelt->add (new_xmlelement("midi-bank", p));
	p = elt->getProgram();
    if (p != TMidiInstrument::undefined)
        xmlelt->add (new_xmlelement("midi-program", p));
	p = elt->getUnpitched();
    if (p != TMidiInstrument::undefined)
        xmlelt->add (new_xmlelement("midi-unpitched", p));
	add(xmlelt);
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e notations element is as follow:
\n \verbatim
<!ELEMENT notations
	(%editorial;, 
	 (tied | slur | tuplet | glissando | slide | 
	  ornaments | technical | articulations | dynamics |
	  fermata | arpeggiate | non-arpeggiate | 
	  accidental-mark | other-notation)*)>
<!ATTLIST notations
    editorial-level CDATA #IMPLIED
>
\endverbatim
\note editorial-level is not supported
*/
void TMusicXMLVisitor::visite ( SNotation& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("notations");
	push(xmlelt);
	elt->editorial().accept(*this);
	elt->list().accept(*this);
	pop();
}

//________________________________________________________________________
/*!
	The MusicXMl definition of a \e note element is as follow:
\n \verbatim
<!ELEMENT note 
   (((grace, %full-note;, (tie, tie?)?) |
    (cue, %full-note;, duration) |
	 (%full-note;, duration, (tie, tie?)?)),
	instrument?, %editorial-voice;, type?, dot*,
	accidental?, time-modification?, stem?, notehead?,
	staff?, beam*, notations*, lyric*)>
<!ATTLIST note
    %position; 
    %printout;
    dynamics CDATA #IMPLIED
    end-dynamics CDATA #IMPLIED
    attack CDATA #IMPLIED
    release CDATA #IMPLIED
    pizzicato %yes-no; #IMPLIED
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SNote& elt ) { debug
	Sxmlelement xml = new_xmlelement("note");
	push(xml);
	noteAttributes(elt);
	switch (elt->getStyle()) {
		case TNote::normal:
			normalNote (elt);
			break;
		case TNote::cue:
			cueNote (elt);
			break;
		case TNote::grace:
			graceNote (elt);
			break;
	}
	addCommon(elt);
	elt->getLyrics().accept(*this);
	pop();
}

//________________________________________________________________________
/*!
	The MusicXMl definition of an \e notehead element is as follow:
\n \verbatim
<!ELEMENT notehead (#PCDATA)>
<!ATTLIST notehead
    filled %yes-no; #IMPLIED
    parentheses %yes-no; #IMPLIED>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SNoteHead& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("notehead", elt->xmlnotehead(elt->getShape()));

	if (elt->getFilled() != YesNo::undefined)
		xmlelt->add (new_xmlattribute("filled", YesNo::xml(elt->getFilled())));
	if (elt->getParentheses() != YesNo::undefined)
		xmlelt->add (new_xmlattribute("parentheses", YesNo::xml(elt->getParentheses())));
	add(xmlelt);
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e octave-shift element is as follow:
\n \verbatim
<!ELEMENT octave-shift EMPTY>
<!ATTLIST octave-shift
    type (up | down | stop) #REQUIRED
    number %beam-level; #IMPLIED
    size CDATA "8"
    %position; 
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SOctaveShift& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("octave-shift");
	push(xmlelt);
    xmlelt->add(new_xmlattribute ("type", elt->xmltype(elt->getType())));
    if (elt->getNumber() != TOctaveShift::undefined)
        xmlelt->add(new_xmlattribute ("number", elt->getNumber()));
    xmlelt->add(new_xmlattribute ("size", elt->getSize()));
    elt->position().accept (*this);
	pop();
}

//________________________________________________________________________
/*!
	The MusicXML description of an \e accidental-mark element is as follow:
\n \verbatim
<!ELEMENT accidental-mark (#PCDATA)>
<!ATTLIST accidental-mark
    %position; 
    %placement; 
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SAccidentalMark& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("accidental-mark", elt->getData());
	push(xmlelt);
	elt->position().accept(*this);
	elt->placement().accept(*this);
	pop();
}

//________________________________________________________________________
/*!
	The MusicXML description of other articulations:
\n \verbatim
<!ELEMENT other-articulation (#PCDATA)>
<!ATTLIST other-articulation
    %position; 
    %placement; 
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SOtherArticulation& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("other-articulation", elt->getData());
	push(xmlelt);
	elt->position().accept(*this);
	elt->placement().accept(*this);
	pop();
}

//________________________________________________________________________
/*!
	The MusicXML description of other direction:
\n \verbatim
<!ELEMENT other-direction (#PCDATA)>
<!ATTLIST other-direction
    %position; 
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SOtherDirection& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("other-direction", elt->getData());
	push(xmlelt);
	elt->position().accept(*this);
	pop();
}

//________________________________________________________________________
/*!
*/
void TMusicXMLVisitor::visite ( SOtherDirections& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement(elt->xml(elt->getType()));
	push(xmlelt);
	elt->position().accept(*this);
	pop();
}

//________________________________________________________________________
/*!
	The MusicXML description of the pedal element:
\n \verbatim
<!ELEMENT pedal EMPTY>
<!ATTLIST pedal
    type %start-stop; #REQUIRED
    line %yes-no;	#IMPLIED
    %position; 
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SPedal& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("pedal");
	xmlelt->add (new_xmlattribute("type", StartStop::xml(elt->getType())));
	if (elt->getLine() != YesNo::undefined)
		xmlelt->add (new_xmlattribute("line", YesNo::xml(elt->getLine())));	
	push(xmlelt);
	elt->position().accept(*this);
	pop();
}

//________________________________________________________________________
/*!
	The MusicXML description of the rehearsal element:
\n \verbatim
<!ELEMENT rehearsal (#PCDATA)>
<!ATTLIST rehearsal
    %position; 
    %font;
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SRehearsal& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("rehearsal", elt->getData());
	push(xmlelt);
	elt->position().accept(*this);
	elt->font().accept(*this);
	pop();
}

//________________________________________________________________________
/*!
	The MusicXML description of other ornaments:
\n \verbatim
<!ELEMENT other-ornament (#PCDATA)>
<!ATTLIST other-ornament
    %position; 
    %placement; 
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SOtherOrnament& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("other-ornament", elt->getData());
	push(xmlelt);
	elt->position().accept(*this);
	elt->placement().accept(*this);
	pop();
	// Must be done after ornament has been written
	elt->accidents().accept(*this);
}

//________________________________________________________________________
/*!
	mordent and inverted-mordent ornaments are trill ornaments with an 
	additional long attribute
\verbatim
<!ELEMENT mordent EMPTY>
<!ATTLIST mordent
    long %yes-no; #IMPLIED
    %position; 
    %placement; 
    %trill-sound; 
>
\endverbatim	
*/
void TMusicXMLVisitor::visite ( SMordentOrnament& elt ) { debug
	string name = elt->xml(elt->getType());
	if (name.empty()) return;
	Sxmlelement xmlelt = new_xmlelement(name);
	push(xmlelt);
	if (elt->getLong() != YesNo::undefined)
		xmlelt->add (new_xmlattribute("long", YesNo::xml(elt->getLong())));
	elt->position().accept(*this);
	elt->placement().accept(*this);
	elt->trill().accept(*this);		
	pop();
	// Must be done after ornament has been written
	elt->accidents().accept(*this);
}

//________________________________________________________________________
/*!
	A trill ornament includes a trill-sound entity attribute.
*/
void TMusicXMLVisitor::visite ( STrillOrnament& elt ) { debug 
	string name = elt->xml(elt->getType());
	if (name.empty()) return;
	Sxmlelement xmlelt = new_xmlelement(name);
	push(xmlelt);
	elt->position().accept(*this);
	elt->placement().accept(*this);
	elt->trill().accept(*this);
	pop();
	// Must be done after ornament has been written
	elt->accidents().accept(*this);
}

//________________________________________________________________________
/*!
	A single ornament is between trill-mark, turn, delayed-turn, shake,
	wavy-line, mordent, inverted-mordent, 
	schleifer, other-ornament. It may carry \e accidental-mark.
	They all share position and placement attributes.
*/
void TMusicXMLVisitor::visite ( SOrnament& elt ) { debug
	string name = elt->xml(elt->getType());
	if (name.empty()) return;
	Sxmlelement xmlelt = new_xmlelement(name);
	push(xmlelt);
	elt->position().accept(*this);
	elt->placement().accept(*this);
	pop();
	// Must be done after ornament has been written
	elt->accidents().accept(*this);
}

//________________________________________________________________________
/*!
	The MusicXML description of \e ornaments is as follow:
\n \verbatim
<!ELEMENT ornaments
	(((trill-mark | turn | delayed-turn | shake |
	   wavy-line | mordent | inverted-mordent | 
	   schleifer | other-ornament), accidental-mark*)*)>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SOrnaments& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("ornaments");
	push(xmlelt);
	elt->ornaments().accept(*this);
	pop();
}

//________________________________________________________________________
/*!
	The MusicXML \b partwise description of a \e measure is as follow:
\n \verbatim
<!ELEMENT measure (%music-data;)>
<!ATTLIST measure
    number CDATA #REQUIRED
    implicit %yes-no; #IMPLIED
    non-controlling %yes-no; #IMPLIED
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SPWMeasure& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("measure");
    xmlelt->add (new_xmlattribute("number", elt->getStringNumber()));
    if (elt->getImplicit() != YesNo::undefined)
        xmlelt->add(new_xmlattribute ("implicit", YesNo::xml(elt->getImplicit())));
    if (elt->getNonControlling() != YesNo::undefined)
        xmlelt->add(new_xmlattribute ("non-controling", YesNo::xml(elt->getNonControlling())));
	push(xmlelt);
	elt->data().accept(*this);
	pop();
}

//________________________________________________________________________
/*!
	The MusicXML \b partwise description of a \e part element is as follow:
\n \verbatim
<!ELEMENT part (measure+)>
<!ATTLIST part
    id IDREF #REQUIRED
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SPWPart& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("part");
    xmlelt->add (new_xmlattribute("id", elt->getID()));
	push(xmlelt);
	elt->measures().accept(*this);
	pop();
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e part-group element is as follow:
\n \verbatim
<!ELEMENT part-group (group-name?, group-abbreviation?,
	group-symbol?, group-barline?, %editorial;)>
<!ATTLIST part-group
    type %start-stop; #REQUIRED
    number CDATA "1"
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SPartGroup& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("part-group");
    xmlelt->add (new_xmlattribute("type",  StartStop::xml(elt->getType())));
    xmlelt->add (new_xmlattribute("number", elt->getNumber()));
	push(xmlelt);
	
	string str;
	str = elt->getGroupName();
    if (!str.empty()) {
        Sxmlelement xml = new_xmlelement("group-name", str);
        add (xml);
	}
	str = elt->getGroupAbbrev();
    if (!str.empty()) {
        Sxmlelement xml = new_xmlelement("group-abbreviation", str);
        add (xml);
	}
	str = elt->getGroupBarline();
    if (!str.empty()) {
        Sxmlelement xml = new_xmlelement("group-barline", str);
        add (xml);
	}
	elt->editorial().accept(*this);

    TPartGroup::symbol sym = elt->getSymbol();
	if (sym != TPartGroup::undefined) {
        Sxmlelement xml = new_xmlelement("group-symbol", elt->xmlsymbol(sym));
        add (xml);
	}
	pop();
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e part-list element is as follow:
\n \verbatim
<!ELEMENT part-list (part-group*, score-part,
    (part-group | score-part)*)>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SPartList& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("part-list");
	push(xmlelt);
    elt->parts().accept(*this);
	pop();
}

//________________________________________________________________________
/*!
	The MusicXML description of a pitch element is as follow:
\n \verbatim
<!ELEMENT pitch (step, alter?, octave)>
<!ELEMENT step (#PCDATA)>
<!ELEMENT alter (#PCDATA)>
<!ELEMENT octave (#PCDATA)>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SPitch& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("pitch");
    xmlelt->add (new_xmlelement("step", elt->xmlpitch(elt->getStep())));
    if (elt->getAlter()) xmlelt->add (new_xmlelement("alter", elt->getAlter()));
    xmlelt->add (new_xmlelement("octave", elt->getOctave()));
	add(xmlelt);
}

//________________________________________________________________________
/*!
	The MusicXML description of a print element is as follow:
\n \verbatim
<!ELEMENT print EMPTY>
<!ATTLIST print
	staff-spacing %tenths; #IMPLIED
	new-system %yes-no; #IMPLIED
	new-page %yes-no; #IMPLIED	
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SPrint& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("print");
	if (elt->getStaffSpacing() != TPrint::undefined)
		xmlelt->add (new_xmlattribute("staff-spacing", elt->getStaffSpacing()));
	if (elt->getNewSystem() != YesNo::undefined)
		xmlelt->add (new_xmlattribute("new-system", YesNo::xml(elt->getNewSystem())));
	if (elt->getNewPage() != YesNo::undefined)
		xmlelt->add (new_xmlattribute("new-page", YesNo::xml(elt->getNewPage())));
	add(xmlelt);
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e repeat element is as follow:
\n \verbatim
<!ELEMENT repeat EMPTY>
<!ATTLIST repeat
    direction (backward | forward) #REQUIRED
    times CDATA #IMPLIED
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SRepeat& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("repeat");
    xmlelt->add (new_xmlattribute("direction", elt->xmldirection(elt->getDirection())));
    if (elt->getTimes() != TRepeat::undefined)
        xmlelt->add (new_xmlattribute("times", elt->getTimes()));
	add(xmlelt);
}

//________________________________________________________________________
/*!
	The MusicXML description of a rest is as follow:
\n \verbatim
<!ELEMENT rest ((display-step, display-octave)?)>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SRest& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("rest");
    if (elt->getStep() != TPitch::undefined)
        xmlelt->add (new_xmlelement("display-step", elt->xmlpitch(elt->getStep())));
    if (elt->getOctave())
        xmlelt->add (new_xmlelement("display-octave", elt->getOctave()));
	add(xmlelt);
}

//________________________________________________________________________
/*!
	The MusicXML description of an \e rights element is as follow:
\n \verbatim
<!ELEMENT rights (#PCDATA)>
<!ATTLIST rights
    type CDATA #IMPLIED
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SRights& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("rights", elt->getRight());
    string type = elt->getType();
	if (!type.empty())
        xmlelt->add (new_xmlattribute("type", type));
	add(xmlelt);
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e root element is as follow:
\n \verbatim
<!ELEMENT root (root-step, root-alter?)>
<!ELEMENT root-step (#PCDATA)>
<!ELEMENT root-alter (#PCDATA)>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SRoot& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("root");
	xmlelt->add (new_xmlelement("root-step", elt->getRoot()));
	if (!elt->getAlter().empty())
		xmlelt->add (new_xmlelement("root-alter", elt->getAlter()));
	add(xmlelt);
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e bass element is as follow:
\n \verbatim
<!ELEMENT bass (bass-step, bass-alter?)>
<!ELEMENT bass-step (#PCDATA)>
<!ELEMENT bass-alter (#PCDATA)>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SBass& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("bass");
	xmlelt->add (new_xmlelement("bass-step", elt->getRoot()));
	if (!elt->getAlter().empty())
		xmlelt->add (new_xmlelement("bass-alter", elt->getAlter()));
	add(xmlelt);
}

//________________________________________________________________________
void TMusicXMLVisitor::visite ( SScoreHeader& elt ) { debug
	
	if ((TWork *)elt->work())
        elt->work()->accept(*this);

    string movementNum = elt->getMovementNum();
	if (!movementNum.empty()) {
		Sxmlelement xml = new_xmlelement ("movement-number", movementNum);
		add (xml);
	}
    string title = elt->getMovementTitle();
	if (!title.empty()) {
		Sxmlelement xml = new_xmlelement ("movement-title", title);
		add (xml);
	}
	if ((TIdentification *)elt->identification())
        elt->identification()->accept (*this);
    if ((TPartList *)elt->partList())
        elt->partList()->accept (*this);
}

//________________________________________________________________________
/*!
	The MusicXMl definition of a \e score-instrument element is as follow:
\n
\verbatim
<!ELEMENT score-instrument
    (instrument-name, instrument-abbreviation?)>
<!ATTLIST score-instrument
    id ID #REQUIRED
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SScoreInstrument& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("score-instrument");
    xmlelt->add (new_xmlattribute("id", elt->getID()));
    xmlelt->add (new_xmlelement("instrument-name", elt->getName()));
	string abbrev = elt->getAbbrev();
    if (!abbrev.empty())
        xmlelt->add (new_xmlelement("instrument-abbreviation", abbrev));
	add(xmlelt);
}

//________________________________________________________________________
/*!
	The MusicXMl definition of a \e score-part element is as follow:
\n
\verbatim
<!ELEMENT score-part (identification?, part-name,
    part-abbreviation?, group*, score-instrument*,
    midi-device?, midi-instrument*)>
<!ATTLIST score-part
    id ID #REQUIRED
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SScorePart& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("score-part");
    xmlelt->add (new_xmlattribute("id", elt->getID()));
	push(xmlelt);

    if ((TIdentification *)elt->identification())
        elt->identification()->accept(*this);
    
	xmlelt = new_xmlelement("part-name", elt->getPartName());
	add (xmlelt);
	string str = elt->getPartAbbrev();
    if (!str.empty()) {
        xmlelt = new_xmlelement("part-abbreviation", str);
		add (xmlelt);
	}

    elt->scoreInstruments().accept(*this);
    if ((TMidiDevice *)elt->mididevice())
        elt->mididevice()->accept(*this);
    elt->midiInstruments().accept(*this);
	pop();
}

//________________________________________________________________________
void TMusicXMLVisitor::visite ( SScorePartwise& elt ) { debug
	Sxmlelement score = new_xmlelement ("score-partwise");
	start(score);
	if ((TScoreHeader *)elt->scoreHeader())
        elt->scoreHeader()->accept(*this);    
    elt->partList().accept(*this);
}

//________________________________________________________________________
void TMusicXMLVisitor::visite ( SScoreTimewise& elt ) { debug
	Sxmlelement score = new_xmlelement ("score-timewise");
	start(score);
	if ((TScoreHeader *)elt->scoreHeader())
        elt->scoreHeader()->accept(*this);    
    elt->measureList().accept(*this);
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e segno element is as follow:
\n \verbatim
<!ELEMENT segno EMPTY>
<!ATTLIST segno %position; >
\endverbatim
*/
void TMusicXMLVisitor::visite ( SSegno& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("segno");
    push(xmlelt);
	elt->position().accept(*this);
	pop();
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e staff-details element is as follow:
\n \verbatim
<!ELEMENT staff-details (staff-type?, staff-lines?, 
	staff-tuning*, capo?)>
<!ATTLIST staff-details
    number CDATA #IMPLIED
    show-frets (numbers | letters) #IMPLIED
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SStaffDetails& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("staff-details");

    if (elt->getNumber() != TStaffDetails::undefined)
        xmlelt->add (new_xmlattribute("number", elt->getNumber()));
    switch (elt->getShowFret()) {
		case TStaffDetails::numbers:
			xmlelt->add (new_xmlattribute("show-fret", "numbers"));
			break;
		case TStaffDetails::letters:
			xmlelt->add (new_xmlattribute("show-fret", "letters"));
			break;
		default:
		;
	}
	if (elt->getType() != TStaffDetails::undefType) 
		xmlelt->add (new_xmlelement("staff-type", elt->xml(elt->getType())));
	if (elt->getLines() != TStaffDetails::undefined) 
		xmlelt->add (new_xmlelement("staff-lines", elt->getLines()));
	push(xmlelt);
	elt->tuning().accept(*this);
	pop();
	if (!elt->getCapo().empty()) xmlelt->add (new_xmlelement("capo", elt->getCapo()));
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e staff-tuning element is as follow:
\n \verbatim
<!ELEMENT staff-tuning
	(tuning-step, tuning-alter?, tuning-octave)>
<!ATTLIST staff-tuning
    line CDATA #REQUIRED
>
<!ELEMENT tuning-step (#PCDATA)>
<!ELEMENT tuning-alter (#PCDATA)>
<!ELEMENT tuning-octave (#PCDATA)>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SStaffTuning& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("staff-tuning");
	xmlelt->add (new_xmlattribute("line", elt->getLine()));
	xmlelt->add (new_xmlelement("tuning-step", elt->getStep()));
	if (elt->getAlter())
		xmlelt->add (new_xmlelement("tuning-alter", elt->getAlter()));
	xmlelt->add (new_xmlelement("tuning-octave", elt->getOctave()));
	add(xmlelt);
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e support element is as follow:
\n \verbatim
<!ELEMENT supports EMPTY>
<!ATTLIST supports
    type %yes-no; #REQUIRED
    element CDATA #REQUIRED
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SSupport& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("support");
	xmlelt->add (new_xmlattribute("type", YesNo::xml(elt->getType())));
	xmlelt->add (new_xmlattribute("element", elt->getElement()));
	add(xmlelt);
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e sound element is as follow:
\n \verbatim
<!ELEMENT sound (midi-instrument*)>
<!ATTLIST sound
	tempo CDATA #IMPLIED
	dynamics CDATA #IMPLIED
	dacapo %yes-no; #IMPLIED
	segno CDATA #IMPLIED
	dalsegno CDATA #IMPLIED
	coda CDATA #IMPLIED
	tocoda CDATA #IMPLIED
	divisions CDATA #IMPLIED
	forward-repeat %yes-no; #IMPLIED
	fine CDATA #IMPLIED
	time-only CDATA #IMPLIED
	pizzicato %yes-no; #IMPLIED
	pan CDATA #IMPLIED
	elevation CDATA #IMPLIED
	damper-pedal %yes-no; #IMPLIED
	soft-pedal %yes-no; #IMPLIED
	sostenuto-pedal %yes-no; #IMPLIED
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SSound& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("sound");

    if (elt->getTempo() != TSound::undefined)
        xmlelt->add (new_xmlattribute("tempo", elt->getTempo()));
    if (elt->getDynamics() != TSound::undefined)
        xmlelt->add (new_xmlattribute("dynamics", elt->getDynamics()));
    if (elt->getDacapo() == YesNo::yes)
        xmlelt->add (new_xmlattribute("dacapo", YesNo::xml(elt->getDacapo())));
    if (elt->getSegno() != TSound::undefined)
        xmlelt->add (new_xmlattribute("segno", elt->getSegno()));
    if (elt->getDalsegno() != TSound::undefined)
        xmlelt->add (new_xmlattribute("dalsegno", elt->getDalsegno()));
    if (elt->getCoda() != TSound::undefined)
        xmlelt->add (new_xmlattribute("coda", elt->getCoda()));
    if (elt->getTocoda() != TSound::undefined)
        xmlelt->add (new_xmlattribute("tocoda", elt->getTocoda()));
    if (elt->getDivisions() != TSound::undefined)
        xmlelt->add (new_xmlattribute("divisions", elt->getDivisions()));
    if (elt->getForwardRepeat() == YesNo::yes)
        xmlelt->add (new_xmlattribute("forward-repeat", YesNo::xml(elt->getForwardRepeat())));
    if (elt->getFine() != TSound::undefined) {
        if (elt->getFine() == TSound::yes) xmlelt->add (new_xmlattribute("fine", "yes"));
        else 			  xmlelt->add (new_xmlattribute("fine", elt->getFine()));
    }
    if (elt->getTimeOnly() != TSound::undefined)
        xmlelt->add (new_xmlattribute("time-only", elt->getTimeOnly()));
	if (elt->getPizzicato() != YesNo::undefined)
        xmlelt->add (new_xmlattribute("pizzicato", YesNo::xml(elt->getPizzicato())));
/*
   if (elt->getMidiChannel() != TSound::undefined)
        xmlelt->add (new_xmlattribute("midi-channel", elt->getMidiChannel()));
    if (elt->getMidiIntrument() != TSound::undefined)
        xmlelt->add (new_xmlattribute("midi-instrument", elt->getMidiIntrument()));
*/
    if (elt->getPan() != TSound::undefined)
        xmlelt->add (new_xmlattribute("pan", elt->getPan()));
    if (elt->getElevation() != TSound::undefined)
        xmlelt->add (new_xmlattribute("elevation", elt->getElevation()));

    if (elt->getDamperPedal() != YesNo::undefined)
        xmlelt->add (new_xmlattribute("damper-pedal", YesNo::xml(elt->getDamperPedal())));
    if (elt->getSoftPedal() != YesNo::undefined)
        xmlelt->add (new_xmlattribute("soft-pedal", YesNo::xml(elt->getSoftPedal())));
    if (elt->getSostenutoPedal() != YesNo::undefined)
        xmlelt->add (new_xmlattribute("sostenuto-pedal", YesNo::xml(elt->getSostenutoPedal())));

	push(xmlelt);
	elt->instrumentList().accept(*this);
	pop();
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e strong-accent element is as follow:
\n \verbatim
<!ELEMENT strong-accent EMPTY>
<!ATTLIST strong-accent
    %position; 
    %placement; 
    type %up-down; "up"
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SStrongAccent& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement(elt->xmlname(elt->getArtType()));
	push(xmlelt);
	elt->position().accept(*this);
	elt->placement().accept(*this);
    if (elt->getType() != TStrongAccent::undefined)
        xmlelt->add (new_xmlattribute("type", elt->xmltype(elt->getType())));
	pop();
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e with-bar element is as follow:
\n \verbatim
<!ELEMENT with-bar (#PCDATA)>
<!ATTLIST with-bar
    %position; 
    %placement; 
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SBendWithBar& elt )  { 
	Sxmlelement xmlelt = new_xmlelement("with-bar", elt->getData());
	push(xmlelt);
	elt->position().accept(*this);
	elt->placement().accept(*this);
	pop();
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e bend element is as follow:
\n \verbatim
<!ELEMENT bend
	(bend-alter, (pre-bend | release)?, with-bar?)>
<!ATTLIST bend
    %position; 
    %bend-sound;
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SBend& elt )  { 
	Sxmlelement xmlelt = new_xmlelement(elt->xml(elt->getType()));
	push(xmlelt);
	elt->position().accept(*this);
	elt->placement().accept(*this);
	xmlelt->add(new_xmlelement("bend-alter", elt->getAlter()));
	if (elt->getPreBend())
		xmlelt->add(new_xmlelement("pre-bend", elt->getPreBend()));
	else if (elt->getRelease())
		xmlelt->add(new_xmlelement("release", elt->getRelease()));
	SBendWithBar wb = elt->getWithBar();
	if (wb) wb->accept(*this);
	pop();
}

//________________________________________________________________________
/*!
	The MusicXML description of an \e harmonic element is as follow:
\n \verbatim
<!ELEMENT harmonic
	((natural | artificial)?, 
	 (base-pitch | touching-pitch | sounding-pitch)?)>
<!ATTLIST harmonic
    %position; 
    %placement; 
>
<!ELEMENT natural EMPTY>
<!ELEMENT artificial EMPTY>
<!ELEMENT base-pitch EMPTY>
<!ELEMENT touching-pitch EMPTY>
<!ELEMENT sounding-pitch EMPTY>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SHarmonic& elt )  { 
	Sxmlelement xmlelt = new_xmlelement(elt->xml(elt->getType()));
	push(xmlelt);
	elt->position().accept(*this);
	elt->placement().accept(*this);
	THarmonic::harmonict ht = elt->getHarmonic();
	if (ht != THarmonic::undefined)
		xmlelt->add(new_xmlelement(elt->xmlHarmonic(ht)));
	THarmonic::pitch p = elt->getPitch();
	if (p != THarmonic::undefined_pitch)
		xmlelt->add(new_xmlelement(elt->xmlPitch(p)));
	pop();
}

//________________________________________________________________________
/*!
	The MusicXML description of an \e harmony element is as follow:
\n \verbatim
<!ELEMENT harmony ((%harmony-chord;)+, frame?, 
	%editorial;)>
<!ATTLIST harmony
    type (explicit | implied | alternate) #IMPLIED
    print-object %yes-no; #IMPLIED
    print-frame  %yes-no; #IMPLIED
    %position;
    %placement;
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SHarmony& elt )  { 
	Sxmlelement xmlelt = new_xmlelement("harmony");
	push(xmlelt);
	if (elt->getType() != THarmony::undefined)
		xmlelt->add (new_xmlattribute("type", THarmony::xml(elt->getType())));
	if (elt->getPrintObject() != YesNo::undefined)
		xmlelt->add (new_xmlattribute("print-object", YesNo::xml(elt->getPrintObject())));
	if (elt->getPrintFrame() != YesNo::undefined)
		xmlelt->add (new_xmlattribute("print-frame", YesNo::xml(elt->getPrintFrame())));
	elt->position().accept(*this);
	elt->placement().accept(*this);
	elt->getHarmonyChords().accept(*this);
	if (elt->frame())
		elt->frame()->accept(*this);
	elt->editorial().accept(*this);
	pop();
}

//________________________________________________________________________
/*!
	The MusicXML description of an \e harmony-chord entity is as follow:
\n \verbatim
<!ENTITY % harmony-chord "((root | function), kind,
	inversion?, bass?, degree*)">
<!ELEMENT kind (#PCDATA)>
<!ELEMENT inversion (#PCDATA)>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SHarmonyChord& elt )  { 
	if (elt->getRootFunction())
		elt->getRootFunction()->accept(*this);
	Sxmlelement xmlelt = new_xmlelement("kind", elt->getKind());
	add (xmlelt);
	if (elt->getInversion() != THarmonyChord::undefined) {
		xmlelt = new_xmlelement("inversion", elt->getInversion());
		add (xmlelt);
	}
	if (elt->getBass())
		elt->getBass()->accept(*this);
	elt->getDegrees().accept(*this);
}

//________________________________________________________________________
/*!
	The MusicXML description of \e hammer-on and \e pull-off elements is as follow:
\n \verbatim
<!ELEMENT hammer-on (#PCDATA)>
<!ATTLIST hammer-on
    type %start-stop; #REQUIRED
    number %number-level; "1"
    %position;
    %placement;
    %font;
>
<!ELEMENT pull-off (#PCDATA)>
<!ATTLIST pull-off
    type %start-stop; #REQUIRED
    number %number-level; "1"
    %position;
    %placement;
    %font;
>
\endverbatim
\todo font support
*/
void TMusicXMLVisitor::visite ( SHammerPull& elt )  { 
	Sxmlelement xmlelt = new_xmlelement(elt->xml(elt->getType()), elt->getData());
	push(xmlelt);
	xmlelt->add (new_xmlattribute("type", StartStop::xml(elt->getStartStop())));
	if (elt->getNumber() != THammerPull::undefined)
		xmlelt->add (new_xmlattribute("number", elt->getNumber()));
	elt->position().accept(*this);
	elt->placement().accept(*this);
	elt->font().accept(*this);
	pop();
}

//________________________________________________________________________
void TMusicXMLVisitor::visite ( STechnicals& elt )  { 
	Sxmlelement xmlelt = new_xmlelement("technical");
	push(xmlelt);
	elt->technicals().accept (*this); 
	pop();
}
/*!
	Most of the technical elements have only a position and placement attributes.
*/
void TMusicXMLVisitor::visite ( STechnical& elt )  { 
	Sxmlelement xmlelt = new_xmlelement(elt->xml(elt->getType()), elt->getData());
	push(xmlelt);
	elt->position().accept(*this);
	elt->placement().accept(*this);
	pop();
}

//________________________________________________________________________
/*!
	The MusicXML \b timewise description of a \e measure is as follow:
\n \verbatim
<!ELEMENT measure (part+)>
\endverbatim
*/
void TMusicXMLVisitor::visite ( STWMeasure& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("measure");
    xmlelt->add (new_xmlattribute("number", (long)elt->getNumber()));
	push(xmlelt);
	elt->parts().accept(*this);
	pop();
}

//________________________________________________________________________
/*!
	The MusicXML \b timewise description of a \e part element is as follow:
\n \verbatim
<!ELEMENT part (%music-data;)>
\endverbatim
*/
void TMusicXMLVisitor::visite ( STWPart& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("part");
    xmlelt->add (new_xmlattribute("id", elt->getID()));
	push(xmlelt);
	elt->data().accept(*this);
	pop();
}

//________________________________________________________________________
/*!
	\e tie and \e slur elements share common attributes defined as follow:
\n \verbatim
<!ATTLIST
    type %start-stop; #REQUIRED
    number %beam-level; #IMPLIED
    %line-type;
    %position;
    %placement;
    %orientation;
>
\endverbatim
    Elements are declared as EMPTY.
*/
void TMusicXMLVisitor::tieslur ( STieSlur& elt ) { debug
 	Sxmlelement xmlelt = new_xmlelement(elt->getElement());
	push(xmlelt);

    xmlelt->add (new_xmlattribute("type", StartStop::xml(elt->getType())));
    if (elt->getNumber() != TTieSlur::undefined)
        xmlelt->add (new_xmlattribute("number", elt->getNumber()));
    if (elt->getLineType() != LineType::undefined)
        xmlelt->add (new_xmlattribute("line-type", LineType::xml(elt->getLineType())));
    elt->position().accept(*this);
    elt->placement().accept(*this);
    elt->orientation().accept(*this);
	pop();
}
//________________________________________________________________________
void TMusicXMLVisitor::visite ( STie& elt ) { 
	STieSlur sptr = elt;
	tieslur (sptr);
}

//________________________________________________________________________
/*!
	in addition to the \e tie shared attributes \e slur elements carry \e bezier attributes:
*/
void TMusicXMLVisitor::visite ( SSlur& elt ) { 
	STieSlur sptr = elt;
	tieslur (sptr);
	elt->bezier().accept(*this);
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e time-modification element is as follow:
\n \verbatim
<!ELEMENT time-modification
	(actual-notes, normal-notes, 
	(normal-type, normal-dot*)?)>
\endverbatim
\todo support of arbitrary keys using key-step and key-alter
*/
void TMusicXMLVisitor::visite ( STimeModification& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("time-modification");
	add(xmlelt);

    xmlelt->add (new_xmlelement("actual-notes", elt->getActualNotes()));
    xmlelt->add (new_xmlelement("normal-notes", elt->getNormalNotes()));
    if (elt->getNormalType() != NoteType::undefined) {
        xmlelt->add (new_xmlelement("normal-type",  NoteType::xml(elt->getNormalType())));
        int dots = elt->getNormalDots();
        while (dots--) {
            xmlelt->add (new_xmlelement("normal-dots"));
        }
    }
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e time element is as follow:
\n \verbatim
<!ELEMENT time ((beats, beat-type)+ | senza-misura)>
<!ATTLIST time
	symbol (common | cut | single-number | normal) #IMPLIED
>
\endverbatim
\note editorial information is ignored
*/
void TMusicXMLVisitor::visite ( STimeSign& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("time");

    if (elt->getSymbol() != TTimeSign::undefined)
        xmlelt->add (new_xmlattribute ("symbol", elt->xmlsymbol(elt->getSymbol())));
    if (!elt->measured())
        xmlelt->add (new_xmlelement("senza-misura"));
    else {
        vector<long>::const_iterator beat = elt->getBeats().begin();
        vector<long>::const_iterator type = elt->getBeatTypes().begin();
        string beatstr;
        stringstream s;
        while (beat != elt->getBeats().end()) {
            if (*type == TTimeSign::groupbeats) 
                s << *beat << "+";
            else { 
                s << *beat;
                s >> beatstr;
                xmlelt->add (new_xmlelement("beats", beatstr));
                xmlelt->add (new_xmlelement("beat-type", *type));
                beatstr="";
                s.clear();
            }
            beat++; type++;
        }
    }
	add(xmlelt);
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e key element is as follow:
\n \verbatim
<!ELEMENT transpose (diatonic?, chromatic, octave-change?, double?)>
\endverbatim
*/
void TMusicXMLVisitor::visite ( STranspose& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("transpose");
        
	long p = elt->getDiatonic();
    if (p != TTranspose::undefined)
        xmlelt->add (new_xmlelement("diatonic", p));

	xmlelt->add (new_xmlelement("chromatic", elt->getChromatic()));

	p = elt->getOctaveChge();
    if (p != TTranspose::undefined)
        xmlelt->add (new_xmlelement("octave-change", p));

	p = elt->getDouble();
    if (p != TTranspose::undefined)
        xmlelt->add (new_xmlelement("double", p));
	add(xmlelt);
}

//________________________________________________________________________
/*
void TMusicXMLVisitor::visite ( STrill& elt ) { debug
}
*/
//________________________________________________________________________
/*!
	The MusicXML description of a \e tuplet element is as follow:
\n \verbatim
<!ELEMENT tuplet (tuplet-actual?, tuplet-normal?)>
<!ATTLIST tuplet
    type %start-stop; #REQUIRED
    number %beam-level; #IMPLIED
    bracket %yes-no; #IMPLIED
    show-number (actual | both | none) #IMPLIED
    show-type (actual | both | none) #IMPLIED
    %position;
    %placement;
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( STuplet& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("tuplet");
	push(xmlelt);
    xmlelt->add (new_xmlattribute("type", StartStop::xml(elt->getType())));
    if (elt->getNumber() != TTuplet::undefined)
        xmlelt->add (new_xmlattribute("number", elt->getNumber()));
    if (elt->getBracket() !=  YesNo::undefined)
        xmlelt->add (new_xmlattribute("bracket", YesNo::xml(elt->getBracket())));
    if (elt->getShowNum() != TTuplet::undefined)
        xmlelt->add (new_xmlattribute("show-number", elt->xmlshow(elt->getShowNum())));
    if (elt->getShowType() != TTuplet::undefined)
        xmlelt->add (new_xmlattribute("show-type", elt->xmlshow(elt->getShowType())));
    elt->position().accept(*this);
    elt->placement().accept(*this);

    if ((TTupletDesc*)elt->actualDesc())  elt->actualDesc()->accept(*this);
    if ((TTupletDesc*)elt->normalDesc())  elt->normalDesc()->accept(*this);
	pop();
}

//________________________________________________________________________
/*!
	Generates MusicXML description for \e tuplet-actual and \e tuplet-normal elements, 
	defined as below:
\n \verbatim
<!ELEMENT tuplet-actual (tuplet-number?,
	tuplet-type?, tuplet-dot*)>
<!ELEMENT tuplet-normal (tuplet-number?,
	tuplet-type?, tuplet-dot*)>
\endverbatim
*/
void TMusicXMLVisitor::visite ( STupletDesc& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("tuplet-" + elt->getName());
    if (elt->getNumber() != TTupletDesc::undefined)
        xmlelt->add (new_xmlelement("tuplet-number", elt->getNumber()));
    if (elt->getType() != TTupletDesc::undefined)
        xmlelt->add (new_xmlelement("tuplet-type", elt->getType()));
    int dots = elt->getDots();
    while (dots-- > 0)
        xmlelt->add (new_xmlelement("tuplet-dot"));
	add(xmlelt);
}

//________________________________________________________________________
/*!
	The MusicXML description of an unpitched element is as follow:
\n \verbatim
<!ELEMENT unpitched ((display-step, display-octave)?)>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SUnpitched& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("unpitched");
    if (elt->getStep() != TPitch::undefined)
        xmlelt->add (new_xmlelement("display-step", elt->xmlpitch(elt->getStep())));
    if (elt->getOctave())
        xmlelt->add (new_xmlelement("display-octave", elt->getOctave()));
	add(xmlelt);
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e wavy-line element is as follow:
\n \verbatim
<!ELEMENT wavy-line EMPTY>
<!ATTLIST wavy-line
    type %start-stop-continue; #REQUIRED
    number %beam-level; #IMPLIED
    %position;
    %placement; 
    %trill-sound; 
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SWavyLine& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("wavy-line");
	xmlelt->add (new_xmlattribute ("type", StartStop::xml(elt->getType())));
    
	int num = elt->getNumber();
	if (num != TWavyLine::undefined)
        xmlelt->add (new_xmlattribute ("number", num));    
	push(xmlelt);
	elt->position().accept (*this);
    elt->placement().accept (*this);
    elt->trill().accept (*this);
	pop();
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e wedge element is as follow:
\n \verbatim
<!ELEMENT wedge EMPTY>
<!ATTLIST wedge
    type (crescendo | diminuendo | stop) #REQUIRED
    number %beam-level; #IMPLIED
    spread CDATA #IMPLIED
    %position; 
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SWedge& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("wedge");
	push(xmlelt);
    xmlelt->add(new_xmlattribute ("type", elt->xmltype(elt->getType())));
    if (elt->getNumber() != TWedge::undefined)
        xmlelt->add(new_xmlattribute ("number", elt->getNumber()));
    if (elt->getSpread() != TWedge::undefined)
        xmlelt->add(new_xmlattribute ("spread", elt->getSpread()));
    elt->position().accept (*this);
	pop();
}

//________________________________________________________________________
/*!
	The MusicXML description of a \e words element is as follow:
\n \verbatim
<!ELEMENT words (#PCDATA)>
<!ATTLIST words
    justify (left | center | right) #IMPLIED
    %position; 
    %font;
    xml:lang NMTOKEN #IMPLIED
>
\endverbatim
\todo support of the \e font entity
*/
void TMusicXMLVisitor::visite ( SWords& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("words", elt->getValue());
	push (xmlelt);

	int justify = elt->getJustify();
    if (justify != TWords::undefined)
        xmlelt->add(new_xmlattribute ("justify", elt->xmljustify(justify)));
   	elt->position().accept (*this);
   	elt->font().accept(*this);
	string lang = elt->getLang();
    if (!lang.empty())
        xmlelt->add(new_xmlattribute ("xml:lang", lang));
	pop();
}

//______________________________________________________________________________
/*!
	The MusicXML description of a \e work element is as follow:
\n \verbatim
<!ELEMENT work (work-number?, work-title?, opus?)>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SWork& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement("work");
    if (!elt->getNum().empty())
        xmlelt->add (new_xmlelement("work-number", elt->getNum()));
    if (!elt->getTitle().empty())
        xmlelt->add (new_xmlelement("work-title", elt->getTitle()));
	add (xmlelt);
}


//________________________________________________________________________
void TMusicXMLVisitor::visite ( TOrientation* elt ) { debug
    string orient = elt->xmlorientation(elt->get());
    if (!orient.empty())
        current()->add(new_xmlattribute ("orientation", orient));
}

//________________________________________________________________________
void TMusicXMLVisitor::visite ( TPlacement* elt ) { debug
    string place = elt->xmlplace(elt->get());
    if (!place.empty())
         current()->add(new_xmlattribute ("placement", place));
}

//________________________________________________________________________
void TMusicXMLVisitor::visite ( TPosition* elt ) { debug
	for (int i=TPosition::defaultx; i<=TPosition::relativey; i++) {
        long pos = elt->get(i);
        if (pos != TPosition::undefined)
             current()->add (new_xmlattribute(elt->xmlpos(i), pos));
    }
}

//________________________________________________________________________
void TMusicXMLVisitor::visite ( TFont* elt ) { debug
    if (!elt->getFamily().empty())
        current()->add(new_xmlattribute ("font-family", elt->getFamily()));
    if (!elt->getStyle().empty())
        current()->add(new_xmlattribute ("font-style", elt->getStyle()));
    if (!elt->getSize().empty())
        current()->add(new_xmlattribute ("font-size", elt->getSize()));
    if (!elt->getWeight().empty())
        current()->add(new_xmlattribute ("font-weight", elt->getWeight()));
}

//________________________________________________________________________
/*!
	The MusicXML description of the \e printout entity is as follow:
\verbatim
<!ENTITY % printout
	"print-object  %yes-no;  #IMPLIED
	 print-dot     %yes-no;  #IMPLIED
	 print-spacing %yes-no;  #IMPLIED">
\endverbatim
*/
void TMusicXMLVisitor::visite ( TPrintout* elt ) { debug
    if (elt->getPrintObject() != YesNo::undefined)
        current()->add(new_xmlattribute ("print-object", YesNo::xml(elt->getPrintObject())));
    if (elt->getPrintDot() != YesNo::undefined)
        current()->add(new_xmlattribute ("print-dot", YesNo::xml(elt->getPrintDot())));
    if (elt->getPrintSpacing() != YesNo::undefined)
        current()->add(new_xmlattribute ("print-spacing", YesNo::xml(elt->getPrintSpacing())));
}

//________________________________________________________________________
/*!
	The MusicXML description of the \e bezier entity is as follow:
\verbatim
<!ENTITY % bezier
	"bezier-offset  CDATA     #IMPLIED
	 bezier-offset2 CDATA     #IMPLIED
	 bezier-x       %tenths;  #IMPLIED
	 bezier-y       %tenths;  #IMPLIED
	 bezier-x2      %tenths;  #IMPLIED
	 bezier-y2      %tenths;  #IMPLIED">
\endverbatim
*/
void TMusicXMLVisitor::visite ( TBezier* elt ) { debug
    if (elt->getOffset() != TBezier::undefined)
        current()->add(new_xmlattribute ("bezier-offset", elt->getOffset()));
    if (elt->getOffset2() != TBezier::undefined)
        current()->add(new_xmlattribute ("bezier-offset2", elt->getOffset2()));
    if (elt->getX() != TBezier::undefined)
        current()->add(new_xmlattribute ("bezier-x", elt->getX()));
    if (elt->getY() != TBezier::undefined)
        current()->add(new_xmlattribute ("bezier-y", elt->getY()));
    if (elt->getX2() != TBezier::undefined)
        current()->add(new_xmlattribute ("bezier-x2", elt->getX2()));
    if (elt->getY2() != TBezier::undefined)
        current()->add(new_xmlattribute ("bezier-y2", elt->getY2()));
}

//________________________________________________________________________
/*!
	basic PCDATA simple xml element visite
*/
void TMusicXMLVisitor::visite ( SPCData& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement(elt->getName(), elt->getData());
	add (xmlelt);
}
void TMusicXMLVisitor::visite ( SFootnote& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement(elt->getName(), elt->getData());
	add (xmlelt);
}
void TMusicXMLVisitor::visite ( SVoice& elt ) { debug
	Sxmlelement xmlelt = new_xmlelement(elt->getName(), elt->getData());
	add (xmlelt);
}

//________________________________________________________________________
/*!
	The MusicXML description of the \e level element is as follow:
\verbatim
<!ELEMENT level (#PCDATA)>
<!ATTLIST level
    parentheses %yes-no; #IMPLIED
    bracket %yes-no; #IMPLIED
    size %symbol-size; #IMPLIED
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( SLevel& elt ) { debug	
	Sxmlelement xml = new_xmlelement ("level", elt->getData());
	if (elt->getParentheses() != YesNo::undefined)
		xml->add(new_xmlattribute ("parentheses", YesNo::xml(elt->getParentheses())));
	if (elt->getBrackets() != YesNo::undefined)
		xml->add(new_xmlattribute ("bracket", YesNo::xml(elt->getBrackets())));
	if (elt->getSize() != FullCue::undefined)
		xml->add(new_xmlattribute ("size", FullCue::xml(elt->getSize())));
	add (xml);
}

//________________________________________________________________________
/*!
	The MusicXML description of the \e editorial and \e editorial-voice entities are as follow:
\verbatim
<!ENTITY % editorial "(footnote?, level?)">
<!ENTITY % editorial-voice "(footnote?, level?, voice?)">
<!ELEMENT footnote (#PCDATA)>
<!ELEMENT level (#PCDATA)>
<!ATTLIST level
    parentheses %yes-no; #IMPLIED
    bracket %yes-no; #IMPLIED
    size %symbol-size; #IMPLIED
>
\endverbatim
*/
void TMusicXMLVisitor::visite ( TEditorial* elt ) { debug
    if (elt->footnote())	visite(elt->footnote());
    if (elt->level())		visite(elt->level());
    if (elt->voice())		visite(elt->voice());
}

//________________________________________________________________________
/*
<!ENTITY % trill-sound
	"start-note    (upper | main | below)  #IMPLIED
	 trill-step    (whole | half | unison) #IMPLIED
	 two-note-turn (whole | half | none)   #IMPLIED
	 accelerate    %yes-no; #IMPLIED
	 beats         CDATA    #IMPLIED
	 second-beat   CDATA    #IMPLIED
	 last-beat     CDATA    #IMPLIED">
*/
void TMusicXMLVisitor::visite ( TTrillSound* elt ) { debug
	TrillStart::type start = elt->getStartNote();
	if (start != TrillStart::undefined)
		current()->add (new_xmlattribute("start-note", TrillStart::xml(start)));
	TrillStep::type st = elt->getTrillStep();
	if (st != TrillStep::undefined)
		current()->add (new_xmlattribute("trill-step", TrillStep::xml(st)));
	st = elt->getTwoNoteTurn();
	if (st != TrillStep::undefined)
		current()->add (new_xmlattribute("two-note-turn", TrillStep::xml(st)));
	YesNo::type yn = elt->getAccelerate();
	if (yn != YesNo::undefined)
		current()->add (new_xmlattribute("accelerate", YesNo::xml(yn)));

	if (elt->getBeat())		  current()->add (new_xmlattribute("beats", elt->getBeat()));
	if (elt->getSecondBeat()) current()->add (new_xmlattribute("second-beat", elt->getSecondBeat()));
	if (elt->getLastBeat())   current()->add (new_xmlattribute("last-beat", elt->getLastBeat()));
}

//________________________________________________________________________
/*
<!ENTITY % bend-sound
	"accelerate    %yes-no; #IMPLIED
	 beats         CDATA    #IMPLIED
	 first-beat    CDATA    #IMPLIED
	 last-beat     CDATA    #IMPLIED">
*/
void TMusicXMLVisitor::visite ( TBendSound* elt ) { debug
	YesNo::type yn = elt->getAccelerate();
	if (yn != YesNo::undefined)
		current()->add (new_xmlattribute("accelerate", YesNo::xml(yn)));

	if (elt->getBeat())		  current()->add (new_xmlattribute("beats", elt->getBeat()));
	if (elt->getFirstBeat())  current()->add (new_xmlattribute("first-beat", elt->getFirstBeat()));
	if (elt->getLastBeat())   current()->add (new_xmlattribute("last-beat", elt->getLastBeat()));
}

} // namespace MusicXML
