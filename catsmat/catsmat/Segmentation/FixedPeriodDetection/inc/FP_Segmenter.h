
#ifndef __FixedPeriodSegmenter__
#define __FixedPeriodSegmenter__

#include <stdio.h>

#include "TSuffixtreeBuilder.h"
#include "Loki/Visitor.h"
#include "FP_SegmentedScore.h"

using namespace Loki;

namespace CATSMAT {
    
    class FP_Segmenter :
        public Loki::BaseVisitor,
        public Loki::Visitor<IMUSANT_processing, void, true>
    {
    public:
        
        typedef vector<SetOfSegment> SetOfSegmentsVector;
        
        FP_Segmenter(SetOfSegment &segmentation_results)
        : fSegmentationResult(segmentation_results)
        {
        }
        ~FP_Segmenter() {}
        
        void    Visit(const IMUSANT_processing&);
        
        const   SetOfSegmentsVector& getSegmentSets() { return sp; }
        SetOfSegmentsVector findMelodicSegmentsFixedPeriod(const vector<S_IMUSANT_score>& scores);
        
    private:
        
        SetOfSegment &fSegmentationResult;
        
        SetOfSegmentsVector sp;
        
    };
    
}

#endif /* __FixedPeriodSegmenter__ */
