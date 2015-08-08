/*
 *  IMUSANT_processing.h
 *  imusant
 *
 *  Created by Jason Stoessel on 26/07/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __IMUSANT_PROCESSING__
#define __IMUSANT_PROCESSING__

#include <boost/filesystem.hpp>

#include "IMUSANT_collectionvisitor.h"

#include <map>
#include <vector>

using namespace std;
using namespace boost;

namespace IMUSANT
{

class IMUSANT_processing
{
public:
	IMUSANT_processing() {}
	
	void	process_directory_files(const filesystem::path& full_path);
	void	add_file(const filesystem::path& path);
	void	find_repeated_interval_substrings(int min_length=4);
	void	find_repeated_contour_substrings(int min_length=5);
	void	find_repeated_interval_subsequences(int min_length=4);
	void	find_repeated_contour_subsequences(int min_length=5);
	void	find_supermaximals_intervals(int min_length, int min_percent);
	void	find_supermaximals_contours(int min_length, int min_percent);
	void	find_lcs_pairs_intervals(bool consecutive=true);
	void	find_lcs_pairs_intervals_reverse(bool consecutive=true);
	void	find_lcs_pairs_pitches(bool consecutive=true);
	
private:

	map<int,IMUSANT_collection_visitor> collections;
	vector<int> IDs;
};

} //namespace IMUSANT
#endif