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
    
    S_IMUSANT_note new_IMUSANT_note()
    {
        IMUSANT_note * o = new IMUSANT_note(); assert(o!=0); return o;
    }
    
    ostream& operator<< (ostream& os, const S_IMUSANT_note& elt )
    {
        elt->print(os);
        return os;
    }
    
    IMUSANT_note::
    IMUSANT_note() :
    fTieNext(NULL),
    fTiePrevious(NULL),
    fStyle(IMUSANT_NoteStyle::normal),
    fType(IMUSANT_NoteType::pitch),
    fVoice(-1)
    {
        initialize();
    }
    
    IMUSANT_note::
    IMUSANT_note(S_IMUSANT_pitch& pitch, S_IMUSANT_duration& duration )
    :
    fTieNext(NULL),
    fTiePrevious(NULL),
    fStyle(IMUSANT_NoteStyle::normal),
    fType(IMUSANT_NoteType::pitch),
    fVoice(-1)
    {
        initialize();
        
        *fPitch = *pitch;
        *fDuration = *duration;
    }
    
    IMUSANT_note::
    IMUSANT_note(const IMUSANT_note& note)
    {
        initialize();
        
        *this = note;
    }
    
    IMUSANT_note::~IMUSANT_note(){}
    
    void
    IMUSANT_note::
    initialize()
    {
        fPitch = new_IMUSANT_pitch();
        fDuration = new_IMUSANT_duration();
        fAccidental = new_IMUSANT_accidental();
    }
    
    IMUSANT_note&
    IMUSANT_note::
    operator= (const IMUSANT_note& rhs)
    {
        *fPitch = *(rhs.pitch());
        *fDuration = *(rhs.duration());
        *fAccidental = *(rhs.accidental());
        
        fLyrics = rhs.lyrics();
        fMSLyrics = rhs.fMSLyrics;
        fStem = rhs.fStem;
        fStaff = rhs.fStaff;
        fMeasureNumber = rhs.fMeasureNumber;
        fNoteIndex = rhs.fNoteIndex;
        fHasFermata = rhs.fHasFermata;
        fTieNext = rhs.getNextTieNote();
        fTiePrevious = rhs.getPreviousTieNote();
        fStyle = rhs.getStyle();
        fType = rhs.getType();
        fVoice = rhs.getVoice();
        
        return *this;
    }
    
    void
    IMUSANT_note::
    print_short(ostream& os) const
    {
        os << "<NOTE measure_num=" << fMeasureNumber << " index=" << fNoteIndex << " ";
        
        if (fPitch != NULL)
        {
            fPitch->print(os);
        }
        
        os << "\\>"<< endl;
    }
    
    void
    IMUSANT_note::
    print (ostream& os) const
    {
        os << "<NOTE measure_num=" << fMeasureNumber << " index=" << fNoteIndex << " >" << endl;
        
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
        
        if (fVoice != -1)
        {
            os << " <VOICE>" << fVoice << "<VOICE\\>" << endl;
        }
        
        if (getType() == IMUSANT_NoteType::rest)
        {
            os << " <REST\\>" << endl;
        }
        
        if (getStyle() == IMUSANT_NoteStyle::grace)
        {
            os << " <GRACE\\>" << endl;
        }
        
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
    
    string
    IMUSANT_note::
    pretty_print() const
    {
        stringstream os;
        
        os << "{";
        
        os << fMeasureNumber << "." << fNoteIndex << ", ";
        
        
        if (fPitch != NULL)
        {
            os << fPitch->getMidiKeyNumber();
        }
        else
        {
            os << "-";
        }
        
        
        if (fDuration != NULL)
        {
            os << ", ";
            os << fDuration->asAbsoluteNumeric();
        }
        
        
        if (fType ==  IMUSANT_NoteType::rest)
        {
            os << ", ";
            os << "rest";
        };
        
        os << "}";
        
        return os.str();
    }
    
    ostream&
    IMUSANT_note::
    pretty_print(ostream& os) const
    {
        os << pretty_print();
        return os;
    }
    
    void
    IMUSANT_note::
    setPreviousTieNote (const S_IMUSANT_note& previous)
    {
        fTiePrevious = previous;
        
        if (previous->getNextTieNote()!=this)
        {
            previous->setNextTieNote(this);
        }
    }
    
    void
    IMUSANT_note::
    setNextTieNote (const S_IMUSANT_note& next)
    {
        fTieNext = next;
        if (next->getPreviousTieNote()!=this)
        {
            next->setPreviousTieNote(this);
        }
        
    }
    
    const IMUSANT_duration
    IMUSANT_note::
    durationWithTies() const
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
    
    const IMUSANT_duration
    IMUSANT_note::
    getPreviousTiedDurations() const
    {
        IMUSANT_duration total;
        
        total = *fDuration;
        
        if (isTiedPrevious())
        {
            total += getPreviousTieNote()->getPreviousTiedDurations();
        }
        
        return total;
    }
    
    const IMUSANT_duration
    IMUSANT_note::
    getNextTiedDurations() const
    {
        IMUSANT_duration total;
        
        total = *fDuration;
        
        if (isTiedNext())
        {
            total += getNextTieNote()->getNextTiedDurations();
        }
        
        return total;
        
    }
    
    
    void
    IMUSANT_note::
    accept(IMUSANT_visitor& visitor)
    {
        S_IMUSANT_note ptr(this);
        visitor.visit(ptr);
    }
    
    
    bool
    IMUSANT_note::
    operator==(const IMUSANT_note& note) const
    {
        return equals(note);
    }
    
    bool
    IMUSANT_note::
    equals(const IMUSANT_note& n1) const
    {
        const IMUSANT_note& n2 = *this;
        
        bool type_match = n1.fType == n2.fType;
        bool pitch_match = *(n1.pitch()) == *(n2.pitch());
        bool duration_match = *(n1.duration()) == *(n2.duration()) ;
        bool duration_with_ties_match = n1.durationWithTies() == n2.durationWithTies();
        
        return ( type_match &&
                pitch_match &&
                (duration_match || duration_with_ties_match));
    }
    
    
    bool
    IMUSANT_note::
    operator< (const IMUSANT_note& note) const
    {
        signed short i = (this->pitch()->name() + this->pitch()->getInflection()) + ((IMUSANT_pitch::last+1)*this->pitch()->octave());
        signed short j = (note.pitch()->name() + note.pitch()->getInflection()) + ((IMUSANT_pitch::last+1)*note.pitch()->octave());
        return (i - j) < 0;
    }
    
    
    bool
    IMUSANT_note::
    higher(const IMUSANT_note& note1, const IMUSANT_note& note2)
    {
        return note1.pitch() > note2.pitch();
    }
    
} //namespace IMUSANT



