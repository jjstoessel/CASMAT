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
        IMUSANT_duration* o = new IMUSANT_duration();
        assert (o!=0);
        return o;
    }
    
    //ctor functions
    S_IMUSANT_duration new_IMUSANT_duration(const TRational duration)
    {
        IMUSANT_duration* o = new IMUSANT_duration(duration);
        assert (o!=0);
        return o;
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

    const string
    IMUSANT_duration::
    xmlv3(TRational d)
    {
        return fDuration2Stringv3[d];
    }

    TRational
    IMUSANT_duration::
    xmlv1(const string str)
    {
        return fDuration2Stringv1[str];
    }
    
    TRational
    IMUSANT_duration::
    xmlv3(const string str)
    {
        return fDuration2Stringv3[str];
    }
    
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
            << "<RHYTHM_TYPE>" << xmlv1(duration_) << "<\\RHYTHM_TYPE>"
            << "<DOTS>" << to_string(dots_) << "<\\DOTS>"
            << "<TIME_MOD>" << time_modification_.toString() << "<\\TIME_MOD>";
      //   << "<TIME_MOD>" << time_modification_.toString() << " normal-type " << normal_duration_.toString() << " normal-dots " << normal_dots_ << "<\\TIME_MOD>";
    }
    
    void
    IMUSANT_duration::set(TRational dur, int dots)
    {
        set(dur, dots, TRational(1,1), dur, 0);
    }
    
    void
    IMUSANT_duration::set( TRational dur, int dots, TRational timemod)
    {
        set(dur, dots, timemod, dur, 0);
    }
    
    void
    IMUSANT_duration::set( TRational dur, int dots, TRational timemod, TRational normal_dur, int normal_dots)
    {
        
        duration_=dur;
        dots_ = NormaliseDuration(duration_) + dots;
        time_modification_ = timemod;
        normal_duration_ = normal_dur;
        normal_dots_ = normal_dots;
    }
    
    float
    IMUSANT_duration::
    AsAbsoluteNumeric() const
    {
        //
        // This algorithm translates the static duration values defined above (oneohtwofourth etc) into
        // integral values starting with oneohtwofourth=1, and increasing each longer value by powers of two.
        //
        // When we account for tuples (triplets and the like), and dotted notes, this algorithm may return a
        // floating point number.
        //
        // Note that this algorithm does not explicitly use the normal-type value as it is catered for within
        // the values that are used.  See VersionOne TK-01209 -> "Account for normal-type in IMUSANT_duration::asAbsoluteNumeric()"
        
        // Calculate the simple numeric value by normalising to a scale where smallest rhythmic value = 1.
        long numerator = duration_.getNumerator() * SMALLEST_POSSIBLE_NOTE_VALUE_MULTIPLIER;
        float initial_numeric = numerator / duration_.getDenominator();
        
        // Account for time modifications (tuples)
        float initial_numeric_with_time_mod = initial_numeric;
        if (time_modification_ != IMUSANT_duration::unmeasured)
        {
            initial_numeric_with_time_mod = (initial_numeric * time_modification_.getDenominator()) / time_modification_.getNumerator();
        }
        
        // Account for dots. For each additional dot we add a diminishing fraction of the
        // initial note duration value.
        // (A half of the initial value for the first dot, a quarter for the second, and so on)
        float incremental_val = initial_numeric_with_time_mod;
        int fraction_of_initial_value_to_add = 2;
        for (long index = dots_; index > 0 ; index--)
        {
            incremental_val = (incremental_val + (initial_numeric_with_time_mod / fraction_of_initial_value_to_add));
            fraction_of_initial_value_to_add = fraction_of_initial_value_to_add * 2;
        }
        
        return incremental_val;
    }
    
    const IMUSANT_duration&
    IMUSANT_duration::
    operator= (const IMUSANT_duration& dur)
    {
        this->set(dur.duration_, dur.dots_,dur.time_modification_, dur.normal_duration_, dur.normal_dots_);
        //NormaliseDuration(fDuration);
        return *this;
    }
    
    //
    //  Takes durations represented as a single fraction, and converts this to a form of fraction and dots.
    //
    //  Dotted notes are a geometric series where the sum value of (S) of a duration with n dots is
    //      Sn = a (2 - pow(0.5, n))
    //
    int
    IMUSANT_duration::
    NormaliseDuration(TRational& dur)
    {
        dur.rationalise();
        
        int dots = 0;
        float r = 0.5; //ratio
        float gs = 0.0, intpart = 0.0;
        float base = dur; //cast to float
        
        // superparticular and subsuperparticular ratios are dotted notes
        long n = dur.getNumerator();
        long d = dur.getDenominator();
        //determine if it is a duration that cannot be a dotted note
        if (/*(n%2)==1 &&*/ (d & (d-1)) || (n > 3 && (d-n!=1)) )
        {
            return dots; //0
        }
        
        while (dots<5 && modff(log2(base), &intpart)!=0) //modff returns fraction remainder
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
    
    //
    //  Evaluates if a proportional duration
    TRational
    IMUSANT_duration::
    NormaliseTimeModification(TRational& dur)
    {
        long d = dur.getDenominator();
        TRational time_mod(1,1);
        
        //all basic musical durations have a numerator that is a power of two (inc. 1); 
        bool is_power_of_2 = !(d == 0) && !(d & (d-1));
        
        if (!is_power_of_2)
        {
            int power = log2(d);
            time_mod = TRational(d,1<<power);
            time_mod.rationalise();
            dur = TRational(dur.getNumerator(), 1<<power);
            dur.rationalise();
        }
        
        return time_mod;
    }
    
    // -- Comparision operators ---
    //
    //these also test for equality/inequality of simplified durations: see getSimplifiedDuration.
    bool
    IMUSANT_duration::
    operator!= (const IMUSANT_duration& dur) const
    {
        return ! (*this == dur);
    }
    
    bool
    IMUSANT_duration::
    operator== (const IMUSANT_duration& dur) const
    {
        //straight comparison
        bool dur_match = duration_ == dur.duration_;
        bool dots_match = dots_ == dur.dots_;
        bool time_mod_match = time_modification_ == dur.time_modification_;
        bool normal_duration_match = normal_duration_ == dur.normal_duration_;
        bool normal_dots_match = normal_dots_ == dur.normal_dots_;
        
        //calculated comparison
        bool simplified_duration_match = GetSimplifiedDuration().duration_ == dur.GetSimplifiedDuration().duration_;
        
        return (dur_match
                && dots_match
                && time_mod_match
                && normal_duration_match
                && normal_dots_match
                )
                || simplified_duration_match;
    }
    
    
    //Adds two durations, resulting in an absolute duration without dots or time modification
    //To do: check for simple relationships (dots and time modification) in resulting float
    IMUSANT_duration
    IMUSANT_duration::
    operator+(const IMUSANT_duration& right)
    {
        IMUSANT_duration out;
        
        TRational r = GetSimplifiedDuration().duration_ + right.GetSimplifiedDuration().duration_;
        out.dots_ = NormaliseDuration(r);
        out.time_modification_ = NormaliseTimeModification(r);
        out.duration_ = r;
        if (out.time_modification_ != TRational(0))
            out.normal_duration_=r;
        else
            out.normal_duration_=IMUSANT_duration::unmeasured;
        
        return out;
    }
    
    
    void
    IMUSANT_duration::
    operator+=(const IMUSANT_duration& rhs)
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
        
        TRational r = GetSimplifiedDuration().duration_ - right.GetSimplifiedDuration().duration_;
        out.dots_ = NormaliseDuration(r);
        out.time_modification_ = NormaliseTimeModification(r);
        out.duration_ = r;
        if (out.time_modification_ != TRational(0))
            out.normal_duration_=r;
        else
            out.normal_duration_=IMUSANT_duration::unmeasured;
    
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
        return (GetSimplifiedDuration().duration_ > dur.GetSimplifiedDuration().duration_);
    }
    
    bool
    IMUSANT_duration::
    operator <(const IMUSANT_duration &dur) const
    {
        return (GetSimplifiedDuration().duration_ < dur.GetSimplifiedDuration().duration_);
    }
    
    //
    // Simplifies durations with dots and/or time proportions to simple float in fDuration w/o dots & time mods
    //
    IMUSANT_duration
    IMUSANT_duration::
    GetSimplifiedDuration() const
    {
        IMUSANT_duration out = *this;
        
        //if (dots_>8) throw "more than eight dots encountered";
        //  Dotted notes are a geometric series where the sum value of (S) of a duration with n dots is
        //      Sn = a (2 - pow(0.5, n))
        TRational dotsmultiplier(2,1), normaldotsmultiplier(2,1);
    
        if (normal_dots_)
        {
            TRational normalindex = TRational(1, 1<<normal_dots_);
            normaldotsmultiplier -= normalindex;
            out.normal_duration_ = normal_duration_ * normaldotsmultiplier;
            out.normal_dots_ = 0;
        }
        
        if (time_modification_!=TRational(1,1))
        {
            out.duration_ = (out.normal_duration_/time_modification_)*(duration_/normal_duration_);
            out.duration_.rationalise();
            out.time_modification_=1;
            out.normal_duration_ = out.duration_; //will produce unknown duration types
            out.normal_duration_.rationalise();
            
        }
        
        if (dots_)
        {
            TRational index = TRational(1,1<<dots_);
            dotsmultiplier -= index;
            out.duration_ = out.duration_ * dotsmultiplier;
            out.duration_.rationalise();
            out.normal_duration_ = out.duration_;
            out.dots_ = 0;
        }
    
        return out;
    }
    
} //namespace IMUSANT
