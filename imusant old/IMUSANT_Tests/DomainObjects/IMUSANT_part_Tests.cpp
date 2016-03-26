//
//  IMUSANT_part_Tests.cpp
//  imusant
//
//  Created by Derrick Hill on 19/03/2016.
//
//

#include <stdio.h>

#include "gtest/gtest.h"

#include "libIMUSANT.h"

using namespace IMUSANT;

// The fixture for testing class IMUSANT_pitch.
class IMUSANT_part_Tests : public ::testing::Test {
    
protected:
    
    IMUSANT_part_Tests()
    {
        // You can do set-up work for each test here.
    }
    
    virtual ~IMUSANT_part_Tests()
    {
        // You can do clean-up work that doesn't throw exceptions here.
    }
    
    static S_IMUSANT_note initialise_note(long int dur_numerator,
                                   long int dur_denominator,
                                   long dur_dots,
                                   IMUSANT_pitch::type note_name,
                                   unsigned short octave,
                                   unsigned short voice)
    {
        S_IMUSANT_note note = new_IMUSANT_note();
        
        S_IMUSANT_duration d1 = new_IMUSANT_duration();
        d1->set(*new TRational(dur_numerator, dur_denominator), dur_dots, 0, IMUSANT_duration::unmeasured, 0);
        
        note->setDuration(d1);
        
        S_IMUSANT_pitch p1 = new_IMUSANT_pitch();
        p1->set(note_name, octave, voice);
        note->setPitch(p1);
        
        return note;
    }
};


TEST_F(IMUSANT_part_Tests, Notes)
{
    S_IMUSANT_part the_part_we_are_testing = new_IMUSANT_part();
    
    S_IMUSANT_measure m1 = new_IMUSANT_measure();
    S_IMUSANT_measure m2 = new_IMUSANT_measure();
    S_IMUSANT_measure m3 = new_IMUSANT_measure();
    S_IMUSANT_measure m4 = new_IMUSANT_measure();
   
    S_IMUSANT_note n1 = IMUSANT_part_Tests::initialise_note(1, 16, 0, IMUSANT_pitch::type::B,4,1);
    S_IMUSANT_note n2 = IMUSANT_part_Tests::initialise_note(1, 16, 0, IMUSANT_pitch::type::C,4,1);
    S_IMUSANT_note n3 = IMUSANT_part_Tests::initialise_note(1, 32, 0, IMUSANT_pitch::type::D,4,1);
    S_IMUSANT_note n4 = IMUSANT_part_Tests::initialise_note(1, 32, 0, IMUSANT_pitch::type::C,4,1);
    
    n1->setMeasureNum(1);
    n1->setNoteIndex(1);
    n2->setMeasureNum(2);
    n2->setNoteIndex(1);
    n3->setMeasureNum(3);
    n3->setNoteIndex(1);
    n4->setMeasureNum(3);
    n4->setNoteIndex(2);
    
    // This is rerally badly broken.
    // The Note already thinks it knows it's measure number and index.
    // Surely this should be set when the note is added into the measure???
    
    m1->addNote(n1);
    m2->addNote(n2);
    m3->addNote(n3);
    m3->addNote(n4);
    
    the_part_we_are_testing->addMeasure(m1);
    the_part_we_are_testing->addMeasure(m2);
    the_part_we_are_testing->addMeasure(m3);
    the_part_we_are_testing->addMeasure(m4);
    
    IMUSANT_vector<S_IMUSANT_note> the_notes = the_part_we_are_testing->notes();
    S_IMUSANT_pitch pitch = the_notes[0]->pitch();
    
    ASSERT_TRUE(the_notes.size() == 4);
    ASSERT_EQ(pitch->name(),  IMUSANT_pitch::type::B);
    
//    
//    for (S_IMUSANT_note note : the_part_we_are_testing->notes())
//    {
//        cout << note << endl;
//    }
    
}


