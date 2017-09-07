//
// Created by Jason Stoessel on 27/08/2017.
//
#include <iostream>
#include "repeats/inc/CATSMAT_repeats.h"
#include <boost/filesystem.hpp>
#include "GeneralAnalysis/inc/CATSMAT_processing.h"
#include "Application/CATSMAT_menu.h"
#include "IMUSANT_interval_suffixtree_builder.h"
#include "IMUSANT_pitch_suffixtree_builder.h"
#include "IMUSANT_contour_suffixtree_builder.h"

using namespace CATSMAT;

int CATSMAT_repeats::main()
{
    filesystem::path full_path(filesystem::initial_path());
    CATSMAT_menu the_menu;
    CATSMAT_processing processor;
    IMUSANT_IntervalSuffixTreeBuilder  ip;
    IMUSANT_ContourSuffixTreeBuilder cp;

    auto filename = ArgV.get<std::string>(kFileSwitch);
    auto directory = ArgV.get<std::string>(kDirectorySwitch);
    auto config_file = ArgV.get<std::string>(kConfigSwitch);
    bool interval_flag = ArgV.get<bool>(kIntervalSearchFlag);
    bool generalised_interval_flag = ArgV.get<bool>(kGeneralisedIntervalSearchFlag);
    bool contour_flag = ArgV.get<bool>(kContourSearchFlag);
    bool score_only_search_flag = ArgV.get<bool>(kScoreSearchFlag);
    bool pitch_search_flag = ArgV.get<bool>(kPitchSearchFlag);
    bool dyad_search_flag = ArgV.get<bool>(kDyadSearchFlag);
    bool trigram_search_flag = ArgV.get<bool>(kTrigramSearchFlag);
    bool x_score_search_flag = ArgV.get<bool>(kXScoreSearchFlag);
    bool dissonances = ArgV.get<bool>(kDissonancesFlag);
    bool repeats = ArgV.get<bool>(kRepeatsFlag);
    auto length = ArgV.get<int>(kMinSubstringLengthSwitch);

    if (!filename.empty()) {
        processor.addRelativeFile(filename);
    }

    if (!directory.empty()) {
        processor.processRelativeDirectoryFiles(directory);
    }

    if (!processor.getScores().empty())
    {
        if (interval_flag) {
            std::cout << "Performing repeated interval substring search" << std::endl;
            cout << ip.FindAndPrintRepeatedSubstrings(length);
        }

        if (contour_flag) {
            int length = 4; //temp
            std::cout << "Performing repeated contour substring search" << std::endl;
            cout << cp.FindAndPrintRepeatedSubstrings(length);
        }

        if (generalised_interval_flag) {
            //To DO
        }

    }

    return 0;
}
