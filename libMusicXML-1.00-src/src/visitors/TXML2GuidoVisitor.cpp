/*

  Copyright (C) 2003  Grame

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

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  grame@grame.fr

*/

#define debug	// cout << "visite " << __LINE__ << endl; fflush(stdout);

#include "TXML2GuidoVisitor.h"
#include "LibMusicXML.h"
#include "guido.h"

#include <sstream>
#include <iostream>


#define XML2GuidoDebug	0

#if XML2GuidoDebug
#	include <fstream>
	ofstream xml2guido("xml2gmn-debug.txt",ios_base::trunc);
#	define dbgStream   xml2guido
#else
#	define dbgStream   cout
#endif

/*!
\todo support of IDs for tags other than slurs
*/

//________________________________________________________________________
/*
SXML2GuidoVisitor newXML2GuidoVisitor(bool comments, bool checkStem, bool bar) { 
	TXML2GuidoVisitor * o = new TXML2GuidoVisitor(comments, checkStem, bar); 
	assert(o!=0); 
	return o; 
}
*/
//________________________________________________________________________
TXML2GuidoVisitor::TXML2GuidoVisitor (bool comments, bool stem, bool bar)
	: fCurTimeSign (0,1), fComments(comments), fCheckStem(stem) {
	fCrescPending = false;
	fHeaderPending = true;
	fInRepeat = false;
	fCurrentDivision = 1;
	fPendingPops = 0;
	fInTieSlur = fInChord = false;
	fStemDirection = TGraphNote::undefined;
	fGenerateBars = bar;
	fInhibitNextBar=false;
}

TXML2GuidoVisitor::~TXML2GuidoVisitor() {}

//________________________________________________________________________
void TXML2GuidoVisitor::visite ( SAccidental& elt ) { debug
}

//________________________________________________________________________
void TXML2GuidoVisitor::visite ( SArticulationElement& elt ) { debug
	Sguidoelement tag;
    
    if (fNotePass != before) {
        switch (elt->getArtType()) {
            case TArticulationElement::breath_mark:
                tag = new_guidotag("breathMark");
                break;
            default:
                ;
         }
        if (tag) add(tag);
        return;
   }
    // articulations within a chord are ignored
	// actual guido engine don't handle them correctly
	if (fInChord) return; 	
	
    switch (elt->getArtType()) {
		case TArticulationElement::accent:
            tag = new_guidotag("accent");
 			break;
		case TArticulationElement::strong_accent:
            tag = new_guidotag("marcato");
			break;
		case TArticulationElement::staccato:
            tag = new_guidotag("stacc");
			break;
		case TArticulationElement::tenuto:
            tag = new_guidotag("ten");
			break;
		case TArticulationElement::breath_mark:
            tag = 0; // new_guidotag("breathMark");
			break;
        default:
            ;
	}
    if (tag) {
        push(tag);
        fPendingPops++;
    }
}

//________________________________________________________________________
void TXML2GuidoVisitor::visite ( SArticulations& elt ) { debug
	elt->articulations().accept(*this);
}

//________________________________________________________________________
void TXML2GuidoVisitor::visite ( SAttributes& elt ) { debug
    if (elt->getDivision() != TAttributes::undefined)
		fCurrentDivision = elt->getDivision();

    if ((TKey *)elt->key()) 			elt->key()->accept(*this);
    if ((TTimeSign*)elt->timeSign()) 	elt->timeSign()->accept(*this);
	
    elt->clefs().accept(*this);
    if ((TTranspose *)elt->transpose()) 	elt->transpose()->accept(*this);
    if ((TDirective *)elt->directive()) 	elt->directive()->accept(*this);
}

//________________________________________________________________________
void TXML2GuidoVisitor::visite ( SBackup& elt ) { debug
}

//______________________________________________________________________________
/*!
    translation of the xml style to guido is incomplete: guido lacks of
    tag to represent the xml typology. When no corresponding element exists
    the function returns a \bar tag.
*/
const string TXML2GuidoVisitor::guidobarstyle(int style) const {
    switch (style) {
        case TBarline::undefined:
        case TBarline::none:
        case TBarline::regular:		return "bar";
        case TBarline::dotted:		return "tactus";
        case TBarline::light_light:
        case TBarline::light_heavy:
        case TBarline::heavy_light:
        case TBarline::heavy_heavy: return "doubleBar";
        case TBarline::heavy:
        default:					return "bar";
    }
}

//________________________________________________________________________
/*!
    visit of a barline may add several guido elements: \\bar, \\fermata, \\repeatBegin
    \\repeatEnd ...
*/
void TXML2GuidoVisitor::visite ( SBarline& elt ) { debug
    Sguidoelement tag;
    if ((TFermata *)elt->fermata()) {
        tag = new_guidotag("fermata");
        add(tag);
    }

	TEnding* ending = elt->ending();
	if (ending) {
		stringstream s;
		switch (ending->getType()) {
			case TEnding::start:
				tag = new_guidotag("volta");
				s << elt->ending()->getNum() << '.';
				tag->add(new_guidoparam(elt->ending()->getNum(), true));
				tag->add(new_guidoparam(s.str(), true));
				push(tag);
				fInRepeat = true;
				break;
			case TEnding::discontinue:
				if (fInRepeat)
                    current()->add(new_guidoparam("format=\"|-\"", false));
			case TEnding::stop:
				if (fInRepeat) {
					pop();
					fInRepeat = false;
				}
				break;
		}
	}

	if ((TRepeat*)elt->repeat()) {
		switch (elt->repeat()->getDirection()) {
			case TRepeat::forward:
				tag = new_guidotag("repeatBegin");
				add(tag);
				break;
			case TRepeat::backward:
                tag = new_guidotag("repeatEnd");
                add(tag);
                fInhibitNextBar = true;
				break;
		}
	}
/*
	else if (elt->getBarStyle() != TBarline::undefined) {
		Sguidoelement bar = new_guidotag(guidobarstyle(elt->getBarStyle()));	
		add( bar);
	}
*/
}

//________________________________________________________________________
void TXML2GuidoVisitor::visite ( SBeam& elt ) { debug
    Sguidoelement tag;
    switch (elt->getType()) {
        case TBeam::beambegin:
            if ((fNotePass == before) && !fBeamOpened && !fInChord) {
                tag = new_guidotag("beamBegin");
                fBeamOpened = true;
				fBeamNumber = elt->getNumber();
            }
            break;
        case TBeam::beamend:
            if ((fNotePass == after) && fBeamOpened 
				&& !fInChord && (fBeamNumber==elt->getNumber())) {
                tag = new_guidotag("beamEnd");
                fBeamOpened = false;
            }
            break;
        default:
            ;
    }
    if (tag) add(tag);
}

//________________________________________________________________________
void TXML2GuidoVisitor::visite ( SBracket& elt ) { debug
}

//________________________________________________________________________
void TXML2GuidoVisitor::visite ( SChord& elt ) { debug
	long staff = elt->getStaff();
	staff = fCurrentPart->getStaffIndex(staff);

	if (elt->getStyle() == TNote::cue) {
        return; // cue notes are ignored for the moment
        if ((staff != fStaffNum) || fStaffPass) return;
	}
	else if (elt->getVoice() != fCurrentVoice) return;
	
	checkstaff(staff);
	Sguidoelement chord = new_guidochord();
	vvector<SNote>::const_iterator note = elt->notes().begin();
    SGraphNote gn;
	if (note != elt->notes().end()) {
		checkstem(*note);
        gn = (*note)->graphics();
        if (gn) {
            fNotePass = before;
            gn->beamList().accept(*this);
        }
    }
	push(chord);
	fInChord = true;
	elt->notes().accept(*this);
	pop();
	fInChord = false;
    if (gn) {
        fNotePass = after;
        gn->beamList().accept(*this);
    }
}

//________________________________________________________________________
/*!
\todo translation of none and TAB clefs
*/
void TXML2GuidoVisitor::visite ( SClef& elt ) { debug
	long staff = fCurrentPart->getStaffIndex(elt->getStaffNum());
	if ((staff != fStaffNum) || fStaffPass) return;
	
	Sguidoelement tag = new_guidotag("clef");
    stringstream s; string param;
	switch (elt->getSign()) {
		case TClef::G:				s << "g"; break;
		case TClef::F:				s << "f"; break;
		case TClef::C:				s << "c"; break;
		case TClef::percussion:		s << "perc"; break;
	}

    if (elt->getLine() != TClef::undefined) s << elt->getLine();
    long oct = elt->getOctave();
    if (oct) {
        if (oct > 0) s << "+";
        s << oct;
    }
    s >> param;
	checkstaff (staff);
    tag->add (new_guidoparam(param));
    add(tag);
}

//________________________________________________________________________
void TXML2GuidoVisitor::visite ( SCoda& elt ) { debug
/*
	tag is now suppported vua the sound element for consistency reasons
	
	Sguidoelement tag = new_guidotag("coda");
	add (tag);
*/
}

//________________________________________________________________________
/*!
\todo handling the different creator types as defined in MusicXML.
    There is actually no corresponding tag apart the \p composer tag in guido.
*/
void TXML2GuidoVisitor::visite ( SCreator& elt ) { debug
	if ((elt->getType() != "composer") && (elt->getType() != "Composer")) return;
	Sguidoelement tag = new_guidotag("composer");
    tag->add (new_guidoparam(elt->getName()));
    tag->add (new_guidoparam("dy=4hs", false));
	add (tag);
}

//________________________________________________________________________
void TXML2GuidoVisitor::visite ( SDirection& elt ) { debug
	elt->types().accept(*this);
	SSound sound = elt->sound();
	if (sound) sound->accept(*this);
}

//________________________________________________________________________
void TXML2GuidoVisitor::visite ( SDirectionType& elt ) { debug
	elt->elements().accept(*this);
}

//________________________________________________________________________
void TXML2GuidoVisitor::visite ( SDirective& elt ) { debug
	if (fStaffPass) return;
/*
	Sguidoelement tag = new_guidotag("text");
    tag->add (new_guidoparam(elt->getValue()));
    add( tag);
*/
}

//________________________________________________________________________
void TXML2GuidoVisitor::visite ( SDynamic& elt ) { debug
	if (fStaffPass) return;
	vector<TDynamic::dynamic>::const_iterator dyn;
	for (dyn = elt->dynamics().begin(); dyn != elt->dynamics().end(); dyn++) {
		Sguidoelement tag = new_guidotag("intens");
		tag->add (new_guidoparam(elt->xmldynamic(*dyn)));
		add (tag);
	}
}

//________________________________________________________________________
void TXML2GuidoVisitor::visite ( SEncoding& elt ) { debug
}

//________________________________________________________________________
void TXML2GuidoVisitor::visite ( SEnding& elt ) { debug
}

//________________________________________________________________________
void TXML2GuidoVisitor::visite ( SFermata& elt ) { debug
}

//________________________________________________________________________
void TXML2GuidoVisitor::visite ( SForward& elt ) { debug
	long voice = elt->getVoice();
	if ((voice != TForward::undefined) && (voice != fCurrentVoice)) return;
	TRational r(elt->getDuration(), fCurrentDivision*4);
	r.rationalise();
	guidonoteduration dur (r.getNumerator(), r.getDenominator());
	Sguidoelement note = new_guidonote((unsigned short)voice, "empty", 0, dur, "");
	add (note);
    fMeasureEmpty = false;
}

//________________________________________________________________________
void TXML2GuidoVisitor::visite ( SGraceNote& elt ) { debug
}

//________________________________________________________________________
void TXML2GuidoVisitor::visite ( SGraphNote& elt ) { debug
}

//________________________________________________________________________
void TXML2GuidoVisitor::visite ( SIdentification& elt ) { debug
    elt->creators().accept(*this);
}

//________________________________________________________________________
void TXML2GuidoVisitor::visite ( SKey& elt ) { debug
	if (fStaffPass) return;
	Sguidoelement tag = new_guidotag("key");
	tag->add (new_guidoparam(elt->getFifths(), false));
    add (tag);
}

//________________________________________________________________________
//! \todo complete translation of TMetronome
void TXML2GuidoVisitor::visite ( SMetronome& elt ) { debug
	// don't know how to translate the equal from
	if ((TSymbolicNoteDuration *)elt->equal()) return;
	
	Sguidoelement tag = new_guidotag("tempo");
	stringstream s;
	TRational r, rdot(3,2);
	int dots = elt->getDots();
	NoteType::rational(elt->getBeat(), r);
	while (dots>0) {
		r *= rdot;
		dots--;
	}
	r.rationalise();
	s << "[" << (string)r << "] = " << elt->getPerMinute();
	tag->add (new_guidoparam("tempo=\""+s.str()+"\"", false));
//	tag->add (new_guidoparam("bpm=\""+param+"\"", false));
    add (tag);
}

//________________________________________________________________________
void TXML2GuidoVisitor::visite ( SMidiInstrument& elt ) { debug
/*
	if (elt->getProgram() != TMidiInstrument::undefined) {
		Sguidoelement tag = new_guidotag("instr");
		tag->add (new_guidoparam(elt->getName()));
		stringstream s;
		s << "MIDI " << elt->getProgram();
		tag->add (new_guidoparam(s.str()));
		add (tag);
	}
*/
}

//________________________________________________________________________
void TXML2GuidoVisitor::visite ( SNotation& elt ) { debug
	elt->list().accept(*this);
}

//________________________________________________________________________
bool TXML2GuidoVisitor::checkgrace (const SNote& note) {
	if (note->getStyle() == TNote::grace) {
		Sguidoelement tag = new_guidotag("grace");
		push(tag);
		return true;
	}
    return false;
}

//________________________________________________________________________
bool TXML2GuidoVisitor::checkcue (const SNote& note) {
	if (note->getStyle() == TNote::cue) {
		Sguidoelement tag = new_guidotag("cue");
		push(tag);
		return true;
	}
    return false;
}

//________________________________________________________________________
void TXML2GuidoVisitor::checkstem (const SNote& note) {
	if (!fCheckStem) return;
	SGraphNote gn = note->graphics();
	if (gn && !note->isRest()) {
		int stem = gn->getStem();
		if (fStemDirection != stem) {
			Sguidoelement tag;
			switch (stem) {
				case TGraphNote::stemdown:
					tag = new_guidotag("stemsDown");
					break;
				case TGraphNote::stemup:
					tag = new_guidotag("stemsUp");
					break;
				case TGraphNote::stemnone:
					tag = new_guidotag("stemsOff");
					break;
				case TGraphNote::undefined:
					tag = new_guidotag("stemsAuto");
					break;
			}
			if (tag) {
				add(tag);
				fStemDirection = stem;
			}
		}
	}
}

//________________________________________________________________________
void TXML2GuidoVisitor::guidonote (const SNote& note) {

	unsigned short voice = 0;
	string name, accident; char oct;

	if (note->isRest()) {
		name = "_";
		accident = "";
		oct = 0;
	}
	else {
		SPitch pitch = note->pitch();
		name = pitch->xmlpitch(pitch->getStep());
		if (!name.empty()) name[0]=tolower(name[0]);
		else cout << "erreur: pitch name empty: " << pitch->getStep() << endl;
	
		// octave offset between MusicXML and GUIDO is -3
		oct = pitch->getOctave() - 3; 
		
		stringstream s;
		float alter = pitch->getAlter();
		if (alter > 0) {
			while (alter > 0) {
				s << "#";
				alter -= 1;
			}
			s >> accident;
		}
		else if (alter < 0) {
			while (alter < 0) {
				s << "&";
				alter += 1;
			}
			s >> accident;
		}
	}
	
	guidonoteduration dur(0,0);
	if (!note->isGrace()) {
		TRational r(note->getDuration(), fCurrentDivision*4);
		r.rationalise();
		dur.set (r.getNumerator(), r.getDenominator());
	}

	SGraphNote gn = note->graphics();
	if (gn) {
		if (note->isGrace()) {
			TRational r;
			NoteType::rational(gn->getType(), r);
			r.rationalise();
			dur.set (r.getNumerator(), r.getDenominator(), gn->getDots());
		}
		if (gn->getVoice() != TGraphNote::undefined)
			voice = (unsigned short)gn->getVoice();
		checkstem (note);
        fNotePass = before;
        fPendingPops = 0;
        gn->beamList().accept(*this);
        gn->notationList().accept(*this);
	}
    
	if (checkcue (note) || checkgrace (note)) fPendingPops++;

	if (XML2GuidoDebug) dbgStream << "new_guidonote  voice " << voice << " name \"" << name
			<< "\" oct " << (int)oct << " dur " << dur.fNum << "/" << dur.fDenom << " dots " 
			<< dur.fDots << " accident " << accident << endl;
	Sguidoelement elt = new_guidonote(voice, name, oct, dur, accident);
	add (elt);
    while (fPendingPops--) pop();
    fMeasureEmpty = false;
    fNotePass = after;
    if (gn) {
        gn->beamList().accept(*this);
        gn->notationList().accept(*this);
    }
}

//________________________________________________________________________
void TXML2GuidoVisitor::checkstaff (long staff) {
    if (staff != fCurrentStaff) {
        Sguidoelement tag = new_guidotag("staff");
		tag->add (new_guidoparam(staff, false));
        add (tag);
        fCurrentStaff = staff;
    }
}

//________________________________________________________________________
void TXML2GuidoVisitor::visite ( SNote& elt ) { debug
	fInhibitNextBar = false;
	// don't know how to output a note without voice and staff information
	if (!(TGraphNote *)elt->graphics()) return;

    long staff = elt->graphics()->getStaff();
    staff = fCurrentPart->getStaffIndex(staff);

	// cue notes are flushed with the first voice
	if (elt->getStyle() == TNote::cue) {
		return; // cue notes ignored for the moment
        if ((staff != fStaffNum) || fStaffPass) return;
	}
	else if (elt->graphics()->getVoice() != fCurrentVoice) return;

	checkstaff (staff);
	fSlurs.flag = 0;
	elt->accept(fSlurs);
	guidonote(elt);
}

//________________________________________________________________________
void TXML2GuidoVisitor::visite ( SNoteHead& elt ) { debug
}

//________________________________________________________________________
void TXML2GuidoVisitor::visite ( SOctaveShift& elt ) { debug
}

//________________________________________________________________________
void TXML2GuidoVisitor::visite ( SPWMeasure& elt ) { debug
	elt->data().accept(*this);
}

//________________________________________________________________________
void TXML2GuidoVisitor::partheader ( SScoreHeader& elt ) { debug
	if ((TPartList *)elt->partList())
		elt->partList()->accept(*this);
}

//________________________________________________________________________
void TXML2GuidoVisitor::guidoheader ( SScoreHeader& elt ) { debug
	string title = elt->getMovementTitle();
	if (!title.empty()) {
		Sguidoelement tag = new_guidotag("title");
		tag->add (new_guidoparam(title));
//		tag->add (new_guidoparam("dy=-2hs"));
		add (tag);
	}
	if ((TWork *)elt->work())
		elt->work()->accept(*this);
	if ((TIdentification *)elt->identification())
		elt->identification()->accept(*this);
}

//________________________________________________________________________
void TXML2GuidoVisitor::measurend (SPWMeasure meas, int position) {
	// time is not measured
	if (fCurTimeSign.getNumerator() == 0) return;

	unsigned long dur = meas->getDuration(fCurrentVoice ? fCurrentVoice : TPWMeasure::allVoices);
    unsigned long mlength = fCurTimeSign.getNumerator() * fCurrentDivision 
                                * 4 / fCurTimeSign.getDenominator();

    if (fMeasureEmpty) {
		TRational r(meas->getDuration(), 4*fCurrentDivision);
		r.rationalise();
		guidonoteduration gdur (r.getNumerator(), r.getDenominator());
		Sguidoelement empty = new_guidonote((unsigned short)fCurrentVoice, "empty", 0, gdur, "");
		add (empty);
    }
    else {
		if ((position!=kFirst) && (dur < mlength)) {
			TRational r(mlength - dur, 4*fCurrentDivision);
			r.rationalise();
			guidonoteduration gdur (r.getNumerator(), r.getDenominator());
			Sguidoelement empty = new_guidonote((unsigned short)fCurrentVoice, "empty", 0, gdur, "");
			add (empty);
    	}
    	if (!fStaffPass && (fGenerateBars || (dur < mlength)) && (position != kLast)) {
    		// barlines are inhibited after a repeat bar
    		if (!fInhibitNextBar) {
				Sguidoelement tag = new_guidotag("bar");
				add (tag);
				fInhibitNextBar = false;
			}
    	}    	
    }
}

//________________________________________________________________________
void TXML2GuidoVisitor::startmeasure () {
	fMeasNum++;
	fMeasureEmpty = true;
	if (fComments) {
		stringstream s; string comment;
		s << "   (* meas. ";
		s << fMeasNum;
		s << " *) ";
		comment="\n"+s.str();
		Sguidoelement elt = new_guidoelement (comment);
		add (elt);
	}
}

//________________________________________________________________________
void TXML2GuidoVisitor::visite ( SPWPart& elt ) { debug

	fCurrentPart = fScan.getPartSummary(elt->getID());
    if (!(TPartSummary*)fCurrentPart) {
        cerr << "Warning: part id " << elt->getID() << " without summary" << endl;
        return;
    }

    long voices = fCurrentPart->countVoices ();
    if (!voices) voices = 1;
	fStaffNum = 0xfff;	// initialized to a value we'll unlikely encounter
	for (long i = 0; i< voices; i++) {
        fBeamOpened = false;
        fCurrentVoice = fCurrentPart->getVoice(i);
        long mainstaff = fCurrentPart->getStaffIndex(fCurrentPart->getMainStaff(fCurrentVoice));
        if (fStaffNum == mainstaff) {
            fStaffPass++;    
        }
        else {
            fStaffPass = 0;
            fCurrentStaff = fStaffNum = mainstaff;
        }

        Sguidoelement seq = new_guidoseq();
        push (seq);
	
        Sguidoelement tag = new_guidotag("staff");
        tag->add (new_guidoparam(fStaffNum, false));
        add(tag);

        if (fHeaderPending) {
            if ((TScoreHeader *)fScore->scoreHeader())
                guidoheader (fScore->scoreHeader());
            fHeaderPending = false;
        }
        if (!fStaffPass) partheader(fScore->scoreHeader());
			
		fStemDirection = TGraphNote::undefined;
        fMeasNum = 0;
        vvector<SPWMeasure>::const_iterator next, meas = elt->measures().begin();
        if (meas!=elt->measures().end()) {
            startmeasure();
			(*meas)->accept(*this);
            measurend(*meas, kFirst);
            meas++;
        }
        for ( ; meas!=elt->measures().end();) {
            startmeasure();
            (*meas)->accept(*this);
			next = meas;
            measurend(*meas, ++next==elt->measures().end() ? kLast : kMiddle);
			meas++;
		}

        pop();
    }
}

//________________________________________________________________________
void TXML2GuidoVisitor::visite ( SPartGroup& elt ) { debug
}

//________________________________________________________________________
void TXML2GuidoVisitor::visite ( SPartList& elt ) { debug
	elt->parts().accept(*this);
}

//________________________________________________________________________
void TXML2GuidoVisitor::visite ( SPitch& elt ) { debug
}

//________________________________________________________________________
void TXML2GuidoVisitor::visite ( SRepeat& elt ) { debug
}

//________________________________________________________________________
void TXML2GuidoVisitor::visite ( SRest& elt ) { debug
}

//________________________________________________________________________
//! \todo support of the MIDI prog change
void TXML2GuidoVisitor::visite ( SScoreInstrument& elt ) { debug
/*	Sguidoelement tag = new_guidotag("instr");
    tag->add (new_guidoparam(elt->getName()));
	add (tag);
*/
}

//________________________________________________________________________
void TXML2GuidoVisitor::addInstr (string instr) {
	Sguidoelement tag = new_guidotag("instr");
	stringstream s1, s2; 
	int offset = instr.size() * 2;

	s1 << "dx=-" << offset << "hs";
	tag->add (new_guidoparam(instr));
	tag->add (new_guidoparam(s1.str(), false));
	tag->add (new_guidoparam("dy=-5hs", false));
	add (tag);

	tag = new_guidotag("systemFormat");
	tag->add (new_guidoparam(""));
	s2 << "dx=" << offset << "hs";
	tag->add (new_guidoparam(s2.str(), false));
	add (tag);	
}

//________________________________________________________________________
void TXML2GuidoVisitor::visite ( SScorePart& elt ) { debug
	if (elt->getID() != fCurrentPart->getID()) return;

	if (!elt->getPartName().empty()) {
		addInstr (elt->getPartName());
	}
	else if (!elt->getPartAbbrev().empty()) {
		addInstr (elt->getPartAbbrev());
	}

	if ((TIdentification *)elt->identification())
		elt->identification()->accept(*this);
	elt->scoreInstruments().accept(*this);
	elt->midiInstruments().accept(*this);
}

//________________________________________________________________________
void TXML2GuidoVisitor::visite ( SScorePartwise& elt ) { debug
	fScore = elt;
	elt->accept(fScan);
    Sguidoelement chord = new_guidochord ();
    fStack.push(chord);
	elt->partList().accept(*this);
}

//________________________________________________________________________
void TXML2GuidoVisitor::visite ( SSegno& elt ) { debug
/*
	tag is now suppported vua the sound element for consistency reasons
	
	Sguidoelement tag = new_guidotag("segno");
	add (tag);
*/
}

//________________________________________________________________________
void TXML2GuidoVisitor::visite ( SSound& elt ) { debug
	stringstream s;
	Sguidoelement tag = 0;

	if (elt->getDacapo() != YesNo::undefined) {
		tag = new_guidotag("daCapo");
	}
	else if (elt->getDalsegno() != TSound::undefined) {
		tag = new_guidotag("dalSegno");
		s << "id=" << elt->getDalsegno();
		tag->add(new_guidoparam(s.str(), false));
	}
	else if (elt->getTocoda() != TSound::undefined) {
		tag = new_guidotag("daCoda");
		s << "id=" << elt->getTocoda();
		tag->add(new_guidoparam(s.str(), false));
	}
	else if (elt->getFine() != TSound::undefined) {
		tag = new_guidotag("fine");
		s << "id=" << elt->getFine();
		tag->add(new_guidoparam(s.str(), false));
	}
	else if (elt->getSegno() != TSound::undefined) {
		tag = new_guidotag("segno");
		s << "id=" << elt->getSegno();
		tag->add(new_guidoparam(s.str(), false));
	}
	else if (elt->getCoda() != TSound::undefined) {
		tag = new_guidotag("coda");
		s << "id=" << elt->getCoda();
		tag->add(new_guidoparam(s.str(), false));
	}
	if (tag) add (tag);
}

//________________________________________________________________________
void TXML2GuidoVisitor::visite ( SStrongAccent& elt ) { debug
}

//________________________________________________________________________
void TXML2GuidoVisitor::visite ( SSlur& elt ) { debug
    int place = elt->placement().get();
    int num = elt->getNumber();

	static int slurnum=TTieSlur::undefined;
	static bool ignore=false;

	stringstream s;
	s << "slur";
	if ((elt->getType() == StartStop::start) && (fNotePass == before)) {
		s << "Begin";
        if (num != TTieSlur::undefined) {
			s << ':' << num;
            if ((fSlurs.flag & StartStop::start) && (fSlurs.flag & StartStop::stop)) {
				s << '0';
				slurnum = num;
				ignore = true;
			}
		}
		Sguidoelement tag = new_guidotag(s.str());
        if (place == TPlacement::below)
            tag->add (new_guidoparam("curve=\"down\"", false));
		add(tag);
	}
	if ((elt->getType() == StartStop::stop) && (fNotePass == after)) {
		s << "End";
        if (num != TTieSlur::undefined) {
			s << ':' << num;
			if (ignore) ignore = false;
			else if (num == slurnum) {
				s << '0';
				slurnum = TTieSlur::undefined;
			} 
		}
		Sguidoelement tag = new_guidotag(s.str());
		add(tag);
	}
}

//________________________________________________________________________
void TXML2GuidoVisitor::visite ( STie& elt ) { debug
    int place = elt->placement().get();
    int num = elt->getNumber();
	if ((elt->getType() == StartStop::stop) && (fNotePass == after)) {
		Sguidoelement tag = new_guidotag("tieEnd");
        if (num != TTieSlur::undefined)
            tag->add (new_guidoparam(num, false));
		add(tag);
	}
	if ((elt->getType() == StartStop::start) && (fNotePass == before)) {
		Sguidoelement tag = new_guidotag("tieBegin");
        if (num != TTieSlur::undefined)
            tag->add (new_guidoparam(num, false));
        if (place == TPlacement::below)
            tag->add (new_guidoparam("curve=\"down\"", false));
		add(tag);
	}
}

//________________________________________________________________________
/*
void TXML2GuidoVisitor::visite ( STieSlur& elt ) { debug
    STie tie; tie.cast((TTieSlur *)elt);
    SSlur slur; slur.cast((TTieSlur *)elt);
    string baseTag;
    if (tie) baseTag = "tie";
    else if (slur) baseTag = "slur";
    else return;		// unexpected class
   	
	if (slur) {
		visite (slur);
		return;
	}

    int place = elt->placement().get();
    int num = elt->getNumber();
	if ((elt->getType() == StartStop::start) && (fNotePass == before)) {
		Sguidoelement tag = new_guidotag(baseTag+"Begin");
        if (num != TTieSlur::undefined)
            tag->add (new_guidoparam(num, false));
        if (place == TPlacement::below)
            tag->add (new_guidoparam("curve=\"down\"", false));
		add(tag);
	}
	if ((elt->getType() == StartStop::stop) && (fNotePass == after)) {
		Sguidoelement tag = new_guidotag(baseTag+"End");
        if (num != TTieSlur::undefined)
            tag->add (new_guidoparam(num, false));
		add(tag);
	}
}
*/

//________________________________________________________________________
void TXML2GuidoVisitor::visite ( STimeModification& elt ) { debug
}

//______________________________________________________________________________
//! time representation is translated literaly ie "3/4" or "3+2/4" or "3/4+2/4"
//! \todo check that the guido handles composite measures (and how)
void TXML2GuidoVisitor::guidotime(STimeSign& elt)
{
	if (fStaffPass) return;

    stringstream s; string time; string sep ="";
    vector<long>::const_iterator beat = elt->getBeats().begin();
    vector<long>::const_iterator type = elt->getBeatTypes().begin();
    while (beat != elt->getBeats().end()) {
        if (*type == TTimeSign::groupbeats) {
            s << sep << *beat << "+";
            sep = "";
        }
        else { 
            s << sep << *beat << "/" << *type;
            sep = "+";
        }
        beat++; type++;
    }
    s >> time;
    current()->add (new_guidoparam(time));
}

//________________________________________________________________________
//! \todo check the way unmeasured time is handled
//! \todo check the symbol translation and handle the single number symbol
void TXML2GuidoVisitor::visite ( STimeSign& elt ) { debug
	if (fStaffPass) return;

	Sguidoelement tag = new_guidotag("meter");
    push (tag);
    if (!elt->measured()) {
        tag->add (new_guidoparam(""));
    }
    else {
    	switch (elt->getSymbol()) {
            case TTimeSign::common:		tag->add (new_guidoparam("C")); break;
            case TTimeSign::cut:		tag->add (new_guidoparam("C/")); break;
            default:					guidotime(elt); 
        }
        if (fGenerateBars) 
 	      	tag->add (new_guidoparam("autoBarlines=\"off\"", false));
        fCurTimeSign = elt->rational();
    }
    pop();
}

//________________________________________________________________________
void TXML2GuidoVisitor::visite ( STranspose& elt ) { debug
}

//________________________________________________________________________
void TXML2GuidoVisitor::visite ( STuplet& elt ) { debug
}

//________________________________________________________________________
void TXML2GuidoVisitor::visite ( STupletDesc& elt ) { debug
}

//________________________________________________________________________
void TXML2GuidoVisitor::visite ( SUnpitched& elt ) { debug
}

//________________________________________________________________________
void TXML2GuidoVisitor::visite ( SWavyLine& elt ) { debug
}

//________________________________________________________________________
void TXML2GuidoVisitor::visite ( SWedge& elt ) { debug
	if (fStaffPass) return;
/*
	Sguidoelement tag;
	switch (elt->getType()) {
		case TWedge::crescendo:
			tag = new_guidotag("crescBegin");
			fCrescPending = true;
			add (tag);
			break;
		case TWedge::diminuendo:
			tag = new_guidotag("dimBegin");
			fCrescPending = false;
			add (tag);
			break;
		case TWedge::stop:
			tag = new_guidotag(fCrescPending ? "crescEnd" : "dimEnd");
			add (tag);
			break;
	}
*/
}

//________________________________________________________________________
void TXML2GuidoVisitor::visite ( SWords& elt ) { debug
	if (fStaffPass) return;
/*
	Sguidoelement tag = new_guidotag("text");
    tag->add (new_guidoparam(elt->getValue()));
    add( tag);
*/
}
