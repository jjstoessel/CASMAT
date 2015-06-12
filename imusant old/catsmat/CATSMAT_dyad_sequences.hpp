//
//  CATSMAT_dyad_sequences.h
//  imusant
//
//  Created by Jason Stoessel on 12/06/2015.
//
//

#ifndef __imusant__CATSMAT_dyad_sequences__
#define __imusant__CATSMAT_dyad_sequences__

#include <stdio.h>
#include "CATSMAT_cp_matrix.hpp"
#include "IMUSANT_interval_vector.h"

using namespace IMUSANT;
using namespace Loki;

namespace CATSMAT
{

class CATSMAT_dyad_sequences: public BaseVisitor, public Visitor<CATSMAT_cp_matrix, void, true>
{

public:
    friend  ostream& operator<< (ostream& os, const CATSMAT_dyad_sequences& elt );
    
    CATSMAT_dyad_sequences(bool ignoreRepeatedDyads=true);
    ~CATSMAT_dyad_sequences();
    
    void    Visit(const CATSMAT_cp_matrix& matrix);
    
    void    print(ostream& os) const;
    
private:
    
    void    process(const list<S_IMUSANT_chord>& matrix);
    
    vector<S_IMUSANT_interval_vector>   fVIntervalVector;
    vector< vector<int> >               fTaneievIntervalVectors;
    long                                fSaveI = 0;
};

} //namespace CATSMAT
#endif /* defined(__imusant__CATSMAT_dyad_sequences__) */
