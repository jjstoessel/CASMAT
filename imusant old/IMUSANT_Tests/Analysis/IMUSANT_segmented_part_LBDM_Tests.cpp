//
//  IMUSANT_segmented_part_LBDM_Tests.cpp
//  imusant
//
//  Created by Derrick Hill on 15/03/2016.
//
//

#include <stdio.h>

#include "gtest/gtest.h"

#include "IMUSANT_test_utilities.h"

#include "libIMUSANT.h"
#include <boost/filesystem.hpp>

using namespace IMUSANT;
using namespace boost;

// #define VERBOSE = 0;

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
    
    static void SetUpTestCase() {
        _test_utils = new IMUSANT_test_utilities("IMUSANT_testdata");
        
//        fScore_ParserTest1 = _test_utils->initialise_score_from_file("REVISIT");

    }
    
    static IMUSANT_test_utilities * _test_utils;
    
//    static S_IMUSANT_score fScore_ParserTest1;
    
};


IMUSANT_test_utilities * IMUSANT_segmented_part_LBDM_Tests::_test_utils = NULL;


// ************* TEST CASES START HERE *********** //


TEST_F(IMUSANT_segmented_part_LBDM_Tests, REVISIT)
{
    S_IMUSANT_part part = new_IMUSANT_part();
    
    IMUSANT_segmented_part_LBDM * segmented_part = new IMUSANT_segmented_part_LBDM(part);
    
    ASSERT_FALSE(segmented_part == NULL);

    delete segmented_part;
}
