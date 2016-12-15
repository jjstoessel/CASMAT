//
//  CATSMAT_scoredata.cpp
//  catsmat
//
//  Created by Jason Stoessel on 22/09/2016.
//
//

#include "CATSMAT_scoredata.h"
#include <numeric>

namespace CATSMAT {
    
    template
    void
    CATSMAT_scoredata::PrintTable<IMUSANT_pitch>(ostream& os, const vector<tuple<string,IMUSANT_pitch,int> >& table, const map<IMUSANT_pitch,int>& profile, string& type);

    
    void
    CATSMAT_scoredata::
    findBasicDataFromScore(S_IMUSANT_score score)
    {
        //Collect basic metadata for score
        fWorkTitle = score->getWorkTitle();
        fWorkNum = score->getWorkNum();
        fMovementTitle = score->getMovementTitle();
        fMovementNum = score->getMovementNum();
        fCreator = score->getCreator();
        fRights = score->getRights();
        fScoreComments = score->getComments();
        fSource = score->getSource();
        fEditor = score->getEditor();
        fDate = score->getDate();
        
        //cycle through each part collecting data about music notation
        for (auto part : score->partlist()->parts())
        {
            fPartsData[part->getID()] = new_CATSMAT_object<CATSMAT_partdata>();
            fPartsData[part->getID()]->findBasicDataFromPart(part);
        }
        
        PostProcess();
    }
    
    /*
    void
    CATSMAT_scoredata::
    PostProcess()
    {
        //cycle through parts gathering cumulative data
        for (auto data : fPartsData )
        {
            //accumulate note/rest counts
            fTotalNoteCount += data.second->getNoteCount();
            fTotalRestCount += data.second->getRestCount();
            
            //accumulate pitch data maps - check that accumulate is non-destructive
            //templatise this function
            map<IMUSANT_pitch,int> pp = data.second->getPitchProfile();
            
            fPitchProfile = std::accumulate(pp.begin(),pp.end(),fPitchProfile,
                                            [](std::map<IMUSANT_pitch,int> &m, const std::pair<const IMUSANT_pitch, int> p)
                                            {
                                                return (m[p.first] +=p.second, m);
                                            });
            //tabulate pitch occurrence for each part
            for (auto p : pp)
            {
                fPitchTable.push_back(std::make_tuple(data.first,p.first,p.second));
            }
            
            //accumulate interval data maps - check
            map<IMUSANT_interval, int> ip = data.second->getHIntervalProfile();
            
            fIntervalProfile = std::accumulate(ip.begin(), ip.end(), fIntervalProfile,
                                               [](std::map<IMUSANT_interval,int> &m, const std::pair<const IMUSANT_interval,int> p)
                                               {
                                                   return (m[p.first] +=p.second, m);
                                               });
            
            //tabulate interval occurrence for each part
            for (auto i : ip)
            {
                fIntervalTable.push_back(std::make_tuple(data.first,i.first,i.second));
            }
            
            //accumulate duration data maps - check
            map<IMUSANT_duration, int> dp = data.second->getDurationProfile();
            
            fDurationProfile = std::accumulate(dp.begin(), dp.end(), fDurationProfile,
                                               [](std::map<IMUSANT_duration,int> &m, const std::pair<const IMUSANT_duration, int> p)
                                               {
                                                   return (m[p.first] +=p.second, m);
                                               });
            //tabulate duration occurence for each part
            for (auto d : dp)
            {
                fDurationTable.push_back(std::make_tuple(data.first,d.first,d.second));
            }
        }
        
        //sort tuples in vector [use key of profile and part to output]
        std::sort(fPitchTable.begin(),
                  fPitchTable.end(),
                  [](PITCH_TABLE_TUPLE const &tuple1, PITCH_TABLE_TUPLE const &tuple2)
                  {
                      return get<0>(tuple1) > get<0>(tuple2) && get<1>(tuple1) > get<1>(tuple2);
                  });
        std::sort(fIntervalTable.begin(),
                  fIntervalTable.end(),
                  [](INTERVAL_TABLE_TUPLE const &tuple1, INTERVAL_TABLE_TUPLE const &tuple2)
                  {
                      return get<0>(tuple1) > get<0>(tuple2) && get<1>(tuple1) > get<1>(tuple2);
                  });
        std::sort(fDurationTable.begin(),
                  fDurationTable.end(),
                  [](DURATION_TABLE_TUPLE const &tuple1, DURATION_TABLE_TUPLE const &tuple2)
                  {
                      return get<0>(tuple1) > get<0>(tuple2) && get<1>(tuple1) > get<1>(tuple2);
                  });
        
    }
    */
    
    void
    CATSMAT_scoredata::
    PostProcess()
    {
        //cycle through parts gathering cumulative data
        for (auto data : fPartsData )
        {
            //accumulate note/rest counts
            fTotalNoteCount += data.second->getNoteCount();
            fTotalRestCount += data.second->getRestCount();
            
            fScorePitchProfile.Accumulate(data.first, data.second->getPitchProfile());
            fScoreDurationProfile.Accumulate(data.first, data.second->getDurationProfile());
            fScoreIntervalProfile.Accumulate(data.first, data.second->getHIntervalProfile());
            
        }
        
        fScorePitchProfile.Sort();
        fScoreDurationProfile.Sort();
        fScoreIntervalProfile.Sort();
    }

    
    
    void
    CATSMAT_scoredata::
    findContrapuntalData(CATSMAT_dyad_sequences& dyads)
    {
        
    }
    
    void
    CATSMAT_scoredata::
    print(ostream& os)
    {
        string title = "unknown";
        
        if (!fWorkTitle.empty() ) {
            title = fWorkTitle;
            if (!fMovementTitle.empty())
            {
                title += (": " + fMovementTitle);
            }
        } else if (!fMovementTitle.empty())
        {
            title = fMovementTitle;
        }
        
        os << "General data for " << title << endl;
        
        
        os << fScorePitchProfile;
        os << fScoreDurationProfile;
        os << fScoreIntervalProfile;
        
    }
    
   }
