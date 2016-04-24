//
//  IMUSNT_test_utilities.cpp
//  imusant
//
//  Created by Derrick Hill on 19/03/2016.
//
//

#include "IMUSANT_test_utilities.h"
#include <boost/filesystem.hpp>


S_IMUSANT_score
IMUSANT_test_utilities::
initialiseScoreFromFile(string relative_path)
{
    filesystem::path file_path = makePathToTestFile(relative_path);
    
    IMUSANT_processing parser;
    S_IMUSANT_score parser_test_score = parser.addFile(file_path);
    return parser_test_score;
}


filesystem::path
IMUSANT_test_utilities::
makePathToTestFile(string relative_path_to_test_data_file)
{
    filesystem::path testdata(filesystem::initial_path());
    testdata.append(_root_test_data_dir_name);
    testdata.append(relative_path_to_test_data_file);
    return testdata;
}

