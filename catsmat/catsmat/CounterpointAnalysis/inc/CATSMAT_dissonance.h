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
#include "smartpointer.h"
#include "IMUSANT_interval.h"
#include "IMUSANT_duration.h"

using namespace IMUSANT;

namespace CATSMAT
{
    class CATSMAT_dissonance : public IMUSANT_interval
    {
    public:
        enum schemata {
            unclassified,
            upper_passing_tone,
            lower_passing_tone,
            upper_neighbour_tone,
            lower_neighbour_tone,
            suspension, //accented
            ritardation, //unaccented
            cambiata,
            escape_tone,
            pedal_point,
            unknown,
        };
        
        CATSMAT_dissonance();
        ~CATSMAT_dissonance();
        
        const IMUSANT_duration& getDuration() { return duration_; }
        const schemata  getSchemata() { return schemata_; }
        
        //override compare function
        int                 compare(const CATSMAT_dissonance& i) const;
    private:
        
        IMUSANT_duration    duration_;
        schemata            schemata_ = unclassified;
    };
    
    using S_CATSMAT_dissonance = IMUSANT_SMARTP<CATSMAT_dissonance>;

}//namespace CATSMAT
#endif /* CATSMAT_dissonance_h */
