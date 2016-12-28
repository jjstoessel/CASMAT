//
//  IMUSANT_partlist_ordered_by_part_entry_Tests.cpp
//  catsmat
//
//  Created by Derrick Hill on 28/12/16.
//
//

#include <stdio.h>

#include "gtest/gtest.h"

#include "IMUSANT_test_utilities.h"

#include "libIMUSANT.h"
#include <boost/filesystem.hpp>

using namespace IMUSANT;

using namespace boost;

//#define VERBOSE = 1;



class IMUSANT_partlist_ordered_by_part_entry_Tests :
public ::testing::Test
{
protected:
    
    IMUSANT_partlist_ordered_by_part_entry_Tests()
    {
        // You can do set-up work for each test here.
        // This is a bit inefficient as each file gets parsed for each test case.
    }
    
    virtual ~IMUSANT_partlist_ordered_by_part_entry_Tests()
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

IMUSANT_test_utilities * IMUSANT_partlist_ordered_by_part_entry_Tests::_test_utils = NULL;

S_IMUSANT_score IMUSANT_partlist_ordered_by_part_entry_Tests::fScore_Kyrie = NULL;
S_IMUSANT_score IMUSANT_partlist_ordered_by_part_entry_Tests::fScore_Sanctus = NULL;
S_IMUSANT_score IMUSANT_partlist_ordered_by_part_entry_Tests::fScore_YankeeDoodle = NULL;
S_IMUSANT_score IMUSANT_partlist_ordered_by_part_entry_Tests::fScore_Josquin_MAF_Christe = NULL;

// ************* TEST CASES START HERE *********** //


TEST_F(IMUSANT_partlist_ordered_by_part_entry_Tests, IMUSANT_PartEntry_Vector_Sort)
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
    
    IMUSANT_PartEntry pe1(dummy_part, 1, 1, duration1);
    IMUSANT_PartEntry pe2(dummy_part, 2, 2, duration2);
    IMUSANT_PartEntry pe3(dummy_part, 3, 3, duration3);
    IMUSANT_PartEntry pe4(dummy_part, 4, 4, duration4);
    IMUSANT_PartEntry pe5(dummy_part, 5, 5, duration5);
    
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


TEST_F(IMUSANT_partlist_ordered_by_part_entry_Tests, PartlistOrderedByPartEntry_Constructor)
{
    IMUSANT_partlist_ordered_by_part_entry * ordered_partlist = new IMUSANT_partlist_ordered_by_part_entry();
    S_IMUSANT_partlist_ordered_by_part_entry s_ordered_partlist = new_IMUSANT_partlist_ordered_by_part_entry();
    
    
    ASSERT_FALSE(ordered_partlist == NULL);
    ASSERT_FALSE(s_ordered_partlist == NULL);
    
    delete ordered_partlist;
}


TEST_F(IMUSANT_partlist_ordered_by_part_entry_Tests, PartlistOrderedByPartEntry_GetPartsInOrder_YankeeDoodle)
{
    S_IMUSANT_partlist_ordered_by_part_entry s_ordered_partlist = new_IMUSANT_partlist_ordered_by_part_entry();
    
    vector<IMUSANT_PartEntry> ordered_partlist = s_ordered_partlist->getPartsInOrder(fScore_YankeeDoodle);
    
    ASSERT_FALSE(s_ordered_partlist == NULL);
    ASSERT_EQ(1, ordered_partlist.size());
    
    IMUSANT_duration default_duration;
    
    ASSERT_EQ(1, ordered_partlist[0].EntryMeasureNum);
    ASSERT_EQ(1, ordered_partlist[0].EntryNoteIndex);
    ASSERT_EQ(default_duration, *(ordered_partlist[0].EntryDurationOffset));
}

TEST_F(IMUSANT_partlist_ordered_by_part_entry_Tests, PartlistOrderedByPartEntry_GetPartsInOrder_Kyrie)
{
    S_IMUSANT_partlist_ordered_by_part_entry s_ordered_partlist = new_IMUSANT_partlist_ordered_by_part_entry();
    
    vector<IMUSANT_PartEntry> ordered_partlist = s_ordered_partlist->getPartsInOrder(fScore_Kyrie);
    
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
}

TEST_F(IMUSANT_partlist_ordered_by_part_entry_Tests, PartlistOrderedByPartEntry_GetPartsInOrder_Sanctus)
{
    S_IMUSANT_partlist_ordered_by_part_entry s_ordered_partlist = new_IMUSANT_partlist_ordered_by_part_entry();
    
    vector<IMUSANT_PartEntry> ordered_partlist = s_ordered_partlist->getPartsInOrder(fScore_Sanctus);
    
    ASSERT_FALSE(s_ordered_partlist == NULL);
    ASSERT_EQ(3, ordered_partlist.size());
    
}

TEST_F(IMUSANT_partlist_ordered_by_part_entry_Tests, PartlistOrderedByPartEntry_GetPartsInOrder_Josquin_MAF_Christe)
{
    S_IMUSANT_partlist_ordered_by_part_entry s_ordered_partlist = new_IMUSANT_partlist_ordered_by_part_entry();
    
    vector<IMUSANT_PartEntry> ordered_partlist = s_ordered_partlist->getPartsInOrder(fScore_Josquin_MAF_Christe);
    
    ASSERT_FALSE(s_ordered_partlist == NULL);
    ASSERT_EQ(4, ordered_partlist.size());
    
}
