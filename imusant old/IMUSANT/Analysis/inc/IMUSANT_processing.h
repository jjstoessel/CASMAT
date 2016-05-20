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
//#include "IMUSANT_repeated_interval_substring.h"
#include "IMUSANT_t_repeated_substring.h"
#include "suffixtree.h"
#include <map>
#include <vector>

#define NEW
//#define OLD   //----- This doesn't compile any more.
// #define VERBOSE //----- Print out data structures for testing - use with caution

using namespace std;
using namespace boost;
using namespace ns_suffixtree;

namespace IMUSANT
{
//#ifdef NEW
    //class IMUSANT_repeated_interval_substring : public IMUSANT_t_repeated_substring<IMUSANT_interval> {};
//#endif
    
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
#ifdef OLD
    void	findRepeatedContourSubstrings(int min_length=5);
#endif
#ifdef NEW
    vector<IMUSANT_repeated_contour_substring> findRepeatedContourSubstrings(int min_length=5);
#endif
	void	findSupermaximalsIntervals(int min_length, int min_percent);
	void	findSupermaximalsContours(int min_length, int min_percent);
	void	findLcsPairsIntervals(bool consecutive=true);
	void	findLcsPairsIntervalsReverse(bool consecutive=true);
	void	findLcsPairsPitches(bool consecutive=true);
    vector<S_IMUSANT_segmented_part_LBDM> findMelodicSegments_LBDM();
	
    typedef suffixtree< vector<IMUSANT_interval> >  interval_tree;
    typedef suffixtree< vector<IMUSANT_contour_symbol> > contour_tree;
    
private:
    
    vector<S_IMUSANT_score> scores;                             // One score for each file that has been added.

	map<int,IMUSANT_collection_visitor> collection_visitors;    // One collection visitor for each score.
	vector<int> IDs;                                            // Index into collection_visitors. OLD!
    void createCollectionVisitorForScore(const S_IMUSANT_score score);
    
    
    typedef map<int, vector<IMUSANT_interval> >     ID_ivec_map;
    typedef map<int, vector<IMUSANT_contour_symbol> > ID_cvec_map;
    
    interval_tree*  buildIntervalSuffixTree(ID_ivec_map& id_ivec_map);
    contour_tree*   buildContourSuffixTree(ID_cvec_map& id_cvec_map);
    
    //template<class T> suffixtree< vector<T> >* buildIntervalSuffixTree(map<int, vector<T> >& id_vec_map);
    template<class T> suffixtree< vector<T> >* buildSuffixTree(const map<int, vector<T> >& id_vec_map);
    
    enum music_file_format {imusant, musicxml1, musicxml3, mei, unknown};
    music_file_format decideFileType(const filesystem::path& path);
    
    S_IMUSANT_score processMusicxml1File(const filesystem::path& path);
    S_IMUSANT_score processMusicxml3File(const filesystem::path& path);
    S_IMUSANT_score processImusantFile(const filesystem::path& path);
};



} //namespace IMUSANT
#endif