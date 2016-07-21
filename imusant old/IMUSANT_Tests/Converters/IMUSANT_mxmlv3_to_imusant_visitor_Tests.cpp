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
#include "IMUSANT_test_utilities.h"
#include <boost/filesystem.hpp>

using namespace IMUSANT;
using namespace boost;

#define VERBOSE = 0;

// The fixture for testing class IMUSANT_pitch.
class IMUSANT_mxmlv3_to_imusant_visitor_Tests : public ::testing::Test {
    
protected:

    IMUSANT_mxmlv3_to_imusant_visitor_Tests()
    {
        // You can do set-up work for each test here.
        // This is a bit inefficient as each file gets parsed for each test case.
    }
    
    virtual ~IMUSANT_mxmlv3_to_imusant_visitor_Tests()
    {
        // You can do clean-up work that doesn't throw exceptions here.
    }
    
    virtual void SetUp() {
        // Code here will be called immediately after the constructor (right
        // before each test).
       
    }
    
    static void SetUpTestCase() {
        _test_utils = new IMUSANT_test_utilities("IMUSANT_testdata");
        
        fScore_ParserTest1 = _test_utils->initialiseScoreFromFile("MusicXMLv3/MusicXML_ParserTest1.xml");
        fScore_ParserTest2 = _test_utils->initialiseScoreFromFile("MusicXMLv3/MusicXML_ParserTest2.xml");
        fScore_ParserTest3 = _test_utils->initialiseScoreFromFile("MusicXMLv3/MusicXML_ParserTest3.xml");
        fScore_ParserTest4 = _test_utils->initialiseScoreFromFile("MusicXMLv3/MusicXML_ParserTest4.xml");
        fScore_ParserTest5 = _test_utils->initialiseScoreFromFile("MusicXMLv3/MusicXML_ParserTest5.xml");
        
        fScore_ParserTestBeetAnGeSample = _test_utils->initialiseScoreFromFile("MusicXMLv3.xmlsamples/BeetAnGeSample.xml");
    }
    
    static bool CheckLyric(S_IMUSANT_part part, int measure_index, int note_index,
                           int syllable_index, string expected,
                           IMUSANT_syllabic::type syllabic = IMUSANT_syllabic::type::single)
    {
        IMUSANT_vector<S_IMUSANT_measure> measures = part->measures();
        S_IMUSANT_measure p_m = measures[measure_index];
        
        IMUSANT_vector<S_IMUSANT_note>& notes = p_m->notes();
        vector<S_IMUSANT_note>::iterator it;
        
        S_IMUSANT_note note = notes[note_index];
        S_IMUSANT_lyric lyric = (note->lyrics())[0];
        string syllable = lyric->getSyllables()[syllable_index];
        
        bool result = syllable.compare(expected) == 0;
        bool syllabic_result = (lyric->getSyllabic() == syllabic);
        
        if (!result) cout << "Got: " << syllable << ", Expected: " << expected << endl;
        
        
        if (!syllabic_result)
        {
            string syl_expected = IMUSANT_syllabic::xml(syllabic);
            string syl_actual = IMUSANT_syllabic::xml(lyric->getSyllabic());
            cout << "Got syllabic of: " << syl_actual << ", Expected: " << syl_expected << endl;
            
        }
        return (result && syllabic_result);
    }
    
    static IMUSANT_test_utilities * _test_utils;
    
    static S_IMUSANT_score fScore_ParserTest1;
    static S_IMUSANT_score fScore_ParserTest2;
    static S_IMUSANT_score fScore_ParserTest3;
    static S_IMUSANT_score fScore_ParserTest4;
    static S_IMUSANT_score fScore_ParserTest5;
    static S_IMUSANT_score fScore_ParserTestBeetAnGeSample;
    
    const int NUM_MEASURES_PARSER_TEST_1 = 12;
    const int KEY_AND_TIME_CHANGE_MEASURE_NUM_PARSER_TEST_1 = 7; // This is the bar where the time and key signatures change
    
    void verbose_output(string expected, string actual);
};


// Initialise static's outside the class so it will link.
S_IMUSANT_score IMUSANT_mxmlv3_to_imusant_visitor_Tests::fScore_ParserTest1 = NULL;
S_IMUSANT_score IMUSANT_mxmlv3_to_imusant_visitor_Tests::fScore_ParserTest2 = NULL;
S_IMUSANT_score IMUSANT_mxmlv3_to_imusant_visitor_Tests::fScore_ParserTest3 = NULL;
S_IMUSANT_score IMUSANT_mxmlv3_to_imusant_visitor_Tests::fScore_ParserTest4 = NULL;
S_IMUSANT_score IMUSANT_mxmlv3_to_imusant_visitor_Tests::fScore_ParserTest5 = NULL;
S_IMUSANT_score IMUSANT_mxmlv3_to_imusant_visitor_Tests::fScore_ParserTestBeetAnGeSample = NULL;

IMUSANT_test_utilities * IMUSANT_mxmlv3_to_imusant_visitor_Tests::_test_utils = NULL;


void
IMUSANT_mxmlv3_to_imusant_visitor_Tests::
verbose_output(string expected, string actual)
{
#ifdef VERBOSE
    _test_utils->DiffActualAndExpected(actual, expected);
    
//    cout << "ACTUAL: " << endl;
//    cout << actual << endl;
//    cout << "EXPECTED " << endl;
//    cout << expected << endl;
#endif
}


// ************* TEST CASES START HERE *********** //


TEST_F(IMUSANT_mxmlv3_to_imusant_visitor_Tests, MXMLv3_Dichterliebe01)
{
    string relative_path = "MusicXMLv3.xmlsamples/Dichterliebe01.xml";
    
    filesystem::path file_path = _test_utils->makePathToTestFile(relative_path);
    
    IMUSANT_processing parser;
    S_IMUSANT_score score = parser.addFile(file_path);
    
    ASSERT_EQ(score->getWorkNum(),  "Op. 48");
    ASSERT_EQ(score->getWorkTitle(), "Dichterliebe");
    
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
    S_IMUSANT_score score = IMUSANT_mxmlv3_to_imusant_visitor_Tests::fScore_ParserTest1;
    
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
    S_IMUSANT_score score = IMUSANT_mxmlv3_to_imusant_visitor_Tests::fScore_ParserTest1;
    
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
    
    ASSERT_EQ(12, part_list[0]->getDivisions());
    ASSERT_EQ(12, part_list[1]->getDivisions());
    ASSERT_EQ(12, part_list[2]->getDivisions());
    ASSERT_EQ(12, part_list[3]->getDivisions());
}


TEST_F(IMUSANT_mxmlv3_to_imusant_visitor_Tests, MeasureProperties_ParserTest1)
{
    S_IMUSANT_score score = IMUSANT_mxmlv3_to_imusant_visitor_Tests::fScore_ParserTest1;

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
    unsigned long p1_m1_note_count = first_p1_measure->elements().size();
    unsigned long  p1_m2_note_count = second_p1_measure->elements().size();
    unsigned long  p4_m7_note_count = change_p4_measure->elements().size();
    
    ASSERT_EQ(1, p1_m1_note_count);
    ASSERT_EQ(3, p1_m2_note_count);
    ASSERT_EQ(5, p4_m7_note_count);
}

TEST_F(IMUSANT_mxmlv3_to_imusant_visitor_Tests, MeasurePrintTest1_ParserTest1)
{
    S_IMUSANT_score score = IMUSANT_mxmlv3_to_imusant_visitor_Tests::fScore_ParserTest1;

    S_IMUSANT_part p1_sop;
    score->getPartById("P1", p1_sop);
    IMUSANT_vector<S_IMUSANT_measure> p1_measures = p1_sop->measures();
    S_IMUSANT_measure second_p1_measure = p1_measures[1];
    
    const string second_p1_measure_expected =
    "<MEAS>=1\n<CLEF> 0@0<\\CLEF>\n<TIME>/<\\TIME>\n<KEY>-1, mode: 0<\\KEY>\n<NOTE measure_num=1 index=1 >\n <PITCH>C1@4<\\PITCH>\n <VOICE>1<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>measure[0] index[1]<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE measure_num=1 index=2 >\n <PITCH>C0@5<\\PITCH>\n <VOICE>1<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>natural<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE measure_num=1 index=3 >\n <PITCH>G0@4<\\PITCH>\n <VOICE>1<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/2<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<\\MEAS>\n";
    
    stringstream second_p1_measure_printed;
    
    second_p1_measure->print(second_p1_measure_printed);
    
    verbose_output(second_p1_measure_expected, second_p1_measure_printed.str());
    
    ASSERT_EQ(second_p1_measure_expected, second_p1_measure_printed.str());
}

TEST_F(IMUSANT_mxmlv3_to_imusant_visitor_Tests, MeasurePrintTest2_ParserTest1)
{
    S_IMUSANT_score score = IMUSANT_mxmlv3_to_imusant_visitor_Tests::fScore_ParserTest1;
    
    S_IMUSANT_part p1_sop;
    score->getPartById("P1", p1_sop);
    IMUSANT_vector<S_IMUSANT_measure> p1_measures = p1_sop->measures();
    S_IMUSANT_measure change_p1_measure = p1_measures[KEY_AND_TIME_CHANGE_MEASURE_NUM_PARSER_TEST_1];
    
    const string change_p1_measure_expected = "<MEAS>=7\n<CLEF> 0@0<\\CLEF>\n<TIME>6/8<\\TIME>\n<KEY>3, mode: 0<\\KEY>\n<NOTE measure_num=7 index=1 >\n <PITCH>C1@5<\\PITCH>\n <VOICE>1<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>1<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE measure_num=7 index=2 >\n <PITCH>C1@5<\\PITCH>\n <VOICE>1<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>1<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<\\MEAS>\n";
    
    stringstream change_p1_measure_printed;
    
    change_p1_measure->print(change_p1_measure_printed);

    verbose_output(change_p1_measure_expected,change_p1_measure_printed.str());
    
    ASSERT_EQ(change_p1_measure_expected, change_p1_measure_printed.str());
}

TEST_F(IMUSANT_mxmlv3_to_imusant_visitor_Tests, MeasurePrintTest3_ParserTest1)
{
    S_IMUSANT_score score = IMUSANT_mxmlv3_to_imusant_visitor_Tests::fScore_ParserTest1;
    
    S_IMUSANT_part p1_sop;
    score->getPartById("P1", p1_sop);
    IMUSANT_vector<S_IMUSANT_measure> p1_measures = p1_sop->measures();
    S_IMUSANT_measure p1_m4 = p1_measures[4];
    
    const string p1_m4_expected = "<MEAS>=4\n<CLEF> 0@0<\\CLEF>\n<TIME>/<\\TIME>\n<KEY>-1, mode: 0<\\KEY>\n<BARLINE location=left style=heavy-light\\>\n <REPEAT direction=forward //>\n<NOTE measure_num=4 index=1 >\n <PITCH>F1@4<\\PITCH>\n <VOICE>1<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/8<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>3/2<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE measure_num=4 index=2 >\n <PITCH>F-1@4<\\PITCH>\n <VOICE>1<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/8<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>3/2<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>flat<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE measure_num=4 index=3 >\n <PITCH>F1@4<\\PITCH>\n <VOICE>1<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/8<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>3/2<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>sharp<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE measure_num=4 index=4 >\n <PITCH>F-2@4<\\PITCH>\n <VOICE>1<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/8<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>3/2<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>flat-flat<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE measure_num=4 index=5 >\n <PITCH>E2@4<\\PITCH>\n <VOICE>1<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/8<\\RHYTHM_TYPE><DOTS>1<\\DOTS><TIME_MOD>3/2<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>double-sharp<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE measure_num=4 index=6 >\n <PITCH>F1@4<\\PITCH>\n <VOICE>1<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/16<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>3/2<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>sharp<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE measure_num=4 index=7 >\n <PITCH>NULL<\\PITCH>\n <VOICE>1<VOICE\\>\n <REST\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE measure_num=4 index=8 >\n <PITCH>NULL<\\PITCH>\n <VOICE>1<VOICE\\>\n <REST\\>\n <DURATION><RHYTHM_TYPE>1/8<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE measure_num=4 index=9 >\n <PITCH>NULL<\\PITCH>\n <VOICE>1<VOICE\\>\n <REST\\>\n <DURATION><RHYTHM_TYPE>1/8<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<\\MEAS>\n";
    
    stringstream p1_m4_printed;
    
    p1_m4->print(p1_m4_printed);
    
    verbose_output(p1_m4_expected, p1_m4_printed.str());
    
    ASSERT_EQ(p1_m4_expected, p1_m4_printed.str());
}

TEST_F(IMUSANT_mxmlv3_to_imusant_visitor_Tests, GraceNotes_ParserTest1)
{
    S_IMUSANT_score score = IMUSANT_mxmlv3_to_imusant_visitor_Tests::fScore_ParserTest1;
    
    S_IMUSANT_part p2_alto;
    score->getPartById("P2", p2_alto);
    IMUSANT_vector<S_IMUSANT_measure> p2_measures = p2_alto->measures();
    S_IMUSANT_measure p2_m2 = p2_measures[2];
    
    const string p2_m2_expected = "<MEAS>=2\n<CLEF> 0@0<\\CLEF>\n<TIME>/<\\TIME>\n<KEY>-1, mode: 0<\\KEY>\n<NOTE measure_num=2 index=1 >\n <PITCH>E0@4<\\PITCH>\n <VOICE>1<VOICE\\>\n <GRACE\\>\n <DURATION><RHYTHM_TYPE>1/8<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE measure_num=2 index=2 >\n <PITCH>E0@4<\\PITCH>\n <VOICE>1<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/2<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE measure_num=2 index=3 >\n <PITCH>G0@4<\\PITCH>\n <VOICE>1<VOICE\\>\n <GRACE\\>\n <DURATION><RHYTHM_TYPE>1/8<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE measure_num=2 index=4 >\n <PITCH>G0@4<\\PITCH>\n <VOICE>1<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE measure_num=2 index=5 >\n <PITCH>G0@4<\\PITCH>\n <VOICE>1<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE measure_num=2 index=6 >\n <PITCH>F1@4<\\PITCH>\n <VOICE>1<VOICE\\>\n <GRACE\\>\n <DURATION><RHYTHM_TYPE>1/16<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<\\MEAS>\n";
    
    stringstream p2_m2_printed;
    
    p2_m2->print(p2_m2_printed);
    
    verbose_output(p2_m2_expected,p2_m2_printed.str());
    
    ASSERT_EQ(p2_m2_expected, p2_m2_printed.str());

}

TEST_F(IMUSANT_mxmlv3_to_imusant_visitor_Tests, Rests_ParserTest1)
{
    S_IMUSANT_score score = IMUSANT_mxmlv3_to_imusant_visitor_Tests::fScore_ParserTest1;
    
    S_IMUSANT_part p2_alto;
    score->getPartById("P2", p2_alto);
    IMUSANT_vector<S_IMUSANT_measure> p2_measures = p2_alto->measures();
    S_IMUSANT_measure p2_m3 = p2_measures[3];
    
    // whole bar rest...
    const string p2_m3_expected = "<MEAS>=3\n<CLEF> 0@0<\\CLEF>\n<TIME>/<\\TIME>\n<KEY>-1, mode: 0<\\KEY>\n<NOTE measure_num=3 index=1 >\n <PITCH>NULL<\\PITCH>\n <VOICE>1<VOICE\\>\n <REST\\>\n <DURATION><RHYTHM_TYPE>1/1<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<\\MEAS>\n";
    
    stringstream p2_m3_printed;
    
    p2_m3->print(p2_m3_printed);
    
    verbose_output(p2_m3_expected,p2_m3_printed.str());

    ASSERT_EQ(p2_m3_expected, p2_m3_printed.str());
    
    S_IMUSANT_part p3_tenor;
    score->getPartById("P3", p3_tenor);
    IMUSANT_vector<S_IMUSANT_measure> p3_measures = p3_tenor->measures();
    S_IMUSANT_measure p3_m4 = p3_measures[4];
    
    const string p3_m4_expected = "<MEAS>=4\n<CLEF> 0@0<\\CLEF>\n<TIME>/<\\TIME>\n<KEY>-1, mode: 0<\\KEY>\n<BARLINE location=left style=heavy-light\\>\n <REPEAT direction=forward //>\n<NOTE measure_num=4 index=1 >\n <PITCH>NULL<\\PITCH>\n <VOICE>1<VOICE\\>\n <REST\\>\n <DURATION><RHYTHM_TYPE>1/8<\\RHYTHM_TYPE><DOTS>1<\\DOTS><TIME_MOD>3/3<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE measure_num=4 index=2 >\n <PITCH>NULL<\\PITCH>\n <VOICE>1<VOICE\\>\n <REST\\>\n <DURATION><RHYTHM_TYPE>1/16<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>3/3<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE measure_num=4 index=3 >\n <PITCH>NULL<\\PITCH>\n <VOICE>1<VOICE\\>\n <REST\\>\n <DURATION><RHYTHM_TYPE>1/8<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>3/3<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE measure_num=4 index=4 >\n <PITCH>NULL<\\PITCH>\n <VOICE>1<VOICE\\>\n <REST\\>\n <DURATION><RHYTHM_TYPE>1/16<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>3/2<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE measure_num=4 index=5 >\n <PITCH>NULL<\\PITCH>\n <VOICE>1<VOICE\\>\n <REST\\>\n <DURATION><RHYTHM_TYPE>1/16<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>3/2<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE measure_num=4 index=6 >\n <PITCH>NULL<\\PITCH>\n <VOICE>1<VOICE\\>\n <REST\\>\n <DURATION><RHYTHM_TYPE>1/16<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>3/2<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE measure_num=4 index=7 >\n <PITCH>NULL<\\PITCH>\n <VOICE>1<VOICE\\>\n <REST\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE measure_num=4 index=8 >\n <PITCH>NULL<\\PITCH>\n <VOICE>1<VOICE\\>\n <REST\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<\\MEAS>\n";
    
    stringstream p3_m4_printed;
    
    p3_m4->print(p3_m4_printed);
    
    verbose_output(p3_m4_expected,p3_m4_printed.str());
    
    ASSERT_EQ(p3_m4_expected, p3_m4_printed.str());
}


TEST_F(IMUSANT_mxmlv3_to_imusant_visitor_Tests, BackwardRepeat_ParserTest1)
{
    S_IMUSANT_score score = IMUSANT_mxmlv3_to_imusant_visitor_Tests::fScore_ParserTest1;
    
    S_IMUSANT_part p2_alto;
    score->getPartById("P2", p2_alto);
    IMUSANT_vector<S_IMUSANT_measure> p2_measures = p2_alto->measures();
    S_IMUSANT_measure p2_m8 = p2_measures[8];
    
    const string p2_m8_expected = "<MEAS>=8\n<CLEF> 0@0<\\CLEF>\n<TIME>/<\\TIME>\n<KEY>-1, mode: 0<\\KEY>\n<BARLINE location=left style=none\\>\n <ENDING type=start number=1 \\>\n<NOTE measure_num=8 index=1 >\n <PITCH>NULL<\\PITCH>\n <VOICE>1<VOICE\\>\n <REST\\>\n <DURATION><RHYTHM_TYPE>3/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<BARLINE location=right style=light-heavy\\>\n <ENDING type=stop number=1 \\>\n <REPEAT direction=backward //>\n<\\MEAS>\n";
    
    stringstream p2_m8_printed;
    
    p2_m8->print(p2_m8_printed);
    
    verbose_output(p2_m8_expected,p2_m8_printed.str());
    
    ASSERT_EQ(p2_m8_expected, p2_m8_printed.str());
}

TEST_F(IMUSANT_mxmlv3_to_imusant_visitor_Tests, Ending_ParserTest1)
{
    S_IMUSANT_score score = IMUSANT_mxmlv3_to_imusant_visitor_Tests::fScore_ParserTest1;
    
    S_IMUSANT_part p2_alto;
    score->getPartById("P2", p2_alto);
    IMUSANT_vector<S_IMUSANT_measure> p2_measures = p2_alto->measures();
    S_IMUSANT_measure p2_m9 = p2_measures[9];
    
    const string p2_m9_expected = "<MEAS>=9\n<CLEF> 0@0<\\CLEF>\n<TIME>/<\\TIME>\n<KEY>-1, mode: 0<\\KEY>\n<BARLINE location=left style=none\\>\n <ENDING type=start number=2 \\>\n<NOTE measure_num=9 index=1 >\n <PITCH>NULL<\\PITCH>\n <VOICE>1<VOICE\\>\n <REST\\>\n <DURATION><RHYTHM_TYPE>3/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<BARLINE location=right style=none\\>\n <ENDING type=stop number=2 \\>\n<\\MEAS>\n";
    
    stringstream p2_m9_printed;
    
    p2_m9->print(p2_m9_printed);
    
    verbose_output(p2_m9_expected, p2_m9_printed.str());

    ASSERT_EQ(p2_m9_expected, p2_m9_printed.str());
}


TEST_F(IMUSANT_mxmlv3_to_imusant_visitor_Tests, Chords_Simple_ParserTest2)
{
    S_IMUSANT_score score = fScore_ParserTest2;
    
    S_IMUSANT_part p1;
    score->getPartById("P1", p1);
    IMUSANT_vector<S_IMUSANT_measure> p1_measures = p1->measures();
    S_IMUSANT_measure p1_m2 = p1_measures[2];
    
    // REVISIT - it is strange that there are two chords in this measure. Each hand on the Piano seems to be treated separatly.
    const string p1_m2_expected = "<MEAS>=3\n<CLEF> 0@0<\\CLEF>\n<TIME>/<\\TIME>\n<KEY>-1, mode: 0<\\KEY>\n<NOTE measure_num=3 index=1 >\n <PITCH>E0@4<\\PITCH>\n <VOICE>1<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/1<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<CHRD>\n <NOTE measure_num=3 index=1 >\n <PITCH>E0@4<\\PITCH>\n <VOICE>1<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/1<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n <NOTE measure_num=3 index=2 >\n <PITCH>C0@5<\\PITCH>\n <VOICE>1<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/1<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<\\CHRD>\n<NOTE measure_num=3 index=2 >\n <PITCH>C0@5<\\PITCH>\n <VOICE>1<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/1<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE measure_num=3 index=3 >\n <PITCH>C0@3<\\PITCH>\n <VOICE>5<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/1<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<CHRD>\n <NOTE measure_num=3 index=3 >\n <PITCH>C0@3<\\PITCH>\n <VOICE>5<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/1<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n <NOTE measure_num=3 index=4 >\n <PITCH>G0@3<\\PITCH>\n <VOICE>5<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/1<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<\\CHRD>\n<NOTE measure_num=3 index=4 >\n <PITCH>G0@3<\\PITCH>\n <VOICE>5<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/1<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<\\MEAS>\n";
    
    stringstream p1_m2_actual;
    
    p1_m2->print(p1_m2_actual);
    
    verbose_output(p1_m2_expected, p1_m2_actual.str());

    ASSERT_EQ(p1_m2_expected, p1_m2_actual.str());
}

TEST_F(IMUSANT_mxmlv3_to_imusant_visitor_Tests, Chords_LessSimple_ParserTest2)
{
    S_IMUSANT_score score = fScore_ParserTest2;
    
    S_IMUSANT_part p1;
    score->getPartById("P1", p1);
    IMUSANT_vector<S_IMUSANT_measure> p1_measures = p1->measures();
    S_IMUSANT_measure p1_m3 = p1_measures[3];
    
    // REVISIT - it is strange that there are two chords in this measure. Each hand on the Piano seems to be treated separatly.
    const string p1_m3_expected = "<MEAS>=4\n<CLEF> 0@0<\\CLEF>\n<TIME>/<\\TIME>\n<KEY>-1, mode: 0<\\KEY>\n<NOTE measure_num=4 index=1 >\n <PITCH>E0@4<\\PITCH>\n <VOICE>1<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/8<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<CHRD>\n <NOTE measure_num=4 index=1 >\n <PITCH>E0@4<\\PITCH>\n <VOICE>1<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/8<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n <NOTE measure_num=4 index=2 >\n <PITCH>C0@5<\\PITCH>\n <VOICE>1<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/8<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<\\CHRD>\n<NOTE measure_num=4 index=2 >\n <PITCH>C0@5<\\PITCH>\n <VOICE>1<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/8<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE measure_num=4 index=3 >\n <PITCH>D0@5<\\PITCH>\n <VOICE>1<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/8<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE measure_num=4 index=4 >\n <PITCH>E0@4<\\PITCH>\n <VOICE>1<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<CHRD>\n <NOTE measure_num=4 index=4 >\n <PITCH>E0@4<\\PITCH>\n <VOICE>1<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n <NOTE measure_num=4 index=5 >\n <PITCH>E0@5<\\PITCH>\n <VOICE>1<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<\\CHRD>\n<NOTE measure_num=4 index=5 >\n <PITCH>E0@5<\\PITCH>\n <VOICE>1<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE measure_num=4 index=6 >\n <PITCH>G0@4<\\PITCH>\n <VOICE>1<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<CHRD>\n <NOTE measure_num=4 index=6 >\n <PITCH>G0@4<\\PITCH>\n <VOICE>1<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n <NOTE measure_num=4 index=7 >\n <PITCH>D0@5<\\PITCH>\n <VOICE>1<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<\\CHRD>\n<NOTE measure_num=4 index=7 >\n <PITCH>D0@5<\\PITCH>\n <VOICE>1<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE measure_num=4 index=8 >\n <PITCH>E0@4<\\PITCH>\n <VOICE>1<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<CHRD>\n <NOTE measure_num=4 index=8 >\n <PITCH>E0@4<\\PITCH>\n <VOICE>1<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n <NOTE measure_num=4 index=9 >\n <PITCH>C0@5<\\PITCH>\n <VOICE>1<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<\\CHRD>\n<NOTE measure_num=4 index=9 >\n <PITCH>C0@5<\\PITCH>\n <VOICE>1<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE measure_num=4 index=10 >\n <PITCH>C0@3<\\PITCH>\n <VOICE>5<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<CHRD>\n <NOTE measure_num=4 index=10 >\n <PITCH>C0@3<\\PITCH>\n <VOICE>5<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n <NOTE measure_num=4 index=11 >\n <PITCH>G0@3<\\PITCH>\n <VOICE>5<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<\\CHRD>\n<NOTE measure_num=4 index=11 >\n <PITCH>G0@3<\\PITCH>\n <VOICE>5<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE measure_num=4 index=12 >\n <PITCH>D0@3<\\PITCH>\n <VOICE>5<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<CHRD>\n <NOTE measure_num=4 index=12 >\n <PITCH>D0@3<\\PITCH>\n <VOICE>5<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n <NOTE measure_num=4 index=13 >\n <PITCH>G0@3<\\PITCH>\n <VOICE>5<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<\\CHRD>\n<NOTE measure_num=4 index=13 >\n <PITCH>G0@3<\\PITCH>\n <VOICE>5<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE measure_num=4 index=14 >\n <PITCH>E0@3<\\PITCH>\n <VOICE>5<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<CHRD>\n <NOTE measure_num=4 index=14 >\n <PITCH>E0@3<\\PITCH>\n <VOICE>5<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n <NOTE measure_num=4 index=15 >\n <PITCH>G0@3<\\PITCH>\n <VOICE>5<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<\\CHRD>\n<NOTE measure_num=4 index=15 >\n <PITCH>G0@3<\\PITCH>\n <VOICE>5<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE measure_num=4 index=16 >\n <PITCH>F0@3<\\PITCH>\n <VOICE>5<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<CHRD>\n <NOTE measure_num=4 index=16 >\n <PITCH>F0@3<\\PITCH>\n <VOICE>5<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n <NOTE measure_num=4 index=17 >\n <PITCH>G0@3<\\PITCH>\n <VOICE>5<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<\\CHRD>\n<NOTE measure_num=4 index=17 >\n <PITCH>G0@3<\\PITCH>\n <VOICE>5<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<\\MEAS>\n";
    
    stringstream p1_m3_actual;
    
    p1_m3->print(p1_m3_actual);
    
    verbose_output(p1_m3_expected,p1_m3_actual.str());

    ASSERT_EQ(p1_m3_expected, p1_m3_actual.str());
    
}

TEST_F(IMUSANT_mxmlv3_to_imusant_visitor_Tests, Chords_MultiNote_BeetAnGeSample)
{
    S_IMUSANT_score score = fScore_ParserTestBeetAnGeSample;
    
    S_IMUSANT_part p2;
    score->getPartById("P2", p2);
    IMUSANT_vector<S_IMUSANT_measure> p2_measures = p2->measures();
    S_IMUSANT_measure p2_m3 = p2_measures[2];
    
    const string p2_m3_expected = "<MEAS>=3\n<CLEF> 0@0<\\CLEF>\n<TIME>/<\\TIME>\n<KEY>-1, mode: 0<\\KEY>\n<NOTE measure_num=3 index=1 >\n <PITCH>NULL<\\PITCH>\n <VOICE>1<VOICE\\>\n <REST\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE measure_num=3 index=2 >\n <PITCH>G0@3<\\PITCH>\n <VOICE>1<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<CHRD>\n <NOTE measure_num=3 index=2 >\n <PITCH>G0@3<\\PITCH>\n <VOICE>1<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n <NOTE measure_num=3 index=3 >\n <PITCH>C0@4<\\PITCH>\n <VOICE>1<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n <NOTE measure_num=3 index=4 >\n <PITCH>E-1@4<\\PITCH>\n <VOICE>1<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n <NOTE measure_num=3 index=5 >\n <PITCH>G0@4<\\PITCH>\n <VOICE>1<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<\\CHRD>\n<NOTE measure_num=3 index=3 >\n <PITCH>C0@4<\\PITCH>\n <VOICE>1<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE measure_num=3 index=4 >\n <PITCH>E-1@4<\\PITCH>\n <VOICE>1<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE measure_num=3 index=5 >\n <PITCH>G0@4<\\PITCH>\n <VOICE>1<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE measure_num=3 index=6 >\n <PITCH>NULL<\\PITCH>\n <VOICE>1<VOICE\\>\n <REST\\>\n <DURATION><RHYTHM_TYPE>1/8<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE measure_num=3 index=7 >\n <PITCH>G0@3<\\PITCH>\n <VOICE>1<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/8<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<CHRD>\n <NOTE measure_num=3 index=7 >\n <PITCH>G0@3<\\PITCH>\n <VOICE>1<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/8<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n <NOTE measure_num=3 index=8 >\n <PITCH>E-1@4<\\PITCH>\n <VOICE>1<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/8<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n <NOTE measure_num=3 index=9 >\n <PITCH>G0@4<\\PITCH>\n <VOICE>1<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/8<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<\\CHRD>\n<NOTE measure_num=3 index=8 >\n <PITCH>E-1@4<\\PITCH>\n <VOICE>1<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/8<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE measure_num=3 index=9 >\n <PITCH>G0@4<\\PITCH>\n <VOICE>1<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/8<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE measure_num=3 index=10 >\n <PITCH>NULL<\\PITCH>\n <VOICE>3<VOICE\\>\n <REST\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE measure_num=3 index=11 >\n <PITCH>C0@2<\\PITCH>\n <VOICE>3<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<CHRD>\n <NOTE measure_num=3 index=11 >\n <PITCH>C0@2<\\PITCH>\n <VOICE>3<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n <NOTE measure_num=3 index=12 >\n <PITCH>C0@3<\\PITCH>\n <VOICE>3<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<\\CHRD>\n<NOTE measure_num=3 index=12 >\n <PITCH>C0@3<\\PITCH>\n <VOICE>3<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/4<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE measure_num=3 index=13 >\n <PITCH>NULL<\\PITCH>\n <VOICE>3<VOICE\\>\n <REST\\>\n <DURATION><RHYTHM_TYPE>1/8<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<NOTE measure_num=3 index=14 >\n <PITCH>B-1@1<\\PITCH>\n <VOICE>3<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/8<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<CHRD>\n <NOTE measure_num=3 index=14 >\n <PITCH>B-1@1<\\PITCH>\n <VOICE>3<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/8<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n <NOTE measure_num=3 index=15 >\n <PITCH>B-1@2<\\PITCH>\n <VOICE>3<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/8<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<\\CHRD>\n<NOTE measure_num=3 index=15 >\n <PITCH>B-1@2<\\PITCH>\n <VOICE>3<VOICE\\>\n <DURATION><RHYTHM_TYPE>1/8<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n<\\MEAS>\n";
    
    stringstream p2_m3_actual;
    
    p2_m3->print(p2_m3_actual);
    
    verbose_output(p2_m3_expected,p2_m3_actual.str());
    
    ASSERT_EQ(p2_m3_expected, p2_m3_actual.str());
    
}

TEST_F(IMUSANT_mxmlv3_to_imusant_visitor_Tests, Clef_ParserTest3)
{
    S_IMUSANT_score score = fScore_ParserTest3;
    
    S_IMUSANT_part p1;
    S_IMUSANT_part p3;
    S_IMUSANT_part p4;
    score->getPartById("P1", p1);
    score->getPartById("P3", p3);
    score->getPartById("P4", p4);
    
    IMUSANT_vector<S_IMUSANT_measure> p1_measures = p1->measures();
    S_IMUSANT_measure p1_m2 = p1_measures[2];
    IMUSANT_clef clef = p1_m2->getClef();
    ASSERT_EQ(IMUSANT_clef::C_clef, clef.getSign());
    ASSERT_EQ(2, clef.getLine());
    ASSERT_EQ(0, clef.getTransposition());
    
    IMUSANT_vector<S_IMUSANT_measure> p3_measures = p3->measures();
    S_IMUSANT_measure p3_m0 = p3_measures[0];
    clef = p3_m0->getClef();
    ASSERT_EQ(IMUSANT_clef::G_clef, clef.getSign());
    ASSERT_EQ(2, clef.getLine());
    ASSERT_EQ(-1, clef.getTransposition());
    
    IMUSANT_vector<S_IMUSANT_measure> p4_measures = p4->measures();
    S_IMUSANT_measure p4_m2 = p4_measures[2];
    clef = p4_m2->getClef();
    ASSERT_EQ(IMUSANT_clef::F_clef, clef.getSign());
    ASSERT_EQ(4, clef.getLine());
    ASSERT_EQ(1, clef.getTransposition());
}


TEST_F(IMUSANT_mxmlv3_to_imusant_visitor_Tests, Lyric_ParserTest4)
{
    S_IMUSANT_score score = fScore_ParserTest4;
    
    S_IMUSANT_part p1;
    score->getPartById("P1", p1);
    
    ASSERT_TRUE(CheckLyric(p1, 0, 0, 0, "these"));
    ASSERT_FALSE(CheckLyric(p1, 0, 0, 0, "IGNORE THIS OUTPUT UNLESS THE TEST FAILS")) << "Test is broken...";
    
    
    ASSERT_TRUE(CheckLyric(p1, 1, 0, 0, "are"));
    ASSERT_TRUE(CheckLyric(p1, 2, 0, 0, "the"));
    ASSERT_TRUE(CheckLyric(p1, 3, 0, 0, "words"));
    ASSERT_TRUE(CheckLyric(p1, 4, 0, 0, "to"));
    ASSERT_TRUE(CheckLyric(p1, 5, 0, 0, "a"));
    ASSERT_TRUE(CheckLyric(p1, 6, 0, 0, "short"));
    ASSERT_TRUE(CheckLyric(p1, 7, 0, 0, "song"));
    
    ASSERT_TRUE(CheckLyric(p1, 8, 0, 0, "pol", IMUSANT_syllabic::type::begin));
    ASSERT_TRUE(CheckLyric(p1, 8, 1, 0, "y", IMUSANT_syllabic::type::middle));
    ASSERT_TRUE(CheckLyric(p1, 9, 0, 0, "syl", IMUSANT_syllabic::type::middle));
    ASSERT_TRUE(CheckLyric(p1, 9, 1, 0, "ab", IMUSANT_syllabic::type::middle));
    ASSERT_TRUE(CheckLyric(p1, 10, 0, 0, "ic", IMUSANT_syllabic::type::end));
}


TEST_F(IMUSANT_mxmlv3_to_imusant_visitor_Tests, Frermata_ParserTest5)
{
    S_IMUSANT_score score = fScore_ParserTest5;
    
    S_IMUSANT_part p1;
    S_IMUSANT_part p2;
    
    score->getPartById("P1", p1);
    score->getPartById("P2", p2);
    
    IMUSANT_vector<S_IMUSANT_measure> p1_measures = p1->measures();
    IMUSANT_vector<S_IMUSANT_measure> p2_measures = p2->measures();
    
    S_IMUSANT_measure p1_m1 = p1_measures[0];
    IMUSANT_vector<S_IMUSANT_note> notes = p1_m1->notes();
    
    ASSERT_FALSE(notes[0]->hasFermata());
    ASSERT_FALSE(notes[1]->hasFermata());
    ASSERT_FALSE(notes[2]->hasFermata());
    ASSERT_TRUE(notes[3]->hasFermata());

    S_IMUSANT_measure p2_m1 = p2_measures[0];
    notes = p2_m1->notes();
    
    ASSERT_FALSE(notes[0]->hasFermata());
    ASSERT_TRUE(notes[1]->hasFermata());

    
    // See Task TK-01140 in VersionOne
    // REVISIT - I have generated test data from MuseScore, but it
    // does not appear to support fermata on barlines.  This means
    // that when you export as MusicXML, MuseScore does not generate
    // any barline elements for the first measure, and so the code
    // below crashes.  You can see this in the test data file used
    // in this test.
    
    
//    IMUSANT_vector<S_IMUSANT_barline> barlines = p2_m1->barlines();
//    S_IMUSANT_barline barline = barlines[0];
//    ASSERT_FALSE(barline->hasFermata());
//    
//    barline = p2_m1->barlines()[1];
//    ASSERT_TRUE(barline->hasFermata());
    
}


TEST_F(IMUSANT_mxmlv3_to_imusant_visitor_Tests, ExpectingAnException_ScoreInstrument_Telemann_mxml3)
{
    // MusicXMLv3.xmlsamples/Telemann.xml is not a simple partwise score but uses a "orchestral part".
    // Exception should be thrown.
    
    bool exception_occurred = false;
    
    try
    {
        _test_utils->initialiseScoreFromFile("MusicXMLv3.xmlsamples/Telemann.xml");
    }
    catch (string s)
    {
        exception_occurred = true;
    }
    
    ASSERT_TRUE(exception_occurred) << "Didn't receive the expected exception";

}


