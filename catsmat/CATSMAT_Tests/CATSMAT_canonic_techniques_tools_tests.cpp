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
#include "CATSMAT_canonic_techniques_tools.h"

#include "CATSMAT_canonic_techniques_tools_expected.h"

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

//simple three-part canon at unison
TEST_F(CATSMAT_Canonic_Tools_Test, TestScore_Talent_mest_pris) {
    
    S_IMUSANT_score imusant_score =  testUtil.InitialiseScoreFromFile("Anon-Talent_mest_pris_I-IV_115.xml");
    
    S_CATSMAT_CanonicTechniquesTools tools = new_CATSMAT_object<CATSMAT_CanonicTechniquesTools>();
    tools->Initialise(imusant_score);
    
    std::stringstream the_type_as_stringstream;
    for ( auto type : tools->GetCanonTypes())
    {
        the_type_as_stringstream << type;
    }
    string the_types_as_string = the_type_as_stringstream.str();
    
    ASSERT_EQ(TestScore_Talent_mest_pris_canontype_Expected, the_types_as_string);
}

//stacked canon
TEST_F(CATSMAT_Canonic_Tools_Test, TestScore_Ockeghem_Prenez_sur_moi) {
    
    S_IMUSANT_score imusant_score =  testUtil.InitialiseScoreFromFile("Ockeghem_Prenez_sur_moi_Cop.xml");
    
    S_CATSMAT_CanonicTechniquesTools tools = new_CATSMAT_object<CATSMAT_CanonicTechniquesTools>();
    tools->Initialise(imusant_score);
    
    std::stringstream the_type_as_stringstream;
    for ( auto type : tools->GetCanonTypes())
    {
        the_type_as_stringstream << type;
    }
    string the_types_as_string = the_type_as_stringstream.str();
    
    ASSERT_EQ(TestScore_Ockeghem_Prenez_sur_moi_canontype_Expected, the_types_as_string);
}

//several canons
TEST_F(CATSMAT_Canonic_Tools_Test, TestScore_Josquin_MAF_Kyrie) {
    
    S_IMUSANT_score imusant_score =  testUtil.InitialiseScoreFromFile("Josquin_MAF_Kyrie.xml");
    
    S_CATSMAT_CanonicTechniquesTools tools = new_CATSMAT_object<CATSMAT_CanonicTechniquesTools>();
    tools->Initialise(imusant_score);
    
    std::stringstream the_type_as_stringstream;
    for ( auto type : tools->GetCanonTypes())
    {
        the_type_as_stringstream << type;
    }
    string the_types_as_string = the_type_as_stringstream.str();
    
    ASSERT_EQ(TestScore_Josquin_MAF_Kyrie_canontype_Expected, the_types_as_string);
}

//test for retrograde
TEST_F(CATSMAT_Canonic_Tools_Test, TestScore_Machaut_Ma_fin_est_mon_commencement) {
    
    S_IMUSANT_score imusant_score =  testUtil.InitialiseScoreFromFile("Machaut-Ma_fin_est_mon_commencement.xml");
    
    S_CATSMAT_CanonicTechniquesTools tools = new_CATSMAT_object<CATSMAT_CanonicTechniquesTools>();
    tools->Initialise(imusant_score);
    
    std::stringstream the_type_as_stringstream;
    for ( auto type : tools->GetCanonTypes())
    {
        the_type_as_stringstream << type;
    }
    string the_types_as_string = the_type_as_stringstream.str();
    
    ASSERT_EQ(TestScore_Machaut_Ma_fin_est_mon_commencement_Expected, the_types_as_string);
}

//test for contrary motion
TEST_F(CATSMAT_Canonic_Tools_Test, TestScore_Cerreto_CM_canon) {
    
    S_IMUSANT_score imusant_score =  testUtil.InitialiseScoreFromFile("Cerreto-CM_canon_Della_prattica_musica_p222.xml");
    
    S_CATSMAT_CanonicTechniquesTools tools = new_CATSMAT_object<CATSMAT_CanonicTechniquesTools>();
    tools->Initialise(imusant_score);
    
    std::stringstream the_type_as_stringstream;
    for ( auto type : tools->GetCanonTypes())
    {
        the_type_as_stringstream << type;
    }
    string the_types_as_string = the_type_as_stringstream.str();
    
    ASSERT_EQ(TestScore_Cerreto_CM_canon_Expected, the_types_as_string);
}

//test for retrograde contrary motion
TEST_F(CATSMAT_Canonic_Tools_Test, TestScore_Bononcini_RCM_canon) {
    
    S_IMUSANT_score imusant_score =  testUtil.InitialiseScoreFromFile("Bononcini-RCM_canon_Musico_prattico_p105.xml");
    
    S_CATSMAT_CanonicTechniquesTools tools = new_CATSMAT_object<CATSMAT_CanonicTechniquesTools>();
    tools->Initialise(imusant_score);
    
    std::stringstream the_type_as_stringstream;
    for ( auto type : tools->GetCanonTypes())
    {
        the_type_as_stringstream << type;
    }
    string the_types_as_string = the_type_as_stringstream.str();
    
    ASSERT_EQ(TestScore_Bononcini_RCM_canon_Expected, the_types_as_string);
}

//test for proportional canon
//Du_Fay-Bien_veignes_vous.xml
TEST_F(CATSMAT_Canonic_Tools_Test, TestScore_Bien_veignes_vous) {
    
    S_IMUSANT_score imusant_score =  testUtil.InitialiseScoreFromFile("Du_Fay-Bien_veignes_vous.xml");
    
    S_CATSMAT_CanonicTechniquesTools tools = new_CATSMAT_object<CATSMAT_CanonicTechniquesTools>();
    tools->Initialise(imusant_score);
    
    std::stringstream the_type_as_stringstream;
    for ( auto type : tools->GetCanonTypes())
    {
        the_type_as_stringstream << type;
    }
    string the_types_as_string = the_type_as_stringstream.str();
    
    ASSERT_EQ(TestScore_Du_Fay_Bien_veignes_vous_Expected, the_types_as_string);
}
