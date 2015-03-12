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

#include <map>
#include <vector>

using namespace std;
using namespace boost;

namespace CATSMAT
{

class CATSMAT_processing : public IMUSANT_processing
{
public:
	CATSMAT_processing() {}
	
	void	process_directory_files(const filesystem::path& full_path);
	void	add_file(const filesystem::path& path);
	
private:

	map<int,CATSMAT_collection_visitor> collections;
	vector<int> IDs;
};

} //namespace IMUSANT
#endif //__CATSMAT_PROCESSING__