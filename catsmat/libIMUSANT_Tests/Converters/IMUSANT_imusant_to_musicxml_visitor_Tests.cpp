//
// IMUSANT_imusant_to_musicxml_visitor_Tests.cpp
//
// Created by Jason Stoessel on 2019-04-13.
//

#include <stdio.h>

#include "gtest/gtest.h"

#include "libIMUSANT.h"
#include "IMUSANT_test_utilities.h"
#include "IMUSANT_imusant_to_musicxml_visitor.h"

#define VERBOSE 1

using namespace IMUSANT;

// The fixture for testing class IMUSANT_duration.
class IMUSANT_imusant_to_musicxml_visitor_Tests : public ::testing::Test {

protected:

    IMUSANT_imusant_to_musicxml_visitor_Tests()
    {
        // You can do set-up work for each test here.
    }

    virtual ~IMUSANT_imusant_to_musicxml_visitor_Tests()
    {
        // You can do clean-up work that doesn't throw exceptions here.
    }
    static void SetUpTestCase() {
        _test_utils = new IMUSANT_test_utilities("IMUSANT_testdata");

        fScore_ParserTest1 = _test_utils->initialiseScoreFromFile("MusicXMLv3/MusicXML_ParserTest1.xml");
        fScore_ParserTest2 = _test_utils->initialiseScoreFromFile("MusicXMLv3/MusicXML_ParserTest2.xml");
        fScore_ParserTest3 = _test_utils->initialiseScoreFromFile("MusicXMLv3/MusicXML_ParserTest3.xml");
        fScore_ParserTest4 = _test_utils->initialiseScoreFromFile("MusicXMLv3/MusicXML_ParserTest4.xml");
        fScore_ParserTest5 = _test_utils->initialiseScoreFromFile("MusicXMLv3/MusicXML_ParserTest5.xml");

    }

    static IMUSANT_test_utilities * _test_utils;

    static S_IMUSANT_score fScore_ParserTest1;
    static S_IMUSANT_score fScore_ParserTest2;
    static S_IMUSANT_score fScore_ParserTest3;
    static S_IMUSANT_score fScore_ParserTest4;
    static S_IMUSANT_score fScore_ParserTest5;

    void verbose_output(string expected, string actual);
};

// Initialise static's outside the class so it will link.
S_IMUSANT_score IMUSANT_imusant_to_musicxml_visitor_Tests::fScore_ParserTest1 = NULL;
S_IMUSANT_score IMUSANT_imusant_to_musicxml_visitor_Tests::fScore_ParserTest2 = NULL;
S_IMUSANT_score IMUSANT_imusant_to_musicxml_visitor_Tests::fScore_ParserTest3 = NULL;
S_IMUSANT_score IMUSANT_imusant_to_musicxml_visitor_Tests::fScore_ParserTest4 = NULL;
S_IMUSANT_score IMUSANT_imusant_to_musicxml_visitor_Tests::fScore_ParserTest5 = NULL;

IMUSANT_test_utilities * IMUSANT_imusant_to_musicxml_visitor_Tests::_test_utils = NULL;

void
IMUSANT_imusant_to_musicxml_visitor_Tests::
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

TEST_F(IMUSANT_imusant_to_musicxml_visitor_Tests, ParserTest1)
{
    S_IMUSANT_score score = IMUSANT_imusant_to_musicxml_visitor_Tests::fScore_ParserTest1;

    IMUSANT_to_MusicXML_Visitor IMUSANT_to_MUSICXML;

    score->accept(IMUSANT_to_MUSICXML);

    std::stringstream rxmlss;
    factoryPrint(IMUSANT_to_MUSICXML.getFactory(), rxmlss);
    std::string reconstituted_xml = rxmlss.str();

    filesystem::path test_file_path = _test_utils->makePathToTestFile("MusicXMLv3/MusicXML_ParserTest1.xml");
    std::ifstream oxmlf;
    oxmlf.open(test_file_path.c_str());
    std::stringstream oxmlss;
    oxmlss << oxmlf.rdbuf();
    std::string original_xml = oxmlss.str();

#ifdef VERBOSE
    cout << original_xml << std::endl;
    cout << reconstituted_xml << std::endl;
    cout << "Diff for original and reconstituted XML file" << endl;
    _test_utils->DiffActualAndExpected(original_xml, reconstituted_xml);
#endif
    ASSERT_EQ(original_xml, reconstituted_xml);

}
