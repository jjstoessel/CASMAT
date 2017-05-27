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

TEST_F(IMUSANT_key_Tests, xmlmode_String2ModeTest)
{
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
    ASSERT_TRUE(the_key->getMode() == IMUSANT_key::minor);
    
    bool expected_exception_thrown = false;
    try
    {
        the_key->xmlmode("this is not a mode and we expect an exception");
    }
    catch (string e)
    {
        expected_exception_thrown = true;
    }
    ASSERT_TRUE(expected_exception_thrown);
}

TEST_F(IMUSANT_key_Tests, xmlmode_Mode2StringTest)
{
    IMUSANT_key *the_key = new IMUSANT_key(3, IMUSANT_key::mixolydian, 0);
    
    string the_mode;
    
    the_mode = the_key->xmlmode(IMUSANT_key::generic);
    ASSERT_EQ("generic" , the_mode);
    
    the_mode = the_key->xmlmode(IMUSANT_key::dorian);
    ASSERT_EQ("dorian" , the_mode);
    
    the_mode = the_key->xmlmode(IMUSANT_key::hypodorian);
    ASSERT_EQ("hypodorian" , the_mode);
    
    the_mode = the_key->xmlmode(IMUSANT_key::phrygian);
    ASSERT_EQ("phrygian" , the_mode);
    
    the_mode = the_key->xmlmode(IMUSANT_key::hypophrygian);
    ASSERT_EQ("hypophrygian" , the_mode);
    
    the_mode = the_key->xmlmode(IMUSANT_key::lydian);
    ASSERT_EQ("lydian" , the_mode);
    
    the_mode = the_key->xmlmode(IMUSANT_key::hypolydian);
    ASSERT_EQ("hypolydian" , the_mode);
    
    the_mode = the_key->xmlmode(IMUSANT_key::mixolydian);
    ASSERT_EQ("mixolydian" , the_mode);
    
    the_mode = the_key->xmlmode(IMUSANT_key::hypomixolydian);
    ASSERT_EQ("hypomixolydian" , the_mode);
    
    the_mode = the_key->xmlmode(IMUSANT_key::aeolian);
    ASSERT_EQ("aeolian" , the_mode);
    
    the_mode = the_key->xmlmode(IMUSANT_key::locrian);
    ASSERT_EQ("locrian" , the_mode);
    
    the_mode = the_key->xmlmode(IMUSANT_key::ionian);
    ASSERT_EQ("ionian" , the_mode);
    
    the_mode = the_key->xmlmode(IMUSANT_key::major);
    ASSERT_EQ("major" , the_mode);
    
    the_mode = the_key->xmlmode(IMUSANT_key::minor);
    ASSERT_EQ("minor" , the_mode);
}


