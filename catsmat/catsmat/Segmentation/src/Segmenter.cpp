//
// Created by Jason Stoessel on 15/9/17.
//

#include "Segmenter.h"
#include "GeneralAnalysis/inc/CATSMAT_processing.h"
#include "LBDM_Segmenter.h"
#include "FP_Segmenter.h"

using namespace CATSMAT;

int Segmenter::main() {

    try {

        CATSMAT_processing processor;

        auto filename = ArgV.get<std::string>(kFileSwitch);
        auto directory = ArgV.get<std::string>(kDirectorySwitch);
        auto config_file = ArgV.get<std::string>(kConfigSwitch);
        bool default_config = ArgV.get<bool>(kDefaultConfigFlag);
        auto output_file = ArgV.get<std::string>(kOutputFileSwitch);
        bool LBDM = ArgV.get<bool>(kLowerBoundaryDetectionModelSegmentationFlag);
        bool isoperiodic = ArgV.get<bool>(kIsoperiodicSegmentationFlag);

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

            if (LBDM) { //old option H

                vector<S_IMUSANT_segmented_part_LBDM> segmented_parts;

                SetOfSegment segmentation_result;
                LBDM_Segmenter segmenter(segmentation_result);
                segmenter.Visit(processor);


                cout << "ORIGINAL IMPLEMENTATION USING vector<S_IMUSANT_segmented_part_LBDM>" << endl;
                segmented_parts = segmenter.getSegmentedParts();
                for (vector<S_IMUSANT_segmented_part_LBDM>::iterator seg_part_iter = segmented_parts.begin(); seg_part_iter != segmented_parts.end() ; seg_part_iter++)
                {
                    cout << ((*seg_part_iter)->print(true,true)) << endl;
                }

                cout << "NEW IMPLEMENTATION USING SetOfSegment segmentation_result" << endl;
                cout << "Not working because LBDM_SegmentedPart does not yet implement the use of the segmentation_results input parameter." << endl;


                cout << segmentation_result << endl;
            }

            if (isoperiodic) { //old option T

                SetOfSegment segmentation_results;
                FP_Segmenter segmenter(segmentation_results);
                segmenter.Visit(processor);

                FP_Segmenter::SetOfSegmentsVector segments = segmenter.getSegmentSets();
                for (FP_Segmenter::SetOfSegmentsVector::iterator segment_set_iter = segments.begin();
                     segment_set_iter != segments.end() ;
                     segment_set_iter++)
                {
                    cout << *segment_set_iter << endl;
                    cout << endl << endl;
                }

                cout << "Format for using this data with R:" << endl;
                bool first_time_round = true;
                for (FP_Segmenter::SetOfSegmentsVector::iterator segment_set_iter = segments.begin();
                     segment_set_iter != segments.end() ;
                     segment_set_iter++)
                {
                    cout << segment_set_iter->printProperties(first_time_round);
                    first_time_round = false;
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