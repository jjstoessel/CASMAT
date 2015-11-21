/*
 *  IMUSANT_barline.h
 *  imusant
 *
 *  Created by Jason Stoessel on 18/06/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __IMUSANT_BARLINE__
#define __IMUSANT_BARLINE__

#include "IMUSANT_element.h"
#include "IMUSANT_conversions.h"

#include <string>

namespace IMUSANT
{
    //
    //  IMUSANT_ending
    //
    class IMUSANT_ending : public smartable
    {
    public:
        
        friend SMARTP<IMUSANT_ending> new_IMUSANT_ending();
        
        enum type { undefined=0, start=1, stop, last=stop };
        static const string	xml (type d);               // convert a string to a numeric value
        static       type	xml (const string str);     // convert type to IMUSANT syllabic type
        
        IMUSANT_ending() : fType(undefined), fOrdinal(0){}
        virtual ~IMUSANT_ending(){}
        
        void	setType(type t) { fType = t; }
        void	setNumber(long times) { fOrdinal = times; }
        type	getType() const { return fType; }
        long	getNumber() const { return fOrdinal; }
        
        void    print (ostream& os) const;
        
    private:
        type	fType;
        long	fOrdinal;
    };
    typedef SMARTP<IMUSANT_ending> S_IMUSANT_ending;
    
    
    //
    // IMUSANT_repeat
    //
    class IMUSANT_repeat : public smartable
    {
    public:
        friend SMARTP<IMUSANT_repeat> new_IMUSANT_repeat();
        
        enum direction { undefined=0, forward=1, backward, last=backward };
        static const string	xml (direction d);                 // convert type to string
        static       direction	xml (const string str);        // convert a string to a numeric value
        
        IMUSANT_repeat() : fDirection(undefined), fTimes(0) {}
        virtual ~IMUSANT_repeat() {}
        
        void		setDirection(direction d) { fDirection = d; }
        void		setTimes(long times) { fTimes=times; }
        direction	getDirection() const { return fDirection; }
        long		getTimes() const { return fTimes; }
        
        void        print (ostream& os) const;
        
    private:
        direction	fDirection;
        long		fTimes;

    };
    typedef SMARTP<IMUSANT_repeat> S_IMUSANT_repeat;
    
    
    //
    // IMUSANT_barline
    //
    class EXP IMUSANT_barline : public IMUSANT_element
    {
    public:
        enum location {
            undefined=0, right=1, left, middle,
            lastloc= middle
        };
        
        enum type {
            none=1, regular, dotted, heavy, light_light,
            light_heavy, heavy_light, heavy_heavy,
            last=heavy_heavy };
        
        EXP friend SMARTP<IMUSANT_barline> new_IMUSANT_barline();
        
        virtual void accept(IMUSANT_visitor& visitor);
        
        void		setLocation(location loc);
        void		setBarStyle(type style);
        void		setEnding(const S_IMUSANT_ending ending) { fEnding = ending; }
        void		setRepeat(const S_IMUSANT_repeat repeat) { fRepeat = repeat; }
        
        location	getLocation()	const 	{ return fLocation; }
        type		getBarStyle()	const 	{ return fBarStyle; }

        S_IMUSANT_ending&	ending() 		{ return fEnding; }
        S_IMUSANT_repeat&	repeat() 		{ return fRepeat; }
        //SSegno&		segno()		 	{ return fSegno; }
        //SCoda&		coda()		 	{ return fCoda; }
        
        static const string	xmllocation (location d);               // convert an integer location to a string
        static location		xmllocation (const string str);         // convert an string to an integer location
        
        static const string	xmlstyle (type d);                      // convert an integer bar style to a string
        static type			xmlstyle (const string str);            // convert an string to an integer bar style
        
        void    print (ostream& os) const;
        
    protected:
        IMUSANT_barline() : fLocation(undefined), fBarStyle(none) {}
        virtual ~IMUSANT_barline() {}
        
    private:
        
        location 		fLocation;          // the barline location attribute (default to right)
        type			fBarStyle;          // optionnal barline style
        
        S_IMUSANT_ending	fEnding;
        S_IMUSANT_repeat	fRepeat;
        //SSegno 		fSegno;
        //SCoda 		fCoda;
    };
    typedef SMARTP<IMUSANT_barline> S_IMUSANT_barline;
    
    
    
    SMARTP<IMUSANT_ending> new_IMUSANT_ending();
    SMARTP<IMUSANT_repeat> new_IMUSANT_repeat();
    EXP SMARTP<IMUSANT_barline> new_IMUSANT_barline();
    
} //namespace IMUSANT

#endif //__IMUSANT_BARLINE