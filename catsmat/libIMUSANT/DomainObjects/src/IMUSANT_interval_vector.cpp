/*
 *  IMUSANT_interval_vector.cpp
 *  imusant
 *
 *  Created by Jason Stoessel on 24/06/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "IMUSANT_interval_vector.h"
#include "IMUSANT_note.h"

namespace IMUSANT
{
    
    S_IMUSANT_interval_vector new_IMUSANT_interval_vector()
    { IMUSANT_interval_vector* o = new IMUSANT_interval_vector(); assert(o!=0); return o; }
    
    ostream& operator<< (ostream& os, const S_IMUSANT_interval_vector& elt )
    {
        elt->print(os);
        
        return os;
    }
    
    IMUSANT_interval_vector::IMUSANT_interval_vector()
    : fMinimumIntervals(3), fMaximumIntervals(12)
    {
        fIntervals.reserve(fMinimumIntervals);
    }
    
    bool	IMUSANT_interval_vector::add(const IMUSANT_interval& interval)
    {
        if ( fIntervals.size()<fMaximumIntervals)
        {
            //copies interval
            fIntervals.push_back(interval);
            return true;
        }
        else //If reached here, then vector is maxed out.
        {
            fIntervals.emplace_back(interval);
        }
        
        return false;
    }
    
    bool
    IMUSANT_interval_vector::
    add(const IMUSANT_vector<S_IMUSANT_note>& note_vector)
    {
        IMUSANT_vector<S_IMUSANT_note>::const_iterator i = note_vector.begin();
        for ( IMUSANT_vector<S_IMUSANT_note>::const_iterator j = std::next(i);
              j!=note_vector.end(); i++, j++)
        {
            //skip to last tied note
            while (i!=note_vector.end() && (*i)->getNextTieNote()!=NULL)
            {
                i++;
                j++;
            }
            if (i==note_vector.end() || j==note_vector.end()) break;
            IMUSANT_pitch pitch_1 = *(*i)->pitch();
            IMUSANT_pitch pitch_2 = *(*j)->pitch();
            //IMUSANT_pitch undefined_pitch;
            
            if( (*j)->getPreviousTieNote()!=(*i) )
            {
                if ( (*i)->getType() == IMUSANT_NoteType::pitch && (*j)->getType() == IMUSANT_NoteType::pitch )
                {
                    IMUSANT_interval interval((*i)->pitch(),(*j)->pitch());
                    interval.setLocation(0, (*i)->getMeasureNum(), (*i)->getNoteIndex(), 0, (*j)->getMeasureNum(), (*j)->getNoteIndex());
                    fIntervals.push_back(interval);
                }
            }
        }
        
        return true;
    }
    
#ifdef ORIGINAL
    void IMUSANT_interval_vector::print(ostream& os)
    {
        for ( vector<IMUSANT_interval>::const_iterator interval = fIntervals.begin();
             interval != fIntervals.end();
             interval++ )
        {
            os << (*interval) << ", ";
        }
        os << endl;
    }
#endif
    
#ifdef NEW
    void IMUSANT_interval_vector::print(ostream& os)
    {
        for ( vector<IMUSANT_interval>::const_iterator interval = fIntervals.begin();
             interval != fIntervals.end();
             interval++ )
        {
            os << (*interval) <<  "(" << interval->getLocation() << ")" <<  ", ";
        }
        os << endl;
    }
#endif
    
}//namespace IMUSANT
