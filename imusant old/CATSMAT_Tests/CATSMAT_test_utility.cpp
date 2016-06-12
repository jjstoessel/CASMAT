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

#include "CATSMAT_test_utility.h"


SScore
CATSMAT_test_utility::ConvertMusicXmlToSscore(filesystem::path music_xml_file) const
{
    TMusicXMLFile reader;
    SScore xml_score = reader.read((string&)music_xml_file);
    return xml_score;
}

S_IMUSANT_score
CATSMAT_test_utility::ConvertSscoreToImusantscore(SScore xml_score) const
{
    TXML2IMUSANTVisitor xml_2_imusant_translator;
    xml_score->accept(xml_2_imusant_translator);
    S_IMUSANT_score imusant_score = xml_2_imusant_translator.get_imusant_score();
    return imusant_score;
}

unsigned long
CATSMAT_test_utility::GetNumPartsInScore(S_IMUSANT_score imusant_score) const
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
    filesystem::path full_path = MakePathToTestData(relative_path_to_xml_file);
    
    SScore xml_score = ConvertMusicXmlToSscore(full_path);
    S_IMUSANT_score imusant_score = ConvertSscoreToImusantscore(xml_score);
    CATSMAT::S_CATSMAT_cp_matrix the_matrix = ConvertImusantscoreToCpmatrix(imusant_score);
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
    boost::filesystem::path temp = boost::filesystem::temp_directory_path();
    boost::filesystem::path temp_file_name = boost::filesystem::unique_path();
    
    temp /= temp_file_name;
    temp.replace_extension(".txt");
    
    // cout << "Temp file is: " << temp.string() << endl;
    
    return temp.string();
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

IMUSANT_note &
CATSMAT_test_utility::CreateNote(IMUSANT_pitch::type note_name, int octave, TRational note_duration) const
{
    S_IMUSANT_pitch pitch = new_IMUSANT_pitch();
    pitch->set(note_name, octave, 1);
    
    S_IMUSANT_duration duration = new_IMUSANT_duration();
    duration->set(note_duration, 0);
    
    const long FIRST_NOTE_IN_MEASURE = 1;
    long note_index = FIRST_NOTE_IN_MEASURE;
    
    IMUSANT_note *note = new IMUSANT_note();
    
    note->setNoteIndex(note_index);
    note->setPitch(pitch);
    note->setDuration(duration);
    
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
