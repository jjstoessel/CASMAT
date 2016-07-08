
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
#include "IMUSANT_segmented_part_LBDM_Expected.h"

#include "libIMUSANT.h"
#include <boost/filesystem.hpp>

using namespace IMUSANT;

using namespace boost;

// #define VERBOSE = 1;

// The fixture for testing class IMUSANT_pitch.
class IMUSANT_segmented_part_LBDM_Tests :
            public ::testing::Test,
            public IMUSANT_segmented_part_LBDM_Expected
{
    
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
    
    static void SetUpTestCase() {
        _test_utils = new IMUSANT_test_utilities("IMUSANT_testdata");
        
        fScore_LBDM_Test1 = _test_utils->initialiseScoreFromFile("MusicXMLv3/LBDM_Segmented_Part_Test_1.xml");
        fScore_YankeeDoodle = _test_utils->initialiseScoreFromFile("MusicXMLv3/Yankee_Doodle.xml");
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

// ************* TEST CASES START HERE *********** //


TEST_F(IMUSANT_segmented_part_LBDM_Tests, Constructor)
{
    S_IMUSANT_part part = new_IMUSANT_part();
    
    IMUSANT_segmented_part_LBDM * segmented_part = new IMUSANT_segmented_part_LBDM(part);
    
    ASSERT_FALSE(segmented_part == NULL);

    delete segmented_part;
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


TEST_F(IMUSANT_segmented_part_LBDM_Tests, LongOutputOperator)
{
    string soprano_expected =
    "PART NAME - Soprano\nSTRENGTH VECTORS\nNOTE1                       NOTE2                                  PITCH             IOI            REST    WEIGHTED AVG\n{\n{-,                         {1.1, 72, 256},                      5184.00,        65536.00,            0.00,        17032.00},             // 0\n{{1.1, 72, 256},            {1.2, 72, 256},                         0.00,            0.00,            0.00,            0.00},             // 1\n{{1.2, 72, 256},            {1.3, 72, 256},                         0.00,            0.00,            0.00,            0.00},             // 2\n{{1.3, 72, 256},            {1.4, 72, 256},                         0.00,           85.33,            0.00,           21.33},             // 3\n{{1.4, 72, 256},            {2.1, 72, 512},                         0.00,          170.67,            0.00,           42.67},             // 4\n{{2.1, 72, 512},            {2.2, 72, 512},                         0.00,          170.67,            0.00,           42.67},             // 5\n{{2.2, 72, 512},            {3.1, 72, 1024},                        0.00,         1137.78,            0.00,          284.44},             // 6\n{{3.1, 72, 1024},           {4.1, 72, 128},                         0.00,           99.56,            0.00,           24.89},             // 7\n{{4.1, 72, 128},            {4.2, 72, 128},                         0.00,            0.00,            0.00,            0.00},             // 8\n{{4.2, 72, 128},            {4.3, 72, 128},                         0.00,            0.00,            0.00,            0.00},             // 9\n{{4.3, 72, 128},            {4.4, 72, 128},                         0.00,           76.80,            0.00,           19.20},             // 10\n{{4.4, 72, 128},            {4.5, 72, 512},                         0.00,          380.34,            0.00,           95.09},             // 11\n{{4.5, 72, 512},            {5.1, 72, 384},                         0.00,          246.86,            0.00,           61.71},             // 12\n{{5.1, 72, 384},            {5.2, 72, 128},                         0.00,          128.00,            0.00,           32.00},             // 13\n{{5.2, 72, 128},            {5.3, 72, 384},                         0.00,          384.00,            0.00,           96.00},             // 14\n{{5.3, 72, 384},            {5.4, 72, 128},                         0.00,          163.56,            0.00,           40.89},             // 15\n{{5.4, 72, 128},            {6.1, 72, 1024},                        0.00,          796.44,            0.00,          199.11},             // 16\n}\n";
    
    
    S_IMUSANT_part& soprano = fScore_LBDM_Test1->partlist()->getPart("P1");
    
    S_IMUSANT_segmented_part_LBDM seg_part = new_IMUSANT_segmented_part_LBDM(soprano);
    
    seg_part->getOverallLocalBoundaryStrengthProfile();
    
    stringstream soprano_long_actual;
    soprano_long_actual << *seg_part;
    ASSERT_EQ(soprano_expected, soprano_long_actual.str());

 }

TEST_F(IMUSANT_segmented_part_LBDM_Tests, ShortOutputOperator)
{
    string soprano_expected =
    "PART NAME - Soprano\nSTRENGTH VECTORS\n           PITCH             IOI            REST    WEIGHTED AVG\n{\n{         5184.00,        65536.00,            0.00,        17032.00},             // 0\n{            0.00,            0.00,            0.00,            0.00},             // 1\n{            0.00,            0.00,            0.00,            0.00},             // 2\n{            0.00,           85.33,            0.00,           21.33},             // 3\n{            0.00,          170.67,            0.00,           42.67},             // 4\n{            0.00,          170.67,            0.00,           42.67},             // 5\n{            0.00,         1137.78,            0.00,          284.44},             // 6\n{            0.00,           99.56,            0.00,           24.89},             // 7\n{            0.00,            0.00,            0.00,            0.00},             // 8\n{            0.00,            0.00,            0.00,            0.00},             // 9\n{            0.00,           76.80,            0.00,           19.20},             // 10\n{            0.00,          380.34,            0.00,           95.09},             // 11\n{            0.00,          246.86,            0.00,           61.71},             // 12\n{            0.00,          128.00,            0.00,           32.00},             // 13\n{            0.00,          384.00,            0.00,           96.00},             // 14\n{            0.00,          163.56,            0.00,           40.89},             // 15\n{            0.00,          796.44,            0.00,          199.11},             // 16\n}\n";
    
    
    S_IMUSANT_part& soprano = fScore_LBDM_Test1->partlist()->getPart("P1");
    
    S_IMUSANT_segmented_part_LBDM seg_part = new_IMUSANT_segmented_part_LBDM(soprano);
    
    seg_part->getOverallLocalBoundaryStrengthProfile();
    
    stringstream soprano_short_actual;
    soprano_short_actual << (*seg_part).printForTesting();
    ASSERT_EQ(soprano_expected, soprano_short_actual.str());
    
}

TEST_F(IMUSANT_segmented_part_LBDM_Tests, GetSegments_From_Score_LBDM_Test1)
{
    S_IMUSANT_part& soprano = fScore_YankeeDoodle->partlist()->getPart("P1");
    
    S_IMUSANT_segmented_part_LBDM seg_part = new_IMUSANT_segmented_part_LBDM(soprano);
    
    seg_part->getOverallLocalBoundaryStrengthProfile();
    
    vector<int> segment_boundaries = seg_part->getSegmentBoundaries();

    ASSERT_EQ(9, segment_boundaries.size()) << "Unexpected number of segment boundaries";
    
    ASSERT_EQ(0, segment_boundaries[0]);
    ASSERT_EQ(7, segment_boundaries[1]);
    ASSERT_EQ(12, segment_boundaries[2]);
    ASSERT_EQ(28, segment_boundaries[3]);
    ASSERT_EQ(35, segment_boundaries[4]);
    ASSERT_EQ(41, segment_boundaries[5]);
    ASSERT_EQ(49, segment_boundaries[6]);
    ASSERT_EQ(53, segment_boundaries[7]);
    ASSERT_EQ(55, segment_boundaries[8]);
    
    // ASSERT_TRUE(false) << "IMUSANT_segmented_part_LBDM_Tests::GetSegments - Deliberatly failing this test.";
}




