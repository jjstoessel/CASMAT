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
    
    vector<float> getOverallStrengthVectorFromPart(string part_id)
    {
        S_IMUSANT_part part;
        fScore_ParserTest1->getPartById(part_id, part);
        
        IMUSANT_segmented_part_LBDM seg_part(part);
        
        vector<float> lbsp = seg_part.getOverallLocalBoundaryStrengthProfile();
        return lbsp;
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


const int P1_COUNT = 17;
const int P2_COUNT = 12;
const int PITCH_STRENGTH_EXPECTED = 0;
const int IOI_STRENGTH_EXPECTED = 1;
const int WEIGHTED_AVG_STRENGTH_EXPECTED = 2;

float strength_part1_expected[P1_COUNT][3] =
{
//  PITCH       IOI             WEIGHTED AVG
    {5184,      65536,          17032},     // 0
    {0,         0,              0},         // 1
    {0,         0,              0},         // 2
    {0,         85.3333,        21.3333},   // 3
    {0,         170.6666,       42.6666},   // 4
    {0,         170.6666,       42.6666},   // 5
    {0,         1137.7777,      284.4444},  // 6
    {0,         99.5555,        24.8888},   // 7
    {0,         0,              0},         // 8
    {0,         0,              0},         // 9
    {0,         76.8003,        19.2000},   // 10
    {0,         380.3428,       95.0857},   // 11
    {0,         246.8571,       61.7142},   // 12
    {0,         128.0000,       32.0000},   // 13
    {0,         384.0000,       96.0000},   // 14
    {0,         163.5555,       40.8888},   // 15
    {0,         796.4444,       199.1111}   // 16
};

float strength_part2_expected[P2_COUNT][3] =
{
//  PITCH           IOI     WEIGHETD AVG
    {5184.5039,     262144,     66184.0625},    // 0
    {1.5107,        0,          0.1888},        // 1
    {2.0004,        0,          0.2500},        // 2
    {2.0004,        0,          0.2500},        // 3
    {1.4887,        0,          0.1860},        // 4
    {1.5119,        0,          0.1889},        // 5
    {2.0005,        0,          0.2500},        // 6
    {2.9190,        0,          0.3648},        // 7
    {3.5301,        0,          0.4412},        // 8
    {3.9444,        0,          0.4930},        // 9
    {74.5899,       0,          9.3237},        // 10
    {1.34217702E+9, 0,          static_cast<float>(167772128)}     // 11
};

TEST_F(IMUSANT_segmented_part_LBDM_Tests, pitch_interval_profile_P1_calculateStrengthVector)
{
    S_IMUSANT_part part;
    fScore_ParserTest1->getPartById("P1", part);
    
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
        ASSERT_TRUE(equalWithinTollerance(strength_part1_expected[jdex][PITCH_STRENGTH_EXPECTED], profile.strength_vector[jdex]))
                << "Failed with jdex = " << jdex
                << "Expected " << strength_part1_expected[jdex][PITCH_STRENGTH_EXPECTED]
                << ". Received " << profile.strength_vector[jdex]
                << endl;
    }
}


TEST_F(IMUSANT_segmented_part_LBDM_Tests, ioi_interval_profile_P1_calculateStrengthVector)
{
    S_IMUSANT_part part;
    fScore_ParserTest1->getPartById("P1", part);
    
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
        ASSERT_TRUE(equalWithinTollerance(strength_part1_expected[jdex][IOI_STRENGTH_EXPECTED], profile.strength_vector[jdex]))
                << "Failed with jdex = " << jdex
                << ". Expected " << strength_part1_expected[jdex][IOI_STRENGTH_EXPECTED]
                << ". Received " << profile.strength_vector[jdex]
                << endl;
    }
    
}

TEST_F(IMUSANT_segmented_part_LBDM_Tests, calculateOverallLocalBoundaryStrengthProfile_P1)
{
    vector<float> lbsp = getOverallStrengthVectorFromPart("P1");

    for (int jdex = 0 ; jdex < P1_COUNT; jdex++)
    {
        ASSERT_TRUE(equalWithinTollerance(strength_part1_expected[jdex][WEIGHTED_AVG_STRENGTH_EXPECTED], lbsp[jdex]))
            << "Failed with jdex = " << jdex
            << ". Expected " << strength_part1_expected[jdex][WEIGHTED_AVG_STRENGTH_EXPECTED]
            << ". Received " << lbsp[jdex]
            << endl;
    }
    
}

TEST_F(IMUSANT_segmented_part_LBDM_Tests, pitch_interval_profile_P2_calculateStrengthVector)
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
    
    for (int jdex = 0 ; jdex < P2_COUNT; jdex++)
    {
        ASSERT_TRUE(equalWithinTollerance(strength_part2_expected[jdex][PITCH_STRENGTH_EXPECTED], profile.strength_vector[jdex]))
            << "Failed with jdex = " << jdex
            << "Expected " << strength_part2_expected[jdex][PITCH_STRENGTH_EXPECTED]
            << ". Received " << profile.strength_vector[jdex]
            << endl;
    }
}


TEST_F(IMUSANT_segmented_part_LBDM_Tests, ioi_interval_profile_P2_calculateStrengthVector)
{
    S_IMUSANT_part part;
    fScore_ParserTest1->getPartById("P2", part);
    
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
        ASSERT_TRUE(equalWithinTollerance(strength_part2_expected[jdex][IOI_STRENGTH_EXPECTED], profile.strength_vector[jdex]))
        << "Failed with jdex = " << jdex
        << ". Expected " << strength_part2_expected[jdex][IOI_STRENGTH_EXPECTED]
        << ". Received " << profile.strength_vector[jdex]
        << endl;
    }
    
}

TEST_F(IMUSANT_segmented_part_LBDM_Tests, calculateOverallLocalBoundaryStrengthProfile_P2)
{
    vector<float> lbsp = getOverallStrengthVectorFromPart("P2");

    for (int jdex = 0 ; jdex < P2_COUNT; jdex++)
    {
        ASSERT_TRUE(equalWithinTollerance(strength_part2_expected[jdex][WEIGHTED_AVG_STRENGTH_EXPECTED], lbsp[jdex]))
            << "Failed with jdex = " << jdex
            << ". Expected " << strength_part2_expected[jdex][WEIGHTED_AVG_STRENGTH_EXPECTED]
            << ". Received " << lbsp[jdex]
            << endl;
    }
}



