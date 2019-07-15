//
//  CATSMAT_sonority_sequences.h
//  imusant
//
//  Created by Jason Stoessel on 29/06/2015.
//
//

#ifndef CATSMAT_quality_sequences__
#define CATSMAT_quality_sequences__

#include <stdio.h>

#include "CATSMAT_sequences_base.h"
#include "suffixtree.h"

using namespace ns_suffixtree;

namespace CATSMAT
{
    class sonority
    {
    public:
        
        sonority(int q = 0, int m = 0, int i = 0, float d = 0.0) : mQuality(q), mMeasure(m), mIndex(i), mDuration(d) {}
        sonority(const sonority& iv) : mQuality(iv.getQuality()), mMeasure(iv.getMeasure()), mIndex(iv.getIndex()), mDuration (iv.getDuration()) {}
        
        int     getQuality() const { return mQuality; }
        int     getMeasure() const { return mMeasure; }
        int     getIndex() const  { return mIndex; }
        float   getDuration() const { return mDuration; }
        
        void    setQuality(const int q) { mQuality = q; }
        void    setLocation(const int m, int i) { mMeasure = m; mIndex = i; }
        void    setDuration(const float d) { mDuration = d; }
        
        friend  ostream& operator<< (ostream& os, const sonority& elt );
        void        print(ostream& os) const;
        
        
        inline bool operator==(const sonority& r) const { return (compare(r)==0);}
        inline bool operator!=(const sonority& r) const { return !(*this==r); }
        inline bool operator<(const sonority& r) const { return (compare(r)<0); }
        inline bool operator>=( const sonority& r) const { return (compare(r)>=0); }
        inline bool operator>(const sonority& r) const { return (compare(r)>0); }
        inline bool operator<=( const sonority& r)  const { return (compare(r)<=0); }
        
        sonority& operator=(const sonority& r);
    private:
        
        signed int  compare(const sonority& i) const;
        
        int mQuality;
        int mMeasure, mIndex;
        float mDuration;
    };

    class CATSMAT_sonority_sequences : public CATSMAT_sequences_base<sonority>
    {
    public:
        typedef suffixtree< vector<sonority> > int_tree;
        
        CATSMAT_sonority_sequences(bool ignoreRepeatedDyads=true) : CATSMAT_sequences_base<sonority>() {}
        
        friend  ostream& operator<<(ostream& os, const CATSMAT_sonority_sequences& sequences);
        
        void Visit(const CATSMAT_cp_matrix& matrix);
        
        void Print(ostream& os) const;
        
        void find_repeated(int min);
    
    private:
        void find_repeated_substrings(vector< pair<int_tree::size_type, int_tree::size_type> >& results, const int_tree::node& n, int min_length);
    };
    
} //namespace
#endif /* defined(__imusant__CATSMAT_quality_sequences__) */
