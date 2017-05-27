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

#include "IMUSANT_element.h"
#include "IMUSANT_key.h"
#include "IMUSANT_types.h"
#include "IMUSANT_note.h"
#include "IMUSANT_barline.h"

using namespace std;

namespace IMUSANT
{
    
    /*!
     \brief The part measure element
     */
    class VEXP IMUSANT_measure : public smartable, public IMUSANT_visitable
    {
    public:
        
        VEXP friend IMUSANT_SMARTP<IMUSANT_measure> new_IMUSANT_measure();
        
        
        IMUSANT_vector<S_IMUSANT_element>&	elements();
        void                                addElement (const S_IMUSANT_element& element);
        
        IMUSANT_vector<S_IMUSANT_note>&     notes();
        void                                addNote(const S_IMUSANT_note& note);

        IMUSANT_vector<S_IMUSANT_barline>&  barlines();
        void                                addBarline(const S_IMUSANT_barline& barline);

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
        IMUSANT_vector<S_IMUSANT_barline>   fBarlines;  //  convenience for getting at barlines regardless of other elements.
        long                                fMeasNum;
    };
    typedef IMUSANT_SMARTP<IMUSANT_measure>	S_IMUSANT_measure;
    
    VEXP    IMUSANT_SMARTP<IMUSANT_measure> new_IMUSANT_measure();
    
} //namespace IMUSANT
#endif
