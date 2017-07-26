//
//  CATSMAT_Menu.cpp
//  imusant
//
//  Created by Derrick Hill on 6/12/2015.
//
//

#include "CATSMAT_menu.h"

#include <fstream>
#include <stdlib.h>
#include <exception>

#include "libIMUSANT.h"

#include "IMUSANT_interval_suffixtree_builder.h"
#include "IMUSANT_pitch_suffixtree_builder.h"
#include "IMUSANT_contour_suffixtree_builder.h"
#include "IMUSANT_LBDM_segmenter.h"
#include "IMUSANT_fixed_period_segmenter.h"

#include "CATSMAT_scoredatacollector.h"
#include "IMUSANT_vectormap_analysis_types.h"

using namespace std;
using namespace CATSMAT;
using namespace boost::filesystem;

void
CATSMAT_menu::
outputWelcomeMessage(ostream &out)
{
    out
    << "========================================================================" << endl
    << "|					 WELCOME TO CATSMAT, version 0.1					" << endl
    << "|           (Canonic Techniques Symbolic Musical Analysis Tool)         " << endl
    << "|																		" << endl
    << "|	Designers: Denis Collins, Jason Stoessel and Derrick Hill			" << endl
    << "|	Programming: Jason Stoessel	and Derrick Hill						" << endl
    << "|	Development Tool: Apple Computer's XCode version 6.1.1 (LLVM C++)   " << endl
    << "|                                                                       " << endl
    << "|   These symbolic musical analysis tools have been developed by        " << endl
    << "|   Chief Investigators Denis Collins and Jason Stoessel for their      " << endl
    << "|   project \"Canonic Techniques and Musical Change, from c.1330 to     " << endl
    << "|   c.1530\", funded by the Australian Research Council (DP150102135).  " << endl
    << "|	This software uses portions of code from the project \"The Meeting  " << endl
    << "|   of Computer Technology and Medieval Music: A Proto-type Software    " << endl
    << "|	Program for Analysis of Musical Intertextuality.\" (2006 University " << endl
    << "|	Research Grant, New England, Armidale, Australia) by Rex Eakins     " << endl
    << "|   and Jason Stoessel.                                                 " << endl
    << "|																		" << endl
    << "|	This program and its code remains the property of the authors and	" << endl
    << "|	where applicable, the University of New England and University of   " << endl
    << "|   Queensland. This program currently makes use of the following       " << endl
    << "|   libraries:                                                          " << endl
    << "|                                                                       " << endl
    << "|		1. MusicXML Library under the GNU Lesser General Public License " << endl
    << "|		2. Boost under Boost Software License (Open source license)		" << endl
    << "|       3. Google Test                                                  " << endl
    << "|																		" << endl
    << "|	The Music XML data format is used under the Royalty-free license	" << endl
    << "|	granted by Recordare LCC; see										" << endl
    << "|		http://www.recordare.com/dtds/license.html						" << endl
    << "|																		" << endl
    << "|	Conditions for those licenses apply to relavant portions of this	" << endl
    << "|	software. Newly created portions of this software and propriety		" << endl
    << "|	data formats are copyrighted by the designers and programmers.		" << endl
    << "|																		" << endl
    << "========================================================================" << endl << endl;
}

void
CATSMAT_menu::
addFilesToAnalyse(CATSMAT_processing *processor)
{
    bool finished = false;
    
    while (! finished)
    {
        cout << endl
        <<	"MAIN MENU" << endl
        <<  "Please select an option:" << endl
        <<	"  1 - Add a file..." << endl
        <<	"  2 - Add all files from a directory..." << endl
        <<  "  3 - Load files from the configuration file at $HOME/catsmat_config.txt" << endl
        <<  "  4 - Load files from a configuration file I select..." << endl
        <<  "  5 - Remove loaded scores from memory" << endl
        <<  "  8 - List the movements I have added so far..." << endl
        <<  "  9 - Analyze the files I have added..." << endl
        <<  "  0 - Exit program" << endl << endl;
    
        char selectedMenuItem = 'x';
        cin >> selectedMenuItem;
        cin.ignore();
        
        try
        {
            switch (selectedMenuItem)
            {
                case '1':
                    addUserSpecifiedFile(processor);
                    finished = false;
                    break;
                    
                case '2':
                    addFilesFromUserSpecifiedDirectory(processor);
                    finished = false;
                    break;
                    
                case '3':
                    addFilesFromFixedConfigFile(processor);
                    finished = false;
                    break;
                    
                case '4':
                    addFilesFromUserSelectedConfigurationFile(processor);
                    finished = false;
                    break;
                    
                case '5':
                    processor->Clear();
                    cout << "Scores unloaded" << endl;
                    finished = false;
                    break;
                    
                case '8':
                    listWorksAndMovementsAddedSoFar(processor);
                    finished = false;
                    break;
                    
                case '0':
                case '9':
                    finished = true;
                    break;
                    
                default:
                    cout << "Invalid selection. Please select a valid menu item." ;
                    finished = false;
            }
        }
        catch (std::exception& e)
        {
            finished = false;
            cout << "Unexpected problem: " << e.what() << endl;
            cout << "Have another go..." << endl << endl;
        }
    }
}


void
CATSMAT_menu::
outputToolsMenu(ostream &out)
{
    out << "IMUSANT ANALYSIS TOOLS" << endl;
    out << "A.  Find repeated interval substrings " << endl;
    out << "B.  Find repeated interval contour substrings " << endl;
    out << "C.  Find interval supermaximals " << endl;
    out << "D.  Find contour supermaximals " << endl;
    out << "E.  Find longest common intervallic subsequence in all pairs" << endl;
    out << "F.  Find longest common intervallic subsequence in all pairs (reverse method)" << endl;
    out << "G.  Find longest common pitch subsequence in all pairs" << endl;
    out << "H.  Find melodic segments using LBDM" << endl;
    out << "T.  Find melodic segments using Periodic Segmentation" << endl;
    out << "R.  Show melodic contours" << endl;
    out << "X.  Entabulate melodic contour duples for all works" << endl;
    out << "S.  Show general data" << endl;
    out << "I.  Run all IMUSANT tools" << endl;
    out << endl;
    out << "CATSMAT ANALYSIS TOOLS" << endl;
    out << "J. Find repeated dyad sequences in voice pairs" << endl;
    out << "K. Find repeated dyad sequences across voice pairs" << endl;
    out << "L. Find repeated dyadtuple sequences" << endl;
    out << "M. Find repeated sonority sequences" << endl;
    out << "T. Find melodic segments using period segmentation" << endl;
    out << "Q. Find all melodic segments using all the segmentation algorithms available" << endl;
    out << "U. Find repeated trigram sequences" << endl;
    out << "V. Give count of trigrams for each score" << endl;
    out << "W. Give count of trigrams for all scores" << endl;
    out << "Z. List canonic techniques for all scores" << endl;
    out << "N. Run all CATSMAT tools" << endl;
    out << endl;
    out << "O. Run all tools" << endl;
    out << "P.  Print all scores" << endl;
    out << endl;
    out << "Please select analysis tool (A - O; any other key to exit): " << endl;
    out << endl;
}


void
CATSMAT_menu::
runToolsMenu(CATSMAT_processing* processor)
{
    bool moreTools = true;
    IMUSANT_IntervalSuffixTreeBuilder  ip;
    IMUSANT_PitchSuffixTreeBuilder     pp;
    IMUSANT_ContourSuffixTreeBuilder   cp;
    IMUSANT_IntervalVectorMapAnalysis  iv;
    IMUSANT_PitchVectorMapAnalysis     pv;
    IMUSANT_ContourVectorMapAnalysis   cv;
    
    do
    {
        outputToolsMenu(cout);
        
        char tool, yn;
        bool continguous = false, ignoreDissonances=true, ignoreRepeatedDyads=true;
        int length = 5;
        cin >> tool;
        try {
        
            switch (tool)
            {
                //IMUSANT analysis tools
                //Find and print repeated interval substrings
                case 'A':
                case 'a':
                    ip.Visit(*processor);
                    cout << "Enter minimum length: ";
                    cin >> length;
                    cout << ip.FindAndPrintRepeatedSubstrings(length);
                    break;
                //Find and print repeated contours substrings
                case 'B':
                case 'b':
                    cout << "Enter minimum length: ";
                    cin >> length;
                    cp.Visit(*processor);
                    cout << cp.FindAndPrintRepeatedSubstrings(length);
                    break;
                //Find interval supermaximals
                case 'C':
                case 'c':
                    ip.Visit(*processor);
                    cout << ip.FindAndPrintSupermaximals(4,100); //length and percent need to be inputs
                    break;
                //Find contour supermaximals
                case 'D':
                case 'd':
                    cp.Visit(*processor);
                    cout << cp.FindAndPrintSupermaximals(4,100);
                    break;
                //Find longest common intervallic subsequence in all pairs
                case 'E':
                case 'e':
                    cout << "Only find continguous segments? (y/n) ";
                    cin >> yn;
                    if (yn == 'y') continguous = true;
                    iv.Visit(*processor);
                    cout << iv.FindAndPrintLCSPairs(continguous);
                    break;
                //Find longest common intervallic subsequence in all pairs (reverse method)
                case 'F':
                case 'f':
                    cout << "Only find continguous segments? (y/n) ";
                    cin >> yn;
                    if (yn == 'y') continguous = true;
                    iv.Visit(*processor);
                    cout << iv.FindAndPrintLCSPairs(continguous,true);
                    break;
                //Find longest common pitch subsequence in all pairs
                case 'G':
                case 'g':
                    cout << "Only find continguous segments? (y/n) ";
                    cin >> yn;
                    if (yn == 'y') continguous = true;
                    pv.Visit(*processor);
                    cout << pv.FindAndPrintLCSPairs(continguous);
                    break;
                //Find melodic segments using LBDM
                case 'H':
                case 'h':
                    {
                        vector<S_IMUSANT_segmented_part_LBDM> segmented_parts;
                        
                        IMUSANT_set_of_segment segmentation_result;
                        IMUSANT_LBDM_segmenter segmenter(segmentation_result);
                        segmenter.Visit(*processor);
                        
                        
                        cout << "ORIGINAL IMPLEMENTATION USING vector<S_IMUSANT_segmented_part_LBDM>" << endl;
                        segmented_parts = segmenter.getSegmentedParts();
                        for (vector<S_IMUSANT_segmented_part_LBDM>::iterator seg_part_iter = segmented_parts.begin(); seg_part_iter != segmented_parts.end() ; seg_part_iter++)
                        {
                            cout << ((*seg_part_iter)->print(true,true)) << endl;
                        }
                        
                        cout << "NEW IMPLEMENTATION USING IMUSANT_set_of_segment segmentation_result" << endl;
                        cout << "Not working because IMUSANT_segmented_part_LBDM does not yet implement the use of the segmentation_results input parameter." << endl;
                        
                        
                        cout << segmentation_result << endl;
                        
                    }
                    break;
                    
                    //Find melodic segments using Periodic Segmentation
                case 'T':
                case 't':
                {
                    IMUSANT_set_of_segment segmentation_results;
                    IMUSANT_fixed_period_segmenter segmenter(segmentation_results);
                    segmenter.Visit(*processor);
                    
                    IMUSANT_fixed_period_segmenter::SetOfSegmentsVector segments = segmenter.getSegmentSets();
                    for (IMUSANT_fixed_period_segmenter::SetOfSegmentsVector::iterator segment_set_iter = segments.begin();
                         segment_set_iter != segments.end() ;
                         segment_set_iter++)
                    {
                        cout << *segment_set_iter << endl;
                        cout << endl << endl;
                    }
                    
                    cout << "Format for using this data with R:" << endl;
                    bool first_time_round = true;
                    for (IMUSANT_fixed_period_segmenter::SetOfSegmentsVector::iterator segment_set_iter = segments.begin();
                         segment_set_iter != segments.end() ;
                         segment_set_iter++)
                    {
                        cout << segment_set_iter->printProperties(first_time_round);
                        first_time_round = false;
                    }
                    
                    
                }
                break;
                    
                case 'Q':
                case 'q':
                {
                    IMUSANT_set_of_segment segmentation_results;
                    
                    IMUSANT_fixed_period_segmenter fp_segmenter(segmentation_results);
                    fp_segmenter.Visit(*processor);
                    
                    IMUSANT_LBDM_segmenter lbdm_segmenter(segmentation_results);
                    lbdm_segmenter.Visit(*processor);
                    
                    // output the segmentation_results here...
                    
                    break;
                }
               
                //Run all IMUSANT tools
                case 'I':
                case 'i':
                    ip.Visit(*processor);
                    cp.Visit(*processor);
                    pp.Visit(*processor);
                    iv.Visit(*processor);
                    pv.Visit(*processor);
                    
                    cout << ip.FindAndPrintRepeatedSubstrings();
                    cout << cp.FindAndPrintRepeatedSubstrings();
                    cout << ip.FindAndPrintSupermaximals(4,100);
                    cout << cp.FindAndPrintSupermaximals(4,100);
                    cout << iv.FindAndPrintLCSPairs(false);
                    cout << pv.FindAndPrintLCSPairs(false);
                    cout << iv.FindAndPrintLCSPairs(false, true);
                    break;
                //meldir
                case 'r':
                case 'R':
                {
                    processor->FindMelodicDirectionCounts();
                    //use the following following for melodic direction duples
                    //cv.Visit(*processor);
                    //cout << cv.EntabulateAndPrintMelodicDirectionPairs();
                    break;
                }
                //melint
                case 's':
                case 'S':
                {
                    CATSMAT_scoredatacollector scoredatacollection;
                    scoredatacollection.Visit(*processor);
                    cout << scoredatacollection;
                    //quick output mechanism for now. Need to get file name and dir from user in future.
                    cout << "Save to file? (y/n) ";
                    cin >> yn;
                    if (yn == 'y' || yn == 'Y')
                    {
                        std::ofstream out("out.txt");
                        if (out.is_open())
                        {
                            out << scoredatacollection;
                            out.close();
                        }
                    }
                    break;
                }
                //CATSMAT Analysis tools
                //Find repeated dyad sequences
                case 'J':
                case 'j':
                    cout << "Ignore dissonances? (y/n) ";
                    cin >> yn;
                    if (yn == 'n') ignoreDissonances = false;
                    cout << "Ignore repeated dyads? (y/n) ";
                    cin >> yn;
                    if (yn == 'n') ignoreRepeatedDyads = false;
                    cout << "Enter minimum length: ";
                    cin >> length;
                    processor->FindRepeatedDyadSequences(length, ignoreDissonances, ignoreRepeatedDyads, false);
                    break;
                case 'K':
                case 'k':
                    cout << "Ignore dissonances? (y/n) ";
                    cin >> yn;
                    if (yn == 'n') ignoreDissonances = false;
                    cout << "Ignore repeated dyads? (y/n) ";
                    cin >> yn;
                    if (yn == 'n') ignoreRepeatedDyads = false;
                    cout << "Enter minimum length: ";
                    cin >> length;
                    processor->FindRepeatedDyadSequences(length, ignoreDissonances, ignoreRepeatedDyads);
                    break;
                //Find repeated dyadtuple sequences
                case 'L':
                case 'l':
                    cout << "L: Not impemented yet.";
                    break;
                //Find repeated sonority sequences
                case 'M':
                case 'm':
                    cout << "Enter minimum length: ";
                    cin >> length;
                    processor->FindRepeatedSonoritySequences(length);
                    break;
                //Run all CATSMAT tools
                case 'N':
                case 'n':
                    cout << "M: Not impemented yet.";
                    break;
                //Run all tools
                case 'O':
                case 'o':
                    cout << "N: Not impemented yet.";
                    break;
                case 'U':
                case 'u':
                    cout << "Enter minimum length: ";
                    cin >> length;
                    cout << "Ignore dissonances? (y/n) ";
                    cin >> yn;
                    if (yn == 'n') ignoreDissonances = false;
                    cout << "Ignore repeated dyads? (y/n) ";
                    cin >> yn;
                    if (yn == 'n') ignoreRepeatedDyads = false;
                    processor->FindRepeatedTrigramSequences(length, ignoreDissonances, ignoreRepeatedDyads);
                    break;
                case 'V':
                case 'v':
                    cout << "Ignore dissonances? (y/n) ";
                    cin >> yn;
                    if (yn == 'n') ignoreDissonances = false;
                    cout << "Ignore repeated dyads? (y/n) ";
                    cin >> yn;
                    if (yn == 'n') ignoreRepeatedDyads = false;
                    processor->FindTrigramCounts(ignoreDissonances, ignoreRepeatedDyads);
                    break;
                case 'W':
                case 'w':
                    cout << "Ignore dissonances? (y/n) ";
                    cin >> yn;
                    if (yn == 'n') ignoreDissonances = false;
                    cout << "Ignore repeated dyads? (y/n) ";
                    cin >> yn;
                    if (yn == 'n') ignoreRepeatedDyads = false;
                    processor->FindSummativeTrigramCounts(ignoreDissonances, ignoreRepeatedDyads);
                    break;
                case 'X':
                case 'x':
                    processor->FindMelodicDirectionDupleCounts();
                    break;
                case 'Z':
                case 'z':
                    processor->ListCanonicTechniques();
                    break;
                //Print all scores
                case 'P':
                case 'p':
                {
                    vector<S_IMUSANT_score> scores = processor->getScores();
                    for (int index = 0 ; index < scores.size(); index++)
                    {
                        cout << scores[index] << endl << endl  << endl;
                    }
                    
                    break;
                }
                    
            }
            cout << endl << "Run another test? (y/n): ";
            cin >> tool;
            if (tool!='y') moreTools = false;
        }
        
        catch (std::exception &e)
        {
            cout << "Unexpected problem: " << e.what() << endl;
        }
       
    } while (moreTools);
}

void
CATSMAT_menu::
addUserSpecifiedFile(CATSMAT_processing *processor)
{
    filesystem::path full_path(filesystem::initial_path());
    string filename;
    
    cout << "Adding a single file." << endl;
    cout << "Enter file name: ";
    if (getline(cin, filename))
    {
        full_path = filesystem::system_complete( filesystem::path(filename) );
        if (!filesystem::exists( full_path ))
        {
            cerr << full_path << " not found." << endl << endl;
        }
        else if (!filesystem::is_directory( full_path ) )
        {
            processor->addFile(full_path);
            cout << "Added " << full_path << endl << endl;
        }
    }
}

void
CATSMAT_menu::
addFilesFromUserSpecifiedDirectory(CATSMAT_processing *processor)
{
    filesystem::path full_path(filesystem::initial_path());
    string directory;
    cout << "Enter directory name: ";
    getline( cin, directory);
    full_path = filesystem::system_complete( filesystem::path(directory) );
    if (!filesystem::exists( full_path ))
    {
        cerr << full_path << " not found." << endl << endl;
    }
    else if (filesystem::is_directory( full_path ) )
    {
        processor->processDirectoryFiles(full_path);
        cout << "Data files loaded into memory." << endl << endl;
    }
}

void
CATSMAT_menu::
addFilesFromFixedConfigFile(CATSMAT_processing *processor)
{
    boost::filesystem::path config_file = getHomeDirectory();
    
    config_file /= FIXED_CONFIG_FILE_NAME;
    
    addFilesFromConfigFile(processor, config_file);
}

void
CATSMAT_menu::
addFilesFromConfigFile(CATSMAT_processing *processor, boost::filesystem::path config_file)
{
    vector<string> files = getContentsOfConfigurationFile(config_file);
    vector<string>::iterator it;
    
    for(it = files.begin(); it < files.end(); it++)
    {
        cout << " Adding: " << *it << "...";
        try
        {
            processor->addFile(*it);
        }
        catch (std::exception& e)
        {
            cout << e.what() << endl;
        }
        catch (...)
        {
            cout << "ERROR processing file." << endl;
        }
        cout << "...done" << endl;
    }
}


void
CATSMAT_menu::
addFilesFromUserSelectedConfigurationFile(CATSMAT_processing *processor)
{
    index_path_pair configured_files = getConfigurationFiles();
    
    bool finished = false;
    while (! finished)
    {
        cout << endl << "CONFIGURATION FILE SELECTION MENU" << endl;
        cout << endl << "Pick a file..." << endl;
        
        for(auto const &next_path : configured_files)
        {
            cout << "  " << next_path.first << ". " << next_path.second.string() << endl;
        }
        
        cout << endl << "Or press any other key to return to the main menu..." << endl;
        
        char user_selection;
        cin >> user_selection;
        cin.ignore();
        
        int file_index = atoi(&user_selection);
        if (file_index == 0) // could not convert - not a number.
        {
            finished = true;
        }
        else
        {
            index_path_pair::iterator it;
            it = configured_files.find(file_index);   // is the user selected number in the list...
            if (it != configured_files.end())
            {
                addFilesFromConfigFile(processor, configured_files[file_index]);  // yes...
            }
            else
            {
                finished = true;   // no...
            }
        }
    }
}

void
CATSMAT_menu::
listWorksAndMovementsAddedSoFar(CATSMAT_processing *processor)
{
    vector<string> movements = processor->listWorksAndMovements();
    
    if (movements.empty())
    {
        cout << "No movements added so far." << endl;
        
    }
    
    for(string next_movement : movements)
    {
        cout << next_movement << endl;
    }
}

//  ******* UTILITY FUNCTIONS *******

boost::filesystem::path
CATSMAT_menu::
getHomeDirectory()
{
    char * home_dir = NULL;
    home_dir = getenv(HOME_DIR_ENV_VAR_NAME);
    if (home_dir == NULL)
    {
        cerr << "No $HOME directory set.  Cannot read configuration.";
    }
    
    string home_dir_str(home_dir);
    boost::filesystem::path home_dir_path(home_dir_str);
    return home_dir_path;
    
}

vector<string>
CATSMAT_menu::
getContentsOfConfigurationFile(boost::filesystem::path full_path)
{
    vector<string> ret_val;
    string next_line;
    std::ifstream input_stream;
    
    //  0427 569 018
    
    input_stream.open(full_path.string());
    if (! input_stream.good())
    {
        cerr << "Error opening configuration file: " << full_path << endl;
        input_stream.close();
        return ret_val;
    }
    
    while (getline(input_stream, next_line))
    {
        if (! next_line.empty())
        {
            ret_val.push_back(next_line);
        }
    }
    
    input_stream.close();
    return ret_val;
}


map<int, boost::filesystem::path>
CATSMAT_menu::
getConfigurationFiles()
{
    map<int, boost::filesystem::path> ret_val;
    
    boost::filesystem::path config_dir(getHomeDirectory());
    config_dir /= CONFIG_FILE_DIR;
    
    directory_iterator end_iter;
    int file_index = 1;
    for(directory_iterator dir_iter(config_dir) ; dir_iter != end_iter ; ++dir_iter)
    {
        if (is_regular_file(dir_iter->status()) )
        {
            // cout << "ADDING [" << file_index << ", " << dir_iter->path().string() << "]" << endl;
            ret_val.insert(std::pair<int,boost::filesystem::path>(file_index++,*dir_iter) );
        }
    }
    return ret_val;
}



