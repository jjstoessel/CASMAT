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
   
//    VEXP
//    IMUSANT_SMARTP<CATSMAT_scoredata>
//    new_CATSMAT_scoredata()
//    {
//        IMUSANT_score* o = new CATSMAT_scoredata();
//        if (o==0) throw catsmat_runtime_error("Unable to allocate CATSMAT_scoredata");
//        return o;
//    }

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
                                                }
                                            );
            
            //accumulate interval data maps - check
            map<IMUSANT_interval, int> ip = data.second->getHIntervalProfile();
            
            fIntervalProfile = std::accumulate(ip.begin(), ip.end(), fIntervalProfile,
                                               [](std::map<IMUSANT_interval,int> &m, const std::pair<const IMUSANT_interval,int> p){ return (m[p.first] +=p.second, m); }
                                               );
            
            //accumulate duration data maps - check
            map<IMUSANT_duration, int> dp = data.second->getDurationProfile();
            
            fDurationProfile = std::accumulate(dp.begin(), dp.end(), fDurationProfile,
                                               [](std::map<IMUSANT_duration,int> &m, const std::pair<const IMUSANT_duration, int> p)
                                               {
                                                   return (m[p.first] +=p.second, m);
                                               }
                                               );
        }
        
        
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
        os << "General data for " << fWorkTitle << " " << fMovementTitle << std::endl;
        
        for (auto data : fPartsData )
        {
            os << "Part: " << data.first << std::endl;
            data.second->print(os);
        }
    }
}