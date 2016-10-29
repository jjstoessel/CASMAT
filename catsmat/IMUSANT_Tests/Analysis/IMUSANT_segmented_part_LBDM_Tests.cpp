
//  IMUSANT_segmented_part_LBDM_Tests.cpp
//  imusant
//
//  Created by Derrick Hill on 15/03/2016.
//
//

#include <stdio.h>
#include <math.h>

#include "gtest/gtest.h"

#include "IMUSANT_test_utilities.h"
#include "IMUSANT_segmented_part_LBDM_Expected.h"
#include "IMUSANT_segmented_profile_vectors.h"

#include "libIMUSANT.h"
#include <boost/filesystem.hpp>

using namespace IMUSANT;

using namespace boost;

//#define VERBOSE = 1;

// The fixture for testing class IMUSANT_pitch.
class IMUSANT_segmented_part_LBDM_Tests :
            public ::testing::Test,
            public IMUSANT_segmented_part_LBDM_Expected
{
    
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
        
        fScore_LBDM_Test1 = _test_utils->initialiseScoreFromFile("MusicXMLv3/LBDM_Segmented_Part_Test_1.xml");
        fScore_LBDM_Test3 = _test_utils->initialiseScoreFromFile("MusicXMLv3/LBDM_Segmented_Part_Test_3.xml");
        fScore_Kyrie = _test_utils->initialiseScoreFromFile("MusicXMLv3/Kyrie.xml");
        fScore_Sanctus = _test_utils->initialiseScoreFromFile("MusicXMLv3/Sanctus.xml");
        fScore_YankeeDoodle = _test_utils->initialiseScoreFromFile("MusicXMLv3/Yankee_Doodle.xml");
    }
    
    IMUSANT_strength_vector getOverallStrengthVectorFromPart(S_IMUSANT_score score, string part_id)
    {
        S_IMUSANT_part part;
        score->getPartById(part_id, part);
        
        IMUSANT_segmented_part_LBDM seg_part;
        seg_part.initialise(part);
        
        IMUSANT_strength_vector lbsp = seg_part.getWeightedAverageStrengthVector();
        
#ifdef VERBOSE
        cout << seg_part;
#endif
        return lbsp;
    }
    
    bool checkEqualWithinTolleranceField(double expected, double actual, int index_pos)
    {
        if (_test_utils->equalWithinTollerance(expected, actual))
            return true;
        else
        {
            cout << "Failed with jdex = " << index_pos
            << ". Expected " << expected
            << ". Received " << actual
            << endl;
            
            return false;
        }
    };
    
    double euclidianDistance(vector<double> v1, vector<double> v2)
    {
        while (v1.size() > v2.size())
        {
            v2.push_back(0);
        }
        
        while (v2.size() > v1.size())
        {
            v1.push_back(0);
        }
        
        if (v1.size() != v2.size())
        {
            throw "Unexpected vector sizes after equalisation.";
        }
        
        double cumulative_distance = 0;
        
        for (int index = 0; index < v1.size(); index++)
        {
            double val1 = v1[index] - v2[index];
            double val2 = pow((val1), 2);
            cumulative_distance += val2;
            
#ifdef VERBOSE
            cout << "v1[" << index << "]: " << v1[index] << endl;
            cout << "v2[" << index << "]: " << v2[index] << endl;
            cout << "val1: " << val1 << endl;
            cout << "val2: " << val2 << endl << endl;
#endif
        }
        
        cumulative_distance =  sqrt(cumulative_distance);
        
        return cumulative_distance;
        
    };
    
    
    static IMUSANT_test_utilities * _test_utils;
    static S_IMUSANT_score fScore_LBDM_Test1;
    static S_IMUSANT_score fScore_LBDM_Test3;
    static S_IMUSANT_score fScore_Kyrie;
    static S_IMUSANT_score fScore_Sanctus;
    static S_IMUSANT_score fScore_YankeeDoodle;

    
};

IMUSANT_test_utilities * IMUSANT_segmented_part_LBDM_Tests::_test_utils = NULL;
S_IMUSANT_score IMUSANT_segmented_part_LBDM_Tests::fScore_LBDM_Test1 = NULL;
S_IMUSANT_score IMUSANT_segmented_part_LBDM_Tests::fScore_LBDM_Test3 = NULL;
S_IMUSANT_score IMUSANT_segmented_part_LBDM_Tests::fScore_Kyrie = NULL;
S_IMUSANT_score IMUSANT_segmented_part_LBDM_Tests::fScore_Sanctus = NULL;
S_IMUSANT_score IMUSANT_segmented_part_LBDM_Tests::fScore_YankeeDoodle = NULL;

// ************* TEST CASES START HERE *********** //


TEST_F(IMUSANT_segmented_part_LBDM_Tests, Constructor)
{
    S_IMUSANT_part part = new_IMUSANT_part();
    IMUSANT_segmented_part_LBDM * segmented_part = new IMUSANT_segmented_part_LBDM();
    ASSERT_FALSE(segmented_part == NULL);

    S_IMUSANT_segmented_part_LBDM s_segmented_part = new_IMUSANT_segmented_part_LBDM();
    ASSERT_FALSE(s_segmented_part == NULL);

    delete segmented_part;
}


TEST_F(IMUSANT_segmented_part_LBDM_Tests, calculateOverallLocalBoundaryStrengthProfile_P1)
{
    vector<double> lbsp = getOverallStrengthVectorFromPart(fScore_LBDM_Test1, "P1");

    for (int jdex = 0 ; jdex < P1_COUNT; jdex++)
    {
        ASSERT_TRUE(_test_utils->equalWithinTollerance(strength_P1_expected[jdex][WEIGHTED_AVG_STRENGTH_EXPECTED], lbsp[jdex]))
            << "Failed with jdex = " << jdex
            << ". Expected " << strength_P1_expected[jdex][WEIGHTED_AVG_STRENGTH_EXPECTED]
            << ". Received " << lbsp[jdex]
            << endl;
    }
}

TEST_F(IMUSANT_segmented_part_LBDM_Tests, calculateOverallLocalBoundaryStrengthProfile_P2)
{
    vector<double> lbsp = getOverallStrengthVectorFromPart(fScore_LBDM_Test1, "P2");

    for (int jdex = 0 ; jdex < P2_COUNT; jdex++)
    {
        ASSERT_TRUE(_test_utils->equalWithinTollerance(strength_P2_expected[jdex][WEIGHTED_AVG_STRENGTH_EXPECTED], lbsp[jdex]))
            << "Failed with jdex = " << jdex
            << ". Expected " << strength_P2_expected[jdex][WEIGHTED_AVG_STRENGTH_EXPECTED]
            << ". Received " << lbsp[jdex]
            << endl;
    }
}

TEST_F(IMUSANT_segmented_part_LBDM_Tests, calculateOverallLocalBoundaryStrengthProfile_P3)
{
    vector<double> lbsp = getOverallStrengthVectorFromPart(fScore_LBDM_Test1, "P3");
    
    for (int jdex = 0 ; jdex < P3_COUNT; jdex++)
    {
        ASSERT_TRUE(_test_utils->equalWithinTollerance(strength_P3_expected[jdex][WEIGHTED_AVG_STRENGTH_EXPECTED], lbsp[jdex]))
        << "Failed with jdex = " << jdex
        << ". Expected " << strength_P3_expected[jdex][WEIGHTED_AVG_STRENGTH_EXPECTED]
        << ". Received " << lbsp[jdex]
        << endl;
    }
}

TEST_F(IMUSANT_segmented_part_LBDM_Tests, calculateOverallLocalBoundaryStrengthProfile_YankeeDoodle)
{
    vector<double> lbsp = getOverallStrengthVectorFromPart(fScore_YankeeDoodle, "P1");
    
    for (int jdex = 0 ; jdex < YANKEEDOODLE_COUNT; jdex++)
    {
        ASSERT_TRUE(_test_utils->equalWithinTollerance(strength_YD_expected[jdex][WEIGHTED_AVG_STRENGTH_EXPECTED], lbsp[jdex]))
        << "Failed with jdex = " << jdex
        << ". Expected " << strength_YD_expected[jdex][WEIGHTED_AVG_STRENGTH_EXPECTED]
        << ". Received " << lbsp[jdex]
        << endl;
    }
}


TEST_F(IMUSANT_segmented_part_LBDM_Tests, getConsolidatedProfiles_YankeeDoodle)
{
    S_IMUSANT_part part;
    fScore_YankeeDoodle->getPartById("P1", part);
    
    IMUSANT_segmented_part_LBDM seg_part;
    seg_part.initialise(part);
    
    IMUSANT_consolidated_interval_profile_vector_LBDM consolidated_profiles = seg_part.getConsolidatedProfiles();
    
    int count_expected = YANKEEDOODLE_COUNT;
    ASSERT_EQ(count_expected, consolidated_profiles.size());
    
    for (int jdex = 0 ; jdex < YANKEEDOODLE_COUNT; jdex++)
    {
        IMUSANT_consolidated_interval_profile_LBDM next_row = consolidated_profiles[jdex];
        
        ASSERT_TRUE(checkEqualWithinTolleranceField(strength_YD_expected[jdex][WEIGHTED_AVG_STRENGTH_EXPECTED],
                                                    next_row.getWeightedAverage(),
                                                    jdex));
        
        
        ASSERT_TRUE(checkEqualWithinTolleranceField(strength_YD_expected[jdex][IOI_STRENGTH_EXPECTED],
                                                    next_row.getIOI(),
                                                    jdex));
                    
        ASSERT_TRUE(checkEqualWithinTolleranceField(strength_YD_expected[jdex][REST_STRENGTH_EXPECTED],
                                                    next_row.getRest(),
                                                    jdex));
        
        ASSERT_TRUE(checkEqualWithinTolleranceField(strength_YD_expected[jdex][PITCH_STRENGTH_EXPECTED],
                                                    next_row.getPitch(),
                                                    jdex));
        
        if (next_row.getStartNote() != NULL)
        {
            ASSERT_TRUE(checkEqualWithinTolleranceField(notes_YD_expected[jdex][START_INDEX_EXPECTED],
                                                        next_row.getStartNote()->getNoteIndex(),
                                                        jdex));
            
            ASSERT_TRUE(checkEqualWithinTolleranceField(notes_YD_expected[jdex][START_MEASURE_EXPECTED],
                                                        next_row.getStartNote()->getMeasureNum(),
                                                        jdex));
        }
        
        ASSERT_TRUE(checkEqualWithinTolleranceField(notes_YD_expected[jdex][END_INDEX_EXPECTED],
                                                    next_row.getEndNote()->getNoteIndex(),
                                                    jdex));
        
        ASSERT_TRUE(checkEqualWithinTolleranceField(notes_YD_expected[jdex][END_MEASURE_EXPECTED],
                                                    next_row.getEndNote()->getMeasureNum(),
                                                    jdex));
    }
}


TEST_F(IMUSANT_segmented_part_LBDM_Tests, LongOutputOperator)
{
    string soprano_expected =
    "PART NAME - Soprano\nSTRENGTH VECTORS\nNOTE1                       NOTE2                                  PITCH             IOI            REST    WEIGHTED AVG\n{\n{-,                         {1.1, 72, 256},                        72.00,          256.00,            0.00,           73.00},             // 0\n{{1.1, 72, 256},            {1.2, 72, 256},                         0.00,            0.00,            0.00,            0.00},             // 1\n{{1.2, 72, 256},            {1.3, 72, 256},                         0.00,            0.00,            0.00,            0.00},             // 2\n{{1.3, 72, 256},            {1.4, 72, 256},                         0.00,           85.33,            0.00,           21.33},             // 3\n{{1.4, 72, 256},            {2.1, 72, 512},                         0.00,          170.67,            0.00,           42.67},             // 4\n{{2.1, 72, 512},            {2.2, 72, 512},                         0.00,          170.67,            0.00,           42.67},             // 5\n{{2.2, 72, 512},            {3.1, 72, 1024},                        0.00,         1137.78,            0.00,          284.44},             // 6\n{{3.1, 72, 1024},           {4.1, 72, 128},                         0.00,           99.56,            0.00,           24.89},             // 7\n{{4.1, 72, 128},            {4.2, 72, 128},                         0.00,            0.00,            0.00,            0.00},             // 8\n{{4.2, 72, 128},            {4.3, 72, 128},                         0.00,            0.00,            0.00,            0.00},             // 9\n{{4.3, 72, 128},            {4.4, 72, 128},                         0.00,           76.80,            0.00,           19.20},             // 10\n{{4.4, 72, 128},            {4.5, 72, 512},                         0.00,          380.34,            0.00,           95.09},             // 11\n{{4.5, 72, 512},            {5.1, 72, 384},                         0.00,          246.86,            0.00,           61.71},             // 12\n{{5.1, 72, 384},            {5.2, 72, 128},                         0.00,          128.00,            0.00,           32.00},             // 13\n{{5.2, 72, 128},            {5.3, 72, 384},                         0.00,          384.00,            0.00,           96.00},             // 14\n{{5.3, 72, 384},            {5.4, 72, 128},                         0.00,          163.56,            0.00,           40.89},             // 15\n{{5.4, 72, 128},            {6.1, 72, 1024},                        0.00,          796.44,            0.00,          199.11},             // 16\n}\n";
    
    
    S_IMUSANT_part& soprano = fScore_LBDM_Test1->partlist()->getPart("P1");
    
    S_IMUSANT_segmented_part_LBDM seg_part = new_IMUSANT_segmented_part_LBDM();
    
    seg_part->initialise(soprano);
    
    stringstream soprano_long_actual;
    soprano_long_actual << *seg_part;
    ASSERT_EQ(soprano_expected, soprano_long_actual.str());

 }

TEST_F(IMUSANT_segmented_part_LBDM_Tests, ShortOutputOperator)
{
    string soprano_expected =
    "PART NAME - Soprano\nSTRENGTH VECTORS\n           PITCH             IOI            REST    WEIGHTED AVG\n{\n{           72.00,          256.00,            0.00,           73.00},             // 0\n{            0.00,            0.00,            0.00,            0.00},             // 1\n{            0.00,            0.00,            0.00,            0.00},             // 2\n{            0.00,           85.33,            0.00,           21.33},             // 3\n{            0.00,          170.67,            0.00,           42.67},             // 4\n{            0.00,          170.67,            0.00,           42.67},             // 5\n{            0.00,         1137.78,            0.00,          284.44},             // 6\n{            0.00,           99.56,            0.00,           24.89},             // 7\n{            0.00,            0.00,            0.00,            0.00},             // 8\n{            0.00,            0.00,            0.00,            0.00},             // 9\n{            0.00,           76.80,            0.00,           19.20},             // 10\n{            0.00,          380.34,            0.00,           95.09},             // 11\n{            0.00,          246.86,            0.00,           61.71},             // 12\n{            0.00,          128.00,            0.00,           32.00},             // 13\n{            0.00,          384.00,            0.00,           96.00},             // 14\n{            0.00,          163.56,            0.00,           40.89},             // 15\n{            0.00,          796.44,            0.00,          199.11},             // 16\n}\n";
    
    
    S_IMUSANT_part& soprano = fScore_LBDM_Test1->partlist()->getPart("P1");
    
    S_IMUSANT_segmented_part_LBDM seg_part = new_IMUSANT_segmented_part_LBDM();
    
    seg_part->initialise(soprano);
    
    stringstream soprano_short_actual;
    soprano_short_actual << (*seg_part).printForTesting();
    ASSERT_EQ(soprano_expected, soprano_short_actual.str());
    
}

TEST_F(IMUSANT_segmented_part_LBDM_Tests, GetSegmentsAsNoteVectors_From_Score_YankeeDoodle)
{
    S_IMUSANT_part& the_part = fScore_YankeeDoodle->partlist()->getPart("P1");
    
    S_IMUSANT_segmented_part_LBDM seg_part = new_IMUSANT_segmented_part_LBDM();
    seg_part->initialise(the_part);
    
    seg_part->setSegmentBoundaryCalculationSpan(4);
    IMUSANT_consolidated_interval_profile_vector_LBDM data = seg_part->getConsolidatedProfiles();
    
    vector<IMUSANT_note_vector> segments = seg_part->getSegmentsAsNoteVectors();
    
    ASSERT_EQ(6, segments.size()) << "Unexpected number of segments";
    
    ASSERT_EQ(12, segments[0].size());
    ASSERT_EQ(16, segments[1].size());
    ASSERT_EQ(7, segments[2].size());
    ASSERT_EQ(6, segments[3].size());
    ASSERT_EQ(12, segments[4].size());
    ASSERT_EQ(2, segments[5].size());
    
    ASSERT_EQ(1, segments[0][0]->getMeasureNum());
    ASSERT_EQ(1, segments[0][0]->getNoteIndex());
    
    ASSERT_EQ(2, segments[0][11]->getMeasureNum());
    ASSERT_EQ(4, segments[0][11]->getNoteIndex());
    
    ASSERT_EQ(2, segments[1][0]->getMeasureNum());
    ASSERT_EQ(5, segments[1][0]->getNoteIndex());
    
    ASSERT_EQ(4, segments[1][15]->getMeasureNum());
    ASSERT_EQ(6, segments[1][15]->getNoteIndex());
    
    ASSERT_EQ(5, segments[2][0]->getMeasureNum());
    ASSERT_EQ(1, segments[2][0]->getNoteIndex());
    
    ASSERT_EQ(5, segments[2][6]->getMeasureNum());
    ASSERT_EQ(7, segments[2][6]->getNoteIndex());
    
    ASSERT_EQ(6, segments[3][0]->getMeasureNum());
    ASSERT_EQ(1, segments[3][0]->getNoteIndex());
    
    ASSERT_EQ(6, segments[3][5]->getMeasureNum());
    ASSERT_EQ(6, segments[3][5]->getNoteIndex());
    
    ASSERT_EQ(7, segments[4][0]->getMeasureNum());
    ASSERT_EQ(1, segments[4][0]->getNoteIndex());
    
    ASSERT_EQ(8, segments[4][11]->getMeasureNum());
    ASSERT_EQ(4, segments[4][11]->getNoteIndex());
    
    ASSERT_EQ(8, segments[5][0]->getMeasureNum());
    ASSERT_EQ(5, segments[5][0]->getNoteIndex());
    
    ASSERT_EQ(8, segments[5][1]->getMeasureNum());
    ASSERT_EQ(6, segments[5][1]->getNoteIndex());
}

TEST_F(IMUSANT_segmented_part_LBDM_Tests, GetSegmentsAsNoteVectors_From_Score_Kyrie)
{
    // See Task TK-01264 - "Investigate anomaly with segment boundaries involving rests in first bars of Kyrie"
    // See Task TK-01266 - "Generate results for Sanctus and analyse."
    // Current implementation of LBDM does not really give us the results we are looking for.  Work in progress.
    
    S_IMUSANT_part& the_part = fScore_Kyrie->partlist()->getPart("P2");
    
    S_IMUSANT_segmented_part_LBDM seg_part = new_IMUSANT_segmented_part_LBDM();
    seg_part->initialise(the_part);
    
    seg_part->setSegmentBoundaryCalculationSpan(4);
    IMUSANT_consolidated_interval_profile_vector_LBDM data = seg_part->getConsolidatedProfiles();
    
    vector<IMUSANT_note_vector> segments = seg_part->getSegmentsAsNoteVectors();
    
#ifdef VERBOSE
    cout << endl << endl << "IOI" << endl ;
    cout << seg_part->ioi_interval_profile << endl;
    
    cout << endl << endl << "PITCH" << endl ;
    cout << seg_part->pitch_interval_profile << endl;
 
    cout << endl << endl << "REST" << endl ;
    cout << seg_part->rest_interval_profile << endl;
 
#endif

    ASSERT_EQ(20, segments.size()) << "Unexpected number of segments";
    
    ASSERT_EQ(6, segments[0].size());
    ASSERT_EQ(6, segments[1].size());
    ASSERT_EQ(6, segments[2].size());
    ASSERT_EQ(8, segments[3].size());
    ASSERT_EQ(9, segments[4].size());
    ASSERT_EQ(10, segments[5].size());
    ASSERT_EQ(6, segments[6].size());
    ASSERT_EQ(10, segments[7].size());
    ASSERT_EQ(8, segments[8].size());
    ASSERT_EQ(6, segments[9].size());
    ASSERT_EQ(8, segments[10].size());
    ASSERT_EQ(10, segments[11].size());
    ASSERT_EQ(7, segments[12].size());
    ASSERT_EQ(10, segments[13].size());
    ASSERT_EQ(7, segments[14].size());
    ASSERT_EQ(12, segments[15].size());
    ASSERT_EQ(6, segments[16].size());
    ASSERT_EQ(6, segments[17].size());
    ASSERT_EQ(12, segments[18].size());
    ASSERT_EQ(2, segments[19].size());
}

TEST_F(IMUSANT_segmented_part_LBDM_Tests, GetSegmentsAsNoteVectors_From_Score_Sanctus)
{
    S_IMUSANT_part& the_part = fScore_Sanctus->partlist()->getPart("P2");
    
    S_IMUSANT_segmented_part_LBDM seg_part = new_IMUSANT_segmented_part_LBDM();
    seg_part->initialise(the_part);
    
    seg_part->setSegmentBoundaryCalculationSpan(4);
    IMUSANT_consolidated_interval_profile_vector_LBDM data = seg_part->getConsolidatedProfiles();
    
    vector<IMUSANT_note_vector> segments = seg_part->getSegmentsAsNoteVectors();
    
#ifdef VERBOSE
    cout << endl << endl << "IOI" << endl ;
    cout << seg_part->ioi_interval_profile << endl;
    
    cout << endl << endl << "PITCH" << endl ;
    cout << seg_part->pitch_interval_profile << endl;
    
    cout << endl << endl << "REST" << endl ;
    cout << seg_part->rest_interval_profile << endl;
    
    cout << endl << endl << seg_part->print(true, true) << endl;
    
    cout << "SEGMENT LENGTHS" << endl;
    for (int index = 0; index < segments.size(); index++)
    {
        cout << segments[index].size() << endl;
        
    }
#endif

    ASSERT_EQ(22, segments.size()) << "Unexpected number of segments.";
    
    ASSERT_EQ(12, segments[0].size());
    ASSERT_EQ(11, segments[1].size());
    ASSERT_EQ(8, segments[2].size());
    ASSERT_EQ(5, segments[3].size());
    ASSERT_EQ(11, segments[4].size());
    ASSERT_EQ(7, segments[5].size());
    ASSERT_EQ(7, segments[6].size());
    ASSERT_EQ(7, segments[7].size());
    ASSERT_EQ(9, segments[8].size());
    ASSERT_EQ(5, segments[9].size());
    ASSERT_EQ(7, segments[10].size());
    ASSERT_EQ(10, segments[11].size());
    ASSERT_EQ(8, segments[12].size());
    ASSERT_EQ(6, segments[13].size());
    ASSERT_EQ(5, segments[14].size());
    ASSERT_EQ(9, segments[15].size());
    ASSERT_EQ(6, segments[16].size());
    ASSERT_EQ(9, segments[17].size());
    ASSERT_EQ(9, segments[18].size());
    ASSERT_EQ(6, segments[19].size());
    ASSERT_EQ(11, segments[20].size());
    ASSERT_EQ(12, segments[21].size());
    
    // Spot test some values
    
    // Beginning...
    ASSERT_EQ(1, segments[0][0]->getMeasureNum());
    ASSERT_EQ(1, segments[0][0]->getNoteIndex());
    ASSERT_EQ(IMUSANT_pitch::undefined, segments[0][0]->pitch()->name());
    
    // Middle...
    ASSERT_EQ(44, segments[6][3]->getMeasureNum());
    ASSERT_EQ(1, segments[6][3]->getNoteIndex());
    ASSERT_EQ(IMUSANT_pitch::E, segments[6][3]->pitch()->name());
    
    // End...
    ASSERT_EQ(115, segments[21][11]->getMeasureNum());
    ASSERT_EQ(1, segments[21][11]->getNoteIndex());
    ASSERT_EQ(IMUSANT_pitch::A, segments[21][11]->pitch()->name());
    
}

TEST_F(IMUSANT_segmented_part_LBDM_Tests, getSegmentsWithProfileVectors_Test)
{
    S_IMUSANT_part& the_part = fScore_LBDM_Test3->partlist()->getPart("P1");
    
    S_IMUSANT_segmented_part_LBDM seg_part = new_IMUSANT_segmented_part_LBDM();
    
    seg_part->initialise(the_part);
    seg_part->setSegmentBoundaryCalculationSpan(4);
    vector<IMUSANT_consolidated_interval_profile_vector_LBDM> segments = seg_part->getSegmentsWithProfileVectors();
    
    ASSERT_EQ(4, segments.size());
    ASSERT_EQ(7, segments[0].size());
    ASSERT_EQ(8, segments[1].size());
    ASSERT_EQ(8, segments[2].size());
    ASSERT_EQ(8, segments[3].size());
}

TEST_F(IMUSANT_segmented_part_LBDM_Tests, getSegmentsWithWeightedAverages_Test)
{
    S_IMUSANT_part& the_part = fScore_LBDM_Test3->partlist()->getPart("P1");
    
    S_IMUSANT_segmented_part_LBDM seg_part = new_IMUSANT_segmented_part_LBDM();
    
    seg_part->initialise(the_part);
    seg_part->setSegmentBoundaryCalculationSpan(4);
    vector<IMUSANT_strength_vector> segments = seg_part->getSegmentsWithWeightedAverages();
    
    ASSERT_EQ(4, segments.size());
    ASSERT_EQ(7, segments[0].size());
    ASSERT_EQ(8, segments[1].size());
    ASSERT_EQ(8, segments[2].size());
    ASSERT_EQ(8, segments[3].size());
}

TEST_F(IMUSANT_segmented_part_LBDM_Tests, euclidianDistance_Test)
{
    vector<double> v1;
    vector<double> v2;
    vector<double> v3;
    
    v1.push_back(12.456);
    v1.push_back(14.54321);
    v1.push_back(45.677899);
    v1.push_back(2);
    
    v2.push_back(12.456);
    v2.push_back(14.54321);
    v2.push_back(45.677899);
    v2.push_back(2);
    
    v3.push_back(12.456);
    v3.push_back(14.54321);
    v3.push_back(45.677899);
    v3.push_back(2);
    v3.push_back(12.456);
    v3.push_back(14.54321);
    v3.push_back(45.677899);
    v3.push_back(2);
    
    vector < vector <double> > segments;
    segments.push_back(v1);
    segments.push_back(v2);
    segments.push_back(v3);
    
    double one_two = euclidianDistance(v1, v2);
    double one_three = euclidianDistance(v1, v3);
    
#ifdef VERBOSE
    cout << endl << "Segment Weighted Averages:" << endl;
    for (int segment_index = 0; segment_index <= 1; segment_index++)
    {   cout << segment_index << ":  ";
        for (int index = 0; index < segments[segment_index].size() ; index++)
        {
            cout << segments[segment_index][index] << ", ";
        }
        cout << endl;
    }
    
    cout << endl << endl;
    
    cout
    << "Segment Distances" << endl
    << "1 - 2  : " << one_two << endl
    << "1 - 3  : " << one_three << endl  << endl << endl << endl;
#endif
    
    ASSERT_TRUE(_test_utils->equalWithinTollerance(0, one_two));
    ASSERT_TRUE(_test_utils->equalWithinTollerance(49.5694, one_three));
}

TEST_F(IMUSANT_segmented_part_LBDM_Tests, getSegmentsWithWeightedAverages_Similarity_Test)
{
    S_IMUSANT_part& the_part = fScore_LBDM_Test3->partlist()->getPart("P1");
    
    S_IMUSANT_segmented_part_LBDM seg_part = new_IMUSANT_segmented_part_LBDM();
    
    seg_part->initialise(the_part);
    seg_part->setSegmentBoundaryCalculationSpan(4);
    vector<IMUSANT_strength_vector>  segments = seg_part->getSegmentsWithWeightedAverages();
    
    ASSERT_TRUE(_test_utils->equalWithinTollerance(40.7482, segments[0][0]));
    ASSERT_TRUE(_test_utils->equalWithinTollerance(21.5194, segments[1][3]));
    ASSERT_TRUE(_test_utils->equalWithinTollerance(93.7083, segments[2][7]));
    ASSERT_TRUE(_test_utils->equalWithinTollerance(106.667, segments[3][0]));
    ASSERT_TRUE(_test_utils->equalWithinTollerance(153.663, segments[3][7]));
    
    
    double zero_one = euclidianDistance(segments[0], segments[1]);
    double zero_two  = euclidianDistance(segments[0], segments[2]);
    double zero_three  = euclidianDistance(segments[0], segments[3]);
    double one_two  = euclidianDistance(segments[1], segments[2]);
    double one_three  = euclidianDistance(segments[1], segments[3]);
    double two_three  = euclidianDistance(segments[2], segments[3]);
    
    
#ifdef VERBOSE
    cout << endl << "Segment Weighted Averages:" << endl;
    for (int segment_index = 0; segment_index <= 3; segment_index++)
    {   cout << segment_index << ":  ";
        for (int index = 0; index < segments[segment_index].size() ; index++)
        {
            cout << segments[segment_index][index] << ", ";
        }
        cout << endl;
    }
    
    cout << endl << endl;
    
    cout
    << "Segment Distances" << endl
    << "0 - 1  : " << zero_one << endl
    << "0 - 2  : " << zero_two << endl
    << "0 - 3  : " << zero_three << endl
    << "1 - 2  : " << one_two << endl
    << "1 - 3  : " << one_three << endl
    << "2 - 3  : " << two_three << endl << endl << endl;
#endif
    
    ASSERT_TRUE(_test_utils->equalWithinTollerance(138.795, zero_one));
    ASSERT_TRUE(_test_utils->equalWithinTollerance(139.39, zero_two));
    ASSERT_TRUE(_test_utils->equalWithinTollerance(179.098, zero_three));
    ASSERT_TRUE(_test_utils->equalWithinTollerance(0.839491, one_two));
    ASSERT_TRUE(_test_utils->equalWithinTollerance(63.1178, one_three));
    ASSERT_TRUE(_test_utils->equalWithinTollerance(62.3701, two_three));

}

// #define V_VERBOSE

TEST_F(IMUSANT_segmented_part_LBDM_Tests, getSegmentsFromMultiplePartsWithWeightedAverages_Similarity_Test)
{
    
    IMUSANT_LBDM_segmenter segmenter;
    vector<S_IMUSANT_score> scores;
    scores.push_back(fScore_Kyrie);
    
    IMUSANT_LBDM_segmenter::PART_SEGS_VEC parts = segmenter.findMelodicSegments_LBDM(scores);
    
    vector<IMUSANT_strength_vector> all_weighted_avg_segments;
    vector<IMUSANT_note_vector> all_note_segments;
    
    for (IMUSANT_LBDM_segmenter::PART_SEGS_VEC::iterator part_iter = parts.begin();
         part_iter != parts.end();
         part_iter++)
    {
        vector<IMUSANT_note_vector> note_segments;
        note_segments = (*part_iter)->getSegmentsAsNoteVectors();
        all_note_segments.insert(all_note_segments.end(), note_segments.begin(), note_segments.end());
        
        vector<IMUSANT_strength_vector> weighted_avg_segments;
        weighted_avg_segments = (*part_iter)->getSegmentsWithWeightedAverages();
        all_weighted_avg_segments.insert(all_weighted_avg_segments.end(), weighted_avg_segments.begin(), weighted_avg_segments.end());
    }
    
    vector<string> distances;
    
    for (unsigned long index = 0; index < all_weighted_avg_segments.size(); index++)
    {
        for (unsigned long jdex = index+1; jdex < all_weighted_avg_segments.size(); jdex++)
        {
            double distance = euclidianDistance(all_weighted_avg_segments[index], all_weighted_avg_segments[jdex]);
            

            string str_distance = "[" + to_string(index) + ", " + to_string(jdex) + ", " + to_string(distance) + "] ";
            distances.push_back(str_distance);
            
            if (distance <= 0.2)
            {
#ifdef V_VERBOSE
                cout << endl << "----------" << endl << "Distance = " << distance << endl;
                
                cout << "Segment One" << endl;
                for (IMUSANT_note_vector::iterator iter = all_note_segments[index].begin();
                     iter != all_note_segments[index].end();
                     iter++)
                {
                    cout << (*iter)->pretty_print() << " ";
                }
                
                cout << endl << endl << "Segment Two" << endl;
                
                for (IMUSANT_note_vector::iterator iter = all_note_segments[jdex].begin();
                     iter != all_note_segments[jdex].end();
                     iter++)
                {
                    cout << (*iter)->pretty_print() << " ";
                }
                
                cout << endl;
#endif
            }
        }
    }
    
#ifdef V_VERBOSE
    cout << endl << "Segment Weighted Averages:" << endl;
    
    for (vector<string>::iterator distances_iter = distances.begin();
         distances_iter != distances.end();
         distances_iter++)
    {
        cout << *distances_iter << endl;
    }
    
    cout << endl << endl;
#endif
    
}





