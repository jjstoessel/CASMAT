//
//  IMUSANT_transposer.cpp
//  catsmat
//
//  Created by Derrick Hill on 3/09/2016.
//
//

#include <stdio.h>

#include "IMUSANT_transposer.h"

namespace IMUSANT
{
    
    struct ic_2_tic
    {
    public:
        ic_2_tic(int ic, IMUSANT_interval::interval_type tic)
        :
        IC(ic),
        TIC(tic)
        {}
        
        int IC;
        IMUSANT_interval::interval_type TIC;
    };
    
    static const int NUM_TICS = 13;
    
    const ic_2_tic ic_2_tic_table[NUM_TICS] =
    {
        ic_2_tic(0, IMUSANT_interval::per1),
        ic_2_tic(1, IMUSANT_interval::min2),
        ic_2_tic(2, IMUSANT_interval::maj2),
        ic_2_tic(3, IMUSANT_interval::min3),
        ic_2_tic(4, IMUSANT_interval::maj3),
        ic_2_tic(5, IMUSANT_interval::per4),
        ic_2_tic(6, IMUSANT_interval::dim5),
        ic_2_tic(7, IMUSANT_interval::per5),
        ic_2_tic(8, IMUSANT_interval::min6),
        ic_2_tic(9, IMUSANT_interval::maj6),
        ic_2_tic(10, IMUSANT_interval::min7),
        ic_2_tic(11, IMUSANT_interval::maj7),
        ic_2_tic(12, IMUSANT_interval::per1)
    };
    
    IMUSANT_pitch::TPC
    IMUSANT_transposer::
    transpose(IMUSANT_pitch::TPC the_TPC_to_transpose,
              int diatonic,
              int chromatic,
              int octave_change)
    {
        int direction_of_transposition;
        (chromatic < 0) ? direction_of_transposition = -1 : direction_of_transposition = 1;
        
        IMUSANT_interval::interval_type tonal_interval_class = ic_2_tic_table[abs(chromatic)].TIC;
        
        const int tonal_interval_class_int = static_cast<int>(tonal_interval_class);
        
        int calculated_tonal_pitch_class = (the_TPC_to_transpose + (tonal_interval_class_int * direction_of_transposition)) ;
        
        IMUSANT_pitch::TPC ret_val = static_cast<IMUSANT_pitch::TPC>(calculated_tonal_pitch_class);
        
        return ret_val;
    };
    
    
    S_IMUSANT_transposer new_IMUSANT_transposer()
    {
        IMUSANT_transposer * o = new IMUSANT_transposer();
        assert(o!=0);
        return o;
    }
    
}