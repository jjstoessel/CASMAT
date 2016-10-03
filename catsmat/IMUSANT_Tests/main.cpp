//
//  main.cpp
//  imusant
//
//  Created by Derrick Hill on 8/08/2015.
//
//

#include <stdio.h>

#include <iostream>
#include <gtest/gtest.h>

using namespace std;

int main(int argc, char * argv[]) {
    
    cout << "RUNNING IMUSANT TESTS" << endl;
    cout << "---------------------" << endl;
 //   ::testing::GTEST_FLAG(filter) = "*GetSegmentsAsNoteVectors_From_Score_Kyrie*";   // Syntax for limiting which tests get run.
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    
}