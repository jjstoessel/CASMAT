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
#include "IMUSANT_generalised_interval.h"

#include "smartpointer.h"

using namespace IMUSANT;

namespace CATSMAT {
    
    class CATSMAT_partdata : public smartable
    {
    public:
        friend  VEXP IMUSANT_SMARTP<CATSMAT_partdata> new_CATSMAT_object<CATSMAT_partdata>();
        
        void    findBasicDataFromPart(S_IMUSANT_part part);
        void    print(std::ostream& os);
        void    print_interval_profile(std::ostream& os);
        void    print_duration_profile(std::ostream& os);
        void    print_pitch_profile(std::ostream& os);
        void    print_interval_pitch_matrix(std::ostream& os);
        int     getNoteCount() { return fNoteCount; }
        int     getRestCount() { return fRestCount; }
        const std::map<IMUSANT_pitch,int>& getPitchProfile() { return fPitchProfile; }
        const std::map<IMUSANT_duration,int>& getDurationProfile() { return fDurationProfile; }
        const std::map<IMUSANT_interval,int>& getHIntervalProfile() { return fHIntervalProfile; }
        const std::map<IMUSANT_contour_symbol,int>& getContourSymbolProfile() { return fContourSymbolProfile; }
        const std::map<std::pair<IMUSANT_contour_symbol,IMUSANT_contour_symbol>, int>& getContourSymbolDupleProfile() { return fContourSymbolDupleProfile; }
        const std::map<int,int>& getGeneralisedIntervalProfile() { return fGeneralisedIntervalProfile; }
        const std::map<std::pair<IMUSANT_pitch,IMUSANT_pitch>,int>& getHIntervalPitchProfile() { return fHIntervalPitchProfile; }
    protected:
        CATSMAT_partdata();
        ~CATSMAT_partdata() {}
        
    private:
        int fNoteCount = 0;
        int fRestCount = 0;
        S_IMUSANT_pitch                  fLastPitch;
        //S_IMUSANT_note              fPreviousNote = NULL;
        IMUSANT_contour_symbol           fLastContour;
        std::map<IMUSANT_pitch,int>      fPitchProfile;
        std::map<IMUSANT_duration,int>   fDurationProfile;
        std::map<IMUSANT_interval, int>  fHIntervalProfile; //horizontal interval profile
        std::map<IMUSANT_contour_symbol, int> fContourSymbolProfile;
        std::map<std::pair<IMUSANT_contour_symbol, IMUSANT_contour_symbol>, int > fContourSymbolDupleProfile;
        std::map<int, int>               fGeneralisedIntervalProfile;
        std::map<pair<IMUSANT_pitch,IMUSANT_pitch>,int> fHIntervalPitchProfile;
    };
    
    typedef IMUSANT_SMARTP<CATSMAT_partdata> S_CATSMAT_partdata;
    
}
#endif /* defined(__catsmat__CATSMAT_partdata__) */
