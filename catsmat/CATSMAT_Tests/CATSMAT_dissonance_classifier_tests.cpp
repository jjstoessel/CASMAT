//
//  CATSMAT_dissonance_classifier_tests.cpp
//  CATSMAT_Tests
//
//  Created by Jason Stoessel on 12/7/19.
//

#include <stdio.h>

#include <boost/filesystem.hpp>

#include "CATSMAT_test_utility.h"
#include "gtest/gtest.h"
#include "CATSMAT_dissonance.h"
//#include "CATSMAT_dissonance_classifer.h"

//#include "CATSMAT_canonic_techniques_tools_expected.h"

// The fixture for testing class CATSMAT_cp_matrix.
class CATSMAT_Dissonance_Classifier_Tests : public ::testing::Test {
    
protected:
    
    CATSMAT_Dissonance_Classifier_Tests() {
        // You can do set-up work for each test here.
    }
    
    virtual ~CATSMAT_Dissonance_Classifier_Tests() {
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

TEST_F(CATSMAT_Dissonance_Classifier_Tests, Suspension_Test_1) {
    
    S_IMUSANT_pitch utop = new_IMUSANT_pitch();
    S_IMUSANT_pitch udissp = new_IMUSANT_pitch();
    S_IMUSANT_pitch ufromp = new_IMUSANT_pitch();
    S_IMUSANT_pitch ltop = new_IMUSANT_pitch();
    S_IMUSANT_pitch ldissp = new_IMUSANT_pitch();
    S_IMUSANT_pitch lfromp = new_IMUSANT_pitch();
    
    //void set(type name_as_written, unsigned short octave_as_written, unsigned short voice);
    utop->set(IMUSANT_pitch::C, 4, 1);
    udissp->set(IMUSANT_pitch::B, 3, 1);
    ufromp->set(IMUSANT_pitch::B, 3, 1);
    ltop->set(IMUSANT_pitch::A, 3, 2);
    ldissp->set(IMUSANT_pitch::A, 3, 2);
    lfromp->set(IMUSANT_pitch::G, 3, 2);
    
    S_IMUSANT_duration utodur, udissdur, ufromdur, ltodur, ldissdur, lfromdur;
    
    utodur = new_IMUSANT_duration(IMUSANT_duration::minim);
    udissdur = new_IMUSANT_duration(IMUSANT_duration::minim);
    ufromdur = new_IMUSANT_duration(IMUSANT_duration::minim);
    ltodur = new_IMUSANT_duration(IMUSANT_duration::minim);
    ldissdur = new_IMUSANT_duration(IMUSANT_duration::minim);
    lfromdur = new_IMUSANT_duration(IMUSANT_duration::minim);
    
    //IMUSANT_note(S_IMUSANT_pitch& pitch, S_IMUSANT_duration& duration );
    
    IMUSANT_note uto(utop, utodur), udiss(udissp,udissdur), ufrom(ufromp,ufromdur), lto(ltop,ltodur), ldiss(ldissp,ldissdur), lfrom(lfromp,lfromdur);
    
    CATSMAT_dissonance dissonance;
    dissonance.Calculate(uto, lto, udiss, ldiss, ufrom, lfrom);
    
    ASSERT_EQ(dissonance.getSchemata().getType(), CATSMAT_dissonance::schemata::suspension);
}
