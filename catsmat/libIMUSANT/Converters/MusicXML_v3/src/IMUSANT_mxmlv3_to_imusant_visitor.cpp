//
//  IMUSANT_mxmlv3_to_imusant_visitor.cpp
//  imusant
//
//  Created by Derrick Hill on 19/09/2015.
//
//  Changes:
//  24 March 2016   Handlers for <normal-type> and <normal-dots> added for time modification
//

#include <stdio.h>
#include <stdlib.h>

#include "IMUSANT_conversions.h"

#include "IMUSANT_mxmlv3_to_imusant_visitor.h"

namespace IMUSANT
{
    
#define debug(method) // cout << "Visiting " << method << endl; fflush(stdout)

    
    IMUSANT_mxmlv3_to_imusant_visitor::
    IMUSANT_mxmlv3_to_imusant_visitor()
    {
        
        
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_score_partwise& elt)
    {
        debug("S_score_partwise");
        fImusantScore = new_IMUSANT_score();
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_work_title& elt)
    {
        debug("S_work_title");
        assert(fImusantScore);
        fImusantScore->setWorkTitle(elt->getValue());
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_work_number& elt)
    {
        debug("S_work_title");
        assert(fImusantScore);
        fImusantScore->setWorkNum(elt->getValue());
    }
    
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_movement_title& elt)
    {
        debug("S_movement_title");
        assert(fImusantScore);
        fImusantScore->setMovementTitle(elt->getValue());
    }
    
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_movement_number& elt)
    {
        debug("S_movement_number");
        assert(fImusantScore);
        fImusantScore->setMovementNum(elt->getValue());
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_creator &elt)
    {
        debug("S_creator");
        STRPAIR creator;
        
        creator.first = elt->getAttributeValue("type");
        creator.second = elt->getValue();
        
        fImusantScore->addCreator(creator);
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_score_part& elt)
    {
        debug("S_score_part");
        assert(fImusantScore);
        
        S_IMUSANT_part part = new_IMUSANT_part();
        fCurrentPart = part;
        
        fNumberOfInstrumentsInPart = 0;
        
        part->setID(elt->getAttributeValue("id"));
        
        fImusantScore->addPart(part);
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_score_instrument & elt)
    {
        debug("S_score_instrument - NOT IMPLEMENTED YET");
        fNumberOfInstrumentsInPart++;
        
        if (fNumberOfInstrumentsInPart > 1)
        {
            MusicXML3_ElementNotImplemented e("S_score_instrument");
            throw e;
        }
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_part_name& elt)
    {
        debug("S_part_name");
        assert(fCurrentPart);
        fCurrentPart->setPartName(elt->getValue());
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_part_abbreviation& elt)
    {
        debug("S_part_abbreviation");
        assert(fCurrentPart);
        fCurrentPart->setPartAbbrev(elt->getValue());
    }
    
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_part& elt)
    {
        // The "part" element is outside the scope of the "score-part" element that we processed above.
        // Therefore whenever we encounter a "part" element we need to reset the fCurrentPart to
        // point to it.
        
        debug("S_part");
        
        string part_id = elt->getAttributeValue("id");
        
        if (! fImusantScore->getPartById(part_id, fCurrentPart))
        {
            MusicXML3_UnexpectedElement e("S_part [part_id = " + part_id + "]");
            throw e;
        }
        
        fTransposing = false;
        fTransposeDiatonic = 0;
        fTransposeChromatic = 0;
        fTransposeOctaveChange = 0;
        fTransposeDoubled = false;
    }

    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_attributes& elt)
    {
        fCurrent_attributes = new_IMUSANT_attributes();
        assert(fCurrent_attributes);
    }

    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_divisions &elt)
    {
        string divisions_str = elt->getValue();
        int divisions = atoi(divisions_str.c_str());
        fCurrentPart->setDivisions(divisions);
        //new
        fCurrent_attributes->setDivisions_(divisions);
        //TO DO: remove divisions, etc. from part to IMUSANT_measure in attributes member
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_voice &elt)
    {
        debug("S_voice");
        
        if (fInNoteElement)
        {
            string voice_str = elt->getValue();
            int voice = atoi(voice_str.c_str());
            fCurrentNote->setVoice(voice);
        }
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_clef &elt)
    {
        debug("S_clef Start");
        
        IMUSANT_clef the_clef(IMUSANT_clef::undefined, 0, 0);
        fCurrentClef = the_clef;
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_sign &elt)
    {
        debug("S_sign");
        
        string sign_value = elt->getValue();
        char sign_char = sign_value.at(0);
        fCurrentClef.setSign(sign_char);
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_line &elt)
    {
        debug("S_line");
        int line = atoi(elt->getValue().c_str());
        fCurrentClef.setLine(line);
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_clef_octave_change &elt)
    {
        debug("S_clef_octave_change");
        int octave_change = atoi(elt->getValue().c_str());
        fCurrentClef.setTransposition(octave_change);
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitEnd( S_clef &elt)
    {
        debug("S_clef End");
        
        if (fCurrentMeasure != 0)
        {
            fCurrentMeasure->setClef(fCurrentClef);
            //new
            fCurrent_attributes->setClef(fCurrentClef);
            fCurrentMeasure->setAttributes(fCurrent_attributes);
            // TODO: remove clef, etc. from IMUSANT_measure in favour of attributes member
        }
        else
        {
            MusicXML3_UnexpectedElement e("In S_clef - Expected fCurrentMeasure to be set but it is null");
            throw e;
        }
    }
    
    
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_measure& elt)
    {
        debug("S_measure");

        fCurrentMeasureNumber = elt->getAttributeIntValue("number", fCurrentMeasureNumber + 1);
        fCurrentNoteIndex = 0;  //reset on measure entry
        fCurrentAccidentals.clear(); //reset
        
        S_IMUSANT_measure measure = new_IMUSANT_measure();
        measure->setMeasureNum(static_cast<int>(fCurrentMeasureNumber));
        fCurrentMeasure = measure;
        
        if (fImusantScore)  //assert that uberclass has been instantiated.
        {
            fCurrentPart->addMeasure(measure);
        }
    }
    
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_barline& elt)
    {
//        <measure number="4" width="291.58">
//          <barline location="left">
//            <bar-style>heavy-light</bar-style>
//            <repeat direction="forward"/>
//          </barline>

        
        debug("S_barline - start");
        
        string location = elt->getAttributeValue("location");
        
        S_IMUSANT_barline barline = new_IMUSANT_barline();
        fCurrentBarline = barline;
        
        fCurrentBarline->setLocation(IMUSANT_barline::xmllocation(location));
        
        fInBarlineElement = true;
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitEnd( S_barline& elt)
    {
        debug("S_barline - end");
        
        fCurrentMeasure->addBarline(fCurrentBarline);
        
        fInBarlineElement = false;
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_bar_style& elt)
    {
        string bar_style = elt->getValue();
        
        fCurrentBarline->setBarStyle(IMUSANT_barline::xmlstyle(bar_style));
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_repeat& elt)
    {
        debug("S_repeat");
        
        S_IMUSANT_repeat repeat = new_IMUSANT_repeat();
       
        string direction_str = elt->getAttributeValue("direction");
        long times = elt->getAttributeLongValue("times", 0);
        
        IMUSANT_repeat::direction direction =  IMUSANT_repeat::xml(direction_str);
        repeat->setDirection(direction);
        repeat->setTimes(times);
        
        fCurrentBarline->setRepeat(repeat);
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_ending& elt)
    {
        debug("S_ending");
        
        // "Endings" are the alternative bars at the end of repeated pasages. e.g. first and second endings.
        
        S_IMUSANT_ending ending = new_IMUSANT_ending();
        
        string ending_type_str = elt->getAttributeValue("type");
        IMUSANT_ending::type ending_type = IMUSANT_ending::xml(ending_type_str);
        
        long ending_number = elt->getAttributeLongValue("number", 1);
        
        ending->setNumber(ending_number);
        ending->setType(ending_type);
        
        fCurrentBarline->setEnding(ending);
    }
    
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_key& elt)
    {
        // <key>
        //    <fifths>0</fifths>
        //    <mode>minor</mode>
        // </key>
        
        debug("S_key start");
        
        fInKeyElement = true;
        fCurrentKey = IMUSANT_key();
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitEnd( S_key& elt)
    {
        debug("S_key end");
        fInKeyElement = false;
        fCurrentPart->getCurrentMeasure()->setKey(fCurrentKey);
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_fifths& elt)
    {
        debug("S_fifths");
        if (fInKeyElement)
        {
            string fifths_value_str = elt->getValue();
            long fifths_value_long = atol(fifths_value_str.c_str());
            fCurrentKey.setFifths(static_cast<int>(fifths_value_long));
        }
        else
        {
            MusicXML3_UnexpectedElement e("In S_fifths - Expected to be in Key element");
            throw e;
        }
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_mode& elt)
    {
        debug("S_mode");
        if (fInKeyElement)
        {
            string mode_str = elt->getValue();
            IMUSANT_key::mode the_mode = IMUSANT_key::xmlmode(mode_str);
            fCurrentKey.setMode(the_mode);
        }
        else
        {
            MusicXML3_UnexpectedElement e("In S_mode, expected to be in Key element.");
            throw e;
        }
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_time& elt)
    {
        // <time>
        //    <beats>2</beats>
        //    <beat-type>4</beat-type>
        // </time>
        
        debug("S_time start");
        fInTimeElement = true;
        fCurrentTime = IMUSANT_time();
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitEnd( S_time& elt)
    {
        debug("S_time end");
        fInTimeElement = false;
        fCurrentPart->getCurrentMeasure()->setTime(fCurrentTime);
    }

    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_beats& elt)
    {
        debug("S_beats");
        
        if (fInTimeElement)
        {
            string numerator_str = elt->getValue();
            int the_numerator = atoi(numerator_str.c_str());
            fCurrentTime.addNumerator(the_numerator);
        }
        else
        {
            MusicXML3_UnexpectedElement e("In S_beats, expected to be in Time element.");
            throw e;
        }
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_beat_type& elt)
    {
        debug("S_beat_type");
        
        if (fInTimeElement)
        {
            string denominator_str = elt->getValue();
            int the_denominator = atoi(denominator_str.c_str());
            fCurrentTime.addDenominator(the_denominator);
        }
        else
        {
            MusicXML3_UnexpectedElement e("In S_beat_type, expected to be in Time element.");
            throw e;
        }
    }

    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_note& elt)
    {

// A regular note...
//        <note default-x="149">
//          <pitch>
//            <step>C</step>
//            <alter>1</alter>
//            <octave>5</octave>
//          </pitch>
//          <duration>2</duration>
//          <tie type="start"/>
//          <voice>1</voice>
//          <type>16th</type>
//          <stem default-y="18">up</stem>
//          <staff>1</staff>
//          <notations>
//            <tied type="start"/>
//            <slur number="1" placement="above" type="start"/>
//          </notations>
//        </note>
        

// A triplet...
//        <note default-x="18.21" default-y="-35.00">
//          <pitch>
//            <step>F</step>
//            <alter>1</alter>
//            <octave>4</octave>
//          </pitch>
//          <duration>2</duration>
//          <voice>1</voice>
//          <type>eighth</type>
//            <time-modification>
//              <actual-notes>3</actual-notes>
//              <normal-notes>2</normal-notes>
//            </time-modification>
//          <stem>up</stem>
//          <beam number="1">begin</beam>
//          <notations>
//            <tuplet type="start" bracket="no"/>
//          </notations>
//          </note>
        
        debug("S_note start");
        
        fInNoteElement = true;
        fCurrentNoteInChord = false;    // We don't yet know that this Note is in a chord.
        fPreviousNote = fCurrentNote;
        fCurrentNote = new_IMUSANT_note();
        fCurrentNote->setMeasureNum(fCurrentMeasure->getMeasureNum());
        fCurrentNote->setNoteIndex(++fCurrentNoteIndex);
        fCurrentNote->setStaffName(fCurrentPart->getPartName());
        fCurrentNumberofDotsOnNote = 0;
        fCurrentNoteTimeModification.set(1,1);
        fCurrentNoteDurationType.set(0,0);
        fCurrentNormalNumberofDotsOnNote = 0;
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitEnd( S_note& elt)
    {
        debug("S_note end");
        
        if (fInNoteElement)
        {
            S_IMUSANT_duration duration = new_IMUSANT_duration();
            duration->set(fCurrentNoteDurationType,
                          fCurrentNumberofDotsOnNote,
                          fCurrentNoteTimeModification,
                          fCurrentNormalNoteDurationType,
                          fCurrentNormalNumberofDotsOnNote);
            fCurrentNote->setDuration(*duration);
            
            //Set note type to hidden if "invisible" in the score
            string printobj = elt->getAttributeValue("print-object");
            if (printobj=="no") {
                fCurrentNote->setStyle(IMUSANT_NoteStyle::hidden);
            }
            // We ignore cue notes and don't add them to the current measure.
            // This is a bit fugly but it avoids having to add this guard into
            // all the sub elements of Note.
            if (! fInCueNote)
            {
                fCurrentMeasure->addNote(fCurrentNote);
            }
            else
            {
                fInCueNote = false;
            }
        }
        
        fInNoteElement = false;
        
        if (! fCurrentNoteInChord)
        {
            fInChord = false;
        }
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_rest& elt)
    {
//        <note>
//          <rest/>
//          <duration>9</duration>
//          <voice>1</voice>
//          <type>eighth</type>
//          <dot/>
//          <time-modification>
//            <actual-notes>3</actual-notes>
//            <normal-notes>3</normal-notes>
//            <normal-type>eighth</normal-type>
//          </time-modification>
//          <notations>
//            <tuplet type="start" bracket="yes"/>
//          </notations>
//        </note>
        
        debug("S_rest");
        if (fInNoteElement)
        {
            fCurrentNote->setType(IMUSANT_NoteType::rest);
        }
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart(S_duration& elt)
    {
        //
        // See VersionOne S-01114.
        //
        // See the MusicXML v3 documentation for the "divisions" element,
        // which is within the "attributes" element on "part".
        //
        
        debug("S_duration");
        
        int duration = atoi(elt->getValue().c_str());
        TRational duration_rat;
        duration_rat.set(duration, 1);
        
        int divisions = fCurrentPart->getDivisions();
        TRational divisions_rat;
        divisions_rat.set(divisions, 1);
        
        // (1/4 divided by Divisions) * Duration = Type
        
        TRational note_type = (IMUSANT_duration::crochet /  divisions_rat) * duration_rat;
        
        note_type.rationalise();
        
        fCurrentNoteDurationType = note_type;
        //23 April 2017 - assume until there is a element indicating different that normal note is the same
        fCurrentNormalNoteDurationType = note_type;
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart(S_fermata& elt)
    {
        debug("S_fermata");
        
        if (fInNoteElement)
        {
            debug("     Fermata on Note");
            fCurrentNote->setFermata(true);
        }
        else if (fInBarlineElement)
        {
            debug("     Fermata on Barline");
            fCurrentBarline->setFermata(true);
        }
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart(S_type& elt)
    {
        // <note... >
        //   ...
        //   <type>128th</type>
        //   ...
        //
        
        debug("S_type");
        if (fInNoteElement)
        {
            string note_type_str = elt->getValue();
            TRational note_type = IMUSANT_duration::xmlv3(note_type_str);
            fCurrentNoteDurationType = note_type;
        }
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_dot& elt)
    {
        // There can be multiple dots on any given note.  We just have
        // to count them.
        
        debug("S_dot");
        
        if (fInNoteElement)
        {
            fCurrentNumberofDotsOnNote++;
        }
    }

    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_stem& elt)
    {
        debug("S_stem");

        string direction = elt->getValue();
        fCurrentNote->setStemDirection(direction);
    }


    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_time_modification& elt)
    {
        //            <time-modification>
        //              <actual-notes>3</actual-notes>
        //              <normal-notes>2</normal-notes>
        //              <normal-type>eighth</normal-type> //optional
        //            </time-modification>
        
        debug("S_time_modification");
        
        if (fInNoteElement)
        {
            string element_name;
            int actual_notes = 1;
            int normal_notes = 1;
            MusicXML2::xmlelement *next_element;
            
            for (int index = 0 ; index < elt->elements().size()  ; index++ )
            {
                next_element = elt->elements()[index];
                element_name = next_element->getName();
                
                if (element_name.compare("actual-notes") == 0)
                {
                    actual_notes = stoi(next_element->getValue());
                }
                
                
                if (element_name.compare("normal-notes") == 0)
                {
                    normal_notes = stoi(next_element->getValue());
                }
                
                if (element_name.compare("normal-type") == 0)
                {
                    string note_type_str = next_element->getValue();
                    TRational note_type = IMUSANT_duration::xmlv3(note_type_str);
                    fCurrentNormalNoteDurationType = note_type;
                }
                
                if (element_name.compare("normal-dot") == 0)
                {
                    fCurrentNormalNumberofDotsOnNote = stoi(next_element->getValue());
                }
            }
            
            fCurrentNoteTimeModification.set(actual_notes, normal_notes);
        }
    }
        
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_pitch& elt)
    {
        //        <pitch>
        //          <step>C</step>
        //          <alter>1</alter>
        //          <octave>5</octave>
        //        </pitch>
        
        debug("S_pitch start");
        fInPitchElement = true;
        fCurrentPitch = new_IMUSANT_pitch();
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitEnd( S_pitch& elt)
    {
        debug("S_pitch end");
        
        if (fTransposing)
        {
            fCurrentPitch->transpose(fTransposeDiatonic, fTransposeChromatic, fTransposeOctaveChange, fTransposeDoubled);
        }
        
        fCurrentNote->setPitch(*fCurrentPitch);
        fCurrentNote->setType(IMUSANT_NoteType::pitch);
        fInPitchElement = false;
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_step& elt)
    {
        debug("S_step");
        string note_name = elt->getValue();
        fCurrentPitch->setName(note_name);
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_alter& elt)
    {
        debug("S_alter");
        string alteration = elt->getValue();
        fCurrentPitch->setAlteration(alteration);
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_octave& elt)
    {
        debug("S_octave");
        string octave = elt->getValue();
        fCurrentPitch->setOctave(octave);
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_lyric& elt)
    {
        debug("S_lyric");
        
        fCurrentLyric = new_IMUSANT_lyric();
        
        fCurrentLyric->setNumber_v3(elt->getAttributeValue("number"));
        fCurrentLyric->setName(elt->getAttributeValue("name"));

        // Need to implement:
        // Syllabic
        // Elision?
        // Extend?
        // Humming?
        // end-line?
        // end-paragraph?
        
        fCurrentNote->addLyric(fCurrentLyric);
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart(S_text& elt)
    {
        debug("S_text");
        fCurrentLyric->addSyllable(elt->getValue());
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart(S_syllabic& elt)
    {
        debug("S_syllabic");
        
        IMUSANT_syllabic::type syllabic_val = IMUSANT_syllabic::xml(elt->getValue());
        fCurrentLyric->setSyllabic(syllabic_val);
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_tie& elt)
    {
//        This relies on the fact that a tie starts and ends on juxtaposing
//        notes - a single tie cannot span multiple notes.
//        Therefore we just wait until we see a tie stop, and then
//        link the current note to the previous note.
        
        debug("S_tie");
        
        string type_attribute = elt->getAttributeValue("type");
        
        if (type_attribute.compare("stop") == 0)
        {
            fCurrentNote->setPreviousTieNote(fPreviousNote);
        }
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_accidental& elt)
    {
        debug("S_accidental");
        
        string accidental_str = elt->getValue();
        IMUSANT_accidental::accident accident = IMUSANT_accidental::xml(accidental_str);
        S_IMUSANT_accidental accidental = new_IMUSANT_accidental();
        accidental->setAccident(accident);
        
        fCurrentNote->setAccidental(*accidental);
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_grace& elt)
    {
        debug("S_grace");
        
        fCurrentNote->setStyle(IMUSANT_NoteStyle::grace);
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_cue& elt)
    {
        debug("S_cue");
        
        fInCueNote = true;
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_unpitched& elt)
    {
        debug("S_unpitched");
        fCurrentNote->setType(IMUSANT_NoteType::nonpitch);
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart(S_chord& elt)
    {
        debug("S_chord");
        
        fCurrentNoteInChord = true;
        
        if (fInChord)
        {
            // Just add the current note into the current chord.
            fCurrentChord->add(fCurrentNote);
        }
        else
        {
            // this is the first </chord> element so add the previous note and the current note into a new chord.
            fCurrentChord = new_IMUSANT_chord();
            fCurrentMeasure->addElement(fCurrentChord);
            fCurrentChord->add(fPreviousNote);
            fCurrentChord->add(fCurrentNote);
            fInChord = true;
        }
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_transpose& elt)
    {
        debug("S_transpose");
        
        fTransposing = true;
        fTransposeDiatonic = 0;
        fTransposeChromatic = 0;
        fTransposeOctaveChange = 0;
        fTransposeDoubled = false;
    }
    
     void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_diatonic& elt)
    {
        debug("S_diatonic");
        
        string str_val = elt->getValue();
        fTransposeDiatonic = atoi(str_val.c_str());
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_chromatic& elt)
    {
        debug("S_chromatic");
        
        string str_val = elt->getValue();
        fTransposeChromatic = atoi(str_val.c_str());
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_octave_change& elt)
    {
        debug("S_octave_change");
        
        string str_val = elt->getValue();
        fTransposeOctaveChange = atoi(str_val.c_str());
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_double& elt)
    {
        debug("S_double");
        fTransposeDoubled = true;
    }
    
    
}
