//
//  CATSMAT_scoredatacollector_tests.cpp
//  catsmat
//
//  Created by Jason Stoessel on 7/10/2016.
//
//

#include "CATSMAT_scoredatacollector_tests.h"

#include <stdio.h>

#include "CATSMAT_scoredatacollector.h"

#include "CATSMAT_test_utility.h"

#include "gtest/gtest.h"
#include <boost/filesystem.hpp>

using namespace boost;

// The fixture for testing class CATSMAT_cp_matrix.
class CATSMAT_scoredatacollector_tests : public ::testing::Test {
    
protected:
    
    CATSMAT_scoredatacollector_tests() {
        // You can do set-up work for each test here.
    }
    
    virtual ~CATSMAT_scoredatacollector_tests() {
        // You can do clean-up work that doesn't throw exceptions here.
    }
    
    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:
    
    virtual void SetUp() {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }
    
    virtual void TearDown() {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }
    
    // Objects declared here can be used by all tests in the test case for CATSMAT_cp_matrix_Test.
    CATSMAT_test_utility testUtil;
    
};

TEST_F(CATSMAT_scoredatacollector_tests, TestScore_1_Measure) {
    
    CATSMAT_processing *the_processor = new CATSMAT_processing();
    CATSMAT_scoredatacollector scoredatacollection;
    filesystem::path testdata = testUtil.MakePathToTestData("TestScore_1_Measure.xml");
    the_processor->addFile(testdata);
    
    scoredatacollection.Visit(*the_processor);

    ostringstream the_score_data_as_string;
    the_score_data_as_string << scoredatacollection;
    ASSERT_EQ(TestScore_1_Measure_Expected, the_score_data_as_string.str());
}

TEST_F(CATSMAT_scoredatacollector_tests, TestScore_4_Measures) {
    
    CATSMAT_processing *the_processor = new CATSMAT_processing();
    CATSMAT_scoredatacollector scoredatacollection;
    filesystem::path testdata = testUtil.MakePathToTestData("TestScore_4_Measures.xml");
    
    the_processor->addFile(testdata);
    
    scoredatacollection.Visit(*the_processor);
    
    ostringstream the_score_data_as_string;
    the_score_data_as_string << scoredatacollection;
    ASSERT_EQ(TestScore_4_Measures_Expected, the_score_data_as_string.str());
}

TEST_F(CATSMAT_scoredatacollector_tests, TestScore_4_Measures_WithQuaverPassingNotes) {
    
    CATSMAT_processing *the_processor = new CATSMAT_processing();
    CATSMAT_scoredatacollector scoredatacollection;
    filesystem::path testdata = testUtil.MakePathToTestData("TestScore_4_Measures_WithQuaverPassingNotes.xml");
    
    the_processor->addFile(testdata);
    
    scoredatacollection.Visit(*the_processor);
    
    ostringstream the_score_data_as_string;
    the_score_data_as_string << scoredatacollection;
    ASSERT_EQ(TestScore_4_Measures_WithQuaverPassingNotes_Expected, the_score_data_as_string.str());
    
}

TEST_F(CATSMAT_scoredatacollector_tests, TestScore_4_Measures_WithSemiQuaverPassingNotes) {
    
    CATSMAT_processing *the_processor = new CATSMAT_processing();
    CATSMAT_scoredatacollector scoredatacollection;
    filesystem::path testdata = testUtil.MakePathToTestData("TestScore_4_Measures_WithSemiQuaverPassingNotes.xml");
    
    the_processor->addFile(testdata);
    
    scoredatacollection.Visit(*the_processor);
    
    ostringstream the_score_data_as_string;
    the_score_data_as_string << scoredatacollection;
    ASSERT_EQ(TestScore_4_Measures_WithSemiQuaverPassingNotes_Expected, the_score_data_as_string.str());
    
}

