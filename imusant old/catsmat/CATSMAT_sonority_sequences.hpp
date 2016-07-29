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

#include "CATSMAT_dyad_sequences_base.hpp"
#include "suffixtree.h"

using namespace ns_suffixtree;

namespace CATSMAT
{
    class sonority
    {
    public:
        
        sonority(int q = 0, int m = 0, int i = 0) : mQuality(q), mMeasure(m), mIndex(i) {}
        sonority(const sonority& iv) : mQuality(iv.getQuality()), mMeasure(iv.getMeasure()), mIndex(iv.getIndex()) {}
        
        int     getQuality() const { return mQuality; }
        long    getMeasure() const { return mMeasure; }
        long    getIndex() const  { return mIndex; }
        
        void    setQuality(const int q) { mQuality = q; }
        void    setLocation(const long m, long i) { mMeasure = m; mIndex = i; }
        
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
        long mMeasure, mIndex;
    };

    class CATSMAT_sonority_sequences : public CATSMAT_dyad_sequences_base
    {
    public:
        typedef suffixtree< vector<sonority> > int_tree;
        
        CATSMAT_sonority_sequences(bool ignoreRepeatedDyads=true) : CATSMAT_dyad_sequences_base() {}
        
        void Visit(const CATSMAT_cp_matrix& matrix);
        
        void print(ostream& os) const;
        
        void find_repeated(int min);
    
    private:
        void find_repeated_substrings(vector< pair<int_tree::size_type, int_tree::size_type> >& results, const int_tree::node& n, int min_length);
        
        std::vector<sonority> fQualityVector;
    };
    
} //namespace
#endif /* defined(__imusant__CATSMAT_quality_sequences__) */
