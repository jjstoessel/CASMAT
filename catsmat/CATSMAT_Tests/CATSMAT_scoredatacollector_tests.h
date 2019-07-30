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

const string TestScore_1_Measure_Expected = "General data for TestScore_1_Measure\nPitches\tC4\tC5\tE5\tG5\t\nP1\t0\t2\t1\t1\t\nP2\t4\t0\t0\t0\t\nTotal\t4\t2\t1\t1\t\nDurations\tquarter\t\nP1\t4\t\nP2\t4\t\nTotal\t8\t\nMelodic Intervals\tper1\t-min3\t-maj3\t+per5\t\nP1\t0\t1\t1\t1\t\nP2\t3\t0\t0\t0\t\nTotal\t3\t1\t1\t1\t\nGeneral Melodic Intervals\t-2\t0\t4\t\nP1\t2\t0\t1\t\nP2\t0\t3\t0\t\nTotal\t2\t3\t1\t\n\n";

const string TestScore_4_Measures_Expected = "General data for TestScore_4_Measures\nPitches\tC4\tD4\tE4\tG4\tB4\tC5\tE5\tF5\tG5\t\nP1\t0\t0\t0\t0\t1\t5\t5\t1\t1\t\nP2\t6\t1\t3\t3\t0\t0\t0\t0\t0\t\nTotal\t6\t1\t3\t3\t1\t5\t5\t1\t1\t\nDurations\tquarter\twhole\t\nP1\t12\t1\t\nP2\t12\t1\t\nTotal\t24\t2\t\nMelodic Intervals\tper1\t-min2\t-maj2\t+min3\t+maj3\t-per4\t+per5\t\nP1\t6\t2\t1\t1\t1\t1\t0\t\nP2\t2\t0\t2\t3\t2\t0\t3\t\nTotal\t8\t2\t3\t4\t3\t1\t3\t\nGeneral Melodic Intervals\t-4\t-3\t-2\t-1\t0\t1\t2\t4\t\nP1\t0\t1\t0\t2\t6\t1\t2\t0\t\nP2\t1\t0\t4\t0\t2\t2\t1\t2\t\nTotal\t1\t1\t4\t2\t8\t3\t3\t2\t\n\n";

const string TestScore_4_Measures_WithQuaverPassingNotes_Expected = "General data for TestScore_4_Measures_WithQuaverPassingNotes\nPitches\tC4\tD4\tE4\tG4\tB4\tC5\tD5\tE5\tF5\tG5\t\nP1\t0\t0\t0\t0\t1\t5\t1\t5\t2\t1\t\nP2\t6\t1\t6\t3\t0\t0\t0\t0\t0\t0\t\nTotal\t6\t1\t6\t3\t1\t5\t1\t5\t2\t1\t\nDurations\teighth\tquarter\twhole\t\nP1\t4\t10\t1\t\nP2\t6\t9\t1\t\nTotal\t10\t19\t2\t\nMelodic Intervals\tper1\t+min2\t+maj2\t+min3\t+maj3\t-per4\t\nP1\t6\t3\t4\t0\t0\t1\t\nP2\t2\t0\t2\t6\t5\t0\t\nTotal\t8\t3\t6\t6\t5\t1\t\nGeneral Melodic Intervals\t-3\t-2\t-1\t0\t1\t2\t\nP1\t1\t0\t2\t6\t5\t0\t\nP2\t0\t6\t0\t2\t2\t5\t\nTotal\t1\t6\t2\t8\t7\t5\t\n\n";

const string TestScore_4_Measures_WithSemiQuaverPassingNotes_Expected = "General data for TestScore_4_Measures_WithSemiQuaverPassingNotes\nPitches\tC4\tD4\tE4\tF4\tG4\tB4\tC5\tD5\tE5\tF5\tG5\t\nP1\t0\t0\t0\t0\t0\t1\t5\t1\t6\t4\t1\t\nP2\t6\t3\t6\t2\t3\t0\t0\t0\t0\t0\t0\t\nTotal\t6\t3\t6\t2\t3\t1\t5\t1\t6\t4\t1\t\nDurations\t16th\teighth\tquarter\twhole\t\nP1\t4\t4\t9\t1\t\nP2\t8\t2\t9\t1\t\nTotal\t12\t6\t18\t2\t\nMelodic Intervals\tper1\t+min2\t+maj2\t-min3\t-maj3\t-dim5\t\nP1\t6\t6\t4\t0\t0\t1\t\nP2\t2\t2\t8\t4\t3\t0\t\nTotal\t8\t8\t12\t4\t3\t1\t\nGeneral Melodic Intervals\t-4\t-2\t-1\t0\t1\t2\t\nP1\t1\t0\t3\t6\t7\t0\t\nP2\t0\t4\t4\t2\t6\t3\t\nTotal\t1\t4\t7\t8\t13\t3\t\n\n";

#endif /* defined(__catsmat__CATSMAT_scoredatacollector_tests__) */
