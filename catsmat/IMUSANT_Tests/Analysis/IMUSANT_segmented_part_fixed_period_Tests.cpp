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

#define VERBOSE = 1;

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
        fScore_Kyrie_TwoPartsOnly = _test_utils->initialiseScoreFromFile("MusicXMLv3/Kyrie_TwoPartsOnly.xml");
        fScore_Sanctus = _test_utils->initialiseScoreFromFile("MusicXMLv3/Sanctus.xml");
        fScore_YankeeDoodle = _test_utils->initialiseScoreFromFile("MusicXMLv3/Yankee_Doodle.xml");
        fScore_Josquin_MAF_Christe = _test_utils->initialiseScoreFromFile("MusicXMLv3/Josquin_MAF_Christe.xml");
    }
    
    
    static IMUSANT_test_utilities * _test_utils;
    static S_IMUSANT_score fScore_Kyrie;
    static S_IMUSANT_score fScore_Kyrie_TwoPartsOnly;
    static S_IMUSANT_score fScore_Sanctus;
    static S_IMUSANT_score fScore_YankeeDoodle;
    static S_IMUSANT_score fScore_Josquin_MAF_Christe;
    
    string getActualSegmentsAsString(SetOfSegments segment_set);
};

IMUSANT_test_utilities * IMUSANT_segmented_part_fixed_period_Tests::_test_utils = NULL;

S_IMUSANT_score IMUSANT_segmented_part_fixed_period_Tests::fScore_Kyrie = NULL;
S_IMUSANT_score IMUSANT_segmented_part_fixed_period_Tests::fScore_Kyrie_TwoPartsOnly = NULL;
S_IMUSANT_score IMUSANT_segmented_part_fixed_period_Tests::fScore_Sanctus = NULL;
S_IMUSANT_score IMUSANT_segmented_part_fixed_period_Tests::fScore_YankeeDoodle = NULL;
S_IMUSANT_score IMUSANT_segmented_part_fixed_period_Tests::fScore_Josquin_MAF_Christe = NULL;


// ************* UTILITY FUNCTIONS START HERE *********** //

string
IMUSANT_segmented_part_fixed_period_Tests::
getActualSegmentsAsString(SetOfSegments segments_set)
{
    
    // The code below gurantees that the output is in a deterministic order (we use unordered_set, so I'm just making sure...).
#ifdef VERBOSE
    cout << endl << "----- SEGMENTS -----" << endl;
#endif
    
    vector<string> segment_strings;
    
    for (SetOfSegments::iterator it = segments_set.begin() ;
         it != segments_set.end();
         it++)
    {
        stringstream buffer;
        buffer << *it;
        segment_strings.push_back(buffer.str());
        
#ifdef VERBOSE
        cout << *it << endl;
#endif
    }
    
    // Sort the segments....
    std::sort(segment_strings.begin(), segment_strings.end());
    
    // and write them back into a stringstream for comparison against expected...
    stringstream actual_output;
    for(int index = 0 ; index < segment_strings.size(); index++)
    {
        actual_output << segment_strings[index] << endl;
    }
    actual_output << endl;
    
    return actual_output.str();
}


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

TEST_F(IMUSANT_segmented_part_fixed_period_Tests, FixedPeriodSegmentation_Initialise__Josquin_MAF_Christe_NotAPeriodicCannon)
{
    // The algorithm cannot recognise this as a cannon at the moment.
    // There seems to be a periodic cannon between Superious and Tenor parts, but it's difficult.
    S_IMUSANT_segmented_part_fixed_period s_segmented_part = new_IMUSANT_segmented_part_fixed_period();
    int ret_val = s_segmented_part->initialise(fScore_Josquin_MAF_Christe);
    
    ASSERT_EQ(IMUSANT_segmented_part_fixed_period::SUCCESS, ret_val);
    vector<S_IMUSANT_segment> segments = s_segmented_part->getSegments();
    ASSERT_EQ(0, segments.size()) << "Unexpected number of segments...";
}

TEST_F(IMUSANT_segmented_part_fixed_period_Tests, FixedPeriodSegmentation_Initialise_Kyrie_TwoPartsOnly)
{
    S_IMUSANT_segmented_part_fixed_period s_segmented_part = new_IMUSANT_segmented_part_fixed_period();
    int error_code = s_segmented_part->initialise(fScore_Kyrie_TwoPartsOnly);
    
    ASSERT_EQ(IMUSANT_segmented_part_fixed_period::SUCCESS, error_code);
    ASSERT_EQ(10752, s_segmented_part->getPeriodDurationForThisScore()->asAbsoluteNumeric());
    
    SetOfSegments segments_set = s_segmented_part->getSegmentsSet();
    
    ASSERT_EQ(16, segments_set.size()) << "Unexpected number of segments in set...";
    
    string FixedPeriodSegmentation_Initialise_Kyrie_TwoPartsOnly_Expected = "Kyrie ele\xC3\x98son:Ca 1:15:1:21:3:16:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:Ca 1:1:1:7:2:14:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:Ca 1:22:1:28:2:18:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:Ca 1:29:1:35:2:14:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:Ca 1:36:1:42:3:14:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:Ca 1:43:1:49:2:32:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:Ca 1:50:1:56:3:25:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:Ca 1:8:1:14:2:14:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:Ca 2:15:1:21:2:14:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:Ca 2:22:1:28:3:16:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:Ca 2:29:1:35:2:18:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:Ca 2:36:1:42:2:14:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:Ca 2:43:1:49:3:14:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:Ca 2:50:1:56:2:32:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:Ca 2:57:1:63:3:25:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:Ca 2:8:1:14:2:14:0:IMUSANT_segmented_part_fixed_period\n\n";
    
    string actual_output = getActualSegmentsAsString(segments_set);
   
    ASSERT_EQ(FixedPeriodSegmentation_Initialise_Kyrie_TwoPartsOnly_Expected, actual_output);
}

TEST_F(IMUSANT_segmented_part_fixed_period_Tests, FixedPeriodSegmentation_Initialise_Kyrie)
{
    // Q: How many segments are there in Kyrie?
    //
    // A: By part:
    //   Ca1 has 9     (63 bars / 7 bar segments)
    //   Ca2 has 8     (Ca1 - 1 because Ca2 starts one segment later)
    //   T   has 7     (Ca1 - 2 because TY starts 2 segments later)
    //   -----------
    //   TOTAL  24
    
// RESULTS as at 13 Jan 2016...
//    Kyrie ele√òson	Ca 1	1	1	7	2	14	0
//    Kyrie ele√òson	Ca 1	8	1	14	2	14	0
//    Kyrie ele√òson	Ca 1	15	1	21	3	16	0
//    Kyrie ele√òson	Ca 1	22	1	28	2	18	0
//    Kyrie ele√òson	Ca 1	29	1	35	2	14	0
//    Kyrie ele√òson	Ca 1	36	1	42	3	14	0
//    Kyrie ele√òson	Ca 1	43	1	49	2	32	0
//    Kyrie ele√òson	Ca 1	50	1	56	3	25	0
    // --   MISSING THE LAST SEGMENT IN THE FIRST PART.
//    Kyrie ele√òson	Ca 2	8	1	14	2	14	0
//    Kyrie ele√òson	Ca 2	15	1	21	2	14	0
//    Kyrie ele√òson	Ca 2	22	1	28	3	16	0
//    Kyrie ele√òson	Ca 2	29	1	35	2	18	0
//    Kyrie ele√òson	Ca 2	36	1	42	2	14	0
//    Kyrie ele√òson	Ca 2	43	1	49	3	14	0
//    Kyrie ele√òson	Ca 2	50	1	56	2	32	0
//    Kyrie ele√òson	Ca 2	57	1	63	3	25	0
//    Kyrie ele√òson	T	15	1	21	2	14	0
//    Kyrie ele√òson	T	22	1	28	2	14	0
//    Kyrie ele√òson	T	29	1	35	3	16	0
//    Kyrie ele√òson	T	36	1	42	2	18	0
//    Kyrie ele√òson	T	43	1	49	2	14	0
//    Kyrie ele√òson	T	50	1	56	3	14	0
//    Kyrie ele√òson	T	57	1	63	2	32	0
    
    S_IMUSANT_segmented_part_fixed_period s_segmented_part = new_IMUSANT_segmented_part_fixed_period();
    int error_code = s_segmented_part->initialise(fScore_Kyrie);
    
    ASSERT_EQ(IMUSANT_segmented_part_fixed_period::SUCCESS, error_code);
    ASSERT_EQ(10752, s_segmented_part->getPeriodDurationForThisScore()->asAbsoluteNumeric());
    
    vector<S_IMUSANT_segment> segments = s_segmented_part->getSegments();
  //  ASSERT_EQ(21, segments.size()) << "Unexpected number of segments in vector...";
    
    SetOfSegments segmentset = s_segmented_part->getSegmentsSet();
    
    cout << endl << "----- SEGMENTS -----" << endl;
    for (SetOfSegments::iterator it = segmentset.begin(); it != segmentset.end(); it++ )
    {
        cout << *it << endl;
    }
    
    ASSERT_EQ(24, segmentset.size()) << "Unexpected number of segments in set...";
    
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
    ASSERT_EQ(7680, s_segmented_part->getPeriodDurationForThisScore()->asAbsoluteNumeric() );
    
//    vector<S_IMUSANT_segment> segments = s_segmented_part->getSegments();
//    ASSERT_EQ(23, segments.size()) << "Unexpected number of segments...";
    
    SetOfSegments segmentset = s_segmented_part->getSegmentsSet();
    
    cout << endl << "----- SEGMENTS -----" << endl;
    for (SetOfSegments::iterator it = segmentset.begin(); it != segmentset.end(); it++ )
    {
        cout << *it << endl;
    }
    
    for (SetOfSegments::iterator it = segmentset.begin() ;
         it != segmentset.end();
         it++)
    {
        ASSERT_EQ(*fScore_Kyrie_TwoPartsOnly, *it->getScore());
    }
    
//    for (int seg_index = 0 ; seg_index < segments.size(); seg_index++)
//    {
//        ASSERT_EQ(*fScore_Sanctus, *(segments[seg_index]->getScore()));
//    }
}

