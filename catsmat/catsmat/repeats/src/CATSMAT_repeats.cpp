//
// Created by Jason Stoessel on 27/08/2017.
//
#include <iostream>
#include "repeats/inc/CATSMAT_repeats.h"
#include <boost/filesystem.hpp>
#include "GeneralAnalysis/inc/CATSMAT_processing.h"
#include "Application/CATSMAT_menu.h"

using namespace CATSMAT;

int CATSMAT_repeats::main()
{
    filesystem::path full_path(filesystem::initial_path());
    CATSMAT_menu the_menu;
    CATSMAT_processing processor;

    auto file = ArgV.get<std::string>("file");
    bool interval_flag = ArgV.get<bool>("interval");

    if (!file.empty())
    {
        std::cout << "File: " << name.c_str() << std::endl;
        //the_menu.addUserSpecifiedFile(processor)
    }


    std::cout << "Flag: ";

    if (interval_flag)
        std::cout << "interval" << std::endl;

    return 0;
}
