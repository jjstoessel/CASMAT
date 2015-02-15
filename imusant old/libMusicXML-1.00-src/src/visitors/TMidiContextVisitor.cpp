/*
  Copyright © Grame 2003

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.
    
    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.
    
    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Grame Research Laboratory, 9, rue du Garet 69001 Lyon - France
    grame@grame.fr

*/

#include <math.h>

#ifndef max
static inline long max(long v1, long v2) {return (v1 < v2) ? v2 : v1;}
#endif

#include "LibMusicXML.h"
#include "TMidiContextVisitor.h"
#include "xml.h"

#define PRINT(x) { printf x; fflush(stdout); }
#define DBUG(x)  /* PRINT(x) */


SChannelTable newChannelTable() { TChannelTable *o = new TChannelTable(); assert(o!=0); return o; }

//________________________________________________________________________
TMidiContextVisitor::~TMidiContextVisitor() {}

//________________________________________________________________________
TMidiContextVisitor::TMidiContextVisitor(long tpq) 
{ 
    fCurDate = 0;
    fMaxDate = 0;
    fDynamics = 90;
    fTranspose = 0;
    fPart = 0;
    fCurMap = 0;
    fDivisions = 1; // to be checked
	fTPQ = tpq;
    fInChord = false;
}

//________________________________________________________________________
TMidiContextVisitor::TMidiContextVisitor() 
{ 
    fCurDate = 0;
    fMaxDate = 0;
    fDynamics = 90;
    fTranspose = 0;
    fPart = 0;
    fCurMap = 0;
    fDivisions = 1; // to be checked
    fTPQ = -1;
    fInChord = false;
}

//________________________________________________________________________
void TMidiContextVisitor::addDuration(long dur) 
{ 
    fCurDate += dur; 
    fMaxDate = max(fMaxDate,fCurDate);
}

//________________________________________________________________________
void TMidiContextVisitor::addScorePart(string ident) 
{ 
    DBUG(("addScorePart %s \n",ident.c_str()));
    // Make the ID, score-part association
    fCurMap = newChannelTable();
    fMidiInstrumentTable.insert(make_pair(ident, fCurMap));
    assert(fCurMap);
    fPart++;
}

//________________________________________________________________________
void TMidiContextVisitor::addInstrument(string ident, long chan) 
{ 
    assert(fCurMap);
    TChannelTable::iterator it = fCurMap->find(ident); 
    
    if (it != fCurMap->end()) {
        DBUG(("[ID : Midi channel] pair already done \n"));
    }else{
        DBUG(("Make [ID : Midi channel] pair %s %ld \n", ident.c_str(),chan));
        fCurMap->insert(make_pair(ident,TInstrument(chan,fPart)));
    }
}

//________________________________________________________________________
void TMidiContextVisitor::initTrack(string ident)
{
    fCurDate = 0;
    fMaxDate = 0;
    fTranspose = 0;
    fTempo = 120;
    fDynamics = 90;
    fDivisions = 1; 
    fInChord = false;
    
    DBUG(("SPWPart \n"));

    map<string, SChannelTable>::iterator it = fMidiInstrumentTable.find(ident);
    
    if (it != fMidiInstrumentTable.end()) {
        fCurMap = it->second; // keep the current part, (midi-channel , inst)
        DBUG(("SPWPart : instrument found %s %ld\n",ident.c_str(),fCurMap->size()));
    }else{
        fCurMap = 0;
        DBUG(("SPWPart error : instrument not found %s \n",ident.c_str()));
    }
}

//________________________________________________________________________
long TMidiContextVisitor::getChan(SNote& elt) 
{
    TInstrument inst(1,1);
    getInstrument(elt->getInstrumentID(),inst);
    return inst.getChan();
}

//________________________________________________________________________
long TMidiContextVisitor::getPart(SNote& elt) 
{
    TInstrument inst(1,1);
    getInstrument(elt->getInstrumentID(),inst);
    return inst.getPart();
}

//________________________________________________________________________
bool TMidiContextVisitor::getInstrument(string ident, TInstrument& instrument)
{
    if (ident == "") { // note without instrument

        if(fCurMap) {
        
            TChannelTable::iterator it = fCurMap->begin();  // only one channel
        
            if (it != fCurMap->end()) {
                instrument = it->second;
                return true;
            }else{
                DBUG(("GetCurInstrument error : instrument not found %s \n", ident.c_str()));
                return false;
            }
        }else{
            DBUG(("GetCurInstrument default channel \n"));
            return false;
        }
    
    }else{
    
        DBUG(("GetCurInstrument : note with instrument\n"));
        assert(fCurMap);
    
        TChannelTable::iterator it = fCurMap->find(ident); 
        
        if (it != fCurMap->end()) {
            instrument = it->second;
            return true;
        }else{
            DBUG(("GetCurInstrument error : instrument not found %s \n", ident.c_str()));
            return false;        
        }
    }
}
    
//________________________________________________________________________
bool TMidiContextVisitor::getInstrument(TInstrument& instrument)
{
    if (fCurMap) {
    
        TChannelTable::iterator it = fCurMap->begin();  // only one channel
    
        if (it != fCurMap->end()) {
            instrument = it->second;
            return true;
        }else{
            return false;
        }
    }else{
        DBUG(("GetCurInstrument default channel \n"));
        return false;
    }
}

//________________________________________________________________________
unsigned long TMidiContextVisitor::getFullDuration(SNote& elt) 
{
    return convert2Tick(elt->getFullDuration());
}

//________________________________________________________________________
long TMidiContextVisitor::getPitch(SNote& elt)
{
    return elt->pitch()->MIDIPitch() + getTranspose();
}

//________________________________________________________________________
void TMidiContextVisitor::visiteEnter ( SAttributes& elt )
{
    if (elt->getDivision() != TAttributes::undefined){
		long divisions = elt->getDivision();
        setDivisions(divisions);
		if (fTPQ == -1) fTPQ = divisions; // If no tpq is specified use the value read in the XML file
        DBUG(("fDivisions %f\n", divisions));
    }
}

//________________________________________________________________________
void TMidiContextVisitor::visiteEnter( SBackup& elt )
{
    addDuration(-elt->getDuration());
    DBUG(("SBackup :dur %ld :date %ld\n",elt->getDuration(),fCurDate));
}


//________________________________________________________________________
void TMidiContextVisitor::visiteEnter ( SChord& elt )
{
    fInChord = true;
}

//________________________________________________________________________
void TMidiContextVisitor::visiteLeave ( SChord& elt )
{
    fInChord = false;
    addDuration(elt->getDuration());
    DBUG(("SChord %ld\n",elt->getDuration()));
}

//________________________________________________________________________
void TMidiContextVisitor::visiteEnter ( SForward& elt )
{
    addDuration(elt->getDuration());
    DBUG(("SForward :dur %ld :voice %ld :staff %ld :date %ld\n",elt->getDuration(),elt->getVoice(), elt->getStaff(), fCurDate));
}

//________________________________________________________________________
void TMidiContextVisitor::visiteEnter ( SMidiInstrument& elt )
{
    addInstrument(elt->getID(),elt->getChannel());
}

//________________________________________________________________________
void TMidiContextVisitor::visiteLeave ( SNote& elt )
{
    // Time advance only for normal notes, graces notes are not handled
    if (elt->isNormal() && !fInChord) addDuration(elt->getDuration());
    DBUG(("SNote :dur %ld :date %ld\n",elt->getDuration(), fCurDate));
}

//________________________________________________________________________
void TMidiContextVisitor::visiteEnter ( SPWMeasure& elt )
{
    fCurDate = fMaxDate; // Set cur date to the maximum voice duration inside the previous measure
    fMaxDate = 0;
    DBUG(("SPWMeasure :date %ld\n",fCurDate));
}

//________________________________________________________________________
void TMidiContextVisitor::visiteEnter ( SPWPart& elt )
{
    initTrack(elt->getID());
}

//________________________________________________________________________
void TMidiContextVisitor::visiteEnter ( SScoreHeader& elt ) {}

//________________________________________________________________________
void TMidiContextVisitor::visiteEnter ( SScorePart& elt ) 
{
    // Make the ID, score-part association
    addScorePart(elt->getID());   
}

//________________________________________________________________________
void TMidiContextVisitor::visiteEnter ( SSound& elt )
{
    if(elt->getDynamics() != TSound::undefined) 
       setDynamics(elt->getDynamics()); 
    if(elt->getTempo() != TSound::undefined)
       setTempo(elt->getTempo());
}

//________________________________________________________________________
void TMidiContextVisitor::visiteEnter ( STranspose& elt )
{
    setTranspose(elt->getChromatic() + elt->getOctaveChge() * 12);     
    DBUG(("fTranspose %ld\n", fTranspose));
}
