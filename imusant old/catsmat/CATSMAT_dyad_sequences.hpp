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
#include "CATSMAT_dyad_sequences_base.hpp"
#include "suffixtree.h"

using namespace IMUSANT;
using namespace Loki;
using namespace ns_suffixtree;

namespace CATSMAT
{
    class CATSMAT_dyad_sequences: public CATSMAT_dyad_sequences_base
    {
        
    public:
        typedef suffixtree< vector<IMUSANT_interval> > interval_tree;
        
        CATSMAT_dyad_sequences(bool ignoreRepeatedDyads=true);
        ~CATSMAT_dyad_sequences();
        
        void    Visit(const CATSMAT_cp_matrix& matrix);
        
        void    find_repeated(int min=3);
        void    print(ostream& os) const;
        
    private:
        
        void    process(const list<S_IMUSANT_chord>& matrix);
        void    find_repeated_substrings(vector< pair<interval_tree::size_type, interval_tree::size_type> >& results,
                                         const interval_tree::node& n,
                                         int min_length=2);
        
        vector<S_IMUSANT_interval_vector>   fVIntervalVector;
        long                                fSaveI = 0;
    };
    
} //namespace CATSMAT
#endif /* defined(__imusant__CATSMAT_dyad_sequences__) */
