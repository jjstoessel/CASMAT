//
// Created by Jason Stoessel on 15/9/17.
//

#ifndef CATSMAT_SEGMENTER_H
#define CATSMAT_SEGMENTER_H

#include "Commando/inc/MultiMode.hpp"

using namespace std;

namespace CATSMAT {

    class Segmenter : public CLI::SingleMode {
    public:
        const string kFileSwitch = "file";
        const string kDirectorySwitch = "directory";
        const string kConfigSwitch = "config";
        const string kDefaultConfigFlag = "default_config";
        const string kOutputFileSwitch = "output_file";
        const string kLowerBoundaryDetectionModelSegmentationFlag = "LBDM";
        const string kIsoperiodicSegmentationFlag = "isoperiodic";

        CLI::Switch file_{kFileSwitch, "", "File to operate on", "f"};
        CLI::Switch directory_{kDirectorySwitch, "", "Directory to operate on", "d"};
        CLI::Switch config_{kConfigSwitch, "", "Configuration file listing files to operate on", "k"};
        CLI::Flag   default_config_{kDefaultConfigFlag, "0",
                                  "Use configuration file in HOME directory listing files to operate on", "K"};
        CLI::Switch output_file_        {kOutputFileSwitch, "out.txt", "Results output file", "o"};

        CLI::Flag   LBDM_{kLowerBoundaryDetectionModelSegmentationFlag,"0","Use Lower Boundary Detection Model segmentation", "L"};
        CLI::Flag   isoperiodic_{kIsoperiodicSegmentationFlag, "0", "Use isoperiodic segmentation", "I"};


        CLI::Terminator version_{"version", "show version info",
                                 "CATSMAT_canonic_techniques (1.0.0)\nCopyright (c) Jason Stoessel 2018. All rights reserved."
                                         "\nGNU General Public License v3.0\nThis is free software; see the source for"
                                         " copying conditions.  There is NO\nwarranty; not even for MERCHANTABILITY or"
                                         " FITNESS FOR A PARTICULAR PURPOSE.", "V"};

        CLI::Terminator copyright_{"copyright", "show copyright info",
                                   "CATSMAT_canonic_techniques (1.0.1)\nCopyright (c) Jason Stoessel 2018. All rights reserved."
                                           "\nGNU General Public License v3.0\nThis is free software; see the source for"
                                           " copying conditions.  There is NO\nwarranty; not even for MERCHANTABILITY or"
                                           " FITNESS FOR A PARTICULAR PURPOSE.", "C"};

        Segmenter(const int argc, const char **argv)
                : SingleMode(argc, argv,
                             "Data collection utility for canonic compositions. Give one of the above subcommands "
                                     "with no arguments for their respective usage, or pass the -h, --help flag "
                                     "for more information alone or with one of the above subcommands.",
                             "Report bugs to: jason.stoessel@une.edu.au\n"
                                     "CATSMAT home page: <https://github.com/jjstoessel/CATSMAT>") {
            Register(&file_);
            Register(&directory_);
            Register(&config_);
            Register(&default_config_);
            Register(&LBDM_);
            Register(&isoperiodic_);

            Register(&version_, &copyright_);
        }

        virtual int main();
    };
}


#endif //CATSMAT_SEGMENTER_H
