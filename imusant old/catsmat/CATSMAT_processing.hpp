/*
 *  IMUSANT_processing.h
 *  imusant
 *
 *  Created by Jason Stoessel on 26/07/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __CATSMAT_PROCESSING__
#define __CATSMAT_PROCESSING__

#include <boost/filesystem.hpp>

#include "IMUSANT_processing.h"
#include "CATSMAT_collectionvisitor.hpp"

using namespace IMUSANT;
using namespace std;
using namespace boost;

namespace CATSMAT
{

class CATSMAT_processing : public IMUSANT_processing
{
public:

    CATSMAT_processing() {}
    
    void find_repeated_dyad_sequences(int min=3);
    void find_repeated_dyadtuple_sequences(int min);
    void find_repeated_sonority_sequences(int min);
	
private:


};

} //namespace CATSMAT
#endif //__CATSMAT_PROCESSING__