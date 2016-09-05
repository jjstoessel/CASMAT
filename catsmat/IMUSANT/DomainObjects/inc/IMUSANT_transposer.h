//
//  IMUSANT_transposer.h
//  imusant
//
//  Created by Derrick Hill on 14/08/2016.
//
//

#ifndef imusant_IMUSANT_transposer_h
#define imusant_IMUSANT_transposer_h

#include "IMUSANT_interval.h"
#include "IMUSANT_pitch.h"
#include "smartpointer.h"



namespace IMUSANT
{
    class IMUSANT_transposer : public smartable
    {
    public:
        
        IMUSANT_pitch::TPC transpose(IMUSANT_pitch::TPC the_TPC_to_transpose,
                                     int diatonic,
                                     int chromatic,
                                     int octave_change);
    };
    
    typedef IMUSANT_SMARTP<IMUSANT_transposer> S_IMUSANT_transposer;
    S_IMUSANT_transposer new_IMUSANT_transposer();
}



#endif
