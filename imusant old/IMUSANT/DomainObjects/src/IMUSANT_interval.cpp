/*
 *  IMUSANT_interval.cpp
 *  imusant
 *
 *  Created by Jason Stoessel on 24/06/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 *  Changes:
 *
 *  14 June 2015    getNumber() member function added; a littly flaky. A mathematical solution would be better.
 *  29 June 2015    getQuality() member function added
 *  9  Feb  2016    Commenced redesign of IMUSANT_interval (S-01093): redesigned procedures indicated is NEW macro (ORIGINAL to be removed).
 *  23 Feb  2016    Tonal Pitch Class differences used to calculate interval. Tested without failout across current suit of interval test.
 *
 */

#include "IMUSANT_interval.h"

#include <stdlib.h>

namespace IMUSANT
{
    
    //binary operators required for + and -
    IMUSANT_interval operator+( const IMUSANT_interval& lhs, const IMUSANT_interval& rhs )
    {
        IMUSANT_interval ret(lhs);
        
        ret+=rhs;
        ret.check();
        
        return ret;
    }
    
    IMUSANT_interval operator-( const IMUSANT_interval& lhs, const IMUSANT_interval& rhs )
    {
        IMUSANT_interval ret(lhs);
        
        ret -= rhs;
        ret.check();
        
        return ret;
    }
    
    ostream& operator<<( ostream& os, const IMUSANT_interval& i )
    {
        if (i.fOctaves < IMUSANT_interval::undefined-FLAGSPACE) //don't try to print terminator elements.
        {
            os << IMUSANT_interval::xmlinterval(i.fInterval) << " ";
            os << (((i.fDirection==-1)?("\\"):((i.fDirection==1)?("/"):("")))) << " ";
        }
        else
            os << "undefined ";
        
        return os;
    }
    
    istream& operator>>( istream& is, IMUSANT_interval& i )
    {
        return is;
    }
    
    //ctor functions
    S_IMUSANT_interval new_IMUSANT_interval()
    {
        IMUSANT_interval* o = new IMUSANT_interval();
        assert(o!=0);
        return o;
    }
    
    S_IMUSANT_interval new_IMUSANT_interval(const S_IMUSANT_pitch first, const S_IMUSANT_pitch second)
    {
        IMUSANT_interval* o = new IMUSANT_interval(first, second);
        assert(o!=0);
        return o;
    }
    
    ostream& operator<<( ostream& os, const IMUSANT_range& range )
    {
        os << range.first.measure << ", " << range.first.note_index << ", " << range.partID;
        
        return os;
    }
    
  
#ifdef ORIGINAL
    //
    // Lookup tables and translations from numeric to string representations...
    //
    string	IMUSANT_interval::fIntervalStrings[] = {
        "dim1", "perf1", "aug1", "dim2", "min2", "maj2", "aug2", "dim3",
        "min3", "maj3", "aug3", "dim4", "per4", "aug4", "dim5", "per5",
        "aug5", "dim6", "min6", "maj6", "aug6", "dim7", "min7", "maj7",
        "aug7", "dim8", "octave"
    };
    
    int	IMUSANT_interval::fIntervalTbl[] = {
        dim1, perf1, aug1, dim2, min2, maj2, aug2, dim3, min3, maj3, aug3,
        dim4, per4, aug4, dim5, per5, aug5, dim6, min6, maj6, aug6, dim7,
        min7, maj7, aug7, dim8, octave
    };
    
    bimap<string, int>	IMUSANT_interval::fInterval2String( fIntervalStrings, fIntervalTbl, 27 );
    
    //! convert a numeric value to string
    const string IMUSANT_interval::xmlinterval (int iv)
    {
        return fInterval2String[iv];
    }
    
    //! convert a string to a numeric value
    int	IMUSANT_interval::xmlinterval (const string str)
    {
        return fInterval2String[str];
    }
    
    int IMUSANT_interval::int2intervaltype(int interval)
    {
        //  cout << "INTERVAL = " << interval << endl;
        
        int iv = abs(interval % base);  // get rid of octaves and direction
        
        IMUSANT_interval::interval_type return_value = IMUSANT_interval::undefined;
        bool found = false;
        
        for (int index = 0 ; index < NUM_INTERVAL_TYPES && !found ; index++)
        {
            if (fIntervalTbl[index] >= iv)  // REVISIT  - the >= test doesn't work
            {
                return_value = fIntervalTbl[index];
                found = true;
            }
        }
        return return_value;
    }
    
#endif
    
#ifdef NEW
    //THIS NEEDS TO BE CONVERTED TO A BIMAP STRUCTURE!!!
    //better error handling, etc.
    string	IMUSANT_interval::fIntervalStrings[] = {
        "dimdim4th",
        "dimdim1", "dimdim5", "dim2", "dim6", "dim3", "dim7", "dim4",
        "dim1", "dim5", "min2", "min6", "min3", "min7", "per4",
        "per1", "per5", "maj2", "maj6", "maj3", "maj7", "aug4",
        "aug1", "aug5", "aug2", "aug6", "aug3", "aug7", "augaug4",
        "augaug1", "augaug5", "augaug2", "augaug6", "augaug3", "augaug7"
    };
    
    const int NUM_INTERVAL_TYPES = 35;
    IMUSANT_interval::interval_type IMUSANT_interval::fIntervalTbl[] = {
        IMUSANT_interval::dimdim4th,
        IMUSANT_interval::dimdim1,
        IMUSANT_interval::dimdim5,
        IMUSANT_interval::dim2,
        IMUSANT_interval::dim6,
        IMUSANT_interval::dim3,
        IMUSANT_interval::dim7,
        IMUSANT_interval::dim4,
        IMUSANT_interval::dim1,
        IMUSANT_interval::dim5,
        IMUSANT_interval::min2,
        IMUSANT_interval::min6,
        IMUSANT_interval::min3,
        IMUSANT_interval::min7,
        IMUSANT_interval::per4,
        IMUSANT_interval::per1,
        IMUSANT_interval::per5,
        IMUSANT_interval::maj2,
        IMUSANT_interval::maj6,
        IMUSANT_interval::maj3,
        IMUSANT_interval::maj7,
        IMUSANT_interval::aug4,
        IMUSANT_interval::aug1,
        IMUSANT_interval::aug5,
        IMUSANT_interval::aug2,
        IMUSANT_interval::aug6,
        IMUSANT_interval::aug3,
        IMUSANT_interval::aug7,
        IMUSANT_interval::augaug4,
        IMUSANT_interval::augaug1,
        IMUSANT_interval::augaug5,
        IMUSANT_interval::augaug2,
        IMUSANT_interval::augaug6,
        IMUSANT_interval::augaug3,
        IMUSANT_interval::augaug7
    };
    
    bimap<string, IMUSANT_interval::interval_type>
    IMUSANT_interval::
    fInterval2String( fIntervalStrings, fIntervalTbl, NUM_INTERVAL_TYPES );
    
    //! convert a numeric value to string
    const string IMUSANT_interval::xmlinterval (interval_type iv)
    {
        return fInterval2String[iv];
    }
    
    //! convert a string to a numeric value
    IMUSANT_interval::interval_type	IMUSANT_interval::xmlinterval (const string str)
    {
        return fInterval2String[str];
    }
    
    // convert an integer to an interval_type - returns "undefined" if there is no match.

    IMUSANT_interval::interval_type IMUSANT_interval::int2intervaltype(int interval)
    {
        //  cout << "INTERVAL = " << interval << endl;
        
        interval_type iv = (interval_type)abs(interval % base);  // get rid of octaves and direction
        
        IMUSANT_interval::interval_type return_value = IMUSANT_interval::undefined;
        bool found = false;
        
        for (int index = 0 ; index < NUM_INTERVAL_TYPES && !found ; index++)
        {
            if (fIntervalTbl[index] >= iv)  // REVISIT  - the >= test doesn't work
            {
                return_value = fIntervalTbl[index];
                found = true;
            }
        }
        return return_value;
    }
    
    
#endif
    
    
    IMUSANT_interval IMUSANT_interval::MakeUniqueInterval()
    {
        static int unique = undefined;
        
        IMUSANT_interval out(unique);
        
        out.fOctaves = --unique;
        
        if (undefined-unique>FLAGSPACE)
            cerr << "Unique flag limit reached" << endl;
        
        return out;
    }
    
    //protected ctor member
    IMUSANT_interval::IMUSANT_interval(const S_IMUSANT_pitch first, const S_IMUSANT_pitch second)
    {
        *this = calculate(first,second);
    }
    
    //record note locations that form interval
    void
    IMUSANT_interval::setLocation(long partID, long startMeasure, long startNoteIndex, long endMeasure, long endNoteIndex)
    {
        fLocation.partID = partID;
        fLocation.first.measure = startMeasure;
        fLocation.first.note_index = startNoteIndex;
        fLocation.last.measure = endMeasure;
        fLocation.last.note_index = endNoteIndex;
    }
    
#ifdef ORIGINAL
    //static function returns interval and direction for two notes
    IMUSANT_interval IMUSANT_interval::calculate(const S_IMUSANT_pitch& first, const S_IMUSANT_pitch& second)
    {
        IMUSANT_interval ret;
        
        if (first->name()!=IMUSANT_pitch::undefined && second->name()!=IMUSANT_pitch::undefined)
        {
            int first_octave = (first->octave() * base);
            int second_octave = (second->octave() * base);
            
            int first_name = (int)first->name();
            int second_name = (int)second->name();
            
            int first_absolute =  first_name + first->alteration() + first_octave;
            int second_absolute = second_name + second->alteration() + second_octave;
            
            ret.fOctaves = 0;
            
            ret.fInterval = second_absolute - first_absolute;
            ret.check();
        }
        
        return ret;
    }
#endif
    
#ifdef NEW
    
    //
    // Static function returns interval and direction for two notes
    //
    IMUSANT_interval
    IMUSANT_interval::calculate(const S_IMUSANT_pitch& first, const S_IMUSANT_pitch& second)
    {
        IMUSANT_interval ret;
        //make sure TPC set; this should be set on pitch creation, but isn't at the moment
        first->setTonalPitchClass(); second->setTonalPitchClass();
        if (first->name()!=IMUSANT_pitch::undefined && second->name()!=IMUSANT_pitch::undefined)
        {
            //Must account for octaves for compound intervals.
            
            if (first->getTPC()==second->getTPC()) //if a unison or compound unison; 
            {
                ret.fInterval = IMUSANT_interval::per1;
                ret.fOctaves = abs(second->octave() - first->octave());
                ret.fDirection = IMUSANT_interval::unison;
                ret.fQuality = perfect;
            }
            else if (*second>*first) //ascending interval
            {
                ret.fInterval = second->getTPC() - first->getTPC();
                ret.fOctaves = ((second->name() + (second->octave()*IMUSANT_pitch::diatonicSteps)) - (first->name() + (first->octave()*IMUSANT_pitch::diatonicSteps)))/7;
                ret.fDirection = IMUSANT_interval::ascending;
            }
            else //descending interval
            {
                ret.fInterval = (interval_type)(first->getTPC() - second->getTPC());
                ret.fOctaves = ret.fOctaves = (first->name() + (first->octave()*IMUSANT_pitch::diatonicSteps) - second->name() + (second->octave()*IMUSANT_pitch::diatonicSteps))/7;
                ret.fDirection = IMUSANT_interval::descending;
            }
            
            //ret.check();
        }
        
        return ret;
    }
#endif
    
    //returns the interval numbers without quality
    int IMUSANT_interval::getNumber() const
    {
        int ret;
        
        //switch (this->simple())
        switch (this->fInterval)
        {
            case dim1:
            case per1:
            case aug1:
                ret = 1;
                break;
            case dim2:
            case min2:
            case maj2:
            case aug2:
                ret = 2;
                break;
            case dim3:
            case min3:
            case maj3:
            case aug3:
                ret = 3;
                break;
            case dim4:
            case per4:
            case aug4:
                ret = 4;
                break;
            case dim5:
            case per5:
            case aug5:
                ret = 5;
                break;
            case dim6:
            case min6:
            case maj6:
            case aug6:
                ret = 6;
                break;
            case dim7:
            case min7:
            case maj7:
            case aug7:
                ret = 7;
                break;
            //case octave:
            //    ret = 8;
                break;
            default:
                ret = undefined;
                break;
        }
        
        if (this->fDirection==descending)
            ret *= -1;
        
        return ret;
    }
#ifdef ORIGINAL
    int IMUSANT_interval::getQuality()
    {
        int quality = 0;
        
        //switch (this->simple())
        switch (this->fInterval)
        {
            case per1:
            case per5:
            //case octave:
                quality = perfect;
                break;
            case min3:
            case maj3:
            case min6:
            case maj6:
                quality = imperfect;
                break;
            case dim1:
            case aug1:
            case dim2:
            case min2:
            case maj2:
            case aug2:
            case dim3:
            case aug3:
            case dim4:
            case per4:
            case aug4:
            case dim5:
            case aug5:
            case dim6:
            case aug6:
            case dim7:
            case min7:
            case maj7:
            case aug7:
                quality = dissonant;
                break;
        }
        
        return quality;
    }
#endif
#ifdef NEW
    IMUSANT_interval::quality IMUSANT_interval::getQuality()
    {
        quality q = perfect;
        
        //switch (this->simple())
        switch (this->fInterval)
        {
            case per1:
            case per5:
                //case octave:
                q = perfect;
                break;
            case min3:
            case maj3:
            case min6:
            case maj6:
                q = imperfect;
                break;
            case dim1:
            case aug1:
            case dim2:
            case min2:
            case maj2:
            case aug2:
            case dim3:
            case aug3:
            case dim4:
            case per4:
            case aug4:
            case dim5:
            case aug5:
            case dim6:
            case aug6:
            case dim7:
            case min7:
            case maj7:
            case aug7:
                q = dissonant;
                break;
        }
        
        return q;
    }
#endif
    //returns a non-compound interval
    IMUSANT_interval IMUSANT_interval::simple()
    {
        IMUSANT_interval ret(*this);
        
        ret.check();
        ret.fOctaves = 0;
        
        return ret;
    }
 
    //returns the literally inverted interval
#ifdef ORIGINAL
    //NOT IMPLEMENTED!
    IMUSANT_interval	IMUSANT_interval::inverted()
    {
        IMUSANT_interval ret(*this);
        
        if (ret.fDirection==ascending)
            ret.fDirection = descending;
        else if (ret.fDirection==descending)
            ret.fDirection = ascending;
        
        return ret;
    }
#endif
#ifdef NEW
    //Inversion is trivial in new TPC based classed
    IMUSANT_interval	IMUSANT_interval::inverted()
    {
        IMUSANT_interval ret(*this);
        
        if (ret.fOctaves==0) // simple inversion
        {
            ret.fInterval*=-1; //changing the sign of a tonal interval inverts it.
            ret.fDirection=static_cast<direction>(ret.fDirection*-1);
        }
        else // hand inversions of compound intervals correctly
        {
            ret.fOctaves=-1;
        }
        
        return ret;
    }
#endif
    //calculates the diatonic inversion required for pre-20th century music
    //NOT IMPLEMENTED!
    IMUSANT_interval	IMUSANT_interval::inverted_diatonically(IMUSANT_key& key, IMUSANT_pitch::type first)
    {
        IMUSANT_interval ret(*this);
        //determine whether pitches are diatonic and map inverted interval to diatonic key.
        //eg. CE->CA (maj3 transformed to min3)
        
        
        return ret;
    }

    //returns distance between intervals, hence 0 is equal, hence used in comparison operators
    int	IMUSANT_interval::compare(const IMUSANT_interval& i) const
    {
        return (int)*this-(int)i;
    }
    
#ifdef ORIGINAL
    //private member function: checks interval is in correct form.
    void IMUSANT_interval::check()
    {
        //check that fInterval is positive except dim unison
        if (fInterval!=undefined)
        {
            if (fInterval!=0 && fInterval!=-1)
            {
                if (fInterval/abs(fInterval)==1)
                    fDirection = ascending;
                else if (fInterval/abs(fInterval)==-1)
                {
                    fDirection = descending;
                    fInterval = abs(fInterval);
                }
            }
            
            //fInterval should have range -1 to base
            if (fInterval==0)
                fDirection = unison;
            else if (fInterval>base)
            {
                fOctaves = fInterval/base;
                fInterval %= base;
            }
        }
        else
            cerr << "Check on undefined interval." << endl;
    }
#endif
    
#ifdef NEW
    //private member function: checks interval is in correct form.
    void IMUSANT_interval::check(int calculated_interval)
    {
        fDirection = unison;
        fOctaves = 0;
        fInterval = int2intervaltype(calculated_interval);
        
        if (calculated_interval != 0 && calculated_interval != -1)
        {
            if (calculated_interval / abs(calculated_interval) == 1)
            {
                fDirection = ascending;
            }
            
            else if (calculated_interval / abs(calculated_interval) == -1)
            {
                fDirection = descending;
            }
        }
        
        //fInterval should have range -1 to base
        
        if (calculated_interval > base)
        {
            fOctaves = calculated_interval / base;
            
            int base_interval;
            base_interval = calculated_interval % base;
            
            fInterval = int2intervaltype(base_interval);
        }
        
        fQuality = getQuality();
    }
    
    //private member function: checks interval is in correct form.
    void IMUSANT_interval::check()
    {
        if (fInterval!=undefined)
        {
            if (fInterval!=0 && fInterval!=-1)
            {
                if (fInterval/abs(fInterval)==1)
                    fDirection = ascending;
                else if (fInterval/abs(fInterval)==-1)
                {
                    fDirection = descending;
                    fInterval = int2intervaltype(abs(fInterval));
                }
            }
            
            //fInterval should have range -1 to base
            if (fInterval==0)
                fDirection = unison;
            else if (fInterval>base)
            {
                fOctaves = fInterval/base;
                // fInterval %= base;
                
                int tmp_fInterval;
                tmp_fInterval = fInterval % base;
                fInterval = int2intervaltype(tmp_fInterval);
            }
        }
        else
            cerr << "Check on undefined interval." << endl;
    }
#endif
    
    //operators
    const IMUSANT_interval& IMUSANT_interval::operator=( const IMUSANT_interval& rhs )
    {
        fInterval = rhs.fInterval;
        fOctaves = rhs.fOctaves;
        fDirection = rhs.fDirection;
        fLocation = rhs.fLocation;
        return *this;
    }
    
#ifdef NEW
    IMUSANT_interval::operator int() const
    {
        int r = 0;
        
        if (abs(fInterval)>0)
        {
            if (abs(fInterval)==1)
                r = 7 * fInterval;
            else
                r = (fInterval*7) % 12;
        
            if (r<0)
                r+=12;
        }
        
        r+=12*fOctaves;
        
        return r;
    }
    
    const IMUSANT_interval& IMUSANT_interval::operator=( const int binv )
    {
        fInterval = int2intervaltype(binv);
        check();
        
        return *this;
    }
    
    IMUSANT_interval& IMUSANT_interval::operator+=( const IMUSANT_interval& rhs )
    {
        fInterval =  int2intervaltype((int)*this + (int)rhs);
        check();
        return *this;
    }
    
    IMUSANT_interval& IMUSANT_interval::operator-=( const IMUSANT_interval& rhs )
    {
        fInterval = int2intervaltype((int)*this - (int)rhs);
        check();
        return *this;
    }
    
    IMUSANT_interval& IMUSANT_interval::operator++() //prefix: returns &*this
    {
        // fInterval++;
        increment_fInterval();
        check();
        return *this;
    }
    
    const IMUSANT_interval IMUSANT_interval::operator++(int) //postfix: returns copy
    {
        IMUSANT_interval ret(*this);
        
        // ret.fInterval++;
        ret.increment_fInterval();
        ret.check();
        
        return ret;
    }
    
    void
    IMUSANT_interval::
    increment_fInterval()
    {
        for (int index = 0 ; index < NUM_INTERVAL_TYPES ; index++)  // iterate through the table of intervals...
        {
            if (fIntervalTbl[index] == fInterval)   // find the current value if fInterval
            {
                if (index == NUM_INTERVAL_TYPES - 1)
                {
                    fInterval = fIntervalTbl[0];   // if we are at the end set fInterval to the first value (wrap)
                }
                else
                {
                    fInterval = fIntervalTbl[index+1];  // otherwise set fInterval to the next value.
                }
            }
        }
    }
    
#endif
    
#ifdef ORIGINAL
    const IMUSANT_interval& IMUSANT_interval::operator=( const signed int binv )
    {
        fInterval = binv;
        check();
        
        return *this;
    }
    
    IMUSANT_interval& IMUSANT_interval::operator+=( const IMUSANT_interval& rhs )
    {
        fInterval = (signed short)*this + (signed short)rhs;
        check();
        return *this;
    }
    
    IMUSANT_interval& IMUSANT_interval::operator-=( const IMUSANT_interval& rhs )
    {
        fInterval = (signed short)*this - (signed short)rhs;
        check();
        return *this;
    }
    
    IMUSANT_interval& IMUSANT_interval::operator++() //prefix: returns &*this
    {
        fInterval++;
        check();
        return *this;
    }
    
    const IMUSANT_interval IMUSANT_interval::operator++(int) //postfix: returns copy
    {
        IMUSANT_interval ret(*this);
        
        ret.fInterval++;
        ret.check();
        
        return ret;
    }
    
#endif
    
    
}//namespace IMUSANT
