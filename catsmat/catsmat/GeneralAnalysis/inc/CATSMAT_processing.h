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

namespace CATSMAT
{

class CATSMAT_processing : public IMUSANT_processing
{
public:

    CATSMAT_processing() {}
    //relative file and config loaders
    void processRelativeDirectoryFiles(const std::string& directory);
    S_IMUSANT_score addRelativeFile(const std::string& filename);
    void addFilesFromFixedConfigFile();
    void addFilesFromConfigFile(boost::filesystem::path config_file);

    void FindRepeatedDyadSequences(int min=3, bool ignoreDissonances=true, bool ignoreRepeatedDyads=true, bool across=true);
    void FindRepeatedSonoritySequences(int min);
    void FindRepeatedTrigramSequences(int min=3, bool ignoreDissonances=true, bool ignoreRepeatedDyads=true);
    void FindRepeatedTrigramSequencesCanonic(int min=3, bool ignoreDissonances=true, bool ignoreRepeatedDyads=true);
    void FindRepeatedTrigramSequencesEachPair(int min=3, bool ignoreDissonances=true, bool ignoreRepeatedDyads=true);
    void FindRepeatedTrigramSequencesThreeVoices(int min=3, bool ignoreDissonances=true, bool ignoreRepeatedDyads=true);
    void FindTrigramCounts(bool ignoreDissonances, bool ignoreRepeatedDyads);
    void FindSummativeTrigramCounts(bool ignoreDissonances, bool ignoreRepeatedDyads);
    void FindSummativeTrigramCountsByPart(bool ignoreDissonances, bool ignoreRepeatedDyads);
    void FindMelodicDirectionCounts();
    void FindMelodicDirectionDupleCounts();
    void FindPitchIntervalCounts();
    void ListCanonicTechniques();
private:
    typedef std::map<int, boost::filesystem::path> index_path_pair;

    //utility
    boost::filesystem::path getHomeDirectory();

    //config file handlers
    index_path_pair getConfigurationFiles();
    std::vector<std::string> getContentsOfConfigurationFile(boost::filesystem::path path_to_configuration_file);

    const char * HOME_DIR_ENV_VAR_NAME = "HOME";
    const std::string FIXED_CONFIG_FILE_NAME = "catsmat_config.txt";
    const std::string CONFIG_FILE_DIR = "catsmat_config";

};

    
    
} //namespace CATSMAT
#endif //__CATSMAT_PROCESSING__
