//
//  CATSMAT_NGram_Test.cpp
//  imusant
//
//  Created by Jason Stoessel on 27/11/2016.
//
//

#include <stdio.h>

#include "CATSMAT_TrigramSequences.hpp"
#include "CATSMAT_TrigramSuffixTreeBuilder.hpp"
#include "IMUSANT_t_repeated_substring.h"

#include "CATSMAT_test_utility.h"

#include "CATSMAT_TrigramSequences_Test_Expected.h"

#include "gtest/gtest.h"
#include <boost/filesystem.hpp>

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
    theSequences.Visit(*the_matrix);
    
    string the_sequences_as_string = testUtil.ConvertNGramSequencesToString(theSequences);
    
    ASSERT_EQ(TestScore_1_Measure_Expected, the_sequences_as_string);
}

TEST_F(CATSMAT_TrigramSequences_Test, TestScore_4_Measures) {

    CATSMAT::S_CATSMAT_cp_matrix the_matrix = testUtil.ConvertMusicXmlToCpmatrix("TestScore_4_Measures.xml");
    theSequences.Visit(*the_matrix);

    string the_sequences_as_string = testUtil.ConvertNGramSequencesToString(theSequences);
    
    ASSERT_EQ(TestScore_4_Measures_Expected, the_sequences_as_string);
}

TEST_F(CATSMAT_TrigramSequences_Test, TestScore_4_Measures_WithQuaverPassingNotes) {
    
    CATSMAT::S_CATSMAT_cp_matrix the_matrix = testUtil.ConvertMusicXmlToCpmatrix("TestScore_4_Measures_WithQuaverPassingNotes.xml");
    theSequences.Visit(*the_matrix);
    
    string the_sequences_as_string = testUtil.ConvertNGramSequencesToString(theSequences);
    
    ASSERT_EQ(TestScore_4_Measures_WithQuaverPassingNotes_Expected, the_sequences_as_string);
}

TEST_F(CATSMAT_TrigramSequences_Test, TestScore_4_Measures_WithSemiQuaverPassingNotes) {
    
    CATSMAT::S_CATSMAT_cp_matrix the_matrix = testUtil.ConvertMusicXmlToCpmatrix("TestScore_4_Measures_WithSemiQuaverPassingNotes.xml");
    theSequences.Visit(*the_matrix);
    
    string the_sequences_as_string = testUtil.ConvertNGramSequencesToString(theSequences);
    
    ASSERT_EQ(TestScore_4_Measures_WithSemiQuaverPassingNotes_Expected, the_sequences_as_string);
}


TEST_F(CATSMAT_TrigramSequences_Test, TestScore_Josquin_MAF_Kyrie) {
    
    CATSMAT::S_CATSMAT_cp_matrix the_matrix = testUtil.ConvertMusicXmlToCpmatrix("Josquin_MAF_Kyrie.xml");
    theSequences.Visit(*the_matrix);
    
    string the_sequences_as_string = testUtil.ConvertNGramSequencesToString(theSequences);
    
    ASSERT_EQ(TestScore_Josquin_MAF_Kyrie, the_sequences_as_string);
}

TEST_F(CATSMAT_TrigramSequences_Test, TestScore_Josquin_MAF_Kyrie_Repeats) {
    
    CATSMAT_TrigramSuffixTreeBuilder::SUBSTR_VECTOR repeats;
    CATSMAT_TrigramSuffixTreeBuilder trigram_tree;
    
    CATSMAT::S_CATSMAT_cp_matrix the_matrix = testUtil.ConvertMusicXmlToCpmatrix("Josquin_MAF_Kyrie.xml");
    
    theSequences.Visit(*the_matrix);
    trigram_tree.Visit(theSequences);
    
    repeats = trigram_tree.FindRepeatedIntervalSubstrings(3);
    
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
    
    theSequences.Visit(*the_matrix);
    trigram_tree.Visit(theSequences);
    
    repeats = trigram_tree.FindRepeatedIntervalSubstrings(4);
    
    std::stringstream the_dyads_as_stringstream;
    for ( auto repeat : repeats)
    {
        the_dyads_as_stringstream << repeat;
    }
    string the_sequences_as_string = the_dyads_as_stringstream.str();
    
    ASSERT_EQ(TestScore_Talent_mest_pris_repeats_Expected, the_sequences_as_string);
}
