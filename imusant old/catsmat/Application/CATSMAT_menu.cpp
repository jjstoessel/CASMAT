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

#include "IMUSANT_interval_processor.h"
#include "IMUSANT_pitch_processor.h"
#include "IMUSANT_contour_processor.h"

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
    << "=========================================================================" << endl << endl;
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
        <<  "  8 - List the movements I have added so far..." << endl
        <<  "  9 - Analyze the files I have added..." << endl << endl;
    
        char selectedMenuItem = 'x';
        cin >> selectedMenuItem;
        cin.ignore();
        
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
                
            case '8':
                listWorksAndMovementsAddedSoFar(processor);
                finished = false;
                break;
                
            case '9':
                finished = true;
                break;
                
            default:
                cout << "Invalid selection. Please select a valid menu item." ;
                finished = false;
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
    out << "O.  Print all scores" << endl;
    out << "I.  Run all IMUSANT tools" << endl;
    out << endl;
    out << "CATSMAT ANALYSIS TOOLS" << endl;
    out << "J. Find repeated dyad sequences" << endl ;
    out << "K. Find repeated dyadtuple sequences" << endl;
    out << "L. Find repeated sonority sequences" << endl;
    out << "M. Run all CATSMAT tools" << endl;
    out << endl;
    out << "N. Run all tools" << endl;
    out << endl;
    out << "Please select analysis tool (A - N; any other key to exit): " << endl;
    out << endl;
}


void
CATSMAT_menu::
runToolsMenu(CATSMAT_processing* processor)
{
    bool moreTools = true;
    IMUSANT_interval_processor  ip;
    IMUSANT_pitch_processor     pp;
    IMUSANT_contour_processor   cp;
    do
    {
        outputToolsMenu(cout);
        
        char tool, yn;
        bool continguous = false;
        int length = 5;
        cin >> tool;
        switch (tool)
        {
            case 'A':
            case 'a':
                ip.Visit(*processor);
                cout << "Enter minimum length: ";
                cin >> length;
                cout << ip.findAndPrintRepeatedIntervalSubstrings(length);
                break;
                
            case 'B':
            case'b':
                cout << "Enter minimum length: ";
                cin >> length;
                cp.Visit(*processor);
                cp.findRepeatedContourSubstrings(length);
                break;
                
            case 'C':
            case 'c':
                ip.Visit(*processor);
                ip.findSupermaximalsIntervals(4,100);
                break;
                
            case 'D':
            case 'd':
                cp.Visit(*processor);
                cp.findSupermaximalsContours(4,100);
                break;
                
            case 'E':
            case 'e':
                cout << "Only find continguous segments? (y/n) ";
                cin >> yn;
                if (yn == 'y') continguous = true;
                ip.Visit(*processor);
                ip.findLcsPairsIntervals(continguous);
                break;
                
            case 'F':
            case 'f':
                cout << "Only find continguous segments? (y/n) ";
                cin >> yn;
                if (yn == 'y') continguous = true;
                ip.Visit(*processor);
                ip.findLcsPairsIntervals(continguous,true);
                break;
                
            case 'G':
            case 'g':
                cout << "Only find continguous segments? (y/n) ";
                cin >> yn;
                if (yn == 'y') continguous = true;
                pp.Visit(*processor);
                pp.findLcsPairsPitches(continguous);
                break;
                
            case 'H':
            case 'h':
            {
                vector<S_IMUSANT_segmented_part_LBDM> segmented_parts;
                segmented_parts = processor->findMelodicSegments_LBDM();
                for (vector<S_IMUSANT_segmented_part_LBDM>::iterator seg_part_iter = segmented_parts.begin(); seg_part_iter != segmented_parts.end() ; seg_part_iter++)
                {
                    cout << *(*seg_part_iter) << endl;
                }
            
                break;
            }
                
            case 'O':
            case 'o':
            {
                vector<S_IMUSANT_score> scores = processor->getScores();
                for (int index = 0 ; index < scores.size(); index++)
                {
                    cout << scores[index] << endl << endl  << endl;
                }
                
                break;
            }
                
            case 'I':
            case 'i':
                ip.Visit(*processor);
                cp.Visit(*processor);
                pp.Visit(*processor);

                ip.findRepeatedIntervalSubstrings();
                cp.findRepeatedContourSubstrings();
                ip.findSupermaximalsIntervals(4,100);
                cp.findSupermaximalsContours(4,100);
                ip.findLcsPairsIntervals(false);
                pp.findLcsPairsPitches(false);
                ip.findLcsPairsIntervals(false, true);
                break;
                
            case 'J':
            case 'j':
                cout << "I: Not impemented yet.";
                break;
                
            case 'K':
            case 'k':
                cout << "J: Not impemented yet.";
                break;
                
            case 'L':
            case 'l':
                cout << "K: Not impemented yet.";
                break;
                
            case 'M':
            case 'm':
                cout << "L: Not impemented yet.";
                break;
                
            case 'N':
            case 'n':
                cout << "M: Not impemented yet.";
                break;
                
        }
        cout << endl << "Run another test? (y/n): ";
        cin >> tool;
        if (tool!='y') moreTools = false;
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



