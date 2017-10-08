//
//  Segmenter_Tests.cpp
//


#include <stdio.h>

#include "gtest/gtest.h"

#include "CATSMAT_test_utility.h"

#include "libIMUSANT.h"

#include "Segmenter.h"

#include <boost/filesystem.hpp>

using namespace IMUSANT;
using namespace CATSMAT;

using namespace boost;

//#define VERBOSE = 1;



class Segmenter_Tests :
        public ::testing::Test
{
protected:

    Segmenter_Tests()
    {
        // You can do set-up work for each test here.
        // This is a bit inefficient as each file gets parsed for each test case.
    }

    virtual ~Segmenter_Tests()
    {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    virtual void SetUp() {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    static void SetUpTestCase() {
        _test_utils = new CATSMAT_test_utility("testdata");

        fScore_Kyrie = _test_utils->InitialiseScoreFromFile("Kyrie.xml");
        fScore_Sanctus = _test_utils->InitialiseScoreFromFile("Sanctus.xml");
        fScore_YankeeDoodle = _test_utils->InitialiseScoreFromFile("Yankee_Doodle.xml");
        fScore_Josquin_MAF_Christe = _test_utils->InitialiseScoreFromFile("Josquin_MAF_Christe.xml");
    }


    static CATSMAT_test_utility * _test_utils;
    static S_IMUSANT_score fScore_Kyrie;
    static S_IMUSANT_score fScore_Sanctus;
    static S_IMUSANT_score fScore_YankeeDoodle;
    static S_IMUSANT_score fScore_Josquin_MAF_Christe;


};

CATSMAT_test_utility * Segmenter_Tests::_test_utils = NULL;

S_IMUSANT_score Segmenter_Tests::fScore_Kyrie = NULL;
S_IMUSANT_score Segmenter_Tests::fScore_Sanctus = NULL;
S_IMUSANT_score Segmenter_Tests::fScore_YankeeDoodle = NULL;
S_IMUSANT_score Segmenter_Tests::fScore_Josquin_MAF_Christe = NULL;

// ************* TEST CASES START HERE *********** //


TEST_F(Segmenter_Tests, IMUSANT_PartEntry_Vector_Sort)
{

    ASSERT_EQ(true, false);

}