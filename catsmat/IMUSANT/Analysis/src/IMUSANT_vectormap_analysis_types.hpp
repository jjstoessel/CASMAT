//
//  IMUSANT_VectorMapAnalysisTypes.hpp
//  catsmat
//
//  Created by Jason James Stoessel on 7/03/2017.
//
//

#ifndef IMUSANT_VectorMapAnalysisTypes_hpp
#define IMUSANT_VectorMapAnalysisTypes_hpp

#include <stdio.h>
#include "IMUSANT_t_vectormap_analysis.hpp"
#include "IMUSANT_interval.h"
#include "IMUSANT_processing.h"

namespace IMUSANT {
    
    class IMUSANT_IntervalVectorMapAnalysis : public IMUSANT_T_VectorMapAnalysis<IMUSANT_interval,IMUSANT_processing>
    {
    public:
                IMUSANT_IntervalVectorMapAnalysis() {}
        
        void    Visit(const IMUSANT_processing&);
    private:
        void    BuildVectorMap(IMUSANT_processing::COLLECTIONMAP& collections);
        void    Localise( IMUSANT_T_RepeatedSubstring<IMUSANT_interval>&, DEQUE_PAIR, typename IMUSANT_T_VectorMap<IMUSANT_interval,IMUSANT_processing>::id_vec_map::iterator&, typename IMUSANT_T_VectorMap<IMUSANT_interval,IMUSANT_processing>::id_vec_map::iterator&,bool first, bool consecutive);
    };
    
    class IMUSANT_PitchVectorMapAnalysis : public IMUSANT_T_VectorMapAnalysis<IMUSANT_pitch,IMUSANT_processing>
    {
    public:
                IMUSANT_PitchVectorMapAnalysis() {}
        
        void    Visit(const IMUSANT_processing&);
    private:
        void    BuildVectorMap(IMUSANT_processing::COLLECTIONMAP& collections);
        void    Localise( IMUSANT_T_RepeatedSubstring<IMUSANT_pitch>& repeats, DEQUE_PAIR z, typename IMUSANT_T_VectorMap<IMUSANT_pitch,IMUSANT_processing>::id_vec_map::iterator& i,typename IMUSANT_T_VectorMap<IMUSANT_pitch,IMUSANT_processing>::id_vec_map::iterator& j, bool first, bool consecutive);
    };
}

#endif /* IMUSANT_VectorMapAnalysisTypes_hpp */
