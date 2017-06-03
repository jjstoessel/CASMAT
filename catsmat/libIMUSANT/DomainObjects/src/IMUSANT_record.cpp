/*
 *  IMUSANT_record.cpp
 *  imusant
 *
 *  Created by Jason Stoessel on 24/06/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "IMUSANT_record.h"

namespace IMUSANT
{

S_IMUSANT_record new_IMUSANT_record() { IMUSANT_record* o = new IMUSANT_record(); assert (o!=0); return o; }

}//namespace IMUSANT