//
//  CATSMAT_cp_matrix_Test.cpp
//  imusant
//
//

#include "CATSMAT_cp_matrix.hpp"
#include "CATSMAT_processing.hpp"
#include "CATSMAT_collectionvisitor.hpp"

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

TEST_F(CATSMAT_cp_matrix_Test, CanAddOneNote) {
    
    S_IMUSANT_pitch pitch = new_IMUSANT_pitch();
    pitch->set(IMUSANT_pitch::type::E, 2, 1, IMUSANT_pitch::type::A);

    S_IMUSANT_duration duration = new_IMUSANT_duration();
    duration->set(*new TRational(4,4), 0, *new TRational(2,2));

    IMUSANT_note *note = new IMUSANT_note();

    // REVISIT - IMUSANT_note::print() crashes if pitch == null or duration == null. Probably should make this more robust somehow.
    // REVISIT - IMUSANT_duration::print() is not implemented.
    // REVISIT - IMUSANT_pitch::print() need to confirm that the output is as intended.  For the above I get "<PITCH>E0@2<\PITCH>".

    note->setPitch(pitch);
    note->setDuration(duration);

    theMatrix->addpart();
    theMatrix->add(*note);
    
    theMatrix->print(cout);

    // REVISIT - FORCE THIS TEST TO FAIL FOR THE MOMENT.
    EXPECT_EQ(100, 10) << "Forcing failure to see if this works...";
    
}

TEST_F(CATSMAT_cp_matrix_Test, Sanctus)
{
    filesystem::path testdata(filesystem::initial_path());
    testdata.append("testdata/Sanctus.xml");
    
    TMusicXMLFile reader;
    SScore xml_score = reader.read((string&)testdata);
    EXPECT_FALSE(xml_score == NULL);
    
    TXML2IMUSANTVisitor xml_2_imusant_translator;
    xml_score->accept(xml_2_imusant_translator);
    
    S_IMUSANT_score imusant_score = xml_2_imusant_translator.getIMUSANTScore();
    IMUSANT_vector<S_IMUSANT_part> parts = imusant_score->partlist()->parts();
    unsigned long num_parts_in_score = parts.size();
    
    CATSMAT::CATSMAT_collection_visitor imusant_to_cp_matrix_translator;
    imusant_score->accept(imusant_to_cp_matrix_translator);
    
    theMatrix = imusant_to_cp_matrix_translator.getCPMatrix();
    
    EXPECT_EQ(num_parts_in_score, theMatrix->partCount());
}


