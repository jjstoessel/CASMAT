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
    IMUSANT_pitch C4;
    IMUSANT_pitch D4;
    IMUSANT_pitch B3;
    IMUSANT_pitch B4;
    IMUSANT_pitch C5;
    IMUSANT_pitch D5;
    IMUSANT_pitch D4_Sharp;
    IMUSANT_pitch D4_Flat;
    
private:
    
    IMUSANT_pitch CreatePitch(IMUSANT_pitch::type note,
                              unsigned short octave,
                              IMUSANT_pitch::inflection alteration)
    {
        IMUSANT_pitch *the_pitch = new IMUSANT_pitch();
        
        the_pitch->setOctave(octave);
        the_pitch->setName(note);
        the_pitch->setAlteration(alteration);
        
        return *the_pitch;
    };
};


TEST_F(IMUSANT_pitch_Tests, TestGreaterThan)
{
    // Same note
    ASSERT_FALSE(C4 > C4);
    
    // Octaves are different
    ASSERT_TRUE(C5 > C4);
    ASSERT_TRUE(C5 > D4_Flat);
    ASSERT_FALSE(C4 > C5);
    
    // Same octave, different notes
    ASSERT_TRUE(D4 > C4);
    ASSERT_TRUE(B4 > C4);
    ASSERT_FALSE(D4 > B4);
    
    // Same octave, same note, altered
    ASSERT_TRUE(D4 > D4_Flat);
    ASSERT_TRUE(D4_Sharp > D4);
    ASSERT_TRUE(D4_Sharp > D4_Flat);
    ASSERT_FALSE(D4_Flat > D4);
    
}

TEST_F(IMUSANT_pitch_Tests, TestPC)
{
    ASSERT_TRUE(C4.getPC() == 0);
    ASSERT_TRUE(D4.getPC() == 2);
    ASSERT_TRUE(D4_Sharp.getPC() == 3);
    ASSERT_TRUE(D4_Flat.getPC() == 1);
    ASSERT_TRUE(B4.getPC() == 11);
}

TEST_F(IMUSANT_pitch_Tests, TestMidiKeyNumber)
{
    ASSERT_TRUE(C4.getMidiKeyNumber()==60);
    ASSERT_TRUE(B4.getMidiKeyNumber()==71);
    ASSERT_TRUE(C5.getMidiKeyNumber()==72);
    ASSERT_TRUE(D4_Sharp.getMidiKeyNumber()==63);
    ASSERT_TRUE(D4_Flat.getMidiKeyNumber()==61);
}
