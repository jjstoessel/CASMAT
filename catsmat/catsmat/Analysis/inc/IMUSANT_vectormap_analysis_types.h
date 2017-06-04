//
//  IMUSANT_VectorMapAnalysisTypes.hpp
//  catsmat
//
//  Created by Jason Stoessel on 7/03/2017.
//
//

#ifndef IMUSANT_VectorMapAnalysisTypes_hpp
#define IMUSANT_VectorMapAnalysisTypes_hpp

#include <stdio.h>

#include "libIMUSANT.h"

#include "IMUSANT_t_vectormap_analysis.h"
#include "IMUSANT_contour_symbol.h"

using namespace IMUSANT;

namespace CATSMAT {
    
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
    
    class IMUSANT_ContourVectorMapAnalysis : public IMUSANT_T_VectorMapAnalysis<IMUSANT_contour_symbol, IMUSANT_processing>
    {
    public:
        typedef std::map<int, map<pair<IMUSANT_contour_symbol, IMUSANT_contour_symbol>, int> > CONTOUR_TABLE;
        
                        IMUSANT_ContourVectorMapAnalysis() {}
        void            Visit(const IMUSANT_processing&);
        
        CONTOUR_TABLE   EntabulateMelodicDirectionPairs();
        string          EntabulateAndPrintMelodicDirectionPairs();
    private:
        void            BuildVectorMap(IMUSANT_processing::COLLECTIONMAP& collections);
        void            Localise( IMUSANT_T_RepeatedSubstring<IMUSANT_contour_symbol>& repeats, DEQUE_PAIR z, typename IMUSANT_T_VectorMap<IMUSANT_contour_symbol,IMUSANT_processing>::id_vec_map::iterator& i,typename IMUSANT_T_VectorMap<IMUSANT_contour_symbol,IMUSANT_processing>::id_vec_map::iterator& j, bool first, bool consecutive);
        
    };
    
    class IMUSANT_ContourDupleVectorMapAnalysis : public IMUSANT_T_VectorMapAnalysis<std::pair<IMUSANT_contour_symbol, IMUSANT_contour_symbol>, IMUSANT_processing>
    {
    public:
        typedef std::pair<IMUSANT_contour_symbol, IMUSANT_contour_symbol>   CONTOUR_PAIR;
        typedef std::map<int, map<CONTOUR_PAIR, int> >                      CONTOUR_TABLE;
        
                        IMUSANT_ContourDupleVectorMapAnalysis() {}
        void            Visit(const IMUSANT_processing&);

    private:
        void            BuildVectorMap(IMUSANT_processing::COLLECTIONMAP& collections);
        void            Localise( IMUSANT_T_RepeatedSubstring<CONTOUR_PAIR>& repeats, DEQUE_PAIR z, typename IMUSANT_T_VectorMap<CONTOUR_PAIR,IMUSANT_processing>::id_vec_map::iterator& i,typename IMUSANT_T_VectorMap<CONTOUR_PAIR,IMUSANT_processing>::id_vec_map::iterator& j, bool first, bool consecutive);
        
    };
}

#endif /* IMUSANT_VectorMapAnalysisTypes_hpp */
