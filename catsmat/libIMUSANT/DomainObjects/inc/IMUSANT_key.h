/*
 *  IMUSANT_key.h
 *  imusant
 *
 *  Created by Jason Stoessel on 30/08/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __IMUSANT_KEY__
#define __IMUSANT_KEY__

#include <string>

#include "bimap.h"
#include "IMUSANT_pitch.h"

namespace IMUSANT
{
    
    class IMUSANT_key;
    
    ostream& operator<< (ostream& os, const IMUSANT_key& elt );
    
    /*!
     \brief An IMUSANT key representation.
     */
    class IMUSANT_key
    {
    public:
        
        enum { undefined=-1 };
        enum mode {  generic = 0, dorian=1, hypodorian, phrygian, hypophrygian, lydian, hypolydian, mixolydian, hypomixolydian, aeolian,
                     locrian, ionian, major, minor, last=minor };
        
        IMUSANT_key (int fifths=undefined, mode m=IMUSANT_key::generic, int cancel=undefined)
            :   fFifths(fifths),
                fMode(m),
                fCancel(cancel)
        { }
        
        void operator=(const IMUSANT_key& key);
        bool operator==(const IMUSANT_key& key) const;
        bool operator!=(const IMUSANT_key& key) const;
        
        int	    getFifths()	const	{ return fFifths; }
        mode	getMode() const		{ return fMode; }
        int	    getCancel()	const	{ return fCancel; }
        
        void	setFifths(const int fifths) { fFifths = fifths; }
        void	setMode(const mode m) { fMode = m; }
        void	setCancel(const int cancel) { fCancel = cancel; }
        
        bool	isDefined() const { return (fMode != generic) && (fFifths!=undefined) && (fCancel!=undefined); }
        
        void	print(ostream& os) const;
        
        bool	PitchAlterInSignature(IMUSANT_pitch::type name, signed short alter);
        
        static const string	xmlmode (mode m);
        static       mode	xmlmode (const string str);

        
    private:
        
//        void	CalcMode(); //function determines mode based on signature (fifths) and tonic (or finalis)

        int	    fFifths; //+/- 0-11 (or more), -1 = F maj or D min
        mode	fMode;
        int	    fCancel;
        
        static const int            fModeTbl_Length = 14;
        static mode					fModeTbl[];
        static string				fModeStrings[];
        static pair<IMUSANT_pitch::type,signed short> fFlatFifthsTbl[];
        static pair<IMUSANT_pitch::type,signed short> fSharpFifthsTbl[];
        
    };
    
} //namespace IMUSANT
#endif //__IMUSANT_KEY__