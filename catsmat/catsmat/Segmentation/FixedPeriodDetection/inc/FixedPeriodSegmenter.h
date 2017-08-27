
#ifndef FixedPeriodSegmenter_hpp
#define FixedPeriodSegmenter_hpp

#include <stdio.h>

#include "IMUSANT_t_suffixtree_builder.h"
#include "Loki/Visitor.h"
#include "SegmentedScoreFixedPeriod.h"

using namespace Loki;

namespace CATSMAT {
    
    class FixedPeriodSegmenter :
        public Loki::BaseVisitor,
        public Loki::Visitor<IMUSANT_processing, void, true>
    {
    public:
        
        typedef vector<IMUSANT_set_of_segment> SetOfSegmentsVector;
        
        FixedPeriodSegmenter(IMUSANT_set_of_segment &segmentation_results)
        : fSegmentationResult(segmentation_results)
        {
        }
        ~FixedPeriodSegmenter() {}
        
        void    Visit(const IMUSANT_processing&);
        
        const   SetOfSegmentsVector& getSegmentSets() { return sp; }
        SetOfSegmentsVector findMelodicSegmentsFixedPeriod(const vector<S_IMUSANT_score>& scores);
        
    private:
        
        IMUSANT_set_of_segment &fSegmentationResult;
        
        SetOfSegmentsVector sp;
        
    };
    
}

#endif /* FixedPeriodSegmenter_hpp */
