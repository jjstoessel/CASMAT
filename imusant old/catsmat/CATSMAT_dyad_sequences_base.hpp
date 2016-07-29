//
//  CATSMAT_dyad_sequences_base.h
//  imusant
//
//  Created by Jason Stoessel on 14/06/2015.
//
//

#ifndef __imusant__CATSMAT_dyad_sequences_base__
#define __imusant__CATSMAT_dyad_sequences_base__

#include <stdio.h>
#include "CATSMAT_cp_matrix.hpp"

using namespace IMUSANT;
using namespace Loki;

namespace CATSMAT
{

class CATSMAT_dyad_sequences_base: public BaseVisitor, public Visitor<CATSMAT_cp_matrix, void, true>
{

public:
    friend  ostream& operator<< (ostream& os, const CATSMAT_dyad_sequences_base& elt );
    
    CATSMAT_dyad_sequences_base() {}
    virtual ~CATSMAT_dyad_sequences_base() {}
    
    virtual void    Visit(const CATSMAT_cp_matrix& matrix) = 0;
    
    virtual void    print(ostream& os) const = 0;
    
};


inline ostream& operator<< (ostream& os, const CATSMAT_dyad_sequences_base& elt )
{
    elt.print(os);
    
    return os;
}
    
} //namespace CATSMAT
#endif /* defined(__imusant__CATSMAT_dyad_sequences__) */
