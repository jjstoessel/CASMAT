//
//  IMUSANT_interval_Tests.cpp
//  imusant
//
//  Created by Derrick Hill on 17/12/2015.
//
//

#include <stdio.h>

#include "gtest/gtest.h"

#include "libIMUSANT.h"

using namespace IMUSANT;

// The fixture for testing class IMUSANT_interval.
class IMUSANT_interval_Tests : public ::testing::Test {
    
    
protected:
    
    IMUSANT_interval_Tests()
    {
        // You can do set-up work for each test here.
    }
    
    virtual ~IMUSANT_interval_Tests()
    {
        // You can do clean-up work that doesn't throw exceptions here.
    }
    
    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:
    
    virtual void SetUp()
    {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }
    
    virtual void TearDown()
    {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }
    
    // Objects declared here can be used by all tests.
    
    int
    calculate_pitch_interval(IMUSANT_pitch::type p1,
                             IMUSANT_pitch::type p2,
                             int octave1,
                             int octave2,
                             int alteration1 = 0,
                             int alteration2 = 0)
    {
        S_IMUSANT_pitch pitch1 = new_IMUSANT_pitch();
        S_IMUSANT_pitch pitch2 = new_IMUSANT_pitch();
        
        pitch1->set(p1, octave1, 1);
        pitch2->set(p2, octave2, 1);
        
        pitch1->setAlteration(alteration1);
        pitch2->setAlteration(alteration2);
        
        IMUSANT_interval interval = IMUSANT_interval::calculate(pitch1, pitch2);
        return interval.getInterval();
    }
    
    
    
private:
    
};

TEST_F(IMUSANT_interval_Tests, xmlinterval_string_to_enum_Test)
{
    ASSERT_EQ(IMUSANT_interval::dim1, IMUSANT_interval::xmlinterval("dim1")) ;
    ASSERT_EQ(IMUSANT_interval::perf1, IMUSANT_interval::xmlinterval("perf1")) ;
    ASSERT_EQ(IMUSANT_interval::aug1, IMUSANT_interval::xmlinterval("aug1")) ;
    ASSERT_EQ(IMUSANT_interval::dim2, IMUSANT_interval::xmlinterval("dim2")) ;
    ASSERT_EQ(IMUSANT_interval::min2, IMUSANT_interval::xmlinterval("min2")) ;
    ASSERT_EQ(IMUSANT_interval::maj2, IMUSANT_interval::xmlinterval("maj2")) ;
    ASSERT_EQ(IMUSANT_interval::aug2, IMUSANT_interval::xmlinterval("aug2")) ;
    ASSERT_EQ(IMUSANT_interval::dim3, IMUSANT_interval::xmlinterval("dim3")) ;
    ASSERT_EQ(IMUSANT_interval::min3, IMUSANT_interval::xmlinterval("min3")) ;
    ASSERT_EQ(IMUSANT_interval::maj3, IMUSANT_interval::xmlinterval("maj3")) ;
    ASSERT_EQ(IMUSANT_interval::maj3, IMUSANT_interval::xmlinterval("maj3")) ;
    ASSERT_EQ(IMUSANT_interval::aug3, IMUSANT_interval::xmlinterval("aug3")) ;
    ASSERT_EQ(IMUSANT_interval::dim4, IMUSANT_interval::xmlinterval("dim4")) ;
    ASSERT_EQ(IMUSANT_interval::per4, IMUSANT_interval::xmlinterval("per4")) ;
    ASSERT_EQ(IMUSANT_interval::aug4, IMUSANT_interval::xmlinterval("aug4")) ;
    ASSERT_EQ(IMUSANT_interval::dim5, IMUSANT_interval::xmlinterval("dim5")) ;
    ASSERT_EQ(IMUSANT_interval::per5, IMUSANT_interval::xmlinterval("per5")) ;
    ASSERT_EQ(IMUSANT_interval::aug5, IMUSANT_interval::xmlinterval("aug5")) ;
    ASSERT_EQ(IMUSANT_interval::dim6, IMUSANT_interval::xmlinterval("dim6")) ;
    ASSERT_EQ(IMUSANT_interval::min6, IMUSANT_interval::xmlinterval("min6")) ;
    ASSERT_EQ(IMUSANT_interval::maj6, IMUSANT_interval::xmlinterval("maj6")) ;
    ASSERT_EQ(IMUSANT_interval::aug6, IMUSANT_interval::xmlinterval("aug6")) ;
    ASSERT_EQ(IMUSANT_interval::dim7, IMUSANT_interval::xmlinterval("dim7")) ;
    ASSERT_EQ(IMUSANT_interval::min7, IMUSANT_interval::xmlinterval("min7")) ;
    ASSERT_EQ(IMUSANT_interval::maj7, IMUSANT_interval::xmlinterval("maj7")) ;
    ASSERT_EQ(IMUSANT_interval::aug7, IMUSANT_interval::xmlinterval("aug7")) ;
    ASSERT_EQ(IMUSANT_interval::dim8, IMUSANT_interval::xmlinterval("dim8")) ;
    ASSERT_EQ(IMUSANT_interval::octave, IMUSANT_interval::xmlinterval("octave")) ;
}

TEST_F(IMUSANT_interval_Tests, xmlinterval_enum_to_string_Test)
{
    ASSERT_EQ("dim1", IMUSANT_interval::xmlinterval(IMUSANT_interval::dim1)) ;
    ASSERT_EQ("perf1", IMUSANT_interval::xmlinterval(IMUSANT_interval::perf1)) ;
    ASSERT_EQ("aug1", IMUSANT_interval::xmlinterval(IMUSANT_interval::aug1)) ;
    ASSERT_EQ("dim2", IMUSANT_interval::xmlinterval(IMUSANT_interval::dim2)) ;
    ASSERT_EQ("min2", IMUSANT_interval::xmlinterval(IMUSANT_interval::min2)) ;
    ASSERT_EQ("maj2", IMUSANT_interval::xmlinterval(IMUSANT_interval::maj2)) ;
    ASSERT_EQ("aug2", IMUSANT_interval::xmlinterval(IMUSANT_interval::aug2)) ;
    ASSERT_EQ("dim3", IMUSANT_interval::xmlinterval(IMUSANT_interval::dim3)) ;
    ASSERT_EQ("min3", IMUSANT_interval::xmlinterval(IMUSANT_interval::min3)) ;
    ASSERT_EQ("maj3", IMUSANT_interval::xmlinterval(IMUSANT_interval::maj3)) ;
    ASSERT_EQ("aug3", IMUSANT_interval::xmlinterval(IMUSANT_interval::aug3)) ;
    ASSERT_EQ("dim4", IMUSANT_interval::xmlinterval(IMUSANT_interval::dim4)) ;
    ASSERT_EQ("per4", IMUSANT_interval::xmlinterval(IMUSANT_interval::per4)) ;
    ASSERT_EQ("aug4", IMUSANT_interval::xmlinterval(IMUSANT_interval::aug4)) ;
    ASSERT_EQ("dim5", IMUSANT_interval::xmlinterval(IMUSANT_interval::dim5)) ;
    ASSERT_EQ("per5", IMUSANT_interval::xmlinterval(IMUSANT_interval::per5)) ;
    ASSERT_EQ("aug5", IMUSANT_interval::xmlinterval(IMUSANT_interval::aug5)) ;
    ASSERT_EQ("dim6", IMUSANT_interval::xmlinterval(IMUSANT_interval::dim6)) ;
    ASSERT_EQ("min6", IMUSANT_interval::xmlinterval(IMUSANT_interval::min6)) ;
    ASSERT_EQ("maj6", IMUSANT_interval::xmlinterval(IMUSANT_interval::maj6)) ;
    ASSERT_EQ("aug6", IMUSANT_interval::xmlinterval(IMUSANT_interval::aug6)) ;
    ASSERT_EQ("dim7", IMUSANT_interval::xmlinterval(IMUSANT_interval::dim7)) ;
    ASSERT_EQ("min7", IMUSANT_interval::xmlinterval(IMUSANT_interval::min7)) ;
    ASSERT_EQ("maj7", IMUSANT_interval::xmlinterval(IMUSANT_interval::maj7)) ;
    ASSERT_EQ("aug7", IMUSANT_interval::xmlinterval(IMUSANT_interval::aug7)) ;
    ASSERT_EQ("dim8", IMUSANT_interval::xmlinterval(IMUSANT_interval::dim8)) ;
    ASSERT_EQ("octave", IMUSANT_interval::xmlinterval(IMUSANT_interval::octave)) ;
}

TEST_F(IMUSANT_interval_Tests, calculate_same_octave_Test)
{
    S_IMUSANT_pitch pitch1 = new_IMUSANT_pitch();
    S_IMUSANT_pitch pitch2 = new_IMUSANT_pitch();
    int result;
    
    result = calculate_pitch_interval(IMUSANT_pitch::A, IMUSANT_pitch::A, 3, 3);
    ASSERT_EQ(IMUSANT_interval::perf1, result);
    
    result = calculate_pitch_interval(IMUSANT_pitch::A, IMUSANT_pitch::B, 3, 3);
    ASSERT_EQ(IMUSANT_interval::maj2, result);
    
    result = calculate_pitch_interval(IMUSANT_pitch::A, IMUSANT_pitch::D, 3, 3);
    ASSERT_EQ(IMUSANT_interval::per5, result);
    
}

TEST_F(IMUSANT_interval_Tests, calculate_different_octave_Test)
{
    S_IMUSANT_pitch pitch1 = new_IMUSANT_pitch();
    S_IMUSANT_pitch pitch2 = new_IMUSANT_pitch();
    
    int result;
    
    result = calculate_pitch_interval(IMUSANT_pitch::A, IMUSANT_pitch::C, 3, 4);
    ASSERT_EQ(IMUSANT_interval::min3, result);
    
    result = calculate_pitch_interval(IMUSANT_pitch::A, IMUSANT_pitch::D, 3, 4);
    ASSERT_EQ(IMUSANT_interval::per4, result);
    
    result = calculate_pitch_interval(IMUSANT_pitch::D, IMUSANT_pitch::A, 3, 4);
    ASSERT_EQ(IMUSANT_interval::per5, result);
    
    result = calculate_pitch_interval(IMUSANT_pitch::C, IMUSANT_pitch::E, 3, 4);
    ASSERT_EQ(IMUSANT_interval::maj3, result);
    
    result = calculate_pitch_interval(IMUSANT_pitch::C, IMUSANT_pitch::E, 3, 5);
    ASSERT_EQ(IMUSANT_interval::maj3, result);
}

TEST_F(IMUSANT_interval_Tests, Calculate_Cflat_Csharp_Test)
{
    S_IMUSANT_pitch pitch1 = new_IMUSANT_pitch();
    S_IMUSANT_pitch pitch2 = new_IMUSANT_pitch();
    
    int result;
    
    //
    // The following test "fails" in the original implementation
    // because it returns a value of 2 which does not map onto any
    // of the intervalic values supported by IMUSANT_interval.  But
    // is the name for this interval?
    //
    // One implication of this is that the xml translation functions
    // don't work for what should be a legitimate value returned from
    // IMUSANT_interval::calculate().
    //
    
    // Cb to C# - no interval defined in our scheme
    result = calculate_pitch_interval(IMUSANT_pitch::C, IMUSANT_pitch::C, 3, 3, -1 , 1);
    ASSERT_EQ(IMUSANT_interval::maj2, result) << "Cb to C# - Major 2dn (?????)";
}

TEST_F(IMUSANT_interval_Tests, Calculate_C_Gsharp_Test)
{
    S_IMUSANT_pitch pitch1 = new_IMUSANT_pitch();
    S_IMUSANT_pitch pitch2 = new_IMUSANT_pitch();
    
    int result;
    
    result = calculate_pitch_interval(IMUSANT_pitch::C, IMUSANT_pitch::G, 3, 3, 0 , 1);
    ASSERT_EQ(IMUSANT_interval::aug5, result) << "C to G# - Augmented 5th";
}

TEST_F(IMUSANT_interval_Tests, Calculate_C_Gdoublesharp_Test)
{
    S_IMUSANT_pitch pitch1 = new_IMUSANT_pitch();
    S_IMUSANT_pitch pitch2 = new_IMUSANT_pitch();
    
    int result;
    
    // C to G## - Dim 6th  ??
    // What is the name for this interval??
    // If this passes I would expect the Cb to C# test to also pass.
    result = calculate_pitch_interval(IMUSANT_pitch::C, IMUSANT_pitch::G, 3, 3, 0 , 2);
    ASSERT_EQ(IMUSANT_interval::dim6, result) << "C to G## - Dim 6th  (really?)";
}

TEST_F(IMUSANT_interval_Tests, Calculate_C_Aflat_Test)
{
    S_IMUSANT_pitch pitch1 = new_IMUSANT_pitch();
    S_IMUSANT_pitch pitch2 = new_IMUSANT_pitch();
    
    int result;
    
    result = calculate_pitch_interval(IMUSANT_pitch::C, IMUSANT_pitch::A, 3, 3, 0 , -1);
    ASSERT_EQ(IMUSANT_interval::min6, result) << "C to Ab - Minor 6th";
}

TEST_F(IMUSANT_interval_Tests, Calculate_C_Adoubleflat_Test)
{
    S_IMUSANT_pitch pitch1 = new_IMUSANT_pitch();
    S_IMUSANT_pitch pitch2 = new_IMUSANT_pitch();
    
    int result;
    
    result = calculate_pitch_interval(IMUSANT_pitch::C, IMUSANT_pitch::A, 3, 3, 0 , -2);
    ASSERT_EQ(IMUSANT_interval::dim6, result) << "C to Abb - Diminished 6th";
}
