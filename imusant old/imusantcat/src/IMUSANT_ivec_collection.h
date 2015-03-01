/*
 *  IMUSANT_ivec_collection.h
 *  imusant
 *
 *  Created by Jason Stoessel on 24/06/06.
 *  Copyright 2006 Jason Stoessel. All rights reserved.
 *
 *	This class creates and administers interval vectors.
 */
#ifndef __IMUSANT_IVEC_COLLECTION__
#define __IMUSANT_IVEC_COLLECTION__

#include "smartpointer.h"
#include "IMUSANT_interval_vector.h"

#include <vector>

namespace IMUSANT
{

typedef vector<S_IMUSANT_interval_vector> SEGMENTS;

class IMUSANT_ivec_collection : public SEGMENTS, public smartable
{
	public:
		friend SMARTP<IMUSANT_ivec_collection> new_IMUSANT_ivec_collection(long min, long max);
		
	protected:
				IMUSANT_ivec_collection(long min, long max);
		virtual ~IMUSANT_ivec_collection() {}
	private:
		
		long	fMaximum;
		long	fMinimum;
};
typedef SMARTP<IMUSANT_ivec_collection> S_IMUSANT_ivec_collection;

S_IMUSANT_ivec_collection new_IMUSANT_ivec_collection(long min=3, long max=12);
    
} //namespace IMUSANT
#endif