//
//  CATSMAT_dissonance_type.hpp
//  catsmat
//
//  Created by Jason Stoessel on 7/7/19.
//
//  CATSMAT_dissonance_type permits dissonances to be classified according to their schemata type, i.e.
//
//  passing tone (upper and lower), metrically weak, short
//  neighbour tone (upper and lower), metrically weak, short
//  appoggiatura, metrically strong (possible also to distinguish the shorter acciaccatura later)
//  suspension, metrically strong S, steps down to dissonance, PSR; longer
//  retardation, i.e. "fake" suspension, metrically weak, steps up to dissonance, longer
//  escape tone/echappée, step to weak dissonance, leap to consonance, short
//  cambiata - two successive dissonances with consonances on either side - lower priority
//  pedal point - sustained lower tone
//  unknown - dissonance whose behaviour cannot be classified as one of the above types

#ifndef CATSMAT_dissonance_h
#define CATSMAT_dissonance_h

#include <stdio.h>
#include <array>

#include "smartpointer.h"
#include "IMUSANT_interval.h"
#include "IMUSANT_note.h"

using namespace IMUSANT;


namespace CATSMAT
{
    class CATSMAT_dissonance : public IMUSANT_interval
    {
    public:
        enum schemata : int {
            unclassified,               //0,0,0,0
            ascending_passing_tone,     //unaccented, melodic upper 1, 1, lower 0,*
            descending_passing_tone,    //unaccented, melodic upper -1, -1, lower 0,*
            upper_neighbour_tone,       //unaccented, melodic upper 1,-1, lower 0,*
            lower_neighbour_tone,       //unaccented, melodic upper -1, 1, lower 0,*
            incomplete_lower_neighbour_tone,  //unaccented, melodic upper <-1, 1, lower 0,*
            incomplete_upper_neighbour_tone,  //unaccended, melodic upper >1, -1, lower 0,*
            anticipation,               //unaccented, melodic upper, -1, 0, lower 0,* NB. consonance anticipations
            appoggiatura,               //accented, melodic upper *, -1, lower *,0
            acciaccatura,               //accented, melodic upper *, -1, lower *,0, dissonance is shorter than appoggiatura
            suspension,                 //accented, melodic upper 0, -1, lower -1, 0 (P,S,R)
            retardation,                //accented, melodic upper 0, 1, lower, -1, 0 (P,S,R)
            cambiata_w,                 //unaccented, melodic upper -1,2,-1, lower 0,0,*
            cambiata_m,                 //unaccented, melodic upper 1,-2, 1, lower 0,0,*
            upper_escape_tone,          //unaccented, melodic upper 1,<-1, lower 0, *
            lower_escape_tone,          //unaccented, melodic upper -1,>1, lower 0, *
            pedal_point,                //varies, melodic, *,*,*, lower is static
            unknown                     //none of the above
        };
        
        //templates for each schemata behaviour, i.e. upper/lower melodies.
        
        using quingram = std::array<int,5>;
        enum  quingram_elt : int { dyad1, dyad2, dyad3, lower_mel1, lowermel2 };
        
        CATSMAT_dissonance();
        ~CATSMAT_dissonance();
        
        void Calculate(IMUSANT_note& u1, IMUSANT_note& l1,
                       IMUSANT_note& u2, IMUSANT_note& l2,
                       IMUSANT_note& u3, IMUSANT_note& l3);
        
        const IMUSANT_duration& getDuration() { return duration_; }
        const schemata  getSchemata() { return schemata_; }
        
        //override compare function
        int                 compare(const CATSMAT_dissonance& i) const;
    private:
        
        IMUSANT_duration    duration_;
        schemata            schemata_ = unclassified;
        quingram            quingram_;
    };
    
    using S_CATSMAT_dissonance = IMUSANT_SMARTP<CATSMAT_dissonance>;

}//namespace CATSMAT
#endif /* CATSMAT_dissonance_h */
