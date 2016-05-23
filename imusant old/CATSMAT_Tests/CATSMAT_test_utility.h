//
//  CATSMAT_test_utility.h
//  imusant
//
//  Created by Derrick Hill on 5/07/2015.
//
//

#ifndef __imusant__CATSMAT_test_utility__
#define __imusant__CATSMAT_test_utility__

#include "CATSMAT_collectionvisitor.hpp"
#include "CATSMAT_dyad_sequences.hpp"
#include "CATSMAT_dyadtuple_sequences.hpp"

// #include "CATSMAT_cp_matrix_Expected.h"

#include "TMusicXMLFile.h"
#include "TXML2IMUSANTVisitor.h"

#include <boost/filesystem.hpp>
#include "gtest/gtest.h"

using namespace boost;
using namespace CATSMAT;

class CATSMAT_test_utility {
    
public:
    
    filesystem::path MakePathToTestData(string relative_path) const;
  
    SScore ConvertMusicXmlToSscore(filesystem::path music_xml_file) const;
    S_IMUSANT_score ConvertSscoreToImusantscore(SScore xml_score) const;
    S_CATSMAT_cp_matrix ConvertImusantscoreToCpmatrix(S_IMUSANT_score imusant_score) const;
    S_CATSMAT_cp_matrix ConvertMusicXmlToCpmatrix(string relative_path_to_xml_file) const;
    
    string ConvertCpmatrixToString(S_CATSMAT_cp_matrix the_matrix) const;
    string ConvertDyadSequencesToString(CATSMAT_dyad_sequences the_dyad_sequences) const;
    string ConvertDyadtupleSequencesToString(CATSMAT_dyadtuple_sequences the_dyadtuple_sequences) const;
    
    unsigned long GetNumPartsInScore(S_IMUSANT_score imusant_score) const;
    IMUSANT_note & CreateNote(IMUSANT_pitch::type note_name, int octave, TRational note_duration) const;
    
    const string ERR_MSG_FAILED_TO_PARSE_XML =
    "Failed to parse XML file. \nHave you added this file into the Copy Files build phase?";
    
    void DiffActualAndExpected(string actual, string expected);
    
private:
    string GetTempFilePath();
    void DiffFiles(string file1, string file2 );
    void ExecuteSystemCommand(string system_command);
    void OutputDiffResult(string temp_output_file_path);

};


#endif
