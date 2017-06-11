//
//  IMUSANT_fixed_period_segmenter.hpp
//  catsmat
//
//  Created by Derrick Hill on 28/1/17.
//
//

#ifndef IMUSANT_fixed_period_segmenter_hpp
#define IMUSANT_fixed_period_segmenter_hpp

#include <stdio.h>

#include "IMUSANT_t_suffixtree_builder.h"
#include "Visitor.h"
#include "IMUSANT_segmented_part_fixed_period.h"

using namespace Loki;

namespace CATSMAT {
    
    class IMUSANT_fixed_period_segmenter :
        public Loki::BaseVisitor,
        public Loki::Visitor<IMUSANT_processing, void, true>
    {
    public:
        
        typedef vector<IMUSANT_set_of_segment> SetOfSegmentsVector;
        
        IMUSANT_fixed_period_segmenter() {}
        ~IMUSANT_fixed_period_segmenter() {}
        
        void    Visit(const IMUSANT_processing&);
        const   SetOfSegmentsVector& getSegmentSets() { return sp; }
        SetOfSegmentsVector findMelodicSegmentsFixedPeriod(const vector<S_IMUSANT_score>& scores);
        
    private:
        
        SetOfSegmentsVector sp;
        
    };
    
}

#endif /* IMUSANT_fixed_period_segmenter_hpp */
