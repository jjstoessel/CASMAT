//
//  IMUSANT_generic_interval_Test.cpp
//  
//
//  Created by Jason James Stoessel on 19/11/2016.
//
//

#include "IMUSANT_generic_interval_Test.h"

#include <stdio.h>

#include "gtest/gtest.h"

#include "libIMUSANT.h"

using namespace IMUSANT;

// The fixture for testing class IMUSANT_pitch.
class IMUSANT_generic_interval_Tests : public ::testing::Test {
    
protected:
    
    IMUSANT_generic_interval_Tests()
    {
        // You can do set-up work for each test here.
    }
    
    virtual ~IMUSANT_generic_interval_Tests()
    {
        // You can do clean-up work that doesn't throw exceptions here.
    }
    
};

TEST_F(IMUSANT_generic_interval_Tests, SmokeTest)
{
    IMUSANT_generic_interval perfect_fifth(IMUSANT_interval::per5);
    IMUSANT_generic_interval augmented_fourth(IMUSANT_interval::aug4);
    IMUSANT_generic_interval minor_third(IMUSANT_interval::min3);
    IMUSANT_generic_interval major_sixth(IMUSANT_interval::maj6);
    IMUSANT_generic_interval major_third(IMUSANT_interval::maj3);
    
    ASSERT_TRUE(perfect_fifth.getNumber()==IMUSANT_generic_interval::fifth);
    ASSERT_TRUE(augmented_fourth.getNumber()==IMUSANT_generic_interval::fourth);
    ASSERT_TRUE(minor_third.getNumber()==IMUSANT_generic_interval::third);
    ASSERT_TRUE(major_sixth.getNumber()==IMUSANT_generic_interval::sixth);
    ASSERT_TRUE(major_third.getNumber()==IMUSANT_generic_interval::third);
    ASSERT_TRUE((int)major_third==(int)minor_third);
    
}
