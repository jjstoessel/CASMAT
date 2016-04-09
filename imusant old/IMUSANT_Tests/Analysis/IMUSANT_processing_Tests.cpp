//
//  IMUSANT_processing_Tests.cpp
//  imusant
//
//  Created by Derrick Hill on 9/08/2015.
//
//

#include "IMUSANT_processing_Expected.h"

#include <stdio.h>

#include "gtest/gtest.h"

#include "libIMUSANT.h"
#include <boost/filesystem.hpp>

#define VERBOSE //toggle for verbose output

using namespace IMUSANT;
using namespace boost;

// The fixture for testing class IMUSANT_pitch.
class IMUSANT_processing_Tests : public ::testing::Test {
    
protected:
    
    IMUSANT_processing_Tests()
    {
        // You can do set-up work for each test here.
    }
    
    virtual ~IMUSANT_processing_Tests()
    {
        // You can do clean-up work that doesn't throw exceptions here.
    }
    
    vector<IMUSANT_repeated_interval_substring> find_repeated_substrings_by_file(string path_to_test_data_file);
    vector<IMUSANT_repeated_interval_substring> find_repeated_substrings_by_directory(string path_to_test_data_directory);
    
    filesystem::path make_path_to_test_file(string relative_path_to_test_data_file);
  
};


filesystem::path
IMUSANT_processing_Tests::
make_path_to_test_file(string relative_path_to_test_data_file)
{
    filesystem::path testdata(filesystem::initial_path());
    testdata.append("IMUSANT_testdata");
    testdata.append(relative_path_to_test_data_file);
    return testdata;
}


vector<IMUSANT_repeated_interval_substring>
IMUSANT_processing_Tests::
find_repeated_substrings_by_file(string relative_path_to_test_data_file)
{
    filesystem::path testdata = make_path_to_test_file(relative_path_to_test_data_file);
    
    filesystem::file_status status = filesystem::status(testdata);
    if (!filesystem::exists(status))
    {
        cerr << "Can't find the test data file at " <<  relative_path_to_test_data_file << endl;
        throw("File not found: " + relative_path_to_test_data_file) ;
    }
    
    if (!filesystem::is_regular_file(status))
    {
        cerr << "This path is not a file: " <<  relative_path_to_test_data_file << endl;
        throw("Not a file: " + relative_path_to_test_data_file) ;
    }
    
    IMUSANT_processing *the_processor = new IMUSANT_processing();
    
    the_processor->add_file(testdata);
    
    vector<IMUSANT_repeated_interval_substring> repeated_substrings_result;
    repeated_substrings_result = the_processor->find_repeated_interval_substrings();
    
    return repeated_substrings_result;
}

vector<IMUSANT_repeated_interval_substring>
IMUSANT_processing_Tests::
find_repeated_substrings_by_directory(string relative_path_to_test_data_directory)
{
    filesystem::path testdata(filesystem::initial_path());
    testdata.append("IMUSANT_testdata");
    testdata.append(relative_path_to_test_data_directory);
    
    filesystem::file_status status = filesystem::status(testdata);
    if (!filesystem::exists(status))
    {
        cerr << "Problem with the test data at " <<  relative_path_to_test_data_directory << endl;
        throw("File not found: " + relative_path_to_test_data_directory) ;
    }
    
    if (!filesystem::is_directory(status))
    {
        cerr << "This path is not a directory: " <<  relative_path_to_test_data_directory << endl;
        throw("Not a directory: " + relative_path_to_test_data_directory) ;
    }
    
    IMUSANT_processing *the_processor = new IMUSANT_processing();
    
    the_processor->process_directory_files(testdata);
    
    vector<IMUSANT_repeated_interval_substring> repeated_substrings_result;
    repeated_substrings_result = the_processor->find_repeated_interval_substrings();
    
    return repeated_substrings_result;
}


// ************* TEST CASES START HERE *********** //


TEST_F(IMUSANT_processing_Tests, find_repeated_interval_substrings_simple_test_1)
{
    vector<IMUSANT_repeated_interval_substring> repeated_substrings_result;
    //repeated_substrings_result = find_repeated_substrings_by_file("/MusicXMLv3.simple_test_data/RepeatedIntervalSubstrings_SimpleTest1.xml");
    repeated_substrings_result = find_repeated_substrings_by_file("/RepeatedIntervalSubstrings_SimpleTest1.xml");

    // REVISIT - remove this output once we have resolved "D-01021" - "https://www52.v1host.com/Private63/defect.mvc/Summary?oidToken=Defect%3A2543"
#ifdef VERBOSE
    stringstream actual_output;
    actual_output << IMUSANT_repeated_interval_substring::output_operator_help();
    
    for(int index = 0 ; index < repeated_substrings_result.size(); index++)
    {
        actual_output << repeated_substrings_result[index];
    }
   
    actual_output << endl;

    cout << actual_output.str();
#endif
    
    ASSERT_FALSE(true) << "Repeated Interval Substrings should not span different parts? - Deliberatly failing test (WIP)";
}


TEST_F(IMUSANT_processing_Tests, find_repeated_interval_substrings_from_v1_directory)
{
//    vector<IMUSANT_repeated_interval_substring> repeated_substrings_result;
//    repeated_substrings_result = find_repeated_substrings_by_directory("MusicXMLv1.simple_test_data");
//    
//    ASSERT_EQ(48, repeated_substrings_result.size());
//    
//    stringstream actual_output;
//    for(int index = 0 ; index < repeated_substrings_result.size(); index++)
//    {
//        actual_output << repeated_substrings_result[index];
//    }
//    
//    actual_output << endl;
//    
//    //    cout << actual_output.str();
//    //    cout << FindRepeatedIntervalSubstrings_RefactorTest_Expected;
//    
//    ASSERT_EQ(FindRepeatedIntervalSubstrings_RefactorTest_Expected, actual_output.str());
    ASSERT_TRUE(false) << "Deliberatly failing this test.  See D-01025 in VersionOne.";
}

TEST_F(IMUSANT_processing_Tests, compare_v1_and_v3_repeated_substring_processing)
{
//    vector<IMUSANT_repeated_interval_substring> v1_repeated_substrings_result;
//    v1_repeated_substrings_result = find_repeated_substrings_by_file("test_files/MusicXMLv1/Josquin_MSN_Kyrie.xml");
//    
//    vector<IMUSANT_repeated_interval_substring> v3_repeated_substrings_result;
//    v3_repeated_substrings_result = find_repeated_substrings_by_file("test_files/MusicXMLv3/Josquin_MSN_Kyrie_v3_exported_from_v1.xml");
//    
//    ASSERT_EQ(v1_repeated_substrings_result.size(), v3_repeated_substrings_result.size())  << "EXPECTED FAILURE - Output vectors are not the same length.";
//  
//    stringstream v1_actual_output;
//    stringstream v3_actual_output;
//    
//    for(int index = 0 ; index < v1_repeated_substrings_result.size(); index++)
//    {
//        v1_actual_output << v1_repeated_substrings_result[index];
//    }
//    
//    for(int index = 0 ; index < v3_repeated_substrings_result.size(); index++)
//    {
//        v3_actual_output << v3_repeated_substrings_result[index];
//    }
//    
//    ASSERT_EQ(v1_actual_output.str(), v3_actual_output.str()) << "Output strings are not identical.";
    
    //cout << "V1 ACTUAL:" << endl << v1_actual_output.str() << endl;
    //cout << endl;
    //cout << "V3 ACTUAL:" << endl << v3_actual_output.str() << endl;
    
        ASSERT_TRUE(false) << "Deliberatly failing this test.  See D-01025 in VersionOne.";
}

TEST_F(IMUSANT_processing_Tests, FindRepeatedIntervalSubstrings_Telemann_mxml3)
{
    // This is a fairly complex file so I'm including a very rough test
    // here just to make sure that the parser covers it.

//    string relative_path = "MusicXMLv3.xmlsamples/Telemann.xml";
//    vector<IMUSANT_repeated_interval_substring> repeated_substrings_result;
//    repeated_substrings_result = find_repeated_substrings_by_file(relative_path);
//    
//    ASSERT_EQ(299, repeated_substrings_result.size());
    
            ASSERT_TRUE(false) << "Deliberatly failing this test.  See D-01025 in VersionOne.";
}



