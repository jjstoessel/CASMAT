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
        friend  VEXP IMUSANT_SMARTP<CATSMAT_partdata> new_CATSMAT_object<CATSMAT_partdata>();
        
        void    findBasicDataFromPart(S_IMUSANT_part part);
        void    print(ostream& os);
        
        int     getNoteCount() { return fNoteCount; }
        int     getRestCount() { return fRestCount; }
        const map<IMUSANT_pitch,int>& getPitchProfile() { return fPitchProfile; }
        
    protected:
        CATSMAT_partdata() {}
        ~CATSMAT_partdata() {}
        
    private:
        int fNoteCount = 0;
        int fRestCount = 0;
        map<IMUSANT_pitch,int>      fPitchProfile;
        map<IMUSANT_duration,int>   fDurationProfile;
        map<IMUSANT_interval, int>  fIntervalProfile;
    };
    
    typedef IMUSANT_SMARTP<CATSMAT_partdata> S_CATSMAT_partdata;
    
}
#endif /* defined(__catsmat__CATSMAT_partdata__) */
