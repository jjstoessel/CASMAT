/*
 *  IMUSANT_rvec_collection.cpp
 *  imusant
 *
 *  Created by Jason Stoessel on 27/06/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "IMUSANT_rvec_collection.h"

namespace IMUSANT
{

S_IMUSANT_rvec_collection new_IMUSANT_rvec_collection() 
{ IMUSANT_rvec_collection* o = new IMUSANT_rvec_collection(); assert (o!=0); return o; }

}//namespace IMUSANT