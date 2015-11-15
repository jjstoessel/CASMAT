//
//  IMUSANT_mxmlv3_to_imusant_visitor_Tests.cpp
//  imusant
//
//  Created by Derrick Hill on 15/11/2015.
//
//

#include <stdio.h>

#include "gtest/gtest.h"

#include "libIMUSANT.h"
#include <boost/filesystem.hpp>

using namespace IMUSANT;
using namespace boost;

// The fixture for testing class IMUSANT_pitch.
class IMUSANT_mxmlv3_to_imusant_visitor_Tests : public ::testing::Test {
    
protected:
    
    IMUSANT_mxmlv3_to_imusant_visitor_Tests()
    {
        // You can do set-up work for each test here.
        initialise_ParserTest1_score();
    }
    
    virtual ~IMUSANT_mxmlv3_to_imusant_visitor_Tests()
    {
        // You can do clean-up work that doesn't throw exceptions here.
    }
    
    filesystem::path make_path_to_test_file(string relative_path_to_test_data_file);
    
    S_IMUSANT_score fScore_ParserTest1;
    void initialise_ParserTest1_score();
    const int NUM_MEASURES_PARSER_TEST_1 = 12;
    const int KEY_AND_TIME_CHANGE_MEASURE_NUM_PARSER_TEST_1 = 7; // This is the bar where the time and key signatures change
    
};


void
IMUSANT_mxmlv3_to_imusant_visitor_Tests::
initialise_ParserTest1_score()
{
    string relative_path = "MusicXMLv3.simple_test_data/MusicXML_ParserTest1.xml";
    
    filesystem::path file_path = make_path_to_test_file(relative_path);
    
    IMUSANT_processing parser;
    fScore_ParserTest1 = parser.process_musicxml3_file(file_path);
}


filesystem::path
IMUSANT_mxmlv3_to_imusant_visitor_Tests::
make_path_to_test_file(string relative_path_to_test_data_file)
{
    filesystem::path testdata(filesystem::initial_path());
    testdata.append("IMUSANT_testdata");
    testdata.append(relative_path_to_test_data_file);
    return testdata;
}




// ************* TEST CASES START HERE *********** //


TEST_F(IMUSANT_mxmlv3_to_imusant_visitor_Tests, MXMLv3_Dichterliebe01)
{
    string relative_path = "MusicXMLv3.xmlsamples/Dichterliebe01.xml";
    
    filesystem::path file_path = make_path_to_test_file(relative_path);
    
    IMUSANT_processing parser;
    S_IMUSANT_score score = parser.process_musicxml3_file(file_path);
    
    /*
     <movement-number>1</movement-number>
     <movement-title>Im wunderschönen Monat Mai</movement-title>
     */
    ASSERT_EQ(score->getMovementNum(), "1");
    ASSERT_EQ(score->getMovementTitle(), "Im wunderschönen Monat Mai");
    
    /*
     <creator type="composer">Robert Schumann</creator>
     <creator type="lyricist">Heinrich Heine</creator>
     */
    STRPAIRVECTOR creators = score->getCreator();
    ASSERT_EQ(2, creators.size());
    ASSERT_EQ(creators[0].first, "composer");
    ASSERT_EQ(creators[0].second, "Robert Schumann");
    ASSERT_EQ(creators[1].first, "lyricist");
    ASSERT_EQ(creators[1].second, "Heinrich Heine");
    
    /*
     <score-part id="P1">
     ...
     <score-part id="P2">
     */
    IMUSANT_vector<S_IMUSANT_part> part_list = score->partlist()->parts();
    ASSERT_EQ(2, part_list.size());
    ASSERT_EQ(part_list[0]->getID(), "P1");
    ASSERT_EQ(part_list[1]->getID(), "P2");
    
    const int NUM_MEASURES = 27;
    
    IMUSANT_vector<S_IMUSANT_measure> pt1_measures = part_list[0]->measures();
    ASSERT_EQ(NUM_MEASURES, pt1_measures.size());
    IMUSANT_vector<S_IMUSANT_measure> pt2_measures = part_list[1]->measures();
    ASSERT_EQ(NUM_MEASURES, pt2_measures.size());
    
    S_IMUSANT_part p1;
    S_IMUSANT_part p2;
    
    score->getPartById("P1", p1);
    score->getPartById("P2", p2);
    
    IMUSANT_vector<S_IMUSANT_measure> p1_measures = p1->measures();
    IMUSANT_vector<S_IMUSANT_measure> p2_measures = p2->measures();
    
    ASSERT_EQ(NUM_MEASURES, p1_measures.size());
    ASSERT_EQ(NUM_MEASURES, p2_measures.size());
    
    S_IMUSANT_measure first_p1_measure = p1_measures[0];
    
    IMUSANT_key::mode p1_mode = first_p1_measure->getKey().getMode();
    long p1_fifths = first_p1_measure->getKey().getFifths();
    ASSERT_EQ(3, p1_fifths);
    ASSERT_EQ(IMUSANT_key::mode::major, p1_mode);
    
    IMUSANT_time p1_time = first_p1_measure->getTime();
    ASSERT_EQ(p1_time.getNumerator()[0], 2);
    ASSERT_EQ(p1_time.getDenominator()[0], 4);
}

TEST_F(IMUSANT_mxmlv3_to_imusant_visitor_Tests, ScoreMetadata_ParserTest1)
{
    S_IMUSANT_score score = fScore_ParserTest1;
    
    /*
     <movement-number>1</movement-number>
     <movement-title>Im wunderschönen Monat Mai</movement-title>
     */
    ASSERT_EQ(score->getMovementNum(), "1");
    ASSERT_EQ(score->getMovementTitle(), "Introduction");
    
    /*
     <creator type="composer">Robert Schumann</creator>
     <creator type="lyricist">Heinrich Heine</creator>
     */
    STRPAIRVECTOR creators = score->getCreator();
    ASSERT_EQ(2, creators.size());
    ASSERT_EQ(creators[0].first, "composer");
    ASSERT_EQ(creators[0].second, "Derrick Hill");
    ASSERT_EQ(creators[1].first, "lyricist");
    ASSERT_EQ(creators[1].second, "Derrick Hill");
}

TEST_F(IMUSANT_mxmlv3_to_imusant_visitor_Tests, PartsAndMeasures_ParserTest1)
{
    S_IMUSANT_score score = fScore_ParserTest1;
    
    /*
     <score-part id="P1">
     ...
     <score-part id="P2"
     ...
     <score-part id="P3"
     ...
     <score-part id="P4">
     */
    IMUSANT_vector<S_IMUSANT_part> part_list = score->partlist()->parts();
    ASSERT_EQ(4, part_list.size());
    ASSERT_EQ(part_list[0]->getPartName(), "Soprano");
    ASSERT_EQ(part_list[1]->getPartName(), "Alto");
    ASSERT_EQ(part_list[2]->getPartName(), "Tenor");
    ASSERT_EQ(part_list[3]->getPartName(), "Bass");
    
    IMUSANT_vector<S_IMUSANT_measure> pt1_measures = part_list[0]->measures();
    IMUSANT_vector<S_IMUSANT_measure> pt2_measures = part_list[1]->measures();
    IMUSANT_vector<S_IMUSANT_measure> pt3_measures = part_list[2]->measures();
    IMUSANT_vector<S_IMUSANT_measure> pt4_measures = part_list[3]->measures();
    
    
    ASSERT_EQ(NUM_MEASURES_PARSER_TEST_1, pt1_measures.size());
    ASSERT_EQ(NUM_MEASURES_PARSER_TEST_1, pt2_measures.size());
    ASSERT_EQ(NUM_MEASURES_PARSER_TEST_1, pt3_measures.size());
    ASSERT_EQ(NUM_MEASURES_PARSER_TEST_1, pt4_measures.size());
}


TEST_F(IMUSANT_mxmlv3_to_imusant_visitor_Tests, MeasureProperties_ParserTest1)
{
    S_IMUSANT_score score = fScore_ParserTest1;

    S_IMUSANT_part p1_sop;
    S_IMUSANT_part p4_bass;
    
    score->getPartById("P1", p1_sop);
    score->getPartById("P4", p4_bass);
    
    IMUSANT_vector<S_IMUSANT_measure> p1_measures = p1_sop->measures();
    IMUSANT_vector<S_IMUSANT_measure> p4_measures = p4_bass->measures();

    S_IMUSANT_measure first_p1_measure = p1_measures[0];
    S_IMUSANT_measure second_p1_measure = p1_measures[1];
    
    IMUSANT_key::mode p1_mode = first_p1_measure->getKey().getMode();
    long p1_fifths = first_p1_measure->getKey().getFifths();
    ASSERT_EQ(2, p1_fifths);
    ASSERT_EQ(IMUSANT_key::mode::generic, p1_mode);
    
    IMUSANT_time p1_time = first_p1_measure->getTime();
    ASSERT_EQ(p1_time.getNumerator()[0], 4);
    ASSERT_EQ(p1_time.getDenominator()[0], 4);
    
    S_IMUSANT_measure change_p1_measure = p1_measures[KEY_AND_TIME_CHANGE_MEASURE_NUM_PARSER_TEST_1];
    S_IMUSANT_measure change_p4_measure = p4_measures[KEY_AND_TIME_CHANGE_MEASURE_NUM_PARSER_TEST_1];
    
    // Check the key change.
    p1_mode = change_p1_measure->getKey().getMode();
    p1_fifths = change_p1_measure->getKey().getFifths();
    ASSERT_EQ(3, p1_fifths);
    ASSERT_EQ(IMUSANT_key::mode::generic, p1_mode);
    
    // Check the time signature change
    p1_time = change_p1_measure->getTime();
    ASSERT_EQ(p1_time.getNumerator()[0], 6);
    ASSERT_EQ(p1_time.getDenominator()[0], 8);
    
    // Check we have the right number of notes...
    int p1_m1_note_count = first_p1_measure->getNoteCount();
    int p1_m2_note_count = second_p1_measure->getNoteCount();
    int p4_m7_note_count = change_p4_measure->getNoteCount();
    
    ASSERT_EQ(1, p1_m1_note_count);
    ASSERT_EQ(3, p1_m2_note_count);
    ASSERT_EQ(5, p4_m7_note_count);
}

TEST_F(IMUSANT_mxmlv3_to_imusant_visitor_Tests, MeasurePrintTest1_ParserTest1)
{
    S_IMUSANT_score score = fScore_ParserTest1;

    S_IMUSANT_part p1_sop;
    score->getPartById("P1", p1_sop);
    IMUSANT_vector<S_IMUSANT_measure> p1_measures = p1_sop->measures();
    S_IMUSANT_measure second_p1_measure = p1_measures[1];
    
    const string second_p1_measure_expected =
    "<MEAS>=1\n<CLEF> 0@0<\\CLEF>\n<TIME>/<\\TIME>\n<KEY>-1, mode: 0<\\KEY>\n<NOTE index=1 measure_num=1 >\n <PITCH>C1@4<\\PITCH>\n <DURATION><RHYTHM_TYPE>1/4<//RHYTHM_TYPE><DOTS>0<//DOTS><TIME_MOD>0/0<TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>measure[0] index[1]<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE index=2 measure_num=1 >\n <PITCH>C0@5<\\PITCH>\n <DURATION><RHYTHM_TYPE>1/4<//RHYTHM_TYPE><DOTS>0<//DOTS><TIME_MOD>0/0<TIME_MOD><\\DURATION>\n <ACCIDENTAL>natural<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE index=3 measure_num=1 >\n <PITCH>G0@4<\\PITCH>\n <DURATION><RHYTHM_TYPE>1/2<//RHYTHM_TYPE><DOTS>0<//DOTS><TIME_MOD>0/0<TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<\\MEAS>\n";
    
    stringstream second_p1_measure_printed;
    
    second_p1_measure->print(second_p1_measure_printed);
    
    // cout << second_p1_measure_printed.str();
    ASSERT_EQ(second_p1_measure_expected, second_p1_measure_printed.str());
}

TEST_F(IMUSANT_mxmlv3_to_imusant_visitor_Tests, MeasurePrintTest2_ParserTest1)
{
    S_IMUSANT_score score = fScore_ParserTest1;
    
    S_IMUSANT_part p1_sop;
    score->getPartById("P1", p1_sop);
    IMUSANT_vector<S_IMUSANT_measure> p1_measures = p1_sop->measures();
    S_IMUSANT_measure change_p1_measure = p1_measures[KEY_AND_TIME_CHANGE_MEASURE_NUM_PARSER_TEST_1];
    
    const string change_p1_measure_expected = "<MEAS>=7\n<CLEF> 0@0<\\CLEF>\n<TIME>6/8<\\TIME>\n<KEY>3, mode: 0<\\KEY>\n<NOTE index=1 measure_num=7 >\n <PITCH>C1@5<\\PITCH>\n <DURATION><RHYTHM_TYPE>1/4<//RHYTHM_TYPE><DOTS>1<//DOTS><TIME_MOD>0/0<TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE index=2 measure_num=7 >\n <PITCH>D0@5<\\PITCH>\n <DURATION><RHYTHM_TYPE>1/8<//RHYTHM_TYPE><DOTS>0<//DOTS><TIME_MOD>0/0<TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE index=3 measure_num=7 >\n <PITCH>C1@5<\\PITCH>\n <DURATION><RHYTHM_TYPE>1/4<//RHYTHM_TYPE><DOTS>1<//DOTS><TIME_MOD>0/0<TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<\\MEAS>\n";
    
    stringstream change_p1_measure_printed;
    
    change_p1_measure->print(change_p1_measure_printed);
    // cout << change_p1_measure_printed.str();
    ASSERT_EQ(change_p1_measure_expected, change_p1_measure_printed.str());
}

TEST_F(IMUSANT_mxmlv3_to_imusant_visitor_Tests, MeasurePrintTest3_ParserTest1)
{
    S_IMUSANT_score score = fScore_ParserTest1;
    
    S_IMUSANT_part p1_sop;
    score->getPartById("P1", p1_sop);
    IMUSANT_vector<S_IMUSANT_measure> p1_measures = p1_sop->measures();
    S_IMUSANT_measure p1_m4 = p1_measures[4];
    
    const string p1_m4_expected = "<MEAS>=4\n<CLEF> 0@0<\\CLEF>\n<TIME>/<\\TIME>\n<KEY>-1, mode: 0<\\KEY>\n<NOTE index=1 measure_num=4 >\n <PITCH>F1@4<\\PITCH>\n <DURATION><RHYTHM_TYPE>1/8<//RHYTHM_TYPE><DOTS>0<//DOTS><TIME_MOD>3/2<TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE index=2 measure_num=4 >\n <PITCH>F-1@4<\\PITCH>\n <DURATION><RHYTHM_TYPE>1/8<//RHYTHM_TYPE><DOTS>0<//DOTS><TIME_MOD>3/2<TIME_MOD><\\DURATION>\n <ACCIDENTAL>flat<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE index=3 measure_num=4 >\n <PITCH>F1@4<\\PITCH>\n <DURATION><RHYTHM_TYPE>1/8<//RHYTHM_TYPE><DOTS>0<//DOTS><TIME_MOD>3/2<TIME_MOD><\\DURATION>\n <ACCIDENTAL>sharp<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE index=4 measure_num=4 >\n <PITCH>F-2@4<\\PITCH>\n <DURATION><RHYTHM_TYPE>1/8<//RHYTHM_TYPE><DOTS>0<//DOTS><TIME_MOD>3/2<TIME_MOD><\\DURATION>\n <ACCIDENTAL>flat-flat<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE index=5 measure_num=4 >\n <PITCH>E2@4<\\PITCH>\n <DURATION><RHYTHM_TYPE>1/8<//RHYTHM_TYPE><DOTS>1<//DOTS><TIME_MOD>3/2<TIME_MOD><\\DURATION>\n <ACCIDENTAL>double-sharp<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE index=6 measure_num=4 >\n <PITCH>F1@4<\\PITCH>\n <DURATION><RHYTHM_TYPE>1/16<//RHYTHM_TYPE><DOTS>0<//DOTS><TIME_MOD>3/2<TIME_MOD><\\DURATION>\n <ACCIDENTAL>sharp<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE index=7 measure_num=4 >\n <PITCH>F1@4<\\PITCH>\n <DURATION><RHYTHM_TYPE>1/4<//RHYTHM_TYPE><DOTS>0<//DOTS><TIME_MOD>0/0<TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE index=8 measure_num=4 >\n <PITCH>F1@4<\\PITCH>\n <DURATION><RHYTHM_TYPE>1/4<//RHYTHM_TYPE><DOTS>0<//DOTS><TIME_MOD>0/0<TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<\\MEAS>\n";
    
    stringstream p1_m4_printed;
    
    p1_m4->print(p1_m4_printed);
    // cout << p1_m4_printed.str();
    ASSERT_EQ(p1_m4_expected, p1_m4_printed.str());
}



