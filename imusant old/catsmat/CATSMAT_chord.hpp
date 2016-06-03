//
//  CATSMAT_sonority.h
//  imusant
//
//  Created by Jason Stoessel on 30/05/2016.
//
//

#ifndef __imusant__CATSMAT_sonority__
#define __imusant__CATSMAT_sonority__

#include <stdio.h>
#include <map>
#include "IMUSANT_note.h"
#include "smartpointer.h"

#endif /* defined(__imusant__CATSMAT_sonority__) */

using namespace IMUSANT;

namespace CATSMAT {
    
    class CATSMAT_chord : public smartable, public map<int, S_IMUSANT_note>
    {
    public:
        friend SMARTP<CATSMAT_chord> new_CATSMAT_sonority();
        
        void	print(ostream& os) const;
        void    print_short(ostream& os) const;
        
        void	sort();
    };
    
    typedef SMARTP<CATSMAT_chord> S_CATSMAT_chord;
    
    S_CATSMAT_chord new_CATSMAT_chord();
}