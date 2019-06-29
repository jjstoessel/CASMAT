//
// Created by Jason Stoessel on 11/09/2017.
//

#include "CATSMAT_count.h"
#include "CATSMAT_processing.h"
#include "CATSMAT_scoredatacollector.h"
#include <fstream>

using namespace CATSMAT;

int CATSMAT_count::main() {

    try {

        CATSMAT_processing processor;

        auto filename = ArgV.get<std::string>(kFileSwitch);
        auto directory = ArgV.get<std::string>(kDirectorySwitch);
        auto config_file = ArgV.get<std::string>(kConfigSwitch);
        bool default_config = ArgV.get<bool>(kDefaultConfigFlag);
        auto output_file = ArgV.get<std::string>(kOutputFileSwitch);
        bool interval_flag = ArgV.get<bool>(kIntervalSearchFlag);
        bool generalised_interval_flag = ArgV.get<bool>(kGeneralisedIntervalSearchFlag);
        bool contour_flag = ArgV.get<bool>(kContourSearchFlag);
        bool pitch_flag = ArgV.get<bool>(kPitchSearchFlag);
        bool interval_pitches_flag = ArgV.get<bool>(kIntervalPitchesFlag);
        bool dyad_search_flag = ArgV.get<bool>(kDyadSearchFlag);
        bool sonority_search_flag = ArgV.get<bool>(kSonoritySearchFlag);
        bool trigram_search_flag = ArgV.get<bool>(kTrigramSearchFlag);
        bool trigram_table_flag = ArgV.get<bool>(kTrigramTableSearchFlag);
        bool duples_flag = ArgV.get<bool>(kDuples);
        bool x_score_search_flag = ArgV.get<bool>(kXScoreSearchFlag);
        bool include_dissonances = ArgV.get<bool>(kDissonancesFlag);
        bool include_repeats = ArgV.get<bool>(kRepeatsFlag);
        bool general_flag = ArgV.get<bool>(kGeneral);

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

            if (contour_flag) {
                if (duples_flag) {
                    processor.FindMelodicDirectionDupleCounts(); //old option R
                } else {
                    processor.FindMelodicDirectionCounts(); //old option X
                }
            }

            if (trigram_search_flag) {
                if (x_score_search_flag) { //old option W
                    processor.FindSummativeTrigramCounts(!include_dissonances, !include_repeats);
                } else { //old option V
                    processor.FindTrigramCounts(!include_dissonances, !include_repeats);
                }
            }

            if (trigram_table_flag)
            {
                processor.FindSummativeTrigramCountsByPart(!include_dissonances, !include_repeats);
            }

            CATSMAT_scoredatacollector scoredatacollection;
            scoredatacollection.Visit(processor);

            if (interval_flag) {
                for (auto scoredata : scoredatacollection.get()) {
                    scoredata->PrintTitle(std::cout);
                    scoredata->score_interval_profile().print(std::cout);
                }
            }

            if (generalised_interval_flag)
            {
                for (auto scoredata : scoredatacollection.get()) {
                    scoredata->PrintTitle(std::cout);
                    scoredata->score_generalised_interval_profile().print(std::cout);
                }
            }

            if (interval_pitches_flag)
            {
                processor.FindPitchIntervalCounts();
            }


            if (contour_flag) {
                for (auto scoredata : scoredatacollection.get()) {
                    scoredata->PrintTitle(std::cout);
                    scoredata->score_contour_symbol_profile().print(std::cout);
                }
            }

            if (pitch_flag) {
                for (auto scoredata : scoredatacollection.get()) {
                    scoredata->PrintTitle(std::cout);
                    scoredata->score_pitch_profile().print(std::cout);
                }
            }

            if (dyad_search_flag) {
                for (auto scoredata : scoredatacollection.get()) {
                    //to do
                }
            }

            if (general_flag) {

                cout << scoredatacollection;
                //quick output mechanism for now. Need to get file name and dir from user in future.
                std::ofstream out(output_file);
                if (out.is_open()) {
                    out << scoredatacollection;
                    out.close();
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
