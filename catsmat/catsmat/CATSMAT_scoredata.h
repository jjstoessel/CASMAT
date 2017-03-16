/**
    \class      CATSMAT_scoredata
    \file       CATSMAT_scoredata.h
    \namespace  catsmat
    \date       Created by Jason Stoessel on 15/12/16.
    \author     Jason Stoessel
    \copyright  [add licence name]
    \brief      A class for holding and returning basic data from a score, eg. number of parts, number of notes, melodic intervals
*/

#ifndef __catsmat__CATSMAT_scoredata__
#define __catsmat__CATSMAT_scoredata__

#include <stdio.h>
#include <map>
#include <tuple>
//#include "boost/tuple/tuple.hpp"

#include "IMUSANT_score.h"
#include "IMUSANT_generalised_interval.h"
#include "IMUSANT_common.h"
#include "CATSMAT_dyad_sequences.hpp"
#include "CATSMAT_t_utilities.h"
#include "CATSMAT_partdata.h"
#include "CATSMAT_score_profile.hpp"
#include "IMUSANT_contour_symbol.h"

using namespace IMUSANT;
using namespace std;

namespace CATSMAT {

    class CATSMAT_scoredata : public smartable
    {
    public:
        
        friend  VEXP IMUSANT_SMARTP<CATSMAT_scoredata> new_CATSMAT_object<CATSMAT_scoredata>();
        
        void    findBasicDataFromScore(S_IMUSANT_score scores);
        void    findContrapuntalData(CATSMAT_dyad_sequences& dyads);
        
        CATSMAT_score_profile<IMUSANT_pitch>&   score_pitch_profile(){ return fScorePitchProfile; }
        CATSMAT_score_profile<IMUSANT_duration> score_duration_profile(){ return fScoreDurationProfile; }
        CATSMAT_score_profile<IMUSANT_interval> score_interval_profile(){ return fScoreIntervalProfile; }
        CATSMAT_score_profile<IMUSANT_generalised_interval> score_generalised_interval_profile(){ return fScoreGeneralisedIntervalProfile; }
        CATSMAT_score_profile<IMUSANT_contour_symbol>& score_contour_symbol_profile(){ return  fScoreContourSymbolProfile; }
        CATSMAT_score_profile<std::pair<IMUSANT_contour_symbol, IMUSANT_contour_symbol> >& score_contour_symbol_duple_profile() { return fContourSymbolDupleProfile; }
        
        void    print(ostream& os);
        
    protected:
        
        CATSMAT_scoredata();
        ~CATSMAT_scoredata() {}
        
        
    private:
        
        void    findBasicDataFromPart(S_IMUSANT_part part);
        void    PostProcess();
        template <typename T> void PrintTable(ostream& os, const vector<tuple<string,T,int> >& table, const map<T,int>& profile, string& type);
        
        string          fWorkTitle;
        string          fWorkNum;
        string          fMovementTitle;
        string          fMovementNum;
        STRPAIRVECTOR   fCreator;
        STRPAIRVECTOR   fRights;
        string          fScoreComments;
        string          fSource;
        string          fEditor;
        string          fDate;
        
        map<string,S_CATSMAT_partdata>  fPartsData;
        int                             fTotalNoteCount = 0;
        int                             fTotalRestCount = 0;
        CATSMAT_score_profile<IMUSANT_pitch>    fScorePitchProfile;
        CATSMAT_score_profile<IMUSANT_duration> fScoreDurationProfile;
        CATSMAT_score_profile<IMUSANT_interval> fScoreIntervalProfile;
        CATSMAT_score_profile<IMUSANT_generalised_interval> fScoreGeneralisedIntervalProfile;
        CATSMAT_score_profile<IMUSANT_contour_symbol>   fScoreContourSymbolProfile;
        CATSMAT_score_profile<std::pair<IMUSANT_contour_symbol, IMUSANT_contour_symbol> > fContourSymbolDupleProfile;
        
    };
    
    typedef IMUSANT_SMARTP<CATSMAT_scoredata> S_CATSMAT_scoredata;
    
}

#endif /* defined(__catsmat__CATSMAT_scoredata__) */
