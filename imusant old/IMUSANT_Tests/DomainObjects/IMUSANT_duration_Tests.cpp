//
//  IMUSANT_duration_Tests.cpp
//  imusant
//
//  Created by Derrick Hill on 20/03/2016.
//
//

#include <stdio.h>

#include "gtest/gtest.h"

#include "libIMUSANT.h"

using namespace IMUSANT;

// The fixture for testing class IMUSANT_duration.
class IMUSANT_duration_Tests : public ::testing::Test {
    
protected:
    
    IMUSANT_duration_Tests()
    {
        // You can do set-up work for each test here.
    }
    
    virtual ~IMUSANT_duration_Tests()
    {
        // You can do clean-up work that doesn't throw exceptions here.
    }
    
};


TEST_F(IMUSANT_duration_Tests, set2)
{
    S_IMUSANT_duration duration = new_IMUSANT_duration();
    duration->set(IMUSANT_duration::semibreve, 0);
    
    ASSERT_TRUE(duration->fTimeModification == IMUSANT_duration::unmeasured);
    ASSERT_EQ(0, duration->fTimeModification.getNumerator());
    ASSERT_EQ(1, duration->fTimeModification.getDenominator());
    
    ASSERT_TRUE(duration->fNormalDuration == IMUSANT_duration::unmeasured);
    ASSERT_EQ(0, duration->fNormalDuration.getNumerator());
    ASSERT_EQ(1, duration->fNormalDuration.getDenominator());
    ASSERT_EQ(0, duration->fNormalDots);
}

TEST_F(IMUSANT_duration_Tests, set5)
{
    S_IMUSANT_duration duration = new_IMUSANT_duration();
    duration->set(IMUSANT_duration::semibreve, 3, *new TRational(3,2), *new TRational(5,6), 2);
    
    ASSERT_EQ(3, duration->fDots);
    
    ASSERT_EQ(3, duration->fTimeModification.getNumerator());
    ASSERT_EQ(2, duration->fTimeModification.getDenominator());
    
    ASSERT_EQ(5, duration->fNormalDuration.getNumerator());
    ASSERT_EQ(6, duration->fNormalDuration.getDenominator());
    ASSERT_EQ(2, duration->fNormalDots);
}

TEST_F(IMUSANT_duration_Tests, asAbsoluteNumeric)
{
    S_IMUSANT_duration duration = new_IMUSANT_duration();
    duration->set(IMUSANT_duration::semibreve, 0);
    float actual_val = duration->asAbsoluteNumeric();
    ASSERT_EQ(1024, actual_val) << "A semibreve with no modifications.";
    
    duration->set(IMUSANT_duration::semibreve, 1);
    actual_val = duration->asAbsoluteNumeric();
    ASSERT_EQ(1024 + 512, actual_val) << "A semibreve with one dot.";
    
    duration->set(IMUSANT_duration::crochet, 2);
    actual_val = duration->asAbsoluteNumeric();
    ASSERT_EQ(256 + 128 + 64, actual_val) << "A minim with two dots.";
    
    duration->set(IMUSANT_duration::oneohtwofourth , 4 );
    actual_val = duration->asAbsoluteNumeric();
    ASSERT_EQ(1 + (1 * 0.5) + (1 * 0.25) + (1 * 0.125) + (1 * 0.0625), actual_val) << "A oneohtwofourth with four dots.";
    
    duration->set(IMUSANT_duration::crochet, 0, *new TRational(3,2), IMUSANT_duration::unmeasured, 0);
    actual_val = duration->asAbsoluteNumeric();
    ASSERT_EQ((256 * 2) / (float)3, actual_val) << "A crotchet that is part of a triplet.";
    
    duration->set(IMUSANT_duration::crochet, 0, *new TRational(5,2), IMUSANT_duration::unmeasured, 0);
    actual_val = duration->asAbsoluteNumeric();
    ASSERT_EQ((256 * 2) / (float)5, actual_val) << "A crotchet that is part of five over two...";
    
    duration->set(IMUSANT_duration::crochet, 1, *new TRational(3,2), IMUSANT_duration::unmeasured, 0);
    actual_val = duration->asAbsoluteNumeric();
    ASSERT_EQ(256, actual_val) << "A dotted crotchet that is part of a triplet.";
}

// If we have two crotchets we should have 256 + 256 = 512 as the duration.
// If we have a simple triplet, do we get the right answer?
TEST_F(IMUSANT_duration_Tests, asAbsoluteNumeric_SumOfSimpleTuple)
{
    S_IMUSANT_duration crotchet1 = new_IMUSANT_duration();
    crotchet1->set(IMUSANT_duration::crochet, 0);
    float crotchet1_actual_val = crotchet1->asAbsoluteNumeric();
    
    S_IMUSANT_duration crotchet2 = new_IMUSANT_duration();
    crotchet2->set(IMUSANT_duration::crochet, 0);
    float crotchet2_actual_val = crotchet2->asAbsoluteNumeric();
    
    float sum_of_crotchets = crotchet1_actual_val + crotchet2_actual_val;
    
    S_IMUSANT_duration crotchet_in_triplet_1 = new_IMUSANT_duration();
    crotchet_in_triplet_1->set(IMUSANT_duration::crochet, 0, *new TRational(3,2), IMUSANT_duration::unmeasured, 0);
    float crotchet_in_triplet_1_actual_val = crotchet_in_triplet_1->asAbsoluteNumeric();
    
    S_IMUSANT_duration crotchet_in_triplet_2 = new_IMUSANT_duration();
    crotchet_in_triplet_2->set(IMUSANT_duration::crochet, 0, *new TRational(3,2), IMUSANT_duration::unmeasured, 0);
    float crotchet_in_triplet_2_actual_val = crotchet_in_triplet_2->asAbsoluteNumeric();
    
    S_IMUSANT_duration crotchet_in_triplet_3 = new_IMUSANT_duration();
    crotchet_in_triplet_3->set(IMUSANT_duration::crochet, 0, *new TRational(3,2), IMUSANT_duration::unmeasured, 0);
    float crotchet_in_triplet_3_actual_val = crotchet_in_triplet_3->asAbsoluteNumeric();
    
    float sum_of_tuple = crotchet_in_triplet_1_actual_val + crotchet_in_triplet_2_actual_val + crotchet_in_triplet_3_actual_val;
    
    ASSERT_EQ(sum_of_crotchets, sum_of_tuple) << "The sum of the duration for two crotchets does not equal the sum of a triplet over two crotchets. It should.";
    
}

// If we have two crotchets we should have 256 + 256 = 512 as the duration.
// If we have a triplet with a dotted crotchet in it, do we get the right answer?

TEST_F(IMUSANT_duration_Tests, asAbsoluteNumeric_SumOfTupleWithDots)
{
    S_IMUSANT_duration crotchet1 = new_IMUSANT_duration();
    crotchet1->set(IMUSANT_duration::crochet, 0);
    float crotchet1_actual_val = crotchet1->asAbsoluteNumeric();

    S_IMUSANT_duration crotchet2 = new_IMUSANT_duration();
    crotchet2->set(IMUSANT_duration::crochet, 0);
    float crotchet2_actual_val = crotchet2->asAbsoluteNumeric();
    
    float sum_of_crotchets = crotchet1_actual_val + crotchet2_actual_val;
    
    S_IMUSANT_duration crotchet_in_triplet_1 = new_IMUSANT_duration();
    crotchet_in_triplet_1->set(IMUSANT_duration::crochet, 0, *new TRational(3,2), IMUSANT_duration::unmeasured, 0);
    float crotchet_in_triplet_1_actual_val = crotchet_in_triplet_1->asAbsoluteNumeric();
    
    S_IMUSANT_duration dotted_crotchet_in_triplet_2 = new_IMUSANT_duration();
    dotted_crotchet_in_triplet_2->set(IMUSANT_duration::crochet, 1, *new TRational(3,2), IMUSANT_duration::unmeasured, 0);
    float dotted_crotchet_in_triplet_2_actual_val = dotted_crotchet_in_triplet_2->asAbsoluteNumeric();
    
    S_IMUSANT_duration quaver_in_triplet = new_IMUSANT_duration();
    quaver_in_triplet->set(IMUSANT_duration::quaver, 0, *new TRational(3,2), IMUSANT_duration::crochet, 0);
    float quaver_in_triplet_actual_val = quaver_in_triplet->asAbsoluteNumeric();
    
    float sum_of_tuple = crotchet_in_triplet_1_actual_val + dotted_crotchet_in_triplet_2_actual_val + quaver_in_triplet_actual_val;
    
    ASSERT_EQ(sum_of_crotchets, sum_of_tuple) << "The sum of the duration for two crotchets does not equal the sum of a tuple with dots over two crotchets. It should.";
}