//
//  I_Segment.h
//  catsmat
//
//  Created by Derrick Hill on 25/6/17.
//
//

#ifndef __I_Segment__
#define __I_Segment__

#include "SegmentContext.h"
#include "libIMUSANT.h"


namespace CATSMAT
{
    class I_Segment
    {
        
    public:
        I_Segment(S_SegmentContext context)
        {
            fSegmentContext = context;
        }
        
        virtual const vector<S_IMUSANT_note> notes() const = 0;
        virtual void addNote(S_IMUSANT_note note) = 0;
        virtual S_IMUSANT_note getFirstNote() const = 0;
        virtual S_IMUSANT_note getLastNote() const = 0;
        
    protected:
        S_SegmentContext fSegmentContext;
        
    };
}



#endif /* __I_Segment__ */
