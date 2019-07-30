//
//  CATSMAT_sonority_sequences_Expected.h
//  imusant
//
//  Created by Jason Stoessel on 11/06/2016.
//
//

#ifndef imusant_CATSMAT_sonority_sequences_Expected_h
#define imusant_CATSMAT_sonority_sequences_Expected_h

const string TestScore_1_Measure_Expected = "sonority types (measure, index, duration, sonority type): \n(1, 1, 256, 1)\n(1, 2, 256, 1)\n(1, 3, 256, 2)\n(1, 4, 256, 1)\n";

const string TestScore_4_Measures_Expected = "sonority types (measure, index, duration, sonority type): \n(1, 1, 256, 1)\n(1, 2, 256, 4)\n(1, 3, 256, 2)\n(1, 4, 256, 1)\n(2, 1, 256, 2)\n(2, 2, 256, 2)\n(2, 3, 256, 1)\n(2, 4, 256, 2)\n(3, 1, 256, 1)\n(3, 2, 256, 2)\n(3, 3, 256, 1)\n(3, 4, 256, 2)\n(4, 1, 1024, 1)\n";

const string TestScore_4_Measures_WithQuaverPassingNotes_Expected = "sonority types (measure, index, duration, sonority type): \n(1, 1, 128, 1)\n(1, 2, 128, 2)\n(1, 3, 256, 4)\n(1, 4, 256, 2)\n(1, 5, 128, 1)\n(1, 6, 128, 4)\n(2, 1, 128, 2)\n(2, 2, 128, 1)\n(2, 3, 256, 2)\n(2, 4, 256, 1)\n(2, 5, 128, 2)\n(2, 6, 128, 4)\n(3, 1, 256, 1)\n(3, 2, 256, 2)\n(3, 3, 256, 1)\n(3, 4, 128, 2)\n(3, 5, 128, 1)\n(4, 1, 1024, 1)\n";

const string TestScore_4_Measures_WithSemiQuaverPassingNotes_Expected = "sonority types (measure, index, duration, sonority type): \n(1, 1, 64, 1)\n(1, 2, 64, 4)\n(1, 3, 64, 2)\n(1, 4, 64, 1)\n(1, 5, 256, 4)\n(1, 6, 256, 2)\n(1, 7, 128, 1)\n(1, 8, 128, 4)\n(2, 1, 128, 2)\n(2, 2, 128, 1)\n(2, 3, 256, 2)\n(2, 4, 256, 1)\n(2, 5, 128, 2)\n(2, 6, 128, 4)\n(3, 1, 256, 1)\n(3, 2, 256, 2)\n(3, 3, 64, 1)\n(3, 4, 64, 4)\n(3, 5, 64, 1)\n(3, 6, 64, 4)\n(3, 7, 64, 2)\n(3, 8, 64, 4)\n(3, 9, 64, 1)\n(3, 10, 64, 2)\n(4, 1, 1024, 1)\n";

#endif
