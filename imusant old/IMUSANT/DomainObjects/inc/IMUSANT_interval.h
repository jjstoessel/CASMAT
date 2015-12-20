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

#define ORIGINAL = 1

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
        
#ifdef ORIGINAL
        enum
        {
            dim1=-1, perf1=0, aug1=1, dim2=3, min2=4, maj2=5, aug2=6, dim3=8, min3=9, maj3=10,
            aug3=11, dim4=13, per4=14, aug4=15, dim5=18, per5=19, aug5=20, dim6=21, min6=23, maj6=24, aug6=25,
            dim7=26, min7=28, maj7=29, aug7=30, dim8=32, base=33, octave=base, count=base+1, undefined=0x4FFFFFFF/base
        }  ; //undefined is internal variable
        
        int getInterval() { return fInterval; }
#endif
        
#ifdef NEW
        enum interval_type
        {
            dim1=-1, perf1=0, aug1=1, dim2=3, min2=4, maj2=5, aug2=6, dim3=8, min3=9, maj3=10,
            aug3=11, dim4=13, per4=14, aug4=15, dim5=18, per5=19, aug5=20, dim6=21, min6=23, maj6=24, aug6=25,
            dim7=26, min7=28, maj7=29, aug7=30, dim8=32, base=33, octave=base, count=base+1, undefined=0x4FFFFFFF/base
        }  ;
        
        interval_type getInterval() { return fInterval; }
#endif
        
        enum direction { descending=-1, unison=0, ascending = 1 };
        
        enum quality { perfect = 1, imperfect = (1<<1), dissonant = (1<<2) };
        
        friend SMARTP<IMUSANT_interval> new_IMUSANT_interval();
        friend SMARTP<IMUSANT_interval> new_IMUSANT_interval(const S_IMUSANT_pitch previous, const S_IMUSANT_pitch current);
        
        //getter and setters
        
        int                 getNumber();
        direction           getDirection() { return fDirection; }
        int                 getOctaves() { return fOctaves; }
        IMUSANT_range		getLocation() const { return fLocation; }
        int                 getQuality();
        
        void				setLocation(long partID, long startMeasure,
                                        long startNoteIndex, long endMeasure, long endNoteIndex);
        
        //tests if compound
        bool				iscompound() const { return fOctaves > 0; }
        //returns a non-compound interval
        IMUSANT_interval	simple();
        //returns the inverted interval
        IMUSANT_interval	inverted();
        //calculates the diatonic inversion required for pre-20th century music
        IMUSANT_interval	inverted_diatonically(IMUSANT_key& key, IMUSANT_pitch::type first);
        //returns distance between intervals, hence 0 is equal, hence used in comparison operators
        signed int			compare(const IMUSANT_interval& i) const;
        
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
        const IMUSANT_interval& operator=( const signed int binv );
        inline operator signed int() const { return (fInterval+(base*fOctaves))*fDirection; }
        
        //increment/decrement
        friend IMUSANT_interval operator+( const IMUSANT_interval& lhs, const IMUSANT_interval& rhs );
        friend IMUSANT_interval operator-( const IMUSANT_interval& lhs, const IMUSANT_interval& rhs );
        IMUSANT_interval& operator+=( const IMUSANT_interval& rhs );
        IMUSANT_interval& operator-=( const IMUSANT_interval& rhs );
        
        IMUSANT_interval& operator++(); //prefix: returns &*this
        const IMUSANT_interval operator++(int); //postfix: returns copy
        
        //static function returns interval and direction
        static IMUSANT_interval calculate(const S_IMUSANT_pitch& first, const S_IMUSANT_pitch& second);
        
#ifdef ORIGINAL
        
        static const string	xmlinterval (int iv);                   //! convert a numeric value to string
        static       int	xmlinterval (const string str);         //! convert a string to a numeric value
#endif
        
#ifdef NEW
        static const string	xmlinterval (interval_type iv);         //! convert a numeric value to string
        static       interval_type	xmlinterval (const string str); //! convert a string to a numeric value
#endif
        
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
        
#ifdef NEW
        IMUSANT_interval(interval_type iv) : fInterval(iv)
        {}
        
        IMUSANT_interval(signed short iv)
        {
            fInterval = int2intervaltype(iv);
            check();
        }
#endif
        
#ifdef ORIGINAL
        IMUSANT_interval(signed short iv)
        {
            fInterval = iv;
            check();
        }
#endif
        virtual ~IMUSANT_interval() {}
        
    private:
        
        
        
#ifdef ORIGINAL
        
        void check();
        
        int   fInterval;
        
        static bimap<string, int>	fInterval2String;
        static int                  fIntervalTbl[];
        static string               fIntervalStrings[];
#endif
        
#ifdef NEW
        
        void            check();
        void            check(int calculated_interval);
        
        interval_type   fInterval;
        void            increment_fInterval();
        
        static bimap<string, IMUSANT_interval::interval_type>   fInterval2String;
        static IMUSANT_interval::interval_type                  fIntervalTbl[];
        static string                                           fIntervalStrings[];
        
        static interval_type int2intervaltype(int iv);
#endif
        
        direction       fDirection;
        int             fOctaves;
        IMUSANT_range	fLocation;
        
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