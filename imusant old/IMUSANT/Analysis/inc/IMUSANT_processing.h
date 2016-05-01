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

#include "IMUSANT_score.h"
#include "IMUSANT_collectionvisitor.h"
#include "IMUSANT_segmented_part_LBDM.h"
#include "IMUSANT_repeated_interval_substring.h"
#include "suffixtree.h"
#include <map>
#include <vector>

#define NEW
// #define OLD   ----- This doesn't compile any more.

using namespace std;
using namespace boost;
using namespace ns_suffixtree;

namespace IMUSANT
{

class IMUSANT_processing
{
public:
	IMUSANT_processing() {}
	
	void	processDirectoryFiles(const filesystem::path& full_path);
	S_IMUSANT_score	addFile(const filesystem::path& path);
    
    const vector<S_IMUSANT_score> getScores() { return scores; }
    vector<string> listWorksAndMovements();
    
	string	findAndPrintRepeatedIntervalSubstrings(int min_length=4);
    vector<IMUSANT_repeated_interval_substring> findRepeatedIntervalSubstrings(int min_length=4);
	void	findRepeatedContourSubstrings(int min_length=5);
	void	findSupermaximalsIntervals(int min_length, int min_percent);
	void	findSupermaximalsContours(int min_length, int min_percent);
	void	findLcsPairsIntervals(bool consecutive=true);
	void	findLcsPairsIntervalsReverse(bool consecutive=true);
	void	findLcsPairsPitches(bool consecutive=true);
    vector<S_IMUSANT_segmented_part_LBDM> findMelodicSegments_LBDM();
	
private:
    
    vector<S_IMUSANT_score> scores;                             // One score for each file that has been added.

	map<int,IMUSANT_collection_visitor> collection_visitors;    // One collection visditor for each score.
	vector<int> IDs;                                            // Index into collection_visitors.
    void createCollectionVisitorForScore(const S_IMUSANT_score score);
    
    typedef suffixtree< vector<IMUSANT_interval> > interval_tree;
    
#ifdef OLD
    interval_tree buildSuffixTree();
#endif
#ifdef NEW
    interval_tree* buildIntervalSuffixTree();
#endif
    
    enum music_file_format {imusant, musicxml1, musicxml3, mei, unknown};
    music_file_format decideFileType(const filesystem::path& path);
    
    S_IMUSANT_score processMusicxml1File(const filesystem::path& path);
    S_IMUSANT_score processMusicxml3File(const filesystem::path& path);
    S_IMUSANT_score processImusantFile(const filesystem::path& path);
};

} //namespace IMUSANT
#endif