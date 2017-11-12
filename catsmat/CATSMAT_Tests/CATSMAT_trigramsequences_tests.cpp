//
//  CATSMAT_NGram_Test.cpp
//  imusant
//
//  Created by Jason Stoessel on 27/11/2016.
//
//

#include <stdio.h>

#include "CATSMAT_TrigramSequences.h"
#include "CATSMAT_TrigramSuffixTreeBuilder.h"
#include "TRepeatedSubstring.h"

#include "CATSMAT_test_utility.h"

#include "CATSMAT_trigramsequences_expected.h"

#include "gtest/gtest.h"
#include <boost/filesystem.hpp>

#define VERBOSE

// The fixture for testing class CATSMAT_cp_matrix.
class CATSMAT_TrigramSequences_Test : public ::testing::Test {
    
protected:
    
    CATSMAT_TrigramSequences_Test() {
        // You can do set-up work for each test here.
    }
    
    virtual ~CATSMAT_TrigramSequences_Test() {
        // You can do clean-up work that doesn't throw exceptions here.
    }
    
    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:
    
    virtual void SetUp() {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }
    
    virtual void TearDown() {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }
    
    // Objects declared here can be used by all tests in the test case for CATSMAT_cp_matrix_Test.
    CATSMAT_test_utility testUtil;
    CATSMAT::CATSMAT_TrigramSequences theSequences;
    
};

TEST_F(CATSMAT_TrigramSequences_Test, TestScore_1_Measure) {
    
    CATSMAT::S_CATSMAT_cp_matrix the_matrix = testUtil.ConvertMusicXmlToCpmatrix("TestScore_1_Measure.xml");
    the_matrix->Accept(theSequences);
    
    string the_sequences_as_string = testUtil.ConvertNGramSequencesToString(theSequences);
    
    ASSERT_EQ(TestScore_1_Measure_Expected, the_sequences_as_string);
}

TEST_F(CATSMAT_TrigramSequences_Test, TestScore_4_Measures) {

    CATSMAT::S_CATSMAT_cp_matrix the_matrix = testUtil.ConvertMusicXmlToCpmatrix("TestScore_4_Measures.xml");
    the_matrix->Accept(theSequences);

    string the_sequences_as_string = testUtil.ConvertNGramSequencesToString(theSequences);
    
    ASSERT_EQ(TestScore_4_Measures_Expected, the_sequences_as_string);
}

TEST_F(CATSMAT_TrigramSequences_Test, TestScore_4_Measures_WithQuaverPassingNotes) {
    
    CATSMAT::S_CATSMAT_cp_matrix the_matrix = testUtil.ConvertMusicXmlToCpmatrix("TestScore_4_Measures_WithQuaverPassingNotes.xml");
    theSequences.set_ignore_dissonances(false);
    the_matrix->Accept(theSequences);
    
    string the_sequences_as_string = testUtil.ConvertNGramSequencesToString(theSequences);
    
    ASSERT_EQ(TestScore_4_Measures_WithQuaverPassingNotes_Expected, the_sequences_as_string);
}

TEST_F(CATSMAT_TrigramSequences_Test, TestScore_4_Measures_WithSemiQuaverPassingNotes) {
    
    CATSMAT::S_CATSMAT_cp_matrix the_matrix = testUtil.ConvertMusicXmlToCpmatrix("TestScore_4_Measures_WithSemiQuaverPassingNotes.xml");
    theSequences.set_ignore_dissonances(false);
    the_matrix->Accept(theSequences);
    
    string the_sequences_as_string = testUtil.ConvertNGramSequencesToString(theSequences);
    
    ASSERT_EQ(TestScore_4_Measures_WithSemiQuaverPassingNotes_Expected, the_sequences_as_string);
}


TEST_F(CATSMAT_TrigramSequences_Test, TestScore_Josquin_MAF_Kyrie) {
    
    CATSMAT::S_CATSMAT_cp_matrix the_matrix = testUtil.ConvertMusicXmlToCpmatrix("Josquin_MAF_Kyrie.xml");
    theSequences.set_ignore_dissonances(false);
    the_matrix->Accept(theSequences);
    
    string the_sequences_as_string = testUtil.ConvertNGramSequencesToString(theSequences);
    
#ifdef VERBOSE
    cout << "Diff for Triplet_Test_Actual and Triplet_Test_Expected" << endl;
    testUtil.DiffActualAndExpected(the_sequences_as_string, TestScore_Josquin_MAF_Kyrie);
#endif
    
    ASSERT_EQ(TestScore_Josquin_MAF_Kyrie, the_sequences_as_string);
}

TEST_F(CATSMAT_TrigramSequences_Test, TestScore_Josquin_MAF_Kyrie_no_dissonances) {
    
    CATSMAT::S_CATSMAT_cp_matrix the_matrix = testUtil.ConvertMusicXmlToCpmatrix("Josquin_MAF_Kyrie.xml");
    theSequences.set_ignore_dissonances(true);
    the_matrix->Accept(theSequences);
    std::stringstream ss;
    
    int i = 1;
    for (auto tokens_sequence : theSequences.get_tokens())
    {
        ss << "Voice pair" << i << " : ";
        for (auto token : tokens_sequence)
        {
            CATSMAT_TrigramSequences::Trigram trigram = CATSMAT_TrigramSequences::Token2Triple(token);
            ss << trigram << ", ";
        }
        i++;
        ss << endl;
    }
    
    string the_tokens_as_string = ss.str();
    
    ASSERT_EQ(TestScore_Josquin_MAF_Kyrie_no_dissonances_Expected, the_tokens_as_string);
}

TEST_F(CATSMAT_TrigramSequences_Test, TestScore_Josquin_MAF_Kyrie_Repeats) {
    
    CATSMAT_TrigramSuffixTreeBuilder::SUBSTR_VECTOR repeats;
    CATSMAT_TrigramSuffixTreeBuilder trigram_tree;
    
    CATSMAT::S_CATSMAT_cp_matrix the_matrix = testUtil.ConvertMusicXmlToCpmatrix("Josquin_MAF_Kyrie.xml");
    
    theSequences.set_ignore_dissonances(true);
    theSequences.set_ignore_repeated(true);
    the_matrix->Accept(theSequences);
    theSequences.Accept(trigram_tree);
    
    repeats = trigram_tree.FindRepeatedSubstrings(3);
    
    std::stringstream the_dyads_as_stringstream;
    for ( auto repeat : repeats)
    {
        the_dyads_as_stringstream << repeat;
    }
    string the_sequences_as_string = the_dyads_as_stringstream.str();
    
    ASSERT_EQ(TestScore_Josquin_MAF_Kyrie_Repeats_Expected, the_sequences_as_string);
}

TEST_F(CATSMAT_TrigramSequences_Test, TestScore_Talent_mest_pris_repeats) {
    
    CATSMAT_TrigramSuffixTreeBuilder::SUBSTR_VECTOR repeats;
    CATSMAT_TrigramSuffixTreeBuilder trigram_tree;
    
    CATSMAT::S_CATSMAT_cp_matrix the_matrix = testUtil.ConvertMusicXmlToCpmatrix("Anon-Talent_mest_pris_I-IV_115.xml");
    
    theSequences.set_ignore_dissonances(true);
    the_matrix->Accept(theSequences);
    theSequences.Accept(trigram_tree);
    
    repeats = trigram_tree.FindRepeatedSubstrings(4);
    
    std::stringstream the_trigrams_as_stringstream;

    for (auto repeat : repeats)
    {
        //the following replaces for now the following call that no longer evokes the override friend function
        //the_trigrams_as_stringstream << repeat;
        the_trigrams_as_stringstream << " ";

        for (auto token : repeat.sequence)
        {
            the_trigrams_as_stringstream << CATSMAT_TrigramSequences::Token2Triple(token);
        }

        for (auto occurrence : repeat.occurrences)
        {
            the_trigrams_as_stringstream << "("
               << "MVT: " << occurrence.movement << ", "
               << "VCE: " << occurrence.voice << ", "
               << "MES: " << occurrence.measure << ", "
               << "IDX: " << occurrence.note_index << ") ";
        }
        the_trigrams_as_stringstream << std::endl << std::endl;
    }
    string the_sequences_as_string = the_trigrams_as_stringstream.str();
    
    ASSERT_EQ(TestScore_Talent_mest_pris_repeats_Expected, the_sequences_as_string);
}

TEST_F(CATSMAT_TrigramSequences_Test, TestScore_Talent_mest_pris_trigram_information) {
    
    CATSMAT_TrigramSuffixTreeBuilder::SUBSTR_VECTOR repeats;
    
    CATSMAT::S_CATSMAT_cp_matrix the_matrix = testUtil.ConvertMusicXmlToCpmatrix("Anon-Talent_mest_pris_I-IV_115.xml");
    
    theSequences.set_ignore_dissonances(true);
    the_matrix->Accept(theSequences);
    CATSMAT_TrigramInformation trigram_info;
    theSequences.Accept(trigram_info);
    
    std::stringstream the_info_as_stringstream;
    the_info_as_stringstream << trigram_info;
    string the_sequences_as_string = the_info_as_stringstream.str();
    
    ASSERT_EQ(TestScore_Talent_mest_pris_trigram_information_Expected, the_sequences_as_string);
}

TEST_F(CATSMAT_TrigramSequences_Test, TestScore_Josquin_MAF_Kyrie_trigram_information) {
    
    CATSMAT_TrigramSuffixTreeBuilder::SUBSTR_VECTOR repeats;
    
    CATSMAT::S_CATSMAT_cp_matrix the_matrix = testUtil.ConvertMusicXmlToCpmatrix("Josquin_MAF_Kyrie.xml");
    
    theSequences.set_ignore_dissonances(true);
    the_matrix->Accept(theSequences);
    CATSMAT_TrigramInformation trigram_info;
    theSequences.Accept(trigram_info);
    
    std::stringstream the_info_as_stringstream;
    the_info_as_stringstream << trigram_info;
    string the_sequences_as_string = the_info_as_stringstream.str();
    
    ASSERT_EQ(TestScore_Josquin_MAF_Kyrie_trigram_information_Expected, the_sequences_as_string);
}

TEST_F(CATSMAT_TrigramSequences_Test, TestScore_4_Measures_WithQuaverPassingNotes_output) {

    CATSMAT::S_CATSMAT_cp_matrix the_matrix = testUtil.ConvertMusicXmlToCpmatrix("TestScore_4_Measures_WithQuaverPassingNotes.xml");
    theSequences.set_ignore_dissonances(false);
    the_matrix->Accept(theSequences);

    std::stringstream ss;
    theSequences.PrintTokens(ss);

    string the_sequences_as_string = ss.str();

    ASSERT_EQ(TestScore_4_Measures_WithQuaverPassingNotesOutput_Expected, the_sequences_as_string);
}

TEST_F(CATSMAT_TrigramSequences_Test, TestScore_4_Measures_WithSemiQuaverPassingNotes_output) {

    CATSMAT::S_CATSMAT_cp_matrix the_matrix = testUtil.ConvertMusicXmlToCpmatrix("TestScore_4_Measures_WithSemiQuaverPassingNotes.xml");
    theSequences.set_ignore_dissonances(false);
    the_matrix->Accept(theSequences);

    std::stringstream ss;
    theSequences.PrintTokens(ss);

    string the_sequences_as_string = ss.str();

    ASSERT_EQ(TestScore_4_Measures_WithSemiQuaverPassingNotes_output, the_sequences_as_string);
}

TEST_F(CATSMAT_TrigramSequences_Test, Josquin_MAF_Kyrie_trigram_output) {

    CATSMAT::S_CATSMAT_cp_matrix the_matrix = testUtil.ConvertMusicXmlToCpmatrix("Josquin_MAF_Kyrie.xml");
    theSequences.set_ignore_dissonances(false);
    the_matrix->Accept(theSequences);

    std::stringstream ss;
    ss << "Indices: " << "\t";
    for (auto chord : the_matrix->getCPmatrix())
    {
        ss << chord->begin()->second->getMeasureNum() << "." << chord->begin()->second->getNoteIndex() << "\t";
    }
    ss << std::endl;

    theSequences.PrintTokens(ss);

    string the_sequences_as_string = ss.str();

#ifdef VERBOSE
    cout << the_sequences_as_string << endl;
#endif

    ASSERT_EQ(Josquin_MAF_Kyrie_trigram_output, the_sequences_as_string);
}
