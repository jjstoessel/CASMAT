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
#include <exception>

#define NEW
//#define OLD   //----- This doesn't compile any more.
// #define VERBOSE //----- Print out data structures for testing - use with caution

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
        
        map<S_IMUSANT_score,IMUSANT_collection_visitor> getCollections() const { return collection_visitors; }
        const vector<S_IMUSANT_score> getScores() const { return scores; }
        vector<string> listWorksAndMovements();

        vector<S_IMUSANT_segmented_part_LBDM> findMelodicSegments_LBDM();

        typedef map<S_IMUSANT_score,IMUSANT_collection_visitor> COLLECTIONMAP;
        
    private:
        // One collection visitor for each score. Pointer to score is key
        COLLECTIONMAP collection_visitors;
        void createCollectionVisitorForScore(const S_IMUSANT_score score);

        enum music_file_format {musicxml1, musicxml3, mei, unknown};
        music_file_format decideFileType(const filesystem::path& path);
        S_IMUSANT_score processMusicxml1File(const filesystem::path& path);
        S_IMUSANT_score processMusicxml3File(const filesystem::path& path);
        
        // One score for each file that has been added.
        vector<S_IMUSANT_score> scores;
    };
    
    struct MusicXML1FormatException : public std::exception
    {
        const char * what ()
        {
            return "Invalid file format - MusicXML 1 files shound be converted to MusicXML 3 for processing.";
        }
    };
    
    struct UnknownFormatException : public std::exception
    {
        const char * what ()
        {
            return "Unrecognised file format.";
        }
    };

} //namespace IMUSANT
#endif