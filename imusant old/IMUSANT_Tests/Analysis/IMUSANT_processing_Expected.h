//
//  IMUSANT_processing_Expected.h
//  imusant
//
//  Created by Derrick Hill on 9/08/2015.
//
//


#ifndef imusant_IMUSANT_processing_Expected_h
#define imusant_IMUSANT_processing_Expected_h

// using namespace std;

#include <string>

const std::string FindRepeatedIntervalSubstrings_RefactorTest_Expected =
    "Sequence: maj3 \\ , maj2 / , maj2 / , min2 / , \nOccurrences: (2, 1, 82, 1) (2, 2, 87, 1) (2, 3, 92, 1) (1, 1, 16, 1) (1, 2, 23, 1) (1, 3, 30, 1) \n\nSequence: maj2 \\ , maj2 \\ , min2 \\ , maj2 \\ , \nOccurrences: (2, 3, 72, 1) (2, 1, 62, 1) (2, 2, 67, 1) (2, 1, 109, 1) (2, 2, 114, 1) (2, 1, 113, 3) (2, 3, 73, 4) (2, 1, 63, 4) (2, 2, 68, 4) (1, 1, 51, 4) (1, 2, 58, 4) \n\nSequence: maj2 \\ , maj2 \\ , maj2 / , maj2 / , \nOccurrences: (1, 2, 11, 2) (1, 3, 18, 2) (1, 1, 4, 2) (2, 1, 89, 1) (2, 2, 94, 1) (2, 3, 61, 1) (2, 1, 51, 1) (2, 2, 56, 1) \n\nSequence: maj2 \\ , maj2 \\ , maj2 / , maj2 / , maj2 \\ , \nOccurrences: (1, 2, 11, 2) (1, 3, 18, 2) (1, 1, 4, 2) (2, 1, 89, 1) (2, 2, 94, 1) \n\nSequence: maj2 \\ , maj2 \\ , maj2 / , per5 / , \nOccurrences: (1, 2, 20, 1) (1, 3, 27, 1) (2, 3, 84, 1) \n\nSequence: maj2 \\ , min2 \\ , maj2 \\ , maj2 \\ , \nOccurrences: (2, 3, 73, 1) (2, 1, 63, 1) (2, 2, 68, 1) (1, 2, 10, 2) (1, 3, 17, 2) (1, 1, 3, 2) (2, 1, 88, 1) (2, 2, 93, 1) \n\nSequence: maj2 \\ , min2 \\ , maj2 \\ , maj2 \\ , maj2 / , maj2 / , maj2 \\ , \nOccurrences: (1, 2, 10, 2) (1, 3, 17, 2) (1, 1, 3, 2) (2, 1, 88, 1) (2, 2, 93, 1) \n\nSequence: maj2 \\ , min2 \\ , maj2 \\ , maj2 / , \nOccurrences: (2, 3, 57, 1) (2, 1, 47, 1) (2, 2, 52, 1) (1, 2, 53, 7) (1, 3, 60, 7) (2, 3, 12, 1) (2, 1, 2, 1) (2, 2, 7, 1) \n\nSequence: maj2 \\ , min2 \\ , maj2 \\ , maj2 / , maj2 \\ , maj2 \\ , maj2 / , \nOccurrences: (2, 3, 57, 1) (2, 1, 47, 1) (2, 2, 52, 1) (1, 2, 53, 7) (1, 3, 60, 7) \n\nSequence: maj2 \\ , min2 \\ , min2 / , maj2 \\ , \nOccurrences: (2, 3, 69, 1) (2, 1, 59, 1) (2, 2, 64, 1) (1, 2, 52, 3) (1, 3, 59, 3) (1, 1, 45, 3) \n\nSequence: maj2 \\ , min2 \\ , min2 / , maj2 / , \nOccurrences: (1, 2, 15, 1) (1, 3, 22, 1) (1, 1, 8, 1) (2, 3, 99, 1) \n\nSequence: maj2 \\ , min2 \\ , min2 / , per5 / , \nOccurrences: (1, 1, 13, 1) (2, 1, 74, 1) (2, 2, 79, 1) \n\nSequence: maj2 \\ , min2 \\ , min3 / , maj2 \\ , \nOccurrences: (2, 3, 26, 1) (2, 1, 16, 1) (2, 2, 21, 1) (1, 2, 49, 1) (1, 3, 56, 1) (1, 1, 42, 1) \n\nSequence: maj2 \\ , perf1  , maj2 \\ , min2 \\ , \nOccurrences: (2, 1, 86, 1) (2, 2, 91, 1) (2, 3, 96, 1) (1, 2, 14, 1) (1, 3, 21, 1) (1, 1, 7, 1) \n\nSequence: maj2 \\ , maj2 / , maj3 \\ , min2 \\ , \nOccurrences: (2, 1, 79, 5) (2, 2, 84, 5) (2, 3, 89, 5) (1, 1, 62, 1) \n\nSequence: maj2 \\ , maj2 / , maj2 \\ , maj2 \\ , \nOccurrences: (2, 1, 108, 2) (2, 2, 113, 2) (1, 1, 51, 2) (1, 2, 58, 2) (1, 1, 20, 1) (1, 2, 27, 1) (1, 3, 34, 1) (2, 3, 59, 1) (2, 1, 49, 1) (2, 2, 54, 1) (1, 2, 54, 2) (1, 3, 61, 2) (2, 3, 81, 2) \n\nSequence: maj2 \\ , maj2 / , maj2 \\ , maj2 \\ , min2 \\ , \nOccurrences: (2, 1, 108, 2) (2, 2, 113, 2) (1, 1, 51, 2) (1, 2, 58, 2) (1, 1, 20, 1) (1, 2, 27, 1) (1, 3, 34, 1) \n\nSequence: maj2 \\ , maj2 / , maj2 \\ , maj2 \\ , min2 \\ , maj2 \\ , \nOccurrences: (2, 1, 108, 2) (2, 2, 113, 2) (1, 1, 51, 2) (1, 2, 58, 2) \n\nSequence: maj2 \\ , maj2 / , maj2 \\ , maj2 \\ , maj2 / , \nOccurrences: (2, 3, 59, 1) (2, 1, 49, 1) (2, 2, 54, 1) (1, 2, 54, 2) (1, 3, 61, 2) (2, 3, 81, 2) \n\nSequence: maj2 \\ , maj2 / , maj2 \\ , min2 \\ , min2 / , \nOccurrences: (1, 2, 52, 1) (1, 3, 59, 1) (1, 1, 45, 1) (2, 1, 71, 2) (2, 2, 76, 2) \n\nSequence: maj2 \\ , maj2 / , maj2 \\ , maj2 / , \nOccurrences: (1, 1, 61, 1) (2, 1, 107, 1) (2, 2, 112, 1) (2, 1, 77, 1) (2, 2, 82, 1) (2, 3, 87, 1) \n\nSequence: maj2 \\ , maj2 / , perf1  , maj2 \\ , \nOccurrences: (2, 1, 99, 2) (2, 2, 104, 2) (2, 3, 109, 2) (1, 1, 23, 1) (1, 2, 30, 1) (1, 3, 37, 1) \n\nSequence: maj2 \\ , maj2 / , maj2 / , maj2 \\ , \nOccurrences: (1, 2, 12, 1) (1, 3, 19, 1) (1, 1, 5, 1) (2, 1, 89, 2) (2, 2, 94, 2) (1, 1, 18, 2) (1, 2, 25, 2) (1, 3, 32, 2) (1, 2, 51, 3) (1, 3, 58, 3) (1, 1, 44, 3) \n\nSequence: maj2 \\ , maj2 / , maj2 / , maj2 \\ , maj2 / , \nOccurrences: (2, 1, 89, 2) (2, 2, 94, 2) (1, 1, 18, 2) (1, 2, 25, 2) (1, 3, 32, 2) (1, 2, 51, 3) (1, 3, 58, 3) (1, 1, 44, 3) \n\nSequence: min2 \\ , maj2 \\ , maj2 \\ , maj2 / , maj2 / , maj2 \\ , \nOccurrences: (1, 2, 11, 1) (1, 3, 18, 1) (1, 1, 4, 1) (2, 1, 88, 2) (2, 2, 93, 2) \n\nSequence: min2 \\ , maj2 \\ , maj2 / , maj2 \\ , maj2 \\ , maj2 / , \nOccurrences: (2, 3, 58, 1) (2, 1, 48, 1) (2, 2, 53, 1) (1, 2, 54, 1) (1, 3, 61, 1) \n\nSequence: min2 \\ , min2 / , maj2 \\ , min2 \\ , \nOccurrences: (2, 3, 56, 1) (2, 1, 46, 1) (2, 2, 51, 1) (1, 2, 52, 4) (1, 3, 59, 4) (1, 1, 45, 4) \n\nSequence: min2 / , maj2 \\ , maj2 \\ , min2 \\ , \nOccurrences: (2, 3, 69, 3) (2, 1, 59, 3) (2, 2, 64, 3) (1, 1, 46, 6) \n\nSequence: min2 / , min2 \\ , maj2 \\ , maj2 / , \nOccurrences: (2, 1, 79, 3) (2, 2, 84, 3) (2, 3, 89, 3) (1, 1, 47, 3) \n\nSequence: min2 / , maj2 / , maj2 / , maj2 \\ , \nOccurrences: (1, 2, 46, 2) (1, 3, 53, 2) (1, 1, 39, 2) (1, 1, 63, 1) (1, 2, 63, 2) (2, 3, 47, 1) (2, 1, 37, 1) (2, 2, 42, 1) \n\nSequence: maj2 / , maj2 \\ , maj2 \\ , min2 \\ , \nOccurrences: (2, 1, 108, 3) (2, 2, 113, 3) (2, 1, 113, 2) (1, 1, 51, 3) (1, 2, 58, 3) (1, 1, 12, 1) (1, 1, 20, 2) (1, 2, 27, 2) (1, 3, 34, 2) (1, 2, 47, 2) (1, 3, 54, 2) (1, 1, 40, 2) \n\nSequence: maj2 / , maj2 \\ , maj2 \\ , min2 \\ , maj2 \\ , \nOccurrences: (2, 1, 108, 3) (2, 2, 113, 3) (2, 1, 113, 2) (1, 1, 51, 3) (1, 2, 58, 3) \n\nSequence: maj2 / , maj2 \\ , maj2 \\ , maj2 / , \nOccurrences: (2, 3, 35, 1) (2, 1, 25, 1) (2, 2, 30, 1) (2, 3, 60, 1) (2, 1, 50, 1) (2, 2, 55, 1) (1, 2, 54, 3) (1, 3, 61, 3) (1, 1, 54, 3) (1, 2, 61, 3) (2, 3, 83, 2) \n\nSequence: maj2 / , maj2 \\ , min2 \\ , min2 / , \nOccurrences: (2, 3, 48, 2) (2, 1, 38, 2) (2, 2, 43, 2) (2, 3, 68, 1) (2, 1, 58, 1) (2, 2, 63, 1) (1, 2, 52, 2) (1, 3, 59, 2) (1, 1, 45, 2) (2, 1, 73, 2) (2, 2, 78, 2) \n\nSequence: maj2 / , maj2 \\ , min2 \\ , min2 / , maj2 \\ , \nOccurrences: (2, 3, 68, 1) (2, 1, 58, 1) (2, 2, 63, 1) (1, 2, 52, 2) (1, 3, 59, 2) (1, 1, 45, 2) \n\nSequence: maj2 / , maj2 \\ , maj2 / , maj2 \\ , \nOccurrences: (2, 1, 108, 1) (2, 2, 113, 1) (1, 1, 19, 2) (1, 2, 26, 2) (1, 3, 33, 2) (1, 2, 51, 5) (1, 3, 58, 5) (1, 1, 44, 5) (2, 1, 76, 3) (2, 2, 81, 3) (2, 3, 86, 3) \n\nSequence: maj2 / , maj2 \\ , maj2 / , maj2 \\ , maj2 \\ , min2 \\ , \nOccurrences: (2, 1, 108, 1) (2, 2, 113, 1) (1, 1, 19, 2) (1, 2, 26, 2) (1, 3, 33, 2) \n\nSequence: maj2 / , min2 / , min2 \\ , maj2 \\ , \nOccurrences: (1, 1, 32, 2) (1, 2, 39, 2) (1, 3, 46, 2) (2, 3, 21, 1) (2, 1, 11, 1) (2, 2, 16, 1) (2, 1, 79, 2) (2, 2, 84, 2) (2, 3, 89, 2) \n\nSequence: maj2 / , min2 / , maj2 / , maj2 \\ , \nOccurrences: (2, 3, 31, 2) (2, 1, 21, 2) (2, 2, 26, 2) (1, 2, 53, 4) (1, 3, 60, 4) \n\nSequence: maj2 / , min2 / , maj2 / , maj2 / , maj2 \\ , \nOccurrences: (1, 1, 38, 1) (1, 1, 62, 8) (2, 3, 46, 2) (2, 1, 36, 2) (2, 2, 41, 2) \n\nSequence: maj2 / , maj2 / , maj2 \\ , maj2 / , \nOccurrences: (2, 1, 89, 3) (2, 2, 94, 3) (1, 1, 19, 1) (1, 2, 26, 1) (1, 3, 33, 1) (1, 2, 51, 4) (1, 3, 58, 4) (1, 1, 44, 4) (2, 1, 76, 2) (2, 2, 81, 2) (2, 3, 86, 2) \n\nSequence: maj2 / , maj2 / , maj2 \\ , maj2 / , maj2 \\ , \nOccurrences: (1, 1, 19, 1) (1, 2, 26, 1) (1, 3, 33, 1) (1, 2, 51, 4) (1, 3, 58, 4) (1, 1, 44, 4) (2, 1, 76, 2) (2, 2, 81, 2) (2, 3, 86, 2) \n\nSequence: maj2 / , maj2 / , min2 / , maj2 \\ , \nOccurrences: (1, 1, 46, 4) (2, 1, 104, 3) (2, 2, 109, 3) \n\nSequence: maj2 / , maj2 / , min2 / , maj2 / , \nOccurrences: (2, 3, 31, 1) (2, 1, 21, 1) (2, 2, 26, 1) (1, 1, 62, 7) (2, 3, 46, 1) (2, 1, 36, 1) (2, 2, 41, 1) \n\nSequence: maj2 / , maj2 / , min2 / , maj2 / , maj2 / , maj2 \\ , \nOccurrences: (1, 1, 62, 7) (2, 3, 46, 1) (2, 1, 36, 1) (2, 2, 41, 1) \n\nSequence: maj2 / , maj2 / , maj2 / , maj2 \\ , \nOccurrences: (1, 2, 18, 1) (1, 3, 25, 1) (1, 1, 11, 1) (2, 3, 64, 1) (2, 1, 54, 1) (2, 2, 59, 1) \n\nSequence: maj2 / , maj2 / , maj2 / , min2 / , \nOccurrences: (2, 1, 104, 2) (2, 2, 109, 2) (2, 3, 114, 2) (1, 1, 62, 6) \n\nSequence: min3 / , maj2 / , maj2 / , maj2 / , \nOccurrences: (1, 2, 17, 2) (1, 3, 24, 2) (1, 1, 10, 2) (2, 1, 104, 1) (2, 2, 109, 1) (2, 3, 114, 1) \n\n";

const std::string FindRepeatedIntervalSubstrings_SmokeTest_Expected =
    "1: Kyrie ele\xC3\x98son\n2: Sanctus\nResults are labeled (movement, voice, measure, note index).\nVoices are designated from highest (1) to lowest.\nFound common exact intevallic subsequences of 4 or more elements at: \nInstance: maj3 \\  maj2 /  maj2 /  min2 /  (2,1,82,1)(2,2,87,1)(2,3,92,1)(1,1,16,1)(1,2,23,1)(1,3,30,1)\nLength: 4 Occurences: 6\n\nInstance: maj2 \\  maj2 \\  min2 \\  maj2 \\  (2,3,72,1)(2,1,62,1)(2,2,67,1)(2,1,109,1)(2,2,114,1)(2,1,113,3)(2,3,73,4)(2,1,63,4)(2,2,68,4)(1,1,51,4)(1,2,58,4)\nLength: 4 Occurences: 11\n\nInstance: maj2 \\  maj2 \\  maj2 /  maj2 /  (1,2,11,2)(1,3,18,2)(1,1,4,2)(2,1,89,1)(2,2,94,1)(2,3,61,1)(2,1,51,1)(2,2,56,1)\nLength: 4 Occurences: 8\n\nInstance: maj2 \\  maj2 \\  maj2 /  maj2 /  maj2 \\  (1,2,11,2)(1,3,18,2)(1,1,4,2)(2,1,89,1)(2,2,94,1)\nLength: 5 Occurences: 5\n\nInstance: maj2 \\  maj2 \\  maj2 /  per5 /  (1,2,20,1)(1,3,27,1)(2,3,84,1)\nLength: 4 Occurences: 3\n\nInstance: maj2 \\  min2 \\  maj2 \\  maj2 \\  (2,3,73,1)(2,1,63,1)(2,2,68,1)(1,2,10,2)(1,3,17,2)(1,1,3,2)(2,1,88,1)(2,2,93,1)\nLength: 4 Occurences: 8\n\nInstance: maj2 \\  min2 \\  maj2 \\  maj2 \\  maj2 /  maj2 /  maj2 \\  (1,2,10,2)(1,3,17,2)(1,1,3,2)(2,1,88,1)(2,2,93,1)\nLength: 7 Occurences: 5\n\nInstance: maj2 \\  min2 \\  maj2 \\  maj2 /  (2,3,57,1)(2,1,47,1)(2,2,52,1)(1,2,53,7)(1,3,60,7)(2,3,12,1)(2,1,2,1)(2,2,7,1)\nLength: 4 Occurences: 8\n\nInstance: maj2 \\  min2 \\  maj2 \\  maj2 /  maj2 \\  maj2 \\  maj2 /  (2,3,57,1)(2,1,47,1)(2,2,52,1)(1,2,53,7)(1,3,60,7)\nLength: 7 Occurences: 5\n\nInstance: maj2 \\  min2 \\  min2 /  maj2 \\  (2,3,69,1)(2,1,59,1)(2,2,64,1)(1,2,52,3)(1,3,59,3)(1,1,45,3)\nLength: 4 Occurences: 6\n\nInstance: maj2 \\  min2 \\  min2 /  maj2 /  (1,2,15,1)(1,3,22,1)(1,1,8,1)(2,3,99,1)\nLength: 4 Occurences: 4\n\nInstance: maj2 \\  min2 \\  min2 /  per5 /  (1,1,13,1)(2,1,74,1)(2,2,79,1)\nLength: 4 Occurences: 3\n\nInstance: maj2 \\  min2 \\  min3 /  maj2 \\  (2,3,26,1)(2,1,16,1)(2,2,21,1)(1,2,49,1)(1,3,56,1)(1,1,42,1)\nLength: 4 Occurences: 6\n\nInstance: maj2 \\  perf1   maj2 \\  min2 \\  (2,1,86,1)(2,2,91,1)(2,3,96,1)(1,2,14,1)(1,3,21,1)(1,1,7,1)\nLength: 4 Occurences: 6\n\nInstance: maj2 \\  maj2 /  maj3 \\  min2 \\  (2,1,79,5)(2,2,84,5)(2,3,89,5)(1,1,62,1)\nLength: 4 Occurences: 4\n\nInstance: maj2 \\  maj2 /  maj2 \\  maj2 \\  (2,1,108,2)(2,2,113,2)(1,1,51,2)(1,2,58,2)(1,1,20,1)(1,2,27,1)(1,3,34,1)(2,3,59,1)(2,1,49,1)(2,2,54,1)(1,2,54,2)(1,3,61,2)(2,3,81,2)\nLength: 4 Occurences: 13\n\nInstance: maj2 \\  maj2 /  maj2 \\  maj2 \\  min2 \\  (2,1,108,2)(2,2,113,2)(1,1,51,2)(1,2,58,2)(1,1,20,1)(1,2,27,1)(1,3,34,1)\nLength: 5 Occurences: 7\n\nInstance: maj2 \\  maj2 /  maj2 \\  maj2 \\  min2 \\  maj2 \\  (2,1,108,2)(2,2,113,2)(1,1,51,2)(1,2,58,2)\nLength: 6 Occurences: 4\n\nInstance: maj2 \\  maj2 /  maj2 \\  maj2 \\  maj2 /  (2,3,59,1)(2,1,49,1)(2,2,54,1)(1,2,54,2)(1,3,61,2)(2,3,81,2)\nLength: 5 Occurences: 6\n\nInstance: maj2 \\  maj2 /  maj2 \\  min2 \\  min2 /  (1,2,52,1)(1,3,59,1)(1,1,45,1)(2,1,71,2)(2,2,76,2)\nLength: 5 Occurences: 5\n\nInstance: maj2 \\  maj2 /  maj2 \\  maj2 /  (1,1,61,1)(2,1,107,1)(2,2,112,1)(2,1,77,1)(2,2,82,1)(2,3,87,1)\nLength: 4 Occurences: 6\n\nInstance: maj2 \\  maj2 /  perf1   maj2 \\  (2,1,99,2)(2,2,104,2)(2,3,109,2)(1,1,23,1)(1,2,30,1)(1,3,37,1)\nLength: 4 Occurences: 6\n\nInstance: maj2 \\  maj2 /  maj2 /  maj2 \\  (1,2,12,1)(1,3,19,1)(1,1,5,1)(2,1,89,2)(2,2,94,2)(1,1,18,2)(1,2,25,2)(1,3,32,2)(1,2,51,3)(1,3,58,3)(1,1,44,3)\nLength: 4 Occurences: 11\n\nInstance: maj2 \\  maj2 /  maj2 /  maj2 \\  maj2 /  (2,1,89,2)(2,2,94,2)(1,1,18,2)(1,2,25,2)(1,3,32,2)(1,2,51,3)(1,3,58,3)(1,1,44,3)\nLength: 5 Occurences: 8\n\nInstance: min2 \\  maj2 \\  maj2 \\  maj2 /  maj2 /  maj2 \\  (1,2,11,1)(1,3,18,1)(1,1,4,1)(2,1,88,2)(2,2,93,2)\nLength: 6 Occurences: 5\n\nInstance: min2 \\  maj2 \\  maj2 /  maj2 \\  maj2 \\  maj2 /  (2,3,58,1)(2,1,48,1)(2,2,53,1)(1,2,54,1)(1,3,61,1)\nLength: 6 Occurences: 5\n\nInstance: min2 \\  min2 /  maj2 \\  min2 \\  (2,3,56,1)(2,1,46,1)(2,2,51,1)(1,2,52,4)(1,3,59,4)(1,1,45,4)\nLength: 4 Occurences: 6\n\nInstance: min2 /  maj2 \\  maj2 \\  min2 \\  (2,3,69,3)(2,1,59,3)(2,2,64,3)(1,1,46,6)\nLength: 4 Occurences: 4\n\nInstance: min2 /  min2 \\  maj2 \\  maj2 /  (2,1,79,3)(2,2,84,3)(2,3,89,3)(1,1,47,3)\nLength: 4 Occurences: 4\n\nInstance: min2 /  maj2 /  maj2 /  maj2 \\  (1,2,46,2)(1,3,53,2)(1,1,39,2)(1,1,63,1)(1,2,63,2)(2,3,47,1)(2,1,37,1)(2,2,42,1)\nLength: 4 Occurences: 8\n\nInstance: maj2 /  maj2 \\  maj2 \\  min2 \\  (2,1,108,3)(2,2,113,3)(2,1,113,2)(1,1,51,3)(1,2,58,3)(1,1,12,1)(1,1,20,2)(1,2,27,2)(1,3,34,2)(1,2,47,2)(1,3,54,2)(1,1,40,2)\nLength: 4 Occurences: 12\n\nInstance: maj2 /  maj2 \\  maj2 \\  min2 \\  maj2 \\  (2,1,108,3)(2,2,113,3)(2,1,113,2)(1,1,51,3)(1,2,58,3)\nLength: 5 Occurences: 5\n\nInstance: maj2 /  maj2 \\  maj2 \\  maj2 /  (2,3,35,1)(2,1,25,1)(2,2,30,1)(2,3,60,1)(2,1,50,1)(2,2,55,1)(1,2,54,3)(1,3,61,3)(1,1,54,3)(1,2,61,3)(2,3,83,2)\nLength: 4 Occurences: 11\n\nInstance: maj2 /  maj2 \\  min2 \\  min2 /  (2,3,48,2)(2,1,38,2)(2,2,43,2)(2,3,68,1)(2,1,58,1)(2,2,63,1)(1,2,52,2)(1,3,59,2)(1,1,45,2)(2,1,73,2)(2,2,78,2)\nLength: 4 Occurences: 11\n\nInstance: maj2 /  maj2 \\  min2 \\  min2 /  maj2 \\  (2,3,68,1)(2,1,58,1)(2,2,63,1)(1,2,52,2)(1,3,59,2)(1,1,45,2)\nLength: 5 Occurences: 6\n\nInstance: maj2 /  maj2 \\  maj2 /  maj2 \\  (2,1,108,1)(2,2,113,1)(1,1,19,2)(1,2,26,2)(1,3,33,2)(1,2,51,5)(1,3,58,5)(1,1,44,5)(2,1,76,3)(2,2,81,3)(2,3,86,3)\nLength: 4 Occurences: 11\n\nInstance: maj2 /  maj2 \\  maj2 /  maj2 \\  maj2 \\  min2 \\  (2,1,108,1)(2,2,113,1)(1,1,19,2)(1,2,26,2)(1,3,33,2)\nLength: 6 Occurences: 5\n\nInstance: maj2 /  min2 /  min2 \\  maj2 \\  (1,1,32,2)(1,2,39,2)(1,3,46,2)(2,3,21,1)(2,1,11,1)(2,2,16,1)(2,1,79,2)(2,2,84,2)(2,3,89,2)\nLength: 4 Occurences: 9\n\nInstance: maj2 /  min2 /  maj2 /  maj2 \\  (2,3,31,2)(2,1,21,2)(2,2,26,2)(1,2,53,4)(1,3,60,4)\nLength: 4 Occurences: 5\n\nInstance: maj2 /  min2 /  maj2 /  maj2 /  maj2 \\  (1,1,38,1)(1,1,62,8)(2,3,46,2)(2,1,36,2)(2,2,41,2)\nLength: 5 Occurences: 5\n\nInstance: maj2 /  maj2 /  maj2 \\  maj2 /  (2,1,89,3)(2,2,94,3)(1,1,19,1)(1,2,26,1)(1,3,33,1)(1,2,51,4)(1,3,58,4)(1,1,44,4)(2,1,76,2)(2,2,81,2)(2,3,86,2)\nLength: 4 Occurences: 11\n\nInstance: maj2 /  maj2 /  maj2 \\  maj2 /  maj2 \\  (1,1,19,1)(1,2,26,1)(1,3,33,1)(1,2,51,4)(1,3,58,4)(1,1,44,4)(2,1,76,2)(2,2,81,2)(2,3,86,2)\nLength: 5 Occurences: 9\n\nInstance: maj2 /  maj2 /  min2 /  maj2 \\  (1,1,46,4)(2,1,104,3)(2,2,109,3)\nLength: 4 Occurences: 3\n\nInstance: maj2 /  maj2 /  min2 /  maj2 /  (2,3,31,1)(2,1,21,1)(2,2,26,1)(1,1,62,7)(2,3,46,1)(2,1,36,1)(2,2,41,1)\nLength: 4 Occurences: 7\n\nInstance: maj2 /  maj2 /  min2 /  maj2 /  maj2 /  maj2 \\  (1,1,62,7)(2,3,46,1)(2,1,36,1)(2,2,41,1)\nLength: 6 Occurences: 4\n\nInstance: maj2 /  maj2 /  maj2 /  maj2 \\  (1,2,18,1)(1,3,25,1)(1,1,11,1)(2,3,64,1)(2,1,54,1)(2,2,59,1)\nLength: 4 Occurences: 6\n\nInstance: maj2 /  maj2 /  maj2 /  min2 /  (2,1,104,2)(2,2,109,2)(2,3,114,2)(1,1,62,6)\nLength: 4 Occurences: 4\n\nInstance: min3 /  maj2 /  maj2 /  maj2 /  (1,2,17,2)(1,3,24,2)(1,1,10,2)(2,1,104,1)(2,2,109,1)(2,3,114,1)\nLength: 4 Occurences: 6\n\n\n";


#endif
