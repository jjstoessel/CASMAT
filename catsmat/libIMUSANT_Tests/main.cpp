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
    
    // Exclude specific tests...
    // ::testing::GTEST_FLAG(filter) = "-IMUSANT_segmented_part_fixed_period_Tests*" ;
    
    // Include specific tests...
    // ::testing::GTEST_FLAG(filter) = "IMUSANT_partlist_ordered_by_part_entry_Tests*" ;

 
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    
}
