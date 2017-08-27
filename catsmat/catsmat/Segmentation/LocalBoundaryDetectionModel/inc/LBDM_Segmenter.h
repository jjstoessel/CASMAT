//
//  IMUSANT_LBDM_segmenter.h
//  imusant
//
//  Created by Jason Stoessel on 30/06/2016.
//
//

#ifndef __LBDM_Segmenter__
#define __LBDM_Segmenter__

#include <stdio.h>
#include "IMUSANT_t_suffixtree_builder.h"
#include "Loki/Visitor.h"
#include "LBDM_SegmentedPart.h"

using namespace Loki;

namespace CATSMAT {
   

    class LBDM_Segmenter :
        public Loki::BaseVisitor,
        public Loki::Visitor<IMUSANT_processing, void, true>
    {
    public:
        
        typedef vector<S_IMUSANT_segmented_part_LBDM> PART_SEGS_VEC;
        
        LBDM_Segmenter(SetOfSegment &segmentation_results)
        : fSegmentationResult(segmentation_results)
        {
        }
        ~LBDM_Segmenter() {}
        
        void    Visit(const IMUSANT_processing&);
        const   PART_SEGS_VEC& getSegmentedParts() { return sp; }
        PART_SEGS_VEC findMelodicSegments_LBDM(const vector<S_IMUSANT_score>& scores);
        
    private:
        SetOfSegment &fSegmentationResult;
        
        PART_SEGS_VEC sp;
        
    };

}
#endif /* defined(__LBDM_Segmenter__) */
