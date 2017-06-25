//
//  IMUSANT_LBDM_segmenter.h
//  imusant
//
//  Created by Jason Stoessel on 30/06/2016.
//
//

#ifndef __imusant__IMUSANT_LBDM_segmenter__
#define __imusant__IMUSANT_LBDM_segmenter__

#include <stdio.h>
#include "IMUSANT_t_suffixtree_builder.h"
#include "Visitor.h"
#include "IMUSANT_segmented_part_LBDM.h"

using namespace Loki;

namespace CATSMAT {
   

    class IMUSANT_LBDM_segmenter :
        public Loki::BaseVisitor,
        public Loki::Visitor<IMUSANT_processing, void, true>
    {
    public:
        
        typedef vector<S_IMUSANT_segmented_part_LBDM> PART_SEGS_VEC;
        
        IMUSANT_LBDM_segmenter(IMUSANT_set_of_segment &segmentation_results)
        : fSegmentationResult(segmentation_results)
        {
        }
        ~IMUSANT_LBDM_segmenter() {}
        
        void    Visit(const IMUSANT_processing&);
        const   PART_SEGS_VEC& getSegmentedParts() { return sp; }
        PART_SEGS_VEC findMelodicSegments_LBDM(const vector<S_IMUSANT_score>& scores);
        
    private:
        IMUSANT_set_of_segment &fSegmentationResult;
        
        PART_SEGS_VEC sp;
        
    };

}
#endif /* defined(__imusant__IMUSANT_LBDM_segmenter__) */
