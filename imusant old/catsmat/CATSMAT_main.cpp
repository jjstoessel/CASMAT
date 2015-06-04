/*
 *  CATSMAT_main.cpp
 *  imusant
 *
 *  Created by Jason Stoessel on 8 March 2015.
 *  Copyright © 2015 Jason Stoessel. All rights reserved.
 *  
 *
 */
#include <iostream>

#include <boost/filesystem.hpp>

#include "TMusicXMLFile.h"
#include "IMUSANT_XMLFile.h"
#include "TXML2IMUSANTVisitor.h"
#include "IMUSANT_XMLVisitor.h"
#include "IMUSANT_XMLReader.h"
#include "IMUSANT_collectionvisitor.h"
#include "TScore.h"
#include "CATSMAT_processing.hpp"



#define __DEBUG__ 0

using namespace boost;
using namespace std;
using namespace CATSMAT;

extern int catalogue(filesystem::path& p);
extern void runToolMenu(CATSMAT_processing& processor);

int main (int argc, char * const argv[]) {
	filesystem::path full_path(filesystem::initial_path());
	CATSMAT_processing processor;
	
	cout	<< "========================================================================" << endl
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
	
	cout	<<	"							MAIN MENU" << endl
			<<	"              1. Test a single file" << endl
			<<	"              2. Batch test files in a directory" << endl
            <<  "              3. Identify canonic technique (not available)" << endl << endl
			<<	"Please select a menu item (1-2): ";
	
	char menuItem = 0; 
	char yesNo = 'y';
	string directory, file;
	bool end = false;
	do 
	{
		cin >> menuItem;
		cin.ignore();
		switch (menuItem)
		{
            case '1':
                while ( yesNo != 'n' && yesNo != 'N' )
                {
                    cout << "Enter file name: ";
                    if (getline(cin, file))
                    {
                        full_path = filesystem::system_complete( filesystem::path(file) );
                        if (!filesystem::exists( full_path ))
                        {
                            cerr << full_path << " not found." << endl;
                        }
                        else if (!filesystem::is_directory( full_path ) )
                        {
                            processor.add_file(full_path);
                        }
                        cout << "Add another file? (y/n):";
                        
                        cin >> yesNo;
                        cin.ignore();
                    }
                }
                
                runToolMenu(processor);
                end = true;
                break;
			case '2':
				cout << "Enter directory name: ";
				getline( cin, directory);
				full_path = filesystem::system_complete( filesystem::path(directory) );
				if (!filesystem::exists( full_path ))
				{
					cerr << full_path << " not found." << endl;
					break;
				}
				if (filesystem::is_directory( full_path ) )
				{
					processor.process_directory_files(full_path);
					cout << "Data files loaded into memory." << endl << endl;
					runToolMenu (processor);
					end = true;
				}
				break;
            case '3':
                cout << "Currently not available." << endl;
			default:
				cout << "Invalid selection. Please select a menu item (1-2): " ;
		}
	} while (!end);
	

	
	
	cout << "Goodbye." << endl;
	
	//else //is file
	//	return catalogue(full_path);
	
	return 0;

}

void runToolMenu(CATSMAT_processing& processor)
{
	bool moreTools = true;
	do
	{
		cout << "ANALYSIS TOOLS" << endl;
		cout << "1. Find repeated interval substrings " << endl;
		cout << "2. Find repeated interval contour substrings " << endl;
		cout << "3. Find interval supermaximals " << endl;
		cout << "4. Find contour supermaximals " << endl;
		cout << "5. Find longest common intervallic subsequence in all pairs" << endl;
		cout << "6. Find longest common intervallic subsequence in all pairs (reverse method)" << endl;
		cout << "7. Find longest common pitch subsequence in all pairs" << endl;
		cout << "8. Run all tools" << endl;
		cout << "Please select analysis tool (1-8; any other key to exit): "; 
		char tool, yn;
		bool continguous = false;
		int length = 5;
		cin >> tool;
		switch (tool)
		{
			case '1':
				cout << "Enter minimum length: ";
				cin >> length;
				processor.find_repeated_interval_substrings(length);
				break;
			case '2':
				cout << "Enter minimum length: ";
				cin >> length;
				processor.find_repeated_contour_substrings(length);
				break;
			case '3':
				processor.find_supermaximals_intervals(4,100);
				break;
			case '4':
				processor.find_supermaximals_contours(4,100);
				break;
			case '5':
				cout << "Only find continguous segments? (y/n) ";
				cin >> yn;
				if (yn == 'y') continguous = true;
				processor.find_lcs_pairs_intervals(continguous);
				break;
			case '6':
				cout << "Only find continguous segments? (y/n) ";
				cin >> yn;
				if (yn == 'y') continguous = true;
				processor.find_lcs_pairs_intervals_reverse(continguous);
				break;
			case '7':
				cout << "Only find continguous segments? (y/n) ";
				cin >> yn;
				if (yn == 'y') continguous = true;
				processor.find_lcs_pairs_pitches(continguous);
				break;
			case '8':	
				processor.find_repeated_interval_substrings();
				processor.find_repeated_contour_substrings();
				processor.find_supermaximals_intervals(4,100);
				processor.find_supermaximals_contours(4,100);
				processor.find_lcs_pairs_intervals(false);
				processor.find_lcs_pairs_pitches(false);
				processor.find_lcs_pairs_intervals_reverse(false);
				break;
		}
		cout << "Run another test? (y/n): ";
		cin >> tool;
		if (tool!='y') moreTools = false;
	} while (moreTools);

}

int catalogue(filesystem::path& p)
{
	TXML2IMUSANTVisitor c;    
    TMusicXMLFile reader;
	string xml(".xml"), imusant(".ims");
	IMUSANT_XMLFile ixml;
	filesystem::path mutable_path = p;
	IMUSANT_collection_visitor collection;
	
	if (filesystem::extension(p)==xml)
	{
		//convert first
		SScore score = reader.read((string&)p);
		if (score == NULL) {
			cerr << "Parse error";
			return 1;
		}
		
		//error checking required!
		score->accept(c);
		
		c.getIMUSANTScore()->accept(collection);
		//mutable_path = filesystem::change_extension(p, imusant);
		//ixml.write(c.getIMUSANTScore(),mutable_path.native_file_string()); //write to file
	}
	//check extension
	if (filesystem::extension(p)==imusant)
	{
		ixml.read((string&)mutable_path); //reader file
		//verify, catalogue to default directory
	}

	return 0;
}
