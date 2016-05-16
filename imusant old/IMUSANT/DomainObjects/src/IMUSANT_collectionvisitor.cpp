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
    
IMUSANT_collection_visitor::IMUSANT_collection_visitor()
{
	fInChord = false;
	fLastNote = 0;
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
		fLastNote = 0;
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
				interval.setLocation(fCurrentPartID, fLastNote->getMeasureNum(), fLastNote->getNoteIndex(), elt->getMeasureNum(), elt->getNoteIndex());
#ifdef OLD
				fIntervalVector->add(interval);
#endif
#ifdef NEW
                fCurrentIntervalVector->add(interval);
#endif
				//contour symbol storage
				IMUSANT_contour_symbol symbol(fLastNote->pitch(), elt->pitch());
				symbol.setLocation(fCurrentPartID,fLastNote->getMeasureNum(), fLastNote->getNoteIndex(), elt->getMeasureNum(), elt->getNoteIndex());
				fMelodicContour->push_back(symbol);
			}
		}
		
		//pitch storage
		if (!elt->isTiedPrevious() && !(fIgnoreRepeatedPitches && elt->pitch()==fLastNote->pitch()))
			fPitchVector->push_back(*(elt->pitch()));
		
		fLastNote = elt;
	}
	else if (elt->getType()==IMUSANT_NoteType::rest)
	{	//currently segmenting for all rests
		//IMUSANT_interval empty;
		//fIntervalVector->add(empty);
		fLastNote = 0;
	}
	else//is non-pitched therefore interval can't be calculated
	{
		fLastNote = 0;
	}

	elt->lyrics().accept(*this);
}

#pragma mark IMUSANT_part handler
void IMUSANT_collection_visitor::visit ( S_IMUSANT_part& elt )
{
	//create part summary
	fLastNote = 0;
	fCurrentPartID++;
#ifdef NEW
    fCurrentIntervalVector = new_IMUSANT_interval_vector();
    fCurrentIntervalVector->setMaximum(0x7fffffff);
#endif
	//call sub-elements
	elt->measures().accept(*this);
#ifdef NEW
    //stow partwise derived data vectors, but only if they contain elements
    if (! fCurrentIntervalVector->getIntervals().empty())
    {
        fCurrentIntervalVector->add(IMUSANT_interval::MakeUniqueInterval()); //add unique terminator
        fPartwiseIntervalVectors.push_back(fCurrentIntervalVector);
    }
#endif
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
	fRhythmCollection = new_IMUSANT_rvec_collection();
#ifdef OLD
	fIntervalVector = new_IMUSANT_interval_vector();	
	fIntervalVector->setMaximum(0x7fffffff);
#endif
	fMelodicContour = new_IMUSANT_contour();
	fPitchVector = new_IMUSANT_pitch_vector();
	
	fMovementTitle = elt->getMovementTitle();
    fWorkTitle = elt->getWorkTitle();
	
	if ((IMUSANT_partlist*)elt->partlist())
		elt->partlist()->accept(*this);
	//add unique teminator elements in anticipation of processing.
#ifdef OLD
	fIntervalVector->add(IMUSANT_interval::MakeUniqueInterval());
#endif
	fPitchVector->push_back(IMUSANT_pitch::MakeUniquePitch());
	fMelodicContour->push_back(IMUSANT_contour_symbol::MakeUniqueSymbol());
}


} //namespace IMUSANT