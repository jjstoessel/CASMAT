////
//  SegmentedScoreFixedPeriod_Tests.cpp
//  catsmat
//
//  Created by Derrick Hill on 29/10/2016.
//
//

#include <stdio.h>

#include <stdio.h>
#include <math.h>

#include "gtest/gtest.h"

#include "CATSMAT_test_utility.h"

#include "libIMUSANT.h"


#include "IMUSANT_set_of_segment.h"
#include "SegmentedScoreFixedPeriod.h"

#include <boost/filesystem.hpp>

using namespace IMUSANT;
using namespace CATSMAT;

using namespace boost;

// #define VERBOSE = 1;

// The fixture for testing class IMUSANT_pitch.
class SegmentedScoreFixedPeriod_Tests :
public ::testing::Test
{
    
protected:
    
    SegmentedScoreFixedPeriod_Tests()
    {
        // You can do set-up work for each test here.
        // This is a bit inefficient as each file gets parsed for each test case.
    }
    
    virtual ~SegmentedScoreFixedPeriod_Tests()
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
        fScore_Kyrie_TwoPartsOnly = _test_utils->InitialiseScoreFromFile("Kyrie_TwoPartsOnly.xml");
        fScore_Sanctus = _test_utils->InitialiseScoreFromFile("Sanctus.xml");
        fScore_YankeeDoodle = _test_utils->InitialiseScoreFromFile("Yankee_Doodle.xml");
        fScore_Josquin_MAF_Christe = _test_utils->InitialiseScoreFromFile("Josquin_MAF_Christe.xml");
    }
    
    
    static CATSMAT_test_utility * _test_utils;
    static S_IMUSANT_score fScore_Kyrie;
    static S_IMUSANT_score fScore_Kyrie_TwoPartsOnly;
    static S_IMUSANT_score fScore_Sanctus;
    static S_IMUSANT_score fScore_YankeeDoodle;
    static S_IMUSANT_score fScore_Josquin_MAF_Christe;
    
    string getActualSegmentsAsString(IMUSANT_set_of_segment segment_set);
};

CATSMAT_test_utility * SegmentedScoreFixedPeriod_Tests::_test_utils = NULL;

S_IMUSANT_score SegmentedScoreFixedPeriod_Tests::fScore_Kyrie = NULL;
S_IMUSANT_score SegmentedScoreFixedPeriod_Tests::fScore_Kyrie_TwoPartsOnly = NULL;
S_IMUSANT_score SegmentedScoreFixedPeriod_Tests::fScore_Sanctus = NULL;
S_IMUSANT_score SegmentedScoreFixedPeriod_Tests::fScore_YankeeDoodle = NULL;
S_IMUSANT_score SegmentedScoreFixedPeriod_Tests::fScore_Josquin_MAF_Christe = NULL;


// ************* UTILITY FUNCTIONS START HERE *********** //

string
SegmentedScoreFixedPeriod_Tests::
getActualSegmentsAsString(IMUSANT_set_of_segment segments_set)
{
    
    // The code below gurantees that the output is in a deterministic order (we use unordered_set, so I'm just making sure...).
    vector<string> segment_strings;
    
    for (IMUSANT_set_of_segment::iterator it = segments_set.begin() ;
         it != segments_set.end();
         it++)
    {
        stringstream buffer;
        buffer << *it;
        segment_strings.push_back(buffer.str());
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


TEST_F(SegmentedScoreFixedPeriod_Tests, FixedPeriodSegmentation_Constructor)
{
    IMUSANT_set_of_segment seg_results;
    SegmentedScoreFixedPeriod * segmented_score = new SegmentedScoreFixedPeriod(seg_results);
    S_SegmentedScoreFixedPeriod s_segmented_score = new_SegmentedScoreFixedPeriod(seg_results);
    
    ASSERT_FALSE(segmented_score == NULL);
    ASSERT_FALSE(s_segmented_score == NULL);
    
    delete segmented_score;
}

TEST_F(SegmentedScoreFixedPeriod_Tests, FixedPeriodSegmentation_Initialise_NotEnoughParts)
{
    IMUSANT_set_of_segment seg_results;
    S_SegmentedScoreFixedPeriod s_segmented_score = new_SegmentedScoreFixedPeriod(seg_results);
    int ret_val = s_segmented_score->initialise(fScore_YankeeDoodle);
    
    ASSERT_EQ(SegmentedScoreFixedPeriod::ERR_NOT_ENOUGH_PARTS, ret_val);
}

TEST_F(SegmentedScoreFixedPeriod_Tests, FixedPeriodSegmentation_Initialise__Josquin_MAF_Christe_NotAPeriodicCannon)
{
    // The algorithm cannot recognise this as a cannon at the moment.
    // There seems to be a periodic cannon between Superious and Tenor parts, but it's difficult.
    IMUSANT_set_of_segment seg_results;
    S_SegmentedScoreFixedPeriod s_segmented_part = new_SegmentedScoreFixedPeriod(seg_results);
    int ret_val = s_segmented_part->initialise(fScore_Josquin_MAF_Christe);
    
    ASSERT_EQ(SegmentedScoreFixedPeriod::SUCCESS, ret_val);
    IMUSANT_set_of_segment segments = s_segmented_part->getSegmentsSet();
    ASSERT_EQ(0, segments.size()) << "Unexpected number of segments...";
}

TEST_F(SegmentedScoreFixedPeriod_Tests, FixedPeriodSegmentation_Initialise_Kyrie_TwoPartsOnly)
{
    IMUSANT_set_of_segment seg_results;
    S_SegmentedScoreFixedPeriod s_segmented_part = new_SegmentedScoreFixedPeriod(seg_results);
    int error_code = s_segmented_part->initialise(fScore_Kyrie_TwoPartsOnly);
    
    ASSERT_EQ(SegmentedScoreFixedPeriod::SUCCESS, error_code);
    ASSERT_EQ(10752, s_segmented_part->getPeriodDurationForThisScore()->AsAbsoluteNumeric());
    
    IMUSANT_set_of_segment segments_set = s_segmented_part->getSegmentsSet();
    
#ifdef VERBOSE
    cout << segments_set << endl;
#endif
    
    ASSERT_EQ(16, segments_set.size()) << "Unexpected number of segments in set...";
    
    string FixedPeriodSegmentation_Initialise_Kyrie_TwoPartsOnly_Expected = "Kyrie ele\xC3\x98son:Ca 1:15:1:21:3:16:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:Ca 1:1:1:7:2:14:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:Ca 1:22:1:28:2:18:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:Ca 1:29:1:35:2:14:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:Ca 1:36:1:42:3:14:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:Ca 1:43:1:49:2:32:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:Ca 1:50:1:56:3:25:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:Ca 1:8:1:14:2:14:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:Ca 2:15:1:21:2:14:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:Ca 2:22:1:28:3:16:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:Ca 2:29:1:35:2:18:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:Ca 2:36:1:42:2:14:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:Ca 2:43:1:49:3:14:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:Ca 2:50:1:56:2:32:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:Ca 2:57:1:63:3:25:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:Ca 2:8:1:14:2:14:0:IMUSANT_segmented_part_fixed_period\n\n";
    
    string actual_output = getActualSegmentsAsString(segments_set);
   
    ASSERT_EQ(FixedPeriodSegmentation_Initialise_Kyrie_TwoPartsOnly_Expected, actual_output);
}

TEST_F(SegmentedScoreFixedPeriod_Tests, FixedPeriodSegmentation_Initialise_Kyrie)
{
    // Q: How many segments are there in Kyrie?
    //
    // A: By part:
    //   Ca1 has 8     (63 bars / 7 bar segments, but the last 7 bars are not a segment)
    //   Ca2 has 8     (= Ca1  : because Ca2 starts one segment later than Ca1, but it's last segment is included)
    //   T   has 7     (= Ca2 - 1 : because T starts 1 segment later than Ca2)
    //   -----------
    //   TOTAL  23
    
// RESULTS as at 13 Jan 2016...
//    Kyrie ele√òson	Ca 1	1	1	7	2	14	0
//    Kyrie ele√òson	Ca 1	8	1	14	2	14	0
//    Kyrie ele√òson	Ca 1	15	1	21	3	16	0
//    Kyrie ele√òson	Ca 1	22	1	28	2	18	0
//    Kyrie ele√òson	Ca 1	29	1	35	2	14	0
//    Kyrie ele√òson	Ca 1	36	1	42	3	14	0
//    Kyrie ele√òson	Ca 1	43	1	49	2	32	0
//    Kyrie ele√òson	Ca 1	50	1	56	3	25	0
    // --   MISSING THE LAST SEGMENT IN THE FIRST PART -- EXPECTED - It's not a segment.
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
    
    IMUSANT_set_of_segment seg_results;
    S_SegmentedScoreFixedPeriod s_segmented_part = new_SegmentedScoreFixedPeriod(seg_results);
    int error_code = s_segmented_part->initialise(fScore_Kyrie);
    
    ASSERT_EQ(SegmentedScoreFixedPeriod::SUCCESS, error_code);
    ASSERT_EQ(10752, s_segmented_part->getPeriodDurationForThisScore()->AsAbsoluteNumeric());
    
    IMUSANT_set_of_segment segmentset = s_segmented_part->getSegmentsSet();

#ifdef VERBOSE
    cout << segmentset << endl;
#endif
    
    ASSERT_EQ(23, segmentset.size()) << "Unexpected number of segments in set...";
    
    string FixedPeriodSegmentation_Initialise_Kyrie_Expected = "Kyrie ele\xC3\x98son:Ca 1:15:1:21:3:16:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:Ca 1:1:1:7:2:14:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:Ca 1:22:1:28:2:18:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:Ca 1:29:1:35:2:14:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:Ca 1:36:1:42:3:14:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:Ca 1:43:1:49:2:32:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:Ca 1:50:1:56:3:25:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:Ca 1:8:1:14:2:14:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:Ca 2:15:1:21:2:14:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:Ca 2:22:1:28:3:16:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:Ca 2:29:1:35:2:18:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:Ca 2:36:1:42:2:14:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:Ca 2:43:1:49:3:14:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:Ca 2:50:1:56:2:32:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:Ca 2:57:1:63:3:25:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:Ca 2:8:1:14:2:14:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:T:15:1:21:2:14:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:T:22:1:28:2:14:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:T:29:1:35:3:16:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:T:36:1:42:2:18:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:T:43:1:49:2:14:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:T:50:1:56:3:14:0:IMUSANT_segmented_part_fixed_period\nKyrie ele\xC3\x98son:T:57:1:63:2:32:0:IMUSANT_segmented_part_fixed_period\n\n";
    
    string actual_output = getActualSegmentsAsString(segmentset);
    
    ASSERT_EQ(FixedPeriodSegmentation_Initialise_Kyrie_Expected, actual_output);
}

TEST_F(SegmentedScoreFixedPeriod_Tests, FixedPeriodSegmentation_Initialise_Sanctus)
{
    
    // Q: How many segments are there in Sanctus?
    //
    // A: By part:
    //   Ca1 has 22    (115 bars / 5 bar segments, but the last 7 bars are not a segment)
    //   Ca2 has 22    (= Ca1 :  because Ca2 starts one segment later, but it's last segment is included)
    //   T   has 21    (= Ca2 - 1 : because T starts 1 segments later than Ca2)
    //   -----------
    //   TOTAL   65
    
    
    IMUSANT_set_of_segment seg_results;
    S_SegmentedScoreFixedPeriod s_segmented_part = new_SegmentedScoreFixedPeriod(seg_results);
    
    const double ERROR_THRESHOLD = 0.2;
    int ret_val = s_segmented_part->initialise(fScore_Sanctus, ERROR_THRESHOLD);
    
    ASSERT_EQ(SegmentedScoreFixedPeriod::SUCCESS, ret_val);
    ASSERT_EQ(7680, s_segmented_part->getPeriodDurationForThisScore()->AsAbsoluteNumeric() );
    
    IMUSANT_set_of_segment segmentset = s_segmented_part->getSegmentsSet();
    
#ifdef VERBOSE
    cout << segmentset << endl;
#endif
    
    ASSERT_EQ(65, segmentset.size()) << "Unexpected number of segments in set...";
    
    string FixedPeriodSegmentation_Initialise_Sanctus_Expected = "Sanctus:Ca 1:101:1:105:1:10:0:IMUSANT_segmented_part_fixed_period\nSanctus:Ca 1:106:1:110:1:12:0:IMUSANT_segmented_part_fixed_period\nSanctus:Ca 1:11:1:15:1:7:0:IMUSANT_segmented_part_fixed_period\nSanctus:Ca 1:16:1:20:1:7:0:IMUSANT_segmented_part_fixed_period\nSanctus:Ca 1:1:1:5:1:5:0:IMUSANT_segmented_part_fixed_period\nSanctus:Ca 1:21:1:25:1:6:0:IMUSANT_segmented_part_fixed_period\nSanctus:Ca 1:26:1:30:2:7:0:IMUSANT_segmented_part_fixed_period\nSanctus:Ca 1:31:1:35:1:7:0:IMUSANT_segmented_part_fixed_period\nSanctus:Ca 1:36:1:40:1:9:0:IMUSANT_segmented_part_fixed_period\nSanctus:Ca 1:41:1:45:2:8:0:IMUSANT_segmented_part_fixed_period\nSanctus:Ca 1:46:1:50:1:6:0:IMUSANT_segmented_part_fixed_period\nSanctus:Ca 1:51:1:55:1:7:0:IMUSANT_segmented_part_fixed_period\nSanctus:Ca 1:56:1:60:1:7:0:IMUSANT_segmented_part_fixed_period\nSanctus:Ca 1:61:1:65:1:10:0:IMUSANT_segmented_part_fixed_period\nSanctus:Ca 1:66:1:70:1:6:0:IMUSANT_segmented_part_fixed_period\nSanctus:Ca 1:6:1:10:2:8:0:IMUSANT_segmented_part_fixed_period\nSanctus:Ca 1:71:1:75:1:9:0:IMUSANT_segmented_part_fixed_period\nSanctus:Ca 1:76:1:80:1:11:0:IMUSANT_segmented_part_fixed_period\nSanctus:Ca 1:81:1:85:2:9:0:IMUSANT_segmented_part_fixed_period\nSanctus:Ca 1:86:1:90:1:8:0:IMUSANT_segmented_part_fixed_period\nSanctus:Ca 1:91:1:95:2:7:0:IMUSANT_segmented_part_fixed_period\nSanctus:Ca 1:96:1:100:2:9:0:IMUSANT_segmented_part_fixed_period\nSanctus:Ca 2:101:1:105:2:9:0:IMUSANT_segmented_part_fixed_period\nSanctus:Ca 2:106:1:110:1:10:0:IMUSANT_segmented_part_fixed_period\nSanctus:Ca 2:111:1:115:1:12:0:IMUSANT_segmented_part_fixed_period\nSanctus:Ca 2:11:1:15:2:8:0:IMUSANT_segmented_part_fixed_period\nSanctus:Ca 2:16:1:20:1:7:0:IMUSANT_segmented_part_fixed_period\nSanctus:Ca 2:21:1:25:1:7:0:IMUSANT_segmented_part_fixed_period\nSanctus:Ca 2:26:1:30:1:6:0:IMUSANT_segmented_part_fixed_period\nSanctus:Ca 2:31:1:35:2:7:0:IMUSANT_segmented_part_fixed_period\nSanctus:Ca 2:36:1:40:1:7:0:IMUSANT_segmented_part_fixed_period\nSanctus:Ca 2:41:1:45:1:9:0:IMUSANT_segmented_part_fixed_period\nSanctus:Ca 2:46:1:50:2:8:0:IMUSANT_segmented_part_fixed_period\nSanctus:Ca 2:51:1:55:1:6:0:IMUSANT_segmented_part_fixed_period\nSanctus:Ca 2:56:1:60:1:7:0:IMUSANT_segmented_part_fixed_period\nSanctus:Ca 2:61:1:65:1:7:0:IMUSANT_segmented_part_fixed_period\nSanctus:Ca 2:66:1:70:1:10:0:IMUSANT_segmented_part_fixed_period\nSanctus:Ca 2:6:1:10:1:5:0:IMUSANT_segmented_part_fixed_period\nSanctus:Ca 2:71:1:75:1:6:0:IMUSANT_segmented_part_fixed_period\nSanctus:Ca 2:76:1:80:1:9:0:IMUSANT_segmented_part_fixed_period\nSanctus:Ca 2:81:1:85:1:11:0:IMUSANT_segmented_part_fixed_period\nSanctus:Ca 2:86:1:90:2:9:0:IMUSANT_segmented_part_fixed_period\nSanctus:Ca 2:91:1:95:1:8:0:IMUSANT_segmented_part_fixed_period\nSanctus:Ca 2:96:1:100:2:7:0:IMUSANT_segmented_part_fixed_period\nSanctus:T:101:1:105:2:7:0:IMUSANT_segmented_part_fixed_period\nSanctus:T:106:1:110:2:9:0:IMUSANT_segmented_part_fixed_period\nSanctus:T:111:1:115:1:10:0:IMUSANT_segmented_part_fixed_period\nSanctus:T:11:1:15:1:5:0:IMUSANT_segmented_part_fixed_period\nSanctus:T:16:1:20:2:8:0:IMUSANT_segmented_part_fixed_period\nSanctus:T:21:1:25:1:7:0:IMUSANT_segmented_part_fixed_period\nSanctus:T:26:1:30:1:7:0:IMUSANT_segmented_part_fixed_period\nSanctus:T:31:1:35:1:6:0:IMUSANT_segmented_part_fixed_period\nSanctus:T:36:1:40:2:7:0:IMUSANT_segmented_part_fixed_period\nSanctus:T:41:1:45:1:7:0:IMUSANT_segmented_part_fixed_period\nSanctus:T:46:1:50:1:9:0:IMUSANT_segmented_part_fixed_period\nSanctus:T:51:1:55:2:8:0:IMUSANT_segmented_part_fixed_period\nSanctus:T:56:1:60:1:6:0:IMUSANT_segmented_part_fixed_period\nSanctus:T:61:1:65:1:7:0:IMUSANT_segmented_part_fixed_period\nSanctus:T:66:1:70:1:7:0:IMUSANT_segmented_part_fixed_period\nSanctus:T:71:1:75:1:10:0:IMUSANT_segmented_part_fixed_period\nSanctus:T:76:1:80:1:6:0:IMUSANT_segmented_part_fixed_period\nSanctus:T:81:1:85:1:9:0:IMUSANT_segmented_part_fixed_period\nSanctus:T:86:1:90:1:11:0:IMUSANT_segmented_part_fixed_period\nSanctus:T:91:1:95:2:9:0:IMUSANT_segmented_part_fixed_period\nSanctus:T:96:1:100:1:8:0:IMUSANT_segmented_part_fixed_period\n\n";
    
    string actual_output = getActualSegmentsAsString(segmentset);
    
    ASSERT_EQ(FixedPeriodSegmentation_Initialise_Sanctus_Expected, actual_output);
}

