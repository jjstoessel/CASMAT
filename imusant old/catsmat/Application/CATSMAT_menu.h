//
//  CATSMAT_Menu.h
//  imusant
//
//  Created by Derrick Hill on 6/12/2015.
//
//

#ifndef __imusant__CATSMAT_Menu__
#define __imusant__CATSMAT_Menu__

#include <stdio.h>
#include <vector>
#include <string>
#include "CATSMAT_processing.hpp"
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost;

namespace CATSMAT
{
    
    class CATSMAT_menu
    {
    
    public:
        
        CATSMAT_menu() {};
        
        void outputWelcomeMessage(ostream &out);
        void addFilesToAnalyse(CATSMAT_processing *processor);
        void runToolsMenu(CATSMAT_processing *processor);
        
    private:
        typedef map<int, boost::filesystem::path> index_path_pair;
        
        void addUserSpecifiedFile(CATSMAT_processing *processor);
        void addFilesFromUserSpecifiedDirectory(CATSMAT_processing *processor);
        void addFilesFromFixedConfigFile(CATSMAT_processing *processor);
        void addFilesFromUserSelectedConfigurationFile(CATSMAT_processing *processor);
        
        void listMovementsAddedSoFar(CATSMAT_processing *processor);
        
        boost::filesystem::path getHomeDirectory();
        index_path_pair getConfigurationFiles();
        vector<string> getContentsOfConfigurationFile(boost::filesystem::path path_to_configuration_file);
        void addFilesFromConfigFile(CATSMAT_processing *processor, boost::filesystem::path config_file);
        
        void outputToolsMenu(ostream &out);
        
        const char * HOME_DIR_ENV_VAR_NAME = "HOME";
        const string FIXED_CONFIG_FILE_NAME = "catsmat_config.txt";
        const string CONFIG_FILE_DIR = "catsmat_config";
    };
    
    
    
} //namespace CATSMAT




#endif /* defined(__imusant__CATSMAT_Menu__) */
