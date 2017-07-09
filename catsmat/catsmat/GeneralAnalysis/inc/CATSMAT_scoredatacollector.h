//
//  CATSMAT_scoredatacollector.h
//  catsmat
//
//  Created by Jason Stoessel on 22/09/2016.
//
//

#ifndef __catsmat__CATSMAT_scoredatacollector__
#define __catsmat__CATSMAT_scoredatacollector__

#include <stdio.h>
#include "Visitor.h"
#include "CATSMAT_processing.h"
#include "CATSMAT_scoredata.h"

namespace CATSMAT {
    
    class CATSMAT_scoredatacollector :
    public Loki::BaseVisitor,
    public Loki::Visitor<CATSMAT_processing, void, true>
    {
    public:
        friend ostream& operator<< (ostream& os, const CATSMAT_scoredatacollector& elt );
        
        CATSMAT_scoredatacollector() {}
        ~CATSMAT_scoredatacollector() {}
        
        void Visit(const CATSMAT_processing& processor);
        
        void print(ostream& os) const;
        
    private:
        
        vector<S_CATSMAT_scoredata>    scoresdata;
    };
}

#endif /* defined(__catsmat__CATSMAT_scoredatacollector__) */
