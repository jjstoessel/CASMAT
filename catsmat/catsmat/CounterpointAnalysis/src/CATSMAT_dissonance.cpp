//
//  CATSMAT_dissonance.cpp
//  catsmat
//
//  Created by Jason Stoessel on 7/7/19.
//
//  Class to categorise dissonance handling schematae

#include "CATSMAT_dissonance.h"
#include "IMUSANT_generalised_interval.h"
#include "CATSMAT_t_utilities.h"

namespace CATSMAT
{
    using namespace CATSMAT;
    using namespace IMUSANT;
    using namespace std;
    
    ostream& operator<< (ostream& os, const CATSMAT_dissonance& elt )
    {
        elt.print(os);
        return os;
    }
    
    //map of lambda functions used to find a dissonance behaviour, avoiding long if … else search
    const std::map<CATSMAT_dissonance::schemata::type, CATSMAT_dissonance::schemata::eval_function_> CATSMAT_dissonance::schemata::behaviours_ =
    {
        {
            CATSMAT_dissonance::schemata::ascending_passing_tone,
            [](const CATSMAT_dissonance::schemata::behaviour_array& b, bool a)
            {
                return
                (b[up_mel_to] == 1 && b[up_mel_from] == 1 && b[low_mel_to] == 0 && !a) ||
                (b[up_mel_to] == 0 && b[low_mel_to] == 1 && b[low_mel_from] == 1 && !a);
            }
        },
        {
            CATSMAT_dissonance::schemata::descending_passing_tone,
            [](const CATSMAT_dissonance::schemata::behaviour_array& b, bool a)
            {
                return
                (b[up_mel_to] == -1 && b[up_mel_from] == -1 && b[low_mel_to] == 0 && !a) ||
                (b[up_mel_to] == 0 && b[low_mel_to] == -1 && b[low_mel_from] == -1 && !a);
            }
        },
        {
            CATSMAT_dissonance::schemata::upper_neighbour_tone,
            [](const CATSMAT_dissonance::schemata::behaviour_array& b, bool a)
            {
                return
                (b[up_mel_to] == 1 && b[up_mel_from] == -1 && b[low_mel_to] == 0 && !a) ||
                (b[up_mel_to] == 0 && b[low_mel_to] == 1 && b[low_mel_from] == -1 && !a);
            }
        },
        {
            CATSMAT_dissonance::schemata::lower_neighbour_tone,
            [](const CATSMAT_dissonance::schemata::behaviour_array& b, bool a)
            {
                return
                (b[up_mel_to] == -1 && b[up_mel_from] == 1 && b[low_mel_to] == 0 && !a) ||
                (b[up_mel_to] == 0 && b[low_mel_to] == -1 && b[low_mel_from] == 1 && !a);
            }
        },
        {
            CATSMAT_dissonance::schemata::incomplete_upper_neighbour_tone,
            [](const CATSMAT_dissonance::schemata::behaviour_array& b, bool a)
            {
                return
                (b[up_mel_to] > 1 && b[up_mel_from] == -1 && b[low_mel_to] == 0 && !a) ||
                (b[up_mel_to] == 0 && b[low_mel_to] > 1 && b[low_mel_from] == -1 && !a);
            }
        },
        {
            CATSMAT_dissonance::schemata::incomplete_lower_neighbour_tone,
            [](const CATSMAT_dissonance::schemata::behaviour_array& b, bool a)
            {
                return
                (b[up_mel_to] < -1 && b[up_mel_from] == 1 && b[low_mel_to] == 0 && !a) ||
                (b[up_mel_to] == 0 && b[low_mel_to] < -1 && b[low_mel_from] == 1 && !a);
                
            }
        },
        {
            CATSMAT_dissonance::schemata::appoggiatura,
            [](const CATSMAT_dissonance::schemata::behaviour_array& b, bool a)
            {
                return
                ( b[up_mel_to] != 0 && b[up_mel_from] == -1 && b[low_mel_from] == 0 && a) ||
                (b[up_mel_from] == 0 && b[low_mel_to] != 0 && b[low_mel_from] == -1 && a);
            }
        },
        {
            CATSMAT_dissonance::schemata::suspension,
            [](const CATSMAT_dissonance::schemata::behaviour_array& b, bool a)
            {
                return
                (b[up_mel_to] == -1 && b[up_mel_from] == 0 && b[low_mel_to] == 0 && b[low_mel_from] == -1 && a) ||
                (b[up_mel_to] == 0 && b[up_mel_from] == -1 && b[low_mel_to] == -1 && b[low_mel_from] == 0 && a);
            }
        },
        {
            CATSMAT_dissonance::schemata::suspension_by_third,
            [](const CATSMAT_dissonance::schemata::behaviour_array& b, bool a)
            {
                return
                (b[up_mel_to] == -2 && b[up_mel_from] == 0 && b[low_mel_to] == 0 && b[low_mel_from] == -1 && a) ||
                (b[up_mel_to] == 0 && b[up_mel_from] == -1 && b[low_mel_to] == -2 && b[low_mel_from] == 0 && a);
            }
        },
        {
            CATSMAT_dissonance::schemata::retardation,
            [](const CATSMAT_dissonance::schemata::behaviour_array& b, bool a)
            {
                return
                (b[up_mel_to] == 1 && b[up_mel_from] == 0 && b[low_mel_to] == 0 && b[low_mel_from] == -1 && a) ||
                (b[up_mel_to] == 0 && b[up_mel_from] == -1 && b[low_mel_to] == 1 && b[low_mel_from] == 0 && a);
                
            }
        },
        {
            CATSMAT_dissonance::schemata::cambiata,
            [](const CATSMAT_dissonance::schemata::behaviour_array& b, bool a)
            { return
                (b[0] == -1 && b[1] == -2 && b[2] == 1 && b[3] == 0 && b[4] == 0 && b[5] == 0 && !a) ||
                (b[0] == 0 && b[1] == 0 && b[2] == 0 && b[3] == -1 && b[4] == -1 && b[5] == 1 && !a);
            }
        },
        {
            CATSMAT_dissonance::schemata::cambiata_i,
            [](const CATSMAT_dissonance::schemata::behaviour_array& b, bool a)
            {
                return
                (b[0] == 1 && b[1] == 2 && b[2] == -1 && b[3] == 0 && b[4] == 0 && !a) ||
                (b[0] == 0 && b[1] == 0 && b[2] == 0 && b[3] == 1 && b[4] == 2 && b[5] == -1 && !a);
            }
        },
        //unaccented, melodic upper 1,<-1, lower 0, *
        {
            CATSMAT_dissonance::schemata::upper_escape_tone,
            [](const CATSMAT_dissonance::schemata::behaviour_array& b, bool a)
            {
                return
                (b[up_mel_to] == 1 && b[up_mel_from] < -1 && b[low_mel_to] == 0 && !a) ||
                (b[up_mel_from] == 0 && b[low_mel_to] == 1 && b[low_mel_from] < -1 && !a);
            }
        },
        //unaccented, melodic upper -1,>1, lower 0, *
        {
            CATSMAT_dissonance::schemata::lower_escape_tone,
            [](const CATSMAT_dissonance::schemata::behaviour_array& b, bool a)
            {
                return
                (b[up_mel_to] == -1 && b[up_mel_from] > 1 && b[low_mel_to] == 0 && !a) ||
                (b[up_mel_from] == 0 && b[low_mel_to] == -1 && b[low_mel_from] > 1 && !a);
            }
        }
    };
    
    const map<CATSMAT_dissonance::schemata::type, string> CATSMAT_dissonance::schemata::type_strings =
    {
        { unclassified, "Unclassified" },
        { ascending_passing_tone, "Ascending Passing Tone" },
        { descending_passing_tone, "Descending Passing Tone" },
        { upper_neighbour_tone, "Upper Neighbour Tone" },
        { lower_neighbour_tone, "Lower Neighbour Tone" },
        { incomplete_upper_neighbour_tone, "Incomplete Upper Neighbour Tone" },
        { incomplete_lower_neighbour_tone, "Incomplete Lower Neighbour Tone" },
        { appoggiatura, "Appoggiatura" },
        { suspension, "Suspension" },
        { suspension_by_third, "Suspension by third" },
        { anticipation, "Anticipation" },
        { retardation, "Retardation" },
        { cambiata, "Cambiata" },
        { cambiata_i, "Inverted Cambiata" },
        { upper_escape_tone, "Upper Escape Tone" },
        { lower_escape_tone, "Lower Escape Tone" },
        { pedal_point, "Pedal Point" }
    };
    
    CATSMAT_dissonance::schemata::schemata(int up_mel_to, int up_mel_from, int low_mel_to, int low_mel_from, bool accented)
    {
        set(up_mel_to, up_mel_from, low_mel_to, low_mel_from, accented);
    }
    
    CATSMAT_dissonance::schemata::schemata(int up_intermed, int up_mel_to, int up_mel_from, int low_intermed, int low_mel_to, int low_mel_from, bool accented)
    {
        set(up_intermed, up_mel_to, up_mel_from, low_intermed, low_mel_to, low_mel_from, accented);
    }
    
    const CATSMAT_dissonance::schemata::type
    CATSMAT_dissonance::schemata::find_type(const array<int, 6> &b, const bool accented)
    {
        auto i = behaviours_.begin();

        for ( ; i!=behaviours_.end() ; i++ )
        {
            if (i->second(b, accented)) break;
        }

        if (i!=behaviours_.end())
            return i->first;
        else return unclassified;
    }
    
    void CATSMAT_dissonance::schemata::set(int up_mel_to, int up_mel_from, int low_mel_to, int low_mel_from, bool accented)
    {
        behaviour_ = { up_mel_to, up_mel_from, low_mel_to, low_mel_from, 0, 0};
        accented_ = accented;
        type_ = find_type(behaviour_, accented_);
    }
    
    void CATSMAT_dissonance::schemata::set(int up_intermed, int up_mel_to, int up_mel_from, int low_intermed, int low_mel_to, int low_mel_from, bool accented)
    {
        behaviour_ = { up_intermed, up_mel_to, up_mel_from, low_intermed, low_mel_to, low_mel_from };
        accented_ = accented;
        type_ = find_type(behaviour_, accented);
    }
    
    bool CATSMAT_dissonance::schemata::equal(const CATSMAT::CATSMAT_dissonance::schemata &rhs) const { 
        return behaviour_==rhs.behaviour_ && accented_==rhs.accented_ && type_==rhs.type_;
    }
    
#pragma mark ==== Dissonance class ====
    
    CATSMAT_dissonance::CATSMAT_dissonance()
        : schemata_() //default initialisers
    {
        
    }
    
    //constructor for three element dissonance progression
    CATSMAT_dissonance::CATSMAT_dissonance(IMUSANT_note& u1, IMUSANT_note& l1,
                                           IMUSANT_note& u2, IMUSANT_note& l2,
                                           IMUSANT_note& u3, IMUSANT_note& l3,
                                           bool accented)
    {
        SetSchemata(u1, l1, u2, l2, u3, l3, accented);
    }
    //constructor for four element dissonance progression
    CATSMAT_dissonance::CATSMAT_dissonance(IMUSANT::IMUSANT_note &u1, IMUSANT::IMUSANT_note &l1, IMUSANT::IMUSANT_note &u2, IMUSANT::IMUSANT_note &l2, IMUSANT::IMUSANT_note &u3, IMUSANT::IMUSANT_note &l3, IMUSANT::IMUSANT_note &u4, IMUSANT::IMUSANT_note &l4, bool accented)
    {
        SetSchemata(u1, l1, u2, l2, u3, l3, u4, l4, accented);
    }
    
    CATSMAT_dissonance::~CATSMAT_dissonance()
    {
    
    }
    
    void CATSMAT_dissonance::SetSchemata(IMUSANT_note& u1, IMUSANT_note& l1,
                                         IMUSANT_note& u2, IMUSANT_note& l2,
                                         IMUSANT_note& u3, IMUSANT_note& l3,
                                         bool accented)
    {
        
        //approximate approach to voice crossing
        //swap_less<IMUSANT_note>(u1, l1);
        //swap_less<IMUSANT_note>(u2, l2);
        //swap_less<IMUSANT_note>(u3, l3);
        
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
        
        //insert simplified representation; finds type upon initialisation
        schemata_ = schemata(umt, umf, lmt, lmf, accented);
    }
    
    void CATSMAT_dissonance::SetSchemata(IMUSANT::IMUSANT_note &u1, IMUSANT::IMUSANT_note &l1,
                                         IMUSANT::IMUSANT_note &u2, IMUSANT::IMUSANT_note &l2,
                                         IMUSANT::IMUSANT_note &u3, IMUSANT::IMUSANT_note &l3,
                                         IMUSANT::IMUSANT_note &u4, IMUSANT::IMUSANT_note &l4, bool accented)
    {
        
        //approximate approach to voice crossing
        swap_less<IMUSANT_note>(u1, l1);
        swap_less<IMUSANT_note>(u2, l2);
        swap_less<IMUSANT_note>(u3, l3);
        swap_less<IMUSANT_note>(u4, l4);
        
        IMUSANT_generalised_interval v2(u2.pitch(),l2.pitch());
        
        
        if (v2.getQuality()!=IMUSANT_interval::dissonant) throw ("Non-dissonant interval passed as middle vertical interval in CATSMAT_dissonance::Calculate()");
        //could also test that note pairs u1 and l1, etc. are the same duration
        dissonance_=v2;
        
        if (u2.duration()->duration()!=l2.duration()->duration()) throw ("Notes passed for dissonance in CATSMAT_dissonance::Calculate() are not the same duration.");
        
        duration_.set(u2.duration()->duration());
        
        IMUSANT_generalised_interval upper_mel_to(u1.pitch(),u2.pitch());
        IMUSANT_generalised_interval upper_mel_inter(u2.pitch(),u3.pitch());
        IMUSANT_generalised_interval upper_mel_from(u3.pitch(),u4.pitch());
        IMUSANT_generalised_interval lower_mel_to(l1.pitch(),l2.pitch());
        IMUSANT_generalised_interval lower_mel_inter(l2.pitch(),l3.pitch());
        IMUSANT_generalised_interval lower_mel_from(l3.pitch(),l4.pitch());
        
        int umt, umi, umf, lmt, lmi, lmf;
        umt = upper_mel_to.getNumber();
        umi = upper_mel_inter.getNumber();
        umf = upper_mel_from.getNumber();
        lmt = lower_mel_to.getNumber();
        lmi = lower_mel_inter.getNumber();
        lmf = lower_mel_from.getNumber();
        
        //insert simplified representation; finds type upon initialisation
        schemata_ = schemata(umt, umi, umf, lmt, lmi, lmf, accented);
    }
    
    CATSMAT::CATSMAT_dissonance &CATSMAT_dissonance::operator=(const CATSMAT::CATSMAT_dissonance &dissonance)
    { 
        this->dissonance_ = dissonance.dissonance_;
        this->duration_ = dissonance.duration_;
        this->schemata_ = dissonance.schemata_;
        return *this;
    }
    
    bool CATSMAT_dissonance::operator==(const CATSMAT::CATSMAT_dissonance &dissonance) const
    {
        return equal(dissonance);
    }
    
    bool CATSMAT_dissonance::operator!=(const CATSMAT::CATSMAT_dissonance &dissonance) const
    {
        return equal(dissonance)==false;
    }
    
    bool CATSMAT_dissonance::equal(const CATSMAT::CATSMAT_dissonance &dissonance) const
    {
        return dissonance_==dissonance.dissonance_ && duration_==dissonance.duration_ && schemata_==dissonance.schemata_;
    }
        bool CATSMAT_dissonance::operator>(const CATSMAT::CATSMAT_dissonance &dissonance) const
    {
        return less(dissonance)>0;
    }
    
    bool CATSMAT_dissonance::operator<(const CATSMAT::CATSMAT_dissonance &dissonance) const
    {
        return less(dissonance)<0;
    }
    
    int CATSMAT_dissonance::less(const CATSMAT::CATSMAT_dissonance &dissonance) const
    {
        return schemata_.getType()-dissonance.schemata_.getType();
    }
    
    void CATSMAT_dissonance::print(std::ostream &os) const
    {
        string s = schemata::type_strings.at(schemata_.getType());
        string t = schemata_.getBehaviour();
        os << dissonance_ << ", " << duration_ << ", " << s;
    }
    
}



