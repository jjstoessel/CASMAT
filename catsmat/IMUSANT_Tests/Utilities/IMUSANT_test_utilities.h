//
//  IMUSNT_test_utilities.h
//  imusant
//
//  Created by Derrick Hill on 19/03/2016.
//
//

#ifndef __imusant__IMUSANT_test_utilities__
#define __imusant__IMUSANT_test_utilities__

#include <stdio.h>
#include <boost/filesystem.hpp>
#include "libIMUSANT.h"


using namespace IMUSANT;

class VEXP IMUSANT_test_utilities
{
public:
    
    IMUSANT_test_utilities(string root_test_data_dir_name)
    {
        _root_test_data_dir_name = root_test_data_dir_name;
    }
    
    S_IMUSANT_score initialiseScoreFromFile(string relative_path);
    filesystem::path makePathToTestFile(string relative_path_to_test_data_file);

    void DiffActualAndExpected(string actual, string expected);
    
private:
    string GetTempFilePath();
    void DiffFiles(string file1, string file2 );
    void ExecuteSystemCommand(string system_command);
    void OutputDiffResult(string temp_output_file_path);
    
    string _root_test_data_dir_name;
    
};

#endif /* defined(__imusant__IMUSANT_test_utilities__) */
