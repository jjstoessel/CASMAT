//
//  CATSMAT_cp_matrix.cpp
//  imusant
//
//  Created by Jason Stoessel on 29/01/2015.
//
//  Purpose: To build an in memory representation of a contrapuntal structure
//
//  History:
//  – First fully functional on 10/3/2015
//
//
#include "CATSMAT_cp_matrix.hpp"
#include "CATSMAT_exception.h"

namespace CATSMAT
{
    
    S_CATSMAT_cp_matrix new_CATSMAT_cp_matrix()
    {
        CATSMAT_cp_matrix* o = new CATSMAT_cp_matrix();
        //assert(o!=0);
        if (o==0) throw catsmat_runtime_error("Unable to allocate Contrapuntal Matrix");
        return o;
    }

    /*!
     \brief CATSMAT_cp_matrix stream out operator
     
    */
    ostream& operator<< (ostream& os, const S_CATSMAT_cp_matrix& elt )
    {
        elt->print(os);
        
        return os;
    }

    /*!
     \brief CATSMAT_cp_matrix default ctor
     
     */
    CATSMAT_cp_matrix::CATSMAT_cp_matrix()
        : fCurrentPart(-1), fCurrentMeasureNumber(NULL)
    {
        
    }

    CATSMAT_cp_matrix::~CATSMAT_cp_matrix()
    {
        
    }

    /*!
     \brief CATSMAT_cp_matrix::addpart 
        
        Increments fCurrentPart and returned to the first chord of the CP matrix
        called by:
            (visitor)::visit ( S_IMUSANT_part& elt )
     
     */
    void CATSMAT_cp_matrix::addpart()
    {
        //if a part already exists, create an empty part/row for each "chord" vector<IMUSANT_note>
        //In the case of the first part, the matrix grows by pushing a one-dimensional vector<IMUSANT_note>
        //onto the stack. Zero based
        fCurrentPart++;
        
        //increase VectorInterval colection according to the formula of unique pairs n(n-1)/2
        while (fVIntervalVector.size() < ( (fCurrentPart+1)*fCurrentPart/2 ) )
        {
            S_IMUSANT_interval_vector newIV = new_IMUSANT_interval_vector();
            newIV->setMaximum(1024);
            
            fVIntervalVector.push_back(newIV);
        }
        
        fCurrentChord = fCPMatrix.begin();
    }

    /*!
    \brief CATSMAT_cp_matrix::add
     
        Adds a note to the current part
     
     */
    void	CATSMAT_cp_matrix::add(const IMUSANT_note& note)
    {
        if (note.getStyle()==IMUSANT_NoteStyle::hidden) throw catsmat_runtime_error("hidden note encountered"); // ignore hidden notes
        
        if (fCurrentPart==0) // there are no parts added yet
        {
            S_CATSMAT_chord chord = new_CATSMAT_chord();
            S_IMUSANT_note copy_note = new_IMUSANT_note();
            *copy_note = note;
            
            (*chord)[fCurrentPart]=copy_note;
            fCPMatrix.push_back(chord);
            fCurrentChord = --fCPMatrix.end();
            
        }
        else if (fCurrentPart>0)//there is one or more parts already added
        {
            insert(note);
        }
    }

    /*!
     \brief CATSMAT_cp_matrix::insert
        
        Inserts a note into the next chord (and following ones)
     
     */
    void    CATSMAT_cp_matrix::insert(const IMUSANT_note& note)
    {
        if (fCurrentChord==fCPMatrix.end()) throw catsmat_runtime_error("Unexpected end of Contrapuntal Matrix.");

        //call to distribute note and return remainder; if note duration less than current chord duration
        //note is returned as remainder to spilt chord into two parts.
        IMUSANT_note remainder = distribute(note);
        if (remainder.duration()->fDuration != IMUSANT_duration::unmeasured)
            split(remainder);
    }

    /*!
        \brief CATSMAT_cp_matrix::distribute

        A recursive function to distribute a longer note over smaller durations in existing parts/chords;
        returns remainder as IMUSANT_note, which is also the "split note" if the duration is shorter
        than the current chord duration
    */
    IMUSANT_note CATSMAT_cp_matrix::distribute(const IMUSANT_note& note, const S_IMUSANT_note previous_note)
    {
        IMUSANT_note remainder = note;
        
        S_IMUSANT_duration current_chord_dur = (*(*fCurrentChord)).begin()->second->duration();
        
        //assumes that the duration of all notes in each existing chord are the same due to prior operation.
        if ( fCurrentChord!=fCPMatrix.end() && *note.duration() >= *current_chord_dur )
        {
            /*if ((*fCurrentChord)->getNotes()[fCurrentPart-1]->getMeasureNum() != note.getMeasureNum()) {
             cerr << "Mismatched measure insert" << endl;
             }*/
            //create and insert the note with a new duration
            //make sure new duration object is added.
            //TO DO - add ties

            S_IMUSANT_note      part_note = new_IMUSANT_note();
            S_IMUSANT_duration  part_duration = new_IMUSANT_duration();
            
            *part_duration = *current_chord_dur;
            *part_note = note;
            part_note->setDuration(*part_duration);
            if (previous_note!=NULL) part_note->setPreviousTieNote(previous_note);
            
            (*(*fCurrentChord))[fCurrentPart] = part_note;
            //find the remainder of the duration left after the previous chord
            //call recusively
            S_IMUSANT_duration dur = remainder.duration();
            *dur -= *part_duration;
            remainder.setDuration(*dur);
            
            fCurrentChord++;
            
            if (dur->fDuration!=IMUSANT_duration::unmeasured && fCurrentChord!=fCPMatrix.end())
            {
                remainder = distribute(remainder, part_note);
            }
            
        }
        
        return remainder;
    }
    /*!
        \brief CATSMAT_cp_matrix::split
     
        Split split an existing chord with a shorter inserted or remainder note.
     
    */
    void   CATSMAT_cp_matrix::split(const IMUSANT_note& note)
    {
        //create the new chord, ready for filling in for loop
        S_CATSMAT_chord insert_chord = new_CATSMAT_chord();
        S_IMUSANT_note  new_note = new_IMUSANT_note();
        
        //resize notes in previous part in current chord; begin filling new chord, but don't fill the note
        //for the current voice since it will be known only in the next call of add(note&)
        for (int i = 0; i<fCurrentPart; i++)
        {
            //first creating new chord to be inserted before the current chord using the values of note
            S_IMUSANT_note      insert_note = new_IMUSANT_note();
            S_IMUSANT_duration  insert_duration = new_IMUSANT_duration();
        
            *insert_note = *(*fCurrentChord)->at(i);
            *insert_duration = *note.duration();
            insert_note->setDuration(*insert_duration);
            insert_note->setNextTieNote((*fCurrentChord)->at(i));
            (*insert_chord)[i] = insert_note;
            
            //resize the note in the other part
            if (*(*fCurrentChord)->at(i)->duration() != *(*fCurrentChord)->at(i)->duration() - *note.duration())
            {
                *(*fCurrentChord)->at(i)->duration() -= *note.duration();
            }
        }
        
        if (note.duration()->fDuration==IMUSANT_duration::unmeasured) throw catsmat_runtime_error("Unmeasured duration encountered. Check your data.");
        //finally add new note (clone note&) to new chord to be pre-inserted
        *new_note = note;
        (*insert_chord)[fCurrentPart] = new_note;
        //insert new chord *before* current chord
        fCPMatrix.insert(fCurrentChord, insert_chord);
    }
        
    /*!
     \brief CATSMAT_cp_matrix::print
     
        Print function for viewing contents of CP matrix in XML
     
     */
    void CATSMAT_cp_matrix::print(ostream& os)
    {
        for (auto i = fCPMatrix.begin(); i!=fCPMatrix.end(); i++) {
            (*i)->print(os);
        }
    }
    
}//namespace CATSMAT

