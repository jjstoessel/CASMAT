//
//  main.cpp
//  CATSMAT_Tests
//
//  Created by Derrick Hill on 6/06/2015.
//
//

#include <iostream>
#include <gtest/gtest.h>

using namespace std;

int main(int argc, char * argv[]) {
    
    cout << "RUNNING CATSMAT TESTS" << endl;
    cout << "---------------------" << endl;
    ::testing::InitGoogleTest(&argc, argv);
//    ::testing::GTEST_FLAG(filter) = "*GetSegmentsAsNoteVectors_From_Score_Kyrie*";   // Syntax for limiting which tests get run.
    return RUN_ALL_TESTS();
    
}
