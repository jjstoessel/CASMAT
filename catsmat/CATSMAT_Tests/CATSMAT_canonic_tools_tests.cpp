//
//  CATSMAT_canonic_tools_tests.cpp
//  catsmat
//
//  Created by Jason Stoessel on 10/03/2017.
//
//

#include <boost/filesystem.hpp>

#include "CATSMAT_test_utility.h"
#include "gtest/gtest.h"
#include "CATSMAT_canonic_tools.hpp"

#include "CATSMAT_canonic_tools_expected.hpp"

// The fixture for testing class CATSMAT_cp_matrix.
class CATSMAT_Canonic_Tools_Test : public ::testing::Test {
    
protected:
    
    CATSMAT_Canonic_Tools_Test() {
        // You can do set-up work for each test here.
    }
    
    virtual ~CATSMAT_Canonic_Tools_Test() {
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

TEST_F(CATSMAT_Canonic_Tools_Test, TestScore_Talent_mest_pris) {
    
    S_IMUSANT_score imusant_score =  testUtil.InitialiseScoreFromFile("Anon-Talent_mest_pris_I-IV_115.xml");
    
    S_CATSMAT_Canonic_Tools tools = new_CATSMAT_object<CATSMAT_CanonicTools>();
    tools->Initialise(imusant_score);
    
    std::stringstream the_type_as_stringstream;
    for ( auto type : tools->GetCanonTypes())
    {
        the_type_as_stringstream << type;
    }
    string the_types_as_string = the_type_as_stringstream.str();
    
    ASSERT_EQ(TestScore_Talent_mest_pris_canontype_Expected, the_types_as_string);
}

TEST_F(CATSMAT_Canonic_Tools_Test, TestScore_Ockeghem_Prenez_sur_moi) {
    
    S_IMUSANT_score imusant_score =  testUtil.InitialiseScoreFromFile("Ockeghem_Prenez_sur_moi_(Cop).xml");
    
    S_CATSMAT_Canonic_Tools tools = new_CATSMAT_object<CATSMAT_CanonicTools>();
    tools->Initialise(imusant_score);
    
    std::stringstream the_type_as_stringstream;
    for ( auto type : tools->GetCanonTypes())
    {
        the_type_as_stringstream << type;
    }
    string the_types_as_string = the_type_as_stringstream.str();
    
    ASSERT_EQ(TestScore_Ockeghem_Prenez_sur_moi_canontype_Expected, the_types_as_string);
}
