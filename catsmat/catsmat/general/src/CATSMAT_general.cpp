//
// Created by Jason Stoessel on 2019-06-07.
//

#include "CATSMAT_general.h"
#include "CATSMAT_sonority_sequences.h"
#include "CATSMAT_processing.h"

using namespace CATSMAT;

int CATSMAT_general::main()
{
    try
    {

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
        bool include_dissonances = ArgV.get<bool>(kDissonancesFlag);
        bool include_repeats = ArgV.get<bool>(kRepeatsFlag);
        bool canonic_voices_only = ArgV.get<bool>(kCanonicVoicesOnlyFlag);

        if (!filename.empty())
        {
            processor.addRelativeFile(filename);
        }

        if (!directory.empty())
        {
            processor.processRelativeDirectoryFiles(directory);
        }

        if (!config_file.empty()) {

        } else if (default_config)
        {
            processor.addFilesFromFixedConfigFile();
        }

        if (!processor.getScores().empty())
        {
            if (contour_flag)
            {
                for (auto score : processor.getScores())
                {
                    CATSMAT_collection_visitor      score_to_matrix_translator;
                    CATSMAT_sonority_sequences      sonorities;

                    if (score != nullptr)
                    {
                        (*score).accept(score_to_matrix_translator);
                        score_to_matrix_translator.getCPMatrix()->Accept(sonorities);

                        cout << (*score).getMovementTitle() << endl;
                        cout << sonorities << endl;
                    }

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
