//
// Created by Jason Stoessel on 27/08/2017.
//
#include <iostream>
#include "repeats/inc/CATSMAT_repeats.h"
#include "GeneralAnalysis/inc/CATSMAT_processing.h"
#include "IMUSANT_interval_suffixtree_builder.h"
#include "IMUSANT_pitch_suffixtree_builder.h"
#include "IMUSANT_contour_suffixtree_builder.h"

using namespace CATSMAT;

int CATSMAT_repeats::main()
{
    try {

        CATSMAT_processing processor;

        auto filename = ArgV.get<std::string>(kFileSwitch);
        auto directory = ArgV.get<std::string>(kDirectorySwitch);
        auto config_file = ArgV.get<std::string>(kConfigSwitch);
        auto output_file = ArgV.get<std::string>(kOutputFileSwitch); //to implement handler
        bool default_config = ArgV.get<bool>(kDefaultConfigFlag);
        bool interval_flag = ArgV.get<bool>(kIntervalSearchFlag);
        bool generalised_interval_flag = ArgV.get<bool>(kGeneralisedIntervalSearchFlag);
        bool contour_flag = ArgV.get<bool>(kContourSearchFlag);
        bool pitch_flag = ArgV.get<bool>(kPitchSearchFlag);
        bool dyad_search_flag = ArgV.get<bool>(kDyadSearchFlag);
        bool sonority_search_flag = ArgV.get<bool>(kSonoritySearchFlag);
        bool trigram_search_flag = ArgV.get<bool>(kTrigramSearchFlag);
        bool x_score_search_flag = ArgV.get<bool>(kXScoreSearchFlag);
        bool include_dissonances = ArgV.get<bool>(kDissonancesFlag);
        bool include_repeats = ArgV.get<bool>(kRepeatsFlag);
        bool canonic_voices_only = ArgV.get<bool>(kCanonicVoicesOnlyFlag);
        auto length = ArgV.get<int>(kMinSubstringLengthSwitch);

        if (!filename.empty()) {
            processor.addRelativeFile(filename);
        }

        if (!directory.empty()) {
            processor.processRelativeDirectoryFiles(directory);
        }

        if (!config_file.empty()) {

        } else if (default_config) {
            processor.addFilesFromFixedConfigFile();
        }

        if (!processor.getScores().empty()) {
            IMUSANT_IntervalSuffixTreeBuilder ip;
            IMUSANT_PitchSuffixTreeBuilder pp;
            IMUSANT_ContourSuffixTreeBuilder cp;

            if (interval_flag) { //A
                ip.Visit(processor);
                std::cout << "Performing repeated interval substring search" << std::endl;
                cout << ip.FindAndPrintRepeatedSubstrings(length);
            }

            if (contour_flag) { //B

                cp.Visit(processor);
                std::cout << "Performing repeated contour substring search" << std::endl;
                cout << cp.FindAndPrintRepeatedSubstrings(length);
            }

            if (pitch_flag) {
                pp.Visit(processor);
                std::cout << "Performing repeated pitch substring search" << std::endl;
                cout << pp.FindAndPrintRepeatedSubstrings(length);
            }

            if (generalised_interval_flag) {
                //To DO
            }

            if (dyad_search_flag) { //old option J and K
                std::cout << "Performing repeated dyad substring search" << std::endl;
                processor.FindRepeatedDyadSequences(length, !include_dissonances, !include_repeats,
                                                    x_score_search_flag);
            }

            if (sonority_search_flag) { //old option M
                std::cout << "Performing repeated sonority substring search" << std::endl;
                processor.FindRepeatedSonoritySequences(length);
            }

            if (trigram_search_flag) { //old option U
                //need score/x-score approach
                if (canonic_voices_only) {
                    std::cout << "Performing repeated trigram substring search (canonic voices only)" << std::endl;
                    processor.FindRepeatedTrigramSequencesCanonic(length, !include_dissonances, !include_repeats);
                } else {
                    std::cout << "Performing repeated trigram substring search" << std::endl;
                    processor.FindRepeatedTrigramSequences(length, !include_dissonances, !include_repeats);
                }
            }
        }
    }

    catch (std::exception &e)
    {
        cout << "Unexpected problem: " << e.what() << endl;
    }

    return 0;
}
