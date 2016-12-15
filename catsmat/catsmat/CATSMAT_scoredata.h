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
#include <tuple>
//#include "boost/tuple/tuple.hpp"

#include "IMUSANT_score.h"
#include "IMUSANT_interval.h"
#include "IMUSANT_common.h"
#include "CATSMAT_dyad_sequences.hpp"
#include "CATSMAT_t_utilities.h"
#include "CATSMAT_partdata.h"
#include "CATSMAT_score_profile.hpp"

using namespace IMUSANT;
using namespace std;

namespace CATSMAT {

    class CATSMAT_scoredata : public smartable
    {
    public:
        typedef tuple<string,IMUSANT_pitch,int>     PITCH_TABLE_TUPLE;
        typedef tuple<string,IMUSANT_interval,int>  INTERVAL_TABLE_TUPLE;
        typedef tuple<string,IMUSANT_duration,int>  DURATION_TABLE_TUPLE;
        
        friend  VEXP IMUSANT_SMARTP<CATSMAT_scoredata> new_CATSMAT_object<CATSMAT_scoredata>();
        
        void    findBasicDataFromScore(S_IMUSANT_score scores);
        void    findContrapuntalData(CATSMAT_dyad_sequences& dyads);
        
        void    print(ostream& os);
        
    protected:
        
        CATSMAT_scoredata() : fScorePitchProfile("Pitch"), fScoreDurationProfile("Duration"), fScoreIntervalProfile("Interval"){}
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
        vector<PITCH_TABLE_TUPLE>       fPitchTable;    //a sparse "table" of pitches ordered by voices
        vector<INTERVAL_TABLE_TUPLE>    fIntervalTable; //a sparse "table" of intervals ordered by voices
        vector<DURATION_TABLE_TUPLE>    fDurationTable; //a sparde "table" of durations ordered by voices
        int                             fTotalNoteCount = 0;
        int                             fTotalRestCount = 0;
        map<IMUSANT_pitch,int>          fPitchProfile;
        map<IMUSANT_duration,int>       fDurationProfile;
        map<IMUSANT_interval, int>      fIntervalProfile;
        CATSMAT_score_profile<IMUSANT_pitch>    fScorePitchProfile;
        CATSMAT_score_profile<IMUSANT_duration> fScoreDurationProfile;
        CATSMAT_score_profile<IMUSANT_interval> fScoreIntervalProfile;
        
    };
    
    typedef IMUSANT_SMARTP<CATSMAT_scoredata> S_CATSMAT_scoredata;
    
    
    template <typename T>
    void
    CATSMAT_scoredata::PrintTable(ostream& os, const vector<tuple<string,T,int> >& table, const map<T,int>& profile, string& type)
    {
        ostringstream header;
        ostringstream lines;
        header << "Pitch" << "\t";
        
        for (auto data : profile)
        {
            //add pitch name to header
            header << data.first << "\t";
        }
        
        for (auto part : fPartsData)
        {
            ostringstream line;
            string s = part.first; //part label
            line << s.c_str() << "\t";
            
            for (auto data : profile)
            {
                T t = data.first; //pitch type
                //search table for occurrences of pitch in part
                auto it = std::find_if(table.begin(), table.end(), [&s,&t](const tuple<string,T,int>& item)
                                       {
                                           return s == get<0>(item) && t == get<1>(item);
                                       }); //returns iterator
                if (it!=table.end())
                    line << get<2>(*it) << "\t";
                else //not found
                    line << "0" << "\t";
                
            }
            
            lines << line.str() << endl;
        }
        
        header << endl;
        
        os << header.str();
        os << lines.str();
        
    }

}

#endif /* defined(__catsmat__CATSMAT_scoredata__) */
