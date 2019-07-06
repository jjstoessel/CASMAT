//
// Created by Jason Stoessel on 9/9/17.
//

#include "CATSMAT_canonic_techniques.h"
#include "CATSMAT_processing.h"

using namespace CATSMAT;

int CATSMAT_canonic_techniques::main() {

    try {
        CATSMAT_processing processor;

        auto filename = ArgV.get<std::string>(kFileSwitch);
        auto directory = ArgV.get<std::string>(kDirectorySwitch);
        auto config_file = ArgV.get<std::string>(kConfigSwitch);
        bool default_config = ArgV.get<bool>(kDefaultConfigFlag);

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
            processor.ListCanonicTechniques(); //old option Z
            //add file output flag with file name option
        }

    }

    catch (std::exception &e)
    {
        cout << "Unexpected problem: " << e.what() << endl;
    }

    return 0;
}
