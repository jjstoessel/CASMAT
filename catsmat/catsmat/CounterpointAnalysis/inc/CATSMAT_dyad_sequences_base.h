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
#include "CATSMAT_cp_matrix.h"

using namespace IMUSANT;
using namespace Loki;

namespace CATSMAT
{

template <typename T> //T is a vector
class CATSMAT_dyad_sequences_base : public BaseVisitor, public Loki::Visitor<CATSMAT_cp_matrix, void, true>
{
public:

    friend  ostream& operator<< (ostream& os, const CATSMAT_dyad_sequences_base& elt );
    
                    CATSMAT_dyad_sequences_base() {}
    virtual         ~CATSMAT_dyad_sequences_base() {}
    
    virtual void    Visit(const CATSMAT_cp_matrix& matrix) = 0;
    virtual void    Print(ostream& os) const = 0;

    void            set_ignore_repeated(bool ignore) { ignore_repeated_ = ignore; }
    void            set_ignore_dissonances(bool ignore) { ignore_dissonances_ = ignore; }
protected:
    vector<T>           vectors_;
    S_CATSMAT_cp_matrix matrix_ = NULL;
    bool                ignore_repeated_ = true;
    bool                ignore_dissonances_ = true;
};


template <typename T> inline ostream& operator<< (ostream& os, const CATSMAT_dyad_sequences_base<T>& elt )
{
    elt.Print(os);
    
    return os;
}
    
} //namespace CATSMAT
#endif /* defined(__imusant__CATSMAT_dyad_sequences__) */
