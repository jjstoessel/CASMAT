//
//  CATSMAT_dyad_sequences_Test.cpp
//  imusant
//
//  Created by Derrick Hill on 4/07/2015.
//
//

#include <stdio.h>

#include "CATSMAT_dyad_sequences.h"

#include "CATSMAT_test_utility.h"

#include "CATSMAT_dyad_sequences_Expected.h"

#include "gtest/gtest.h"
#include <boost/filesystem.hpp>

// The fixture for testing class CATSMAT_cp_matrix.
class CATSMAT_dyad_sequences_Test : public ::testing::Test {
    
protected:
    
    CATSMAT_dyad_sequences_Test() {
        // You can do set-up work for each test here.
    }
    
    virtual ~CATSMAT_dyad_sequences_Test() {
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
    CATSMAT::CATSMAT_dyad_sequences theSequences;
    
};

TEST_F(CATSMAT_dyad_sequences_Test, TestScore_1_Measure) {
    
    CATSMAT::S_CATSMAT_cp_matrix the_matrix = testUtil.ConvertMusicXmlToCpmatrix("TestScore_1_Measure.xml");
    theSequences.Visit(*the_matrix);
    
    string the_sequences_as_string = testUtil.ConvertDyadSequencesToString(theSequences);
    
    ASSERT_EQ(TestScore_1_Measure_Expected, the_sequences_as_string);
}

TEST_F(CATSMAT_dyad_sequences_Test, TestScore_4_Measures) {

    CATSMAT::S_CATSMAT_cp_matrix the_matrix = testUtil.ConvertMusicXmlToCpmatrix("TestScore_4_Measures.xml");
    theSequences.Visit(*the_matrix);

    string the_sequences_as_string = testUtil.ConvertDyadSequencesToString(theSequences);
    
    ASSERT_EQ(TestScore_4_Measures_Expected, the_sequences_as_string);
}

TEST_F(CATSMAT_dyad_sequences_Test, TestScore_4_Measures_WithQuaverPassingNotes) {
    
    CATSMAT::S_CATSMAT_cp_matrix the_matrix = testUtil.ConvertMusicXmlToCpmatrix("TestScore_4_Measures_WithQuaverPassingNotes.xml");
    theSequences.Visit(*the_matrix);
    
    string the_sequences_as_string = testUtil.ConvertDyadSequencesToString(theSequences);
    
    ASSERT_EQ(TestScore_4_Measures_WithQuaverPassingNotes_Expected, the_sequences_as_string);
}

TEST_F(CATSMAT_dyad_sequences_Test, TestScore_4_Measures_WithSemiQuaverPassingNotes) {
    
    CATSMAT::S_CATSMAT_cp_matrix the_matrix = testUtil.ConvertMusicXmlToCpmatrix("TestScore_4_Measures_WithSemiQuaverPassingNotes.xml");
    theSequences.Visit(*the_matrix);
    
    string the_sequences_as_string = testUtil.ConvertDyadSequencesToString(theSequences);
    
    ASSERT_EQ(TestScore_4_Measures_WithSemiQuaverPassingNotes_Expected, the_sequences_as_string);
}
