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


TEST_F(IMUSANT_processing_Tests, SmokeTest)
{
    string relative_path = "IMUSANT_tests.testdata.MusicXMLv1";

    filesystem::path testdata(filesystem::initial_path());
    testdata.append(relative_path);
    // testdata.append("Kyrie.xml");
    
    IMUSANT_processing *the_processor = new IMUSANT_processing();
    
    the_processor->process_directory_files(testdata);
    // the_processor->add_file(testdata);
    
    string repeated_substrings_result = the_processor->find_repeated_interval_substrings();
    // cout << repeated_substrings_result;
    
    ASSERT_EQ(FindRepeatedIntervalSubstrings_SmokeTest_Expected, repeated_substrings_result);
}

TEST_F(IMUSANT_processing_Tests, FindRepeatedRefactor)
{
    string relative_path = "IMUSANT_tests.testdata.MusicXMLv1";
    
    filesystem::path testdata(filesystem::initial_path());
    testdata.append(relative_path);
    // testdata.append("Kyrie.xml");
    
    IMUSANT_processing *the_processor = new IMUSANT_processing();
    
    vector<IMUSANT_repeated_interval_substring> empty_repeated_substrings_result;
    empty_repeated_substrings_result = the_processor->find_repeated_interval_substrings_2();
    
    ASSERT_EQ(empty_repeated_substrings_result.size(), 0);

    the_processor->process_directory_files(testdata);
    // the_processor->add_file(testdata);
    
    vector<IMUSANT_repeated_interval_substring> repeated_substrings_result;
    repeated_substrings_result = the_processor->find_repeated_interval_substrings_2();
    
    ASSERT_EQ(48, repeated_substrings_result.size());
    
    stringstream actual_output;
    for(int index = 0 ; index < repeated_substrings_result.size(); index++)
    {
        actual_output << repeated_substrings_result[index];
    }
    
    ASSERT_EQ(FindRepeatedIntervalSubstrings_RefactorTest_Expected, actual_output.str());
}

