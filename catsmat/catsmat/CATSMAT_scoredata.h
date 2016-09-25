//
//  CATSMAT_scoredata.h
//  catsmat
//
//  Created by Jason Stoessel on 22/09/2016.
//
//  A class for holding and returning basic data from a score, eg. number of parts, number of notes, melodic intervals
//

#ifndef __catsmat__CATSMAT_scoredata__
#define __catsmat__CATSMAT_scoredata__

#include <stdio.h>
#include <map>
#include "IMUSANT_score.h"
#include "IMUSANT_interval.h"
#include "IMUSANT_common.h"
#include "CATSMAT_dyad_sequences.hpp"
#include "CATSMAT_t_utilities.h"

using namespace IMUSANT;

namespace CATSMAT {

    class CATSMAT_scoredata
    {
    public:
        //friend  VEXP IMUSANT_SMARTP<CATSMAT_scoredata> new_CATSMAT_scoredata();
        friend  VEXP IMUSANT_SMARTP<CATSMAT_scoredata> new_CATSMAT_object<CATSMAT_scoredata>();
        
        void findBasicDataFromScore(S_IMUSANT_score scores);
        void findCountrapuntalData(CATSMAT_dyad_sequences& dyads);
        
    protected:
        
        CATSMAT_scoredata() {}
        ~CATSMAT_scoredata() {}
        
    private:
        
        string	fWorkTitle;
        string  fWorkNum;
        string  fMovementTitle;
        string  fMovementNum;
        STRPAIRVECTOR   fCreator;
        STRPAIRVECTOR   fRights;
        string  fScoreComments;
        string  fSource;
        string  fEditor;
        string  fDate;
        
        map<IMUSANT_interval, int>  fMelodicIntervalCount;
        //map<string,int>             fNotesPerPart;
        int                         fTotalNoteCount = 0;
    };
    
    typedef IMUSANT_SMARTP<CATSMAT_scoredata> S_CATSMAT_scoredata;
}

#endif /* defined(__catsmat__CATSMAT_scoredata__) */
