//
//  CATSMAT_score_splitter.cpp
//  catsmat
//
//  Created by Jason James Stoessel on 22/03/2017.
//
//

#include "CATSMAT_score_splitter.hpp"

namespace CATSMAT {
    CATSMAT_ScoreSpliter::CATSMAT_ScoreSpliter()
    {
        
    }
    
    void
    CATSMAT_ScoreSpliter::
    Visit(const IMUSANT_score& score)
    {
        MEASURE_ITERATORS score_section_begin_measure_iterators;
        
        if (IsItSectioned(score, score_section_begin_measure_iterators))
            SpiltScore(score, score_section_begin_measure_iterators);
        
    }
    
    bool
    CATSMAT_ScoreSpliter::
    IsItSectioned(const IMUSANT_score& score, MEASURE_ITERATORS& score_sections)
    {
        
        return (score_sections.size() > 0);
    }
    
    void
    CATSMAT_ScoreSpliter::
    SpiltScore(const IMUSANT_score& score, MEASURE_ITERATORS& score_sections)
    {
        
    }
    
    CATSMAT_ScoreSpliter::MEASURE_ITERATORS
    CATSMAT_ScoreSpliter::
    FindSectionBeginningsInPart(const S_IMUSANT_part part)
    {
        MEASURE_ITERATORS part_section_begin_measure_iterators;
        
        return part_section_begin_measure_iterators;
    }
    
    CATSMAT_ScoreSpliter::MEASURE_ITERATORS
    CATSMAT_ScoreSpliter::
    FindSectionBeginningsInScore(const MEASURE_ITERATORS& part_end_of_sections)
    {
        MEASURE_ITERATORS score_section_end_measure_iterators;
        
        return score_section_end_measure_iterators;
    }
    
}
