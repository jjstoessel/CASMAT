//
//  CATSMAT_dissonance_classifier.cpp
//  catsmat
//
//  Created by Jason Stoessel on 7/7/19.
//

#include "CATSMAT_dissonance_classifier.h"
#include "CATSMAT_score_profile.h"
#include "CATSMAT_score_profile.cpp" //template function implementations
#include "CATSMAT_dissonance.h"

namespace CATSMAT {
    
    template class CATSMAT_score_profile<CATSMAT_dissonance>;
    
}
