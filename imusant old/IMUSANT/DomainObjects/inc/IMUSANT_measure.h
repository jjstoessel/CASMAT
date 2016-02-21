/*
 *  IMUSANT_measure.h
 *  imusant - the Intertextual MUSic Analysis Tool
 *	Project Supervisor: Dr Rex Eakins
 *
 *  Created by Jason Stoessel on 23/05/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef __IMUSANT_measure__
#define __IMUSANT_measure__

#include "smartclasses.h"
#include "IMUSANT_element.h"
#include "IMUSANT_key.h"
#include "IMUSANT_types.h"
#include "IMUSANT_note.h"

using namespace std;

namespace IMUSANT
{
    
    /*!
     \brief The part measure element
     */
    class VEXP IMUSANT_measure : public smartable, public IMUSANT_visitable
    {
    public:
        
        VEXP friend SMARTP<IMUSANT_measure> new_IMUSANT_measure();
        
        
        IMUSANT_vector<S_IMUSANT_element>&	elements() { return fElements; }
        void                                addElement (const S_IMUSANT_element& element) { fElements.push_back(element); }
        S_IMUSANT_element&                  getElement (long elementIndex);
        short                               getElementCount() { return fElements.size(); } //needs to be a bit more sophisticated and consider ties
        
        IMUSANT_vector<S_IMUSANT_note>&     notes() { return fNotes; }
        void                                addNote(const S_IMUSANT_note& note) { addElement(note); fNotes.push_back(note); }
        short                               getNoteCount() { return fNotes.size(); } //needs to be a bit more sophisticated and consider ties
        
        long				getMeasureNum() { return fMeasNum; }
        IMUSANT_clef&		getClef() { return fClef; }
        IMUSANT_time&		getTime() { return fTime; }
        IMUSANT_key&		getKey()  { return fKey; }
        
        void				setClef (const IMUSANT_clef& clef) { fClef = clef; }
        void				setTime (const IMUSANT_time&	time) { fTime = time; }
        void				setKey	(const IMUSANT_key&	key) { fKey = key; }
        void				setMeasureNum (const long measureNum) { fMeasNum = measureNum; }  //implement error checking!!!
        
        void				print(ostream& os);
        
        void				accept(IMUSANT_visitor& visitor);
        
    protected:
        
        IMUSANT_measure () : fMeasNum(-1) {}
        virtual		~IMUSANT_measure (){}
    private:
        
        IMUSANT_clef	fClef;
        IMUSANT_time	fTime;
        IMUSANT_key		fKey;
        
        IMUSANT_vector<S_IMUSANT_element>   fElements;  //  may be notes, chords, comments or barline
        IMUSANT_vector<S_IMUSANT_note>      fNotes;     //  convenience for getting at notes regardless of other elements.
        long                                fMeasNum;
    };
    typedef SMARTP<IMUSANT_measure>	S_IMUSANT_measure;
    
    VEXP    SMARTP<IMUSANT_measure> new_IMUSANT_measure();
    
} //namespace IMUSANT
#endif