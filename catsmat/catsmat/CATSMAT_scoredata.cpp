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
            
            fScorePitchProfile.Accumulate(data.first, data.second->getPitchProfile());
            fScoreDurationProfile.Accumulate(data.first, data.second->getDurationProfile());
            fScoreIntervalProfile.Accumulate(data.first, data.second->getHIntervalProfile());
            map<IMUSANT_generalised_interval,int> temp_map;
            for ( auto i : data.second->getHIntervalProfile())
            {
                temp_map[i.first] = i.second;
            }
            fScoreGeneralisedIntervalProfile.Accumulate(data.first, temp_map);
            
        }
        
        fScorePitchProfile.Sort();
        fScoreDurationProfile.Sort();
        fScoreIntervalProfile.Sort();
        fScoreGeneralisedIntervalProfile.Sort();
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
        //os << fScoreGeneralisedIntervalProfile;
        os << endl;
        
    }
    
   }
