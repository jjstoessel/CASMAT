//
//  IMUSANT_score_Tests.cpp
//  imusant
//
//  Created by Derrick Hill on 27/09/2015.
//
//

#include <stdio.h>

#include "gtest/gtest.h"

#include "libIMUSANT.h"

using namespace IMUSANT;

// The fixture for testing class IMUSANT_score.
class IMUSANT_score_Tests : public ::testing::Test {
    
    
protected:
    
    IMUSANT_score_Tests()
    {
        // You can do set-up work for each test here.
    }
    
    virtual ~IMUSANT_score_Tests()
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
    
    // Objects declared here can be used by all tests in the test case for CATSMAT_cp_matrix_Test.


    S_IMUSANT_part CreatePart(string part_id, string part_name, S_IMUSANT_score the_score);
    
private:
    
};

S_IMUSANT_part
IMUSANT_score_Tests::
CreatePart(string part_id, string part_name, S_IMUSANT_score the_score)
{
    S_IMUSANT_part new_part = new_IMUSANT_part();
    new_part->setID(part_id);
    new_part->setPartName(part_name);
    
    the_score->addPart(new_part);
    
    return new_part;
};


TEST_F(IMUSANT_score_Tests, TestGetPartById)
{
    S_IMUSANT_score the_score = new_IMUSANT_score();
    
    S_IMUSANT_part part1 = CreatePart("p1", "Part 1", the_score);
    S_IMUSANT_part part2 = CreatePart("p2", "Part 2", the_score);
    S_IMUSANT_part part3 = CreatePart("p3", "Part 3", the_score);
    S_IMUSANT_part part4 = CreatePart("p4", "Part 4", the_score);
    
    S_IMUSANT_part retrieved_part;
    
    if (the_score->getPartById("p1", retrieved_part))
    {
        ASSERT_EQ("p1", retrieved_part->getID());
    }
    
    if (the_score->getPartById("p2", retrieved_part))
    {
        ASSERT_EQ("p2", retrieved_part->getID());
    }
    
    if (the_score->getPartById("p3", retrieved_part))
    {
        ASSERT_EQ("p3", retrieved_part->getID());
    }
    
    if (the_score->getPartById("p4", retrieved_part))
    {
        ASSERT_EQ("p4", retrieved_part->getID());
    }
    
    if (the_score->getPartById("This Part Does Not Exist", retrieved_part))
    {
        ASSERT_FALSE(true) << "Found a part that does not exist.";
    }
}
