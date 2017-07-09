//
//  CATSMAT_visitable.h
//  imusant
//
//  Created by Jason Stoessel on 12/06/2015.
//
//

#ifndef __imusant__CATSMAT_visitable__
#define __imusant__CATSMAT_visitable__

#include <stdio.h>
#include "Visitor.h"

using namespace Loki;

namespace CATSMAT
{
    
    class CATSMAT_visitable : public BaseVisitable<>
    {
    public:
        //LOKI_DEFINE_VISITABLE()
    };
    
} //namespace CATSMAT

#endif /* defined(__imusant__CATSMAT_visitable__) */
