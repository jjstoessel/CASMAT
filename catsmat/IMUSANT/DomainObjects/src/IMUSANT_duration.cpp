/*
 *  IMUSANT_duration.cpp
 *  imusant
 *
 *  Created by Jason Stoessel on 30/08/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include <math.h>
#include "IMUSANT_duration.h"

namespace IMUSANT
{
    //static strings of durations
    TRational IMUSANT_duration::unmeasured(0,1);
    TRational IMUSANT_duration::maxima(8,1);
    TRational IMUSANT_duration::longa(4,1);
    TRational IMUSANT_duration::breve(2,1);
    TRational IMUSANT_duration::semibreve(1,1);
    TRational IMUSANT_duration::minim(1,2);
    TRational IMUSANT_duration::crochet(1,4);
    TRational IMUSANT_duration::quaver(1,8);
    TRational IMUSANT_duration::semiquaver(1,16); //16th
    TRational IMUSANT_duration::demisemiquaver(1,32); //32nd
    TRational IMUSANT_duration::hemidemisemiquaver(1,64); //64th
    TRational IMUSANT_duration::hundredandtwentyeighth(1,128); //128th
    TRational IMUSANT_duration::twofiftysixth(1,256); // 256th
    TRational IMUSANT_duration::fivetwelfth(1,512); // 512th
    TRational IMUSANT_duration::oneohtwofourth(1,1024); // 1024th
    
    
    //ctor functions
    S_IMUSANT_duration new_IMUSANT_duration()
    {
        IMUSANT_duration* o = new IMUSANT_duration(); assert (o!=0); return o;
    }
    
    TRational
    IMUSANT_duration::
    fDurationTblv1[] =
    {
        unmeasured, maxima, longa, breve, semibreve, minim, crochet, quaver,
        semiquaver, demisemiquaver, hemidemisemiquaver, hundredandtwentyeighth
    };
    
    TRational
    IMUSANT_duration::
    fDurationTblv3[] =
    {
        unmeasured, maxima, longa, breve, semibreve, minim, crochet, quaver,
        semiquaver, demisemiquaver, hemidemisemiquaver, hundredandtwentyeighth,
        twofiftysixth, fivetwelfth, oneohtwofourth
    };
    
    string
    IMUSANT_duration::
    fDurationStringsv1[]	=
    {
        "unmeasured", "maxima", "longa", "breve", "semibreve", "minim", "crochet", "quaver",
        "semiquaver", "demisemiquaver", "hemidemisemiquaver", "hundredandtwentyeighth"
    };
    
    string
    IMUSANT_duration::
    fDurationStringsv3[]	=
    {
        "unmeasured", "maxima", "long", "breve", "whole", "half", "quarter", "eighth",
        "16th","32nd", "64th","128th", "256th", "512th", "1024th"
    };
    
    bimap<string, TRational>
    IMUSANT_duration::
    fDuration2Stringv1(fDurationStringsv1, fDurationTblv1, 12);
    
    bimap<string, TRational>
    IMUSANT_duration::
    fDuration2Stringv3(fDurationStringsv3, fDurationTblv3, 15);
    
    const string
    IMUSANT_duration::
    xmlv1(TRational d)
    {
        return fDuration2Stringv1[d];
    }
    
    TRational	IMUSANT_duration::xmlv1(const string str) { return fDuration2Stringv1[str]; }
    TRational	IMUSANT_duration::xmlv3(const string str) { return fDuration2Stringv3[str]; }
    
    ostream& operator<< (ostream& os, const IMUSANT_duration& elt )
    {
        elt.print(os);
        return os;
    }
    
    void
    IMUSANT_duration::
    print (ostream& os) const
    {
        os  //<< "<RHYTHM_TYPE>" << fDuration.toString() << "<\\RHYTHM_TYPE>"
            << "<RHYTHM_TYPE>" << xmlv1(fDuration) << "<\\RHYTHM_TYPE>"
            << "<DOTS>" << to_string(fDots) << "<\\DOTS>"
            << "<TIME_MOD>" << fTimeModification.toString() << "<\\TIME_MOD>";
    }
    
    float
    IMUSANT_duration::
    asAbsoluteNumeric() const
    {
        //
        // This algorithm translates the static duration values defined above (oneohtwofourth etc) into
        // integral values starting with oneohtwofourth=1, and increasing each longer value by powers of two.
        //
        // When we account for tuples (triplets and the like), and dotted notes, this algorithm may return a
        // floating point number.
        //
        
        // Calculate the simple numeric value by normalising to a scale where smallest rhythmic value = 1.
        long numerator = fDuration.getNumerator() * SMALLEST_POSSIBLE_NOTE_VALUE_MULTIPLIER;
        float initial_numeric = numerator / fDuration.getDenominator();
        
        // Account for time modifications (tuples)
        float initial_numeric_with_time_mod = initial_numeric;
        if (fTimeModification != IMUSANT_duration::unmeasured)
        {
            initial_numeric_with_time_mod = (initial_numeric * fTimeModification.getDenominator()) / fTimeModification.getNumerator();
        }
        
        // Account for dots. For each additional dot we add a diminishing fraction of the
        // initial note duration value.
        // (A half of the initial value for the first dot, a quarter for the second, and so on)
        float incremental_val = initial_numeric_with_time_mod;
        int fraction_of_initial_value_to_add = 2;
        for (long index = fDots; index > 0 ; index--)
        {
            incremental_val = (incremental_val + (initial_numeric_with_time_mod / fraction_of_initial_value_to_add));
            fraction_of_initial_value_to_add = fraction_of_initial_value_to_add * 2;
        }
        
        // Account for normal-type
        // REVISIT
        
        return incremental_val;
    }
    
    const IMUSANT_duration&
    IMUSANT_duration::
    operator= (const IMUSANT_duration& dur)
    {
        this->set(dur.fDuration, dur.fDots,dur.fTimeModification, dur.fNormalDuration, dur.fNormalDots);
        NormaliseDuration(fDuration);
        return *this;
    }
    //--
    //  takes durations and reduces them to simplest form
    //  Dotted notes are a geometric series where the sum value of (S) of a duration with n dots is
    //      Sn = a (2 - pow(0.5, n))
    //
    long
    IMUSANT_duration::
    NormaliseDuration(TRational& dur)
    {
        dur.rationalise();
        
        long dots = 0;
        TRational sesquialtera(3,2);
        
        float r = 0.5; //ratio
        float gs = 0.0, intpart = 0.0;
        float base = dur; //cast to float
        
        while (dots<5 && modff(log2(base), &intpart)!=0) //modff returns faction part
        {
            gs = 2 - pow(r,dots+1);
            base = (float)dur/gs;
            dots++;
        }
        
        if (dots > 0 && dots<=4)
        {
            if (intpart<=0)
                dur = TRational(1,pow(2, fabs(intpart)));
            else
                dur = TRational(pow(2,intpart),1);
        }
        else
            dots = 0;
        
        return dots;
    }
    
    //--
    //Comparision operators
    //these also test for equality/inequality of simplified durations: see getSimplifiedDuration.
    bool
    IMUSANT_duration::
    operator!= (const IMUSANT_duration& dur) const
    {
        return (fDuration!=dur.fDuration) || (fDots!=dur.fDots) || (fTimeModification!=dur.fTimeModification)
        || (getSimplifiedDuration().fDuration!=dur.getSimplifiedDuration().fDuration);
    }
    
    bool
    IMUSANT_duration::
    operator== (const IMUSANT_duration& dur) const
    {
        return ((fDuration==dur.fDuration) && (fDots!=dur.fDots) && (fTimeModification==dur.fTimeModification))
        || (getSimplifiedDuration().fDuration==dur.getSimplifiedDuration().fDuration);
    }
    
    
    //Adds two durations, resulting in an absolute duration without dots or time modification
    //To do: check for simple relationships (dots and time modification) in resulting float
    IMUSANT_duration
    IMUSANT_duration::
    operator+(const IMUSANT_duration& right)
    {
        IMUSANT_duration out;
        
        //TRational r = TRational(IMUSANT_duration::xmlv1(getSimplifiedDuration().fDuration)) \
        //+ TRational(IMUSANT_duration::xmlv1(right.getSimplifiedDuration().fDuration));
        TRational r = getSimplifiedDuration().fDuration + right.getSimplifiedDuration().fDuration;
        out.fDots = NormaliseDuration(r);
        out.fDuration = r; //IMUSANT_duration::xmlv1(r.toString());
        out.fTimeModification=1;
        
        return out;
    }
    
    void	IMUSANT_duration::operator+=(const IMUSANT_duration& rhs)
    {
        *this = *this + rhs;
    }
    
    //--
    //Subtracts two durations, resulting in an absolute duration without dots or time modification
    //To do: check for simple relationships (dots and time modification) in resulting float
    //11 June 2015 timeModification handled more correctly, but not for case where two different timeMods in each note.
    IMUSANT_duration
    IMUSANT_duration::
    operator-(const IMUSANT_duration& right)
    {
        IMUSANT_duration out;
        TRational simple_left = getSimplifiedDuration().fDuration;
        TRational simple_right = right.getSimplifiedDuration().fDuration;
        
        TRational r = simple_left - simple_right;
        out.fDots = NormaliseDuration(r);
        
        
        if (fTimeModification != TRational(1))
        {
            out.fTimeModification = fTimeModification;
            out.fDuration = r*fTimeModification;
            out.fDuration.rationalise();
        }
        else if (right.fTimeModification != TRational(1))
        {
            out.fTimeModification = right.fTimeModification;
            out.fDuration = r*right.fTimeModification;
            out.fDuration.rationalise();
        }
        else
        {
            out.fTimeModification=1;
            out.fDuration = r;
        }
        
        return out;
    }
    
    void
    IMUSANT_duration::
    operator-=(const IMUSANT_duration& rhs)
    {
        *this = *this - rhs;
    }
    
    bool
    IMUSANT_duration::
    operator >(const IMUSANT_duration &dur) const
    {
        return (getSimplifiedDuration().fDuration > dur.getSimplifiedDuration().fDuration);
    }
    
    bool
    IMUSANT_duration::
    operator <(const IMUSANT_duration &dur) const
    {
        return (getSimplifiedDuration().fDuration < dur.getSimplifiedDuration().fDuration);
    }
    
    //--
    //Simplifies durations with dots and/or time proportions to simple float in fDuration w/o dots & time mods
    IMUSANT_duration
    IMUSANT_duration::
    getSimplifiedDuration() const
    {
        IMUSANT_duration out;
        
        TRational dotsmultiplier(1,1);
        TRational index(1,1);
        
        for (int i = 1; i <= fDots; i++)
        {
            index *= TRational(1,2);
            dotsmultiplier += index;
            
            if (i>7) {
                throw "iteration error in IMUSANT_duration::getSimplifiedDuration()";
                break;
            }
        }
        
        out.fDuration = (fDuration * dotsmultiplier)/fTimeModification;
        out.fDots = 0;
        out.fTimeModification=1;
        
        return out;
    }
    
} //namespace IMUSANT