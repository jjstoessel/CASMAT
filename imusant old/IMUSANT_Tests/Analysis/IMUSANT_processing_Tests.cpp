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
#include "IMUSANT_interval_processor.h"
#include "IMUSANT_contour_processor.h"
#include "IMUSANT_pitch_processor.h"

//#define VERBOSE //toggle for verbose output

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
    vector<IMUSANT_repeated_contour_substring>  find_repeated_contour_substrings_by_file(string relative_path_to_test_data_file);
    
    vector<IMUSANT_repeated_interval_substring> find_supermaximals_intervals_by_file(string relative_path_to_test_data_file);
    void                                        find_lcs_pairs_intervals_by_file(string relative_path_to_test_data_file, bool reverse_search=false, bool retrograde=false);
    
    vector<S_IMUSANT_segmented_part_LBDM>       findSegmentedPartsByFile(vector<string> relative_paths_to_test_data_files);
    
    filesystem::path make_path_to_test_file(string relative_path_to_test_data_file);
    IMUSANT_processing* file_to_processor(string relative_path_to_test_data_file);
    filesystem::path check_file(string relative_path_to_test_data_file);
  
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

filesystem::path
IMUSANT_processing_Tests::
check_file(string relative_path_to_test_data_file)
{
    filesystem::path testdata = make_path_to_test_file(relative_path_to_test_data_file);
    
    filesystem::file_status status = filesystem::status(testdata);
    if (!filesystem::exists(status))
    {
        cerr << "Can't find the test data file at " <<  testdata << endl;
        throw("File not found: " + testdata.string() );
    }
    
    if (!filesystem::is_regular_file(status))
    {
        cerr << "This path is not a file: " <<  testdata << endl;
        throw("Not a file: " + testdata.string() );
    }

    return testdata;
}

IMUSANT_processing*
IMUSANT_processing_Tests::
file_to_processor(string relative_path_to_test_data_file)
{
    filesystem::path testdata = check_file(relative_path_to_test_data_file);
    
    IMUSANT_processing *the_processor = new IMUSANT_processing();
    
    the_processor->addFile(testdata);
    
    return the_processor;
}

vector<IMUSANT_repeated_interval_substring>
IMUSANT_processing_Tests::
find_repeated_substrings_by_file(string relative_path_to_test_data_file)
{
    IMUSANT_processing *the_processor = file_to_processor(relative_path_to_test_data_file);
    
    IMUSANT_interval_processor interval_processor;
    interval_processor.Visit(*the_processor);
    
    vector<IMUSANT_repeated_interval_substring> repeated_substrings_result;
    repeated_substrings_result = interval_processor.findRepeatedIntervalSubstrings();
    
    return repeated_substrings_result;
}

vector<IMUSANT_repeated_contour_substring>
IMUSANT_processing_Tests::
find_repeated_contour_substrings_by_file(string relative_path_to_test_data_file)
{
    
    IMUSANT_processing *the_processor = file_to_processor(relative_path_to_test_data_file);
    IMUSANT_contour_processor contour_processor;
    contour_processor.Visit(*the_processor);
    vector<IMUSANT_repeated_contour_substring> repeated_substrings_result;
    repeated_substrings_result = contour_processor.findRepeatedContourSubstrings();
    
    return repeated_substrings_result;
    
}

vector<IMUSANT_repeated_interval_substring>
IMUSANT_processing_Tests::
find_supermaximals_intervals_by_file(string relative_path_to_test_data_file)
{
    
    IMUSANT_processing *the_processor = file_to_processor(relative_path_to_test_data_file);
    IMUSANT_interval_processor interval_processor;
    interval_processor.Visit(*the_processor);
    
    vector<IMUSANT_repeated_interval_substring> repeated_substrings_result;
    repeated_substrings_result = interval_processor.findSupermaximalsIntervals(4, 100); //parameterise
    
    //removed below to separate test
    IMUSANT_pitch_processor pitch_processor;
    pitch_processor.Visit(*the_processor);
    pitch_processor.findLcsPairsPitches();
    
    return repeated_substrings_result;
    
}

void
IMUSANT_processing_Tests::
find_lcs_pairs_intervals_by_file(string relative_path_to_test_data_file, bool reverse_search, bool retrograde)
{
    IMUSANT_processing *the_processor = file_to_processor(relative_path_to_test_data_file);
    IMUSANT_interval_processor interval_processor;
    interval_processor.Visit(*the_processor);
    interval_processor.findLcsPairsIntervals(true,reverse_search,retrograde);
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
    
    the_processor->processDirectoryFiles(testdata);
    IMUSANT_interval_processor interval_processor;
    interval_processor.Visit(*the_processor);
    
    vector<IMUSANT_repeated_interval_substring> repeated_substrings_result;
    repeated_substrings_result = interval_processor.findRepeatedIntervalSubstrings();
    
    return repeated_substrings_result;
}

vector<S_IMUSANT_segmented_part_LBDM>
IMUSANT_processing_Tests::
findSegmentedPartsByFile(vector<string> relative_paths_to_test_data_files)
{
    IMUSANT_processing *the_processor = new IMUSANT_processing();
    
    for (vector<string>::iterator path_iter = relative_paths_to_test_data_files.begin(); path_iter != relative_paths_to_test_data_files.end(); path_iter++)
    {
        string relative_path_to_test_data_file = *path_iter;
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
        
        the_processor->addFile(testdata);
    }
    
    vector<S_IMUSANT_segmented_part_LBDM> segmented_parts_result;
    segmented_parts_result = the_processor->findMelodicSegments_LBDM();
    
    return segmented_parts_result;
}


// ************* TEST CASES START HERE *********** //


TEST_F(IMUSANT_processing_Tests, find_repeated_interval_substrings_simple_test_1)
{
    vector<IMUSANT_repeated_interval_substring> repeated_substrings_result;
    repeated_substrings_result = find_repeated_substrings_by_file("MusicXMLv3/RepeatedIntervalSubstrings_SimpleTest1.xml");

    stringstream actual_output;
    
    for(int index = 0 ; index < repeated_substrings_result.size(); index++)
    {
        actual_output << repeated_substrings_result[index];
    }
    actual_output << endl;
    
#ifdef VERBOSE
    cout << IMUSANT_repeated_interval_substring::output_operator_help();
    cout << actual_output.str();
#endif
    
    ASSERT_EQ(FindRepeatedIntervalSubstrings_simple_test_1_Expected, actual_output.str());
}

TEST_F(IMUSANT_processing_Tests, findSupermaximalsIntervals_simple_test_1)
{
    vector<IMUSANT_repeated_interval_substring> repeated_substrings_result;
    //repeated_substrings_result = find_repeated_substrings_by_file("/MusicXMLv3.simple_test_data/RepeatedIntervalSubstrings_SimpleTest1.xml");
    repeated_substrings_result = find_supermaximals_intervals_by_file("MusicXMLv3//RepeatedIntervalSubstrings_SimpleTest1.xml");
//    
//    // REVISIT - remove this output once we have resolved "D-01021" - "https://www52.v1host.com/Private63/defect.mvc/Summary?oidToken=Defect%3A2543"
//    stringstream actual_output;
//    
//    cout << IMUSANT_repeated_interval_substring::output_operator_help();
//    
//    for(int index = 0 ; index < repeated_substrings_result.size(); index++)
//    {
//        actual_output << repeated_substrings_result[index];
//    }
//    actual_output << endl;
//#ifdef VERBOSE
//    cout << actual_output.str();
//#endif
//    ASSERT_EQ(FindRepeatedIntervalSubstrings_simple_test_1_Expected, actual_output.str());
    
    ASSERT_FALSE(true) << "Deliberately failing this test. Needs implementation.";
}


TEST_F(IMUSANT_processing_Tests, find_repeated_interval_substrings_from_v1_directory)
{
//    vector<IMUSANT_repeated_interval_substring> repeated_substrings_result;
//    repeated_substrings_result = find_repeated_substrings_by_directory("MusicXMLv1.simple_test_data");
//    
//    ASSERT_EQ(48, repeated_substrings_result.size());
//    
//    stringstream actual_output;
//    for(int index = 0 ; index < repeated_substrings_result.size(); index++)
//    {
//        actual_output << repeated_substrings_result[index];
//    }
//    
//    actual_output << endl;
    
    //    cout << actual_output.str();
    //    cout << FindRepeatedIntervalSubstrings_RefactorTest_Expected;
    
    //ASSERT_EQ(FindRepeatedIntervalSubstrings_RefactorTest_Expected, actual_output.str()); //use this one
    //ASSERT_TRUE(false) << "Deliberatly failing this test.  See D-01025 in VersionOne.";
}

TEST_F(IMUSANT_processing_Tests, find_lcs_pairs_intervals_simple_test_1)
{
    //vector<IMUSANT_repeated_interval_substring> repeated_substrings_result;
    //repeated_substrings_result = find_repeated_substrings_by_file("/MusicXMLv3.simple_test_data/RepeatedIntervalSubstrings_SimpleTest1.xml");
    //repeated_substrings_result =
    find_lcs_pairs_intervals_by_file("MusicXMLv3/RepeatedIntervalSubstrings_SimpleTest1.xml");
    
    //find_lcs_pairs_intervals_by_file("/RepeatedIntervalSubstrings_SimpleTest1.xml", false, true); // REMOVE TO SEPARATE TEST
    //
    //    // REVISIT - remove this output once we have resolved "D-01021" - "https://www52.v1host.com/Private63/defect.mvc/Summary?oidToken=Defect%3A2543"
    //    stringstream actual_output;
    //
    //    cout << IMUSANT_repeated_interval_substring::output_operator_help();
    //
    //    for(int index = 0 ; index < repeated_substrings_result.size(); index++)
    //    {
    //        actual_output << repeated_substrings_result[index];
    //    }
    //    actual_output << endl;
    //#ifdef VERBOSE
    //    cout << actual_output.str();
    //#endif
    //    ASSERT_EQ(FindRepeatedIntervalSubstrings_simple_test_1_Expected, actual_output.str());
    
    ASSERT_FALSE(true) << "Deliberately failing this test. Needs implementation.";
}

TEST_F(IMUSANT_processing_Tests, exception_when_adding_music_xml_v1_file)
{
    bool expected_exception_caught = false;
    MusicXML1FormatException expected_ex;     //  = *new MusicXML1FormatException();
    string expected_what(expected_ex.what());
    
    cout << "Ignore following output unless this test fails..." << endl;
    
    try
    {
        vector<IMUSANT_repeated_interval_substring> v1_repeated_substrings_result;
        v1_repeated_substrings_result = find_repeated_substrings_by_file("test_files/MusicXMLv1/Josquin_MSN_Kyrie.xml");
    }
    catch (MusicXML1FormatException ex)
    {
        string actual_what(ex.what());
        ASSERT_EQ(expected_what, actual_what);
        expected_exception_caught = true;
    }
    
    ASSERT_TRUE(expected_exception_caught);
}


TEST_F(IMUSANT_processing_Tests, FindRepeatedIntervalSubstrings_Tournai_kyrie_mxml3)
{
    // This is a fairly complex file so I'm including a very rough test
    // here just to make sure that the parser covers it.
    
    string relative_path = "MusicXMLv3/Kyrie.xml";
    vector<IMUSANT_repeated_interval_substring> repeated_substrings_result;
    repeated_substrings_result = find_repeated_substrings_by_file(relative_path);

#ifdef VERBOSE
    stringstream actual_output;
    actual_output << IMUSANT_repeated_interval_substring::output_operator_help();
    
    for(int index = 0 ; index < repeated_substrings_result.size(); index++)
    {
        actual_output << repeated_substrings_result[index];
    }
    
    actual_output << endl;
    
    cout << actual_output.str();
#endif
    
    ASSERT_EQ(154, repeated_substrings_result.size());
}


TEST_F(IMUSANT_processing_Tests, findRepeatedContourSubstrings_simple_test_1)
{
    vector<IMUSANT_repeated_contour_substring> repeated_substrings_result;
    
    repeated_substrings_result = find_repeated_contour_substrings_by_file("MusicXMLv3/RepeatedIntervalSubstrings_SimpleTest1.xml");
    
    // REVISIT - remove this output once we have resolved "D-01021" - "https://www52.v1host.com/Private63/defect.mvc/Summary?oidToken=Defect%3A2543"
    stringstream actual_output;
    
#ifdef VERBOSE
    cout << IMUSANT_repeated_interval_substring::output_operator_help();
#endif
    
    for(int index = 0 ; index < repeated_substrings_result.size(); index++)
    {
        actual_output << repeated_substrings_result[index];
    }
    actual_output << endl;
#ifdef VERBOSE
    cout << actual_output.str();
#endif
    ASSERT_EQ(FindRepeatedContourSubstrings_simple_test_1_Expected, actual_output.str());
    
    //ASSERT_FALSE(true) << "Deliberately failing this test. Return string on ";
}


//
// This is a simple test to see that IMUSANT_processing is basically returning a result that matches the
// file(s).  All the logic tests for S_IMUSANT_segmented_part_LBDM are in the test file that corresponds
// to that class.
//
TEST_F(IMUSANT_processing_Tests, FindMelodicSegments_LBDM_Test1)
{
    vector<S_IMUSANT_segmented_part_LBDM> segmented_parts;
    
    vector<string> test_data_files;
    test_data_files.push_back("MusicXMLv3//LBDM_Segmented_Part_Test_1.xml");
    test_data_files.push_back("MusicXMLv3//LBDM_Segmented_Part_Test_2.xml");
    test_data_files.push_back("MusicXMLv3//LBDM_Segmented_Part_Test_3.xml");

    segmented_parts = findSegmentedPartsByFile(test_data_files);
    
#ifdef VERBOSE
    for (vector<S_IMUSANT_segmented_part_LBDM>::iterator seg_parts_iter = segmented_parts.begin(); seg_parts_iter != segmented_parts.end() ; seg_parts_iter++)
    {
        S_IMUSANT_segmented_part_LBDM sp = (*seg_parts_iter);
        cout << *sp << endl;
    }
#endif
    
    ASSERT_EQ(9, segmented_parts.size()) << "Unexpected number of parts.";
    
    S_IMUSANT_part t1_soprano = segmented_parts[0]->getPart();
    S_IMUSANT_part t1_alto = segmented_parts[1]->getPart();
    S_IMUSANT_part t1_tenor = segmented_parts[2]->getPart();
    S_IMUSANT_part t1_bass = segmented_parts[3]->getPart();
    S_IMUSANT_part t2_soprano = segmented_parts[4]->getPart();
    S_IMUSANT_part t2_alto = segmented_parts[5]->getPart();
    S_IMUSANT_part t2_tenor = segmented_parts[6]->getPart();
    S_IMUSANT_part t2_bass = segmented_parts[7]->getPart();
    S_IMUSANT_part t3_piano = segmented_parts[8]->getPart();
    
    ASSERT_EQ("Soprano", t1_soprano->getPartName());
    ASSERT_EQ("Alto", t1_alto->getPartName());
    ASSERT_EQ("Tenor", t1_tenor->getPartName());
    ASSERT_EQ("Bass", t1_bass->getPartName());
    ASSERT_EQ("Soprano", t2_soprano->getPartName());
    ASSERT_EQ("Alto", t2_alto->getPartName());
    ASSERT_EQ("Tenor", t2_tenor->getPartName());
    ASSERT_EQ("Bass", t2_bass->getPartName());
    ASSERT_EQ("Piano", t3_piano->getPartName());
    
    vector<float> t1_soprano_strengths = segmented_parts[0]->getOverallLocalBoundaryStrengthProfile();
    vector<float> t1_alto_strengths = segmented_parts[1]->getOverallLocalBoundaryStrengthProfile();
    vector<float> t1_tenor_strengths = segmented_parts[2]->getOverallLocalBoundaryStrengthProfile();
    vector<float> t1_bass_strengths = segmented_parts[3]->getOverallLocalBoundaryStrengthProfile();
    vector<float> t2_soprano_strengths = segmented_parts[4]->getOverallLocalBoundaryStrengthProfile();
    vector<float> t2_alto_strengths = segmented_parts[5]->getOverallLocalBoundaryStrengthProfile();
    vector<float> t2_tenor_strengths = segmented_parts[6]->getOverallLocalBoundaryStrengthProfile();
    vector<float> t2_bass_strengths = segmented_parts[7]->getOverallLocalBoundaryStrengthProfile();
    vector<float> t3_piano_strengths = segmented_parts[8]->getOverallLocalBoundaryStrengthProfile();
    
    ASSERT_EQ(17, t1_soprano_strengths.size());
    ASSERT_EQ(12, t1_alto_strengths.size());
    ASSERT_EQ(19, t1_tenor_strengths.size());
    ASSERT_EQ(6, t1_bass_strengths.size());
    ASSERT_EQ(17, t2_soprano_strengths.size());
    ASSERT_EQ(12, t2_alto_strengths.size());
    ASSERT_EQ(19, t2_tenor_strengths.size());
    ASSERT_EQ(15, t2_bass_strengths.size());
    ASSERT_EQ(31, t3_piano_strengths.size());
}


