//
//  IMUSANT_segmented_part_fixed_period_Tests.cpp
//  catsmat
//
//  Created by Derrick Hill on 29/10/2016.
//
//

#include <stdio.h>

#include <stdio.h>
#include <math.h>

#include "gtest/gtest.h"

#include "IMUSANT_test_utilities.h"

#include "libIMUSANT.h"
#include <boost/filesystem.hpp>

using namespace IMUSANT;

using namespace boost;

//#define VERBOSE = 1;

// The fixture for testing class IMUSANT_pitch.
class IMUSANT_segmented_part_fixed_period_Tests :
public ::testing::Test
{
    
protected:
    
    IMUSANT_segmented_part_fixed_period_Tests()
    {
        // You can do set-up work for each test here.
        // This is a bit inefficient as each file gets parsed for each test case.
    }
    
    virtual ~IMUSANT_segmented_part_fixed_period_Tests()
    {
        // You can do clean-up work that doesn't throw exceptions here.
    }
    
    virtual void SetUp() {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }
    
    static void SetUpTestCase() {
        _test_utils = new IMUSANT_test_utilities("IMUSANT_testdata");
        
        fScore_Kyrie = _test_utils->initialiseScoreFromFile("MusicXMLv3/Kyrie.xml");
        fScore_Sanctus = _test_utils->initialiseScoreFromFile("MusicXMLv3/Sanctus.xml");
        fScore_YankeeDoodle = _test_utils->initialiseScoreFromFile("MusicXMLv3/Yankee_Doodle.xml");
    }
    
    
    static IMUSANT_test_utilities * _test_utils;
    static S_IMUSANT_score fScore_Kyrie;
    static S_IMUSANT_score fScore_Sanctus;
    static S_IMUSANT_score fScore_YankeeDoodle;
    
    
};

IMUSANT_test_utilities * IMUSANT_segmented_part_fixed_period_Tests::_test_utils = NULL;

S_IMUSANT_score IMUSANT_segmented_part_fixed_period_Tests::fScore_Kyrie = NULL;
S_IMUSANT_score IMUSANT_segmented_part_fixed_period_Tests::fScore_Sanctus = NULL;
S_IMUSANT_score IMUSANT_segmented_part_fixed_period_Tests::fScore_YankeeDoodle = NULL;

// ************* TEST CASES START HERE *********** //


TEST_F(IMUSANT_segmented_part_fixed_period_Tests, FixedPeriodSegmentation_Constructor)
{
    IMUSANT_segmented_part_fixed_period * segmented_part = new IMUSANT_segmented_part_fixed_period();
    S_IMUSANT_segmented_part_fixed_period s_segmented_part = new_IMUSANT_segmented_part_fixed_period();
    
    ASSERT_FALSE(segmented_part == NULL);
    ASSERT_FALSE(s_segmented_part == NULL);
    
    delete segmented_part;
}

TEST_F(IMUSANT_segmented_part_fixed_period_Tests, FixedPeriodSegmentation_Initialise_NotEnoughParts)
{
    S_IMUSANT_segmented_part_fixed_period s_segmented_part = new_IMUSANT_segmented_part_fixed_period();
    int ret_val = s_segmented_part->initialise(fScore_YankeeDoodle);
    
    ASSERT_EQ(IMUSANT_segmented_part_fixed_period::ERR_NOT_ENOUGH_PARTS, ret_val);
}

TEST_F(IMUSANT_segmented_part_fixed_period_Tests, FixedPeriodSegmentation_Initialise_Kyrie)
{
    S_IMUSANT_segmented_part_fixed_period s_segmented_part = new_IMUSANT_segmented_part_fixed_period();
    int ret_val = s_segmented_part->initialise(fScore_Kyrie);
    
    ASSERT_EQ(IMUSANT_segmented_part_fixed_period::SUCCESS, ret_val);
    ASSERT_EQ(7, s_segmented_part->get_period_length());
}

TEST_F(IMUSANT_segmented_part_fixed_period_Tests, FixedPeriodSegmentation_Initialise_Sanctus)
{
    S_IMUSANT_segmented_part_fixed_period s_segmented_part = new_IMUSANT_segmented_part_fixed_period();
    int ret_val = s_segmented_part->initialise(fScore_Sanctus);
    
    ASSERT_EQ(IMUSANT_segmented_part_fixed_period::SUCCESS, ret_val);
    ASSERT_EQ(5, s_segmented_part->get_period_length());
}

