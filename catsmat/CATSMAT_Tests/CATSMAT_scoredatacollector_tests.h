//
//  CATSMAT_scoredatacollector_tests.h
//  catsmat
//
//  Created by Jason Stoessel on 7/10/2016.
//
//

#ifndef __catsmat__CATSMAT_scoredatacollector_tests__
#define __catsmat__CATSMAT_scoredatacollector_tests__

#include <stdio.h>
#include <string>

using namespace std;

const string TestScore_1_Measure_Expected = "General data for TestScore_1_Measure\nPart: P1\nmaj3 \\ \tmin3 \\ \tper5 / \t\n1\t1\t1\t\nPart: P2\nper1 / \t\n3\t\n";

const string TestScore_4_Measures_Expected = "General data for TestScore_4_Measures\nPart: P1\nper4 \\ \tmaj2 \\ \tmin2 \\ \tper1 / \tmin2 / \tmin3 / \tmaj3 / \t\n1\t1\t1\t6\t1\t1\t1\t\nPart: P2\nper5 \\ \tmaj3 \\ \tmin3 \\ \tper1 / \tmaj2 / \tmin3 / \tper5 / \t\n1\t2\t2\t2\t2\t1\t2\t\n";

const string TestScore_4_Measures_WithQuaverPassingNotes_Expected = "General data for TestScore_4_Measures_WithQuaverPassingNotes\nPart: P1\nper4 \\ \tmaj2 \\ \tmin2 \\ \tper1 / \tmin2 / \tmaj2 / \t\n1\t1\t1\t6\t2\t3\t\nPart: P2\nmaj3 \\ \tmin3 \\ \tper1 / \tmaj2 / \tmin3 / \tmaj3 / \t\n3\t3\t2\t2\t3\t2\t\n";

const string TestScore_4_Measures_WithSemiQuaverPassingNotes_Expected = "General data for TestScore_4_Measures_WithSemiQuaverPassingNotes\nPart: P1\ndim5 \\ \tmaj2 \\ \tmin2 \\ \tper1 / \tmin2 / \tmaj2 / \t\n1\t1\t2\t6\t4\t3\t\nPart: P2\nmaj3 \\ \tmin3 \\ \tmaj2 \\ \tmin2 \\ \tper1 / \tmin2 / \tmaj2 / \tmin3 / \tmaj3 / \t\n2\t2\t3\t1\t2\t1\t5\t2\t1\t\n";

#endif /* defined(__catsmat__CATSMAT_scoredatacollector_tests__) */
