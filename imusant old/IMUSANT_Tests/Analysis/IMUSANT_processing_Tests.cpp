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
    
};


TEST_F(IMUSANT_processing_Tests, find_repeated_interval_substrings)
{
    string relative_path = "IMUSANT_tests.testdata.MusicXMLv1";

    filesystem::path testdata(filesystem::initial_path());
    testdata.append(relative_path);
    
    IMUSANT_processing *the_processor = new IMUSANT_processing();
    
    the_processor->process_directory_files(testdata);
    
    vector<IMUSANT_repeated_interval_substring> repeated_substrings_result;
    repeated_substrings_result = the_processor->find_repeated_interval_substrings();
    
    ASSERT_EQ(48, repeated_substrings_result.size());
    
    stringstream actual_output;
    for(int index = 0 ; index < repeated_substrings_result.size(); index++)
    {
        actual_output << repeated_substrings_result[index];
    }
    
    actual_output << endl;
    
    ASSERT_EQ(FindRepeatedIntervalSubstrings_RefactorTest_Expected, actual_output.str());
}

//TEST_F(IMUSANT_processing_Tests, FindRepeatedRefactor)
//{
//    string relative_path = "IMUSANT_tests.testdata.MusicXMLv1";
//    
//    filesystem::path testdata(filesystem::initial_path());
//    testdata.append(relative_path);
//    // testdata.append("Kyrie.xml");
//    
//    IMUSANT_processing *the_processor = new IMUSANT_processing();
//    
//    vector<IMUSANT_repeated_interval_substring> empty_repeated_substrings_result;
//    empty_repeated_substrings_result = the_processor->find_repeated_interval_substrings_2();
//    
//    ASSERT_EQ(empty_repeated_substrings_result.size(), 0);
//
//    the_processor->process_directory_files(testdata);
//    // the_processor->add_file(testdata);
//    
//    string PRE_repeated_substrings_result;
//    PRE_repeated_substrings_result = the_processor->find_repeated_interval_substrings();
//    
//    vector<IMUSANT_repeated_interval_substring> POST_repeated_substrings_result;
//    POST_repeated_substrings_result = the_processor->find_repeated_interval_substrings_2();
//    
//    ASSERT_EQ(48, POST_repeated_substrings_result.size());
//    
//    stringstream actual_output;
//    for(int index = 0 ; index < POST_repeated_substrings_result.size(); index++)
//    {
//        actual_output << POST_repeated_substrings_result[index];
//    }
//    
//    actual_output << endl;
//    
//    //ASSERT_EQ(FindRepeatedIntervalSubstrings_RefactorTest_Expected, actual_output.str());
//    ASSERT_EQ(actual_output.str(), PRE_repeated_substrings_result);
//    
//}

