/*
 *  IMUSANT_types.h
 *  imusant- the Intertextual MUSic ANalysis Tool
 *	Project Supervisor: Dr Rex Eakins
 *
 *  Created by Jason Stoessel on 9/05/06.
 *  Copyright 2006 Jason Stoessel. All rights reserved.
 *
 */

//Note utility classes
/*!
 \brief An IMUSANT note duration representation.
 
 */
#ifndef __IMUSANT_types__
#define __IMUSANT_types__

#include "exports.h"
#include "smartpointer.h"
#include "TRational.h"
#include "bimap.h"
#include "IMUSANT_conversions.h"
#include "IMUSANT_visitor.h"
#include "IMUSANT_pitch.h"

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <list>

using namespace std;

namespace IMUSANT
{
    
    class IMUSANT_clef;
    class IMUSANT_time;

    ostream& operator<< (ostream& os, const IMUSANT_clef& elt );
    ostream& operator<< (ostream& os, const IMUSANT_time& elt );

    //handling actual note attached accidentals
    class IMUSANT_accidental : public smartable
    {
    public:
        enum accident
        {
            none = 0,
            sharp=1, natural, flat, double_sharp, sharp_sharp, flat_flat,
            natural_sharp, natural_flat, quarter_flat, quarter_sharp,
            three_quarters_flat, three_quarters_sharp,
            sharp_down, sharp_up, natural_down, natural_up, flat_down, flat_up,
            triple_sharp, triple_flat, slash_quarter_sharp, slash_sharp, slash_flat,
            double_slash_flat, sharp_1, sharp_2, sharp_3, sharp_5, flat_1, flat_2, flat_3, flat_4,
            sori, koron,
            last=koron
        };
        
        friend IMUSANT_SMARTP<IMUSANT_accidental> new_IMUSANT_accidental();
        
        accident                    getAccident()   const	{ return fAccident; }
        IMUSANT_YesNo::type			getCautionary() const	{ return fCautionary; }
        IMUSANT_YesNo::type			getEditorial()  const	{ return fEditorial; }
        IMUSANT_YesNo::type			getCancelling() const	{ return fCancelling; }
        
        void setAccident(accident acc) { fAccident = acc; }
        void setCautionary(IMUSANT_YesNo::type	 yn) { fCautionary = yn; }
        void setEditorial(IMUSANT_YesNo::type	 yn) { fEditorial = yn; }
        void setCancelling(IMUSANT_YesNo::type	yn)	 { fCancelling = yn; }
        
        //! convert a numeric accidental type to a MusicXML string
        static const string	xml(accident d);
        
        //! convert an MusicXML string to a numeric accidental type
        static accident		xml(const string str);
        static accident		AlterToAccident(IMUSANT_pitch::inflection alter);
        
        void print(ostream& os) const;
        
        const IMUSANT_accidental& operator= (const IMUSANT_accidental& rhs)
        {
            fAccident = rhs.fAccident;
            fCautionary = rhs.fCautionary;
            fEditorial = rhs.fEditorial;
            fCancelling = rhs.fCancelling;
            return *this;
        }
        
    protected:
        IMUSANT_accidental() :
            fAccident(none),
            fCautionary(IMUSANT_YesNo::undefined),
            fEditorial(IMUSANT_YesNo::undefined),
            fCancelling(IMUSANT_YesNo::undefined)
        {
            // empty constructor
        }
        
        virtual ~IMUSANT_accidental() {}
        
    private:
        accident        fAccident;
        IMUSANT_YesNo::type		fCautionary;
        IMUSANT_YesNo::type		fEditorial;
        IMUSANT_YesNo::type		fCancelling;
        
        static bimap<string, accident> fAccident2String;
        static accident fAccidentTbl[];
        static string 	fAccidentStrings[];
    };
    typedef IMUSANT_SMARTP<IMUSANT_accidental> S_IMUSANT_accidental;
    
    S_IMUSANT_accidental new_IMUSANT_accidental();
    
    
    /*!
     \brief an IMUSANT clef representation.
     
     */
    class IMUSANT_clef
    {
    public:
        enum { G_clef = 'G', F_clef = 'F', C_clef = 'C', D_clef = 'D', tablature = 'T', percussion = 'P', undefined = ' ' };
        
        IMUSANT_clef( char sign=IMUSANT_clef::undefined, short line=0, short transposition=0)
        : fSign(sign), fLine(line), fOctaveChange(transposition){}
        virtual ~IMUSANT_clef(){}
        
        const char	getSign() const { return fSign; }
        short	getLine() const { return fLine; }
        short	getTransposition() const { return fOctaveChange; }
        
        void	setSign( char sign );
        void	setLine( short line ) { fLine = line; }
        void	setTransposition (short transposition) { fOctaveChange = transposition; }
        
        bool	isDefined() const { return fSign!=undefined; }
        
        IMUSANT_clef& operator= (const IMUSANT_clef& clef);
        bool operator!= (const IMUSANT_clef& clef) const;
        bool operator== (const IMUSANT_clef& clef) const;
        
        void print(ostream& os) const { os << "<CLEF>" << fSign << fLine << "@" << fOctaveChange << "<\\CLEF>" << endl; }
        //To do: friend function with staff class to account for non-standard staves.
        
    private:
        char	fSign;  //G,C,F (d?)
        short	fLine;  //from bottom upwards 1-5
        short	fOctaveChange; //transposing clefs negative for number octaves lower, positive for octaves higher
    };
    
    class IMUSANT_time
    {
    public:
        //fSymbol values
        //composite, i.e. 5+3/8, where only one denom is required,
        //multiple (though often referred to as composite, i.e. 2/4 + 3/8
        //NB. -1/1 is unmeasured
        enum symbol {	undefined = 0, common=1, cut, single_number, normal, composite, multiple,\
            C, O, Cdot, Odot, cutC, cutO, cutOdot, cutCdot, C2, O2, C3, O3, last=O3 };
        
        IMUSANT_time() : fSymbol(undefined) {}
        //IMUSANT_time(long num=-1, long denom=1, int symbol=IMUSANT_time::common);
        IMUSANT_time(vector<int>& num, vector<int>& denom, symbol symbol)
        : fBeatNum(num), fBeatDenom(denom), fSymbol(symbol) {}
        
        virtual ~IMUSANT_time(){}
        
        void addNumerator(const int num);
        void addDenominator(const int denom);
        const vector<int>&	getNumerator() const { return fBeatNum; }
        const vector<int>&	getDenominator() const { return fBeatDenom; }
        
        symbol			getSymbol() const { return fSymbol; }
        
        void			setSymbol(const symbol sym) { fSymbol = sym; }
        //in this test, we assume that single number is possible, hence no text of fBeatDenom
        bool			isMeasured() const { return (!fBeatNum.empty()) || (fSymbol!=undefined); }
        
        void print(ostream& os) const;
        
        //to do: set functions, string parser
        
        bool			operator!=(const IMUSANT_time& time) const;
        void			operator=(const IMUSANT_time& time);
        
        
        static const string	xmlsymbol (symbol sym);
        //! convert a string to a numeric value
        static       symbol	xmlsymbol (const string str);
        
    private:
        vector<int>	fBeatNum;	  //number of beats
        vector<int>	fBeatDenom;  //beat type
        symbol			fSymbol;
        
        static bimap<string, symbol>	fType2String;
        static symbol	fSymbolTbl[];
        static string	fSymbolStrings[];
    };

#define CONTAINER_TYPE vector<std::string>
    
    //This is one lyric set to a note, may be multisyllabic
    class IMUSANT_lyric : public smartable, public IMUSANT_visitable
    {
    public:
        
        friend IMUSANT_SMARTP<IMUSANT_lyric> new_IMUSANT_lyric();
        
        void	addSyllable(const string text) { this->fSyllables.push_back(text); }
        
        void	setSyllabic(const IMUSANT_syllabic::type type) { fSyllabic = (IMUSANT_syllabic::type)(fSyllabic|type); }
        void	setNumber(int num) { fNumber = num; }
        void	setNumber_v3(string num) { fNumber_v3 = num; }
        void    setName(string name) { fName = name; }
        
        const CONTAINER_TYPE&	getSyllables() const { return fSyllables; }
        const IMUSANT_syllabic::type	getSyllabic() const { return fSyllabic; }
        bool					isMultiSyllablic() { return fSyllables.size() > 1; }
        int                     getNumber() { return fNumber; }
        string					getNumber_v3() { return fNumber_v3; }
        string                  getName() { return fName; }
            
        
        void accept(IMUSANT_visitor& visitor);
        
    protected:
        IMUSANT_lyric() : fSyllabic(IMUSANT_syllabic::undefined) {}
        virtual ~IMUSANT_lyric(){}
        
    private:
        CONTAINER_TYPE			fSyllables;
        IMUSANT_syllabic::type	fSyllabic;
        int                     fNumber;
        string					fNumber_v3;
        string                  fName;
    };
    typedef IMUSANT_SMARTP<IMUSANT_lyric> S_IMUSANT_lyric;
    
    IMUSANT_SMARTP<IMUSANT_lyric> new_IMUSANT_lyric();

    class IMUSANT_attributes : public smartable, public IMUSANT_visitable
    {
    public:
        friend  IMUSANT_SMARTP<IMUSANT_attributes> new_IMUSANT_attributes();

        void    accept(IMUSANT_visitor& visitor);

        void    setClef(const IMUSANT_clef &clef);
        const   IMUSANT_time &getTime() const;
        void    setTime(const IMUSANT_time &time);
        int     getDivisions_() const;
        void    setDivisions_(int divisions_);
        const   IMUSANT_clef &getClef() const;

    protected:
        IMUSANT_attributes() = default;
        virtual ~IMUSANT_attributes() {}

    private:
        IMUSANT_clef    clef;
        IMUSANT_time    time;
        int             divisions_ = 1;
    };
    typedef IMUSANT_SMARTP<IMUSANT_attributes> S_IMUSANT_attributes;

    IMUSANT_SMARTP<IMUSANT_attributes> new_IMUSANT_attributes();
    
} //namespace IMUSANT
#endif