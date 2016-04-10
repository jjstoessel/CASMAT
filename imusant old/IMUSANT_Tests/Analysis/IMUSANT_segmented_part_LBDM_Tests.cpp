//
//  IMUSANT_segmented_part_LBDM_Tests.cpp
//  imusant
//
//  Created by Derrick Hill on 15/03/2016.
//
//

#include <stdio.h>
#include <math.h>

#include "gtest/gtest.h"

#include "IMUSANT_test_utilities.h"

#include "libIMUSANT.h"
#include <boost/filesystem.hpp>

using namespace IMUSANT;
using namespace boost;

// #define VERBOSE = 1;

// The fixture for testing class IMUSANT_pitch.
class IMUSANT_segmented_part_LBDM_Tests : public ::testing::Test {
    
protected:
    
    IMUSANT_segmented_part_LBDM_Tests()
    {
        // You can do set-up work for each test here.
        // This is a bit inefficient as each file gets parsed for each test case.
    }
    
    virtual ~IMUSANT_segmented_part_LBDM_Tests()
    {
        // You can do clean-up work that doesn't throw exceptions here.
    }
    
    virtual void SetUp() {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }
    
    bool equalWithinTollerance(float f1, float f2)
    {
        return (fabs(f1 - f2) < 0.001);
    }
    
    static void SetUpTestCase() {
        _test_utils = new IMUSANT_test_utilities("IMUSANT_testdata");
        
        fScore_ParserTest1 = _test_utils->initialiseScoreFromFile("LBDM_Segmented_Part_Test_1.xml");

    }
    
    static IMUSANT_test_utilities * _test_utils;
    static S_IMUSANT_score fScore_ParserTest1;
    
};

IMUSANT_test_utilities * IMUSANT_segmented_part_LBDM_Tests::_test_utils = NULL;
S_IMUSANT_score IMUSANT_segmented_part_LBDM_Tests::fScore_ParserTest1 = NULL;



// ************* TEST CASES START HERE *********** //


TEST_F(IMUSANT_segmented_part_LBDM_Tests, Constructor)
{
    S_IMUSANT_part part = new_IMUSANT_part();
    
    IMUSANT_segmented_part_LBDM * segmented_part = new IMUSANT_segmented_part_LBDM(part);
    
    ASSERT_FALSE(segmented_part == NULL);

    delete segmented_part;
}


TEST_F(IMUSANT_segmented_part_LBDM_Tests, IOI_profile_addProfileEntry)
{
    S_IMUSANT_part part;
    fScore_ParserTest1->getPartById("P1", part);
    
    IMUSANT_vector<S_IMUSANT_note> notes = part->notes();
    IMUSANT_IOI_interval_profile ioi_profile;
    ioi_profile.initialise(notes.size());
    
    for (int index = 0; index < notes.size(); index++)
    {
        ioi_profile.addProfileEntry(index, notes);
    }

    ASSERT_EQ(17, ioi_profile.intervals.size());
    ASSERT_EQ(256, ioi_profile.intervals[0]);
    ASSERT_EQ(256, ioi_profile.intervals[1]);
    ASSERT_EQ(256, ioi_profile.intervals[2]);
    ASSERT_EQ(256, ioi_profile.intervals[3]);
    ASSERT_EQ(512, ioi_profile.intervals[4]);
    ASSERT_EQ(512, ioi_profile.intervals[5]);
    ASSERT_EQ(1024, ioi_profile.intervals[6]);
    ASSERT_EQ(128, ioi_profile.intervals[7]);
    ASSERT_EQ(128, ioi_profile.intervals[8]);
    ASSERT_EQ(128, ioi_profile.intervals[9]);
    ASSERT_EQ(128, ioi_profile.intervals[10]);
    ASSERT_EQ(512, ioi_profile.intervals[11]);
    ASSERT_EQ(384, ioi_profile.intervals[12]);
    ASSERT_EQ(128, ioi_profile.intervals[13]);
    ASSERT_EQ(384, ioi_profile.intervals[14]);
    ASSERT_EQ(128, ioi_profile.intervals[15]);
    ASSERT_EQ(1024, ioi_profile.intervals[16]);
              
}

TEST_F(IMUSANT_segmented_part_LBDM_Tests, pitch_profile_addProfileEntry)
{
    S_IMUSANT_part part;
    fScore_ParserTest1->getPartById("P2", part);
    
    IMUSANT_vector<S_IMUSANT_note> notes = part->notes();
    IMUSANT_pitch_interval_profile pitch_profile;
    pitch_profile.initialise(notes.size());
    
    for (int index = 0; index < notes.size(); index++)
    {
        pitch_profile.addProfileEntry(index, notes);
    }
    
    
    ASSERT_EQ(12, pitch_profile.intervals.size());
    
    
#ifdef VERBOSE
    for (int index = 0 ; index < pitch_profile.intervals.size() ; index ++ )
    {
        cout << pitch_profile.intervals[index] << endl;
    }
#endif
    
    ASSERT_EQ(72, pitch_profile.intervals[0]);
    ASSERT_EQ(71, pitch_profile.intervals[1]);
    ASSERT_EQ(69, pitch_profile.intervals[2]);
    ASSERT_EQ(67, pitch_profile.intervals[3]);
    ASSERT_EQ(65, pitch_profile.intervals[4]);
    ASSERT_EQ(64, pitch_profile.intervals[5]);
    ASSERT_EQ(62, pitch_profile.intervals[6]);
    ASSERT_EQ(60, pitch_profile.intervals[7]);
    ASSERT_EQ(64, pitch_profile.intervals[8]);
    ASSERT_EQ(67, pitch_profile.intervals[9]);
    ASSERT_EQ(72, pitch_profile.intervals[10]);
    ASSERT_EQ(IMUSANT_pitch::tpcUndefined, pitch_profile.intervals[11]);
}

TEST_F(IMUSANT_segmented_part_LBDM_Tests, interval_profile_calculateChangeVector)
{
    S_IMUSANT_part part;
    fScore_ParserTest1->getPartById("P2", part);
    
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
}

TEST_F(IMUSANT_segmented_part_LBDM_Tests, interval_profile_calculateStrengthVector)
{
    S_IMUSANT_part part;
    fScore_ParserTest1->getPartById("P2", part);
    
    IMUSANT_vector<S_IMUSANT_note> notes = part->notes();
    IMUSANT_pitch_interval_profile profile;
    profile.initialise(notes.size());
    
    for (int index = 0; index < notes.size(); index++)
    {
        profile.addProfileEntry(index, notes);
    }
    
    profile.calculateChangeVector();
    profile.calculateStrengthVector();
    
    ASSERT_TRUE(equalWithinTollerance(5184.5039, profile.strength_vector[0]));
    ASSERT_TRUE(equalWithinTollerance(1.5107, profile.strength_vector[1]));
    ASSERT_TRUE(equalWithinTollerance(2.0004, profile.strength_vector[2]));
    ASSERT_TRUE(equalWithinTollerance(2.0004, profile.strength_vector[3]));
    ASSERT_TRUE(equalWithinTollerance(1.4887, profile.strength_vector[4]));
    ASSERT_TRUE(equalWithinTollerance(1.5119, profile.strength_vector[5]));
    ASSERT_TRUE(equalWithinTollerance(2.0005, profile.strength_vector[6]));
    ASSERT_TRUE(equalWithinTollerance(2.9190, profile.strength_vector[7]));
    ASSERT_TRUE(equalWithinTollerance(3.5301, profile.strength_vector[8]));
    ASSERT_TRUE(equalWithinTollerance(3.9444, profile.strength_vector[9]));
    ASSERT_TRUE(equalWithinTollerance(74.5899, profile.strength_vector[10]));
}