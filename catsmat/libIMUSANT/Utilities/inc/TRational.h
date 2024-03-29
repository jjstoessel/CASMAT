/*
 Copyright � Grame 2003
 
 This library is free software; you can redistribute it and modify it under
 the terms of the GNU Library General Public License as published by the
 Free Software Foundation version 2 of the License, or any later version.
 
 This library is distributed in the hope that it will be useful, but
 WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public License
 for more details.
 
 You should have received a copy of the GNU Library General Public License
 along with this library; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 
 Grame Research Laboratory, 9, rue du Garet 69001 Lyon - France
 grame@grame.fr
 
 */

#ifndef __TRational__
#define __TRational__

#include <string>
#include "exports.h"

using namespace std;

/*!
 \brief	Rational number representation.
 */

namespace IMUSANT
{
    
    class TRational {
        
    private:
        
        long fNumerator;
        long fDenominator;
        
        /// Used by rationalise()
        long int gcd(long a, long b);
        
    public:
        
        TRational(long num = 0, long denom = 1);
        TRational(const TRational& d);
        TRational(const string &str);
        
        long getNumerator()	const		{ return fNumerator; }
        long getDenominator() const		{ return fDenominator; }
        void setNumerator(long d)		{ fNumerator = d; }
        void setDenominator(long d) 	{ fDenominator = d; }
        void set(long int n, long d)  { fNumerator = n; fDenominator = d; }
        
        TRational operator +(const TRational &dur) const;
        TRational operator -(const TRational &dur) const;
        //! Useful for notes with dots.
        TRational operator *(const TRational &dur) const;
        TRational operator /(const TRational &dur) const;
        // (i.e. dur * 3/2 or dur * 7/4)
        
        TRational operator *(long num) const;
        TRational operator /(long num) const;
        
        TRational& operator +=(const TRational &dur);
        TRational& operator -=(const TRational &dur);
        //! Useful for notes with dots.
        TRational& operator *=(const TRational &dur);
        TRational& operator /=(const TRational &dur);
        // (i.e. dur * 3/2 or dur * 7/4)
        
        TRational& operator *=(long num) { fNumerator *= num; return *this; }
        TRational& operator /=(long num) { fDenominator *= num; return *this; }
        
        TRational& operator =(const TRational& dur);
        
        bool operator >(const TRational &dur) const;
        bool operator >=(const TRational &dur) const 	{return !(*this < dur);}
        bool operator <(const TRational &dur) const;
        bool operator <=(const TRational &dur) const 	{return !(*this > dur);}
        
        bool operator ==(const TRational &dur) const;
        bool operator !=(const TRational &dur) const	{return !(*this == dur);}
        
        bool operator >	(double num) const;
        bool operator >=(double num) const;
        bool operator <	(double num) const;
        bool operator <=(double num) const;
        bool operator ==(double) const;
        
        // Used to "rationalise" TRational.
        void rationalise();
        
        operator string () const;
        operator double () const;
        operator float () const;
        operator int () const;
        
        //virtual string toString() const;  Why ?? SL
        string toString() const;
        double	toDouble() const;
        float	toFloat() const;
        int		toInt() const;
    };
}

#endif
