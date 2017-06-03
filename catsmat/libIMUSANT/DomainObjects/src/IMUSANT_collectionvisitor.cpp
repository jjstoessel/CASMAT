/*
 *  IMUSANT_collectionvisitor.cpp
 *  imusant
 *
 *  Created by Jason Stoessel on 24/06/06.
 *  Copyright 2006 Jason Stoessel. All rights reserved.
 *
 *	This class is a visitor to IMUSANT_score for the purposes of collecting musical data for further manipulation.
 */

#include "IMUSANT_collectionvisitor.h"
#include "IMUSANT_chord.h"
#include "IMUSANT_measure.h"
#include "IMUSANT_part.h"
#include "IMUSANT_partlist.h"
#include "IMUSANT_score.h"
#include "IMUSANT_barline.h"
#include "IMUSANT_marker_interval.h"
#include "search.h"
#include "suffixtree.h"
#include "iterator.h"

#include <algorithm>

using namespace std;
using namespace ns_suffixtree;

namespace IMUSANT
{

S_IMUSANT_pitch_vector new_IMUSANT_pitch_vector()
{ IMUSANT_pitch_vector* o = new IMUSANT_pitch_vector(); assert(o!=0); return o; }
    
S_IMUSANT_rhythm_vector new_IMUSANT_rhythm_vector()
{ IMUSANT_rhythm_vector* o = new IMUSANT_rhythm_vector(); assert(o!=0); return o; }
    
IMUSANT_collection_visitor::IMUSANT_collection_visitor()
{
	fInChord = false;
	fLastNote = nullptr;
	fCurrentPartID = 0;
	fIgnoreRepeatedPitches = false;
}

#pragma mark IMUSANT_attribute handler
void IMUSANT_collection_visitor::visit ( S_IMUSANT_attributes& elt )
{
}

#pragma mark IMUSANT_barline handler
void IMUSANT_collection_visitor::visit ( S_IMUSANT_barline& elt)
{
	if ((elt->getBarStyle()==IMUSANT_barline::heavy ||
         elt->getBarStyle()==IMUSANT_barline::light_light ||
         elt->getBarStyle()==IMUSANT_barline::light_heavy ||
         elt->getBarStyle()==IMUSANT_barline::heavy_light ||
         elt->getBarStyle()==IMUSANT_barline::heavy_heavy)
        &&
        elt->getLocation()==IMUSANT_barline::right)
	{
		fLastNote = NULL;
	}
}

#pragma mark IMUSANT_chord handler
void IMUSANT_collection_visitor::visit ( S_IMUSANT_chord& elt )
{
	fInChord = true;
	elt->getNotes().accept(*this);
	fInChord = false;
}

#pragma mark IMUSANT_comment handler		
void IMUSANT_collection_visitor::visit ( S_IMUSANT_comment& elt )
{
}

#pragma mark IMUSANT_element handler
void IMUSANT_collection_visitor::visit ( S_IMUSANT_element& elt )
{
}

#pragma mark IMUSANT_lyric handler
void IMUSANT_collection_visitor::visit ( S_IMUSANT_lyric& elt )
{
    int j = 0;
    for (auto i = elt->getSyllables().begin(); i!=elt->getSyllables().end(); i++, j++) {
        fLyrics[j] += *i;
        if (elt->getSyllabic()==IMUSANT_syllabic::end || elt->getSyllabic()==IMUSANT_syllabic::single) fLyrics[j]+= " ";
    }
    
}

#pragma mark IMUSANT_measure handler
void IMUSANT_collection_visitor::visit ( S_IMUSANT_measure& elt )
{
	elt->elements().accept(*this);
}

#pragma mark IMUSANT_note handler

void IMUSANT_collection_visitor::visit ( S_IMUSANT_note& elt )
{
	if (elt == 0 || elt->getStyle()==IMUSANT_NoteStyle::hidden) return; //skip hidden notes
	
	if (elt->getType()==IMUSANT_NoteType::pitch)
	{
		if (fLastNote!=0 && !elt->isTiedPrevious())
		{
			if (!(fIgnoreRepeatedPitches && elt->pitch()==fLastNote->pitch()) )
			{
				//exact interval storage
				IMUSANT_interval interval(fLastNote->pitch(), elt->pitch());
				interval.setLocation(fCurrentPartID, fLastNote->getMeasureNum(), fLastNote->getNoteIndex(), fCurrentPartID, elt->getMeasureNum(), elt->getNoteIndex());
                fCurrentIntervalVector->add(interval);
				//contour symbol storage
				IMUSANT_contour_symbol symbol(fLastNote->pitch(), elt->pitch());
				symbol.setLocation(fCurrentPartID,fLastNote->getMeasureNum(), fLastNote->getNoteIndex(), fCurrentPartID, elt->getMeasureNum(), elt->getNoteIndex());
                fCurrentMelodicContour->push_back(symbol);
                fCurrentRhythmVector->push_back(*elt->duration());
			}
		}
        
        if (!elt->isTiedPrevious() && !(fIgnoreRepeatedPitches && elt->pitch()==fLastNote->pitch())){
            fCurrentPitchVector->push_back(*elt->pitch());
        }
		
		fLastNote = elt;
	}
	else if (elt->getType()==IMUSANT_NoteType::rest)
	{	//currently segmenting for all rests
		//IMUSANT_interval empty;
		//fIntervalVector->add(empty);
		fLastNote = nullptr;
	}
	else//is non-pitched therefore interval can't be calculated
	{
		fLastNote = nullptr;
	}

	elt->lyrics().accept(*this);
}

#pragma mark IMUSANT_part handler
void IMUSANT_collection_visitor::visit ( S_IMUSANT_part& elt )
{
	//create part summary
	fLastNote = nullptr;
	fCurrentPartID++;
    fCurrentIntervalVector = new_IMUSANT_interval_vector();
    fCurrentIntervalVector->setMaximum(0x7fffffff);
    fCurrentMelodicContour = new_IMUSANT_contour();
    fCurrentPitchVector = new_IMUSANT_pitch_vector();
    fCurrentRhythmVector = new_IMUSANT_rhythm_vector();
	//call sub-elements
	elt->measures().accept(*this);
    //stow partwise derived data vectors, but only if they contain elements
    if (! fCurrentIntervalVector->getIntervals().empty())
    {
        fCurrentIntervalVector->add(IMUSANT_interval::MakeUniqueInterval()); //add unique terminator
        fPartwiseIntervalVectors.push_back(fCurrentIntervalVector);
    }
    
    if (! fCurrentMelodicContour->empty()) {
        fCurrentMelodicContour->push_back(IMUSANT_contour_symbol::MakeUniqueSymbol());
        fPartwiseContourVectors.push_back(fCurrentMelodicContour);
    }
    
    if (! fCurrentPitchVector->empty()) {
        fCurrentPitchVector->push_back(IMUSANT_pitch::MakeUniquePitch());
        fPartwisePitchVectors.push_back(fCurrentPitchVector);
    }
    if (!fCurrentRhythmVector->empty()) {
        //fCurrentRhythmVector->push_back(IMUSANT_duration::MakeUniqueDuration());
        fPartwiseRhythmVectors.push_back(fCurrentRhythmVector);
    }
}

#pragma mark IMUSANT_partlist handler
void IMUSANT_collection_visitor::visit ( S_IMUSANT_partlist& elt )
{
	elt->parts().accept(*this);
}

#pragma mark IMUSANT_score handler
void IMUSANT_collection_visitor::visit ( S_IMUSANT_score& elt )
{
	//initialise storage containers
	//fRhythmCollection = new_IMUSANT_rvec_collection();
	fMovementTitle = elt->getMovementTitle();
    fWorkTitle = elt->getWorkTitle();
    fWorkNum = elt->getWorkNum();
    fMovementNum = elt->getMovementNum();
    fCreator = elt->getCreator();
    fRights = elt->getRights();
    fScoreComments = elt->getComments();
    fSource = elt->getSource();
    fEditor = elt->getEditor();
    fDate = elt->getDate();
	
	if ((IMUSANT_partlist*)elt->partlist())
		elt->partlist()->accept(*this);
	//add unique teminator elements in anticipation of processing.
}


} //namespace IMUSANT
