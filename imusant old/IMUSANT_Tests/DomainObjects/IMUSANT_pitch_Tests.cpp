//
//  IMUSANT_pitch_Tests.cpp
//  imusant
//
//  Created by Derrick Hill on 26/07/2015.
//
//

#include <stdio.h>

#include "gtest/gtest.h"

#include "libIMUSANT.h"

using namespace IMUSANT;

// The fixture for testing class IMUSANT_pitch.
class IMUSANT_pitch_Tests : public ::testing::Test {
    
    
protected:
    
    IMUSANT_pitch_Tests()
    {
        // You can do set-up work for each test here.
    }
    
    virtual ~IMUSANT_pitch_Tests()
    {
        // You can do clean-up work that doesn't throw exceptions here.
    }
    
    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:
    
    virtual void SetUp()
    {
        // Code here will be called immediately after the constructor (right
        // before each test).
        C4 = CreatePitch(IMUSANT_pitch::type::C, 4, IMUSANT_pitch::natural);
        D4 = CreatePitch(IMUSANT_pitch::type::D, 4, IMUSANT_pitch::natural);
        B3 = CreatePitch(IMUSANT_pitch::type::B, 3, IMUSANT_pitch::natural);
        B4 = CreatePitch(IMUSANT_pitch::type::B, 4, IMUSANT_pitch::natural);
        C5 = CreatePitch(IMUSANT_pitch::type::C, 5, IMUSANT_pitch::natural);
        D5 = CreatePitch(IMUSANT_pitch::type::D, 5, IMUSANT_pitch::natural);
        D4_Sharp = CreatePitch(IMUSANT_pitch::type::D, 4, IMUSANT_pitch::sharp);
        D4_Flat  = CreatePitch(IMUSANT_pitch::type::D, 4, IMUSANT_pitch::flat);
    }
    
    virtual void TearDown()
    {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }
    
    // Objects declared here can be used by all tests in the test case for CATSMAT_cp_matrix_Test.
    S_IMUSANT_pitch C4;
    S_IMUSANT_pitch D4;
    S_IMUSANT_pitch B3;
    S_IMUSANT_pitch B4;
    S_IMUSANT_pitch C5;
    S_IMUSANT_pitch D5;
    S_IMUSANT_pitch D4_Sharp;
    S_IMUSANT_pitch D4_Flat;
    
    S_IMUSANT_pitch CreatePitch(IMUSANT_pitch::type note,
                              unsigned short octave,
                              IMUSANT_pitch::inflection alteration)
    {
        S_IMUSANT_pitch the_pitch = new_IMUSANT_pitch();
        
        the_pitch->setOctave(octave);
        the_pitch->setName(note);
        the_pitch->setAlteration(alteration);
        
        return the_pitch;
    };
    
    private:
};


TEST_F(IMUSANT_pitch_Tests, TestGreaterThan)
{
    // Same note
    ASSERT_FALSE(*C4 > *C4);
    
    // Octaves are different
    ASSERT_TRUE(*C5 > *C4);
    ASSERT_TRUE(*C5 > *D4_Flat);
    ASSERT_FALSE(*C4 > *C5);
    
    // Same octave, different notes
    ASSERT_TRUE(*D4 > *C4);
    ASSERT_TRUE(*B4 > *C4);
    ASSERT_FALSE(*D4 > *B4);
    
    // Same octave, same note, altered
    ASSERT_TRUE(*D4 > *D4_Flat);
    ASSERT_TRUE(*D4_Sharp > *D4);
    ASSERT_TRUE(*D4_Sharp > *D4_Flat);
    ASSERT_FALSE(*D4_Flat > *D4);
    
}

TEST_F(IMUSANT_pitch_Tests, TestPC)
{
    ASSERT_TRUE(C4->getPC() == 0);
    ASSERT_TRUE(D4->getPC() == 2);
    ASSERT_TRUE(D4_Sharp->getPC() == 3);
    ASSERT_TRUE(D4_Flat->getPC() == 1);
    ASSERT_TRUE(B4->getPC() == 11);
}

TEST_F(IMUSANT_pitch_Tests, TestMidiKeyNumber)
{
    ASSERT_TRUE(C4->getMidiKeyNumber()==60);
    ASSERT_TRUE(B4->getMidiKeyNumber()==71);
    ASSERT_TRUE(C5->getMidiKeyNumber()==72);
    ASSERT_TRUE(D4_Sharp->getMidiKeyNumber()==63);
    ASSERT_TRUE(D4_Flat->getMidiKeyNumber()==61);
}

TEST_F(IMUSANT_pitch_Tests, TestTransposeOneOctave)
{
    S_IMUSANT_pitch pitch = CreatePitch(IMUSANT_pitch::type::C, 4, IMUSANT_pitch::natural);
    pitch->transpose(0, 0, 0, false);
    
    ASSERT_EQ(60, pitch->getMidiKeyNumber());
    
    pitch->transpose(0, 0, +1, false);
    ASSERT_EQ(72, pitch->getMidiKeyNumber()) << "Unexpected MidiKeyNumber after transposition by one octave.";
    ASSERT_EQ(IMUSANT_pitch::type::C, pitch->name()) << "Unexpected Name after transposition by one octave.";
    ASSERT_EQ(IMUSANT_pitch::inflection::natural, pitch->getInflection()) << "Unexpected Inflection after transposition by one octave.";
    ASSERT_EQ(5, pitch->octave()) << "Unexpected Octave after transposition by one octave.";
    ASSERT_EQ(IMUSANT_pitch::TPC::tpcC, pitch->getTPC()) << "Unexpected TPC after transposition by one octave.";
    ASSERT_EQ(0, pitch->getPC()) << "Unexpected PC after transposition by one octave.";
}

TEST_F(IMUSANT_pitch_Tests, TestTransposeTwoPitchSteps)
{
    S_IMUSANT_pitch pitch = CreatePitch(IMUSANT_pitch::type::C, 4, IMUSANT_pitch::natural);
    pitch->transpose(+2, +4, 0, false);
    
    ASSERT_EQ(64, pitch->getMidiKeyNumber()) << "Unexpected MidiKeyNumber after transposition.";
    ASSERT_EQ(IMUSANT_pitch::type::E, pitch->name()) << "Unexpected Name after transposition.";
    ASSERT_EQ(IMUSANT_pitch::inflection::natural, pitch->getInflection()) << "Unexpected Inflection after transposition.";
    ASSERT_EQ(4, pitch->octave()) << "Unexpected Octave after transposition.";
    ASSERT_EQ(IMUSANT_pitch::TPC::tpcE, pitch->getTPC()) << "Unexpected TPC after transposition.";
    ASSERT_EQ(4, pitch->getPC()) << "Unexpected PC after transposition.";
    
    // REVISIT - add the beelow when AsWritten is implemented() and tested.
    // ASSERT_EQ(IMUSANT_pitch::type::C,  pitch.asWritten().name()) << "Unexpected AsWritten.Name after transposition.";
}

TEST_F(IMUSANT_pitch_Tests, TestTranspose_CtoDsharp_Up)
{
    S_IMUSANT_pitch pitch = CreatePitch(IMUSANT_pitch::type::C, 4, IMUSANT_pitch::natural);
    pitch->transpose(+1, +3, 0, false);  // C to D#.
    
    ASSERT_EQ(63, pitch->getMidiKeyNumber()) << "Unexpected MidiKeyNumber after transposition.";
    ASSERT_EQ(IMUSANT_pitch::type::D, pitch->name()) << "Unexpected Name after transposition.";
    ASSERT_EQ(IMUSANT_pitch::inflection::sharp, pitch->getInflection()) << "Unexpected Inflection after transposition.";
    ASSERT_EQ(4, pitch->octave()) << "Unexpected Octave after transposition.";
    ASSERT_EQ(IMUSANT_pitch::TPC::tpcDs, pitch->getTPC()) << "Unexpected TPC after transposition.";
    ASSERT_EQ(3, pitch->getPC()) << "Unexpected PC after transposition.";
}

TEST_F(IMUSANT_pitch_Tests, TestTranspose_CtoEflat_Up)
{
    S_IMUSANT_pitch pitch = CreatePitch(IMUSANT_pitch::type::C, 4, IMUSANT_pitch::natural);
    pitch->transpose(+2, +3, 0, false);  // C to Eb.
    
    ASSERT_EQ(63, pitch->getMidiKeyNumber()) << "Unexpected MidiKeyNumber after transposition.";
    ASSERT_EQ(IMUSANT_pitch::type::E, pitch->name()) << "Unexpected Name after transposition.";
    ASSERT_EQ(IMUSANT_pitch::inflection::flat, pitch->getInflection()) << "Unexpected Inflection after transposition.";
    ASSERT_EQ(4, pitch->octave()) << "Unexpected Octave after transposition.";
    ASSERT_EQ(IMUSANT_pitch::TPC::tpcEb, pitch->getTPC()) << "Unexpected TPC after transposition.";
    ASSERT_EQ(3, pitch->getPC()) << "Unexpected PC after transposition.";
}

TEST_F(IMUSANT_pitch_Tests, TestTransposeThreeSemitonesDown)
{
    S_IMUSANT_pitch pitch = CreatePitch(IMUSANT_pitch::type::C, 4, IMUSANT_pitch::natural);
    pitch->transpose(-2, -3, -1, false);  // C to A.
    
    ASSERT_EQ(IMUSANT_pitch::type::A, pitch->name()) << "Unexpected Name after transposition.";
    ASSERT_EQ(IMUSANT_pitch::inflection::natural, pitch->getInflection()) << "Unexpected Inflection after transposition.";
    ASSERT_EQ(3, pitch->octave()) << "Unexpected Octave after transposition.";
    ASSERT_EQ(57, pitch->getMidiKeyNumber()) << "Unexpected MidiKeyNumber after transposition.";
    
}

TEST_F(IMUSANT_pitch_Tests, TestTransposeWrapEnharmonicsTable)
{
    S_IMUSANT_pitch pitch = CreatePitch(IMUSANT_pitch::type::D, 4, IMUSANT_pitch::natural);
    pitch->transpose(-1, 10, 1, false);  // D to C + 1 octave.
    
    ASSERT_EQ(IMUSANT_pitch::type::C, pitch->name()) << "Unexpected Name after transposition.";
    ASSERT_EQ(IMUSANT_pitch::inflection::natural, pitch->getInflection()) << "Unexpected Inflection after transposition.";
    ASSERT_EQ(5, pitch->octave()) << "Unexpected Octave after transposition.";
    ASSERT_EQ(72, pitch->getMidiKeyNumber()) << "Unexpected MidiKeyNumber after transposition.";
}

TEST_F(IMUSANT_pitch_Tests, TestEnharmonicsTable_AddPitchSteps)
{
    EnharmonicsTable tbl;
    
    ASSERT_EQ(IMUSANT_pitch::C, tbl.addPitchSteps(IMUSANT_pitch::type::D, -8));
    ASSERT_EQ(IMUSANT_pitch::D, tbl.addPitchSteps(IMUSANT_pitch::type::D, -7));
    ASSERT_EQ(IMUSANT_pitch::E, tbl.addPitchSteps(IMUSANT_pitch::type::D, -6));
    ASSERT_EQ(IMUSANT_pitch::F, tbl.addPitchSteps(IMUSANT_pitch::type::D, -5));
    ASSERT_EQ(IMUSANT_pitch::G, tbl.addPitchSteps(IMUSANT_pitch::type::D, -4));
    ASSERT_EQ(IMUSANT_pitch::A, tbl.addPitchSteps(IMUSANT_pitch::type::D, -3));
    ASSERT_EQ(IMUSANT_pitch::B, tbl.addPitchSteps(IMUSANT_pitch::type::D, -2));
    ASSERT_EQ(IMUSANT_pitch::C, tbl.addPitchSteps(IMUSANT_pitch::type::D, -1));
    ASSERT_EQ(IMUSANT_pitch::D, tbl.addPitchSteps(IMUSANT_pitch::type::D, 0));
    ASSERT_EQ(IMUSANT_pitch::E, tbl.addPitchSteps(IMUSANT_pitch::type::D, 1));
    ASSERT_EQ(IMUSANT_pitch::F, tbl.addPitchSteps(IMUSANT_pitch::type::D, 2));
    ASSERT_EQ(IMUSANT_pitch::G, tbl.addPitchSteps(IMUSANT_pitch::type::D, 3));
    ASSERT_EQ(IMUSANT_pitch::A, tbl.addPitchSteps(IMUSANT_pitch::type::D, 4));
    ASSERT_EQ(IMUSANT_pitch::B, tbl.addPitchSteps(IMUSANT_pitch::type::D, 5));
    ASSERT_EQ(IMUSANT_pitch::C, tbl.addPitchSteps(IMUSANT_pitch::type::D, 6));
    ASSERT_EQ(IMUSANT_pitch::D, tbl.addPitchSteps(IMUSANT_pitch::type::D, 7));
    ASSERT_EQ(IMUSANT_pitch::E, tbl.addPitchSteps(IMUSANT_pitch::type::D, 8));
    ASSERT_EQ(IMUSANT_pitch::F, tbl.addPitchSteps(IMUSANT_pitch::type::D, 9));
    ASSERT_EQ(IMUSANT_pitch::G, tbl.addPitchSteps(IMUSANT_pitch::type::D, 10));
    ASSERT_EQ(IMUSANT_pitch::A, tbl.addPitchSteps(IMUSANT_pitch::type::D, 11));
    ASSERT_EQ(IMUSANT_pitch::B, tbl.addPitchSteps(IMUSANT_pitch::type::D, 12));
    ASSERT_EQ(IMUSANT_pitch::C, tbl.addPitchSteps(IMUSANT_pitch::type::D, 13));
    ASSERT_EQ(IMUSANT_pitch::D, tbl.addPitchSteps(IMUSANT_pitch::type::D, 14));
    ASSERT_EQ(IMUSANT_pitch::E, tbl.addPitchSteps(IMUSANT_pitch::type::D, 15));
}

TEST_F(IMUSANT_pitch_Tests, TestAsWritten)
{
    ASSERT_TRUE(false) << "TEST NOT IMPLEMENTED YET";
    
//    S_IMUSANT_pitch lC4 = CreatePitch(IMUSANT_pitch::type::C, 4, IMUSANT_pitch::natural);
//    lC4->transpose(4,7,0, false);
//    
//    S_IMUSANT_pitch lC4AsWritten = lC4->asWritten();
//    ASSERT_EQ(60, lC4AsWritten->getMidiKeyNumber());
}
