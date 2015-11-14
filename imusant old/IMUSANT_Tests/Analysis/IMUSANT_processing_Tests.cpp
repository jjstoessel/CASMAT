//
//  IMUSANT_processing_Tests.cpp
//  imusant
//
//  Created by Derrick Hill on 9/08/2015.
//
//

#include "IMUSANT_processing_Expected.h"

#include <stdio.h>

#include "gtest/gtest.h"

#include "libIMUSANT.h"
#include <boost/filesystem.hpp>

using namespace IMUSANT;
using namespace boost;

// The fixture for testing class IMUSANT_pitch.
class IMUSANT_processing_Tests : public ::testing::Test {
    
protected:
    
    IMUSANT_processing_Tests()
    {
        // You can do set-up work for each test here.
    }
    
    virtual ~IMUSANT_processing_Tests()
    {
        // You can do clean-up work that doesn't throw exceptions here.
    }
    
    vector<IMUSANT_repeated_interval_substring> find_repeated_substrings_by_file(string path_to_test_data_file);
    vector<IMUSANT_repeated_interval_substring> find_repeated_substrings_by_directory(string path_to_test_data_directory);
    
    filesystem::path make_path_to_test_file(string relative_path_to_test_data_file);
  
};


filesystem::path
IMUSANT_processing_Tests::
make_path_to_test_file(string relative_path_to_test_data_file)
{
    filesystem::path testdata(filesystem::initial_path());
    testdata.append("IMUSANT_testdata");
    testdata.append(relative_path_to_test_data_file);
    return testdata;
}


vector<IMUSANT_repeated_interval_substring>
IMUSANT_processing_Tests::
find_repeated_substrings_by_file(string relative_path_to_test_data_file)
{
    filesystem::path testdata = make_path_to_test_file(relative_path_to_test_data_file);
    
    filesystem::file_status status = filesystem::status(testdata);
    if (!filesystem::exists(status))
    {
        cerr << "Can't find the test data file at " <<  relative_path_to_test_data_file << endl;
        throw("File not found: " + relative_path_to_test_data_file) ;
    }
    
    if (!filesystem::is_regular_file(status))
    {
        cerr << "This path is not a file: " <<  relative_path_to_test_data_file << endl;
        throw("Not a file: " + relative_path_to_test_data_file) ;
    }
    
    IMUSANT_processing *the_processor = new IMUSANT_processing();
    
    the_processor->add_file(testdata);
    
    vector<IMUSANT_repeated_interval_substring> repeated_substrings_result;
    repeated_substrings_result = the_processor->find_repeated_interval_substrings();
    
    return repeated_substrings_result;
}

vector<IMUSANT_repeated_interval_substring>
IMUSANT_processing_Tests::
find_repeated_substrings_by_directory(string relative_path_to_test_data_directory)
{
    filesystem::path testdata(filesystem::initial_path());
    testdata.append("IMUSANT_testdata");
    testdata.append(relative_path_to_test_data_directory);
    
    filesystem::file_status status = filesystem::status(testdata);
    if (!filesystem::exists(status))
    {
        cerr << "Problem with the test data at " <<  relative_path_to_test_data_directory << endl;
        throw("File not found: " + relative_path_to_test_data_directory) ;
    }
    
    if (!filesystem::is_directory(status))
    {
        cerr << "This path is not a directory: " <<  relative_path_to_test_data_directory << endl;
        throw("Not a directory: " + relative_path_to_test_data_directory) ;
    }
    
    IMUSANT_processing *the_processor = new IMUSANT_processing();
    
    the_processor->process_directory_files(testdata);
    
    vector<IMUSANT_repeated_interval_substring> repeated_substrings_result;
    repeated_substrings_result = the_processor->find_repeated_interval_substrings();
    
    return repeated_substrings_result;
}


// ************* TEST CASES START HERE *********** //


TEST_F(IMUSANT_processing_Tests, find_repeated_interval_substrings_from_v1_directory)
{
    vector<IMUSANT_repeated_interval_substring> repeated_substrings_result;
    repeated_substrings_result = find_repeated_substrings_by_directory("MusicXMLv1.simple_test_data");
    
    ASSERT_EQ(48, repeated_substrings_result.size());
    
    stringstream actual_output;
    for(int index = 0 ; index < repeated_substrings_result.size(); index++)
    {
        actual_output << repeated_substrings_result[index];
    }
    
    actual_output << endl;
    
    //    cout << actual_output.str();
    //    cout << FindRepeatedIntervalSubstrings_RefactorTest_Expected;
    
    ASSERT_EQ(FindRepeatedIntervalSubstrings_RefactorTest_Expected, actual_output.str());
}

TEST_F(IMUSANT_processing_Tests, compare_v1_and_v3_repeated_substring_processing)
{
    vector<IMUSANT_repeated_interval_substring> v1_repeated_substrings_result;
    v1_repeated_substrings_result = find_repeated_substrings_by_file("test_files/MusicXMLv1/Josquin_MSN_Kyrie.xml");
    
    vector<IMUSANT_repeated_interval_substring> v3_repeated_substrings_result;
    v3_repeated_substrings_result = find_repeated_substrings_by_file("test_files/MusicXMLv3/Josquin_MSN_Kyrie.xml");
    
    ASSERT_EQ(v1_repeated_substrings_result.size(), v3_repeated_substrings_result.size())  << "EXPECTED FAILURE - Output vectors are not the same length.";
    
    stringstream v1_actual_output;
    stringstream v3_actual_output;
    
    for(int index = 0 ; index < v1_repeated_substrings_result.size(); index++)
    {
        v1_actual_output << v1_repeated_substrings_result[index];
    }
    
    for(int index = 0 ; index < v3_repeated_substrings_result.size(); index++)
    {
        v3_actual_output << v3_repeated_substrings_result[index];
    }
    
    ASSERT_EQ(v1_actual_output.str(), v3_actual_output.str()) << "Output strings are not identical.";
}

TEST_F(IMUSANT_processing_Tests, FindRepeatedIntervalSubstrings_Dichterliebe01_mxml3)
{
    string relative_path = "MusicXMLv3.xmlsamples/Dichterliebe01.xml";
    vector<IMUSANT_repeated_interval_substring> repeated_substrings_result;
    repeated_substrings_result = find_repeated_substrings_by_file(relative_path);
    
    ASSERT_EQ(519, repeated_substrings_result.size()) << "EXPECTED FAILURE";
    
    stringstream actual_output;
    for(int index = 0 ; index < repeated_substrings_result.size(); index++)
    {
        actual_output << repeated_substrings_result[index];
    }
    
    actual_output << endl;
    
    ASSERT_EQ(FindRepeatedIntervalSubstrings_Dichterliebe01_Expected, actual_output.str());
}

TEST_F(IMUSANT_processing_Tests, MXMLv3_Dichterliebe01)
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
    
    /*
     part
     */
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

TEST_F(IMUSANT_processing_Tests, MXMLv3_MusicXML_ParserTest1)
{
    string relative_path = "MusicXMLv3.simple_test_data/MusicXML_ParserTest1.xml";
    
    filesystem::path file_path = make_path_to_test_file(relative_path);
    
    IMUSANT_processing parser;
    S_IMUSANT_score score = parser.process_musicxml3_file(file_path);
    
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
    
    const int NUM_MEASURES = 12;
    
    IMUSANT_vector<S_IMUSANT_measure> pt1_measures = part_list[0]->measures();
    ASSERT_EQ(NUM_MEASURES, pt1_measures.size());
    IMUSANT_vector<S_IMUSANT_measure> pt2_measures = part_list[1]->measures();
    ASSERT_EQ(NUM_MEASURES, pt2_measures.size());
    
    /*
     part
     */
    S_IMUSANT_part p1_sop;
    S_IMUSANT_part p4_bass;
    
    score->getPartById("P1", p1_sop);
    score->getPartById("P4", p4_bass);
    
    IMUSANT_vector<S_IMUSANT_measure> p1_measures = p1_sop->measures();
    IMUSANT_vector<S_IMUSANT_measure> p4_measures = p4_bass->measures();
    
    ASSERT_EQ(NUM_MEASURES, p1_measures.size());
    ASSERT_EQ(NUM_MEASURES, p4_measures.size());
    
    S_IMUSANT_measure first_p1_measure = p1_measures[0];
    S_IMUSANT_measure second_p1_measure = p1_measures[1];
    
    IMUSANT_key::mode p1_mode = first_p1_measure->getKey().getMode();
    long p1_fifths = first_p1_measure->getKey().getFifths();
    ASSERT_EQ(2, p1_fifths);
    ASSERT_EQ(IMUSANT_key::mode::generic, p1_mode);
    
    IMUSANT_time p1_time = first_p1_measure->getTime();
    ASSERT_EQ(p1_time.getNumerator()[0], 4);
    ASSERT_EQ(p1_time.getDenominator()[0], 4);
    
    const int KEY_AND_TIME_CHANGE_MEASURE_NUM = 7; // This is the bar where the time and key signatures change
    S_IMUSANT_measure change_p1_measure = p1_measures[KEY_AND_TIME_CHANGE_MEASURE_NUM];
    S_IMUSANT_measure change_p4_measure = p4_measures[KEY_AND_TIME_CHANGE_MEASURE_NUM];
    
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
    
    const string second_p1_measure_expected =
        "<MEAS>=1\n<CLEF> 0@0<\\CLEF>\n<TIME>/<\\TIME>\n<KEY>-1, mode: 0<\\KEY>\n<NOTE index=1 measure_num=1 >\n <PITCH>C1@4<\\PITCH>\n <DURATION><RHYTHM_TYPE>1/4<//RHYTHM_TYPE><DOTS>0<//DOTS><TIME_MOD>0/0<TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<\\NOTE>\n<NOTE index=2 measure_num=1 >\n <PITCH>C0@5<\\PITCH>\n <DURATION><RHYTHM_TYPE>1/4<//RHYTHM_TYPE><DOTS>0<//DOTS><TIME_MOD>0/0<TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<\\NOTE>\n<NOTE index=3 measure_num=1 >\n <PITCH>G0@4<\\PITCH>\n <DURATION><RHYTHM_TYPE>1/2<//RHYTHM_TYPE><DOTS>0<//DOTS><TIME_MOD>0/0<TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<\\NOTE>\n<\\MEAS>\n";
    stringstream second_p1_measure_printed;
    
    second_p1_measure->print(second_p1_measure_printed);
    ASSERT_EQ(second_p1_measure_expected, second_p1_measure_printed.str());
    
    
    const string change_p1_measure_expected = "<MEAS>=7\n<CLEF> 0@0<\\CLEF>\n<TIME>6/8<\\TIME>\n<KEY>3, mode: 0<\\KEY>\n<NOTE index=1 measure_num=7 >\n <PITCH>C1@5<\\PITCH>\n <DURATION><RHYTHM_TYPE>1/4<//RHYTHM_TYPE><DOTS>1<//DOTS><TIME_MOD>0/0<TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<\\NOTE>\n<NOTE index=2 measure_num=7 >\n <PITCH>D0@5<\\PITCH>\n <DURATION><RHYTHM_TYPE>1/8<//RHYTHM_TYPE><DOTS>0<//DOTS><TIME_MOD>0/0<TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<\\NOTE>\n<NOTE index=3 measure_num=7 >\n <PITCH>C1@5<\\PITCH>\n <DURATION><RHYTHM_TYPE>1/4<//RHYTHM_TYPE><DOTS>1<//DOTS><TIME_MOD>0/0<TIME_MOD><\\DURATION>\n <ACCIDENTAL>NULL<\\ACCIDENTAL>\n<\\NOTE>\n<\\MEAS>\n";
    stringstream change_p1_measure_printed;
    
    change_p1_measure->print(change_p1_measure_printed);
    ASSERT_EQ(change_p1_measure_expected, change_p1_measure_printed.str());
}



