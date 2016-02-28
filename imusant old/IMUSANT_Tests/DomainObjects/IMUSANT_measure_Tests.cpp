//
//  IMUSANT_measure_Tests.cpp
//  imusant
//
//  Created by Derrick Hill on 27/02/2016.
//
//

#include <stdio.h>

#include "gtest/gtest.h"

#include "libIMUSANT.h"

using namespace IMUSANT;

// The fixture for testing class IMUSANT_measure.
class IMUSANT_measure_Tests : public ::testing::Test {
    
    
protected:
    
    IMUSANT_measure_Tests()
    {
        // You can do set-up work for each test here.
    }
    
    virtual ~IMUSANT_measure_Tests()
    {
        // You can do clean-up work that doesn't throw exceptions here.
    }
    
    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:
    
    virtual void SetUp()
    {
        // Code here will be called immediately after the constructor (right
        // before each test).
        m1 = CreateMeasure();
    }
    
    virtual void TearDown()
    {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }
    
    // Objects declared here can be used by all tests in this test case.
    S_IMUSANT_measure m1;
    
private:
    
    S_IMUSANT_measure CreateMeasure()
    {
        S_IMUSANT_measure the_measure = new_IMUSANT_measure();
        
        the_measure->setMeasureNum(1);
        return the_measure;
    };
};


TEST_F(IMUSANT_measure_Tests, TestBarlines)
{
    S_IMUSANT_barline b1 = new_IMUSANT_barline();
    S_IMUSANT_barline b2 = new_IMUSANT_barline();
    S_IMUSANT_barline b3 = new_IMUSANT_barline();
    S_IMUSANT_barline b4 = new_IMUSANT_barline();
    S_IMUSANT_barline b5 = new_IMUSANT_barline();
    S_IMUSANT_barline b6 = new_IMUSANT_barline();
    
    b3->setFermata(true);
    
    m1->addBarline(b1);
    m1->addBarline(b2);
    m1->addBarline(b3);
    m1->addBarline(b4);
    m1->addBarline(b5);
    m1->addBarline(b6);
    
    IMUSANT_vector<S_IMUSANT_barline> barlines = m1->barlines();
    
    ASSERT_EQ(6, barlines.size());
    
    ASSERT_FALSE(barlines[0]->hasFermata());
    ASSERT_FALSE(barlines[1]->hasFermata());
    ASSERT_TRUE(barlines[2]->hasFermata());
    ASSERT_FALSE(barlines[3]->hasFermata());
    ASSERT_FALSE(barlines[4]->hasFermata());
    ASSERT_FALSE(barlines[5]->hasFermata());
}
