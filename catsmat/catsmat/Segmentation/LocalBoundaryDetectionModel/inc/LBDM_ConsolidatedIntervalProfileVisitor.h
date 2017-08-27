//
//  LBDM_ConsolidatedIntervalProfileVisitor.h
//  catsmat
//
//  Created by Derrick Hill on 10/09/2016.
//
//

#ifndef __LBDM_ConsolidatedIntervalProfileVisitor__
#define __LBDM_ConsolidatedIntervalProfileVisitor__

#include <stdio.h>

namespace CATSMAT
{
    class LBDM_ConsolidatedIntervalProfile;
    
    class LBDM_ConsolidatedIntervalProfileVisitor
    {
    public:
        
        LBDM_ConsolidatedIntervalProfileVisitor() {}
        virtual ~LBDM_ConsolidatedIntervalProfileVisitor() {}
        
        virtual void visit(LBDM_ConsolidatedIntervalProfile *target) = 0;
    };
}

#endif /* defined(__LBDM_ConsolidatedIntervalProfileVisitor__) */
