//
// Created by Jason Stoessel on 2019-06-07.
//

#ifndef CATSMAT_CATSMAT_GENERAL_H
#define CATSMAT_CATSMAT_GENERAL_H

#include "Commando/inc/MultiMode.hpp"

using namespace std;

namespace CATSMAT
{

    class CATSMAT_general : public CLI::SingleMode {
            public:

            const string kFileSwitch = "file";
            const string kDirectorySwitch = "directory";
            const string kConfigSwitch = "config";
            const string kOutputFileSwitch = "output_file";
            const string kDefaultConfigFlag = "default_config";
            const string kIntervalSearchFlag = "interval"; //default
            const string kGeneralisedIntervalSearchFlag = "generalised";
            const string kContourSearchFlag = "contour";
            const string kPitchSearchFlag = "pitch";
            const string kDyadSearchFlag = "dyad";
            const string kSonoritySearchFlag = "sonority";
            const string kTrigramSearchFlag = "trigram";
            const string kDissonancesFlag = "include_dissonances"; //for dyad and trigram searches only
            const string kRepeatsFlag = "include_repeats"; //ignore repeated pitches and dyads
            const string kCanonicVoicesOnlyFlag = "canon_voices";

            CLI::Switch file_               {kFileSwitch, "", "File to operate on", "f"};
            CLI::Switch directory_          {kDirectorySwitch, "", "Directory to operate on", "d"};
            CLI::Switch config_             {kConfigSwitch, "", "Configuration file listing files to operate on", "k"};
            CLI::Switch output_file_        {kOutputFileSwitch, "out.txt", "Results output file", "o"};
            CLI::Flag default_config_       {kDefaultConfigFlag, "0", "Use configuration file in HOME directory listing files to operate on", "K"};

            //different type searches
            CLI::Flag interval_             {kIntervalSearchFlag, "0", "Output all intervals", "i"};
            CLI::Flag generalised_interval_ {kGeneralisedIntervalSearchFlag, "0", "Output all generalised interval", "g"};
            CLI::Flag contour_              {kContourSearchFlag, "0", "Output all contour", "c"};
            CLI::Flag pitch_                {kPitchSearchFlag, "0", "Output all pitches", "p"};
            CLI::Flag dyad_                 {kDyadSearchFlag, "0", "Output all dyads", "y"};
            CLI::Flag sonority_             {kSonoritySearchFlag, "0", "Output all sonorities", "s"};
            CLI::Flag trigram_              {kTrigramSearchFlag, "0", "Output all trigrams", "t"};

            //other options
            CLI::Flag include_dissonances_  {kDissonancesFlag, "0", "Include dissonances (default: off). On = 1, Off = 0", "D"};
            CLI::Flag include_repeats_      {kRepeatsFlag, "0", "Include repeats (default: off). On = 1, Off = 0", "r"};
            CLI::Flag canonic_voices_       {kCanonicVoicesOnlyFlag, "0", "Include canonic voices only. On = 1, Off = 0", "r"};

            CLI::Terminator version_ {"version", "show version info",
                                      "CATSMAT_repeats (1.0.0)\nCopyright (c) Jason Stoessel 2018. All rights reserved."
                                      "\nGNU General Public License v3.0\nThis is free software; see the source for"
                                      " copying conditions.  There is NO\nwarranty; not even for MERCHANTABILITY or"
                                      " FITNESS FOR A PARTICULAR PURPOSE.", "V"};

            CLI::Terminator copyright_ {"copyright", "show copyright info",
                                        "CATSMAT_repeats (1.0.1)\nCopyright (c) Jason Stoessel 2018. All rights reserved."
                                        "\nGNU General Public License v3.0\nThis is free software; see the source for"
                                        " copying conditions.  There is NO\nwarranty; not even for MERCHANTABILITY or"
                                        " FITNESS FOR A PARTICULAR PURPOSE.", "C"};

            CATSMAT_general(const int argc, const char **argv)
            : SingleMode(argc, argv,
                         "Convert symbolic music into list of other elements. Give one of the above subcommands "
                         "with no arguments for their respective usage, or pass the -h, --help flag "
                         "for more information alone or with one of the above subcommands.",
                         "Report bugs to: jason.stoessel@une.edu.au\n"
                         "CATSMAT home page: <https://github.com/jjstoessel/CATSMAT>")
            {
                Register(&file_);
                Register(&directory_);
                Register(&config_);
                Register(&output_file_);
                Register(&default_config_);
                Register(&interval_);
                Register(&generalised_interval_);
                Register(&contour_);
                Register(&pitch_);
                Register(&dyad_);
                Register(&sonority_);
                Register(&trigram_);
                Register(&include_dissonances_);
                Register(&include_repeats_);
                Register(&canonic_voices_);
                Register(&version_, &copyright_);
            }

            virtual int main();

    };

}
#endif //CATSMAT_CATSMAT_GENERAL_H
