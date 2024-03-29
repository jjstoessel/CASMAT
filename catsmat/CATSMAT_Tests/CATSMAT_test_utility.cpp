 //
//  CATSMAT_test_utility.cpp
//  imusant
//
//  Created by Derrick Hill on 5/07/2015.
//
//

#include <stdlib.h>  // for system()
#include <iostream>
#include <fstream>
#include <string>

#include <math.h>


#include "IMUSANT_processing.h"

#include "CATSMAT_test_utility.h"


S_IMUSANT_score
CATSMAT_test_utility::
InitialiseScoreFromFile(string relative_path) const
{
    filesystem::path file_path = MakePathToTestData(relative_path);
    
    IMUSANT_processing parser;
    S_IMUSANT_score parser_test_score = parser.addFile(file_path);
    return parser_test_score;
}


unsigned long
CATSMAT_test_utility::
GetNumPartsInScore(S_IMUSANT_score imusant_score) const
{
    IMUSANT_vector<S_IMUSANT_part> parts = imusant_score->partlist()->parts();
    unsigned long num_parts_in_score = parts.size();
    return num_parts_in_score;
}

CATSMAT::S_CATSMAT_cp_matrix
CATSMAT_test_utility::ConvertImusantscoreToCpmatrix(S_IMUSANT_score imusant_score) const
{
    CATSMAT::CATSMAT_collection_visitor imusant_to_cp_matrix_translator;
    imusant_score->accept(imusant_to_cp_matrix_translator);
    CATSMAT::S_CATSMAT_cp_matrix matrix = imusant_to_cp_matrix_translator.getCPMatrix();
    return matrix;
}

CATSMAT::S_CATSMAT_cp_matrix
CATSMAT_test_utility::ConvertMusicXmlToCpmatrix(string relative_path_to_xml_file) const
{
    S_IMUSANT_score the_score = InitialiseScoreFromFile(relative_path_to_xml_file);
    CATSMAT::S_CATSMAT_cp_matrix the_matrix = ConvertImusantscoreToCpmatrix(the_score);
    return the_matrix;
}

string
CATSMAT_test_utility::ConvertCpmatrixToString(CATSMAT::S_CATSMAT_cp_matrix the_matrix) const
{
    std::stringstream the_matrix_as_stringstream;
    the_matrix_as_stringstream << the_matrix;
    std::string the_matrix_as_string = the_matrix_as_stringstream.str();
    return the_matrix_as_string;
}

string
CATSMAT_test_utility::ConvertDyadSequencesToString(CATSMAT::CATSMAT_dyad_sequences the_dyad_sequences) const
{
    std::stringstream the_dyads_as_stringstream;
    the_dyads_as_stringstream << the_dyad_sequences;
    std::string the_dyads_as_string = the_dyads_as_stringstream.str();
    return the_dyads_as_string;
}


void
CATSMAT_test_utility::DiffActualAndExpected(string actual, string expected)
{
    // Send the strings to files so that we can use UNIX diff to compare them.
    
    string actual_file_path = GetTempFilePath();
    string expected_file_path = GetTempFilePath();
    
    cout << "Actual file: " << actual_file_path << endl;
    cout << "Expected file: " << expected_file_path << endl;
    
    ofstream actual_file(actual_file_path);
    ofstream expected_file(expected_file_path);
    
    actual_file << actual << endl;
    expected_file << expected << endl;
    
    DiffFiles(actual_file_path, expected_file_path);
}

void
CATSMAT_test_utility::DiffFiles(string actual_file_path, string expected_file_path)
{
    // Run UNIX diff and send the output to the screen
    string temp_output_file_path = GetTempFilePath();

    string command = "diff -a --text " + actual_file_path + " " + expected_file_path + " > " + temp_output_file_path;
    
    ExecuteSystemCommand(command);
    OutputDiffResult(temp_output_file_path);
}

string
CATSMAT_test_utility::GetTempFilePath()
{
    string ret_val = tmpnam(nullptr);
#ifdef VERBOSE
    cout << "Temp file is: " << ret_val << endl;
#endif

    return ret_val;
}

void
CATSMAT_test_utility::ExecuteSystemCommand(string system_command)
{
    if (! std::system(NULL))
    {
        cerr << "CATSMAT_test_utility::ExecuteSystemCommand() - system() call not available" << endl;
        throw "CATSMAT_test_utility::ExecuteSystemCommand() - system() call not available";
    }
    
    int status;
    status = std::system(system_command.c_str());
    
    if (status < 0)
    {
        cout << "CATSMAT_test_utility::ExecuteSystemCommand() - Error: " << strerror(errno) << endl;
        throw "CATSMAT_test_utility::ExecuteSystemCommand() - Error";
    }
    else
    {
        if (! WIFEXITED(status))
        {
            cout << "CATSMAT_test_utility::ExecuteSystemCommand() - Program exited abnormaly\n";
            throw "CATSMAT_test_utility::ExecuteSystemCommand() - Program exited abnormaly";
        }
    }
}

void
CATSMAT_test_utility::OutputDiffResult(string temp_output_file_path)
{
    string line;
    ifstream myfile (temp_output_file_path);
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            cout << line << endl;
        }
        myfile.close();
    }
    else
    {
        cout << "CATSMAT_test_utility::OutputDiffResult() - Unable to open file" << endl;
    }
    cout << endl;
}

string
CATSMAT_test_utility::ConvertDyadtupleSequencesToString(CATSMAT_dyadtuple_sequences the_dyadtuple_sequences) const
{
    std::stringstream the_dyadtuples_as_stringstream;
    the_dyadtuples_as_stringstream << the_dyadtuple_sequences;
    std::string the_dyadtuples_as_string = the_dyadtuples_as_stringstream.str();
    return the_dyadtuples_as_string;
}

filesystem::path
CATSMAT_test_utility::MakePathToTestData(string relative_path) const
{
    filesystem::path testdata(filesystem::initial_path());
    testdata.append("testdata");
    testdata.append(relative_path);
    return testdata;
}

filesystem::path
CATSMAT_test_utility::
MakePathToTestFile(string relative_path_to_test_data_file)
{
    filesystem::path testdata(filesystem::initial_path());
    testdata.append(_root_test_data_dir_name);
    testdata.append(relative_path_to_test_data_file);
    return testdata;
}

IMUSANT_note &
CATSMAT_test_utility::CreateNote(IMUSANT_pitch::type note_name, int octave, TRational note_duration) const
{
    S_IMUSANT_pitch pitch = new_IMUSANT_pitch();
    pitch->set(note_name, octave, 1);
    
    S_IMUSANT_duration duration = new_IMUSANT_duration();
    duration->set(note_duration, 0);
    
    const int FIRST_NOTE_IN_MEASURE = 1;
    int note_index = FIRST_NOTE_IN_MEASURE;
    
    IMUSANT_note *note = new IMUSANT_note();
    
    note->setNoteIndex(note_index);
    note->setPitch(*pitch);
    note->setDuration(*duration);
    
    return *note;
}

string
CATSMAT_test_utility::ConvertSonoritySequencesToString(CATSMAT_sonority_sequences the_sonority_sequences ) const
{
    std::stringstream the_sonorities_as_stringstream;
    the_sonorities_as_stringstream << the_sonority_sequences;
    std::string the_sonorities_as_string = the_sonorities_as_stringstream.str();
    return the_sonorities_as_string;
}

string
CATSMAT_test_utility::ConvertNGramSequencesToString(CATSMAT_TrigramSequences the_trigram_sequences) const
{
    std::stringstream the_trigrams_as_stringstream;
    the_trigrams_as_stringstream << the_trigram_sequences;
    std::string the_dyads_as_string = the_trigrams_as_stringstream.str();
    return the_dyads_as_string;
}

bool
CATSMAT_test_utility::
equalWithinTollerance(float f1, float f2)
{
    return (fabs(f1 - f2) < 0.001);
}

bool
CATSMAT_test_utility::
checkEqualWithinTolleranceField(double expected, double actual, int index_pos)
{
    if (equalWithinTollerance(expected, actual))
        return true;
    else
    {
        cout << "Failed with jdex = " << index_pos
        << ". Expected " << expected
        << ". Received " << actual
        << endl;
        
        return false;
    }
};
