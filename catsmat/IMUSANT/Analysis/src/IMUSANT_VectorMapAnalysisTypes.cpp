//
//  IMUSANT_VectorMapAnalysisTypes.cpp
//  catsmat
//
//  Created by Jason James Stoessel on 7/03/2017.
//
//

#include "IMUSANT_vectormap_analysis_types.hpp"

namespace IMUSANT
{
    
    void
    IMUSANT_IntervalVectorMapAnalysis::
    Visit(const IMUSANT_processing& processing)
    {
        IMUSANT_processing::COLLECTIONMAP collections = processing.getCollections();
        
        BuildVectorMap(collections);
    }
    
    void
    IMUSANT_IntervalVectorMapAnalysis::
    BuildVectorMap(IMUSANT_processing::COLLECTIONMAP& collections)
    {
        //get first part from first file
        int ID = 0;
        
        for (auto i = collections.begin(); i!=collections.end(); i++)
        {
            IMUSANT_collection_visitor collection = i->second;
            for (auto j = collection.getPartwiseIntervalVectors().begin(); j!=collection.getPartwiseIntervalVectors().end(); j++)
            {
                ++ID;
                id_vec_map_[ID] = (*j)->getIntervals();
            }
        }
    }

    void
    IMUSANT_IntervalVectorMapAnalysis::
    Localise( IMUSANT_T_RepeatedSubstring<IMUSANT_interval>& repeats,
                  DEQUE_PAIR z,
                  typename IMUSANT_T_VectorMap<IMUSANT_interval,IMUSANT_processing>::id_vec_map::iterator& i,
                  typename IMUSANT_T_VectorMap<IMUSANT_interval,IMUSANT_processing>::id_vec_map::iterator& j,
                  bool first, bool consecutive)
    {
        for (DEQUE_PAIR::iterator iv=z.begin(); iv!=z.end(); iv++)
        {
            IMUSANT_range loc1 = iv->first.getLocation();
            IMUSANT_range loc2 = iv->second.getLocation();
            if (consecutive)
            {
                if (iv+1!=z.end())
                {
                    repeats.sequence.push_back(iv->first);
                    if (!first)
                    {
                        repeats.add_occurrence(i->first, loc1.first.partID, loc1.first.measure, loc1.first.note_index );
                        repeats.add_occurrence(j->first, loc2.first.partID, loc2.first.measure, loc2.first.note_index );
                        first = true;
                    }
                }
            }
            else
            {
                repeats.sequence.push_back(iv->first);
                if (!first)
                {
                    repeats.add_occurrence(i->first, loc1.first.partID, loc1.first.measure, loc1.first.note_index );
                    repeats.add_occurrence(j->first, loc2.first.partID, loc2.first.measure, loc2.first.note_index );
                    first = true;
                }
            }
        }
    }
    
    //=== IMUSANT_PitchVectorMapAnalysis ===
    void
    IMUSANT_PitchVectorMapAnalysis::
    Visit(const IMUSANT_processing& processing)
    {
        IMUSANT_processing::COLLECTIONMAP collections = processing.getCollections();
        
        BuildVectorMap(collections);
    }
    
    void
    IMUSANT_PitchVectorMapAnalysis::
    BuildVectorMap(IMUSANT_processing::COLLECTIONMAP& collections)
    {
        int ID = 0;
        
        for (auto i = collections.begin(); i!=collections.end(); i++)
        {
            IMUSANT_collection_visitor collection = i->second;
            for (auto j = collection.getPartwisePitchVectors().begin(); j!=collection.getPartwisePitchVectors().end(); j++)
            {
                ++ID;
                id_vec_map_[ID] = (*j)->getPitches();
            }
        }
    }
    
    void
    IMUSANT_PitchVectorMapAnalysis::
    Localise( IMUSANT_T_RepeatedSubstring<IMUSANT_pitch>& repeats,
             DEQUE_PAIR z,
             typename IMUSANT_T_VectorMap<IMUSANT_pitch,IMUSANT_processing>::id_vec_map::iterator& i,
             typename IMUSANT_T_VectorMap<IMUSANT_pitch,IMUSANT_processing>::id_vec_map::iterator& j,
             bool first, bool consecutive)
    {
        for (DEQUE_PAIR::iterator iv=z.begin(); iv!=z.end(); iv++)
        {
             repeats.sequence.push_back(iv->first);
        }
    }
}

