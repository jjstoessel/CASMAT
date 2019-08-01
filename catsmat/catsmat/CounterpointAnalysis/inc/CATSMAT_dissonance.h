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
#include <map>
#include <utility>
#include <functional>

#include "smartpointer.h"
#include "IMUSANT_interval.h"
#include "IMUSANT_note.h"

using namespace IMUSANT;

namespace CATSMAT
{
    class CATSMAT_dissonance : public smartable
    {
    public:
        class schemata
        {
        public:
            enum type: int {
                unclassified,               
                ascending_passing_tone,     //unaccented, melodic upper 1, 1, lower 0,*
                descending_passing_tone,    //unaccented, melodic upper -1, -1, lower 0,*
                upper_neighbour_tone,       //unaccented, melodic upper 1,-1, lower 0,*
                lower_neighbour_tone,       //unaccented, melodic upper -1, 1, lower 0,*
                incomplete_upper_neighbour_tone,  //unaccented, melodic upper >1, -1, lower 0,*
                incomplete_lower_neighbour_tone,  //unaccented, melodic upper <-1, 1, lower 0,*
                appoggiatura,               //accented, melodic upper *, -1, lower *,0; includes acciaccatura (which is a shorted accented dissonance)
                suspension,                 //accented, melodic upper 0, -1, lower -1, 0 (P,S,R); is also an anticipation but the syncopated noted is struck again on the accent
                anticipation,               //unaccented suspension, without syncopation; unimpletemented - reserved for future enhancements
                retardation,                //accented, melodic upper 0, 1, lower, -1, 0 (P,S,R)
                cambiata,                 //unaccented, melodic upper -1,-2,1, lower 0,0,* ; dissonance always second element
                cambiata_i,                 //unaccented, melodic upper 1,2,-1, lower 0,0,*
                upper_escape_tone,          //unaccented, melodic upper 1,<-1, lower 0, *
                lower_escape_tone,          //unaccented, melodic upper -1,>1, lower 0, *
                pedal_point                 //varies, melodic, *,*,*, lower is static
            };
            
            static const std::map<type,std::string> type_strings;
            
            enum b_index : int {
                up_mel_to, up_mel_from, low_mel_to, low_mel_from
            };
            
            using behaviour_array = std::array<int,6>;
            using eval_function_ = std::function<bool(const behaviour_array&, const bool)>;
            static const std::map<type, eval_function_> behaviours_;
            
            schemata() {}
            schemata(int up_mel_to, int up_mel_from, int low_mel_to, int low_mel_from, bool accented);
            schemata(int up_intermed, int up_mel_to, int up_mel_from, int low_intermed, int low_mel_to, int low_mel_from, bool accented); //cambiata only
            
            void set(int up_mel_to, int up_mel_from, int low_mel_to, int low_mel_from, bool accented);
            void set(int up_intermed, int up_mel_to, int up_mel_from, int low_intermed, int low_mel_to, int low_mel_from, bool accented);
            
            type getType() const { return type_; }
            bool getAccented() { return accented_; }
            
            bool operator== (const schemata& rhs) const { return equal(rhs); }
            bool operator!= (const schemata& rhs) const { return equal(rhs)==false; }
            bool equal(const schemata& rhs) const;
            
        private:
            behaviour_array behaviour_ = {0,0,0,0,0,0}; //initialise as a vector of four elements
            bool        accented_ = false;
            type        type_ = unclassified;
            
            static const type find_type(const behaviour_array& behaviour, const bool accented); //determine type based upon initialisers
            
        };
        
        CATSMAT_dissonance();
        CATSMAT_dissonance(IMUSANT_note& u1, IMUSANT_note& l1,
                           IMUSANT_note& u2, IMUSANT_note& l2,
                           IMUSANT_note& u3, IMUSANT_note& l3,
                           bool accented = false);
        CATSMAT_dissonance(IMUSANT_note& u1, IMUSANT_note& l1,
                           IMUSANT_note& u2, IMUSANT_note& l2,
                           IMUSANT_note& u3, IMUSANT_note& l3,
                           IMUSANT_note& u4, IMUSANT_note& l4,
                           bool accented = false);
        ~CATSMAT_dissonance();
        
        void SetSchemata(IMUSANT_note& u1, IMUSANT_note& l1,
                         IMUSANT_note& u2, IMUSANT_note& l2,
                         IMUSANT_note& u3, IMUSANT_note& l3,
                         bool accented);
        void SetSchemata(IMUSANT_note& u1, IMUSANT_note& l1,
                         IMUSANT_note& u2, IMUSANT_note& l2,
                         IMUSANT_note& u3, IMUSANT_note& l3,
                         IMUSANT_note& u4, IMUSANT_note& l4,
                         bool accented);
        
        const IMUSANT_duration& getDuration() { return duration_; }
        const IMUSANT_interval& getInterval() { return dissonance_; }
        const schemata&  getSchemata() { return schemata_; }
        
        //operators
        CATSMAT_dissonance& operator= (const CATSMAT_dissonance& dissonance);
        bool operator== (const CATSMAT_dissonance& dissonance) const;
        bool operator!= (const CATSMAT_dissonance& dissonance) const;
        bool equal(const CATSMAT_dissonance& dissonance) const;
        // "greater than" is interpreted to mean
        bool operator> (const CATSMAT_dissonance& dissonance) const;
        bool operator< (const CATSMAT_dissonance& dissonance) const;
        int  less(const CATSMAT_dissonance& dissonance) const;
        //output
        friend ostream& operator<< (ostream& os, const CATSMAT_dissonance& elt );
        void    print (ostream& os) const;
        
    private:
        
        IMUSANT_interval    dissonance_;
        IMUSANT_duration    duration_;
        schemata            schemata_;
    };
    
    using S_CATSMAT_dissonance = IMUSANT_SMARTP<CATSMAT_dissonance>;
    
    ostream& operator<< (ostream& os, const CATSMAT_dissonance& elt );

    template<typename T>
    inline void swap_less(T &x, T &y)
    {
        if (x<y)
        {
            T tmp = x;
            x = y; y = tmp;
        }
    }
}//namespace CATSMAT
#endif /* CATSMAT_dissonance_h */
