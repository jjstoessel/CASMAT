/*
 *  IMUSANT_interval.cpp
 *  imusant
 *
 *  Created by Jason Stoessel on 24/06/06.
 *  Copyright 2006–2016 UNE. All rights reserved.
 *
 *  Description: This is the musical interval domain object. more here
 *
 *  Changes:
 *
 *  29 Jan  2015    Recommissioned for CATSMAT
 *  14 June 2015    getNumber() member function added; a littly flaky. A mathematical solution would be better.
 *  29 June 2015    getQuality() member function added
 *  09 Feb  2016    Commenced redesign of IMUSANT_interval (S-01093): redesigned procedures indicated is NEW macro (ORIGINAL to be removed).
 *  23 Feb  2016    Tonal Pitch Class differences used to calculate interval. Tested without failout across current suit of interval test.
 *  01 Mar  2016    Cleaned up code, removing old code
 *  03 Mar  2016    ctor(p1,p2,octave1,octave2,alteration1,alteration2) added - possibly leaky since it allocs pitches.
 *                  Bug fixed in IMUSANT_interval::calculate for descending interval
 */

#include "IMUSANT_interval.h"

#include <stdlib.h>

//#define _USE_GENERIC_INTERVAL_ //A dumb cludge at the moment for using generic interval comparison instead

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
            os << ((i.fInterval==IMUSANT_interval::per1 && i.fOctaves>0)? "8ve" : IMUSANT_interval::xmlinterval(i.fInterval)) << " ";
            if (i.fDirection!=IMUSANT_interval::vertical_bottomtotop)
            {
                os << (((i.fDirection==IMUSANT_interval::descending)?("\\"):((i.fDirection==IMUSANT_interval::descending)?("\\"):("/")))) << " ";
            }
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
        os << range.first.partID << ", " << range.first.measure << "." << range.first.note_index << " to " << range.last.partID << ", " << range.last.measure << "." << range.last.note_index ;
        //(range.partID.first==range.partID.second ? range.partID.first : (cout << range.partID.first << " & " << range.partID.second))
        return os;
    }
    
    //fIntervalStrings[] and fIntervalTable are co-dependent
    //THESE NEED TO BE CONVERTED TO A BIMAP or or array of pairs STRUCTURE!!!
    //better error handling, etc.
    string	IMUSANT_interval::fIntervalStrings[] = {
        "dimdim2", "dimdim6", "dimdim3", "dimdim7", "dimdim4",
        "dimdim1", "dimdim5", "dim2", "dim6", "dim3", "dim7", "dim4",
        "dim1", "dim5", "min2", "min6", "min3", "min7", "per4",
        "per1", "per5", "maj2", "maj6", "maj3", "maj7", "aug4",
        "aug1", "aug5", "aug2", "aug6", "aug3", "aug7", "augaug4",
        "augaug1", "augaug5", "augaug2", "augaug6", "augaug3", "augaug7"
    };
    
    const int NUM_INTERVAL_TYPES = 39;
    IMUSANT_interval::interval_type IMUSANT_interval::fIntervalTbl[] = {
        IMUSANT_interval::dimdim2,
        IMUSANT_interval::dimdim6,
        IMUSANT_interval::dimdim3,
        IMUSANT_interval::dimdim7,
        IMUSANT_interval::dimdim4,
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

    IMUSANT_interval IMUSANT_interval::MakeUniqueInterval()
    {
        static int unique = undefined;
        
        IMUSANT_interval out(unique);
        
        out.fOctaves = --unique;
        
        if (undefined-unique>FLAGSPACE)
            cerr << "Unique flag limit reached" << endl;
        
        return out;
    }

    IMUSANT_interval::IMUSANT_interval(interval_type iv) : fInterval(iv), fOctaves(0), fDirection(ascending)
    {
        fQuality = calcQuality();
    }
    
    //public ctor member
    IMUSANT_interval::IMUSANT_interval(const S_IMUSANT_pitch first, const S_IMUSANT_pitch second)
    {
        *this = calculate(first,second);
    }
    
    IMUSANT_interval::IMUSANT_interval(IMUSANT_pitch::type p1,
                                       IMUSANT_pitch::type p2,
                                       int octave1,
                                       int octave2,
                                       IMUSANT_pitch::inflection alteration1,
                                       IMUSANT_pitch::inflection alteration2)
    {
        S_IMUSANT_pitch pitch1 = new_IMUSANT_pitch();
        S_IMUSANT_pitch pitch2 = new_IMUSANT_pitch();
        
        pitch1->set(p1, octave1, 1);
        pitch2->set(p2, octave2, 1);
        
        pitch1->setAlteration(alteration1);
        pitch2->setAlteration(alteration2);
        
        *this = calculate(pitch1, pitch2);
    }
    
    //record note locations that form interval
    void
    IMUSANT_interval::setLocation(long startPartID, long startMeasure, long startNoteIndex, long endPartID, long endMeasure, long endNoteIndex)
    {
        fLocation.first.partID = startPartID;
        fLocation.last.partID = endPartID;
        fLocation.first.measure = startMeasure;
        fLocation.first.note_index = startNoteIndex;
        fLocation.last.measure = endMeasure;
        fLocation.last.note_index = endNoteIndex;
    }
    
    //
    // Static function returns interval and direction for two notes
    //
    IMUSANT_interval
    IMUSANT_interval::calculate(const S_IMUSANT_pitch& first, const S_IMUSANT_pitch& second)
    {
        IMUSANT_interval ret;

        if (first->name()!=IMUSANT_pitch::undefined && second->name()!=IMUSANT_pitch::undefined)
        {
            //Must account for octaves for compound intervals.
            if (first->getTPC()==second->getTPC()) //if a unison or compound unison; 
            {
                ret.fInterval = IMUSANT_interval::per1;
                ret.fOctaves = abs(second->octave() - first->octave());
                if (ret.fOctaves == 0)
                    ret.fDirection = IMUSANT_interval::repeat;
                else
                    ret.fDirection = ( second->octave() - first->octave() < 0 ? IMUSANT_interval::descending : IMUSANT_interval::ascending );
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
                ret.fOctaves = ((first->name() + (first->octave()*IMUSANT_pitch::diatonicSteps)) - (second->name() + (second->octave()*IMUSANT_pitch::diatonicSteps)))/7;
                ret.fDirection = IMUSANT_interval::descending;
            }
            ret.fQuality = ret.calcQuality();
            //ret.check();
        }
        
        return ret;
    }
    
    //returns the interval numbers (Tanayev style) without quality, i.e. unison = 0, second = 1, etc.
    int IMUSANT_interval::getNumber() const
    {
        int ret;
        
        //switch (this->simple())
        switch (this->fInterval)
        {
            case dim1:
            case per1:
            case aug1:
                ret = basic::unison;
                break;
            case dim2:
            case min2:
            case maj2:
            case aug2:
                ret = basic::second;
                break;
            case dim3:
            case min3:
            case maj3:
            case aug3:
                ret = basic::third;
                break;
            case dim4:
            case per4:
            case aug4:
                ret = basic::fourth;
                break;
            case dim5:
            case per5:
            case aug5:
                ret = basic::fifth;
                break;
            case dim6:
            case min6:
            case maj6:
            case aug6:
                ret = basic::sixth;
                break;
            case dim7:
            case min7:
            case maj7:
            case aug7:
                ret = basic::seventh;
                break;
            //case octave:
            //    ret = 8;
                break;
            default:
                ret = undefined;
                break;
        }
        
        if (fOctaves>0 & ret==0)
            ret+=7;//ret+=7*fOctaves + 1; //convert to a compound interval
        
        if (this->fDirection==descending)
            ret *= -1;
        
        return ret;
    }

    //IMUSANT_interval::quality IMUSANT_interval::getQuality()
    
    //a pretty dumb dissonance classification - needs plug-in class for different dissonance rules
    IMUSANT_interval::quality IMUSANT_interval::calcQuality()
    {
        quality q = perfect;
        
        if (this->fInterval>=0) {
            if (this->fInterval >= augaug4) {
                q=double_augmented;
            }
            else if (this->fInterval >= aug4)
            {
                q=augmented;
            }
            else
            {
                switch (this->fInterval) {
                    case per1:
                    case per5:
                        q = perfect;
                        break;
                    case maj6:
                    case maj3:
                        q = imperfect;
                        break;
                    case maj2:
                    case maj7:
                        q = dissonant;
                        break;
                    default:
                        q = none;
                        break;
                }
            
            }
        }
        else // <0
        {
            if (this->fInterval<=dimdim5) {
                q=double_diminished;
            }
            else if (this->fInterval<=dim5)
            {
                q=diminished;
            }
            else
            {
                switch (this->fInterval)
                {
                    case min6:
                    case min3:
                        q = imperfect;
                        break;
                    case per4:
                    case min2:
                    case min7:
                        q = dissonant;
                        break;
                    default:
                        q = none;
                        break;
                }
            
            }
        }
            
        
        
        return q;
    }

    //returns a non-compound interval
    IMUSANT_interval IMUSANT_interval::simple()
    {
        IMUSANT_interval ret(*this);
        
        ret.check();
        ret.fOctaves = 0;
        
        return ret;
    }
 
    //Inversion is trivial in new TPC based classed
    IMUSANT_interval	IMUSANT_interval::inverted()
    {
        IMUSANT_interval ret(*this);
        
        if (ret.fOctaves==0) // simple inversion
        {
            //ret.fInterval*=-1; //changing the sign of a tonal interval inverts it.
            ret.fInterval*=IMUSANT_interval::per4;
            ret.fDirection=static_cast<direction>(ret.fDirection*-1);
        }
        else // hand inversions of compound intervals correctly
        {
            ret.fOctaves=-1;
        }
        
        return ret;
    }
    
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
    
    //private member function: checks interval is in correct form.
    void IMUSANT_interval::check(int calculated_interval)
    {
        fDirection = repeat;
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
        
        fQuality = calcQuality();
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
                fDirection = repeat;
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
    
    //operators
    IMUSANT_interval& IMUSANT_interval::operator=( const IMUSANT_interval& rhs )
    {
        fInterval = rhs.fInterval;
        fOctaves = rhs.fOctaves;
        fQuality = rhs.fQuality;
        fDirection = rhs.fDirection;
        fLocation = rhs.fLocation;
        return *this;
    }
#pragma mark IMUSANT_interval::operator int()
    /*
     *  operator int()
     *  Uses algorithm based upon Line of Fifths theory to calculate the number of semitones
     *  in an pitch interval (pi). Since a fifth is pi=7, multiplying abs(fInterval) gives
     *  the number of semintones interated in a line of fifths, but for abs(fInterval) > 1, must
     *  be constrained to the octave by mod 12. A negative result must be "inverted"
     *  by transposing an octave (pi=12), and additional octaves (pi=12) added for coumpound intervals.
     *
     *  pi = n*7%12 (effectively base 7 to base 12)
     *
     *  returns: semitones in interval
     *  used by: operator-=, operator+=
     */
#ifndef _USE_GENERIC_INTERVAL_
    IMUSANT_interval::operator int() const
    {
        int r = 0;
        
        //no need to handle unisons
        if (abs(fInterval)>0)
        {
            if (abs(fInterval)==1) //handle 5ths
                r = 7 * fInterval;
            else
                r = (fInterval*7) % 12; //handle all other intervals as multiples of 5ths
        
            if (r<0) //inverted negative intervals
                r+=12;
        }
        
        r+=12*fOctaves; //convert to a compound interval
        
        //added 28/11/2016 - sign the interval according to melodic direction
        //if(fDirection!=unison || fDirection!=vertical_bottomtotop) r*=fDirection;
            
        return r;
    }
#elif defined _USE_GENERIC_INTERVAL_   //test only - correct function is above
    IMUSANT_interval::operator int() const
    {
        int r = 0;
        
        //no need to handle unisons
        if (abs(fInterval)>0)
        {
            r = getNumber();
                    
            if (r<0) //inverted negative intervals
                    r+=7;
        }
        
        r+=7*fOctaves; //convert to a compound interval
        
        return r;
    }
#endif
//    const IMUSANT_interval& IMUSANT_interval::operator=( const int binv )
//    {
//        fInterval = int2intervaltype(binv);
//        check();
//        
//        return *this;
//    }
    
    IMUSANT_interval& IMUSANT_interval::operator+=( const IMUSANT_interval& rhs )
    {
        fInterval = int2intervaltype((int)*this + (int)rhs);
        check();
        return *this;
    }
    
    /*
     *  operator-=
     *
     *  Adds two intervals together (compounding)
     *
     *  returns: new interval
     *
     */
    IMUSANT_interval& IMUSANT_interval::operator-=( const IMUSANT_interval& rhs )
    {
        fInterval = int2intervaltype((int)*this - (int)rhs);
        check();
        return *this;
    }
    
    /*
     * operator++
     *
     * Expands an interval by a semitone. Esoteric function not currently used.
     *
     */
    IMUSANT_interval& IMUSANT_interval::operator++() //prefix: returns &*this
    {
        // fInterval++;
        increment_fInterval();
        check();
        return *this;
    }
    
    /*
     * const operator++
     *
     * Expands an interval by a semitone. Esoteric function not currently used.
     *
     */
    const IMUSANT_interval IMUSANT_interval::operator++(int) //postfix: returns copy
    {
        IMUSANT_interval ret(*this);
        
        ret.increment_fInterval();
        ret.check();
        
        return ret;
    }
    
    /*
     * increment_fInterval()
     *
     * Expands interval upwards by a semitone.
     *
     */
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
                    //fInterval = fIntervalTbl[index+1];  // otherwise set fInterval to the next value.
                    fInterval+=7;
                }
            }
        }
    }
    
    
}//namespace IMUSANT
