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
    
    ASSERT_TRUE(duration->time_modification() == TRational(1,1));
    ASSERT_EQ(1, duration->time_modification().getNumerator());
    ASSERT_EQ(1, duration->time_modification().getDenominator());
    
    ASSERT_TRUE(duration->normal_duration() == IMUSANT_duration::semibreve);
    ASSERT_EQ(1, duration->normal_duration().getNumerator());
    ASSERT_EQ(1, duration->normal_duration().getDenominator());
    ASSERT_EQ(0, duration->normal_dots());
}

TEST_F(IMUSANT_duration_Tests, Duration_Initialisation)
{
    S_IMUSANT_duration duration = new_IMUSANT_duration();
    duration->set(IMUSANT_duration::semibreve, 3, *new TRational(3,2), *new TRational(5,6), 2);
    
    ASSERT_EQ(3, duration->dots());
    
    ASSERT_EQ(3, duration->time_modification().getNumerator());
    ASSERT_EQ(2, duration->time_modification().getDenominator());
    
    ASSERT_EQ(5, duration->normal_duration().getNumerator());
    ASSERT_EQ(6, duration->normal_duration().getDenominator());
    ASSERT_EQ(2, duration->normal_dots());
}

TEST_F(IMUSANT_duration_Tests, Duration_ConstructionFromTRational)
{
    IMUSANT_duration durationA(IMUSANT_duration::breve);
    S_IMUSANT_duration durationB = new_IMUSANT_duration(IMUSANT_duration::breve);
    
    ASSERT_TRUE(durationA == IMUSANT_duration::breve);
    ASSERT_TRUE(*durationB == IMUSANT_duration::breve);
    ASSERT_TRUE(durationA == *durationB);
    
    IMUSANT_duration duration2(TRational(3,16));    // Hardcoded initialisation to dotted quaver with implicit dot...
    IMUSANT_duration duration3;
    duration3.set(TRational(1,8), 1);               // Initialisation to dotted quaver, with explicit dot
    
    ASSERT_EQ(duration2, duration3);                // implicit and explicit versions are the same...
                               
}

TEST_F(IMUSANT_duration_Tests, Duration_asAbsoluteNumeric)
{
    S_IMUSANT_duration duration = new_IMUSANT_duration();
    duration->set(IMUSANT_duration::semibreve, 0);
    float actual_val = duration->AsAbsoluteNumeric();
    ASSERT_EQ(1024, actual_val) << "A semibreve with no modifications.";
    
    duration->set(IMUSANT_duration::semibreve, 1);
    actual_val = duration->AsAbsoluteNumeric();
    ASSERT_EQ(1024 + 512, actual_val) << "A semibreve with one dot.";
    
    duration->set(IMUSANT_duration::crochet, 2);
    actual_val = duration->AsAbsoluteNumeric();
    ASSERT_EQ(256 + 128 + 64, actual_val) << "A minim with two dots.";
    
    duration->set(IMUSANT_duration::oneohtwofourth , 4 );
    actual_val = duration->AsAbsoluteNumeric();
    ASSERT_EQ(1 + (1 * 0.5) + (1 * 0.25) + (1 * 0.125) + (1 * 0.0625), actual_val) << "A oneohtwofourth with four dots.";
    
    duration->set(IMUSANT_duration::crochet, 0, *new TRational(3,2), IMUSANT_duration::unmeasured, 0);
    actual_val = duration->AsAbsoluteNumeric();
    ASSERT_EQ((256 * 2) / (float)3, actual_val) << "A crotchet that is part of a triplet.";
    
    duration->set(IMUSANT_duration::crochet, 0, *new TRational(5,2), IMUSANT_duration::unmeasured, 0);
    actual_val = duration->AsAbsoluteNumeric();
    ASSERT_EQ((256 * 2) / (float)5, actual_val) << "A crotchet that is part of five over two...";
    
    duration->set(IMUSANT_duration::crochet, 1, *new TRational(3,2), IMUSANT_duration::unmeasured, 0);
    actual_val = duration->AsAbsoluteNumeric();
    ASSERT_EQ(256, actual_val) << "A dotted crotchet that is part of a triplet.";
}

TEST_F(IMUSANT_duration_Tests, Duration_additionOperator_TwoCrotchets)
{
    S_IMUSANT_duration crotchet1 = new_IMUSANT_duration();
    crotchet1->set(IMUSANT_duration::crochet, 0);
    
    S_IMUSANT_duration crotchet2 = new_IMUSANT_duration();
    crotchet2->set(IMUSANT_duration::crochet, 0);
    
    IMUSANT_duration sum = *crotchet1 + *crotchet2;
    
    ASSERT_EQ(1, sum.duration().getNumerator());
    ASSERT_EQ(2, sum.duration().getDenominator());
    ASSERT_EQ(1, sum.time_modification().getNumerator());
    ASSERT_EQ(1, sum.time_modification().getDenominator());
    ASSERT_EQ(1, sum.normal_duration().getNumerator());
    ASSERT_EQ(2, sum.normal_duration().getDenominator());
    ASSERT_EQ(0, sum.normal_dots());
    ASSERT_EQ(0, sum.dots());
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
    
    ASSERT_EQ(13, sum.duration().getNumerator());
    ASSERT_EQ(8, sum.duration().getDenominator());
    ASSERT_EQ(1, sum.time_modification().getNumerator());
    ASSERT_EQ(1, sum.time_modification().getDenominator());
    ASSERT_EQ(13, sum.normal_duration().getNumerator());
    ASSERT_EQ(8, sum.normal_duration().getDenominator());
    ASSERT_EQ(0, sum.normal_dots());
    ASSERT_EQ(0, sum.dots());
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
    
    ASSERT_EQ(39, sum.duration().getNumerator());
    ASSERT_EQ(16, sum.duration().getDenominator());
    ASSERT_EQ(1, sum.time_modification().getNumerator());
    ASSERT_EQ(1, sum.time_modification().getDenominator());
    ASSERT_EQ(39, sum.normal_duration().getNumerator());
    ASSERT_EQ(16, sum.normal_duration().getDenominator());
    ASSERT_EQ(0, sum.normal_dots());
    ASSERT_EQ(0, sum.dots());
}

TEST_F(IMUSANT_duration_Tests, Duration_additionOperator_WithTimeMod)
{
    S_IMUSANT_duration crochet1 = new_IMUSANT_duration();
    S_IMUSANT_duration crochet2 = new_IMUSANT_duration();
    S_IMUSANT_duration crochet3 = new_IMUSANT_duration();
    
    crochet1->set(IMUSANT_duration::crochet, 0, TRational(3,2), IMUSANT_duration::crochet, 0);
    crochet2->set(IMUSANT_duration::crochet, 0, TRational(3,2), IMUSANT_duration::crochet, 0);
    crochet3->set(IMUSANT_duration::crochet, 0, TRational(3,2), IMUSANT_duration::crochet, 0);

    IMUSANT_duration sum = *crochet1 + *crochet1 + *crochet1;
    
    ASSERT_EQ(1, sum.duration().getNumerator());
    ASSERT_EQ(2, sum.duration().getDenominator());
    ASSERT_EQ(1, sum.time_modification().getNumerator());
    ASSERT_EQ(1, sum.time_modification().getDenominator());
    ASSERT_EQ(1, sum.normal_duration().getNumerator());
    ASSERT_EQ(2, sum.normal_duration().getDenominator());
    ASSERT_EQ(0, sum.normal_dots());
    ASSERT_EQ(0, sum.dots());
}

TEST_F(IMUSANT_duration_Tests, Duration_AssignmentOperator)
{
    S_IMUSANT_duration dur1 = new_IMUSANT_duration();
    dur1->set(IMUSANT_duration::crochet, 2);
    
    S_IMUSANT_duration dur2 = new_IMUSANT_duration();
    dur2->set(IMUSANT_duration::quaver, 1, TRational(3,2), IMUSANT_duration::unmeasured, 0);
    
    *dur1 = *dur2;
    
    ASSERT_EQ(1, dur1->duration().getNumerator());
    ASSERT_EQ(8, dur1->duration().getDenominator());
    ASSERT_EQ(3, dur1->time_modification().getNumerator());
    ASSERT_EQ(2, dur1->time_modification().getDenominator());
    ASSERT_EQ(0, dur1->normal_dots());
    ASSERT_EQ(1, dur1->dots());
    
    ASSERT_TRUE(*dur1 == *dur2);
}


TEST_F(IMUSANT_duration_Tests, Duration_CompoundAssignmentOperator)
{
    S_IMUSANT_duration crotchet1 = new_IMUSANT_duration();
    crotchet1->set(IMUSANT_duration::crochet, 0);
    
    S_IMUSANT_duration crotchet2 = new_IMUSANT_duration();
    crotchet2->set(IMUSANT_duration::crochet, 0);
    
    *crotchet1 += *crotchet2;
    
    ASSERT_EQ(1, crotchet1->duration().getNumerator());
    ASSERT_EQ(2, crotchet1->duration().getDenominator());
    ASSERT_EQ(1, crotchet1->time_modification().getNumerator());
    ASSERT_EQ(1, crotchet1->time_modification().getDenominator());
    ASSERT_TRUE(crotchet1->normal_duration() == IMUSANT_duration::minim);
    ASSERT_EQ(0, crotchet1->normal_dots());
    ASSERT_EQ(0, crotchet1->dots());
    
}

TEST_F(IMUSANT_duration_Tests, Duration_NormaliseDottedDuration)
{
    S_IMUSANT_duration dur = new_IMUSANT_duration();
    //long num_dots = 0;
    
    dur->set(TRational(3, 4));
    //num_dots = IMUSANT_duration::NormaliseDuration(dur->duration()); -- change to correct setter always normalises value
    
    ASSERT_EQ(1, dur->dots());
    ASSERT_EQ(1, dur->duration().getNumerator());
    ASSERT_EQ(2, dur->duration().getDenominator());
    ASSERT_TRUE(IMUSANT_duration::minim == dur->duration());
    
    dur->set(TRational(7, 8));
    //num_dots = IMUSANT_duration::NormaliseDuration(dur->duration());
    
    ASSERT_EQ(2, dur->dots());
    ASSERT_EQ(1, dur->duration().getNumerator());
    ASSERT_EQ(2, dur->duration().getDenominator());
    ASSERT_TRUE(IMUSANT_duration::minim == dur->duration());
    
    dur->set(TRational(15, 16));
    //num_dots = IMUSANT_duration::NormaliseDuration(dur->duration());
    
    ASSERT_EQ(3, dur->dots());
    ASSERT_EQ(1, dur->duration().getNumerator());
    ASSERT_EQ(2, dur->duration().getDenominator());
    ASSERT_TRUE(IMUSANT_duration::minim == dur->duration());
    
    dur->set(TRational(6, 4));
    //num_dots = IMUSANT_duration::NormaliseDuration(dur->duration());
    
    ASSERT_EQ(1, dur->dots());
    ASSERT_EQ(1, dur->duration().getNumerator());
    ASSERT_EQ(1, dur->duration().getDenominator());
    ASSERT_TRUE(IMUSANT_duration::semibreve == dur->duration());
}

/* REDUNDANT TESTS - all durations are simplified upon input
TEST_F(IMUSANT_duration_Tests, Duration_GetSimplifiedDuration_SixOverFour)
{
    // A duration of 6/4 simplifies to 3/2, which is a dotted semibreve.
    
    S_IMUSANT_duration dur = new_IMUSANT_duration();
    S_IMUSANT_duration simplified_dur = new_IMUSANT_duration();

    dur->set(TRational(6, 4));

    *simplified_dur = dur->getSimplifiedDuration();
    
    ASSERT_EQ(3, simplified_dur->duration().getNumerator());
    ASSERT_EQ(2, simplified_dur->duration().getDenominator());
    //ASSERT_TRUE(IMUSANT_duration::semibreve == simplified_dur->duration());
    ASSERT_EQ(0, simplified_dur->dots());
    
}

TEST_F(IMUSANT_duration_Tests, Duration_GetSimplifiedDuration_SevenOverEight)
{
    //  A duration of 7/8 simplifies to a double dotted minim
    //  See above for explanation
    
    S_IMUSANT_duration dur = new_IMUSANT_duration();
    S_IMUSANT_duration simplified_dur = new_IMUSANT_duration();
    
    dur->set(TRational(7, 8));
    
    *simplified_dur = dur->getSimplifiedDuration();
    
    ASSERT_EQ(7, simplified_dur->duration().getNumerator());
    ASSERT_EQ(8, simplified_dur->duration().getDenominator());
    //ASSERT_TRUE(IMUSANT_duration::minim == simplified_dur->duration());
    ASSERT_EQ(0, simplified_dur->dots());
}
*/

TEST_F(IMUSANT_duration_Tests, Duration_GetSimplifiedDuration_WithTimeMod)
{
    // We are in a time signature of 4/4.
    // We have a triplet over a minim.
    //
    // There are mixed note values within the triplet.  The first note is a quaver.
    //
    // The logic is as follows:
    //
    // Duration of the full triplet = 1/2 (a half note)
    // Six quavers can be notated within the triplet so each one is worth (1/2 / 6) or 1/12.
    //

    S_IMUSANT_duration dur = new_IMUSANT_duration();
    S_IMUSANT_duration simplified_dur = new_IMUSANT_duration();
    
    // D-01024.  The normal-dur parameter below is ignored.  You can set it to whatever you like and
    // the calculation will still be correct.
    dur->set(TRational(1,8), 0, TRational(3,2), IMUSANT_duration::crochet, 0);
    
    *simplified_dur = dur->GetSimplifiedDuration();
    
    ASSERT_EQ(1, simplified_dur->duration().getNumerator());
    ASSERT_EQ(12, simplified_dur->duration().getDenominator());
    ASSERT_EQ(0, simplified_dur->dots());
    ASSERT_EQ(1, simplified_dur->time_modification().getNumerator());
    ASSERT_EQ(1, simplified_dur->time_modification().getDenominator());
    ASSERT_EQ(1, simplified_dur->normal_duration().getNumerator());
    ASSERT_EQ(12, simplified_dur->normal_duration().getDenominator());
    ASSERT_EQ(0, simplified_dur->normal_dots());
}

TEST_F(IMUSANT_duration_Tests, Duration_GetSimplifiedDuration_WithTimeModAndNormalNote)
{
    // The logic is as follows:
    
    // We have a triplet of eigth notes taking place over the duration of a quarter note
    // (this is just a bog standard three quavers over a crochet). BUT, the first two quavers
    // in the triplet are combined into a crochet.  So we have a crochet plus a quaver taking
    // place over a crochet.
    //
    // So we have:
    //     duration = 1/4
    //     duration of each note in the triplet
    //       = (duration / 3)
    //       = (1/4 / 3)
    //       = 1/12
    //     first crotchet in the triplet is therefore 2 * 1/12 = 1/6
    //
    // We are expecting simplifiedDuration() to give us 1/6.
    //
    
    S_IMUSANT_duration dur = new_IMUSANT_duration();
    S_IMUSANT_duration simplified_dur = new_IMUSANT_duration();
    
    // D-01024.  The normal-dur parameter below is ignored.  You can set it to whatever you like and
    // the calculation will still be correct.
    dur->set(IMUSANT_duration::crochet, 0, TRational(3,2), IMUSANT_duration::quaver, 0);
    
    *simplified_dur = dur->GetSimplifiedDuration();
    
    ASSERT_EQ(1, simplified_dur->duration().getNumerator());
    ASSERT_EQ(6, simplified_dur->duration().getDenominator());
    ASSERT_EQ(0, simplified_dur->dots());
    ASSERT_EQ(1, simplified_dur->time_modification().getNumerator());
    ASSERT_EQ(1, simplified_dur->time_modification().getDenominator());
    ASSERT_EQ(1, simplified_dur->normal_duration().getNumerator());
    ASSERT_EQ(6, simplified_dur->normal_duration().getDenominator());
    ASSERT_EQ(0, simplified_dur->normal_dots());
}

TEST_F(IMUSANT_duration_Tests, Duration_GetSimplifiedDuration_WithTimeModAndDots)
{
    // The logic is as follows:
    
    // We have a triplet of eigth notes taking place over the duration of a quarter note
    // (this is just a bog standard three quavers over a crochet).  One of the notes in the
    // triplet is a quaver, another is a semiquaver, and the other is a dotted quaver.
    //
    // So we have:
    //     duration = 1/4
    //     duration of each note in the triplet
    //       = (duration / 3)
    //       = (1/4 / 3)
    //       = 1/12
    //     duration of dotted quaver = 1/12 + 1/24 = 3/24 = 1/8
    //
    // We are expecting simplifiedDuration() to give us 1/8.
    //
    
    S_IMUSANT_duration dur = new_IMUSANT_duration();
    S_IMUSANT_duration simplified_dur = new_IMUSANT_duration();
    
    // D-01024.  The normal-dur parameter below is ignored.  You can set it to whatever you like and
    // the calculation will still be correct.
    dur->set(IMUSANT_duration::quaver, 1, TRational(3,2), IMUSANT_duration::quaver, 0);
    
    *simplified_dur = dur->GetSimplifiedDuration();
    
    ASSERT_EQ(1, simplified_dur->duration().getNumerator());
    ASSERT_EQ(8, simplified_dur->duration().getDenominator());
    ASSERT_EQ(0, simplified_dur->dots());
    ASSERT_EQ(1, simplified_dur->time_modification().getNumerator());
    ASSERT_EQ(1, simplified_dur->time_modification().getDenominator());
    ASSERT_EQ(1, simplified_dur->normal_duration().getNumerator());
    ASSERT_EQ(8, simplified_dur->normal_duration().getDenominator());
    ASSERT_EQ(0, simplified_dur->normal_dots());
}

TEST_F(IMUSANT_duration_Tests, Duration_additionOperator_equalityOperator_WithTimeMod)
{
    S_IMUSANT_duration crotchet_in_triplet_1 = new_IMUSANT_duration();
    crotchet_in_triplet_1->set(IMUSANT_duration::crochet, 0, *new TRational(3,2), IMUSANT_duration::crochet, 0);
    
    S_IMUSANT_duration crotchet_in_triplet_2 = new_IMUSANT_duration();
    crotchet_in_triplet_2->set(IMUSANT_duration::crochet, 0, *new TRational(3,2), IMUSANT_duration::crochet, 0);
    
    S_IMUSANT_duration crotchet_in_triplet_3 = new_IMUSANT_duration();
    crotchet_in_triplet_3->set(IMUSANT_duration::crochet, 0, *new TRational(3,2), IMUSANT_duration::crochet, 0);
    
    S_IMUSANT_duration crotchet1 = new_IMUSANT_duration();
    crotchet1->set(IMUSANT_duration::crochet, 0);
    
    S_IMUSANT_duration crotchet2 = new_IMUSANT_duration();
    crotchet2->set(IMUSANT_duration::crochet, 0);
    
    IMUSANT_duration sum = *crotchet_in_triplet_1 + *crotchet_in_triplet_2 + *crotchet_in_triplet_3 + *crotchet1 + *crotchet2;
    
    ASSERT_EQ(1, sum.duration().getNumerator());
    ASSERT_EQ(1, sum.duration().getDenominator());
    ASSERT_EQ(1, sum.time_modification().getNumerator());
    ASSERT_EQ(1, sum.time_modification().getDenominator());
    ASSERT_EQ(1, sum.normal_duration().getNumerator());
    ASSERT_EQ(1, sum.normal_duration().getDenominator());
    ASSERT_EQ(0, sum.normal_dots());
    ASSERT_EQ(0, sum.dots());
    
    S_IMUSANT_duration comparison = new_IMUSANT_duration();
    comparison->duration().setNumerator(1);
    comparison->duration().setDenominator(1);
    comparison->time_modification().setNumerator(1);
    comparison->time_modification().setDenominator(1);
    comparison->normal_duration().setNumerator(1);
    comparison->normal_duration().setDenominator(1);
    comparison->set_normal_dots(0);
    comparison->set_dots(0);
    
    ASSERT_TRUE(sum == *comparison);
}

TEST_F(IMUSANT_duration_Tests, Duration_equalityOperator)
{
    S_IMUSANT_duration lhs = new_IMUSANT_duration();
    lhs->set(IMUSANT_duration::crochet, 1, *new TRational(3,2), IMUSANT_duration::crochet, 256);
    
    S_IMUSANT_duration rhs = new_IMUSANT_duration();
    rhs->set(IMUSANT_duration::crochet, 1, *new TRational(3,2), IMUSANT_duration::crochet, 256);
    
    S_IMUSANT_duration neq1 = new_IMUSANT_duration();
    neq1->set(IMUSANT_duration::quaver, 1, *new TRational(3,2), IMUSANT_duration::crochet, 256);
    
    S_IMUSANT_duration neq2 = new_IMUSANT_duration();
    neq2->set(IMUSANT_duration::crochet, 0, *new TRational(3,2), IMUSANT_duration::crochet, 256);
    
    S_IMUSANT_duration neq3 = new_IMUSANT_duration();
    neq3->set(IMUSANT_duration::crochet, 1, *new TRational(2,2), IMUSANT_duration::crochet, 256);
    
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
    n2->duration().setNumerator(2);
    n2->duration().setDenominator(8);
    
    ASSERT_TRUE(*n1 == *n2);
}


// If we have two crotchets we should have 256 + 256 = 512 as the duration.
// If we have a simple triplet, do we get the right answer?
TEST_F(IMUSANT_duration_Tests, Duration_asAbsoluteNumeric_SumOfSimpleTuple)
{
    S_IMUSANT_duration crotchet1 = new_IMUSANT_duration();
    crotchet1->set(IMUSANT_duration::crochet, 0);
    float crotchet1_actual_val = crotchet1->AsAbsoluteNumeric();
    
    S_IMUSANT_duration crotchet2 = new_IMUSANT_duration();
    crotchet2->set(IMUSANT_duration::crochet, 0);
    float crotchet2_actual_val = crotchet2->AsAbsoluteNumeric();
    
    float sum_of_crotchets = crotchet1_actual_val + crotchet2_actual_val;
    
    S_IMUSANT_duration crotchet_in_triplet_1 = new_IMUSANT_duration();
    crotchet_in_triplet_1->set(IMUSANT_duration::crochet, 0, *new TRational(3,2), IMUSANT_duration::crochet, 0);
    float crotchet_in_triplet_1_actual_val = crotchet_in_triplet_1->AsAbsoluteNumeric();
    
    S_IMUSANT_duration crotchet_in_triplet_2 = new_IMUSANT_duration();
    crotchet_in_triplet_2->set(IMUSANT_duration::crochet, 0, *new TRational(3,2), IMUSANT_duration::crochet, 0);
    float crotchet_in_triplet_2_actual_val = crotchet_in_triplet_2->AsAbsoluteNumeric();
    
    S_IMUSANT_duration crotchet_in_triplet_3 = new_IMUSANT_duration();
    crotchet_in_triplet_3->set(IMUSANT_duration::crochet, 0, *new TRational(3,2), IMUSANT_duration::crochet, 0);
    float crotchet_in_triplet_3_actual_val = crotchet_in_triplet_3->AsAbsoluteNumeric();
    
    float sum_of_tuple = crotchet_in_triplet_1_actual_val + crotchet_in_triplet_2_actual_val + crotchet_in_triplet_3_actual_val;
    
    ASSERT_EQ(sum_of_crotchets, sum_of_tuple) << "The sum of the duration for two crotchets does not equal the sum of a triplet over two crotchets. It should.";
    
}

// If we have two crotchets we should have 256 + 256 = 512 as the duration.
// If we have a triplet with a dotted crotchet in it, do we get the right answer?

TEST_F(IMUSANT_duration_Tests, Duration_asAbsoluteNumeric_SumOfTupleWithDots)
{
    S_IMUSANT_duration crotchet1 = new_IMUSANT_duration();
    crotchet1->set(IMUSANT_duration::crochet, 0);
    float crotchet1_actual_val = crotchet1->AsAbsoluteNumeric();

    S_IMUSANT_duration crotchet2 = new_IMUSANT_duration();
    crotchet2->set(IMUSANT_duration::crochet, 0);
    float crotchet2_actual_val = crotchet2->AsAbsoluteNumeric();
    
    float sum_of_crotchets = crotchet1_actual_val + crotchet2_actual_val;
    
    S_IMUSANT_duration crotchet_in_triplet_1 = new_IMUSANT_duration();
    crotchet_in_triplet_1->set(IMUSANT_duration::crochet, 0, *new TRational(3,2), IMUSANT_duration::crochet, 0);
    float crotchet_in_triplet_1_actual_val = crotchet_in_triplet_1->AsAbsoluteNumeric();
    
    S_IMUSANT_duration dotted_crotchet_in_triplet_2 = new_IMUSANT_duration();
    dotted_crotchet_in_triplet_2->set(IMUSANT_duration::crochet, 1, *new TRational(3,2), IMUSANT_duration::crochet, 0);
    float dotted_crotchet_in_triplet_2_actual_val = dotted_crotchet_in_triplet_2->AsAbsoluteNumeric();
    
    S_IMUSANT_duration quaver_in_triplet = new_IMUSANT_duration();
    quaver_in_triplet->set(IMUSANT_duration::quaver, 0, *new TRational(3,2), IMUSANT_duration::crochet, 0);
    float quaver_in_triplet_actual_val = quaver_in_triplet->AsAbsoluteNumeric();
    
    float sum_of_tuple = crotchet_in_triplet_1_actual_val + dotted_crotchet_in_triplet_2_actual_val + quaver_in_triplet_actual_val;
    
    ASSERT_EQ(sum_of_crotchets, sum_of_tuple) << "The sum of the duration for two crotchets does not equal the sum of a tuple with dots over two crotchets. It should.";
}

//

TEST_F(IMUSANT_duration_Tests, Triplet_Addition_With_Dotted_Note_Test)
{
    S_IMUSANT_duration semibreve, triplet_dotted_minim, triplet_crochet, triplet_minim;
    
    semibreve = new_IMUSANT_duration();
    triplet_dotted_minim = new_IMUSANT_duration();
    triplet_crochet = new_IMUSANT_duration();
    triplet_minim = new_IMUSANT_duration();

    semibreve->set(IMUSANT_duration::semibreve,0);
    triplet_dotted_minim->set(IMUSANT_duration::minim, 1, TRational(3,2), IMUSANT_duration::minim, 0);
    triplet_crochet->set(IMUSANT_duration::crochet, 0, TRational(3,2), IMUSANT_duration::crochet, 0);
    triplet_minim->set(IMUSANT_duration::minim, 0, TRational(3,2), IMUSANT_duration::minim, 0);
    
    S_IMUSANT_duration sum = new_IMUSANT_duration();
    
    *sum = *triplet_dotted_minim + *triplet_crochet + *triplet_minim;
    
    ASSERT_EQ(*sum, *semibreve);
    
}

TEST_F(IMUSANT_duration_Tests, Triplet_Subtraction_With_Dotted_Note_Test)
{
    S_IMUSANT_duration undefined, triplet_dotted_minim, triplet_crochet, triplet_minim;
    
    undefined = new_IMUSANT_duration();
    triplet_dotted_minim = new_IMUSANT_duration();
    triplet_crochet = new_IMUSANT_duration();
    triplet_minim = new_IMUSANT_duration();
    
    undefined->set(IMUSANT_duration::unmeasured,0);
    triplet_dotted_minim->set(IMUSANT_duration::minim, 1, TRational(3,2), IMUSANT_duration::minim, 0);
    triplet_crochet->set(IMUSANT_duration::crochet, 0, TRational(3,2), IMUSANT_duration::crochet, 0);
    triplet_minim->set(IMUSANT_duration::minim, 0, TRational(3,2), IMUSANT_duration::minim, 0);
    
    S_IMUSANT_duration sum = new_IMUSANT_duration();
    
    *sum = *triplet_dotted_minim - *triplet_crochet - *triplet_minim;
    
    ASSERT_EQ(*sum, *undefined);
    
}
