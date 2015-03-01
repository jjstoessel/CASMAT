//
//  CATSMAT_cp_matrix.cpp
//  imusant
//
//  Created by Jason Stoessel on 29/01/2015.
//
//

#include "CATSMAT_cp_matrix.h"

namespace CATSMAT
{

S_CATSMAT_cp_matrix new_CATSMAT_cp_matrix()
{ CATSMAT_cp_matrix* o = new CATSMAT_cp_matrix(); assert(o!=0); return o; }

ostream& operator<< (ostream& os, const S_CATSMAT_cp_matrix& elt )
{
    elt->print(os);
    
    return os;
}

CATSMAT_cp_matrix::CATSMAT_cp_matrix()
    : fCurrentPart(-1)
{
    
}

CATSMAT_cp_matrix::~CATSMAT_cp_matrix()
{
    
}
    
bool CATSMAT_cp_matrix::addpart()
{
    //if a part already exists, create an empty part/row for each "chord" vector<IMUSANT_note>
    //In the case of the first part, the matrix grows by pushing a one-dimensional vector<IMUSANT_note>
    //onto the stack. Zero-based array style reference, ie. 0 = first part.
    fCurrentPart++;
    fCurrentChord = fCPMatrix.begin();
    
    return true;
}

bool	CATSMAT_cp_matrix::add(const IMUSANT_note& note)
{
    if (fCurrentPart==0) // there are no parts added yet
    {
        S_IMUSANT_chord chord = new_IMUSANT_chord();
        S_IMUSANT_note copy_note = new_IMUSANT_note();
        *copy_note = note;
        
        chord->add(copy_note);
        fCPMatrix.push_back(chord);
        fCurrentChord = --fCPMatrix.end();
        
    }
    else if (fCurrentPart>0)//there is one or more parts already added
    {
        insert(note);
    }
    
    return true;
}

bool    CATSMAT_cp_matrix::insert(const IMUSANT_note& note)
{
    bool inserted = false;
    
    assert(fCurrentChord!= fCPMatrix.end());

    //call to distribute note and return remainder; if note duration less than current chord duration
    //note is returned as remainder to spilt chord into two parts.
    IMUSANT_note remainder = distribute(note);
    if (remainder.duration()->fDuration != IMUSANT_duration::unmeasured)
        split(remainder);
    
    return inserted;
}

//split a note into smaller durations
void   CATSMAT_cp_matrix::split(const IMUSANT_note& note)
{
    //create the new chord, ready for filling in for loop
    S_IMUSANT_chord insert_chord = new_IMUSANT_chord();
    
    //resize notes in other parts in current chord; begin filling new chord, but don't fill the note
    //for the current voice since it will only be known in the next call of add(note&)
    for (unsigned long i = 0; i<fCurrentPart; i++)
    {
        //create a new note like the one that already exists, change duration
        //to remainder, insert into the new chord
        //To do: ties.
        
        S_IMUSANT_note      insert_note = new_IMUSANT_note();
        S_IMUSANT_duration  insert_duration = insert_note->duration(); //dereference
        
        *insert_note = *(*fCurrentChord)->getNotes()[i];
        insert_note->setDuration(note.duration());
        insert_chord->add(insert_note);
        
        //change duration of current chord
        S_IMUSANT_duration current_dur = (*fCurrentChord)->getNotes()[i]->duration();
        *current_dur -= *note.duration();
    }
    
    //finally add new note (clone note&) to chord to be pre-inserted
    S_IMUSANT_note new_insert_note = new_IMUSANT_note();
    *new_insert_note = note;
    insert_chord->add(new_insert_note);
    
    //insert new chord before current chord
    fCurrentChord = fCPMatrix.insert(fCurrentChord, insert_chord);
    
    fCurrentChord++;
    
}

//recursive function to distribute a note over the following durations
//returns remainder, which is also the split note if duration is shorter
//than the current chord duration
//To do: capture whole note rests!
IMUSANT_note CATSMAT_cp_matrix::distribute(const IMUSANT_note& note)
{
    IMUSANT_note remainder = note;
    
    //assumes that the duration of all notes in each existing chord are the same due to prior operation.
    if ( fCurrentChord!=fCPMatrix.end() && *note.duration() >= *(*fCurrentChord)->getNotes()[fCurrentPart-1]->duration())
    {
        /*if ((*fCurrentChord)->getNotes()[fCurrentPart-1]->getMeasureNum() != note.getMeasureNum()) {
            cerr << "Mismatched measure insert" << endl;
        }*/
        //create and insert the note with a new duration
        //TO DO - add ties
        S_IMUSANT_note part_note = new_IMUSANT_note();
        *part_note = note;
        part_note->setDuration((*fCurrentChord)->getNotes()[fCurrentPart-1]->duration());
        
        (*fCurrentChord)->add(part_note);
        //find the remainder of the duration left after the previous chord
        //call recusively
        S_IMUSANT_duration dur = remainder.duration();
        *dur -= *part_note->duration();
        
        fCurrentChord++;
        
        if (dur->fDuration!=IMUSANT_duration::unmeasured && fCurrentChord!=fCPMatrix.end()) {
                distribute(remainder);
        }
        
    }
    
    return remainder;
}
    
void	CATSMAT_cp_matrix::pop_front()
{
    
}


void CATSMAT_cp_matrix::print(ostream& os)
{
    for (auto vector<S_IMUSANT_chord>::iterator i = fCPMatrix.begin(); i!=fCPMatrix.end(); i++) {
        (*i)->print(os);
    }
}
    
}//namespace CATSMAT

