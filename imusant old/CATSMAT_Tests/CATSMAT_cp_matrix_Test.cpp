//
//  CATSMAT_cp_matrix_Test.cpp
//  imusant
//
//

#include "CATSMAT_test_utility.h"
#include "CATSMAT_cp_matrix.hpp"

#include "CATSMAT_cp_matrix_Expected.h"
#include "CATSMAT_cp_matrix_Kyrie_Expected.h"
#include "CATSMAT_cp_matrix_Sanctus_Expected.h"
#include "CATSMAT_cp_matrix_Josquin_MAF_Kyrie_Expected.h"

#include "gtest/gtest.h"

using namespace boost;

// The fixture for testing class CATSMAT_cp_matrix.
class CATSMAT_cp_matrix_Test : public ::testing::Test {
    
protected:
    
    CATSMAT_cp_matrix_Test() {
        // You can do set-up work for each test here.
    }
    
    virtual ~CATSMAT_cp_matrix_Test() {
        // You can do clean-up work that doesn't throw exceptions here.
    }
    
    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:
    
    virtual void SetUp() {
        // Code here will be called immediately after the constructor (right
        // before each test).
        theMatrix = CATSMAT::new_CATSMAT_cp_matrix();
    }
    
    virtual void TearDown() {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }
    
    // Objects declared here can be used by all tests in the test case for CATSMAT_cp_matrix_Test.
    CATSMAT::S_CATSMAT_cp_matrix theMatrix;
    CATSMAT_test_utility testUtil;
    
};


TEST_F(CATSMAT_cp_matrix_Test, CanAddOneNote) {
    
    const unsigned short OCTAVE_FIVE = 5;
    IMUSANT_note note = testUtil.CreateNote(IMUSANT_pitch::type::E, OCTAVE_FIVE, IMUSANT_duration::minim);
    note.setMeasureNum(12);
    note.setNoteIndex(55);
    
    CATSMAT::S_CATSMAT_cp_matrix theMatrix = CATSMAT::new_CATSMAT_cp_matrix();
    theMatrix->addpart();
    theMatrix->add(note);
    
    string matrix_as_string = testUtil.ConvertCpmatrixToString(theMatrix);
    ASSERT_EQ(CanAddOneNote_Expected, matrix_as_string);
}

TEST_F(CATSMAT_cp_matrix_Test, TestScore_1_Measure)
{
    filesystem::path testdata = testUtil.MakePathToTestData("TestScore_1_Measure.xml");
    
    SScore sscore = testUtil.ConvertMusicXmlToSscore(testdata);
    ASSERT_FALSE(sscore == NULL) << testUtil.ERR_MSG_FAILED_TO_PARSE_XML;
    
    S_IMUSANT_score imusant_score = testUtil.ConvertSscoreToImusantscore(sscore);
    
    CATSMAT::S_CATSMAT_cp_matrix theMatrix = testUtil.ConvertImusantscoreToCpmatrix(imusant_score);
    
    string matrix_as_string = testUtil.ConvertCpmatrixToString(theMatrix);
    ASSERT_EQ(TestScore_1_Measure_Expected, matrix_as_string);
    
    unsigned long num_parts_in_score = testUtil.GetNumPartsInScore(imusant_score);
    ASSERT_EQ(num_parts_in_score, theMatrix->partCount());
}


TEST_F(CATSMAT_cp_matrix_Test, TestScore_4_Measures)
{
    filesystem::path testdata = testUtil.MakePathToTestData("TestScore_4_Measures.xml");
    
    SScore sscore = testUtil.ConvertMusicXmlToSscore(testdata);
    ASSERT_FALSE(sscore == NULL) << testUtil.ERR_MSG_FAILED_TO_PARSE_XML;
    
    S_IMUSANT_score imusant_score = testUtil.ConvertSscoreToImusantscore(sscore);
    
    CATSMAT::S_CATSMAT_cp_matrix theMatrix = testUtil.ConvertImusantscoreToCpmatrix(imusant_score);
    
    //cout << theMatrix;
    
    string matrix_as_string = testUtil.ConvertCpmatrixToString(theMatrix);
    ASSERT_EQ(TestScore_4_Measures_Expected, matrix_as_string);
    
    unsigned long num_parts_in_score = testUtil.GetNumPartsInScore(imusant_score);
    ASSERT_EQ(num_parts_in_score, theMatrix->partCount());
    
    list<S_IMUSANT_chord> chords_in_matrix = theMatrix->getCPmatrix();
    ASSERT_EQ(13, chords_in_matrix.size()) << "Unexpected number of chords in the matrix.";
}

TEST_F(CATSMAT_cp_matrix_Test, TestScore_4_Measures_WithQuaverPassingNotes)
{
    filesystem::path testdata = testUtil.MakePathToTestData("TestScore_4_Measures_WithQuaverPassingNotes.xml");
    
    SScore sscore = testUtil.ConvertMusicXmlToSscore(testdata);
    ASSERT_FALSE(sscore == NULL) << testUtil.ERR_MSG_FAILED_TO_PARSE_XML;
    
    S_IMUSANT_score imusant_score = testUtil.ConvertSscoreToImusantscore(sscore);
    
    CATSMAT::S_CATSMAT_cp_matrix theMatrix = testUtil.ConvertImusantscoreToCpmatrix(imusant_score);
    
    string matrix_as_string = testUtil.ConvertCpmatrixToString(theMatrix);
    ASSERT_EQ(TestScore_4_Measures_WithQuaverPassingNotes_Expected, matrix_as_string);
    
    unsigned long num_parts_in_score = testUtil.GetNumPartsInScore(imusant_score);
    ASSERT_EQ(num_parts_in_score, theMatrix->partCount());
}

TEST_F(CATSMAT_cp_matrix_Test, TestScore_4_Measures_WithSemiQuaverPassingNotes)
{
    filesystem::path testdata = testUtil.MakePathToTestData("TestScore_4_Measures_WithSemiQuaverPassingNotes.xml");
    
    SScore sscore = testUtil.ConvertMusicXmlToSscore(testdata);
    ASSERT_FALSE(sscore == NULL) << testUtil.ERR_MSG_FAILED_TO_PARSE_XML;
    
    S_IMUSANT_score imusant_score = testUtil.ConvertSscoreToImusantscore(sscore);
    
    CATSMAT::S_CATSMAT_cp_matrix theMatrix = testUtil.ConvertImusantscoreToCpmatrix(imusant_score);
    
    string matrix_as_string = testUtil.ConvertCpmatrixToString(theMatrix);
    ASSERT_EQ(TestScore_4_Measures_WithSemiQuaverPassingNotes_Expected, matrix_as_string);
    
    unsigned long num_parts_in_score = testUtil.GetNumPartsInScore(imusant_score);
    ASSERT_EQ(num_parts_in_score, theMatrix->partCount());
}


TEST_F(CATSMAT_cp_matrix_Test, Sanctus)
{
    filesystem::path testdata = testUtil.MakePathToTestData("Sanctus.xml");
    
    SScore sscore = testUtil.ConvertMusicXmlToSscore(testdata);
    ASSERT_FALSE(sscore == NULL) << testUtil.ERR_MSG_FAILED_TO_PARSE_XML;
    
    S_IMUSANT_score imusant_score = testUtil.ConvertSscoreToImusantscore(sscore);
    
    CATSMAT::S_CATSMAT_cp_matrix theMatrix = testUtil.ConvertImusantscoreToCpmatrix(imusant_score);
    
    string matrix_as_string = testUtil.ConvertCpmatrixToString(theMatrix);
    ASSERT_EQ(Sanctus_Expected, matrix_as_string);
    
    unsigned long num_parts_in_score = testUtil.GetNumPartsInScore(imusant_score);
    ASSERT_EQ(num_parts_in_score, theMatrix->partCount());
}

TEST_F(CATSMAT_cp_matrix_Test, Kyrie)
{
    filesystem::path testdata = testUtil.MakePathToTestData("Kyrie.xml");
    
    SScore sscore = testUtil.ConvertMusicXmlToSscore(testdata);
    ASSERT_FALSE(sscore == NULL) << testUtil.ERR_MSG_FAILED_TO_PARSE_XML;
    
    S_IMUSANT_score imusant_score = testUtil.ConvertSscoreToImusantscore(sscore);
    
    CATSMAT::S_CATSMAT_cp_matrix theMatrix = testUtil.ConvertImusantscoreToCpmatrix(imusant_score);
    
    string matrix_as_string = testUtil.ConvertCpmatrixToString(theMatrix);
    ASSERT_EQ(Kyrie_Expected, matrix_as_string);
    
    unsigned long num_parts_in_score = testUtil.GetNumPartsInScore(imusant_score);
    ASSERT_EQ(num_parts_in_score, theMatrix->partCount());
}

TEST_F(CATSMAT_cp_matrix_Test, Josquin_MAF_Kyrie)
{
    filesystem::path testdata = testUtil.MakePathToTestData("Josquin_MAF_Kyrie.xml");
    
    SScore sscore = testUtil.ConvertMusicXmlToSscore(testdata);
    ASSERT_FALSE(sscore == NULL) << testUtil.ERR_MSG_FAILED_TO_PARSE_XML;
    
    S_IMUSANT_score imusant_score = testUtil.ConvertSscoreToImusantscore(sscore);
    
    CATSMAT::S_CATSMAT_cp_matrix theMatrix = testUtil.ConvertImusantscoreToCpmatrix(imusant_score);
    
    string matrix_as_string = testUtil.ConvertCpmatrixToString(theMatrix);
    ASSERT_EQ(Josquin_MAF_Kyrie_Expected, matrix_as_string);
    
    unsigned long num_parts_in_score = testUtil.GetNumPartsInScore(imusant_score);
    ASSERT_EQ(num_parts_in_score, theMatrix->partCount());
}


