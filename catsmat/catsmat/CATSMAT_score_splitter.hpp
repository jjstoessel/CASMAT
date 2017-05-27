//
//  CATSMAT_score_splitter.hpp
//  catsmat
//
//  Created by Jason Stoessel on 22/03/2017.
//
//

#ifndef CATSMAT_score_splitter_hpp
#define CATSMAT_score_splitter_hpp

#include <stdio.h>
#include "IMUSANT_score.h"
#include "Loki/Visitor.h"
#include "smartpointer.h"

using namespace IMUSANT;

namespace CATSMAT
{
    
    class CATSMAT_ScoreSpliter: public smartable, public Loki::BaseVisitor, public Loki::Visitor<IMUSANT_score, void, true>
    {
    public:
        typedef vector<IMUSANT_vector<S_IMUSANT_measure>::iterator> MEASURE_ITERATORS;
        
        CATSMAT_ScoreSpliter();
        
        void Visit(const IMUSANT_score& score);
        
        vector<S_IMUSANT_score> GetSplitScores() { return split_scores_; }
        
    private:
        bool IsItSectioned(const IMUSANT_score& score, MEASURE_ITERATORS& score_sections);
        void SpiltScore(const IMUSANT_score& score, MEASURE_ITERATORS& score_sections);
        MEASURE_ITERATORS FindSectionBeginningsInPart(const S_IMUSANT_part part);
        MEASURE_ITERATORS FindSectionBeginningsInScore(const MEASURE_ITERATORS& part_end_of_sections);
        
        vector<S_IMUSANT_score> split_scores_;
    };

}
#endif /* CATSMAT_score_splitter_hpp */
