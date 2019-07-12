//
//  CATSMAT_dissonance_type.cpp
//  catsmat
//
//  Created by Jason Stoessel on 7/7/19.
//

#include "CATSMAT_dissonance.h"
#include "IMUSANT_generalised_interval.h"
#include "CATSMAT_t_utilities.h"

namespace CATSMAT
{
    using namespace CATSMAT;
    using namespace IMUSANT;
    using namespace std;
    
    //map of lambda functions used to find a dissonance behaviour, avoiding long if … else search
    const std::map<CATSMAT_dissonance::schemata::type, std::function<bool(const array<int,6>&)>  > CATSMAT_dissonance::schemata::behaviours_ =
    {
        { CATSMAT_dissonance::schemata::unclassified,
            [](const array<int,6>& n){ return n[up_mel_to] == 0 && n[up_mel_from] == 0 && n[low_mel_to] == 0 && n[low_mel_from] == 0; } },
        { CATSMAT_dissonance::schemata::ascending_passing_tone,
            [](const array<int,6>& n){ return n[up_mel_to] == 1 && n[up_mel_from] == 1 && n[low_mel_to] == 0; } },
        { CATSMAT_dissonance::schemata::descending_passing_tone,
            [](const array<int,6>& n){ return n[up_mel_to] == -1 && n[up_mel_from] == -1 && n[low_mel_to] == 0; } },
        { CATSMAT_dissonance::schemata::upper_neighbour_tone,
            [](const array<int,6>& n){ return n[up_mel_to] == 1 && n[up_mel_from] == -1 && n[low_mel_to] == 0; } },
        { CATSMAT_dissonance::schemata::lower_neighbour_tone,
            [](const array<int,6>& n){ return n[up_mel_to] == -1 && n[up_mel_from] == 1 && n[low_mel_to] == 0; } },
        { CATSMAT_dissonance::schemata::incomplete_upper_neighbour_tone,
            [](const array<int,6>& n){ return n[up_mel_to] > 1 && n[up_mel_from] == -1 && n[low_mel_to] == 0; } },
        { CATSMAT_dissonance::schemata::incomplete_lower_neighbour_tone,
            [](const array<int,6>& n){ return n[up_mel_to] < -1 && n[up_mel_from] == 1 && n[low_mel_to] == 0; } },
        { CATSMAT_dissonance::schemata::appoggiatura,
            [](const array<int,6>& n){ return n[up_mel_from] == -1 && n[low_mel_from] == 0; } },
        { CATSMAT_dissonance::schemata::suspension,
            [](const array<int,6>& n){ return n[up_mel_to] == -1 && n[up_mel_from] == 0 && n[low_mel_to] == 0 && n[low_mel_from] == -1; } },
        { CATSMAT_dissonance::schemata::retardation,
            [](const array<int,6>& n){ return n[up_mel_to] == 0 && n[up_mel_from] == 1 && n[low_mel_to] == -1 && n[low_mel_from] == 0; } },
        { CATSMAT_dissonance::schemata::cambiata_w,
            [](const array<int,6>& n){ return n[0] == -1 && n[1] == 2 && n[2] == -1 && n[3] == 0 && n[4] == 0; } },
        { CATSMAT_dissonance::schemata::cambiata_m,
            [](const array<int,6>& n){ return n[0] == 1 && n[1] == -2 && n[2] == 1 && n[3] == 0 && n[4] == 0; } }
    };
    
    //const std::multimap<std::function<bool(const array<int,6>&)>, CATSMAT_dissonance::schemata::type> CATSMAT_dissonance::schemata::behaviours_flip_ = flip_map<CATSMAT_dissonance::schemata::type, std::function<bool(const array<int,6>&)> >(CATSMAT_dissonance::schemata::behaviours_);
    
    CATSMAT_dissonance::schemata::schemata(int up_mel_to, int up_mel_from, int low_mel_to, int low_mel_from, bool accented)
    {
        behaviour_ = { up_mel_to, up_mel_from, low_mel_to, low_mel_from, 0, 0};
        accented_ = accented;
        type_ = find_type(behaviour_);
    }
    
    CATSMAT_dissonance::schemata::schemata(int up_intermed, int up_mel_to, int up_mel_from, int low_intermed, int low_mel_to, int low_mel_from, bool accented)
    {
        behaviour_ = { up_intermed, up_mel_to, up_mel_from, low_intermed, low_mel_to, low_mel_from };
        accented_ = accented;
        type_ = find_type(behaviour_);
    }
    
    const CATSMAT_dissonance::schemata::type
    CATSMAT_dissonance::schemata::find_type(const array<int, 6> &b)
    {
        //const auto i = behaviours_flip_.find(std::function<bool(const array<int,6>&)>(b));
        auto i = behaviours_.begin();
        
        for ( ; i!=behaviours_.end() ; i++ )
        {
            if (i->second(b)) break;
        }
        
        if (i!=behaviours_.end())
            return i->first;
        else return unclassified;
        //const auto i = behaviours_flip_.find(std::function<bool(const array<int,6>& n)>);
        //if (i!=behaviours_.end())
         //   return i->second;
        //else
           // return unclassified;
    }
    
    CATSMAT_dissonance::CATSMAT_dissonance()
        : schemata_() //default initialisers
    {
        
    }
    
    
    //constructor for three element dissonance progression
    
    //constructor for four element dissonance progression
    
    CATSMAT_dissonance::~CATSMAT_dissonance()
    {
    
    }
    
    void CATSMAT_dissonance::Calculate(IMUSANT_note& u1, IMUSANT_note& l1,
                                       IMUSANT_note& u2, IMUSANT_note& l2,
                                       IMUSANT_note& u3, IMUSANT_note& l3)
    {
        
        IMUSANT_generalised_interval v2(u2.pitch(),l2.pitch());
        
        
        if (v2.getQuality()!=IMUSANT_interval::dissonant) throw ("Non-dissonant interval passed as middle vertical interval in CATSMAT_dissonance::Calculate()");
        //could also test that note pairs u1 and l1, etc. are the same duration
        dissonance_=v2;
        
        if (u2.duration()->duration()!=l2.duration()->duration()) throw ("Notes passed for dissonance in CATSMAT_dissonance::Calculate() are not the same duration.");
        
        duration_.set(u2.duration()->duration());
        
        IMUSANT_generalised_interval upper_mel_to(u1.pitch(),u2.pitch());
        IMUSANT_generalised_interval upper_mel_from(u2.pitch(),u3.pitch());
        IMUSANT_generalised_interval lower_mel_to(l1.pitch(),l2.pitch());
        IMUSANT_generalised_interval lower_mel_from(l2.pitch(),l3.pitch());
        
        int umt, umf, lmt, lmf;
        umt = upper_mel_to.getNumber();
        umf = upper_mel_from.getNumber();
        lmt = lower_mel_to.getNumber();
        lmf = lower_mel_from.getNumber();
        
        //insert simplified representation
        schemata_ = schemata(umt, umf, lmt, lmf,false);
    }
    
}



