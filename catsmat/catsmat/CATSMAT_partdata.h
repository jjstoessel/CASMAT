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
#include "IMUSANT_pitch.h"
#include "IMUSANT_duration.h"
#include "IMUSANT_interval.h"
#include "IMUSANT_part.h"
#include "IMUSANT_contour_symbol.h"
#include "smartpointer.h"

using namespace IMUSANT;
using namespace std;

namespace CATSMAT {
    
    class CATSMAT_partdata : public smartable
    {
    public:
        friend  VEXP IMUSANT_SMARTP<CATSMAT_partdata> new_CATSMAT_object<CATSMAT_partdata>();
        
        void    findBasicDataFromPart(S_IMUSANT_part part);
        void    print(ostream& os);
        void    print_interval_profile(ostream& os);
        void    print_duration_profile(ostream& os);
        void    print_pitch_profile(ostream& os);
        int     getNoteCount() { return fNoteCount; }
        int     getRestCount() { return fRestCount; }
        const map<IMUSANT_pitch,int>& getPitchProfile() { return fPitchProfile; }
        const map<IMUSANT_duration,int>& getDurationProfile() { return fDurationProfile; }
        const map<IMUSANT_interval,int>& getHIntervalProfile() { return fHIntervalProfile; }
        const map<IMUSANT_contour_symbol,int>& getContourSymbolProfile() { return fContourSymbolProfile; }
        const map<std::pair<IMUSANT_contour_symbol,IMUSANT_contour_symbol>, int>& getContourSymbolDupleProfile() { return fContourSymbolDupleProfile; }
    protected:
        CATSMAT_partdata();
        ~CATSMAT_partdata() {}
        
    private:
        int fNoteCount = 0;
        int fRestCount = 0;
        S_IMUSANT_pitch             fLastPitch;
        //S_IMUSANT_note              fPreviousNote = NULL;
        S_IMUSANT_contour_symbol    fLastContour = nullptr;
        map<IMUSANT_pitch,int>      fPitchProfile;
        map<IMUSANT_duration,int>   fDurationProfile;
        map<IMUSANT_interval, int>  fHIntervalProfile; //horizontal interval profile
        map<IMUSANT_contour_symbol, int> fContourSymbolProfile;
        map<std::pair<IMUSANT_contour_symbol, IMUSANT_contour_symbol>, int > fContourSymbolDupleProfile;
    };
    
    typedef IMUSANT_SMARTP<CATSMAT_partdata> S_CATSMAT_partdata;
    
}
#endif /* defined(__catsmat__CATSMAT_partdata__) */
