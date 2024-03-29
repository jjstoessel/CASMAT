//
//  IMUSNT_test_utilities.cpp
//  imusant
//
//  Created by Derrick Hill on 19/03/2016.
//
//

#include "IMUSANT_test_utilities.h"
#include <boost/filesystem.hpp>

#include <stdlib.h>  // for system()
#include <iostream>
#include <fstream>
#include <string>

#include <math.h>

// #define VERBOSE

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

#ifdef VERBOSE
    cout << "makePathToTestFile() - Path to test data file is: " << testdata.generic_string() << endl;
#endif

    return testdata;
}

void
IMUSANT_test_utilities::
DiffActualAndExpected(string actual, string expected)
{
    // Send the strings to files so that we can use UNIX diff to compare them.
    
    string actual_file_path = GetTempFilePath();
    string expected_file_path = GetTempFilePath();

#ifdef VERBOSE
    cout << "DiffActualAndExpected() - Actual file is: " << actual_file_path << endl;
    cout << "DiffActualAndExpected() - Expected file is: " << expected_file_path << endl;
#endif

    ofstream actual_file(actual_file_path);
    ofstream expected_file(expected_file_path);
    
    actual_file << actual << endl;
    expected_file << expected << endl;
    
    DiffFiles(actual_file_path, expected_file_path);
}

void
IMUSANT_test_utilities::
DiffFiles(string actual_file_path, string expected_file_path)
{
    // Run UNIX diff and send the output to the screen
    string temp_output_file_path = GetTempFilePath();
    
    string command = "diff -a --text " + actual_file_path + " " + expected_file_path + " > " + temp_output_file_path;
    
    ExecuteSystemCommand(command);
    OutputDiffResult(temp_output_file_path);
}

string
IMUSANT_test_utilities::
GetTempFilePath()
{
    string ret_val = tmpnam(nullptr);

#ifdef VERBOSE
    cout << "Temp file is: " << ret_val << endl;
#endif

    return ret_val;
}

void
IMUSANT_test_utilities::
ExecuteSystemCommand(string system_command)
{
    if (! std::system(NULL))
    {
        cerr << "IMUSANT_test_utilities::ExecuteSystemCommand() - system() call not available" << endl;
        throw "IMUSANT_test_utilities::ExecuteSystemCommand() - system() call not available";
    }
    
    int status;

#ifdef VERBOSE
    cout << "System Command: " << system_command.c_str() << endl;
#endif

    status = std::system(system_command.c_str());
    
    if (status < 0)
    {
        cout << "IMUSANT_test_utilities::ExecuteSystemCommand() - Error: " << strerror(errno) << endl;
        throw "IMUSANT_test_utilities::ExecuteSystemCommand() - Error";
    }
    else
    {
        if (! WIFEXITED(status))
        {
            cout << "IMUSANT_test_utilities::ExecuteSystemCommand() - Program exited abnormally\n";
            throw "IMUSANT_test_utilities::ExecuteSystemCommand() - Program exited abnormally";
        }
    }
}

void
IMUSANT_test_utilities::
OutputDiffResult(string temp_output_file_path)
{
    string line;
    ifstream myfile (temp_output_file_path.c_str());
    
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            cout << line << endl;
        }
        myfile.close();
    }
    else
    {
        cout << "IMUSANT_test_utilities::OutputDiffResult() - Unable to open file" << endl;
    }
    cout << endl;
}

bool
IMUSANT_test_utilities::
equalWithinTollerance(float f1, float f2)
{
    return (fabs(f1 - f2) < 0.001);
}

bool
IMUSANT_test_utilities::
checkEqualWithinTolleranceField(double expected, double actual, int index_pos)
{
    if (equalWithinTollerance(expected, actual))
        return true;
    else
    {
        cout << "Failed with jdex = " << index_pos
        << ". Expected " << expected
        << ". Received " << actual
        << endl;
        
        return false;
    }
};

