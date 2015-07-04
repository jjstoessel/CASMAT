//
//  CATSMAT_cp_matrix_Test.cpp
//  imusant
//
//

#include "CATSMAT_cp_matrix.hpp"
#include "CATSMAT_processing.hpp"
#include "CATSMAT_collectionvisitor.hpp"

#include "CATSMAT_cp_matrix_Expected.h"

#include "TMusicXMLFile.h"
#include "TXML2IMUSANTVisitor.h"

#include <boost/filesystem.hpp>
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
    
};

/************ UTILITY FUNCTIONS ******************/

// These really don't belong here.  Refactor soon.

SScore xml_2_sscore(filesystem::path music_xml_file)
{
    TMusicXMLFile reader;
    SScore xml_score = reader.read((string&)music_xml_file);
    return xml_score;
}

S_IMUSANT_score sscore_2_imusantscore(SScore xml_score)
{
    TXML2IMUSANTVisitor xml_2_imusant_translator;
    xml_score->accept(xml_2_imusant_translator);
    S_IMUSANT_score imusant_score = xml_2_imusant_translator.getIMUSANTScore();
    return imusant_score;
}

unsigned long get_num_parts_in_score(S_IMUSANT_score imusant_score)
{
    IMUSANT_vector<S_IMUSANT_part> parts = imusant_score->partlist()->parts();
    unsigned long num_parts_in_score = parts.size();
    return num_parts_in_score;
}

CATSMAT::S_CATSMAT_cp_matrix imusant_2_cp_matrix(S_IMUSANT_score imusant_score)
{
    CATSMAT::CATSMAT_collection_visitor imusant_to_cp_matrix_translator;
    imusant_score->accept(imusant_to_cp_matrix_translator);
    CATSMAT::S_CATSMAT_cp_matrix matrix = imusant_to_cp_matrix_translator.getCPMatrix();
    return matrix;
}

string matrix_2_string(CATSMAT::S_CATSMAT_cp_matrix the_matrix)
{
    std::stringstream the_matrix_as_stringstream;
    the_matrix_as_stringstream << the_matrix;
    std::string the_matrix_as_string = the_matrix_as_stringstream.str();
    return the_matrix_as_string;
}

filesystem::path make_path_to_test_data(string relative_path)
{
    filesystem::path testdata(filesystem::initial_path());
    testdata.append(relative_path);
    return testdata;
}

IMUSANT_note & create_note(IMUSANT_pitch::type note_name, int octave, TRational note_duration)
{
    S_IMUSANT_pitch pitch = new_IMUSANT_pitch();
    pitch->set(note_name, octave, 1);

    S_IMUSANT_duration duration = new_IMUSANT_duration();
    duration->set(note_duration, 0, *new TRational(0,0));
    
    const long FIRST_NOTE_IN_MEASURE = 1;
    long note_index = FIRST_NOTE_IN_MEASURE;
    
    IMUSANT_note *note = new IMUSANT_note();
    
    note->setNoteIndex(note_index);
    note->setPitch(pitch);
    note->setDuration(duration);
    
    return *note;
}

const string ERR_MSG_FAILED_TO_PARSE_XML = "Failed to parse XML file. \nHave you added this file into the Copy Files build phase?";

/************* END UTILITY FUNCTIONS **********************/

/************* TEST CASES **********************/

 TEST_F(CATSMAT_cp_matrix_Test, CanAddOneNote) {
     
     const unsigned short OCTAVE_FIVE = 5;
     IMUSANT_note note = create_note(IMUSANT_pitch::type::E, OCTAVE_FIVE, IMUSANT_duration::minim);
     
     theMatrix->addpart();
     theMatrix->add(note);
     
     string matrix_as_string = matrix_2_string(theMatrix);
     ASSERT_EQ(CanAddOneNote_Expected, matrix_as_string);
}

TEST_F(CATSMAT_cp_matrix_Test, TestScore_1_Measure)
{
    filesystem::path testdata = make_path_to_test_data("testdata/TestScore_1_Measure.xml");
    
    SScore sscore = xml_2_sscore(testdata);
    ASSERT_FALSE(sscore == NULL) << ERR_MSG_FAILED_TO_PARSE_XML;
    
    S_IMUSANT_score imusant_score = sscore_2_imusantscore(sscore);
    theMatrix = imusant_2_cp_matrix(imusant_score);
    
    string matrix_as_string = matrix_2_string(theMatrix);
    ASSERT_EQ(TestScore_1_Measure_Expected, matrix_as_string);
    
    unsigned long num_parts_in_score = get_num_parts_in_score(imusant_score);
    ASSERT_EQ(num_parts_in_score, theMatrix->partCount());
}


TEST_F(CATSMAT_cp_matrix_Test, TestScore_4_Measures)
{
    filesystem::path testdata = make_path_to_test_data("testdata/TestScore_4_Measures.xml");
    
    SScore sscore = xml_2_sscore(testdata);
    ASSERT_FALSE(sscore == NULL) << ERR_MSG_FAILED_TO_PARSE_XML;
    
    S_IMUSANT_score imusant_score = sscore_2_imusantscore(sscore);
    theMatrix = imusant_2_cp_matrix(imusant_score);
    
    //cout << theMatrix;
    
    string matrix_as_string = matrix_2_string(theMatrix);
    ASSERT_EQ(TestScore_4_Measures_Expected, matrix_as_string);
    
    unsigned long num_parts_in_score = get_num_parts_in_score(imusant_score);
    ASSERT_EQ(num_parts_in_score, theMatrix->partCount());
    
    list<S_IMUSANT_chord> chords_in_matrix = theMatrix->getCPmatrix();
    ASSERT_EQ(13, chords_in_matrix.size()) << "Unexpected number of chords in the matrix.";
}

TEST_F(CATSMAT_cp_matrix_Test, TestScore_4_Measures_WithQuaverPassingNotes)
{
    filesystem::path testdata = make_path_to_test_data("testdata/TestScore_4_Measures_WithQuaverPassingNotes.xml");
    
    SScore sscore = xml_2_sscore(testdata);
    ASSERT_FALSE(sscore == NULL) << ERR_MSG_FAILED_TO_PARSE_XML;
    
    S_IMUSANT_score imusant_score = sscore_2_imusantscore(sscore);
    theMatrix = imusant_2_cp_matrix(imusant_score);
    
    string matrix_as_string = matrix_2_string(theMatrix);
    ASSERT_EQ(TestScore_4_Measures_WithQuaverPassingNotes_Expected, matrix_as_string);
    
    unsigned long num_parts_in_score = get_num_parts_in_score(imusant_score);
    ASSERT_EQ(num_parts_in_score, theMatrix->partCount());
}

TEST_F(CATSMAT_cp_matrix_Test, TestScore_4_Measures_WithSemiQuaverPassingNotes)
{
    filesystem::path testdata = make_path_to_test_data("testdata/TestScore_4_Measures_WithSemiQuaverPassingNotes.xml");
    
    SScore sscore = xml_2_sscore(testdata);
    ASSERT_FALSE(sscore == NULL) << ERR_MSG_FAILED_TO_PARSE_XML;
    
    S_IMUSANT_score imusant_score = sscore_2_imusantscore(sscore);
    theMatrix = imusant_2_cp_matrix(imusant_score);
    
    string matrix_as_string = matrix_2_string(theMatrix);
    ASSERT_EQ(TestScore_4_Measures_WithSemiQuaverPassingNotes_Expected, matrix_as_string);
    
    unsigned long num_parts_in_score = get_num_parts_in_score(imusant_score);
    ASSERT_EQ(num_parts_in_score, theMatrix->partCount());
}


TEST_F(CATSMAT_cp_matrix_Test, Sanctus)
{
    filesystem::path testdata = make_path_to_test_data("testdata/Sanctus.xml");
    
    SScore sscore = xml_2_sscore(testdata);
    ASSERT_FALSE(sscore == NULL) << ERR_MSG_FAILED_TO_PARSE_XML;
    
    S_IMUSANT_score imusant_score = sscore_2_imusantscore(sscore);
    theMatrix = imusant_2_cp_matrix(imusant_score);
    
    string matrix_as_string = matrix_2_string(theMatrix);
    ASSERT_EQ(Sanctus_Expected, matrix_as_string);
    
    unsigned long num_parts_in_score = get_num_parts_in_score(imusant_score);
    ASSERT_EQ(num_parts_in_score, theMatrix->partCount());
}

TEST_F(CATSMAT_cp_matrix_Test, Kyrie)
{
    filesystem::path testdata = make_path_to_test_data("testdata/Kyrie.xml");
    
    SScore sscore = xml_2_sscore(testdata);
    ASSERT_FALSE(sscore == NULL) << ERR_MSG_FAILED_TO_PARSE_XML;
    
    S_IMUSANT_score imusant_score = sscore_2_imusantscore(sscore);
    theMatrix = imusant_2_cp_matrix(imusant_score);
    
    string matrix_as_string = matrix_2_string(theMatrix);
    ASSERT_EQ(Kyrie_Expected, matrix_as_string);
    
    unsigned long num_parts_in_score = get_num_parts_in_score(imusant_score);
    ASSERT_EQ(num_parts_in_score, theMatrix->partCount());
}

TEST_F(CATSMAT_cp_matrix_Test, Josquin_MAF_Kyrie)
{
    filesystem::path testdata = make_path_to_test_data("testdata/Josquin_MAF_Kyrie.xml");
    
    SScore sscore = xml_2_sscore(testdata);
    ASSERT_FALSE(sscore == NULL) << ERR_MSG_FAILED_TO_PARSE_XML;
    
    S_IMUSANT_score imusant_score = sscore_2_imusantscore(sscore);
    theMatrix = imusant_2_cp_matrix(imusant_score);
    
    string matrix_as_string = matrix_2_string(theMatrix);
    ASSERT_EQ(Josquin_MAF_Kyrie_Expected, matrix_as_string);
    
    unsigned long num_parts_in_score = get_num_parts_in_score(imusant_score);
    ASSERT_EQ(num_parts_in_score, theMatrix->partCount());
}



/************* END TEST CASES **********************/


