//
//  IMUSANT_segment_Tests.cpp
//  catsmat
//
//  Created by Derrick Hill on 8/11/2016.
//
//

#include <stdio.h>

//#include "IMUSANT_segment.h"

#include "gtest/gtest.h"

#include "IMUSANT_test_utilities.h"

#include "libIMUSANT.h"
#include <boost/filesystem.hpp>

using namespace IMUSANT;
using namespace boost;

//#define VERBOSE = 1;


// The fixture for testing class IMUSANT_pitch.
class IMUSANT_segment_Tests : public ::testing::Test
{
    
protected:
    
    IMUSANT_segment_Tests()
    {
        // You can do set-up work for each test here.
        // This is a bit inefficient as each file gets parsed for each test case.
    }
    
    virtual ~IMUSANT_segment_Tests()
    {
        // You can do clean-up work that doesn't throw exceptions here.
    }
    
    virtual void SetUp() {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }
    
    static void SetUpTestCase() {
        _test_utils = new IMUSANT_test_utilities("IMUSANT_testdata");
        
//        fScore_LBDM_Test1 = _test_utils->initialiseScoreFromFile("MusicXMLv3/LBDM_Segmented_Part_Test_1.xml");
//        fScore_LBDM_Test3 = _test_utils->initialiseScoreFromFile("MusicXMLv3/LBDM_Segmented_Part_Test_3.xml");
//        fScore_Kyrie = _test_utils->initialiseScoreFromFile("MusicXMLv3/Kyrie.xml");
//        fScore_Sanctus = _test_utils->initialiseScoreFromFile("MusicXMLv3/Sanctus.xml");
//        fScore_YankeeDoodle = _test_utils->initialiseScoreFromFile("MusicXMLv3/Yankee_Doodle.xml");
    }
    
//    bool checkEqualWithinTolleranceField(double expected, double actual, int index_pos)
//    {
//        if (_test_utils->equalWithinTollerance(expected, actual))
//            return true;
//        else
//        {
//            cout << "Failed with jdex = " << index_pos
//            << ". Expected " << expected
//            << ". Received " << actual
//            << endl;
//            
//            return false;
//        }
//    };
    
    
    static IMUSANT_test_utilities * _test_utils;
//    static S_IMUSANT_score fScore_LBDM_Test1;
//    static S_IMUSANT_score fScore_LBDM_Test3;
//    static S_IMUSANT_score fScore_Kyrie;
//    static S_IMUSANT_score fScore_Sanctus;
//    static S_IMUSANT_score fScore_YankeeDoodle;
    
    
};

IMUSANT_test_utilities * IMUSANT_segment_Tests::_test_utils = NULL;
//S_IMUSANT_score IMUSANT_segment_Tests::fScore_LBDM_Test1 = NULL;
//S_IMUSANT_score IMUSANT_segment_Tests::fScore_LBDM_Test3 = NULL;
//S_IMUSANT_score IMUSANT_segment_Tests::fScore_Kyrie = NULL;
//S_IMUSANT_score IMUSANT_segment_Tests::fScore_Sanctus = NULL;
//S_IMUSANT_score IMUSANT_segment_Tests::fScore_YankeeDoodle = NULL;

// ************* TEST CASES START HERE *********** //


TEST_F(IMUSANT_segment_Tests, Constructor)
{
    S_IMUSANT_score score = new_IMUSANT_score();
    S_IMUSANT_part part = new_IMUSANT_part();
    string algorithm_id = "test algorithm";
    
    S_IMUSANT_segment p_segment = new_IMUSANT_segment(score, part, algorithm_id);

    ASSERT_FALSE(p_segment == NULL);
    
    ASSERT_EQ(algorithm_id, p_segment->getAlgorithm());
    
    IMUSANT_segment segment(score, part, algorithm_id);
    ASSERT_EQ(algorithm_id, segment.getAlgorithm());
}



