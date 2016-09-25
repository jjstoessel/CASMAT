//
//  CATSMAT_partdata.h
//  catsmat
//
//  Created by Jason Stoessel on 25/09/2016.
//
//

#ifndef __catsmat__CATSMAT_partdata__
#define __catsmat__CATSMAT_partdata__

#include <stdio.h>
#include "CATSMAT_t_utilities.h"

namespace CATSMAT {
    
    class CATSMAT_partdata
    {
    public:
        friend VEXP IMUSANT_SMARTP<CATSMAT_partdata> new_CATSMAT_object<CATSMAT_partdata>();
        
    protected:
        CATSMAT_partdata() {}
        ~CATSMAT_partdata() {}
        
    private:
        int fNoteCount;
        map<IMUSANT_interval, int>  fMelodicIntervalCount;
    };
}
#endif /* defined(__catsmat__CATSMAT_partdata__) */
