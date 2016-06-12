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

#include "TRational.h"
#include <sstream>
#include <cmath>

namespace IMUSANT
{
    
    string TRational::toString() const
    {
        ostringstream res;
        res << fNumerator;
        res << "/";
        res << fDenominator;
        return res.str();
    }
    
    TRational::operator string() const
    {
        return toString();
    }
    
    TRational::operator double() const
    {
        return toDouble();
    }
    
    TRational::operator float() const
    {
        return toFloat();
    }
    
    TRational::operator int() const
    {
        const double x = toDouble();
        return ((int)floor(x + 0.5f));
    }
    
    TRational::TRational(const string &str)
    {
        const char *cstr;
        cstr = str.c_str();
        const char *denom;
        denom = strstr(cstr,"/");
        if (denom) ++denom;
        fNumerator = atol(cstr);
        if (denom) fDenominator = atol(denom);
    }
    
    TRational::TRational(long int num, long int denom) : fNumerator(num), fDenominator(denom)
    {
        // don't allow zero denominators!
        //if (fDenominator == 0) fDenominator = 1;
        if (fNumerator !=0 && fDenominator == 0) fDenominator = 1;
    }
    
    TRational::TRational(const TRational& d)
    {
        fNumerator = d.fNumerator;
        fDenominator = d.fDenominator;
    }
    
    TRational TRational::operator +(const TRational &dur) const {
        return TRational(fNumerator * dur.fDenominator + dur.fNumerator * fDenominator, fDenominator * dur.fDenominator);
    }
    
    TRational TRational::operator -(const TRational &dur) const {
        return TRational(fNumerator * dur.fDenominator - dur.fNumerator * fDenominator, fDenominator * dur.fDenominator);
    }
    
    TRational TRational::operator *(const TRational &dur) const {
        return TRational(fNumerator * dur.fNumerator, fDenominator * dur.fDenominator);
    }
    
    TRational TRational::operator /(const TRational &dur) const {
        return TRational(fNumerator * dur.fDenominator, fDenominator * dur.fNumerator);
    }
    
    TRational TRational::operator *(int num) const {
        return TRational(fNumerator * num, fDenominator);
    }
    
    TRational TRational::operator /(int num) const {
        return TRational(fNumerator, fDenominator * num);
    }
    
    TRational& TRational::operator +=(const TRational &dur)
    {
        if(fDenominator == dur.fDenominator) {
            fNumerator += dur.fNumerator;
        } else {
            fNumerator = fNumerator * dur.fDenominator + dur.fNumerator * fDenominator;
            fDenominator *= dur.fDenominator;
        }
        return (*this);
    }
    
    TRational& TRational::operator -=(const TRational &dur)
    {
        if(fDenominator == dur.fDenominator) {
            fNumerator -= dur.fNumerator;
        } else {
            fNumerator = fNumerator * dur.fDenominator - dur.fNumerator * fDenominator;
            fDenominator *= dur.fDenominator;
        }
        return (*this);
    }
    
    TRational& TRational::operator *=(const TRational &dur)
    {
        fNumerator   *= dur.fNumerator;
        fDenominator *= dur.fDenominator;
        return (*this);
    }
    
    TRational& TRational::operator /=(const TRational &dur)
    {
        fNumerator   *= dur.fDenominator;
        fDenominator *= dur.fNumerator;
        return (*this);
    }
    
    TRational& TRational::operator =(const TRational& dur) {
        fNumerator   = dur.fNumerator;
        fDenominator = dur.fDenominator;
        return (*this);
    }
    
    bool TRational::operator >(const TRational &dur) const
    {
        // a/b > c/d if and only if a * d > b * c.
        return ((fNumerator * dur.fDenominator) > (fDenominator * dur.fNumerator));
    }
    
    bool TRational::operator <(const TRational &dur) const
    {
        // a/b < c/d if and only if a * d < b * c.
        return ((fNumerator * dur.fDenominator) < (fDenominator * dur.fNumerator));
    }
    
    bool TRational::operator ==(const TRational &dur) const
    {
        // a/b < c/d if and only if a * d < b * c.
        return ((fNumerator * dur.fDenominator) == (fDenominator * dur.fNumerator));
    }
    
    bool TRational::operator >(double num) const
    {
        return (toDouble() > num);
    }
    
    bool TRational::operator >= (double num) const
    {
        return (toDouble() >= num);
    }
    
    bool TRational::operator <(double num) const
    {
        return (toDouble() < num);
    }
    
    bool TRational::operator <=(double num) const
    {
        return (toDouble() <= num);
    }
    
    bool TRational::operator ==(double num) const
    {
        return (toDouble() == num);
    }
    
    // gcd(a, b) calculates the gcd of a and b using Euclid's algorithm.
    long int TRational::gcd(long int a1, long int b1)
    {
        long int r;
        
        long int a = abs(a1);
        long int b = abs(b1);
        
        if (!(a == 0) || (b == 0)){
            while (b > 0){
                r = a % b;
                a = b;
                b = r;
            }
            return a;
        }
        return 1;
    }
    
    void TRational::rationalise()
    {
        long int g = gcd(fNumerator, fDenominator);
        fNumerator /= g;
        fDenominator /= g;
        if (fNumerator == 0) fDenominator = 1;
    }
    
    double TRational::toDouble() const
    {
        return (fDenominator != 0) ? ((double)fNumerator/(double)fDenominator) : 0;
    }
    
    float TRational::toFloat() const
    {
        return (fDenominator != 0) ? ((float)fNumerator/(float)fDenominator) : 0;
    }
}
