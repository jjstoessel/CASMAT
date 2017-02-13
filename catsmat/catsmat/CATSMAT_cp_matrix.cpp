//
//  CATSMAT_cp_matrix.cpp
//  imusant
//
//  Created by Jason Stoessel on 29/01/2015.
//
//  Purpose: To build an in memory representation of a contrapuntal structure
//
//  History:
//  10 Mar 2015 - First fully functional on
//  10 Nov 2016 - CPMatrix now copies the inserted note
//
#include "CATSMAT_cp_matrix.hpp"
#include "CATSMAT_exception.h"

namespace CATSMAT
{

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
    : fCurrentPart(-1), fCurrentMeasureNumber(NULL), fLeftBarline(IMUSANT_barline::regular)
    {
        fMeasureDuration.set(TRational(1,1));
        fCumulativeMeasureDuration.set(TRational(0,1));
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
    void
    CATSMAT_cp_matrix::
    addpart()
    {
        //if a part already exists, create an empty part/row for each "chord" vector<IMUSANT_note>
        //In the case of the first part, the matrix grows by pushing a one-dimensional vector<IMUSANT_note>
        //onto the stack. Zero based
        fCurrentPart++;
        fCurrentChord = fCPMatrix.begin();
        fCumulativeMeasureDuration.set(TRational(0,1));
    }

    /*!
    \brief CATSMAT_cp_matrix::add
     
        Adds a note to the current part
     
     */
    void
    CATSMAT_cp_matrix::
    add(const IMUSANT_note& note)
    {
        //change added 10 Nov 2016 - note copied so it can be modified if out of dimensions of measure
        S_IMUSANT_note copy_note = new IMUSANT_note(note);
        
        if (note.getStyle()==IMUSANT_NoteStyle::hidden) throw catsmat_runtime_error("hidden note encountered at note: " + string(note.pretty_print())); // ignore hidden notes
        
        fCumulativeMeasureDuration += *copy_note->duration();
        
        if (fCumulativeMeasureDuration>fMeasureDuration) {
            if (fCurrentMeasureNumber==1)
                fMeasureDuration = fCumulativeMeasureDuration; // a quick hack for the time being for pieces without time signatures
            else //this truncates any notes at end of the measure which exceed the length of a measure; requires testing; will not work if we decide to work with cross-bar/hidden notes
            {
                fCumulativeMeasureDuration -= *note.duration();
                IMUSANT_duration new_dur = fMeasureDuration - fCumulativeMeasureDuration;
                copy_note->setDuration(new_dur);
                fCumulativeMeasureDuration += *copy_note->duration();
            }
            //else
            //    throw catsmat_runtime_error("Total duration of measure exceeded with note: " + string(note.pretty_print()));
        }
        
        if (fCurrentPart==0) // there are no parts added yet
        {
            S_CATSMAT_chord chord = new_CATSMAT_chord();
            (*chord)[fCurrentPart]=copy_note;
            fCPMatrix.push_back(chord);
            fCurrentChord = --fCPMatrix.end();
            
        }
        else if (fCurrentPart>0)//there is one or more parts already added
        {
            insert(*copy_note);
        }
    }

    /*!
     \brief CATSMAT_cp_matrix::insert
        
        Inserts a note into the next chord (and following ones)
     
     */
    void    CATSMAT_cp_matrix::
    insert(const IMUSANT_note& note)
    {
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
    IMUSANT_note
    CATSMAT_cp_matrix::
    distribute(const IMUSANT_note& note, const S_IMUSANT_note previous_note)
    {
        IMUSANT_note remainder = note;
        
        // REVISIT - if duration of final note in current part is greater than duration in other parts,
        // we run over the end of the map
        
        if (fCurrentChord==fCPMatrix.end())
        {
            throw catsmat_runtime_error("Unexpected end of Contrapuntal Matrix at note " + string(note.pretty_print()));
        }
        
        S_IMUSANT_duration current_chord_dur = (*(*fCurrentChord)).begin()->second->duration();
        
        //assumes that the duration of all notes in each existing chord are the same due to prior operation.
        if ( *note.duration() >= *current_chord_dur )
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
            
            if (dur->fDuration!=IMUSANT_duration::unmeasured)
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
    void
    CATSMAT_cp_matrix::
    split(const IMUSANT_note& note)
    {
        if (fCurrentChord==fCPMatrix.end()) throw catsmat_runtime_error("Unexpected end of Contrapuntal Matrix at note " + string(note.pretty_print()));
        
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
     \brief CATSMAT_cp_matrix::setMeasureNumber
     
     Record current measure number
     
     */
    void
    CATSMAT_cp_matrix::
    setMeasureNumber(long currentMeasure)
    {
        if (currentMeasure!=fCurrentMeasureNumber) {
            fCurrentMeasureNumber = currentMeasure;
            fCumulativeMeasureDuration.set(TRational(0,1));;
        }
    }
    
    /*!
     \brief CATSMAT_cp_matrix::set(const IMUSANT_time& time)
     
     Record current measure time and calculate fMeasureDuration
     
     */
    void
    CATSMAT_cp_matrix::
    set(const IMUSANT_time& time)
    {
        if (fCurrentTime!=time && time!=IMUSANT_time()) {
            fCurrentTime = time;
            vector<long> nums = fCurrentTime.getNumerator();
            vector<long> doms = fCurrentTime.getDenominator();
            vector<TRational> rats;
            if (doms.size()<2) {
                for (auto i = doms.begin(); i!=doms.end();i++) {
                    TRational rat1(1,*i);
                    for (auto j=nums.begin(); j!=nums.end(); j++) {
                        TRational rat2 = rat1*TRational(*j,1);
                        rats.push_back(rat2);
                    }
                }
            }
            else
            {
                if (doms.size()==nums.size()) {
                    for (auto i = nums.begin(), j = doms.begin(); i!=nums.end();i++, j++) {
                        TRational rat(*i,*j);
                        rats.push_back(rat);
                    }
                }
            }
            
            IMUSANT_duration dur;
            
            for (auto k = rats.begin(); k!=rats.end(); k++) {
                IMUSANT_duration add;
                add.set(*k, 0); //should rationalise.
                dur += add;
            }
        
            fMeasureDuration = dur;
        }
    }
    
    /*!
     \brief CATSMAT_cp_matrix::reindex
     
     Finishing function to reindex all notes in a matrix according to chord order
     
     */
    void
    CATSMAT_cp_matrix::
    reindex()
    {
        for (list< S_CATSMAT_chord >::iterator chord = fCPMatrix.begin(); chord!=fCPMatrix.end(); chord++)
        {
            map<int, S_IMUSANT_note> chord_notes = *(*chord);
            long measure_number = 0;
            long note_index = 0;
            
            for (auto chord_note = chord_notes.begin(); chord_note!=chord_notes.end(); chord_note++)
            {
                if (chord_note->second->getMeasureNum()>measure_number)
                {
                    measure_number = chord_note->second->getMeasureNum();
                    note_index = 1;
                }
            }
            
            for (auto chord_note = chord_notes.begin(); chord_note!=chord_notes.end(); chord_note++)
            {
                chord_note->second->setMeasureNum(measure_number);
            }
            note_index++;
        }
    }
    
    /*!
     \brief CATSMAT_cp_matrix::print
     
        Print function for viewing contents of CP matrix in XML
     
     */
    void CATSMAT_cp_matrix::
    print(ostream& os)
    {
        for (auto i = fCPMatrix.begin(); i!=fCPMatrix.end(); i++) {
            (*i)->print(os);
        }
    }
    
}//namespace CATSMAT

