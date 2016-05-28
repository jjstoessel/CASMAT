//
//  IMUSANT_interval_profile_LBDM_Tests.cpp
//  imusant
//
//  Created by Derrick Hill on 7/05/2016.
//
//

#include <stdio.h>

#include <math.h>

#include "gtest/gtest.h"

#include "IMUSANT_test_utilities.h"
#include "IMUSANT_segmented_part_LBDM_Expected.h"

#include "libIMUSANT.h"
#include <boost/filesystem.hpp>

using namespace IMUSANT;
using namespace boost;

// #define VERBOSE = 1;

// The fixture for testing class IMUSANT_interval_profile_LBDM
class IMUSANT_interval_profile_LBDM_Tests :
            public ::testing::Test,
            public IMUSANT_segmented_part_LBDM_Expected
{
    
protected:
    
    IMUSANT_interval_profile_LBDM_Tests()
    {
        // You can do set-up work for each test here.
        // This is a bit inefficient as each file gets parsed for each test case.
    }
    
    virtual ~IMUSANT_interval_profile_LBDM_Tests()
    {
        // You can do clean-up work that doesn't throw exceptions here.
    }
    
    virtual void SetUp() {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }
    
    static void SetUpTestCase() {
        _test_utils = new IMUSANT_test_utilities("IMUSANT_testdata");
        
        fScore_LBDM_Test1 = _test_utils->initialiseScoreFromFile("MusicXMLv3/LBDM_Segmented_Part_Test_1.xml");
        fScore_YankeeDoodle = _test_utils->initialiseScoreFromFile("MusicXMLv3/Yankee_Doodle.xml");
    }
    
    static IMUSANT_test_utilities * _test_utils;
    static S_IMUSANT_score fScore_LBDM_Test1;
    static S_IMUSANT_score fScore_YankeeDoodle;
    
};

IMUSANT_test_utilities * IMUSANT_interval_profile_LBDM_Tests::_test_utils = NULL;
S_IMUSANT_score IMUSANT_interval_profile_LBDM_Tests::fScore_LBDM_Test1 = NULL;
S_IMUSANT_score IMUSANT_interval_profile_LBDM_Tests::fScore_YankeeDoodle = NULL;

// ************* TEST CASES START HERE *********** //


TEST_F(IMUSANT_interval_profile_LBDM_Tests, IOI_profile_addProfileEntry)
{
    S_IMUSANT_part part;
    fScore_LBDM_Test1->getPartById("P1", part);
    
    IMUSANT_vector<S_IMUSANT_note> notes = part->notes();
    IMUSANT_IOI_interval_profile ioi_profile;
    ioi_profile.initialise(notes.size());
    
    for (int index = 0; index < notes.size(); index++)
    {
        ioi_profile.addProfileEntry(index, notes);
    }
    
    ASSERT_EQ(17, ioi_profile.profile_vector.size());
    ASSERT_EQ(256, ioi_profile.profile_vector[0]);
    ASSERT_EQ(256, ioi_profile.profile_vector[1]);
    ASSERT_EQ(256, ioi_profile.profile_vector[2]);
    ASSERT_EQ(256, ioi_profile.profile_vector[3]);
    ASSERT_EQ(512, ioi_profile.profile_vector[4]);
    ASSERT_EQ(512, ioi_profile.profile_vector[5]);
    ASSERT_EQ(1024, ioi_profile.profile_vector[6]);
    ASSERT_EQ(128, ioi_profile.profile_vector[7]);
    ASSERT_EQ(128, ioi_profile.profile_vector[8]);
    ASSERT_EQ(128, ioi_profile.profile_vector[9]);
    ASSERT_EQ(128, ioi_profile.profile_vector[10]);
    ASSERT_EQ(512, ioi_profile.profile_vector[11]);
    ASSERT_EQ(384, ioi_profile.profile_vector[12]);
    ASSERT_EQ(128, ioi_profile.profile_vector[13]);
    ASSERT_EQ(384, ioi_profile.profile_vector[14]);
    ASSERT_EQ(128, ioi_profile.profile_vector[15]);
    ASSERT_EQ(1024, ioi_profile.profile_vector[16]);
    
#ifdef VERBOSE
    cout << ioi_profile;
#endif
    
}

TEST_F(IMUSANT_interval_profile_LBDM_Tests, pitch_profile_addProfileEntry)
{
    S_IMUSANT_part part;
    fScore_LBDM_Test1->getPartById("P2", part);
    
    IMUSANT_vector<S_IMUSANT_note> notes = part->notes();
    IMUSANT_pitch_interval_profile pitch_profile;
    pitch_profile.initialise(notes.size());
    
    for (int index = 0; index < notes.size(); index++)
    {
        pitch_profile.addProfileEntry(index, notes);
    }
    
    
    ASSERT_EQ(12, pitch_profile.profile_vector.size());
    
    ASSERT_EQ(72, pitch_profile.profile_vector[0]);
    ASSERT_EQ(71, pitch_profile.profile_vector[1]);
    ASSERT_EQ(69, pitch_profile.profile_vector[2]);
    ASSERT_EQ(67, pitch_profile.profile_vector[3]);
    ASSERT_EQ(65, pitch_profile.profile_vector[4]);
    ASSERT_EQ(64, pitch_profile.profile_vector[5]);
    ASSERT_EQ(62, pitch_profile.profile_vector[6]);
    ASSERT_EQ(60, pitch_profile.profile_vector[7]);
    ASSERT_EQ(64, pitch_profile.profile_vector[8]);
    ASSERT_EQ(67, pitch_profile.profile_vector[9]);
    ASSERT_EQ(72, pitch_profile.profile_vector[10]);
    ASSERT_EQ(0, pitch_profile.profile_vector[11]);
    
    
#ifdef VERBOSE
    cout << pitch_profile;
#endif
}

TEST_F(IMUSANT_interval_profile_LBDM_Tests, rest_profile_addProfileEntry)
{
    S_IMUSANT_part part;
    fScore_LBDM_Test1->getPartById("P3", part);
    
    IMUSANT_vector<S_IMUSANT_note> notes = part->notes();
    IMUSANT_rest_interval_profile rest_profile;
    rest_profile.initialise(notes.size());
    
    for (int index = 0; index < notes.size(); index++)
    {
        rest_profile.addProfileEntry(index, notes);
    }
    
    ASSERT_EQ(19, rest_profile.profile_vector.size());
    ASSERT_EQ(0, rest_profile.profile_vector[0]);
    ASSERT_EQ(0, rest_profile.profile_vector[1]);
    ASSERT_EQ(0, rest_profile.profile_vector[2]);
    ASSERT_EQ(0, rest_profile.profile_vector[3]);
    ASSERT_EQ(1024, rest_profile.profile_vector[4]);
    ASSERT_EQ(0, rest_profile.profile_vector[5]);
    ASSERT_EQ(0, rest_profile.profile_vector[6]);
    ASSERT_EQ(0, rest_profile.profile_vector[7]);
    ASSERT_EQ(0, rest_profile.profile_vector[8]);
    ASSERT_EQ(0, rest_profile.profile_vector[9]);
    ASSERT_EQ(0, rest_profile.profile_vector[10]);
    ASSERT_EQ(512, rest_profile.profile_vector[11]);
    ASSERT_EQ(0, rest_profile.profile_vector[12]);
    ASSERT_EQ(256, rest_profile.profile_vector[13]);
    ASSERT_EQ(0, rest_profile.profile_vector[14]);
    ASSERT_EQ(256, rest_profile.profile_vector[15]);
    ASSERT_EQ(0, rest_profile.profile_vector[16]);
    ASSERT_EQ(256, rest_profile.profile_vector[17]);
    ASSERT_EQ(0, rest_profile.profile_vector[18]);
    
#ifdef VERBOSE
    cout << rest_profile;
#endif
    
}


TEST_F(IMUSANT_interval_profile_LBDM_Tests, pitch_profile_calculateChangeVector)
{
    S_IMUSANT_part part;
    fScore_LBDM_Test1->getPartById("P2", part);
    
    IMUSANT_vector<S_IMUSANT_note> notes = part->notes();
    IMUSANT_pitch_interval_profile profile;
    profile.initialise(notes.size());
    
    for (int index = 0; index < notes.size(); index++)
    {
        profile.addProfileEntry(index, notes);
    }
    
    profile.calculateChangeVector();
    
    
    ASSERT_TRUE(equalWithinTollerance(72.000, profile.change_vector[0]));
    ASSERT_TRUE(equalWithinTollerance(0.0069, profile.change_vector[1]));
    ASSERT_TRUE(equalWithinTollerance(0.0142, profile.change_vector[2]));
    ASSERT_TRUE(equalWithinTollerance(0.0147, profile.change_vector[3]));
    ASSERT_TRUE(equalWithinTollerance(0.0151, profile.change_vector[4]));
    ASSERT_TRUE(equalWithinTollerance(0.0077, profile.change_vector[5]));
    ASSERT_TRUE(equalWithinTollerance(0.0158, profile.change_vector[6]));
    ASSERT_TRUE(equalWithinTollerance(0.0163, profile.change_vector[7]));
    ASSERT_TRUE(equalWithinTollerance(0.0322, profile.change_vector[8]));
    ASSERT_TRUE(equalWithinTollerance(0.0229, profile.change_vector[9]));
    ASSERT_TRUE(equalWithinTollerance(0.0359, profile.change_vector[10]));
    
#ifdef VERBOSE
    cout << profile;
#endif
}

TEST_F(IMUSANT_interval_profile_LBDM_Tests, pitch_profile_P1_calculateStrengthVector)
{
    S_IMUSANT_part part;
    fScore_LBDM_Test1->getPartById("P1", part);
    
    IMUSANT_vector<S_IMUSANT_note> notes = part->notes();
    IMUSANT_pitch_interval_profile profile;
    profile.initialise(notes.size());
    
    for (int index = 0; index < notes.size(); index++)
    {
        profile.addProfileEntry(index, notes);
    }
    
    profile.calculateChangeVector();
    profile.calculateStrengthVector();
    
    for (int jdex = 0 ; jdex < P1_COUNT; jdex++)
    {
        ASSERT_TRUE(equalWithinTollerance(strength_P1_expected[jdex][PITCH_STRENGTH_EXPECTED], profile.strength_vector[jdex]))
        << "Failed with jdex = " << jdex
        << "Expected " << strength_P1_expected[jdex][PITCH_STRENGTH_EXPECTED]
        << ". Received " << profile.strength_vector[jdex]
        << endl;
    }
    
#ifdef VERBOSE
    cout << profile;
#endif
}


TEST_F(IMUSANT_interval_profile_LBDM_Tests, IOI_profile_P1_calculateStrengthVector)
{
    S_IMUSANT_part part;
    fScore_LBDM_Test1->getPartById("P1", part);
    
    IMUSANT_vector<S_IMUSANT_note> notes = part->notes();
    IMUSANT_IOI_interval_profile profile;
    profile.initialise(notes.size());
    
    for (int index = 0; index < notes.size(); index++)
    {
        profile.addProfileEntry(index, notes);
    }
    
    profile.calculateChangeVector();
    profile.calculateStrengthVector();
    
    for (int jdex = 0 ; jdex < P1_COUNT; jdex++)
    {
        ASSERT_TRUE(equalWithinTollerance(strength_P1_expected[jdex][IOI_STRENGTH_EXPECTED], profile.strength_vector[jdex]))
        << "Failed with jdex = " << jdex
        << ". Expected " << strength_P1_expected[jdex][IOI_STRENGTH_EXPECTED]
        << ". Received " << profile.strength_vector[jdex]
        << endl;
    }
    
#ifdef VERBOSE
    cout << profile;
#endif
    
}


TEST_F(IMUSANT_interval_profile_LBDM_Tests, pitch_profile_P2_calculateStrengthVector)
{
    S_IMUSANT_part part;
    fScore_LBDM_Test1->getPartById("P2", part);
    
    IMUSANT_vector<S_IMUSANT_note> notes = part->notes();
    IMUSANT_pitch_interval_profile profile;
    profile.initialise(notes.size());
    
    for (int index = 0; index < notes.size(); index++)
    {
        profile.addProfileEntry(index, notes);
    }
    
    profile.calculateChangeVector();
    profile.calculateStrengthVector();
    
    for (int jdex = 0 ; jdex < P2_COUNT; jdex++)
    {
        ASSERT_TRUE(equalWithinTollerance(strength_P2_expected[jdex][PITCH_STRENGTH_EXPECTED], profile.strength_vector[jdex]))
        << "Failed with jdex = " << jdex
        << " Expected " << strength_P2_expected[jdex][PITCH_STRENGTH_EXPECTED]
        << ". Received " << profile.strength_vector[jdex]
        << endl;
    }
    
#ifdef VERBOSE
    cout << profile;
#endif
    
}


TEST_F(IMUSANT_interval_profile_LBDM_Tests, IOI_profile_P2_calculateStrengthVector)
{
    S_IMUSANT_part part;
    fScore_LBDM_Test1->getPartById("P2", part);
    
    IMUSANT_vector<S_IMUSANT_note> notes = part->notes();
    IMUSANT_IOI_interval_profile profile;
    profile.initialise(notes.size());
    
    for (int index = 0; index < notes.size(); index++)
    {
        profile.addProfileEntry(index, notes);
    }
    
    profile.calculateChangeVector();
    profile.calculateStrengthVector();
    
    for (int jdex = 0 ; jdex < P2_COUNT; jdex++)
    {
        ASSERT_TRUE(equalWithinTollerance(strength_P2_expected[jdex][IOI_STRENGTH_EXPECTED], profile.strength_vector[jdex]))
        << "Failed with jdex = " << jdex
        << ". Expected " << strength_P2_expected[jdex][IOI_STRENGTH_EXPECTED]
        << ". Received " << profile.strength_vector[jdex]
        << endl;
    }
    
#ifdef VERBOSE
    cout << profile;
#endif
    
}

TEST_F(IMUSANT_interval_profile_LBDM_Tests, rest_profile_P3_calculateStrengthVector)
{
    S_IMUSANT_part part;
    fScore_LBDM_Test1->getPartById("P3", part);
    
    IMUSANT_vector<S_IMUSANT_note> notes = part->notes();
    IMUSANT_rest_interval_profile profile;
    profile.initialise(notes.size());
    
    for (int index = 0; index < notes.size(); index++)
    {
        profile.addProfileEntry(index, notes);
    }
    
    profile.calculateChangeVector();
    profile.calculateStrengthVector();
    
#ifdef VERBOSE
    cout << profile;
#endif
    
    for (int jdex = 0 ; jdex < P3_COUNT; jdex++)
    {
        ASSERT_TRUE(equalWithinTollerance(strength_P3_expected[jdex][REST_STRENGTH_EXPECTED], profile.strength_vector[jdex]))
        << "Failed with jdex = " << jdex
        << ". Expected " << strength_P3_expected[jdex][REST_STRENGTH_EXPECTED]
        << ". Received " << profile.strength_vector[jdex]
        << endl;
    }
    
#ifdef VERBOSE
    cout << profile;
#endif
    
}

