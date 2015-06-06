//
//  main.cpp
//  CATSMAT_Tests
//
//  Created by Derrick Hill on 6/06/2015.
//
//

#include <iostream>

#include "CATSMAT_cp_matrix.hpp"

int main(int argc, const char * argv[]) {

    CATSMAT::S_CATSMAT_cp_matrix theMatrix = CATSMAT::new_CATSMAT_cp_matrix();
    
    S_IMUSANT_pitch pitch = new_IMUSANT_pitch();
    pitch->set(IMUSANT_pitch::type::E, 2, 1, IMUSANT_pitch::type::A);
    
    S_IMUSANT_duration duration = new_IMUSANT_duration();
    duration->set(*new TRational(4,4), 0, *new TRational(2,2));
    
    IMUSANT_note *note = new IMUSANT_note();
    
    // REVISIT - IMUSANT_note::print() crashes if pitch == null or duration == null.
    // REVISIT - IMUSANT_duration::print() is not implemented.
    // REVISIT - IMUSANT_pitch::print() need to confirm that the output is as intended.  For the above I get "<PITCH>E0@2<\PITCH>".
    
    note->setPitch(pitch);
    note->setDuration(duration);
    
    theMatrix->addpart();
    theMatrix->add(*note);
    
    theMatrix->print(cout);
    
    return 0;
}
