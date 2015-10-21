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

TEST_F(IMUSANT_key_Tests, xmlmodeTest)
{
    // This test fails. BUG D-01012 raised in VersionOne.
    IMUSANT_key *the_key = new IMUSANT_key(3, IMUSANT_key::mixolydian, 0);
    
    the_key->setMode(the_key->xmlmode("generic"));
    ASSERT_TRUE(the_key->getMode() == IMUSANT_key::generic);
    
    the_key->setMode(the_key->xmlmode("dorian"));
    ASSERT_TRUE(the_key->getMode() == IMUSANT_key::dorian);
    
    the_key->setMode(the_key->xmlmode("hypodorian"));
    ASSERT_TRUE(the_key->getMode() == IMUSANT_key::hypodorian);
    
    the_key->setMode(the_key->xmlmode("phrygian"));
    ASSERT_TRUE(the_key->getMode() == IMUSANT_key::phrygian);
    
    the_key->setMode(the_key->xmlmode("hypophrygian"));
    ASSERT_TRUE(the_key->getMode() == IMUSANT_key::hypophrygian);
    
    the_key->setMode(the_key->xmlmode("lydian"));
    ASSERT_TRUE(the_key->getMode() == IMUSANT_key::lydian);
    
    the_key->setMode(the_key->xmlmode("hypolydian"));
    ASSERT_TRUE(the_key->getMode() == IMUSANT_key::hypolydian);
    
    the_key->setMode(the_key->xmlmode("mixolydian"));
    ASSERT_TRUE(the_key->getMode() == IMUSANT_key::mixolydian);
    
    the_key->setMode(the_key->xmlmode("hypomixolydian"));
    ASSERT_TRUE(the_key->getMode() == IMUSANT_key::hypomixolydian);
    
    the_key->setMode(the_key->xmlmode("aeolian"));
    ASSERT_TRUE(the_key->getMode() == IMUSANT_key::aeolian);
    
    the_key->setMode(the_key->xmlmode("locrian"));
    ASSERT_TRUE(the_key->getMode() == IMUSANT_key::locrian);
    
    the_key->setMode(the_key->xmlmode("ionian"));
    ASSERT_TRUE(the_key->getMode() == IMUSANT_key::ionian);
    
    the_key->setMode(the_key->xmlmode("major"));
    ASSERT_TRUE(the_key->getMode() == IMUSANT_key::major);
    
    the_key->setMode(the_key->xmlmode("minor"));
    ASSERT_TRUE(the_key->getMode() == IMUSANT_key::minor) << "This test fails. BUG D-01012 raised in VersionOne";
}


