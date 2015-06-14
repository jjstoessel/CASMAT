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
#include "CATSMAT_dyad_sequences_base.hpp"
#include "boost/tuple/tuple.hpp"

namespace CATSMAT
{

class CATSMAT_dyadtuple_sequences : public CATSMAT_dyad_sequences_base
{
public:
    CATSMAT_dyadtuple_sequences(bool ignoreRepeatedDyads=true) : CATSMAT_dyad_sequences_base(ignoreRepeatedDyads) {}
    
    void Visit(const CATSMAT_cp_matrix& matrix);
    
    void print(ostream& os) const;
    
protected:
    
private:
    
    vector <vector< boost::tuple<int,int,int,int> > > fTupleVector;
    vector<vector<int> >                fSimpleVIntervalVector;
    long                                fSaveI = 0;
};

}//namespace CATSMAT

#endif /* defined(__imusant__CATSMAT_dyadtuple_sequences__) */
