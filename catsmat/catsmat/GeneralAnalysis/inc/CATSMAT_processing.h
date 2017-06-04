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
#include "CATSMAT_collectionvisitor.h"


using namespace IMUSANT;
using namespace std;
using namespace boost;

namespace CATSMAT
{

class CATSMAT_processing : public IMUSANT_processing
{
public:

    CATSMAT_processing() {}
    
    void FindRepeatedDyadSequences(int min=3, bool ignoreDissonances=true, bool ignoreRepeatedDyads=true, bool across=true);
    void FindRepeatedDyadtupleSequences(int min);
    void FindRepeatedSonoritySequences(int min);
    void FindRepeatedTrigramSequences(int min=3, bool ignoreDissonances=true, bool ignoreRepeatedDyads=true);
    void FindRepeatedTrigramSequencesCanonic(int min=3, bool ignoreDissonances=true, bool ignoreRepeatedDyads=true);
    void FindTrigramCounts(bool ignoreDissonances, bool ignoreRepeatedDyads);
    void FindSummativeTrigramCounts(bool ignoreDissonances, bool ignoreRepeatedDyads);
    void FindMelodicDirectionCounts();
    void FindMelodicDirectionDupleCounts();
    void ListCanonicTechniques();
private:


};

    
    
} //namespace CATSMAT
#endif //__CATSMAT_PROCESSING__