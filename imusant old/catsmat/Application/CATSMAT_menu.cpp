//
//  CATSMAT_Menu.cpp
//  imusant
//
//  Created by Derrick Hill on 6/12/2015.
//
//

#include "CATSMAT_menu.h"

#include <fstream>

using namespace std;
using namespace CATSMAT;

void
CATSMAT_menu::
runMenu()
{
    
    
}

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
getFilesToAnalyse(CATSMAT_processing *processor)
{
    bool finished = false;
    char selectedMenuItem = 0;
    
    while (! finished)
    {
        
        cout << endl
        <<	"Please select an option:" << endl
        <<	"  1 - Add a file..." << endl
        <<	"  2 - Add all files from a directory..." << endl
        <<  "  3 - Load files from the configuration file at $HOME/.catsmat_config" << endl
        <<  "  9 - Analyze the files I have added..." << endl << endl;
        
        selectedMenuItem = readMenuSelection();

        switch (selectedMenuItem)
        {
            case '1':
                getOneFileToAnalyse(processor);
                finished = false;
                break;
                
            case '2':
                getDirectoryToAnalyse(processor);
                finished = false;
                break;
                
            case '3':
                getAllConfiguredFiles(processor);
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
getAllConfiguredFiles(CATSMAT_processing *processor)
{
    char * home_dir = NULL;
    home_dir = getenv("HOME");
    if (home_dir == NULL)
    {
        cerr << "No home directory set.  Cannot read configuration.";
    }
    
    string config_file(home_dir);
    
    config_file += "/catsmat_config.txt";
    
    vector<string> files = getConfiguredFiles(config_file);
    vector<string>::iterator it;
    
    for(it = files.begin(); it < files.end(); it++)
    {
        processor->add_file(*it);
        cout << " Added: " << *it << endl;        
    }
}

vector<string>
CATSMAT_menu::
getConfiguredFiles(string full_path)
{
    vector<string> ret_val;
    string next_line;
    ifstream input_stream;
    
    //  0427 569 018
    
    input_stream.open(full_path);
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


void
CATSMAT_menu::
getOneFileToAnalyse(CATSMAT_processing *processor)
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
            processor->add_file(full_path);
            cout << "Added " << full_path << endl << endl;
        }
    }
    
}


void
CATSMAT_menu::
getDirectoryToAnalyse(CATSMAT_processing *processor)
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
        processor->process_directory_files(full_path);
        cout << "Data files loaded into memory." << endl << endl;
    }
}

char
CATSMAT_menu::
readMenuSelection()
{
    char menuItem;
    cin >> menuItem;
    cin.ignore();
    return menuItem;
}
