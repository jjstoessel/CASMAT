//
//  VectorMapAnalysisTypes.hpp
//  catsmat
//
//  Created by Jason Stoessel on 7/03/2017.
//
//

#ifndef ____VectorMapAnalysisTypes__
#define ____VectorMapAnalysisTypes__

#include <stdio.h>

#include "libIMUSANT.h"

#include "TVectorMapAnalysis.h"
#include "IMUSANT_contour_symbol.h"

using namespace IMUSANT;

namespace CATSMAT {
    
    class IntervalVectorMapAnalysis : public TVectorMapAnalysis<IMUSANT_interval,IMUSANT_processing>
    {
    public:
                IntervalVectorMapAnalysis() {}
        
        void    Visit(const IMUSANT_processing&);
    private:
        void    BuildVectorMap(IMUSANT_processing::COLLECTIONMAP& collections);
        void    Localise( TRepeatedSubstring<IMUSANT_interval>&, DEQUE_PAIR, typename TVectorMap<IMUSANT_interval,IMUSANT_processing>::id_vec_map::iterator&, typename TVectorMap<IMUSANT_interval,IMUSANT_processing>::id_vec_map::iterator&,bool first, bool consecutive);
    };
    
    class PitchVectorMapAnalysis : public TVectorMapAnalysis<IMUSANT_pitch,IMUSANT_processing>
    {
    public:
                PitchVectorMapAnalysis() {}
        
        void    Visit(const IMUSANT_processing&);
    private:
        void    BuildVectorMap(IMUSANT_processing::COLLECTIONMAP& collections);
        void    Localise( TRepeatedSubstring<IMUSANT_pitch>& repeats, DEQUE_PAIR z, typename TVectorMap<IMUSANT_pitch,IMUSANT_processing>::id_vec_map::iterator& i,typename TVectorMap<IMUSANT_pitch,IMUSANT_processing>::id_vec_map::iterator& j, bool first, bool consecutive);
    };
    
    class ContourVectorMapAnalysis : public TVectorMapAnalysis<IMUSANT_contour_symbol, IMUSANT_processing>
    {
    public:
        typedef std::map<int, map<pair<IMUSANT_contour_symbol, IMUSANT_contour_symbol>, int> > CONTOUR_TABLE;
        
                        ContourVectorMapAnalysis() {}
        void            Visit(const IMUSANT_processing&);
        
        CONTOUR_TABLE   EntabulateMelodicDirectionPairs();
        string          EntabulateAndPrintMelodicDirectionPairs();
    private:
        void            BuildVectorMap(IMUSANT_processing::COLLECTIONMAP& collections);
        void            Localise( TRepeatedSubstring<IMUSANT_contour_symbol>& repeats, DEQUE_PAIR z, typename TVectorMap<IMUSANT_contour_symbol,IMUSANT_processing>::id_vec_map::iterator& i,typename TVectorMap<IMUSANT_contour_symbol,IMUSANT_processing>::id_vec_map::iterator& j, bool first, bool consecutive);
        
    };
    
    class ContourDupleVectorMapAnalysis : public TVectorMapAnalysis<std::pair<IMUSANT_contour_symbol, IMUSANT_contour_symbol>, IMUSANT_processing>
    {
    public:
        typedef std::pair<IMUSANT_contour_symbol, IMUSANT_contour_symbol>   CONTOUR_PAIR;
        typedef std::map<int, map<CONTOUR_PAIR, int> >                      CONTOUR_TABLE;
        
                        ContourDupleVectorMapAnalysis() {}
        void            Visit(const IMUSANT_processing&);

    private:
        void            BuildVectorMap(IMUSANT_processing::COLLECTIONMAP& collections);
        void            Localise( TRepeatedSubstring<CONTOUR_PAIR>& repeats, DEQUE_PAIR z, typename TVectorMap<CONTOUR_PAIR,IMUSANT_processing>::id_vec_map::iterator& i,typename TVectorMap<CONTOUR_PAIR,IMUSANT_processing>::id_vec_map::iterator& j, bool first, bool consecutive);
        
    };
}

#endif /* ____VectorMapAnalysisTypes__ */
