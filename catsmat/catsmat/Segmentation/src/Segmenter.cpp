
#include "Segmenter.h"
#include "SetOfSegment.h"

namespace CATSMAT
{
    SetOfSegment&
    Segmenter::
    segmentScores(const IMUSANT_processing &scores)
    {
        SetOfSegment* sos = new SetOfSegment;
        return *sos;
    }

}

