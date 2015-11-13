/*
 *  TXML2IMUSANTVisitor.cpp
 *  imusant
 *
 *  Created by Jason Stoessel on 28/03/06.
 *  Copyright 2006 Jason Stoessel. All rights reserved.
 *
 Changes:
	28/3/06 - First implementation
	16/6/06 - lyric support added
	18/6/06 - support for barlines added
 - creator and right types modified to store pair in vector
 To do:		HIGHER PRIORITY:
 slurs
 LOWER PRIORITY
 measure and note attached expressions
 Barlines, repeats et al.
 tempo marks and directions
 */




#include "TXML2IMUSANTVisitor.h"
#include "LibMusicXML.h"
#include "IMUSANT_element.h"
#include "IMUSANT_note.h"
#include "IMUSANT_chord.h"
#include "IMUSANT_types.h"
#include "IMUSANT_barline.h"

#include <sstream>
#include <iostream>
#include <string>

namespace IMUSANT
{
    
#define debug // cout << "visite " << __LINE__ << endl; fflush(stdout);
#define XML2IMUSANTDebug	0
    
#if XML2IMUSANTDebug
#	include <fstream>
    ofstream xml2IMUSANT("xml2imusant-debug.txt",ios_base::trunc);
#	define dbgStream   xml2IMUSANT
#else
#	define dbgStream   cout
#endif
    
    /*!
     \todo support of IDs for tags other than slurs
     */
    //broken with libMusicXML 1.0
    //________________________________________________________________________
    SXML2IMUSANTVisitor newXML2IMUSANTVisitor(bool comments=true, bool checkStem=true, bool bar=false)
    {
        TXML2IMUSANTVisitor * o = new TXML2IMUSANTVisitor(comments, checkStem, bar);
        assert(o!=0);
        return o;
    }
    
    
    //________________________________________________________________________
    TXML2IMUSANTVisitor::TXML2IMUSANTVisitor (bool comments, bool stem, bool bar)
    : fCurTimeSign (0,1), fComments(comments), fCheckStem(stem)
    {
        fCrescPending = false;
        fInRepeat = false;
        fCurrentDivision = 1;
        fInTieSlur = fInChord = false;
        fStemDirection = TGraphNote::undefined;
        fCurrentIMUSANTPart = 0;
        fNote = 0;
        
    }
#pragma mark TAccidental handler
    //________________________________________________________________________
    // Handles note attached accidental signs, not actual inflections/alterations
    //________________________________________________________________________
    void TXML2IMUSANTVisitor::visite ( SAccidental& elt )
    { debug
        if (fNote!=0)
        {
            S_IMUSANT_accidental acc = new_IMUSANT_accidental();
            //currently strings map from TAccidental to IMUSANT_accidental
            acc->setAccident(IMUSANT_accidental::xml(TAccidental::xmlaccidental(elt->getAccident())));
            acc->setCautionary(elt->getCautionary());
            //if the editorial flag is set, transfer, or save accidental
            if (elt->getEditorial()==YesNo::yes)
                acc->setEditorial(elt->getEditorial());
            else if (acc->getAccident()!=IMUSANT_accidental::undefined)
            {
                //this will erase any accidental on the same pitch from fPreviousAccidentals
                fPreviousAccidentals[make_pair(fNote->pitch()->name(),fNote->pitch()->octave())]=acc->getAccident();
            }
            
            fNote->setAccidental(acc);
        }
    }
    
    //________________________________________________________________________
    /*void TXML2IMUSANTVisitor::visite ( SArticulationElement& elt ) { debug
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
     default:
     ;
     }
     if (tag) {
     push(tag);
     fPendingPops++;
     }
     }*/
    
    //________________________________________________________________________
    /*void TXML2IMUSANTVisitor::visite ( SArticulations& elt ) { debug
     elt->articulations().accept(*this);
     }*/
#pragma mark TAttributes handler
    //________________________________________________________________________
    void TXML2IMUSANTVisitor::visite ( SAttributes& elt ) { debug
        if (elt->getDivision() != TAttributes::undefined)
            fCurrentDivision = elt->getDivision();
        
        elt->editorial().accept(*this);
        if ((TKey *)elt->key()) 			elt->key()->accept(*this);
        if ((TTimeSign*)elt->timeSign()) 	elt->timeSign()->accept(*this);
        elt->clefs().accept(*this);
        if ((TTranspose *)elt->transpose()) 	elt->transpose()->accept(*this);
        if ((TDirective *)elt->directive()) 	elt->directive()->accept(*this);
    }
    
    //________________________________________________________________________
    /*void TXML2IMUSANTVisitor::visite ( SBackup& elt ) { debug
     }*/
    
#pragma mark TBarline handler
    //________________________________________________________________________
    /*!
     visit of a barline may add several elements: \\bar, \\fermata, \\repeatBegin
     \\repeatEnd ...
     */
    void TXML2IMUSANTVisitor::visite ( SBarline& elt )
    { debug
        
        if (fCurrentIMUSANTPart->getCurrentMeasure()!=0)
        {
            S_IMUSANT_barline barline = new_IMUSANT_barline();
            
            barline->setLocation(IMUSANT_barline::xmllocation(TBarline::xmllocation(elt->getLocation())));
            barline->setBarStyle(IMUSANT_barline::xmlstyle(TBarline::xmlstyle(elt->getBarStyle())));
            
            if ((TFermata *)elt->fermata())
            {
            }
            
            if ((TEnding*)elt->ending())
            {
                S_IMUSANT_ending ending = new_IMUSANT_ending();
                ending->setNumber(elt->ending()->getNum());
                
                switch (elt->ending()->getType())
                {
                    case TEnding::start:
                        ending->setType(IMUSANT_ending::start);
                        fInRepeat = true;
                        break;
                    case TEnding::stop:
                        if (fInRepeat)
                        {
                            ending->setType(IMUSANT_ending::stop);
                            fInRepeat = false;
                        }
                        break;
                }
                
                barline->setEnding(ending);
            }
            if ((TRepeat*)elt->repeat())
            {
                S_IMUSANT_repeat repeat = new_IMUSANT_repeat();
                
                switch (elt->repeat()->getDirection())
                {
                    case TRepeat::forward:
                        repeat->setDirection(IMUSANT_repeat::forward);
                        break;
                    case TRepeat::backward:
                        repeat->setDirection(IMUSANT_repeat::backward);
                        repeat->setTimes(elt->repeat()->getTimes());
                        if (!(TEnding*)elt->ending() || (elt->ending()->getType()!=TEnding::stop))
                        {
                            //end of repeat
                        }
                        break;
                }
                
                barline->setRepeat(repeat);
            }
            
            fCurrentIMUSANTPart->getCurrentMeasure()->addElement(barline);
        }
    }
    
    //________________________________________________________________________
    /*void TXML2IMUSANTVisitor::visite ( SBeam& elt ) { debug
     }*/
    
    //________________________________________________________________________
    /*void TXML2IMUSANTVisitor::visite ( SBracket& elt ) { debug
     }*/
#pragma mark TChord handler
    //________________________________________________________________________
    void TXML2IMUSANTVisitor::visite ( SChord& elt ) { debug
        long staff = elt->getStaff();
        staff = fCurrentPart->getStaffIndex(staff);
        
        if (elt->getStyle() == TNote::cue) {
            return; // cue notes are ignored for the moment
            if ((staff != fStaffNum) || fStaffPass) return;
        }
        //else if (elt->getVoice() != fCurrentVoice) return;
        
        S_IMUSANT_chord chord = new_IMUSANT_chord();
        
        for (vvector<SNote>::const_iterator note = elt->notes().begin(); note != elt->notes().end(); note++ )
        {
            chord->add(IMUSANT_note(*note));
        }
        
        S_IMUSANT_measure currentMeasure = fCurrentIMUSANTPart->getCurrentMeasure(); //draw on class variable?
        
        if (currentMeasure != 0)
        {
            currentMeasure->addElement(chord);
        }
        else
        {
            cerr << "TChord Handler called w/o measure instantiation" << endl;
        }
        
    }
    
#pragma mark TClef handler
    //________________________________________________________________________
    /*!
     \todo translation of none and TAB clefs
     \measure contextual function
     */
    void TXML2IMUSANTVisitor::visite ( SClef& elt ) { debug
        //long staff = fCurrentPart->getStaffIndex(elt->getStaffNum());
        //if ((staff != fStaffNum) || fStaffPass) return;
        
        char sign = IMUSANT_clef::undefined;
        short line = -1;
        
        //convert XML numerical clef to IMUSANT character clef
        switch (elt->getSign()) {
            case TClef::G:
                sign = IMUSANT_clef::G_clef;
                break;
            case TClef::F:
                sign = IMUSANT_clef::F_clef;
                break;
            case TClef::C:
                sign = IMUSANT_clef::C_clef;
                break;
            case TClef::percussion:
                sign = IMUSANT_clef::percussion;
                break;
            case TClef::TAB:
                sign = IMUSANT_clef::tablature;
                break;
        }
        
        if (elt->getLine() != TClef::undefined) line = elt->getLine();
        
        IMUSANT_clef clef(sign, line, elt->getOctave());
        
        S_IMUSANT_measure currentMeasure = fCurrentIMUSANTPart->getCurrentMeasure(); //draw on class variable?
        
        if (currentMeasure != 0)
        {
            currentMeasure->setClef(clef);
        }
        else
        {
            cerr << "TKey Handler called w/o measure instantiation" << endl;
        }
    }
    
    //________________________________________________________________________
    /*void TXML2IMUSANTVisitor::visite ( SCoda& elt ) { debug
     }*/
    
#pragma mark TCreator handler
    //________________________________________________________________________
    /*!
     \todo handling the different creator types as defined in MusicXML.
     There is actually no corresponding tag apart the \p composer tag in guido.
     */
    void TXML2IMUSANTVisitor::visite ( SCreator& elt ) { debug
        
        if (fIMUSANTScore)
        {
            fIMUSANTScore->addCreator(make_pair(elt->getType(), elt->getName()));
        }
    }
#pragma mark TDirection and TDirectionType handlers
    //________________________________________________________________________
    void TXML2IMUSANTVisitor::visite ( SDirection& elt ) { debug
        elt->types().accept(*this);
    }
    
    //________________________________________________________________________
    void TXML2IMUSANTVisitor::visite ( SDirectionType& elt ) { debug
        elt->elements().accept(*this);
    }
    
    //________________________________________________________________________
    /*void TXML2IMUSANTVisitor::visite ( SDirective& elt ) { debug
     if (fStaffPass) return;
     
     Sguidoelement tag = new_guidotag("text");
     tag->add (new_guidoparam(elt->getValue()));
     add( tag);
     
     }*/
    
    //________________________________________________________________________
    /*void TXML2IMUSANTVisitor::visite ( SDynamic& elt ) { debug
     if (fStaffPass) return;
     vector<TDynamic::dynamic>::const_iterator dyn;
     for (dyn = elt->dynamics().begin(); dyn != elt->dynamics().end(); dyn++) {
     Sguidoelement tag = new_guidotag("intens");
     tag->add (new_guidoparam(elt->xmldynamic(*dyn)));
     add (tag);
     }
     }*/
    
    //________________________________________________________________________
    /*void TXML2IMUSANTVisitor::visite ( SEncoding& elt ) { debug
     }*/
    
    //________________________________________________________________________
    /*void TXML2IMUSANTVisitor::visite ( SEnding& elt ) { debug
     }*/
    
    //________________________________________________________________________
    /*void TXML2IMUSANTVisitor::visite ( SFermata& elt ) { debug
     }*/
    
    //________________________________________________________________________
    /*void TXML2IMUSANTVisitor::visite ( SForward& elt ) { debug
     long voice = elt->getVoice();
     if ((voice != TForward::undefined) && (voice != fCurrentVoice)) return;
     TRational r(elt->getDuration(), fCurrentDivision*4);
     r.rationalise();
     guidonoteduration dur (r.getNumerator(), r.getDenominator());
     Sguidoelement note = new_guidonote((unsigned short)voice, "empty", 0, dur, "");
     add (note);
     fMeasureEmpty = false;
     }*/
    
    //________________________________________________________________________
    /*/void TXML2IMUSANTVisitor::visite ( SGraceNote& elt ) { debug
     }*/
#pragma mark TGraphNote handler
    //________________________________________________________________________
    void TXML2IMUSANTVisitor::visite ( SGraphNote& elt ) { debug
        
        //elt->printout().accept (*this);
        if ((TAccidental *)elt->accidental()) elt->accidental()->accept (*this);
        //if ((TTimeModification *)elt->timemodification()) elt->timemodification()->accept (*this);
        //if ((TNoteHead *)elt->notehead()) elt->notehead()->accept (*this);
        //elt->beamList().accept(*this);
        //elt->notationList().accept(*this);
    }
#pragma mark SIdentification handler
    //________________________________________________________________________
    void TXML2IMUSANTVisitor::visite ( SIdentification& elt ) { debug
        
        /*if (fIMUSANTScore)
         {
         vvector<SCreator>::iterator creator_iter;
         vvector<SRights>::iterator rights_iter;
         string creators, rights;
         
         for (creator_iter = elt->creators().begin(); creator_iter != elt->creators().end(); creator_iter++ )
         {
         creators += (*creator_iter)->getType(); creators += ": "; creators += (*creator_iter)->getName(); creators += ". ";
         }
         
         fIMUSANTScore->setComposer(creators);
         
         for ( rights_iter = elt->rights().begin(); rights_iter != elt->rights().end(); rights_iter++ )
         {
         rights += (*rights_iter)->getRight();
         }
         
         fIMUSANTScore->setRights(rights);
         fIMUSANTScore->setSource(elt->getSource());
         
         }*/
        if (fIMUSANTScore) fIMUSANTScore->setSource(elt->getSource());
        elt->creators().accept(*this);
        elt->rights().accept(*this);
        //Handle Encoding?
    }
#pragma mark TKey handler
    //________________________________________________________________________
    void TXML2IMUSANTVisitor::visite ( SKey& elt ) { debug
        
        S_IMUSANT_measure currentMeasure = fCurrentIMUSANTPart->getCurrentMeasure(); //draw on class variable?
        
        if (currentMeasure != 0)
        {
            fCurrentKey = IMUSANT_key(elt->getFifths(), IMUSANT_key::ConvertXML2IMUSANTMode(elt->getMode()), elt->getCancel());
            
            currentMeasure->setKey(fCurrentKey);
        }
        else
        {
            cerr << "TKey Handler called w/o measure instantiation" << endl;
        }
        
    }
#pragma mark TLyric handler
    //________________________________________________________________________
    /*!
     \The SLyric visit handler - This is the only way to safely handle SLyric, don't try to handle in note.
     */
    void TXML2IMUSANTVisitor::visite ( SLyric& elt )
    {
        if (fNote!=0)
        {
            fLyric = new_IMUSANT_lyric();
            fLyric->setNumber(elt->getNumber());
            //get first syllable
            fLyric->setSyllabic(IMUSANT_syllabic::MusicXML2IMUSANTSyllabic(elt->getSyllabic()));
            fLyric->addSyllable(elt->getText());
            fNote->addLyric(fLyric);
        }
        else
            fLyric = 0;
        
        elt->getMultipleParts().accept(*this);
    }
    //________________________________________________________________________
    //! \todo complete translation of TMetronome
    /*void TXML2IMUSANTVisitor::visite ( SMetronome& elt ) { debug
     // don't know how to translate the equal from
     if ((TSymbolicNoteDuration *)elt->equal()) return;
     
     Sguidoelement tag = new_guidotag("tempo");
     stringstream s; string param;
     TRational r, rdot(3,2);
     int dots = elt->getDots();
     NoteType::rational(elt->getBeat(), r);
     while (dots>0) {
     r *= rdot;
     dots--;
     }
     r.rationalise();
     s << (string)r << "=" << elt->getPerMinute();
     s >> param;
     tag->add (new_guidoparam(""));
     tag->add (new_guidoparam(param));
     add (tag);
     }*/
    
    //________________________________________________________________________
    /*void TXML2IMUSANTVisitor::visite ( SMidiInstrument& elt ) { debug
     
     if (elt->getProgram() != TMidiInstrument::undefined) {
     Sguidoelement tag = new_guidotag("instr");
     tag->add (new_guidoparam(elt->getName()));
     stringstream s;
     s << "MIDI " << elt->getProgram();
     tag->add (new_guidoparam(s.str()));
     add (tag);
     }
     
     }*/
#pragma mark SMultipleLyricPart handler
    //________________________________________________________________________
    void TXML2IMUSANTVisitor::visite ( SMultipleLyricPart& elt )
    {
        if (fNote!=0 && !fNote->lyrics().empty()) //first element must be added by SLyric handler
        {
            fLyric->setSyllabic(IMUSANT_syllabic::MusicXML2IMUSANTSyllabic(elt->getSyllabic()));
            fLyric->addSyllable(elt->getText());
        }
    }
    //________________________________________________________________________
    /*void TXML2IMUSANTVisitor::visite ( SNotation& elt ) { debug
     elt->list().accept(*this);
     }*/
    
    //________________________________________________________________________
    /*bool TXML2IMUSANTVisitor::checkgrace (const SNote& note) {
     if (note->getStyle() == TNote::grace) {
     Sguidoelement tag = new_guidotag("grace");
     push(tag);
     return true;
     }
     return false;
     }*/
    
    //________________________________________________________________________
    /*bool TXML2IMUSANTVisitor::checkcue (const SNote& note) {
     if (note->getStyle() == TNote::cue) {
     Sguidoelement tag = new_guidotag("cue");
     push(tag);
     return true;
     }    return false;
     }*/
    
    //________________________________________________________________________
#pragma mark TNote Handler
    //________________________________________________________________________
    /*
     \measure contextual function
     */
    S_IMUSANT_note TXML2IMUSANTVisitor::IMUSANT_note (const SNote& note)
    {
        unsigned short	voice = 0, oct = 0;
        signed short semitones = 0;
        IMUSANT_pitch::type name = IMUSANT_pitch::undefined;
        stringstream s;
        
        if (note->isRest()) {
            //these are default values -- change to case with rest element.
        }
        else {
            SPitch pitch = note->pitch();
            name = IMUSANT_pitch::xml(TPitch::xmlpitch(pitch->getStep()));
            if ( name == IMUSANT_pitch::undefined) cout << "erreur: pitch name empty: " << pitch->getStep() << endl;
            
            oct = pitch->getOctave();
            
            float alter = pitch->getAlter();
            if (alter > 0) {
                while (alter > 0)
                {
                    semitones+= 1;
                    alter-=1;
                }
                
            }
            else if (alter < 0) {
                while (alter < 0)
                {
                    semitones -= 1;
                    alter+=1;
                }
            }
        }
        
        S_IMUSANT_duration dur = new_IMUSANT_duration();
        
        SGraphNote gn = note->graphics();
        
        if (!note->isGrace() && gn)
        {
            TRational r;
            long	dots = 0;
            if (gn->getType()!=NoteType::undefined)
            {
                r = NoteType::rational(gn->getType(),r);
                dots = gn->getDots();
            }
            else //whole bar rests do not have a GraphNote type
            {
                r = TRational(note->getDuration(), fCurrentDivision*4);
                dots = IMUSANT_duration::NormaliseDuration(r);
            }
            
            r.rationalise();
            
            TRational timemod(1,1);
            if (gn->timemodification())
            {
                timemod.set(gn->timemodification()->getActualNotes(), gn->timemodification()->getNormalNotes());
            }
            dur->set(r, dots, timemod);
        }
        
        
        if (gn) {
            if (note->isGrace()) {
                TRational r;
                NoteType::rational(gn->getType(), r);
                r.rationalise();
                dur->set(r, gn->getDots(),1);
            }
            if (gn->getVoice() != TGraphNote::undefined)
                voice = (unsigned short)gn->getVoice();
            //checkstem (note);
            fNotePass = before;
            gn->beamList().accept(*this);
            gn->notationList().accept(*this);
        }
        
        S_IMUSANT_pitch pitch = new_IMUSANT_pitch();
        pitch->setName(name);
        pitch->setOctave(oct);
        pitch->setVoice(voice);
        pitch->setAlteration(semitones);
        
        S_IMUSANT_note the_note = new_IMUSANT_note(); //this instance will be passed to measure
        
        the_note->setPitch(pitch);
        the_note->setDuration(dur);
        the_note->setMeasureNum(fMeasNum);
        the_note->setNoteIndex(++fNoteIndex);
        
        //set note stle to hidden if non-printing object, or grace; defaults to normal
        if (gn->printout().getPrintObject() == YesNo::no)
            the_note->setStyle(IMUSANT_NoteStyle::hidden);
        else if (note->isGrace())
            the_note->setStyle(IMUSANT_NoteStyle::grace);
        //default is pitch
        if (note->isRest())
            the_note->setType(IMUSANT_NoteType::rest);
        else if (note->isUnpitched())
            the_note->setType(IMUSANT_NoteType::nonpitch);
        
        //Handling ties - here we pass a handle to a vector to prevent the destruction of the actual object
        //The routine pairs last tied notes with previous tied notes according to voice.
        //Could also be handled as a pair/map with SNote handle to facilitate comparison
        
        if (note->tieNext() != 0)
        {
            S_IMUSANT_note* handle =  new S_IMUSANT_note;
            assert(handle!=NULL);
            
            *handle = the_note;
            
            fPreviousTieNoteList.push_back(handle);
        }
        
        if (note->tiePrevious() != 0 && !fPreviousTieNoteList.empty())
        {
            vector<S_IMUSANT_note*>::iterator iter;
            
            for (iter=fPreviousTieNoteList.begin(); iter!=fPreviousTieNoteList.end(); iter++)
            {
                if ((**iter)->pitch()->voice() == the_note->pitch()->voice())
                {
                    the_note->setPreviousTieNote(**iter);
                    fPreviousTieNoteList.erase(iter);
                    //test
                    //the_note->durationWithTies();
                    break;
                }
            }
        }
        
        fMeasureEmpty = false;
        fNotePass = after;
        
        return the_note;
    }
    
    void TXML2IMUSANTVisitor::checkaccidental()
    {
        //check if editorial flag is it is correct:
        //The assumption here is that all unsigned (i.e. without accidental)
        //alterations/inflections not in key signature are editorial.  This denies the later convention that
        //all pitches inflected earlier in a bar are similar inflected.
        if (fNote && fNote->pitch() && fNote->pitch()->alteration() && !fNote->accidental())
        {
            if (fCurrentKey.PitchAlterInSignature(fNote->pitch()->name(),fNote->pitch()->alteration()))
            {
                signed short alteration = fNote->pitch()->alteration();
                
                for	(	ACCIDENTALMAP::iterator iter = fPreviousAccidentals.begin();
                     iter!=fPreviousAccidentals.end();
                     iter++ )
                {
                    if ((*iter).first.first==fNote->pitch()->name())
                    {
                        alteration += (*iter).first.second;
                        S_IMUSANT_accidental acc = new_IMUSANT_accidental();
                        acc->setAccident(IMUSANT_accidental::AlterToAccident(alteration));
                        acc->setEditorial(YesNo::yes);
                        fNote->setAccidental(acc);
                        break;
                    }
                }
            }
            else
            {
                S_IMUSANT_accidental acc = new_IMUSANT_accidental();
                acc->setAccident(IMUSANT_accidental::AlterToAccident(fNote->pitch()->alteration()));
                acc->setEditorial(YesNo::yes);
                fNote->setAccidental(acc);
            }
        }
    }
    
    //________________________________________________________________________
    void TXML2IMUSANTVisitor::visite ( SNote& elt ) { debug
        
        // don't know how to output a note without voice and staff information
        if (!(TGraphNote *)elt->graphics()) return;
        
        S_IMUSANT_measure currentMeasure = fCurrentIMUSANTPart->getCurrentMeasure(); //draw on class variable?
        
        if (currentMeasure != 0)
        {
            switch (elt->getStyle())
            {
                case TNote::normal:
                    fNote = IMUSANT_note(elt);
                    currentMeasure->addElement(fNote);
                    break;
                case TNote::cue:
                    //cueNote (elt);
                    break;
                case TNote::grace:
                    //graceNote (elt);
                    break;
            }
            
            elt->getLyrics().accept(*this);
            
            //if (elt->graphics())
            //	elt->graphics()->printout().accept(*this);
            //if ((TExpression *)elt->expression())
            //	elt->expression()->accept(*this);
            //if ((elt->getStyle() == TNote::grace) && (TGraceNote *)elt->graceNote())
            //	elt->graceNote()->accept(*this);
            //if((TPitch *)elt->pitch())
            //	elt->pitch()->accept (*this);
            if ((TGraphNote *)elt->graphics())
                elt->graphics()->accept (*this);
            
            checkaccidental();
        }
        else
        {
            cerr << "TNote Handler called w/o measure instantiation" << endl;
        }
    }
    
    //________________________________________________________________________
    /*void TXML2IMUSANTVisitor::visite ( SNoteHead& elt ) { debug
     }*/
    
    //________________________________________________________________________
    /*void TXML2IMUSANTVisitor::visite ( SOctaveShift& elt ) { debug
     }*/
#pragma mark TPWMeasure Handler
    //________________________________________________________________________
    void TXML2IMUSANTVisitor::visite ( SPWMeasure& elt ) { debug
        
        fMeasNum = elt->getNumber();
        fNoteIndex = 0;  //reset on measure entry
        fPreviousAccidentals.clear(); //reset
        
        S_IMUSANT_measure measure = new_IMUSANT_measure();
        
        measure->setMeasureNum(fMeasNum);
        
        if (fIMUSANTScore)  //assert that uberclass has been instantiated.
        {
            fCurrentIMUSANTPart->addMeasure(measure);
            elt->data().accept(*this);
        }
    }
    
    //________________________________________________________________________
    /*void TXML2IMUSANTVisitor::partheader ( SScoreHeader& elt ) { debug
     if ((TPartList *)elt->partList())
     elt->partList()->accept(*this);
     }*/
#pragma mark TScoreHeader handler
    //________________________________________________________________________
    void TXML2IMUSANTVisitor::visite ( SScoreHeader& elt ) { debug
        
        //create IMUSANT score class and fill out "header" information
        fIMUSANTScore = new_IMUSANT_score(elt->getMovementTitle());
        fIMUSANTScore->setMovementNum( elt->getMovementNum() );
        
        //calls functions for TWork, TIdentification and TPartlist
        //TWork and TIdentification handlers fill out more "header" info
        if ((TWork *)elt->work())
            elt->work()->accept(*this);
        if ((TIdentification *)elt->identification())
            elt->identification()->accept (*this);
        if ((TPartList *)elt->partList())
            elt->partList()->accept (*this);
    }
    
    
#pragma mark TPWPart Handler
    //________________________________________________________________________
    void TXML2IMUSANTVisitor::visite ( SPWPart& elt ) { debug
        
        fCurrentKey = IMUSANT_key(); //reset to default
        //set the current part for subsequent calls using the MusicXML ID collected for each part in TScorePart handler
        fCurrentIMUSANTPart = fIMUSANTScore->partlist()->getPart(elt->getID());
        assert(fCurrentIMUSANTPart!=NULL);
        
        long voices = 1;
        fStaffNum = 0xfff;
        fCurrentPart = fScan.getPartSummary(elt->getID());
        
        //check voice count
        if ((TPartSummary*)fCurrentPart)
        {
            
            voices = fCurrentPart->countVoices();
            for (long i = 0; i<voices; i++)
            {
                fCurrentVoice = fCurrentPart->getVoice(i);
                long mainstaff = fCurrentPart->getStaffIndex(fCurrentPart->getMainStaff(fCurrentVoice));
                if (fStaffNum == mainstaff)
                {
                    fStaffPass++;
                }
                else
                {
                    fStaffPass = 0;
                    fCurrentStaff = fStaffNum = mainstaff;
                }
            }
        }
        else
        {
            cerr << "Warning: part id " << elt->getID() << " without summary" << endl;
        }
        
        fCurrentIMUSANTPart->setVoiceCount(voices);
        
        elt->measures().accept(*this);
        
        fPreviousTieNoteList.clear(); //at completion remove any tied notes stored for staff
    }
    
    //________________________________________________________________________
    /*void TXML2IMUSANTVisitor::visite ( SPartGroup& elt ) { debug
     }*/
    
    //________________________________________________________________________
    /*void TXML2IMUSANTVisitor::visite ( SPartList& elt ) { debug
     elt->parts().accept(*this);
     }*/
    
    //________________________________________________________________________
    /*void TXML2IMUSANTVisitor::visite ( SPitch& elt ) { debug
     }*/
    
    //________________________________________________________________________
    /*void TXML2IMUSANTVisitor::visite ( SRepeat& elt ) { debug
     }*/
    
    //________________________________________________________________________
    /*void TXML2IMUSANTVisitor::visite ( SRest& elt ) { debug
     }*/
    
#pragma mark TRights Handler
    //________________________________________________________________________
    void TXML2IMUSANTVisitor::visite ( SRights& elt )
    {
        if (fIMUSANTScore)
        {
            fIMUSANTScore->addRights(make_pair(elt->getType(), elt->getRight()));
        }
    }
    
    //________________________________________________________________________
    //! \todo support of the MIDI prog change
    /*void TXML2IMUSANTVisitor::visite ( SScoreInstrument& elt ) { debug
     Sguidoelement tag = new_guidotag("instr");
     tag->add (new_guidoparam(elt->getName()));
     add (tag);
     
     }*/
    
#pragma mark TScorePart Handler
    //________________________________________________________________________
    //All part instances are instantiated before TPart function is called
    void TXML2IMUSANTVisitor::visite ( SScorePart& elt ) { debug
        //if (elt->getID() != fCurrentPart->getID()) return;
        
        S_IMUSANT_part part = new_IMUSANT_part();
        
        assert(fIMUSANTScore);
        
        fIMUSANTScore->addPart(part);
        
        if (!elt->getPartName().empty()) {
            part->setPartName(elt->getPartName());
        }
        else if (!elt->getPartAbbrev().empty()) {
            part->setPartAbbrev(elt->getPartAbbrev());
        }
        
        if (!elt->getID().empty())
            part->setID(elt->getID());
        
        if ((TIdentification *)elt->identification())
            elt->identification()->accept(*this);
        elt->scoreInstruments().accept(*this);
        if ((TMidiDevice *)elt->mididevice())
            elt->mididevice()->accept(*this);
        elt->midiInstruments().accept(*this);
    }
#pragma mark TScorePartwise handler
    //________________________________________________________________________
    // First visit to class
    void TXML2IMUSANTVisitor::visite ( SScorePartwise& elt )
    {
        debug
        fScore = elt;
        elt->accept(fScan); //fScan is a visitor to scan score for information
        
        if ((TScoreHeader *)elt->scoreHeader())
            elt->scoreHeader()->accept(*this);
        elt->partList().accept(*this);
    }
    
    //________________________________________________________________________
    /*void TXML2IMUSANTVisitor::visite ( SSegno& elt ) { debug
     }*/
    
    //________________________________________________________________________
    /*void TXML2IMUSANTVisitor::visite ( SSound& elt ) { debug
     }*/
    
    //________________________________________________________________________
    /*void TXML2IMUSANTVisitor::visite ( SStrongAccent& elt ) { debug
     }*/
    
    //________________________________________________________________________
    /*void TXML2IMUSANTVisitor::visite ( SSlur& elt ) { debug
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
     */
    
#pragma mark TTie handler
    //________________________________________________________________________
    /*void TXML2IMUSANTVisitor::visite ( STie& elt ) { debug
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
     */
    //________________________________________________________________________
    /*
     void TXML2IMUSANTVisitor::visite ( STieSlur& elt ) { debug
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
    /*void TXML2IMUSANTVisitor::visite ( STimeModification& elt ) { debug
     }*/
    
#pragma mark TTimeSign handler
    //______________________________________________________________________________
    //! time representation 
    //measure contextual function
    //! \todo check the way unmeasured time is handled
    //! \todo check the symbol translation and handle the single number symbol
    void TXML2IMUSANTVisitor::visite ( STimeSign& elt ) { debug
        //if (fStaffPass) return;
        
        S_IMUSANT_measure currentMeasure = fCurrentIMUSANTPart->getCurrentMeasure();
        
        if (currentMeasure != 0)
        {
            IMUSANT_time time( elt->getBeats(), elt->getBeatTypes(), IMUSANT_time::ConvertXML2IMUSANTSymbol(elt->getSymbol()));
            
            currentMeasure->setTime(time);
        }
        else
        {
            cerr << "TTimeSign Handler called w/o measure instantiation" << endl;
        }
        
        fCurTimeSign = elt->rational();
        
    }
    
    //________________________________________________________________________
    /*void TXML2IMUSANTVisitor::visite ( STranspose& elt ) { debug
     }*/
    
    //________________________________________________________________________
    /*void TXML2IMUSANTVisitor::visite ( STuplet& elt ) { debug
     }*/
    
    //________________________________________________________________________
    /*void TXML2IMUSANTVisitor::visite ( STupletDesc& elt ) { debug
     }*/
    
    //________________________________________________________________________
    /*void TXML2IMUSANTVisitor::visite ( SUnpitched& elt ) { debug
     }*/
    
    //________________________________________________________________________
    /*void TXML2IMUSANTVisitor::visite ( SWavyLine& elt ) { debug
     }*/
    
    //________________________________________________________________________
    /*void TXML2IMUSANTVisitor::visite ( SWedge& elt ) { debug
     if (fStaffPass) return;
     
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
     
     }*/
#pragma mark TWords handler
    //________________________________________________________________________
    //This is an element type of DirectionType
    //handle Rex's mensuration signs added as measure attached directions
    //Cdot is not handled correctly at present
    void TXML2IMUSANTVisitor::visite ( SWords& elt ) 
    { debug
        
        if (!fIMUSANTScore && !fCurrentIMUSANTPart->getCurrentMeasure()) return;
        
        if (elt->getValue()=="Ø"||elt->getValue()=="ø")
        {
            fCurrentIMUSANTPart->getCurrentMeasure()->getTime().setSymbol(IMUSANT_time::cutO);
        }
        else if (elt->getValue()=="¢")
        {
            fCurrentIMUSANTPart->getCurrentMeasure()->getTime().setSymbol(IMUSANT_time::cutC);
        }
        else if (elt->getValue()=="Ç")
        {
            fCurrentIMUSANTPart->getCurrentMeasure()->getTime().setSymbol(IMUSANT_time::Cdot);
        }
        else if (elt->getValue()==".")
        {
            cerr << "Warning: unhandled word direction type \"" << elt->getValue() << "\""
            << ", part-id " << fCurrentIMUSANTPart->getID() 
            << ", measure " << fCurrentIMUSANTPart->getCurrentMeasure()->getMeasureNum() << endl;
        }
        
    }
    
#pragma mark TWork handler
    //________________________________________________________________________
    //Visited from TScoreHeader handler
    void TXML2IMUSANTVisitor::visite ( SWork& elt )
    {
        if (fIMUSANTScore)
        {
            fIMUSANTScore->setWorkTitle( elt->getTitle());
            fIMUSANTScore->setWorkNum( elt->getNum());
        }
    }
    
} //namespace IMUSANT