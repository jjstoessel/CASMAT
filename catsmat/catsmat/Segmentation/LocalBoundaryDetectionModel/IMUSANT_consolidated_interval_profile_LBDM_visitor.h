//
//  IMUSANT_consolidated_interval_profile_LBDM_visitor.h
//  catsmat
//
//  Created by Derrick Hill on 10/09/2016.
//
//

#ifndef __catsmat__IMUSANT_consolidated_interval_profile_LBDM_visitor__
#define __catsmat__IMUSANT_consolidated_interval_profile_LBDM_visitor__

#include <stdio.h>

namespace CATSMAT
{
    class IMUSANT_consolidated_interval_profile_LBDM;
    
    class IMUSANT_consolidated_interval_profile_LBDM_visitor
    {
    public:
        
        IMUSANT_consolidated_interval_profile_LBDM_visitor() {}
        virtual ~IMUSANT_consolidated_interval_profile_LBDM_visitor() {}
        
        virtual void visit(IMUSANT_consolidated_interval_profile_LBDM *target) = 0;
    };
}

#endif /* defined(__catsmat__IMUSANT_consolidated_interval_profile_LBDM_visitor__) */
