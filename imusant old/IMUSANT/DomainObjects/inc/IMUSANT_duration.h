/*
 *  IMUSANT_duration.h
 *  imusant
 *
 *  Created by Jason Stoessel on 30/08/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 *  Changes:
 *  24 Mar 2016 Added handlers for time modification and normal duration and normal dots as "variables" of time modification
 */

#ifndef __IMUSANT_DURATION__
#define __IMUSANT_DURATION__

#include <string>
#include <iostream>

#include "smartpointer.h"
#include "TRational.h"
#include "bimap.h"

namespace IMUSANT
{
    class IMUSANT_duration;
    
    VEXP ostream& operator<< (ostream& os, const IMUSANT_duration& elt );
    
    class VEXP IMUSANT_duration : public smartable
    {
    public:
        
        friend SMARTP<IMUSANT_duration> new_IMUSANT_duration();
        
        IMUSANT_duration(): fDuration(IMUSANT_duration::unmeasured),
        fDots(0),
        fTimeModification("1/1"),
        fNormalDuration(0), //zero time modification default
        fNormalDots(0)
        {
            // empty constructor
        }
        
        IMUSANT_duration(const IMUSANT_duration& duration)
        {
            *this = duration;
        }
        
        virtual ~IMUSANT_duration() {}
        
        const IMUSANT_duration& operator= (const IMUSANT_duration& dur)
        {
            this->set(dur.fDuration, dur.fDots,dur.fTimeModification, dur.fNormalDuration, dur.fNormalDots);
            return *this;
        }
        
        bool                operator!= (const IMUSANT_duration& dur) const;
        bool                operator== (const IMUSANT_duration& dur) const;
        IMUSANT_duration	operator+(const IMUSANT_duration& right);
        void				operator+=(const IMUSANT_duration& rhs);
        IMUSANT_duration    operator-(const IMUSANT_duration& right);
        void				operator-=(const IMUSANT_duration& rhs);
        bool                operator >(const IMUSANT_duration &dur) const;
        bool                operator >=(const IMUSANT_duration &dur) const 	{return !(*this < dur);}
        bool                operator <(const IMUSANT_duration &dur) const;
        bool                operator <=(const IMUSANT_duration &dur) const 	{return !(*this > dur);}
        
        friend ostream& operator<< (ostream& os, const IMUSANT_duration& elt );
        void	print (ostream& os) const;
        
        void set( TRational dur, long dots, TRational timemod=1, TRational normal_dur=0, long normal_dots=0)
        {
            fDuration=dur;
            fDots=dots,
            fTimeModification=timemod;
            fNormalDuration = normal_dur;
            fNormalDots = normal_dots;
        }
        
        IMUSANT_duration	getSimplifiedDuration() const;
        float                asAbsoluteNumeric() const;
        
        //checks that TRational type is actually dotted note, return dots and changes dur
        static long	NormaliseDuration(TRational& dur);
        
        
        // Converters
        static const string	xmlv1(TRational d);
        static TRational	xmlv1(const string str);
        static TRational	xmlv3(const string str);
        
        TRational		fDuration;
        long            fDots;
        TRational       fTimeModification;
        TRational       fNormalDuration;    //the duration subject to fTimeModification
        long            fNormalDots;
        
        
        static TRational unmeasured;
        static TRational maxima;
        static TRational longa;
        static TRational breve;
        static TRational semibreve;
        static TRational minim;
        static TRational crochet;
        static TRational quaver;
        static TRational semiquaver; //16th
        static TRational demisemiquaver; //32nd
        static TRational hemidemisemiquaver; //64th
        static TRational hundredandtwentyeighth;  //128th
        static TRational twofiftysixth; // 256th
        static TRational fivetwelfth; // 512th
        static TRational oneohtwofourth; // 1024th
        
        // We multiply the fractional representations of the duration by this value to normalise the values
        // to use a base of 1 for the smallest possible note value.  The smallest note we support is a 1024th.
        const int SMALLEST_POSSIBLE_NOTE_VALUE_MULTIPLIER = 1024;
        
    protected:

        static bimap<string, TRational>	fDuration2Stringv1;
        static bimap<string, TRational>	fDuration2Stringv3;
        
        static TRational				fDurationTblv1[];       // values for MusicXML Version 1
        static TRational				fDurationTblv3[];       // values for MusicXML Version 3
        static string					fDurationStringsv1[];   // values for MusicXML Version 1
        static string					fDurationStringsv3[];   // values for MusicXML Version 3
    };
    
    typedef SMARTP<IMUSANT_duration> S_IMUSANT_duration;
    
    SMARTP<IMUSANT_duration> new_IMUSANT_duration();
    
}
#endif //namespace IMUSANT