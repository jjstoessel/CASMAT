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
     <score-part id="P2">
     */
    IMUSANT_vector<S_IMUSANT_part> part_list = score->partlist()->parts();
    ASSERT_EQ(4, part_list.size());
    ASSERT_EQ(part_list[0]->getPartName(), "Soprano");
    ASSERT_EQ(part_list[1]->getPartName(), "Alto");
    ASSERT_EQ(part_list[2]->getPartName(), "Tenor");
    ASSERT_EQ(part_list[3]->getPartName(), "Bass");
    
    const int NUM_MEASURES = 42;
    
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
    ASSERT_EQ(2, p1_fifths);
    ASSERT_EQ(IMUSANT_key::mode::generic, p1_mode);
    
    IMUSANT_time p1_time = first_p1_measure->getTime();
    ASSERT_EQ(p1_time.getNumerator()[0], 4);
    ASSERT_EQ(p1_time.getDenominator()[0], 4);
    
    S_IMUSANT_measure change_p1_measure = p1_measures[7];
    
    p1_mode = change_p1_measure->getKey().getMode();
    p1_fifths = change_p1_measure->getKey().getFifths();
    ASSERT_EQ(3, p1_fifths);
    ASSERT_EQ(IMUSANT_key::mode::generic, p1_mode);
    
    p1_time = change_p1_measure->getTime();
    ASSERT_EQ(p1_time.getNumerator()[0], 6);
    ASSERT_EQ(p1_time.getDenominator()[0], 8);
    
}



