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


TEST_F(IMUSANT_duration_Tests, Duration_DefaultInitialisation)
{
    S_IMUSANT_duration duration = new_IMUSANT_duration();
    duration->set(IMUSANT_duration::semibreve, 0);
    
    ASSERT_TRUE(duration->fTimeModification == TRational(1,1));
    ASSERT_EQ(1, duration->fTimeModification.getNumerator());
    ASSERT_EQ(1, duration->fTimeModification.getDenominator());
    
    ASSERT_TRUE(duration->fNormalDuration == IMUSANT_duration::semibreve);
    ASSERT_EQ(1, duration->fNormalDuration.getNumerator());
    ASSERT_EQ(1, duration->fNormalDuration.getDenominator());
    ASSERT_EQ(0, duration->fNormalDots);
}

TEST_F(IMUSANT_duration_Tests, Duration_Initialisation)
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

TEST_F(IMUSANT_duration_Tests, Duration_asAbsoluteNumeric)
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

TEST_F(IMUSANT_duration_Tests, Duration_additionOperator_TwoCrotchets)
{
    S_IMUSANT_duration crotchet1 = new_IMUSANT_duration();
    crotchet1->set(IMUSANT_duration::crochet, 0);
    
    S_IMUSANT_duration crotchet2 = new_IMUSANT_duration();
    crotchet2->set(IMUSANT_duration::crochet, 0);
    
    IMUSANT_duration sum = *crotchet1 + *crotchet2;
    
    ASSERT_EQ(1, sum.fDuration.getNumerator());
    ASSERT_EQ(2, sum.fDuration.getDenominator());
    ASSERT_EQ(1, sum.fTimeModification.getNumerator());
    ASSERT_EQ(1, sum.fTimeModification.getDenominator());
    ASSERT_EQ(0, sum.fNormalDuration.getNumerator());
    ASSERT_EQ(1, sum.fNormalDuration.getDenominator());
    ASSERT_EQ(0, sum.fNormalDots);
    ASSERT_EQ(0, sum.fDots);
}

TEST_F(IMUSANT_duration_Tests, Duration_additionOperator_MixedNoteValues)
{
    S_IMUSANT_duration crotchet1 = new_IMUSANT_duration();
    crotchet1->set(IMUSANT_duration::crochet, 0);
    
    S_IMUSANT_duration crotchet2 = new_IMUSANT_duration();
    crotchet2->set(IMUSANT_duration::crochet, 0);
    
    S_IMUSANT_duration quaver1 = new_IMUSANT_duration();
    quaver1->set(IMUSANT_duration::quaver, 0);
    
    S_IMUSANT_duration semibreve1 = new_IMUSANT_duration();
    semibreve1->set(IMUSANT_duration::semibreve, 0);
    
    IMUSANT_duration sum = *crotchet1 + *crotchet2 + *quaver1 + *semibreve1;
    
    ASSERT_EQ(13, sum.fDuration.getNumerator());
    ASSERT_EQ(8, sum.fDuration.getDenominator());
    ASSERT_EQ(1, sum.fTimeModification.getNumerator());
    ASSERT_EQ(1, sum.fTimeModification.getDenominator());
    ASSERT_EQ(0, sum.fNormalDuration.getNumerator());
    ASSERT_EQ(1, sum.fNormalDuration.getDenominator());
    ASSERT_EQ(0, sum.fNormalDots);
    ASSERT_EQ(0, sum.fDots);
}

TEST_F(IMUSANT_duration_Tests, Duration_additionOperator_WithDots)
{
    S_IMUSANT_duration crotchet1 = new_IMUSANT_duration();
    crotchet1->set(IMUSANT_duration::crochet, 1);
    
    S_IMUSANT_duration crotchet2 = new_IMUSANT_duration();
    crotchet2->set(IMUSANT_duration::crochet, 2);
    
    S_IMUSANT_duration quaver1 = new_IMUSANT_duration();
    quaver1->set(IMUSANT_duration::quaver, 0);
    
    S_IMUSANT_duration semibreve1 = new_IMUSANT_duration();
    semibreve1->set(IMUSANT_duration::semibreve, 1);
    
    IMUSANT_duration sum = *crotchet1 + *crotchet2 + *quaver1 + *semibreve1;
    
    ASSERT_EQ(39, sum.fDuration.getNumerator());
    ASSERT_EQ(16, sum.fDuration.getDenominator());
    ASSERT_EQ(1, sum.fTimeModification.getNumerator());
    ASSERT_EQ(1, sum.fTimeModification.getDenominator());
    ASSERT_EQ(0, sum.fNormalDuration.getNumerator());
    ASSERT_EQ(1, sum.fNormalDuration.getDenominator());
    ASSERT_EQ(0, sum.fNormalDots);
    ASSERT_EQ(0, sum.fDots);
}

TEST_F(IMUSANT_duration_Tests, Duration_additionOperator_WithTimeMod)
{
    S_IMUSANT_duration crochet1 = new_IMUSANT_duration();
    S_IMUSANT_duration crochet2 = new_IMUSANT_duration();
    S_IMUSANT_duration crochet3 = new_IMUSANT_duration();
    
    crochet1->set(IMUSANT_duration::crochet, 0, TRational(3,2), IMUSANT_duration::unmeasured, 0);
    crochet2->set(IMUSANT_duration::crochet, 0, TRational(3,2), IMUSANT_duration::unmeasured, 0);
    crochet3->set(IMUSANT_duration::crochet, 0, TRational(3,2), IMUSANT_duration::unmeasured, 0);

    IMUSANT_duration sum = *crochet1 + *crochet1 + *crochet1;
    
    ASSERT_EQ(1, sum.fDuration.getNumerator());
    ASSERT_EQ(2, sum.fDuration.getDenominator());
    ASSERT_EQ(1, sum.fTimeModification.getNumerator());
    ASSERT_EQ(1, sum.fTimeModification.getDenominator());
    ASSERT_EQ(0, sum.fNormalDuration.getNumerator());
    ASSERT_EQ(1, sum.fNormalDuration.getDenominator());
    ASSERT_EQ(0, sum.fNormalDots);
    ASSERT_EQ(0, sum.fDots);
}

TEST_F(IMUSANT_duration_Tests, Duration_CompoundAssignmentOperator)
{
    S_IMUSANT_duration crotchet1 = new_IMUSANT_duration();
    crotchet1->set(IMUSANT_duration::crochet, 0);
    
    S_IMUSANT_duration crotchet2 = new_IMUSANT_duration();
    crotchet2->set(IMUSANT_duration::crochet, 0);
    
    *crotchet1 += *crotchet2;
    
    ASSERT_EQ(1, crotchet1->fDuration.getNumerator());
    ASSERT_EQ(2, crotchet1->fDuration.getDenominator());
    ASSERT_EQ(1, crotchet1->fTimeModification.getNumerator());
    ASSERT_EQ(1, crotchet1->fTimeModification.getDenominator());
    ASSERT_EQ(1, crotchet1->fNormalDuration.getNumerator());   // << FAILING HERE...
    ASSERT_EQ(2, crotchet1->fNormalDuration.getDenominator());
    ASSERT_EQ(0, crotchet1->fNormalDots);
    ASSERT_EQ(0, crotchet1->fDots);
    
}

TEST_F(IMUSANT_duration_Tests, Duration_NormaliseDuration)
{
    S_IMUSANT_duration dur = new_IMUSANT_duration();
    long num_dots = 0;
    
    dur->fDuration = TRational(3, 4);
    num_dots = IMUSANT_duration::NormaliseDuration(dur->fDuration);
    
    ASSERT_EQ(1, num_dots);
    ASSERT_EQ(1, dur->fDuration.getNumerator());
    ASSERT_EQ(2, dur->fDuration.getDenominator());
    ASSERT_TRUE(IMUSANT_duration::minim == dur->fDuration);
    
    dur->fDuration = TRational(7, 8);
    num_dots = IMUSANT_duration::NormaliseDuration(dur->fDuration);
    
    ASSERT_EQ(2, num_dots);
    ASSERT_EQ(1, dur->fDuration.getNumerator());
    ASSERT_EQ(2, dur->fDuration.getDenominator());
    ASSERT_TRUE(IMUSANT_duration::minim == dur->fDuration);
    
    dur->fDuration = TRational(15, 16);
    num_dots = IMUSANT_duration::NormaliseDuration(dur->fDuration);
    
    ASSERT_EQ(3, num_dots);
    ASSERT_EQ(1, dur->fDuration.getNumerator());
    ASSERT_EQ(2, dur->fDuration.getDenominator());
    ASSERT_TRUE(IMUSANT_duration::minim == dur->fDuration);
    
    dur->fDuration = TRational(6, 4);
    num_dots = IMUSANT_duration::NormaliseDuration(dur->fDuration);
    
    ASSERT_EQ(1, num_dots);
    ASSERT_EQ(1, dur->fDuration.getNumerator());
    ASSERT_EQ(1, dur->fDuration.getDenominator());
    ASSERT_TRUE(IMUSANT_duration::semibreve == dur->fDuration);
}

TEST_F(IMUSANT_duration_Tests, Duration_GetSimplifiedDuration_SixOverFour)
{
    // A duration of 6/4 simplifies to 3/2, which is a dotted semibreve.
    
    S_IMUSANT_duration dur = new_IMUSANT_duration();
    S_IMUSANT_duration simplified_dur = new_IMUSANT_duration();

    dur->fDuration = TRational(6, 4);

    *simplified_dur = dur->getSimplifiedDuration();
    
    ASSERT_EQ(1, simplified_dur->fDuration.getNumerator());
    ASSERT_EQ(1, simplified_dur->fDuration.getDenominator());
    ASSERT_TRUE(IMUSANT_duration::semibreve == simplified_dur->fDuration);
    ASSERT_EQ(1, simplified_dur->fDots);
    
}

TEST_F(IMUSANT_duration_Tests, Duration_GetSimplifiedDuration_SevenOverEight)
{
    // A duration of 7/8 simplifies to a double dotted minim
    
    S_IMUSANT_duration dur = new_IMUSANT_duration();
    S_IMUSANT_duration simplified_dur = new_IMUSANT_duration();
    
    dur->fDuration = TRational(7, 8);
    
    *simplified_dur = dur->getSimplifiedDuration();
    
    ASSERT_EQ(1, simplified_dur->fDuration.getNumerator());
    ASSERT_EQ(2, simplified_dur->fDuration.getDenominator());
    ASSERT_TRUE(IMUSANT_duration::minim == simplified_dur->fDuration);
    ASSERT_EQ(2, simplified_dur->fDots);
}

TEST_F(IMUSANT_duration_Tests, Duration_Set_SixOnFour_OneDot)
{
    //
    // The logic is as follows:
    //
    // dur = 6/4 with one dot
    //     = 6/4 + 3/4
    //     = 9/4
    //
    // BUT
    //
    // set() is giving me
    //     (6/4) with one dot
    //   = (4/4 with 1 dot) with one dot
    //   = 4/4 with two dots
    //   = 4/4 + 2/4 + 1/4
    //   = 7/4
    //
    // THIS IS WRONG because 7/4 != 9/4
    //
    
    S_IMUSANT_duration dur = new_IMUSANT_duration();
    dur->set(TRational(6,4), 1);
   
    ASSERT_EQ(9, dur->fDuration.getNumerator()) << "IMUSANT_duration::set() is WRONG in the simplification of dots...";
    ASSERT_EQ(4, dur->fDuration.getDenominator());
    ASSERT_EQ(0, dur->fDots);
}

TEST_F(IMUSANT_duration_Tests, Duration_GetSimplifiedDuration_WithTimeMod)
{
    // The logic is as follows:
    
    // dur = 6/4 with one dot
    //     = 6/4 + 3/4
    //     = 9/4
    //
    // timemod = 3/2
    //
    // simplified_dur = dur / timemod
    //                = 9/4 / 3/2
    //                = 9/4 * 2/3
    //                = 18/12
    //                = 1 1/2
    // which is semibreve with one dot.
    
    S_IMUSANT_duration dur = new_IMUSANT_duration();
    S_IMUSANT_duration simplified_dur = new_IMUSANT_duration();
    
    dur->set(TRational(6,4), 1, TRational(3,2), IMUSANT_duration::unmeasured, 0);
    
    *simplified_dur = dur->getSimplifiedDuration();
    
    ASSERT_EQ(1, simplified_dur->fDuration.getNumerator()) << "IMUSANT_duration::set() is WRONG in the simplification of dots...";
    ASSERT_EQ(1, simplified_dur->fDuration.getDenominator());
    ASSERT_TRUE(IMUSANT_duration::semibreve == simplified_dur->fDuration);
    ASSERT_EQ(1, simplified_dur->fDots);
}

TEST_F(IMUSANT_duration_Tests, Duration_additionOperator_equalityOperator_WithTimeMod)
{
    S_IMUSANT_duration crotchet_in_triplet_1 = new_IMUSANT_duration();
    crotchet_in_triplet_1->set(IMUSANT_duration::crochet, 0, *new TRational(3,2), IMUSANT_duration::unmeasured, 0);
    
    S_IMUSANT_duration crotchet_in_triplet_2 = new_IMUSANT_duration();
    crotchet_in_triplet_2->set(IMUSANT_duration::crochet, 0, *new TRational(3,2), IMUSANT_duration::unmeasured, 0);
    
    S_IMUSANT_duration crotchet_in_triplet_3 = new_IMUSANT_duration();
    crotchet_in_triplet_3->set(IMUSANT_duration::crochet, 0, *new TRational(3,2), IMUSANT_duration::unmeasured, 0);
    
    S_IMUSANT_duration crotchet1 = new_IMUSANT_duration();
    crotchet1->set(IMUSANT_duration::crochet, 0);
    
    S_IMUSANT_duration crotchet2 = new_IMUSANT_duration();
    crotchet2->set(IMUSANT_duration::crochet, 0);
    
    IMUSANT_duration sum = *crotchet_in_triplet_1 + *crotchet_in_triplet_2 + *crotchet_in_triplet_3 + *crotchet1 + *crotchet2;
    
    ASSERT_EQ(1, sum.fDuration.getNumerator());
    ASSERT_EQ(1, sum.fDuration.getDenominator());
    ASSERT_EQ(1, sum.fTimeModification.getNumerator());
    ASSERT_EQ(1, sum.fTimeModification.getDenominator());
    ASSERT_EQ(0, sum.fNormalDuration.getNumerator());
    ASSERT_EQ(1, sum.fNormalDuration.getDenominator());
    ASSERT_EQ(0, sum.fNormalDots);
    ASSERT_EQ(0, sum.fDots);
    
    S_IMUSANT_duration comparison = new_IMUSANT_duration();
    comparison->fDuration.setNumerator(1);
    comparison->fDuration.setDenominator(1);
    comparison->fTimeModification.setNumerator(1);
    comparison->fTimeModification.setDenominator(1);
    comparison->fNormalDuration.setNumerator(0);
    comparison->fNormalDuration.setDenominator(0);
    comparison->fNormalDots = 0;
    comparison->fDots = 0;
    
    ASSERT_TRUE(sum == *comparison);
}

TEST_F(IMUSANT_duration_Tests, Duration_equalityOperator)
{
    S_IMUSANT_duration lhs = new_IMUSANT_duration();
    lhs->set(IMUSANT_duration::crochet, 1, *new TRational(3,2), IMUSANT_duration::unmeasured, 256);
    
    S_IMUSANT_duration rhs = new_IMUSANT_duration();
    rhs->set(IMUSANT_duration::crochet, 1, *new TRational(3,2), IMUSANT_duration::unmeasured, 256);
    
    S_IMUSANT_duration neq1 = new_IMUSANT_duration();
    neq1->set(IMUSANT_duration::quaver, 1, *new TRational(3,2), IMUSANT_duration::unmeasured, 256);
    
    S_IMUSANT_duration neq2 = new_IMUSANT_duration();
    neq2->set(IMUSANT_duration::crochet, 0, *new TRational(3,2), IMUSANT_duration::unmeasured, 256);
    
    S_IMUSANT_duration neq3 = new_IMUSANT_duration();
    neq3->set(IMUSANT_duration::crochet, 1, *new TRational(2,2), IMUSANT_duration::unmeasured, 256);
    
    //
    // We are not handling the MusicXML normal-type and normal-dots elements properly at the moment.
    // See D-01024 - IMUSANT_duration does not handle dotted notes in tuplets (not handling XML normal-type attribute).
    //
    // S_IMUSANT_duration neq4 = new_IMUSANT_duration();
    // neq4->set(IMUSANT_duration::crochet, 1, *new TRational(3,2), IMUSANT_duration::breve, 256);
    //
    
    ASSERT_TRUE(*lhs == *rhs);
    ASSERT_FALSE(*lhs != *rhs);
    
    ASSERT_FALSE(*lhs == *neq1);
    ASSERT_FALSE(*lhs == *neq2);
    ASSERT_FALSE(*lhs == *neq3);
    
    ASSERT_TRUE(*lhs != *neq1);
    ASSERT_TRUE(*lhs != *neq2);
    ASSERT_TRUE(*lhs != *neq3);
    
    // ASSERT_FALSE(*lhs == *neq4);
}

TEST_F(IMUSANT_duration_Tests, Duration_equalityOperator_SameButDifferent)
{
    S_IMUSANT_duration n1 = new_IMUSANT_duration();
    n1->set(IMUSANT_duration::crochet, 0);
    
    S_IMUSANT_duration n2 = new_IMUSANT_duration();
    n2->set(IMUSANT_duration::quaver, 0);
    n2->fDuration.setNumerator(2);
    n2->fDuration.setDenominator(8);
    
    ASSERT_TRUE(*n1 == *n2);
}


// If we have two crotchets we should have 256 + 256 = 512 as the duration.
// If we have a simple triplet, do we get the right answer?
TEST_F(IMUSANT_duration_Tests, Duration_asAbsoluteNumeric_SumOfSimpleTuple)
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

TEST_F(IMUSANT_duration_Tests, Duration_asAbsoluteNumeric_SumOfTupleWithDots)
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

