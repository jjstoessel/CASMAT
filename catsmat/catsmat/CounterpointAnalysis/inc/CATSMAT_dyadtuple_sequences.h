//
//  CATSMAT_dyadtuple_sequences.h
//  imusant
//
//  Created by Jason Stoessel on 14/06/2015.
//
//

#ifndef __imusant__CATSMAT_dyadtuple_sequences__
#define __imusant__CATSMAT_dyadtuple_sequences__

#include <stdio.h>
#include "CATSMAT_dyad_sequences_base.h"
#include "boost/tuple/tuple.hpp"

namespace CATSMAT
{
    
    //typedef boost::tuple<int,int,int,int>   quadruple_int;
    
    class  quadruple_int : public boost::tuples::tuple<int,int,int,int>
    {
    public:
        quadruple_int() : boost::tuples::tuple<int,int,int,int>() {}
        quadruple_int(int a,int b,int c,int d) : boost::tuples::tuple<int,int,int,int>(a,b,c,d) {}
        bool operator <(const quadruple_int &right) const { return (*this<right); }
        bool operator !=(const quadruple_int &right) const { return (*this!=right); }
    };
    typedef vector<quadruple_int>           quadruple_int_vector;
    
    class CATSMAT_dyadtuple_sequences : public CATSMAT_dyad_sequences_base<quadruple_int_vector>
    {
    public:
        
        friend  ostream& operator<<(ostream& os, const CATSMAT_dyadtuple_sequences& sequences);
        
        CATSMAT_dyadtuple_sequences(bool ignoreRepeatedDyads=true) : CATSMAT_dyad_sequences_base() {}
        
        void Visit(const CATSMAT_cp_matrix& matrix);
        
        void Print(ostream& os) const;
        
        void find_repeated_tuplet_sequences(int min);
        
    protected:
        
    private:
        
        long                                fSaveI = 0;
    };
    
}//namespace CATSMAT

#endif /* defined(__imusant__CATSMAT_dyadtuple_sequences__) */
