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
#include "IMUSANT_repeated_interval_substring.h"

#include "suffixtree.h"

#include <map>
#include <vector>

using namespace std;
using namespace boost;
using namespace ns_suffixtree;

namespace IMUSANT
{

class IMUSANT_processing
{
public:
	IMUSANT_processing() {}
	
	void	process_directory_files(const filesystem::path& full_path);
	void	add_file(const filesystem::path& path);
	string	find_repeated_interval_substrings(int min_length=4);
    vector<IMUSANT_repeated_interval_substring> find_repeated_interval_substrings_2(int min_length=4);
	void	find_repeated_contour_substrings(int min_length=5);
	void	find_repeated_interval_subsequences(int min_length=4);
	void	find_repeated_contour_subsequences(int min_length=5);
	void	find_supermaximals_intervals(int min_length, int min_percent);
	void	find_supermaximals_contours(int min_length, int min_percent);
	void	find_lcs_pairs_intervals(bool consecutive=true);
	void	find_lcs_pairs_intervals_reverse(bool consecutive=true);
	void	find_lcs_pairs_pitches(bool consecutive=true);
	
private:

	map<int,IMUSANT_collection_visitor> processed_files;
	vector<int> IDs;
    
    typedef suffixtree< vector<IMUSANT_interval> > interval_tree;
    interval_tree build_suffix_tree();
    
    
};

} //namespace IMUSANT
#endif