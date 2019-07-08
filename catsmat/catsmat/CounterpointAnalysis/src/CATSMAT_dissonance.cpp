//
//  CATSMAT_dissonance_type.cpp
//  catsmat
//
//  Created by Jason Stoessel on 7/7/19.
//

#include "CATSMAT_dissonance.h"
#include "IMUSANT_generalised_interval.h"

namespace CATSMAT
{
    using namespace CATSMAT;
    using namespace IMUSANT;
    
    CATSMAT_dissonance::CATSMAT_dissonance()
        : IMUSANT_interval()
    {
        
    }
    
    CATSMAT_dissonance::~CATSMAT_dissonance() noexcept {
    
    }
    
    int CATSMAT_dissonance::compare(const CATSMAT::CATSMAT_dissonance &i) const
    {
        return this->schemata_-i.schemata_;
    }
    
    void CATSMAT_dissonance::Calculate(IMUSANT_note& u1, IMUSANT_note& l1,
                                       IMUSANT_note& u2, IMUSANT_note& l2,
                                       IMUSANT_note& u3, IMUSANT_note& l3)
    {
        
        IMUSANT_generalised_interval v2(u1.pitch(),l2.pitch());
        
        
        if (v2.getQuality()!=IMUSANT_interval::dissonant) throw ("Non-dissonant interval passed as middle vertical interval in CATSMAT_dissonance::Calculate()");
        //could also test that note pairs u1 and l1, etc. are the same duration
        
        (IMUSANT_interval)*this=v2;
        
        IMUSANT_generalised_interval v1(u1.pitch(),l1.pitch());
        IMUSANT_generalised_interval v3(u1.pitch(),l3.pitch());
        IMUSANT_generalised_interval h1(l1.pitch(),l2.pitch());
        IMUSANT_generalised_interval h2(l2.pitch(),l3.pitch());
        
        //insert simplified representation
        quingram_ = { v1.getNumber(), v2.getNumber(), v3.getNumber(), h1.getNumber(), h2.getNumber()};
    }
    
    

}


