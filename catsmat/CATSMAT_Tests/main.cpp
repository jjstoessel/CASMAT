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
//    ::testing::GTEST_FLAG(filter) = "*CP_Matrix*";   // Syntax for limiting which tests get run.
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    
}
