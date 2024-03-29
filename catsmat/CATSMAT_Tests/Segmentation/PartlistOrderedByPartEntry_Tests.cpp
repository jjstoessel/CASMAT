//
//  PartlistOrderedByPartEntry_Tests.cpp
//  catsmat
//
//  Created by Derrick Hill on 28/12/16.
//
//

#include <stdio.h>

#include "gtest/gtest.h"

#include "CATSMAT_test_utility.h"

#include "libIMUSANT.h"

#include "PartlistOrderedByPartEntry.h"

#include <boost/filesystem.hpp>

using namespace IMUSANT;
using namespace CATSMAT;

using namespace boost;

//#define VERBOSE = 1;



class PartlistOrderedByPartEntry_Tests :
public ::testing::Test
{
protected:

    PartlistOrderedByPartEntry_Tests()
    {
        // You can do set-up work for each test here.
        // This is a bit inefficient as each file gets parsed for each test case.
    }
    
    virtual ~PartlistOrderedByPartEntry_Tests()
    {
        // You can do clean-up work that doesn't throw exceptions here.
    }
    
    virtual void SetUp() {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }
    
    static void SetUpTestCase() {
        _test_utils = new CATSMAT_test_utility("IMUSANT_testdata");
        
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

CATSMAT_test_utility * PartlistOrderedByPartEntry_Tests::_test_utils = NULL;

S_IMUSANT_score PartlistOrderedByPartEntry_Tests::fScore_Kyrie = NULL;
S_IMUSANT_score PartlistOrderedByPartEntry_Tests::fScore_Sanctus = NULL;
S_IMUSANT_score PartlistOrderedByPartEntry_Tests::fScore_YankeeDoodle = NULL;
S_IMUSANT_score PartlistOrderedByPartEntry_Tests::fScore_Josquin_MAF_Christe = NULL;

// ************* TEST CASES START HERE *********** //


TEST_F(PartlistOrderedByPartEntry_Tests, IMUSANT_PartEntry_Vector_Sort)
{
    S_IMUSANT_part dummy_part = new_IMUSANT_part();
    
    S_IMUSANT_duration duration1 = new_IMUSANT_duration();
    duration1->set(TRational(1,4));
    
    S_IMUSANT_duration duration2 = new_IMUSANT_duration();
    duration2->set(TRational(1,2));
    
    S_IMUSANT_duration duration3 = new_IMUSANT_duration();
    duration3->set(TRational(1,1));
    
    S_IMUSANT_duration duration4 = new_IMUSANT_duration();
    duration4->set(TRational(2,1));
    
    S_IMUSANT_duration duration5 = new_IMUSANT_duration();
    duration5->set(TRational(4,1));
    
    PartEntry pe1(dummy_part, 1, 1, duration1);
    PartEntry pe2(dummy_part, 2, 2, duration2);
    PartEntry pe3(dummy_part, 3, 3, duration3);
    PartEntry pe4(dummy_part, 4, 4, duration4);
    PartEntry pe5(dummy_part, 5, 5, duration5);
    
    IMUSANT_PartEntry_Vector pev;
    pev.push_back(pe3);
    pev.push_back(pe1);
    pev.push_back(pe5);
    pev.push_back(pe4);
    pev.push_back(pe2);
    
    std::sort(pev.begin(), pev.end());
    
    ASSERT_EQ(1, pev[0].EntryMeasureNum);
    ASSERT_EQ(2, pev[1].EntryMeasureNum);
    ASSERT_EQ(3, pev[2].EntryMeasureNum);
    ASSERT_EQ(4, pev[3].EntryMeasureNum);
    ASSERT_EQ(5, pev[4].EntryMeasureNum);
    
}


TEST_F(PartlistOrderedByPartEntry_Tests, PartlistOrderedByPartEntry_Constructor)
{
    PartlistOrderedByPartEntry * ordered_partlist = new PartlistOrderedByPartEntry();
    S_PartlistOrderedByPartEntry s_ordered_partlist = new_PartlistOrderedByPartEntry();
    
    
    ASSERT_FALSE(ordered_partlist == NULL);
    ASSERT_FALSE(s_ordered_partlist == NULL);
    
    delete ordered_partlist;
}


TEST_F(PartlistOrderedByPartEntry_Tests, PartlistOrderedByPartEntry_GetPartsInOrder_YankeeDoodle)
{
    S_PartlistOrderedByPartEntry s_ordered_partlist = new_PartlistOrderedByPartEntry();
    
    vector<PartEntry> ordered_partlist = s_ordered_partlist->getPartsInOrder(fScore_YankeeDoodle);
    
    ASSERT_FALSE(s_ordered_partlist == NULL);
    ASSERT_EQ(1, ordered_partlist.size());
    
    IMUSANT_duration default_duration;
    
    ASSERT_EQ(1, ordered_partlist[0].EntryMeasureNum);
    ASSERT_EQ(1, ordered_partlist[0].EntryNoteIndex);
    ASSERT_EQ(default_duration, *(ordered_partlist[0].EntryDurationOffset));
}

TEST_F(PartlistOrderedByPartEntry_Tests, PartlistOrderedByPartEntry_GetPartsInOrder_Kyrie)
{
    S_PartlistOrderedByPartEntry s_ordered_partlist = new_PartlistOrderedByPartEntry();
    
    vector<PartEntry> ordered_partlist = s_ordered_partlist->getPartsInOrder(fScore_Kyrie);
    
    ASSERT_FALSE(s_ordered_partlist == NULL);
    
    ASSERT_EQ(3, ordered_partlist.size());
    ASSERT_EQ("P1", ordered_partlist[0].Part->getID());
    ASSERT_EQ("P2", ordered_partlist[1].Part->getID());
    ASSERT_EQ("P3", ordered_partlist[2].Part->getID());
    
    ASSERT_EQ(1, ordered_partlist[0].EntryNoteIndex);
    ASSERT_EQ(1, ordered_partlist[1].EntryNoteIndex);
    ASSERT_EQ(1, ordered_partlist[2].EntryNoteIndex);
    
    ASSERT_EQ(1, ordered_partlist[0].EntryMeasureNum);
    ASSERT_EQ(8, ordered_partlist[1].EntryMeasureNum);
    ASSERT_EQ(15, ordered_partlist[2].EntryMeasureNum);
    
    ASSERT_EQ(0, ordered_partlist[0].EntryVectorIndexPosition);
    ASSERT_EQ(7, ordered_partlist[1].EntryVectorIndexPosition);
    ASSERT_EQ(14, ordered_partlist[2].EntryVectorIndexPosition);
}

TEST_F(PartlistOrderedByPartEntry_Tests, PartlistOrderedByPartEntry_GetPartsInOrder_Sanctus)
{
    S_PartlistOrderedByPartEntry s_ordered_partlist = new_PartlistOrderedByPartEntry();
    
    vector<PartEntry> ordered_partlist = s_ordered_partlist->getPartsInOrder(fScore_Sanctus);
    
    ASSERT_FALSE(s_ordered_partlist == NULL);
    ASSERT_EQ(3, ordered_partlist.size());
    
    ASSERT_EQ("P1", ordered_partlist[0].Part->getID());
    ASSERT_EQ("P2", ordered_partlist[1].Part->getID());
    ASSERT_EQ("P3", ordered_partlist[2].Part->getID());
    
    ASSERT_EQ(1, ordered_partlist[0].EntryNoteIndex);
    ASSERT_EQ(1, ordered_partlist[1].EntryNoteIndex);
    ASSERT_EQ(1, ordered_partlist[2].EntryNoteIndex);
    
    ASSERT_EQ(1, ordered_partlist[0].EntryMeasureNum);
    ASSERT_EQ(6, ordered_partlist[1].EntryMeasureNum);
    ASSERT_EQ(11, ordered_partlist[2].EntryMeasureNum);
    
    ASSERT_EQ(0, ordered_partlist[0].EntryVectorIndexPosition);
    ASSERT_EQ(5, ordered_partlist[1].EntryVectorIndexPosition);
    ASSERT_EQ(10, ordered_partlist[2].EntryVectorIndexPosition);
}

TEST_F(PartlistOrderedByPartEntry_Tests, PartlistOrderedByPartEntry_GetPartsInOrder_Josquin_MAF_Christe)
{
    S_PartlistOrderedByPartEntry s_ordered_partlist = new_PartlistOrderedByPartEntry();
    
    vector<PartEntry> ordered_partlist = s_ordered_partlist->getPartsInOrder(fScore_Josquin_MAF_Christe);
    
    ASSERT_FALSE(s_ordered_partlist == NULL);
    ASSERT_EQ(4, ordered_partlist.size());
    
    ASSERT_EQ(1, ordered_partlist[0].EntryNoteIndex);
    ASSERT_EQ(1, ordered_partlist[1].EntryNoteIndex);
    ASSERT_EQ(1, ordered_partlist[2].EntryNoteIndex);
    ASSERT_EQ(1, ordered_partlist[3].EntryNoteIndex);
    
    ASSERT_EQ(1, ordered_partlist[0].EntryMeasureNum);
    ASSERT_EQ(1, ordered_partlist[1].EntryMeasureNum);
    ASSERT_EQ(1, ordered_partlist[2].EntryMeasureNum);
    ASSERT_EQ(4, ordered_partlist[3].EntryMeasureNum);
    
    ASSERT_EQ(0, ordered_partlist[0].EntryVectorIndexPosition);
    ASSERT_EQ(0, ordered_partlist[1].EntryVectorIndexPosition);
    ASSERT_EQ(0, ordered_partlist[2].EntryVectorIndexPosition);
    ASSERT_EQ(3, ordered_partlist[3].EntryVectorIndexPosition);
    
}
