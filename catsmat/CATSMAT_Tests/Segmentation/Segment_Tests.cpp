
#include <stdio.h>

#include "gtest/gtest.h"
#include <boost/filesystem.hpp>

#include "CATSMAT_test_utility.h"

#include "libIMUSANT.h"

#include "Segment.h"

using namespace IMUSANT;
using namespace CATSMAT;
using namespace boost;

//#define VERBOSE = 1;


// The fixture for testing class IMUSANT_pitch.
class Segment_Tests : public ::testing::Test
{
    
protected:
    
    Segment_Tests()
    {
        // You can do set-up work for each test here.
        // This is a bit inefficient as each file gets parsed for each test case.
    }
    
    virtual ~Segment_Tests()
    {
        // You can do clean-up work that doesn't throw exceptions here.
    }
    
    virtual void SetUp() {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }
    
    static void SetUpTestCase() {
        _test_utils = new CATSMAT_test_utility("IMUSANT_testdata");
    }
    
    static CATSMAT_test_utility * _test_utils;
};

CATSMAT_test_utility * Segment_Tests::_test_utils = NULL;


// ************* TEST CASES START HERE *********** //


TEST_F(Segment_Tests, Constructor)
{
    S_IMUSANT_score score = new_IMUSANT_score();
    S_IMUSANT_part part = new_IMUSANT_part();
    string algorithm_id = "test algorithm";
    
    S_SegmentContext context = new_SegmentContext(score, part, algorithm_id);
    S_Segment p_segment = new_Segment(context);

    ASSERT_FALSE(p_segment == NULL);
    
    ASSERT_EQ(algorithm_id, p_segment->getAlgorithm());    
    
    Segment segment(context);
    ASSERT_EQ(algorithm_id, segment.getAlgorithm());
}

TEST_F(Segment_Tests, CollectionMethods)
{
    S_IMUSANT_score score = new_IMUSANT_score();
    S_IMUSANT_part part = new_IMUSANT_part();
    string algorithm_id = "test algorithm";
    
    S_SegmentContext context = new_SegmentContext(score, part, algorithm_id);
    
    S_Segment p_segment = new_Segment(context);
    
    S_IMUSANT_note n1 = new_IMUSANT_note();
    S_IMUSANT_note n2 = new_IMUSANT_note();
    S_IMUSANT_note n3 = new_IMUSANT_note();
    S_IMUSANT_note n4 = new_IMUSANT_note();
    S_IMUSANT_note n5 = new_IMUSANT_note();
    
    p_segment->addNote(n1);
    p_segment->addNote(n2);
    p_segment->addNote(n3);
    p_segment->addNote(n4);
    p_segment->addNote(n5);
    
    ASSERT_EQ(5, p_segment->size());
    
    p_segment->clear();
    
    ASSERT_EQ(0, p_segment->size());
}



