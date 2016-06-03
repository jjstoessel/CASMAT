/*
 *  IMUSANT_interval.h
 *  imusant
 *
 *  Created by Jason Stoessel on 24/06/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 *	This is the engine for generating and creating instances of intervals.  Several operators are provided for
 *	convenience and comparison.
 */

#ifndef __IMUSANT_INTERVAL__
#define __IMUSANT_INTERVAL__

#include "smartpointer.h"
#include "IMUSANT_pitch.h"
#include "IMUSANT_key.h"
#include "bimap.h"

#define NEW
//#define ORIGINAL

#define FLAGSPACE 0x2000

using namespace std;

namespace IMUSANT
{
    
    class IMUSANT_range
    {
    public:
        typedef struct location
        {
            long measure;
            long note_index;
        } location;
        
        IMUSANT_range()
        { partID = 0;  first.measure=0; first.note_index=0; last.measure=0; last.note_index = 0; }
        
        const IMUSANT_range& operator=( const IMUSANT_range& rhs )
        {
            partID=rhs.partID;
            first.measure=rhs.first.measure; first.note_index=rhs.first.note_index;
            last.measure=rhs.last.measure; last.note_index = rhs.last.note_index;  return *this;
        }
        
        friend ostream& operator<<( ostream& os, const IMUSANT_range& range );
        
        location first;
        location last;
        long partID;
    };
    
    class IMUSANT_interval : public smartable
    {
    public:
        //These interval numbers are based upon line of fifths theory, and relies on
        //the implementation of Tonal Pitch Class in IMUSANT_pitch
        //consequently, interval comparison routines needed to be rewritten
        enum
        {
            dimdim2=-19, dimdim6=-18, dimdim3=-17, dimdim7=-16,dimdim4=-15,
            dimdim1=-14, dimdim5=-13, dim2=-12, dim6=-11, dim3=-10, dim7=-9, dim4=-8,
            dim1=-7, dim5=-6, min2=-5, min6=-4, min3=-3, min7=-2, per4=-1,
            per1=0, per5=1, maj2=2, maj6=3, maj3=4, maj7=5, aug4=6,
            aug1=7, aug5=8, aug2=9, aug6=10, aug3=11, aug7=12, augaug4=13,
            augaug1=14, augaug5=15, augaug2=16, augaug6=17, augaug3=18, augaug7=19,
            base=39, /*octave=base,*/ count=base+1, undefined=0x4FFFFFFF/base
        }; //undefined is internal variable
        
        typedef int interval_type;
        
        
        enum quality { perfect = 1, imperfect = -1, diminished = -2, augmented = 2, dissonant = (1<<2) };
        enum direction { descending=-1, unison=0, ascending = 1 };
        
        
        friend SMARTP<IMUSANT_interval> new_IMUSANT_interval();
        friend SMARTP<IMUSANT_interval> new_IMUSANT_interval(const S_IMUSANT_pitch previous, const S_IMUSANT_pitch current);
        
        //getters and setters
        interval_type       getInterval()  { return fInterval; }
        direction           getDirection() { return fDirection; }
        int                 getOctaves() const { return fOctaves; }
        IMUSANT_range		getLocation() const { return fLocation; }
        //calculated gets
        int                 getNumber() const;
        quality             getQuality();
        
        void                setInterval(interval_type interval) { fInterval=interval; }
        void                setOctaves(int oct) { fOctaves=oct; }
        void                setDirection(direction dir) { fDirection=dir; }
        void				setLocation(long partID, long startMeasure,
                                        long startNoteIndex, long endMeasure, long endNoteIndex);
        
        //tests if compound
        bool                   iscompound() const { return fOctaves > 0; }
        //returns a non-compound interval
        IMUSANT_interval       simple();
        //returns the inverted interval
        IMUSANT_interval       inverted();
        //calculates the diatonic inversion required for pre-20th century music
        IMUSANT_interval       inverted_diatonically(IMUSANT_key& key, IMUSANT_pitch::type first);
        //returns distance between intervals, hence 0 is equal, hence used in comparison operators
        int                    compare(const IMUSANT_interval& i) const;
        
        //operators
        /*inline*/ bool operator==(const IMUSANT_interval& rhs) const	{ return (compare(rhs)==0); }
        inline bool operator!=(const IMUSANT_interval& rhs) const	{ return (compare(rhs)!=0); }
        inline bool operator<(const IMUSANT_interval& rhs) const	{ return (compare(rhs)<0); }
        inline bool operator>(const IMUSANT_interval& rhs) const	{ return (compare(rhs)>0); }
        inline bool operator<=(const IMUSANT_interval& rhs) const	{ return (compare(rhs)<=0); }
        inline bool operator>=(const IMUSANT_interval& rhs) const	{ return (compare(rhs)>=0); }
        void operator+(const IMUSANT_interval& rhs );
        friend ostream& operator<<( ostream& os, const IMUSANT_interval& i );
        friend istream& operator>>( istream& is, IMUSANT_interval& i );
        const IMUSANT_interval& operator=( const IMUSANT_interval& rhs );
        
        //conversion operators
        const IMUSANT_interval& operator=( const int binv );
        inline operator int() const;
        
        //increment/decrement
        friend IMUSANT_interval operator+( const IMUSANT_interval& lhs, const IMUSANT_interval& rhs );
        friend IMUSANT_interval operator-( const IMUSANT_interval& lhs, const IMUSANT_interval& rhs );
        IMUSANT_interval& operator+=( const IMUSANT_interval& rhs );
        IMUSANT_interval& operator-=( const IMUSANT_interval& rhs );
        
        IMUSANT_interval& operator++(); //prefix: returns &*this
        const IMUSANT_interval operator++(int); //postfix: returns copy
        
        //static function returns interval and direction
        static IMUSANT_interval calculate(const S_IMUSANT_pitch& first, const S_IMUSANT_pitch& second);
        
        static const string	xmlinterval (interval_type iv);         //! convert a numeric value to string
        static       interval_type	xmlinterval (const string str); //! convert a string to a numeric value
        
        static IMUSANT_interval MakeUniqueInterval();        //! make a unique interval to append for suffix tree
        
        
        IMUSANT_interval() :
        fInterval(undefined),
        fDirection(unison),
        fOctaves(undefined)
        {}
        
        IMUSANT_interval(const IMUSANT_interval& iv) :
        fInterval(iv.fInterval),
        fDirection(iv.fDirection),
        fOctaves(iv.fOctaves),
        fLocation(iv.fLocation)
        {}
        
        IMUSANT_interval(const S_IMUSANT_pitch first, const S_IMUSANT_pitch second);
        IMUSANT_interval(interval_type iv) : fInterval(iv) {}
        IMUSANT_interval(signed short iv)
        {
            fInterval = int2intervaltype(iv);
            check();
        }
        IMUSANT_interval(IMUSANT_pitch::type p1,
                         IMUSANT_pitch::type p2,
                         int octave1,
                         int octave2,
                         IMUSANT_pitch::sign alteration1 = IMUSANT_pitch::natural,
                         IMUSANT_pitch::sign alteration2 = IMUSANT_pitch::natural);
        virtual ~IMUSANT_interval() {}
    
    protected:
        interval_type   fInterval; //fTIC Tonal interval class
        quality         fQuality;
        direction       fDirection;
        int             fOctaves;
        IMUSANT_range	fLocation;
        
    private:
        
        void                check();
        void                check(int calculated_interval);
        
        
        void                increment_fInterval();
        
        static bimap<string, IMUSANT_interval::interval_type>   fInterval2String;
        static IMUSANT_interval::interval_type                  fIntervalTbl[];
        static string                                           fIntervalStrings[];
        
        static interval_type int2intervaltype(int iv);
       
        
    };
    
    typedef SMARTP<IMUSANT_interval> S_IMUSANT_interval;
    
    //new function definitions
    S_IMUSANT_interval new_IMUSANT_interval();
    S_IMUSANT_interval new_IMUSANT_interval(const S_IMUSANT_pitch first, const S_IMUSANT_pitch second);
    
    //friend operator function definitions
    IMUSANT_interval operator+( const IMUSANT_interval& lhs, const IMUSANT_interval& rhs );
    IMUSANT_interval operator-( const IMUSANT_interval& lhs, const IMUSANT_interval& rhs );
    ostream& operator<<( ostream& os, const IMUSANT_interval& i );
    istream& operator>>( istream& is, IMUSANT_interval& i );
    
} //namespace IMUSANT
#endif