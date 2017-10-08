//
// Created by Derrick Hill on 8/10/17.
//
// This class provides the main API entry point for segmenting files using the various different segmentation algorithms.
//
// The main data structure returned from this class is I_SetOfSegment which contains one instance of Segment for each
// segments discovered by the various different algorithms, without duplicates.
//

#ifndef CATSMAT_SEGMENTER_H
#define CATSMAT_SEGMENTER_H

#include "SetOfSegment.h"
#include "libIMUSANT.h"


namespace CATSMAT {

    class Segmenter {
    public:
        SetOfSegment& segmentScores(const IMUSANT_processing &scores);
    };
}



#endif //CATSMAT_SEGMENTER_H
