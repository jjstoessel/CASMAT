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

#define VERBOSE = 1;

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
        
        fScore_LBDM_Test1 = _test_utils->initialiseScoreFromFile("LBDM_Segmented_Part_Test_1.xml");
        fScore_YankeeDoodle = _test_utils->initialiseScoreFromFile("Yankee_Doodle.xml");
    }
    
    vector<float> getOverallStrengthVectorFromPart(S_IMUSANT_score score, string part_id)
    {
        S_IMUSANT_part part;
        score->getPartById(part_id, part);
        
        IMUSANT_segmented_part_LBDM seg_part(part);
        
        vector<float> lbsp = seg_part.getOverallLocalBoundaryStrengthProfile();
        
#ifdef VERBOSE
        cout << seg_part;
#endif
        return lbsp;
    }
    
    static IMUSANT_test_utilities * _test_utils;
    static S_IMUSANT_score fScore_LBDM_Test1;
    static S_IMUSANT_score fScore_YankeeDoodle;
    
};

IMUSANT_test_utilities * IMUSANT_segmented_part_LBDM_Tests::_test_utils = NULL;
S_IMUSANT_score IMUSANT_segmented_part_LBDM_Tests::fScore_LBDM_Test1 = NULL;
S_IMUSANT_score IMUSANT_segmented_part_LBDM_Tests::fScore_YankeeDoodle = NULL;



// ************* EXPECTED OUTPUT TABLES *********** //
const int P1_COUNT = 17;
const int P2_COUNT = 12;
const int P3_COUNT = 19;
const int YANKEEDOODLE_COUNT = 55;

const int PITCH_STRENGTH_EXPECTED = 0;
const int IOI_STRENGTH_EXPECTED = 1;
const int REST_STRENGTH_EXPECTED = 2;
const int WEIGHTED_AVG_STRENGTH_EXPECTED = 3;

float strength_P1_expected[P1_COUNT][4] =
{
//	PITCH               IOI                 REST			WEIGHTED AVG
    {5184.00000,		65536.00000,		0.0000,			17032.00000},		// 0
    {0.00000,			0.00000,			0.0000,			0.00000},			// 1
    {0.00000,			0.00000,			0.0000,			0.00000},			// 2
    {0.00000,			85.33334,			0.0000,			21.33333},			// 3
    {0.00000,			170.66667,			0.0000,			42.66667},			// 4
    {0.00000,			170.66667,			0.0000,			42.66667},			// 5
    {0.00000,			1137.77783,			0.0000,			284.44446},			// 6
    {0.00000,			99.55556,			0.0000,			24.88889},			// 7
    {0.00000,			0.00000,			0.0000,			0.00000},			// 8
    {0.00000,			0.00000,			0.0000,			0.00000},			// 9
    {0.00000,			76.80000,			0.0000,			19.20000},			// 10
    {0.00000,			380.34286,			0.0000,			95.08572},			// 11
    {0.00000,			246.85715,			0.0000,			61.71429},			// 12
    {0.00000,			128.00000,			0.0000,			32.00000},			// 13
    {0.00000,			384.00000,			0.0000,			96.00000},			// 14
    {0.00000,			163.55556,			0.0000,			40.88889},			// 15
    {0.00000,			796.44446,			0.0000,			199.11111}          // 16
};

float strength_P2_expected[P2_COUNT][4] =
{
    //	PITCH           IOI                 REST			WEIGHTED AVG
    {5184.50391,		262144.00000,		0.0000,			66184.06250},		// 0
    {1.51079,			0.00000,			0.0000,			0.18885},			// 1
    {2.00042,			0.00000,			0.0000,			0.25005},			// 2
    {2.00045,			0.00000,			0.0000,			0.25006},			// 3
    {1.48872,			0.00000,			0.0000,			0.18609},			// 4
    {1.51200,			0.00000,			0.0000,			0.18900},			// 5
    {2.00052,			0.00000,			0.0000,			0.25007},			// 6
    {2.91909,			0.00000,			0.0000,			0.36489},			// 7
    {3.53016,			0.00000,			0.0000,			0.44127},			// 8
    {3.94442,			0.00000,			0.0000,			0.49305},			// 9
    {74.58991,			0.00000,			0.0000,			9.32374},			// 10
    {00.00000,          0.00000,			512.0000,      64.00000},           // 11
};

float strength_P3_expected[P3_COUNT][4] =
{
//	PITCH               IOI                 REST                WEIGHTED AVG
    {2307.26221,		65536.00000,		0.00000,			16672.40820},			// 0
    {5.27992,			0.00000,			0.00000,			0.65999},               // 1
    {3.53794,			0.00000,			0.00000,			0.44224},               // 2
    {49.92000,			153.60001,			0.00000,			44.64000},              // 3
    {0.00000,           1228.80005,			2048.00000,			563.20001},             // 4
    {49.92000,			153.60001,			0.00000,			44.64000},              // 5
    {3.53794,			0.00000,			0.00000,			0.44224},               // 6
    {3.93336,			0.00000,			0.00000,			0.49167},               // 7
    {5.21739,			0.00000,			0.00000,			0.65217},               // 8
    {3.93336,			0.00000,			0.00000,			0.49167},               // 9
    {53.45795,			85.33334,			0.00000,			28.01558},              // 10
    {0.00000,           341.33334,			1024.00000,			213.33334},             // 11
    {120.00000,			85.33334,			0.00000,			36.33334},              // 12
    {0.00000,           0.00000,			512.00000,			64.00000},              // 13
    {110.00000,			0.00000,			0.00000,			13.75000},              // 14
    {0.00000,           0.00000,			512.00000,			64.00000},              // 15
    {104.00000,			0.00000,			0.00000,			13.00000},              // 16
    {0.00000,           85.33334,			512.00000,			85.33334},              // 17
    {48.00000,			170.66667,			0.00000,			48.66667},              // 18
};

float strength_YD_expected[YANKEEDOODLE_COUNT][4] =
{
//	PITCH               IOI                 REST			WEIGHTED AVG
    {4489.00000,		16384.00000,		0.0000,			4657.12500},		// 0
    {0.98529,			0.00000,			0.0000,			0.12316},			// 1
    {2.00042,			0.00000,			0.0000,			0.25005},			// 2
    {3.07226,			0.00000,			0.0000,			0.38403},			// 3
    {3.88406,			0.00000,			0.0000,			0.48551},			// 4
    {3.07226,			0.00000,			0.0000,			0.38403},			// 5
    {4.67274,			0.00000,			0.0000,			0.58409},			// 6
    {5.71608,			0.00000,			0.0000,			0.71451},			// 7
    {2.59690,			0.00000,			0.0000,			0.32461},			// 8
    {0.98529,			0.00000,			0.0000,			0.12316},			// 9
    {2.00042,			0.00000,			0.0000,			0.25005},			// 10
    {3.07226,			42.66667,			0.0000,			11.05070},			// 11
    {2.44579,			85.33334,			0.0000,			21.63906},			// 12
    {0.99248,			85.33334,			0.0000,			21.45739},			// 13
    {0.50376,			42.66667,			0.0000,			10.72964},			// 14
    {0.98529,			0.00000,			0.0000,			0.12316},			// 15
    {2.00042,			0.00000,			0.0000,			0.25005},			// 16
    {1.51079,			0.00000,			0.0000,			0.18885},			// 17
    {1.00699,			0.00000,			0.0000,			0.12587},			// 18
    {1.51079,			0.00000,			0.0000,			0.18885},			// 19
    {2.00042,			0.00000,			0.0000,			0.25005},			// 20
    {1.48905,			0.00000,			0.0000,			0.18613},			// 21
    {2.55874,			0.00000,			0.0000,			0.31984},			// 22
    {2.92163,			0.00000,			0.0000,			0.36520},			// 23
    {2.00049,			0.00000,			0.0000,			0.25006},			// 24
    {1.51163,			42.66667,			0.0000,			10.85562},			// 25
    {0.50376,			85.33334,			0.0000,			21.39630},			// 26
    {1.53435,			36.57143,			0.0000,			9.33465},			// 27
    {2.45026,			123.42857,			0.0000,			31.16343},			// 28
    {2.03077,			53.33334,			0.0000,			13.58718},			// 29
    {2.00049,			42.66667,			0.0000,			10.91673},			// 30
    {1.96825,			0.00000,			0.0000,			0.24603},			// 31
    {2.00049,			0.00000,			0.0000,			0.25006},			// 32
    {1.51163,			42.66667,			0.0000,			10.85562},			// 33
    {3.10066,			121.90477,			0.0000,			30.86378},			// 34
    {3.38723,			123.42857,			0.0000,			31.28055},			// 35
    {2.03175,			53.33334,			0.0000,			13.58730},			// 36
    {2.00052,			42.66667,			0.0000,			10.91673},			// 37
    {1.48781,			42.66667,			0.0000,			10.85264},			// 38
    {1.95861,			85.33334,			0.0000,			21.57816},			// 39
    {2.52132,			36.57143,			0.0000,			9.45802},			// 40
    {2.00049,			123.42857,			0.0000,			31.10720},			// 41
    {2.03077,			53.33334,			0.0000,			13.58718},			// 42
    {2.00049,			42.66667,			0.0000,			10.91673},			// 43
    {1.96825,			0.00000,			0.0000,			0.24603},			// 44
    {2.00049,			0.00000,			0.0000,			0.25006},			// 45
    {1.51163,			0.00000,			0.0000,			0.18895},			// 46
    {2.03811,			0.00000,			0.0000,			0.25476},			// 47
    {2.48152,			0.00000,			0.0000,			0.31019},			// 48
    {3.38723,			0.00000,			0.0000,			0.42340},			// 49
    {3.10066,			0.00000,			0.0000,			0.38758},			// 50
    {1.96291,			0.00000,			0.0000,			0.24536},			// 51
    {2.54804,			42.66667,			0.0000,			10.98517},			// 52
    {0.98529,			85.33334,			0.0000,			21.45650},			// 53
    {0.00000,			0.00000,			0.0000,			0.00000}			// 54
};



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
    fScore_LBDM_Test1->getPartById("P1", part);
    
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
    
#ifdef VERBOSE
    cout << ioi_profile;
#endif
    
}

TEST_F(IMUSANT_segmented_part_LBDM_Tests, pitch_profile_addProfileEntry)
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
    
    
    ASSERT_EQ(12, pitch_profile.intervals.size());
    
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
    ASSERT_EQ(0, pitch_profile.intervals[11]);
    
    
#ifdef VERBOSE
    cout << pitch_profile;
#endif
}

TEST_F(IMUSANT_segmented_part_LBDM_Tests, rest_profile_addProfileEntry)
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
    
    ASSERT_EQ(19, rest_profile.intervals.size());
    ASSERT_EQ(0, rest_profile.intervals[0]);
    ASSERT_EQ(0, rest_profile.intervals[1]);
    ASSERT_EQ(0, rest_profile.intervals[2]);
    ASSERT_EQ(0, rest_profile.intervals[3]);
    ASSERT_EQ(1024, rest_profile.intervals[4]);
    ASSERT_EQ(0, rest_profile.intervals[5]);
    ASSERT_EQ(0, rest_profile.intervals[6]);
    ASSERT_EQ(0, rest_profile.intervals[7]);
    ASSERT_EQ(0, rest_profile.intervals[8]);
    ASSERT_EQ(0, rest_profile.intervals[9]);
    ASSERT_EQ(0, rest_profile.intervals[10]);
    ASSERT_EQ(512, rest_profile.intervals[11]);
    ASSERT_EQ(0, rest_profile.intervals[12]);
    ASSERT_EQ(256, rest_profile.intervals[13]);
    ASSERT_EQ(0, rest_profile.intervals[14]);
    ASSERT_EQ(256, rest_profile.intervals[15]);
    ASSERT_EQ(0, rest_profile.intervals[16]);
    ASSERT_EQ(256, rest_profile.intervals[17]);
    ASSERT_EQ(0, rest_profile.intervals[18]);
    
#ifdef VERBOSE
    cout << rest_profile;
#endif
    
}


TEST_F(IMUSANT_segmented_part_LBDM_Tests, pitch_profile_calculateChangeVector)
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

TEST_F(IMUSANT_segmented_part_LBDM_Tests, pitch_profile_P1_calculateStrengthVector)
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


TEST_F(IMUSANT_segmented_part_LBDM_Tests, IOI_profile_P1_calculateStrengthVector)
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

TEST_F(IMUSANT_segmented_part_LBDM_Tests, calculateOverallLocalBoundaryStrengthProfile_P1)
{
    vector<float> lbsp = getOverallStrengthVectorFromPart(fScore_LBDM_Test1, "P1");

    for (int jdex = 0 ; jdex < P1_COUNT; jdex++)
    {
        ASSERT_TRUE(equalWithinTollerance(strength_P1_expected[jdex][WEIGHTED_AVG_STRENGTH_EXPECTED], lbsp[jdex]))
            << "Failed with jdex = " << jdex
            << ". Expected " << strength_P1_expected[jdex][WEIGHTED_AVG_STRENGTH_EXPECTED]
            << ". Received " << lbsp[jdex]
            << endl;
    }
    
}

TEST_F(IMUSANT_segmented_part_LBDM_Tests, pitch_profile_P2_calculateStrengthVector)
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


TEST_F(IMUSANT_segmented_part_LBDM_Tests, IOI_profile_P2_calculateStrengthVector)
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

TEST_F(IMUSANT_segmented_part_LBDM_Tests, rest_profile_P3_calculateStrengthVector)
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
    
        cout << profile;
    
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


TEST_F(IMUSANT_segmented_part_LBDM_Tests, calculateOverallLocalBoundaryStrengthProfile_P2)
{
    vector<float> lbsp = getOverallStrengthVectorFromPart(fScore_LBDM_Test1, "P2");

    for (int jdex = 0 ; jdex < P2_COUNT; jdex++)
    {
        ASSERT_TRUE(equalWithinTollerance(strength_P2_expected[jdex][WEIGHTED_AVG_STRENGTH_EXPECTED], lbsp[jdex]))
            << "Failed with jdex = " << jdex
            << ". Expected " << strength_P2_expected[jdex][WEIGHTED_AVG_STRENGTH_EXPECTED]
            << ". Received " << lbsp[jdex]
            << endl;
    }
}

TEST_F(IMUSANT_segmented_part_LBDM_Tests, calculateOverallLocalBoundaryStrengthProfile_P3)
{
    vector<float> lbsp = getOverallStrengthVectorFromPart(fScore_LBDM_Test1, "P3");
    
    for (int jdex = 0 ; jdex < P3_COUNT; jdex++)
    {
        ASSERT_TRUE(equalWithinTollerance(strength_P3_expected[jdex][WEIGHTED_AVG_STRENGTH_EXPECTED], lbsp[jdex]))
        << "Failed with jdex = " << jdex
        << ". Expected " << strength_P3_expected[jdex][WEIGHTED_AVG_STRENGTH_EXPECTED]
        << ". Received " << lbsp[jdex]
        << endl;
    }
}

TEST_F(IMUSANT_segmented_part_LBDM_Tests, calculateOverallLocalBoundaryStrengthProfile_YankeeDoodle)
{
    vector<float> lbsp = getOverallStrengthVectorFromPart(fScore_YankeeDoodle, "P1");
    
    for (int jdex = 0 ; jdex < YANKEEDOODLE_COUNT; jdex++)
    {
        ASSERT_TRUE(equalWithinTollerance(strength_YD_expected[jdex][WEIGHTED_AVG_STRENGTH_EXPECTED], lbsp[jdex]))
        << "Failed with jdex = " << jdex
        << ". Expected " << strength_YD_expected[jdex][WEIGHTED_AVG_STRENGTH_EXPECTED]
        << ". Received " << lbsp[jdex]
        << endl;
    }
}



