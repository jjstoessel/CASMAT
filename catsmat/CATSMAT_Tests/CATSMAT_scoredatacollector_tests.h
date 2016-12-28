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

const string TestScore_1_Measure_Expected = "General data for TestScore_1_Measure\nPitch\tC0@4\tC0@5\tE0@5\tG0@5\t\nP1\t0\t2\t1\t1\t\nP2\t4\t0\t0\t0\t\nTotal\t4\t2\t1\t1\t\nDuration\t\nP1\t\nP2\t\nTotal\t\nInterval\tper1 / \tmin3 \\ \tmaj3 \\ \tper5 / \t\nP1\t0\t1\t1\t1\t\nP2\t3\t0\t0\t0\t\nTotal\t3\t1\t1\t1\t\n\n";

const string TestScore_4_Measures_Expected = "General data for TestScore_4_Measures\nPitch\tC0@4\tD0@4\tE0@4\tG0@4\tB0@4\tC0@5\tE0@5\tF0@5\tG0@5\t\nP1\t0\t0\t0\t0\t1\t5\t5\t1\t1\t\nP2\t6\t1\t3\t3\t0\t0\t0\t0\t0\t\nTotal\t6\t1\t3\t3\t1\t5\t5\t1\t1\t\nDuration\t\nP1\t\nP2\t\nTotal\t\nInterval\tper1 / \tmin2 \\ \tmaj2 \\ \tmin3 / \tmaj3 / \tper4 \\ \tper5 / \t\nP1\t6\t2\t1\t1\t1\t1\t0\t\nP2\t2\t0\t2\t3\t2\t0\t3\t\nTotal\t8\t2\t3\t4\t3\t1\t3\t\n\n";

const string TestScore_4_Measures_WithQuaverPassingNotes_Expected = "General data for TestScore_4_Measures_WithQuaverPassingNotes\nPitch\tC0@4\tD0@4\tE0@4\tG0@4\tB0@4\tC0@5\tD0@5\tE0@5\tF0@5\tG0@5\t\nP1\t0\t0\t0\t0\t1\t5\t1\t5\t2\t1\t\nP2\t6\t1\t6\t3\t0\t0\t0\t0\t0\t0\t\nTotal\t6\t1\t6\t3\t1\t5\t1\t5\t2\t1\t\nDuration\t\nP1\t\nP2\t\nTotal\t\nInterval\tper1 / \tmin2 / \tmaj2 / \tmin3 / \tmaj3 / \tper4 \\ \t\nP1\t6\t3\t4\t0\t0\t1\t\nP2\t2\t0\t2\t6\t5\t0\t\nTotal\t8\t3\t6\t6\t5\t1\t\n\n";

const string TestScore_4_Measures_WithSemiQuaverPassingNotes_Expected = "General data for TestScore_4_Measures_WithSemiQuaverPassingNotes\nPitch\tC0@4\tD0@4\tE0@4\tF0@4\tG0@4\tB0@4\tC0@5\tD0@5\tE0@5\tF0@5\tG0@5\t\nP1\t0\t0\t0\t0\t0\t1\t5\t1\t6\t4\t1\t\nP2\t6\t3\t6\t2\t3\t0\t0\t0\t0\t0\t0\t\nTotal\t6\t3\t6\t2\t3\t1\t5\t1\t6\t4\t1\t\nDuration\t\nP1\t\nP2\t\nTotal\t\nInterval\tper1 / \tmin2 / \tmaj2 / \tmin3 \\ \tmaj3 \\ \tdim5 \\ \t\nP1\t6\t6\t4\t0\t0\t1\t\nP2\t2\t2\t8\t4\t3\t0\t\nTotal\t8\t8\t12\t4\t3\t1\t\n\n";

#endif /* defined(__catsmat__CATSMAT_scoredatacollector_tests__) */
