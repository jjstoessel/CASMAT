//
//  IMUSANT_key_Tests.cpp
//  imusant
//
//  Created by Derrick Hill on 8/08/2015.
//
//

#include <stdio.h>

#include "gtest/gtest.h"

#include "libIMUSANT.h"

using namespace IMUSANT;

// The fixture for testing class IMUSANT_pitch.
class IMUSANT_key_Tests : public ::testing::Test {
    
protected:
    
    IMUSANT_key_Tests()
    {
        // You can do set-up work for each test here.
    }
    
    virtual ~IMUSANT_key_Tests()
    {
        // You can do clean-up work that doesn't throw exceptions here.
    }

};


TEST_F(IMUSANT_key_Tests, SmokeTest)
{
    IMUSANT_key *the_key = new IMUSANT_key(3, IMUSANT_key::mixolydian, 0);
   
    ASSERT_TRUE(the_key->isDefined());
    
    ASSERT_TRUE(the_key->getMode() == IMUSANT_key::mixolydian);
    the_key->setMode(IMUSANT_key::ionian);
    ASSERT_TRUE(the_key->getMode() == IMUSANT_key::ionian);
    
    ASSERT_TRUE(the_key->getFifths() == 3);
    the_key->setFifths(2);
    ASSERT_TRUE(the_key->getFifths() == 2);
    
    ASSERT_TRUE(the_key->getCancel() == 0);
    the_key->setCancel(1);
    ASSERT_TRUE(the_key->getCancel() == 1);
    
    ASSERT_TRUE(the_key->isDefined());
}

