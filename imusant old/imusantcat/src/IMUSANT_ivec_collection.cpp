/*
 *  IMUSANT_ivec_collection.cpp
 *  imusant
 *
 *  Created by Jason Stoessel on 24/06/06.
 *  Copyright 2006 Jason Stoessel. All rights reserved.
 *
 */

#include "IMUSANT_ivec_collection.h"

namespace IMUSANT
{

S_IMUSANT_ivec_collection new_IMUSANT_ivec_collection(long min, long max) 
{ IMUSANT_ivec_collection* o = new IMUSANT_ivec_collection(min, max); assert(o!=0); return o; }

IMUSANT_ivec_collection::IMUSANT_ivec_collection(long min, long max)
{
	fMinimum = min;
	fMaximum = max;
	//fBuffer = new_IMUSANT_interval_vector();
}

}//namespace IMUSANT