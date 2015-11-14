/*
 *  IMUSANT_note.cpp
 *  imusant
 *
 *  Created by Jason Stoessel on 23/05/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "IMUSANT_note.h"

namespace IMUSANT
{

S_IMUSANT_note new_IMUSANT_note() { IMUSANT_note * o = new IMUSANT_note(); assert(o!=0); return o; }

ostream& operator<< (ostream& os, const S_IMUSANT_note& elt )
{
	elt->print(os);
    return os;
}

void IMUSANT_note::print (ostream& os) const
{
	os << "<NOTE index=" << fNoteIndex << " measure_num=" << fMeasureNumber << " >" << endl;
    
    os << " <PITCH>";
    if (fPitch != NULL)
    {
        fPitch->print(os);
    }
    else
    {
        os << "NULL";
        
    }
    os << "<\\PITCH>" << endl;
    
    
    os << " <DURATION>";
    if (fDuration != NULL)
    {
        fDuration->print(os);
    }
    else
    {
        os << "NULL";
    }
    os << "<\\DURATION>" << endl;
    
    os << " <ACCIDENTAL>";
    if (fAccidental != NULL)
    {
        fAccidental->print(os);
    }
    else
    {
        os << "NULL";
    }
    os << "<\\ACCIDENTAL>" << endl;
    
    os << "<PREVIOUS_TIE>";
    if (fTiePrevious != NULL)
    {
        os  << "measure["
            << to_string(fTiePrevious->getMeasureNum())
            << "] index["
            << to_string(fTiePrevious->getNoteIndex())
            << "]";
    }
    else
    {
        os << "NULL";
    }
    os << "<\\PREVIOUS_TIE>" << endl;

	//add other records
	os << "<\\NOTE>" << endl;
}

void IMUSANT_note::setPreviousTieNote (const S_IMUSANT_note& previous) 
{ 
	fTiePrevious = previous; 
	
	if (previous->getNextTieNote()!=this)
	{
		previous->setNextTieNote(this);
	}
}

void IMUSANT_note::setNextTieNote (const S_IMUSANT_note& next) 
{	
	fTieNext = next; 
	if (next->getPreviousTieNote()!=this)
	{
		next->setPreviousTieNote(this);
	}
	
}

const IMUSANT_duration		IMUSANT_note::durationWithTies() const
{
	IMUSANT_duration total;
	
	total = *fDuration;
	
	if (isTiedPrevious())
	{
		total += getPreviousTieNote()->getPreviousTiedDurations();
	}
		
	if (isTiedNext())
	{
		total += getNextTieNote()->getNextTiedDurations();
	}
	
	return total;
}

const IMUSANT_duration		IMUSANT_note::getPreviousTiedDurations() const
{
	IMUSANT_duration total;
	
	total = *fDuration;
	
	if (isTiedPrevious())
	{
		total += getPreviousTieNote()->getPreviousTiedDurations();
	}
		
	return total;
}

const IMUSANT_duration	IMUSANT_note::getNextTiedDurations() const
{
	IMUSANT_duration total;
	
	total = *fDuration;
		
	if (isTiedNext())
	{
		total += getNextTieNote()->getNextTiedDurations();
	}
	
	return total;

}

//______________________________________________________________________________
void IMUSANT_note::accept (IMUSANT_visitor& visitor)
{
	S_IMUSANT_note ptr(this);
	visitor.visit(ptr);
}
//basic comparison
bool IMUSANT_note::operator== (const IMUSANT_note& note) const
{
	return (fType==note.getType() && fPitch==note.pitch() && \
	(fDuration==note.duration() || durationWithTies()==note.durationWithTies()));
}
    
bool IMUSANT_note::operator< (const IMUSANT_note& note) const
{
    signed short i = (this->pitch()->name() + this->pitch()->alteration()) + ((IMUSANT_pitch::last+1)*this->pitch()->octave());
    signed short j = (note.pitch()->name() + note.pitch()->alteration()) + ((IMUSANT_pitch::last+1)*note.pitch()->octave());
    return (i - j) < 0;
}

//start binary operator for use with std::sort
bool  IMUSANT_note::higher(const IMUSANT_note& note1, const IMUSANT_note& note2)
{
    return note1.pitch() > note2.pitch();
}
    
} //namespace IMUSANT



