//
//  IMUSANT_converters_shared_types.h
//  imusant
//
//  Created by Derrick Hill on 26/09/2015.
//
//

#ifndef imusant_IMUSANT_converters_shared_types_h
#define imusant_IMUSANT_converters_shared_types_h

#include "IMUSANT_pitch.h"
#include "IMUSANT_types.h"  // for IMUSANT_accidental

using namespace IMUSANT;

//type for collection of pitch/octave pair with accidental type
typedef map<pair<IMUSANT_pitch::type,unsigned short>,IMUSANT_accidental::accident> ACCIDENTALMAP;



#endif
