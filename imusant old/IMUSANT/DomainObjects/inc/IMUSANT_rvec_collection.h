/*
 *  IMUSANT_rvec_collection.h
 *  imusant
 *
 *  Created by Jason Stoessel on 27/06/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __IMUSANT_RVEC_COLLECTION__
#define __IMUSANT_RVEC_COLLECTION__

#include "smartpointer.h"

#include <vector>

namespace IMUSANT
{

class IMUSANT_rvec_collection : public smartable
{
	public:
		friend IMUSANT_SMARTP<IMUSANT_rvec_collection> new_IMUSANT_rvec_collection();
		
	protected:
				IMUSANT_rvec_collection(){}
		virtual ~IMUSANT_rvec_collection() {}
		
	private:
};
typedef IMUSANT_SMARTP<IMUSANT_rvec_collection> S_IMUSANT_rvec_collection;

S_IMUSANT_rvec_collection new_IMUSANT_rvec_collection();

} //namespace IMUSANT
#endif