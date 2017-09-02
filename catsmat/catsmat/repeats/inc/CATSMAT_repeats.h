//
// Created by Jason James Stoessel on 27/08/2017.
//

#ifndef CATSMAT_CATSMAT_REPEATS_H
#define CATSMAT_CATSMAT_REPEATS_H

#include "Commando/inc/MultiMode.hpp"

/* repeated_substrings - interval (-i), generalised interval (-g), contour_type (-c), pitches (-p), dyads (-d),
 * trigrams (-3) using the current IMUSANT_<type>SuffixTreeBuilder type and FindAndPrintRepeatedSubstrings member
 * function, or processor->FindRepeatedDyadSequences or processor->FindRepeatedTrigramSequences.
 * (It may be useful to add processor member functions for options -i, -c, and -p. Note there needs
 * to be an option (-s)[s for score] or (-x) across option, and a ignore dissonances and ignore repeated
 * (pitches, dyads only) here.) Note that repeated dyadtuple sequences option will be removed:
 * it is not currently implemented. This tool is for finding repeated substrings in scores and over corpuses of scores.
 */

/*class CATSMAT_repeats_required : public CLI::SingleMode
{
public:
    //CLI::Required file_director_or_config {"file_dir_config", "The name of a file, directory or config file"};
    CLI::Flag interval_flag {"interval", "1", "Search for repeated interval substrings", "i"};
    CLI::Flag generalised_interval_flag {"generalised", "1", "Search for repeated generalised interval substrings", "g"};
    CLI::Flag contour_flag {"contour", "O", "Search for repeated contour substrings", "c"};

    CATSMAT_repeats_required(const int argc, const char **argv)
            : SingleMode(argc, argv, "Required")
    {
        //Register(&file_director_or_config);
        Register(&interval_flag);
        Register(&generalised_interval_flag);
        Register(&contour_flag);
    }
    virtual int main();
};*/



class CATSMAT_repeats : public CLI::SingleMode {
public:

    CLI::Switch file_               {"file", "1", "File to operate on", "f"};
    CLI::Switch directory_          {"directory", "1", "Directory to operate on", "d"};
    CLI::Switch config_             {"config", "1", "Configuration file listing files to operate on", "x"};
    CLI::Flag interval_             {"interval", "1", "Search for repeated interval substrings", "i"};
    CLI::Flag generalised_interval_ {"generalised", "1", "Search for repeated generalised interval substrings", "g"};
    CLI::Flag contour_              {"contour", "O", "Search for repeated contour substrings", "c"};

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

    CATSMAT_repeats(const int argc, const char **argv)
            : SingleMode(argc, argv,
                        "Search for repeated substrings in symbolic music. Give one of the above subcommands "
                                "with no arguments for their respective usage, or pass the -h, --help flag "
                                "for more information alone or with one of the above subcommands.",
                        "Report bugs to: jason.stoessel@une.edu.au\n"
                                "CATSMAT home page: <https://github.com/jjstoessel/CATSMAT>")
    {
        Register(&file_);
        Register(&directory_);
        Register(&config_);
        Register(&interval_);
        Register(&generalised_interval_);
        Register(&contour_);
        Register(&version_, &copyright_);
    }

    virtual int main();
};


#endif //CATSMAT_CATSMAT_REPEATS_H
