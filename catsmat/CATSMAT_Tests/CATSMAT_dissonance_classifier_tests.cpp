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
#include "CATSMAT_score_profile.h"
#include "CATSMAT_dyad_sequences.h"
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
    
    CATSMAT_dissonance dissonance(uto, lto, udiss, ldiss, ufrom, lfrom, true);
    
    ASSERT_EQ(dissonance.getSchemata().getType(), CATSMAT_dissonance::schemata::suspension);
}

TEST_F(CATSMAT_Dissonance_Classifier_Tests, Descending_Passing_Tone_Test_1) {
    
    S_IMUSANT_pitch utop = new_IMUSANT_pitch();
    S_IMUSANT_pitch udissp = new_IMUSANT_pitch();
    S_IMUSANT_pitch ufromp = new_IMUSANT_pitch();
    S_IMUSANT_pitch ltop = new_IMUSANT_pitch();
    S_IMUSANT_pitch ldissp = new_IMUSANT_pitch();
    S_IMUSANT_pitch lfromp = new_IMUSANT_pitch();
    
    //void set(type name_as_written, unsigned short octave_as_written, unsigned short voice);
    utop->set(IMUSANT_pitch::C, 4, 1);
    udissp->set(IMUSANT_pitch::B, 3, 1);
    ufromp->set(IMUSANT_pitch::A, 3, 1);
    ltop->set(IMUSANT_pitch::F, 3, 2);
    ldissp->set(IMUSANT_pitch::F, 3, 2);
    lfromp->set(IMUSANT_pitch::F, 3, 2);
    
    S_IMUSANT_duration utodur, udissdur, ufromdur, ltodur, ldissdur, lfromdur;
    
    utodur = new_IMUSANT_duration(IMUSANT_duration::minim);
    udissdur = new_IMUSANT_duration(IMUSANT_duration::minim);
    ufromdur = new_IMUSANT_duration(IMUSANT_duration::minim);
    ltodur = new_IMUSANT_duration(IMUSANT_duration::minim);
    ldissdur = new_IMUSANT_duration(IMUSANT_duration::minim);
    lfromdur = new_IMUSANT_duration(IMUSANT_duration::minim);
    
    //IMUSANT_note(S_IMUSANT_pitch& pitch, S_IMUSANT_duration& duration );
    
    IMUSANT_note uto(utop, utodur), udiss(udissp,udissdur), ufrom(ufromp,ufromdur), lto(ltop,ltodur), ldiss(ldissp,ldissdur), lfrom(lfromp,lfromdur);
    
    CATSMAT_dissonance dissonance(uto, lto, udiss, ldiss, ufrom, lfrom, false);
    
    ASSERT_EQ(dissonance.getSchemata().getType(), CATSMAT_dissonance::schemata::descending_passing_tone);
}

//note: new note constructor method added here
TEST_F(CATSMAT_Dissonance_Classifier_Tests, Ascending_Passing_Tone_Test_1) {
    
    IMUSANT_note uto(IMUSANT_pitch::A, 3, 1, IMUSANT_pitch::natural, IMUSANT_duration::minim);
    IMUSANT_note udiss(IMUSANT_pitch::B, 3, 1, IMUSANT_pitch::natural, IMUSANT_duration::minim);
    IMUSANT_note ufrom(IMUSANT_pitch::C, 4, 1, IMUSANT_pitch::natural, IMUSANT_duration::minim);
    IMUSANT_note lto(IMUSANT_pitch::F, 3, 2, IMUSANT_pitch::natural, IMUSANT_duration::minim);
    IMUSANT_note ldiss(IMUSANT_pitch::F, 3, 2, IMUSANT_pitch::natural, IMUSANT_duration::minim);
    IMUSANT_note lfrom(IMUSANT_pitch::F, 3, 2, IMUSANT_pitch::natural, IMUSANT_duration::minim);
    
    CATSMAT_dissonance dissonance(uto, lto, udiss, ldiss, ufrom, lfrom, false);
    
    ASSERT_EQ(dissonance.getSchemata().getType(), CATSMAT_dissonance::schemata::ascending_passing_tone);
}

//upper_neighbour_tone,       //unaccented, melodic upper 1,-1, lower 0,*
TEST_F(CATSMAT_Dissonance_Classifier_Tests, Upper_Neighbour_Tone_Test_1) {
    
    S_IMUSANT_pitch utop = new_IMUSANT_pitch();
    S_IMUSANT_pitch udissp = new_IMUSANT_pitch();
    S_IMUSANT_pitch ufromp = new_IMUSANT_pitch();
    S_IMUSANT_pitch ltop = new_IMUSANT_pitch();
    S_IMUSANT_pitch ldissp = new_IMUSANT_pitch();
    S_IMUSANT_pitch lfromp = new_IMUSANT_pitch();
    
    //void set(type name_as_written, unsigned short octave_as_written, unsigned short voice);
    utop->set(IMUSANT_pitch::C, 4, 1);
    udissp->set(IMUSANT_pitch::D, 4, 1);
    ufromp->set(IMUSANT_pitch::C, 4, 1);
    ltop->set(IMUSANT_pitch::E, 3, 2);
    ldissp->set(IMUSANT_pitch::E, 3, 2);
    lfromp->set(IMUSANT_pitch::A, 3, 2);
    
    S_IMUSANT_duration utodur, udissdur, ufromdur, ltodur, ldissdur, lfromdur;
    
    utodur = new_IMUSANT_duration(IMUSANT_duration::minim);
    udissdur = new_IMUSANT_duration(IMUSANT_duration::minim);
    ufromdur = new_IMUSANT_duration(IMUSANT_duration::minim);
    ltodur = new_IMUSANT_duration(IMUSANT_duration::minim);
    ldissdur = new_IMUSANT_duration(IMUSANT_duration::minim);
    lfromdur = new_IMUSANT_duration(IMUSANT_duration::minim);
    
    //IMUSANT_note(S_IMUSANT_pitch& pitch, S_IMUSANT_duration& duration );
    
    IMUSANT_note uto(utop, utodur), udiss(udissp,udissdur), ufrom(ufromp,ufromdur), lto(ltop,ltodur), ldiss(ldissp,ldissdur), lfrom(lfromp,lfromdur);
    
    CATSMAT_dissonance dissonance(uto, lto, udiss, ldiss, ufrom, lfrom, false);
    
    ASSERT_EQ(dissonance.getSchemata().getType(), CATSMAT_dissonance::schemata::upper_neighbour_tone);
}

//lower neighbour tone; note: new note constructor method added here
TEST_F(CATSMAT_Dissonance_Classifier_Tests, Lower_Neighbour_Tone_Test_1) {
    
    IMUSANT_note uto(IMUSANT_pitch::F, 4, 1, IMUSANT_pitch::natural, IMUSANT_duration::minim);
    IMUSANT_note udiss(IMUSANT_pitch::E, 4, 1, IMUSANT_pitch::natural, IMUSANT_duration::minim);
    IMUSANT_note ufrom(IMUSANT_pitch::F, 4, 1, IMUSANT_pitch::natural, IMUSANT_duration::minim);
    IMUSANT_note lto(IMUSANT_pitch::F, 3, 2, IMUSANT_pitch::natural, IMUSANT_duration::minim);
    IMUSANT_note ldiss(IMUSANT_pitch::F, 3, 2, IMUSANT_pitch::natural, IMUSANT_duration::minim);
    IMUSANT_note lfrom(IMUSANT_pitch::F, 3, 2, IMUSANT_pitch::natural, IMUSANT_duration::minim);
    
    CATSMAT_dissonance dissonance(uto, lto, udiss, ldiss, ufrom, lfrom, false);
    
    ASSERT_EQ(dissonance.getSchemata().getType(), CATSMAT_dissonance::schemata::lower_neighbour_tone);
}

//incomplete_lower_neighbour_tone,  //unaccented, melodic upper <-1, 1, lower 0,*
TEST_F(CATSMAT_Dissonance_Classifier_Tests, Incomplete_Upper_Neighbour_Tone_Test_1) {
    
    S_IMUSANT_pitch utop = new_IMUSANT_pitch();
    S_IMUSANT_pitch udissp = new_IMUSANT_pitch();
    S_IMUSANT_pitch ufromp = new_IMUSANT_pitch();
    S_IMUSANT_pitch ltop = new_IMUSANT_pitch();
    S_IMUSANT_pitch ldissp = new_IMUSANT_pitch();
    S_IMUSANT_pitch lfromp = new_IMUSANT_pitch();
    
    //void set(type name_as_written, unsigned short octave_as_written, unsigned short voice);
    utop->set(IMUSANT_pitch::B, 3, 1);
    udissp->set(IMUSANT_pitch::D, 4, 1);
    ufromp->set(IMUSANT_pitch::C, 4, 1);
    ltop->set(IMUSANT_pitch::E, 3, 2);
    ldissp->set(IMUSANT_pitch::E, 3, 2);
    lfromp->set(IMUSANT_pitch::A, 3, 2);
    
    S_IMUSANT_duration utodur, udissdur, ufromdur, ltodur, ldissdur, lfromdur;
    
    utodur = new_IMUSANT_duration(IMUSANT_duration::minim);
    udissdur = new_IMUSANT_duration(IMUSANT_duration::minim);
    ufromdur = new_IMUSANT_duration(IMUSANT_duration::minim);
    ltodur = new_IMUSANT_duration(IMUSANT_duration::minim);
    ldissdur = new_IMUSANT_duration(IMUSANT_duration::minim);
    lfromdur = new_IMUSANT_duration(IMUSANT_duration::minim);
    
    //IMUSANT_note(S_IMUSANT_pitch& pitch, S_IMUSANT_duration& duration );
    
    IMUSANT_note uto(utop, utodur), udiss(udissp,udissdur), ufrom(ufromp,ufromdur), lto(ltop,ltodur), ldiss(ldissp,ldissdur), lfrom(lfromp,lfromdur);
    
    CATSMAT_dissonance dissonance(uto, lto, udiss, ldiss, ufrom, lfrom, false);
    
    ASSERT_EQ(dissonance.getSchemata().getType(), CATSMAT_dissonance::schemata::incomplete_upper_neighbour_tone);
}

//incomplete lower neighbour tone; unaccented, melodic upper <-1, 1, lower 0,*note: new note constructor method added here
TEST_F(CATSMAT_Dissonance_Classifier_Tests, Incomplete_Lower_Neighbour_Tone_Test_1) {
    
    IMUSANT_note uto(IMUSANT_pitch::D, 4, 1, IMUSANT_pitch::natural, IMUSANT_duration::minim);
    IMUSANT_note udiss(IMUSANT_pitch::B, 3, 1, IMUSANT_pitch::natural, IMUSANT_duration::minim);
    IMUSANT_note ufrom(IMUSANT_pitch::C, 4, 1, IMUSANT_pitch::natural, IMUSANT_duration::minim);
    IMUSANT_note lto(IMUSANT_pitch::F, 3, 2, IMUSANT_pitch::natural, IMUSANT_duration::minim);
    IMUSANT_note ldiss(IMUSANT_pitch::F, 3, 2, IMUSANT_pitch::natural, IMUSANT_duration::minim);
    IMUSANT_note lfrom(IMUSANT_pitch::F, 3, 2, IMUSANT_pitch::natural, IMUSANT_duration::minim);
    
    CATSMAT_dissonance dissonance(uto, lto, udiss, ldiss, ufrom, lfrom, false);
    
    ASSERT_EQ(dissonance.getSchemata().getType(), CATSMAT_dissonance::schemata::incomplete_lower_neighbour_tone);
}

//appoggiatura, //accented, melodic upper *, -1, lower *,0; includes acciaccatura (which is a shorted accented dissonance)
TEST_F(CATSMAT_Dissonance_Classifier_Tests,Appoggiatura_Test_1) {
    
    S_IMUSANT_pitch utop = new_IMUSANT_pitch();
    S_IMUSANT_pitch udissp = new_IMUSANT_pitch();
    S_IMUSANT_pitch ufromp = new_IMUSANT_pitch();
    S_IMUSANT_pitch ltop = new_IMUSANT_pitch();
    S_IMUSANT_pitch ldissp = new_IMUSANT_pitch();
    S_IMUSANT_pitch lfromp = new_IMUSANT_pitch();
    
    //void set(type name_as_written, unsigned short octave_as_written, unsigned short voice);
    utop->set(IMUSANT_pitch::C, 4, 1);
    udissp->set(IMUSANT_pitch::E, 4, 1);
    ufromp->set(IMUSANT_pitch::D, 4, 1);
    ltop->set(IMUSANT_pitch::E, 3, 2);
    ldissp->set(IMUSANT_pitch::F, 3, 2);
    lfromp->set(IMUSANT_pitch::F, 3, 2);
    
    S_IMUSANT_duration utodur, udissdur, ufromdur, ltodur, ldissdur, lfromdur;
    
    utodur = new_IMUSANT_duration(IMUSANT_duration::minim);
    udissdur = new_IMUSANT_duration(IMUSANT_duration::minim);
    ufromdur = new_IMUSANT_duration(IMUSANT_duration::minim);
    ltodur = new_IMUSANT_duration(IMUSANT_duration::minim);
    ldissdur = new_IMUSANT_duration(IMUSANT_duration::minim);
    lfromdur = new_IMUSANT_duration(IMUSANT_duration::minim);
    
    //IMUSANT_note(S_IMUSANT_pitch& pitch, S_IMUSANT_duration& duration );
    
    IMUSANT_note uto(utop, utodur), udiss(udissp,udissdur), ufrom(ufromp,ufromdur), lto(ltop,ltodur), ldiss(ldissp,ldissdur), lfrom(lfromp,lfromdur);
    
    CATSMAT_dissonance dissonance(uto, lto, udiss, ldiss, ufrom, lfrom, true);
    
    ASSERT_EQ(dissonance.getSchemata().getType(), CATSMAT_dissonance::schemata::appoggiatura);
}

//retardation; accented, melodic upper 0, 1, lower, -1, 0 (P,S,R)
TEST_F(CATSMAT_Dissonance_Classifier_Tests, Retardation_Test_1) {
    
    IMUSANT_note uto(IMUSANT_pitch::D, 4, 1, IMUSANT_pitch::natural, IMUSANT_duration::minim);
    IMUSANT_note udiss(IMUSANT_pitch::D, 4, 1, IMUSANT_pitch::natural, IMUSANT_duration::minim);
    IMUSANT_note ufrom(IMUSANT_pitch::E, 4, 1, IMUSANT_pitch::natural, IMUSANT_duration::minim);
    IMUSANT_note lto(IMUSANT_pitch::F, 3, 2, IMUSANT_pitch::natural, IMUSANT_duration::minim);
    IMUSANT_note ldiss(IMUSANT_pitch::E, 3, 2, IMUSANT_pitch::natural, IMUSANT_duration::minim);
    IMUSANT_note lfrom(IMUSANT_pitch::E, 3, 2, IMUSANT_pitch::natural, IMUSANT_duration::minim);
    
    CATSMAT_dissonance dissonance(uto, lto, udiss, ldiss, ufrom, lfrom, true);
    
    ASSERT_EQ(dissonance.getSchemata().getType(), CATSMAT_dissonance::schemata::retardation);
}

//cambiata,                 //unaccented, melodic upper -1,-2,1, lower 0,0,* ; dissonance always second element
TEST_F(CATSMAT_Dissonance_Classifier_Tests, Cambiata_Test_1) {
    
    S_IMUSANT_pitch utop = new_IMUSANT_pitch();
    S_IMUSANT_pitch udissp = new_IMUSANT_pitch();
    S_IMUSANT_pitch uintp = new_IMUSANT_pitch();
    S_IMUSANT_pitch ufromp = new_IMUSANT_pitch();
    S_IMUSANT_pitch ltop = new_IMUSANT_pitch();
    S_IMUSANT_pitch ldissp = new_IMUSANT_pitch();
    S_IMUSANT_pitch lintp = new_IMUSANT_pitch();
    S_IMUSANT_pitch lfromp = new_IMUSANT_pitch();
    
    //void set(type name_as_written, unsigned short octave_as_written, unsigned short voice);
    utop->set(IMUSANT_pitch::C, 4, 1);
    udissp->set(IMUSANT_pitch::B, 3, 1);
    uintp->set(IMUSANT_pitch::G, 3, 1);
    ufromp->set(IMUSANT_pitch::A, 3, 1);
    ltop->set(IMUSANT_pitch::C, 3, 2);
    ldissp->set(IMUSANT_pitch::C, 3, 2);
    lintp->set(IMUSANT_pitch::C, 3, 2);
    lfromp->set(IMUSANT_pitch::C, 3, 2);
    
    S_IMUSANT_duration utodur, udissdur, uintdur, ufromdur, ltodur, ldissdur, lintdur, lfromdur;
    
    utodur = new_IMUSANT_duration(IMUSANT_duration::minim);
    udissdur = new_IMUSANT_duration(IMUSANT_duration::minim);
    uintdur = new_IMUSANT_duration(IMUSANT_duration::minim);
    ufromdur = new_IMUSANT_duration(IMUSANT_duration::minim);
    ltodur = new_IMUSANT_duration(IMUSANT_duration::minim);
    ldissdur = new_IMUSANT_duration(IMUSANT_duration::minim);
    lintdur = new_IMUSANT_duration(IMUSANT_duration::minim);
    lfromdur = new_IMUSANT_duration(IMUSANT_duration::minim);
    
    //IMUSANT_note(S_IMUSANT_pitch& pitch, S_IMUSANT_duration& duration );
    
    IMUSANT_note uto(utop, utodur), udiss(udissp,udissdur), uint(uintp, uintdur), ufrom(ufromp,ufromdur), lto(ltop,ltodur), ldiss(ldissp,ldissdur), lint(lintp, lintdur), lfrom(lfromp,lfromdur);
    
    CATSMAT_dissonance dissonance(uto, lto, udiss, ldiss, uint, lint, ufrom, lfrom, false);
    
    ASSERT_EQ(dissonance.getSchemata().getType(), CATSMAT_dissonance::schemata::cambiata);
}

//inverted cambiata; unaccented, melodic upper 1,2,-1, lower 0,0,*
TEST_F(CATSMAT_Dissonance_Classifier_Tests, Inverted_Cambiata_Test_1) {
    
    IMUSANT_note uto(IMUSANT_pitch::G, 3, 1, IMUSANT_pitch::natural, IMUSANT_duration::minim);
    IMUSANT_note udiss(IMUSANT_pitch::A, 3, 1, IMUSANT_pitch::natural, IMUSANT_duration::minim);
    IMUSANT_note uint(IMUSANT_pitch::C, 4, 1, IMUSANT_pitch::natural, IMUSANT_duration::minim);
    IMUSANT_note ufrom(IMUSANT_pitch::B, 3, 1, IMUSANT_pitch::natural, IMUSANT_duration::minim);
    IMUSANT_note lto(IMUSANT_pitch::E, 3, 2, IMUSANT_pitch::natural, IMUSANT_duration::minim);
    IMUSANT_note ldiss(IMUSANT_pitch::E, 3, 2, IMUSANT_pitch::natural, IMUSANT_duration::minim);
    IMUSANT_note lint(IMUSANT_pitch::E, 3, 2, IMUSANT_pitch::natural, IMUSANT_duration::minim);
    IMUSANT_note lfrom(IMUSANT_pitch::E, 3, 2, IMUSANT_pitch::natural, IMUSANT_duration::minim);
    
    CATSMAT_dissonance dissonance(uto, lto, udiss, ldiss, uint, lint, ufrom, lfrom, false);
    
    ASSERT_EQ(dissonance.getSchemata().getType(), CATSMAT_dissonance::schemata::cambiata_i);
}

//upper_escape_tone; unaccented, melodic upper 1,<-1, lower 0, *
TEST_F(CATSMAT_Dissonance_Classifier_Tests, Upper_Escape_Tone_Test_1) {
    
    IMUSANT_note uto(IMUSANT_pitch::B, 3, 1, IMUSANT_pitch::natural, IMUSANT_duration::minim);
    IMUSANT_note udiss(IMUSANT_pitch::C, 4, 1, IMUSANT_pitch::natural, IMUSANT_duration::minim);
    IMUSANT_note ufrom(IMUSANT_pitch::A, 3, 1, IMUSANT_pitch::natural, IMUSANT_duration::minim);
    IMUSANT_note lto(IMUSANT_pitch::D, 3, 2, IMUSANT_pitch::natural, IMUSANT_duration::minim);
    IMUSANT_note ldiss(IMUSANT_pitch::D, 3, 2, IMUSANT_pitch::natural, IMUSANT_duration::minim);
    IMUSANT_note lfrom(IMUSANT_pitch::D, 3, 2, IMUSANT_pitch::natural, IMUSANT_duration::minim);
    
    CATSMAT_dissonance dissonance(uto, lto, udiss, ldiss, ufrom, lfrom, false);
    
    ASSERT_EQ(dissonance.getSchemata().getType(), CATSMAT_dissonance::schemata::upper_escape_tone);
}
//lower_escape_tone; unaccented, melodic upper -1,>1, lower 0, *
TEST_F(CATSMAT_Dissonance_Classifier_Tests, Lower_Escape_Tone_Test_1) {
    
    IMUSANT_note uto(IMUSANT_pitch::C, 4, 1, IMUSANT_pitch::natural, IMUSANT_duration::minim);
    IMUSANT_note udiss(IMUSANT_pitch::B, 3, 1, IMUSANT_pitch::natural, IMUSANT_duration::minim);
    IMUSANT_note ufrom(IMUSANT_pitch::D, 4, 1, IMUSANT_pitch::natural, IMUSANT_duration::minim);
    IMUSANT_note lto(IMUSANT_pitch::F, 3, 2, IMUSANT_pitch::natural, IMUSANT_duration::minim);
    IMUSANT_note ldiss(IMUSANT_pitch::F, 3, 2, IMUSANT_pitch::natural, IMUSANT_duration::minim);
    IMUSANT_note lfrom(IMUSANT_pitch::F, 3, 2, IMUSANT_pitch::natural, IMUSANT_duration::minim);
    
    CATSMAT_dissonance dissonance(uto, lto, udiss, ldiss, ufrom, lfrom, false);
    
    ASSERT_EQ(dissonance.getSchemata().getType(), CATSMAT_dissonance::schemata::lower_escape_tone);
}

const string TestScore_Cerreto_CM_canon_Dissonances_Expected = "-per4, quarter, Ascending Passing Tone: 5\n-per4, quarter, Descending Passing Tone: 5\n";
//test for ascending and descending passing tones in canon in contrary motion
TEST_F(CATSMAT_Dissonance_Classifier_Tests, TestScore_Cerreto_CM_canon) {
    
    std::stringstream the_type_as_stringstream;
    S_IMUSANT_score imusant_score =  testUtil.InitialiseScoreFromFile("Cerreto-CM_canon_Della_prattica_musica_p222.musicxml");
    S_CATSMAT_cp_matrix_visitor matrix = new_CATSMAT_object<CATSMAT_cp_matrix_visitor>();
    imusant_score->accept(*matrix);
    
    //use profile to count dissonances
    std::map<CATSMAT_dissonance,int> dissonance_profile;
    
    //set internal parameters called within search functions
    CATSMAT_dyad_sequences      dyads;
    dyads.set_ignore_dissonances(false);
    dyads.set_ignore_repeated(false);
    
    if (imusant_score!=nullptr)
    {
        dyads.Visit(*matrix);
        for (auto dyads : dyads.getSequences())
        {
            vector<IMUSANT_interval> v = dyads->getIntervals();
            for (auto dyad = v.begin(); dyad!=v.end(); ++dyad)
            {
                if (dyad->getQuality()==IMUSANT_interval::dissonant)
                {
                    //back reference to cp_matrix?
                    IMUSANT_range location = dyad->getLocation();
                    auto chord = matrix->getCPmatrix().begin();
                    IMUSANT_note u1, u2, u3, l1, l2, l3;
                    
                    //rough test for known score parameters of two voices
                    for ( ; chord != matrix->getCPmatrix().end(); chord++)
                    {
                        CATSMAT_chord i = **chord;
                        u2 = *i[0];
                        l2 = *i[1];
                        if (i[0]->getMeasureNum() == location.first.measure && i[0]->getNoteIndex() == location.first.note_index)
                        {
                            CATSMAT_chord h = **std::prev(chord);
                            CATSMAT_chord j = **std::next(chord);
                            u1 = *h[0]; l1 = *h[1];
                            u3 = *j[0]; l3 = *j[1];
                            break;
                        }
                    }
                    //find dissonance
                    CATSMAT_dissonance d(u1,l1,u2,l2,u3,l3);
                    dissonance_profile[d] = dissonance_profile[d] + 1;
                }
            }
        }
        
        for (auto i: dissonance_profile)
        {
            the_type_as_stringstream << i.first << ": " << i.second << std::endl;;
        }
        
    }
    
    string the_types_as_string = the_type_as_stringstream.str();
    ASSERT_EQ(TestScore_Cerreto_CM_canon_Dissonances_Expected, the_types_as_string);
}

const string TestScore_Zarlino_Bicinia_1_Expected = "";

TEST_F(CATSMAT_Dissonance_Classifier_Tests, TestScore_Zarlino_Bicinia_1) {
    
    std::stringstream the_type_as_stringstream;
    S_IMUSANT_score imusant_score =  testUtil.InitialiseScoreFromFile("Zarlino_Bicinia_1.xml");
    S_CATSMAT_cp_matrix_visitor matrix = new_CATSMAT_object<CATSMAT_cp_matrix_visitor>();
    imusant_score->accept(*matrix);
    
    //use profile to count dissonances
    std::map<CATSMAT_dissonance,int> dissonance_profile;
    CATSMAT_dyad_sequences      dyads;
    
    //set internal parameters called within search functions
    dyads.set_ignore_dissonances(false);
    dyads.set_ignore_repeated(false);
    
    if (imusant_score!=nullptr)
    {
        dyads.Visit(*matrix);
        for (auto dyads : dyads.getSequences())
        {
            vector<IMUSANT_interval> v = dyads->getIntervals();
            auto chord = matrix->getCPmatrix().begin(); //iterator
            
            for (auto dyad = v.begin(); dyad!=v.end(); ++dyad)
            {
                if (dyad->getQuality()==IMUSANT_interval::dissonant)
                {
                    //back reference to cp_matrix?
                    IMUSANT_range location = dyad->getLocation();
                    
                    //rough test for known score parameters of two voices
                    for ( ; chord != matrix->getCPmatrix().end(); chord++)
                    {
                        IMUSANT_note u1, u2, u3, l1, l2, l3, copy;
                        CATSMAT_chord i = **chord;
                        u2 = *i[0];
                        l2 = *i[1];
                        if (i[0]->getMeasureNum() == location.first.measure && i[0]->getNoteIndex() == location.first.note_index)
                        {
                            CATSMAT_chord h = **std::prev(chord);
                            CATSMAT_chord j = **std::next(chord);
                            u1 = *h[0]; l1 = *h[1];
                            u3 = *j[0]; l3 = *j[1];
                            
                            //find dissonance
                            CATSMAT_dissonance d(u1,l1,u2,l2,u3,l3);
                            dissonance_profile[d] = dissonance_profile[d] + 1;
                            break;
                        }
                    }
                    
                }
            }
        }
        
        for (auto i: dissonance_profile)
        {
            the_type_as_stringstream << i.first << ": " << i.second << std::endl;;
        }
        
    }
    
    string the_types_as_string = the_type_as_stringstream.str();
    ASSERT_EQ(TestScore_Zarlino_Bicinia_1_Expected, the_types_as_string);
}

const string TestScore_Zarlino_Bicinia_1_2_Expected = "";

TEST_F(CATSMAT_Dissonance_Classifier_Tests, TestScore_Zarlino_Bicinia_1_2) {
    
    std::stringstream the_type_as_stringstream;
    S_IMUSANT_score imusant_score =  testUtil.InitialiseScoreFromFile("Zarlino_Bicinia_1.xml");
    S_CATSMAT_cp_matrix_visitor matrix = new_CATSMAT_object<CATSMAT_cp_matrix_visitor>();
    imusant_score->accept(*matrix);
    
    //use profile to count dissonances
    std::map<CATSMAT_dissonance,int> dissonance_profile;
    CATSMAT_dyad_sequences      dyads;
    
    //set internal parameters called within search functions
    dyads.set_ignore_dissonances(false);
    dyads.set_ignore_repeated(false);
    
    if (imusant_score!=nullptr)
    {
        dyads.Visit(*matrix);
        for (auto dyads : dyads.getSequences())
        {
            vector<IMUSANT_interval> v = dyads->getIntervals();
            CATSMAT_cp_matrix::Matrix_iterator chord = matrix->getCPmatrix().begin(); //iterator
            
            for (auto dyad = v.begin(); dyad!=v.end(); ++dyad)
            {
                
                if (dyad->getQuality()==IMUSANT_interval::dissonant)
                {
                    //back reference to cp_matrix?
                    IMUSANT_range location = dyad->getLocation();
                    
                    //rough test for known score parameters of two voices
                    for ( ; chord != matrix->getCPmatrix().end(); chord++)
                    {
                        IMUSANT_note u1, u2, u3, l1, l2, l3, copy;
                        CATSMAT_chord i = **chord;
                        u2 = *i[0];
                        l2 = *i[1];
                        
                        if (i[0]->getMeasureNum() == location.first.measure && i[0]->getNoteIndex() == location.first.note_index)
                        {
                            bool accented = false;
                            
                            CATSMAT_chord h = **std::prev(chord);
                            CATSMAT_chord j = **std::next(chord);
                            u1 = *h[0]; l1 = *h[1];
                            u3 = *j[0]; l3 = *j[1];
                            
                            accented = matrix->isAccented(chord, IMUSANT_duration(IMUSANT_duration::minim));
                            
                            //find dissonance
                            CATSMAT_dissonance d(u1,l1,u2,l2,u3,l3,accented);
                            //dissonance_profile[d] = dissonance_profile[d] + 1;
                            the_type_as_stringstream << "m." << location.first.measure << "." << location.first.note_index << "\t" << d <<  std::endl;
                            break;
                        }
                    }
                    
                }
            }
        }
    }
    
    string the_types_as_string = the_type_as_stringstream.str();
    ASSERT_EQ(TestScore_Zarlino_Bicinia_1_2_Expected, the_types_as_string);
}
