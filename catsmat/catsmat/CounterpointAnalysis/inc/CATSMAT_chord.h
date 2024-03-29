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
using namespace std;

namespace CATSMAT {
    
    class CATSMAT_chord : public smartable, public map<int, S_IMUSANT_note>
    {
    public:
        friend IMUSANT_SMARTP<CATSMAT_chord> new_CATSMAT_sonority();
        
        void	print(ostream& os) const;
        void    print_short(ostream& os) const;
        
        CATSMAT_chord& operator=(const CATSMAT_chord& rhs);
        
    };
    
    typedef IMUSANT_SMARTP<CATSMAT_chord> S_CATSMAT_chord;
    
    S_CATSMAT_chord new_CATSMAT_chord();
}
