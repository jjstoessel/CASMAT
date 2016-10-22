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
            map<IMUSANT_pitch,int> pp = data.second->getPitchProfile();
            
//            fPitchProfile = std::accumulate(pp.begin(),pp.end(),fPitchProfile,
//                                            [](std::map<IMUSANT_pitch,int> &m, const std::pair<const IMUSANT_pitch, int> p)
//                                            {
//                                                return (m[p.first] +=p.second, m);
//                                            });
            
            //same for map<IMUSANT_duration,int>       fDurationProfile;
            //same for map<IMUSANT_interval, int>      fIntervalProfile;
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
        
    }
}