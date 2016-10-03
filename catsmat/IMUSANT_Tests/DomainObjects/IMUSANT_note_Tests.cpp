//
//  IMUSANT_note_Tests.cpp
//  imusant
//
//  Created by Derrick Hill on 13/11/2015.
//
//

#include <stdio.h>

#include "gtest/gtest.h"

#include "libIMUSANT.h"

using namespace IMUSANT;

// The fixture for testing class IMUSANT_note.
class IMUSANT_note_Tests : public ::testing::Test {
    
    
protected:
    
    IMUSANT_note_Tests()
    {
        // You can do set-up work for each test here.
    }
    
    virtual ~IMUSANT_note_Tests()
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
    
    // Objects declared here can be used by all tests.

    
private:
    
};

TEST_F(IMUSANT_note_Tests, BasicPrintTest)
{
    S_IMUSANT_note the_note = new_IMUSANT_note();
    
    the_note->setMeasureNum(1);
    the_note->setNoteIndex(2);

    stringstream *printed_note_1 = new stringstream();
    the_note->print(*printed_note_1);
    
    const string expected_1 = "<NOTE measure_num=1 index=2 >\n <PITCH>0@0<\\PITCH>\n <DURATION><RHYTHM_TYPE>unmeasured<\\RHYTHM_TYPE><DOTS>0<\\DOTS><TIME_MOD>1/1<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>none<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n";
    
    ASSERT_EQ(expected_1, printed_note_1->str());
    
    S_IMUSANT_duration duration = new_IMUSANT_duration();
    TRational dur(6,8);
    long dots = 3;
    TRational time_mod(3,2);
    duration->set(dur, dots,  time_mod, IMUSANT_duration::unmeasured, 0);
    
    S_IMUSANT_pitch pitch = new_IMUSANT_pitch();
    pitch->set(IMUSANT_pitch::type::D, 2, 1, IMUSANT_pitch::natural, false);
    
    the_note->setDuration(*duration);
    the_note->setPitch(*pitch);
    
    stringstream *printed_note_2 = new stringstream();
    the_note->print(*printed_note_2);
    const string expected_2 =
        "<NOTE measure_num=1 index=2 >\n <PITCH>D0@2<\\PITCH>\n <DURATION><RHYTHM_TYPE>minim<\\RHYTHM_TYPE><DOTS>4<\\DOTS><TIME_MOD>3/2<\\TIME_MOD><\\DURATION>\n <ACCIDENTAL>none<\\ACCIDENTAL>\n<PREVIOUS_TIE>NULL<\\PREVIOUS_TIE>\n<\\NOTE>\n";
    
    // cout << "Expected " << endl << expected_2 << endl;
    // cout << "Actual " << endl << printed_note_2->str()  << endl;
    
    ASSERT_EQ(expected_2, printed_note_2->str() );
    
    delete printed_note_1;
    delete printed_note_2;
    
}
