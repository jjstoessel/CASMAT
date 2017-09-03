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

    auto filename = ArgV.get<std::string>(file_switch);
    auto directory = ArgV.get<std::string>(directory_switch);
    bool interval_flag = ArgV.get<bool>(interval_search_flag);
    bool generalised_interval_flag = ArgV.get<bool>(generalised_interval_search_flag);

    bool contour_flag = ArgV.get<bool>(contour_search_flag);

    if (!filename.empty()) {
        processor.addRelativeFile(filename);
    }

    if (!directory.empty()) {
        processor.processRelativeDirectoryFiles(directory);
    }

    if (!processor.getScores().empty())
    {
        if (interval_flag) {
            int length = 4; //temp
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
