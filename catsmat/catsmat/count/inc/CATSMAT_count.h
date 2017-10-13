//
// Created by Jason Stoessel on 11/09/2017.
//

#ifndef CATSMAT_CATSMAT_COUNT_H
#define CATSMAT_CATSMAT_COUNT_H

#include "Commando/inc/MultiMode.hpp"

using namespace std;

namespace CATSMAT {

    class CATSMAT_count : public CLI::SingleMode {
    public:
        const string kFileSwitch = "file";
        const string kDirectorySwitch = "directory";
        const string kConfigSwitch = "config";
        const string kDefaultConfigFlag = "default_config";
        const string kOutputFileSwitch = "output_file";
        const string kIntervalSearchFlag = "interval"; //default
        const string kGeneralisedIntervalSearchFlag = "generalised";
        const string kContourSearchFlag = "contour";
        const string kPitchSearchFlag = "pitch";
        const string kDyadSearchFlag = "dyad";
        const string kSonoritySearchFlag = "sonority";
        const string kTrigramSearchFlag = "trigram";
        const string kDuples = "duples";
        const string kXScoreSearchFlag = "cross_score_search"; //default is false (0)
        const string kDissonancesFlag = "include_dissonances"; //for dyad and trigram searches only
        const string kRepeatsFlag = "include_repeats"; //ignore repeated pitches and dyads
        const string kGeneral = "general";

        CLI::Switch file_{kFileSwitch, "", "File to operate on", "f"};
        CLI::Switch directory_{kDirectorySwitch, "", "Directory to operate on", "d"};
        CLI::Switch config_{kConfigSwitch, "", "Configuration file listing files to operate on", "k"};
        CLI::Switch output_file_        {kOutputFileSwitch, "out.txtleo", "Results output file", "o"};

        CLI::Flag   default_config_{kDefaultConfigFlag, "0",
                                  "Use configuration file in HOME directory listing files to operate on", "K"};

        CLI::Flag interval_             {kIntervalSearchFlag, "0", "Count intervals", "i"};
        CLI::Flag generalised_interval_ {kGeneralisedIntervalSearchFlag, "0", "Count generalised intervals", "g"};
        CLI::Flag contour_              {kContourSearchFlag, "0", "Count contours", "c"};
        CLI::Flag pitch_                {kPitchSearchFlag, "0", "Count pitches", "p"};
        CLI::Flag dyad_                 {kDyadSearchFlag, "0", "Count dyads", "y"};
        CLI::Flag sonority_             {kSonoritySearchFlag, "0", "Count sonorities", "s"};
        CLI::Flag trigram_              {kTrigramSearchFlag, "0", "Count trigrams", "t"};
        CLI::Flag duples_               {kDuples, "0", "Search across scores", "D"};
        CLI::Flag x_score_search_       {kXScoreSearchFlag, "0", "Search across scores", "x"};
        CLI::Flag include_dissonances_  {kDissonancesFlag, "0", "Include dissonances (default: off). On = 1, Off = 0", "D"};
        CLI::Flag include_repeats_      {kRepeatsFlag, "0", "Include repeats (default: off). On = 1, Off = 0", "r"};
        CLI::Flag general_              {kGeneral, "0", "General element count", "G"};

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

        CATSMAT_count(const int argc, const char **argv)
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
            Register(&output_file_);

            Register(&interval_);
            Register(&generalised_interval_);
            Register(&contour_);
            Register(&pitch_);
            Register(&dyad_);
            Register(&sonority_);
            Register(&trigram_);
            Register(&duples_);
            Register(&x_score_search_);
            Register(&include_dissonances_);
            Register(&include_repeats_);
            Register(&general_);

            Register(&version_, &copyright_);
        }

        virtual int main();
    };
}



#endif //CATSMAT_CATSMAT_COUNT_H
