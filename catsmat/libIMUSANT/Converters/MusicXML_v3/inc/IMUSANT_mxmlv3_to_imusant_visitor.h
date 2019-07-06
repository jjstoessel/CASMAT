//
//  IMUSANT_mxmlv3_to_imusant_visitor.h
//  imusant
//
//  Created by Derrick Hill on 19/09/2015.
//
//  This class visits the nodes in a libMusicXML v3 score and translates
//  this into an IMUSANT representation. 
//
// To use this class you do something like this (error handling omitted):
//
//   MusicXML2::xmlreader r;
//   MusicXML2::SXMLFile sxml_file = r.read(path_to_music_xml_3_file);
//   MusicXML2::Sxmlelement sxml_element = sxml_file->elements();
//   IMUSANT_mxmlv3_to_imusant_visitor parser;
//   tree_browser<MusicXML2::xmlelement> browser(&parser);   // 
//   browser.browse(*sxml_element);
//   return parser.get_imusant_score();
//

#ifndef imusant_IMUSANT_mxmlv3_to_imusant_visitor_h
#define imusant_IMUSANT_mxmlv3_to_imusant_visitor_h

#include "IMUSANT_score.h"
#include "IMUSANT_pitch.h"
#include "IMUSANT_types.h"
#include "IMUSANT_note.h"
#include "IMUSANT_barline.h"
#include "IMUSANT_chord.h"
#include "IMUSANT_mxmlv3_exceptions.h"

#include "IMUSANT_converters_shared_types.h"

#include "elements/typedefs.h"


using namespace MusicXML2;

namespace IMUSANT
{
    
    class IMUSANT_mxmlv3_to_imusant_visitor
    :
    public visitor<S_score_partwise>,
    public visitor<S_work_title>,
    public visitor<S_work_number>,
    public visitor<S_movement_title>,
    public visitor<S_movement_number>,
    public visitor<S_creator>,
    public visitor<S_score_part>,
    public visitor<S_score_instrument>,
    public visitor<S_part_name>,
    public visitor<S_part_abbreviation>,
    public visitor<S_part>,
    public visitor<S_attributes>,
    public visitor<S_divisions>,
    public visitor<S_voice>,
    public visitor<S_clef>,
    public visitor<S_sign>,
    public visitor<S_line>,
    public visitor<S_clef_octave_change>,
    public visitor<S_measure>,
    public visitor<S_barline>,
    public visitor<S_bar_style>,
    public visitor<S_repeat>,
    public visitor<S_ending>,
    public visitor<S_key>,
    public visitor<S_fifths>,
    public visitor<S_mode>,
    public visitor<S_time>,
    public visitor<S_beats>,
    public visitor<S_beat_type>,
    public visitor<S_note>,
    public visitor<S_rest>,
    public visitor<S_duration>,
    public visitor<S_stem>,
    public visitor<S_fermata>,
    public visitor<S_type>,
    public visitor<S_dot>,
    public visitor<S_time_modification>,
    public visitor<S_pitch>,
    public visitor<S_step>,
    public visitor<S_alter>,
    public visitor<S_octave>,
    public visitor<S_lyric>,
    public visitor<S_text>,
    public visitor<S_syllabic>,
    public visitor<S_tie>,
    public visitor<S_accidental>,
    public visitor<S_grace>,
    public visitor<S_cue>,
    public visitor<S_unpitched>,
    public visitor<S_chord>,
    public visitor<S_transpose>,
    public visitor<S_diatonic>,
    public visitor<S_chromatic>,
    public visitor<S_octave_change>,
    public visitor<S_double>
    {
        
    public:
        
        IMUSANT_mxmlv3_to_imusant_visitor();
        
        virtual ~IMUSANT_mxmlv3_to_imusant_visitor()
        {
        }
        
        S_IMUSANT_score get_imusant_score()
        {
            assert(fImusantScore!=0);
            return fImusantScore;
        }

    protected:
        
        virtual void visitStart( S_score_partwise& elt);
        virtual void visitStart( S_work_title& elt);
        virtual void visitStart( S_work_number& elt);
        virtual void visitStart( S_movement_title& elt);
        virtual void visitStart( S_movement_number& elt);
        virtual void visitStart( S_creator& elt);
        
        virtual void visitStart( S_score_part& elt);
        virtual void visitStart( S_score_instrument& elt);
        virtual void visitStart( S_part_name& elt);
        virtual void visitStart( S_part_abbreviation& elt);
        
        virtual void visitStart( S_part& elt);
        virtual void visitStart( S_divisions& elt);
        virtual void visitStart( S_voice& elt);

        virtual void visitStart( S_attributes& elt);
        virtual void visitStart( S_clef& elt);
        virtual void visitStart( S_sign& elt);
        virtual void visitStart( S_line& elt);
        virtual void visitStart( S_clef_octave_change& elt);
        virtual void visitEnd( S_clef& elt);
        
        virtual void visitStart( S_measure& elt);
        virtual void visitStart( S_barline& elt);
        virtual void visitEnd( S_barline& elt);
        
        virtual void visitStart( S_bar_style& elt);
        virtual void visitStart( S_repeat& elt);
        virtual void visitStart( S_ending& elt);
        
        virtual void visitStart( S_key& elt);
        virtual void visitEnd( S_key& elt);
        virtual void visitStart( S_fifths& elt);
        virtual void visitStart( S_mode& elt);
        // REVISIT - do we need to handle the Cancel element under Key?
        
        virtual void visitStart( S_time& elt);
        virtual void visitEnd( S_time& elt);
        virtual void visitStart( S_beats& elt);
        virtual void visitStart( S_beat_type& elt);
        // REVISIT - do we need to handle "symbol" element under Time?
        
        virtual void visitStart( S_note& elt);
        virtual void visitEnd( S_note& elt);
        virtual void visitStart( S_rest& elt);
        virtual void visitStart( S_duration& elt);
        virtual void visitStart( S_stem& elt);
        
        virtual void visitStart( S_fermata& elt);
        
        virtual void visitStart( S_type& elt);
        virtual void visitStart( S_dot& elt);
        virtual void visitStart( S_time_modification& elt);
        
        virtual void visitStart( S_pitch& elt);
        virtual void visitEnd( S_pitch& elt);
        virtual void visitStart( S_step& elt);
        virtual void visitStart( S_alter& elt);
        virtual void visitStart( S_octave& elt);
        
        virtual void visitStart( S_lyric& elt);
        virtual void visitStart( S_text& elt);
        virtual void visitStart(S_syllabic& elt);
        
        
        virtual void visitStart( S_tie& elt);
        
        virtual void visitStart( S_accidental& elt);
        
        virtual void visitStart( S_grace& elt);
        virtual void visitStart( S_cue& elt);
        virtual void visitStart( S_unpitched& elt);
        
        virtual void visitStart( S_chord& elt);
        
        virtual void visitStart( S_transpose& elt);
        virtual void visitStart( S_diatonic& elt);
        virtual void visitStart( S_chromatic& elt);
        virtual void visitStart( S_octave_change& elt);
        virtual void visitStart( S_double& elt);
        
    private:
        
        S_IMUSANT_score     fImusantScore;
        
        S_IMUSANT_part      fCurrentPart;
        int                 fCurrentMeasureNumber;
        S_IMUSANT_measure   fCurrentMeasure;
        S_IMUSANT_attributes fCurrent_attributes;
        IMUSANT_clef        fCurrentClef;
        bool                fInChord = false;
        bool                fCurrentNoteInChord = false;
        S_IMUSANT_chord     fCurrentChord;
        S_IMUSANT_barline   fCurrentBarline;
        int                 fCurrentNoteIndex;
        ACCIDENTALMAP       fCurrentAccidentals;
        bool                fInKeyElement = false;
        IMUSANT_key         fCurrentKey;
        bool                fInTimeElement = false;
        IMUSANT_time        fCurrentTime;
        bool                fInNoteElement = false;
        bool                fInBarlineElement = false;
        bool                fInCueNote = false;
        S_IMUSANT_note      fCurrentNote;
        S_IMUSANT_note      fPreviousNote;
        TRational           fCurrentNoteDurationType;
        int                 fCurrentNumberofDotsOnNote;
        TRational           fCurrentNoteTimeModification;
        TRational           fCurrentNormalNoteDurationType;
        int                 fCurrentNormalNumberofDotsOnNote;
        bool                fInLyricElement = false;
        S_IMUSANT_lyric     fCurrentLyric;
        bool                fInPitchElement = false;
        S_IMUSANT_pitch     fCurrentPitch;
        int                 fNumberOfInstrumentsInPart = 0;
        
        bool                fTransposing = false;
        int                 fTransposeDiatonic = 0;
        int                 fTransposeChromatic = 0;
        int                 fTransposeOctaveChange = 0;
        bool                fTransposeDoubled = false;
        
    };
    
}



#endif
