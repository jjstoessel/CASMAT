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
#include "Loki/Visitor.h"
#include "SegmentedScoreFixedPeriod.h"

using namespace Loki;

namespace CATSMAT {
    
    class IMUSANT_fixed_period_segmenter :
        public Loki::BaseVisitor,
        public Loki::Visitor<IMUSANT_processing, void, true>
    {
    public:
        
        typedef vector<IMUSANT_set_of_segment> SetOfSegmentsVector;
        
        IMUSANT_fixed_period_segmenter(IMUSANT_set_of_segment &segmentation_results)
        : fSegmentationResult(segmentation_results)
        {
        }
        ~IMUSANT_fixed_period_segmenter() {}
        
        void    Visit(const IMUSANT_processing&);
        
        const   SetOfSegmentsVector& getSegmentSets() { return sp; }
        SetOfSegmentsVector findMelodicSegmentsFixedPeriod(const vector<S_IMUSANT_score>& scores);
        
    private:
        
        IMUSANT_set_of_segment &fSegmentationResult;
        
        SetOfSegmentsVector sp;
        
    };
    
}

#endif /* IMUSANT_fixed_period_segmenter_hpp */
