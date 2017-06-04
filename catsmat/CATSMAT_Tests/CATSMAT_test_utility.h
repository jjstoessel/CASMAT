//
//  CATSMAT_test_utility.h
//  imusant
//
//  Created by Derrick Hill on 5/07/2015.
//
//

#ifndef __imusant__CATSMAT_test_utility__
#define __imusant__CATSMAT_test_utility__

#include "CATSMAT_collectionvisitor.h"
#include "CATSMAT_dyad_sequences.h"
#include "CATSMAT_dyadtuple_sequences.h"
#include "CATSMAT_sonority_sequences.h"
#include "CATSMAT_TrigramSequences.h"

#include <boost/filesystem.hpp>
#include "gtest/gtest.h"

using namespace boost;
using namespace CATSMAT;

class CATSMAT_test_utility {
    
public:
    
    CATSMAT_test_utility()
    {
        _root_test_data_dir_name = "testdata";
    }
    
    CATSMAT_test_utility(string root_test_data_dir_name)
    {
        _root_test_data_dir_name = root_test_data_dir_name;
    }
    
    filesystem::path MakePathToTestData(string relative_path) const;
    filesystem::path MakePathToTestFile(string relative_path_to_test_data_file);
    
    S_IMUSANT_score InitialiseScoreFromFile(string relative_path) const;
    
    S_CATSMAT_cp_matrix ConvertImusantscoreToCpmatrix(S_IMUSANT_score imusant_score) const;
    S_CATSMAT_cp_matrix ConvertMusicXmlToCpmatrix(string relative_path_to_xml_file) const;
    
    string ConvertCpmatrixToString(S_CATSMAT_cp_matrix the_matrix) const;
    string ConvertDyadSequencesToString(CATSMAT_dyad_sequences the_dyad_sequences) const;
    string ConvertDyadtupleSequencesToString(CATSMAT_dyadtuple_sequences the_dyadtuple_sequences) const;
    string ConvertSonoritySequencesToString(CATSMAT_sonority_sequences the_sonority_sequences ) const;
    string ConvertNGramSequencesToString(CATSMAT_TrigramSequences the_dyad_sequences) const;
    
    unsigned long GetNumPartsInScore(S_IMUSANT_score imusant_score) const;
    IMUSANT_note & CreateNote(IMUSANT_pitch::type note_name, int octave, TRational note_duration) const;
    
    const string ERR_MSG_FAILED_TO_PARSE_XML =
    "Failed to parse XML file. \nHave you added this file into the Copy Files build phase?";
    
    void DiffActualAndExpected(string actual, string expected);
    
    bool equalWithinTollerance(float f1, float f2);
    bool checkEqualWithinTolleranceField(double expected, double actual, int index_pos);
    
private:
    string GetTempFilePath();
    void DiffFiles(string file1, string file2 );
    void ExecuteSystemCommand(string system_command);
    void OutputDiffResult(string temp_output_file_path);
    
    string _root_test_data_dir_name;

};


#endif
