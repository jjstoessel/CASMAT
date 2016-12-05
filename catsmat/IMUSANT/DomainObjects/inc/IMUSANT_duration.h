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
        
        friend IMUSANT_SMARTP<IMUSANT_duration> new_IMUSANT_duration();
        
        IMUSANT_duration() :
            fDuration(IMUSANT_duration::unmeasured),
            fDots(0),
            fTimeModification(TRational(1,1)),
            fNormalDuration(IMUSANT_duration::unmeasured),
            fNormalDots(0)
        {
            // empty constructor
        }
        
        IMUSANT_duration(const IMUSANT_duration& duration)
        {
            *this = duration;
        }
        
        virtual ~IMUSANT_duration() {}
        
        const IMUSANT_duration& operator= (const IMUSANT_duration& dur);
        
        bool                operator!= (const IMUSANT_duration& dur) const;
        bool                operator== (const IMUSANT_duration& dur) const;
        IMUSANT_duration	operator+(const IMUSANT_duration& right);
        IMUSANT_duration&	operator+=(const IMUSANT_duration& rhs);
        IMUSANT_duration    operator-(const IMUSANT_duration& right);
        void				operator-=(const IMUSANT_duration& rhs);
        bool                operator >(const IMUSANT_duration &dur) const;
        bool                operator >=(const IMUSANT_duration &dur) const 	{return !(*this < dur);}
        bool                operator <(const IMUSANT_duration &dur) const;
        bool                operator <=(const IMUSANT_duration &dur) const 	{return !(*this > dur);}
        
        friend ostream& operator<< (ostream& os, const IMUSANT_duration& elt );
        void	print (ostream& os) const;
        
        
        // Simple version for no time modification.
        void set(TRational dur, long dots = 0)
        {
            fDuration = dur;
            fDots = dots;
            fTimeModification = TRational(1,1);
            fNormalDuration = dur;
            fNormalDots = 0;
            
            fDots += NormaliseDuration(fDuration);
        }
        
        // Use this when there is a time modification.
        // See the MusicXML v3 documentation for the time-modification element to understand the last three parameters.
        // If there is no need to use normal_dur then set it to IMUSANT_duration::unmeasured.
        // D-01024.  The normal-dur and normal-dots parameters are ignored.  You can set them to whatever you like and
        // the class will still behave correctly.
        void set( TRational dur, long dots, TRational timemod, TRational normal_dur, long normal_dots)
        {
            fDuration=dur;
            fDots=dots;
            fTimeModification=timemod;
            fNormalDuration = normal_dur;
            fNormalDots = normal_dots;
            
            fDots += NormaliseDuration(fDuration);
        }

        
        IMUSANT_duration	getSimplifiedDuration() const;
        float               asAbsoluteNumeric() const;
        
        // If dur is a ratio that represents a dotted note, then this function reduces dur to the fraction
        // without the dots and retrurns the number of dots required.
        //
        // Examples:
        // * 3/4 represents a dotted crotchet (1/2 + 1/4), and so this function changes 3/4 to 1/2 and returns 1.
        // * 6/4 represents a dotted breive (1/1 + 1/2), and so this function changes 6/4 to 1/1 and returns 1.
        //
        static long	NormaliseDuration(TRational& dur);
        
        
        // Converters
        static const string	xmlv1(TRational d);
        static TRational	xmlv1(const string str);
        static TRational	xmlv3(const string str);
        
        TRational           fDuration;
        long                fDots;
        TRational           fTimeModification;
        TRational           fNormalDuration;    //the duration subject to fTimeModification
        long                fNormalDots;
        
        
        static TRational unmeasured;
        static TRational maxima;                // 8  - asAbsoluteNumeric = 8192
        static TRational longa;                 // 4 -  - asAbsoluteNumeric =  4096
        static TRational breve;                 // 2  - asAbsoluteNumeric = 2048
        static TRational semibreve;             // 1 =  - asAbsoluteNumeric = 1024
        static TRational minim;                 // 1/2  - asAbsoluteNumeric = 512
        static TRational crochet;               // 1/4 -  - asAbsoluteNumeric = 256
        static TRational quaver;                // 8th  - asAbsoluteNumeric = 128
        static TRational semiquaver;            // 16th  - asAbsoluteNumeric = 64
        static TRational demisemiquaver;        // 32nd  - asAbsoluteNumeric = 32
        static TRational hemidemisemiquaver;    // 64th  - asAbsoluteNumeric = 16
        static TRational hundredandtwentyeighth;// 128th  - asAbsoluteNumeric = 8
        static TRational twofiftysixth;         // 256th - asAbsoluteNumeric = 4
        static TRational fivetwelfth;           // 512th  - asAbsoluteNumeric =  2
        static TRational oneohtwofourth;        // 1024th - asAbsoluteNumeric = 1
        
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
    
    typedef IMUSANT_SMARTP<IMUSANT_duration> S_IMUSANT_duration;
    
    IMUSANT_SMARTP<IMUSANT_duration> new_IMUSANT_duration();
    
}
#endif //namespace IMUSANT
