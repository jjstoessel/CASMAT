////
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
        fScore_Josquin_MAF_Christe = _test_utils->initialiseScoreFromFile("MusicXMLv3/Josquin_MAF_Christe.xml");
    }
    
    
    static IMUSANT_test_utilities * _test_utils;
    static S_IMUSANT_score fScore_Kyrie;
    static S_IMUSANT_score fScore_Sanctus;
    static S_IMUSANT_score fScore_YankeeDoodle;
    static S_IMUSANT_score fScore_Josquin_MAF_Christe;
    
    
};

IMUSANT_test_utilities * IMUSANT_segmented_part_fixed_period_Tests::_test_utils = NULL;

S_IMUSANT_score IMUSANT_segmented_part_fixed_period_Tests::fScore_Kyrie = NULL;
S_IMUSANT_score IMUSANT_segmented_part_fixed_period_Tests::fScore_Sanctus = NULL;
S_IMUSANT_score IMUSANT_segmented_part_fixed_period_Tests::fScore_YankeeDoodle = NULL;
S_IMUSANT_score IMUSANT_segmented_part_fixed_period_Tests::fScore_Josquin_MAF_Christe = NULL;

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

TEST_F(IMUSANT_segmented_part_fixed_period_Tests, FixedPeriodSegmentation_Initialise_NotAPeriodicCannon)
{
    S_IMUSANT_segmented_part_fixed_period s_segmented_part = new_IMUSANT_segmented_part_fixed_period();
    int ret_val = s_segmented_part->initialise(fScore_Josquin_MAF_Christe);
    
    ASSERT_EQ(IMUSANT_segmented_part_fixed_period::ERR_MORE_THAN_ONE_PART_AT_BEGINNING, ret_val);
}

TEST_F(IMUSANT_segmented_part_fixed_period_Tests, FixedPeriodSegmentation_Initialise_Kyrie)
{
    S_IMUSANT_segmented_part_fixed_period s_segmented_part = new_IMUSANT_segmented_part_fixed_period();
    int error_code = s_segmented_part->initialise(fScore_Kyrie);
    
    ASSERT_EQ(IMUSANT_segmented_part_fixed_period::SUCCESS, error_code);
    ASSERT_EQ(10752, s_segmented_part->getPeriodDuration());
    
    vector<S_IMUSANT_segment> segments = s_segmented_part->getSegments();
    ASSERT_EQ(9, segments.size()) << "Unexpected number of segments...";
    
    for (int seg_index = 0 ; seg_index < segments.size(); seg_index++)
    {
        ASSERT_EQ(*fScore_Kyrie, *(segments[seg_index]->getScore()));
    }
    
    ASSERT_EQ(14, segments[0]->notes().size());
    ASSERT_EQ(14, segments[1]->notes().size());
    ASSERT_EQ(16, segments[2]->notes().size());
    ASSERT_EQ(18, segments[3]->notes().size());
    ASSERT_EQ(14, segments[4]->notes().size());
    ASSERT_EQ(14, segments[5]->notes().size());
    ASSERT_EQ(32, segments[6]->notes().size());
    ASSERT_EQ(25, segments[7]->notes().size());
    ASSERT_EQ(01, segments[8]->notes().size());
    
    //
    // Spot test some of the notes within the segments...
    //
    
    ASSERT_EQ("Ca 2", segments[0]->getPart()->getPartName());
    ASSERT_EQ(1, segments[0]->notes()[0]->getNoteIndex());
    ASSERT_EQ(IMUSANT_pitch::G, segments[0]->notes()[0]->pitch()->name());
    
    ASSERT_EQ("Ca 2", segments[7]->getPart()->getPartName());
    ASSERT_EQ(57, segments[7]->notes()[0]->getMeasureNum());
    ASSERT_EQ(1, segments[7]->notes()[0]->getNoteIndex());
    ASSERT_EQ(IMUSANT_pitch::D, segments[7]->notes()[0]->pitch()->name());
    
    ASSERT_EQ(63, segments[7]->notes()[24]->getMeasureNum());
    ASSERT_EQ(3, segments[7]->notes()[24]->getNoteIndex());
    ASSERT_EQ(IMUSANT_pitch::D, segments[7]->notes()[24]->pitch()->name());
    
    ASSERT_EQ("Ca 2", segments[8]->getPart()->getPartName());
    ASSERT_EQ(63, segments[8]->notes()[0]->getMeasureNum());
    ASSERT_EQ(4, segments[8]->notes()[0]->getNoteIndex());
    ASSERT_EQ(IMUSANT_pitch::undefined, segments[8]->notes()[0]->pitch()->name());
}

TEST_F(IMUSANT_segmented_part_fixed_period_Tests, FixedPeriodSegmentation_Initialise_Sanctus)
{
    S_IMUSANT_segmented_part_fixed_period s_segmented_part = new_IMUSANT_segmented_part_fixed_period();
    int ret_val = s_segmented_part->initialise(fScore_Sanctus);
    
    ASSERT_EQ(IMUSANT_segmented_part_fixed_period::SUCCESS, ret_val);
    ASSERT_EQ(7680, s_segmented_part->getPeriodDuration());
    
    vector<S_IMUSANT_segment> segments = s_segmented_part->getSegments();
    ASSERT_EQ(23, segments.size()) << "Unexpected number of segments...";
    
    for (int seg_index = 0 ; seg_index < segments.size(); seg_index++)
    {
        ASSERT_EQ(*fScore_Sanctus, *(segments[seg_index]->getScore()));
    }
}

