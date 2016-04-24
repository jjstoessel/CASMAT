/*
 *  imusantcat_main.cpp
 *  imusant
 *
 *  Created by Jason Stoessel on 24/06/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
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
#include "IMUSANT_processing.h"



#define __DEBUG__ 0

using namespace boost;
using namespace std;
using namespace IMUSANT;

extern int catalogue(filesystem::path& p);
extern void runToolMenu(IMUSANT_processing& processor);

int main (int argc, char * const argv[]) {
	filesystem::path full_path(filesystem::initial_path());
	IMUSANT_processing processor;
	
	cout	<< "=========================================================================" << endl
			<< "|					 WELCOME TO IMUSANT, version 0.6					" << endl
			<< "|					(Intertextual MUSic ANalysis Tool)					" << endl
			<< "|																		" << endl
			<< "|	Designers: Rex Eakins, Jason Stoessel								" << endl
			<< "|	Programming: Jason Stoessel											" << endl
			<< "|	Development Tool: Apple Computer's XCode version 2.3 (gcc++)		" << endl
			<< "|																		" << endl
			<< "|	This software is part of the project entitled \"The Meeting of		" << endl
			<< "|	Computer Technology and Medieval Music: A Prototype Software		" << endl
			<< "|	Program for Analysis of Musical Intertextuality.\" Funding for		" << endl
			<< "|	the development of the first working model of this tool has been	" << endl
			<< "|	provide as a 2006 University Research Grant from the University		" << endl
			<< "|	of New England, Armidale, Australia.								" << endl
			<< "|																		" << endl
			<< "|	This program and its code remains the property of the authors and	" << endl
			<< "|	where applicable, the University of New England. This program		" << endl
			<< "|	currently makes use of the following libraries:						" << endl
			<< "|		1. MusicXML Library under the GNU Lesser General Public License " << endl
			<< "|		2. Boost under Boost Software License (Open source license)		" << endl
			<< "|																		" << endl
			<< "|	The Music XML data format is used under the Royalty-free license	" << endl
			<< "|	granted by Recordare LCC; see										" << endl
			<< "|		http://www.recordare.com/dtds/license.html						" << endl
			<< "|																		" << endl
			<< "|	Conditions for those licenses apply to relative portions of this	" << endl
			<< "|	software. Newly created portions of this software and propriety		" << endl
			<< "|	data formats are copyrighted by the designers and programmer.		" << endl
			<< "|																		" << endl
			<< "=========================================================================" << endl << endl;
	
	cout	<<	"							MAIN MENU" << endl
			<<	"              1. Compare files in directory" << endl
			<<	"              2. Compare a selected number of files" << endl << endl
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
					processor.processDirectoryFiles(full_path);
					cout << "Data files loaded into memory." << endl << endl;
					runToolMenu (processor);
					end = true;
				}
				break;
			case '2':
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
							processor.addFile(full_path);
						}
						cout << "Add another file? (y/n):";
						
						cin >> yesNo;
						cin.ignore();
					}
				}
								
				runToolMenu(processor);
				end = true;
				break;
			default:
				cout << "Invalid selection. Please select a menu item (1-2): " ;
		}
	} while (!end);
	

	
	
	cout << "Goodbye." << endl;
	
	//else //is file
	//	return catalogue(full_path);
	
	return 0;

}

/* int main (int argc, char * const argv[]) 
{
	filesystem::path full_path(filesystem::initial_path());
	IMUSANT_processing processor;
	
	if (argc != 2) {
		cerr << "/nusage:imusant <xml file>" << endl;
		return 1;
	}
	else
		full_path = filesystem::system_complete( filesystem::path(argv[1], filesystem::native) );
	
	if (!filesystem::exists( full_path ))
	{
		cerr << full_path.native_file_string() << " not found." << endl;
		return 1;
	}
	
	if (filesystem::is_directory( full_path ) )
	{
		processor.process_directory_files(full_path);
		processor.find_repeated_interval_substrings();
		processor.find_repeated_contour_substrings();
		processor.find_supermaximals_intervals(4,100);
		processor.find_supermaximals_contours(4,100);
		processor.find_lcs_pairs_intervals(false);
		processor.find_lcs_pairs_pitches(false);
	}
	//else //is file
	//	return catalogue(full_path);
	
	return 0;

}
 */
 
void runToolMenu(IMUSANT_processing& processor)
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
				cout << processor.findAndPrintRepeatedIntervalSubstrings(length);
				break;
			case '2':
				cout << "Enter minimum length: ";
				cin >> length;
				processor.findRepeatedContourSubstrings(length);
				break;
			case '3':
				processor.findSupermaximalsIntervals(4,100);
				break;
			case '4':
				processor.findSupermaximalsContours(4,100);
				break;
			case '5':
				cout << "Only find continguous segments? (y/n) ";
				cin >> yn;
				if (yn == 'y') continguous = true;
				processor.findLcsPairsIntervals(continguous);
				break;
			case '6':
				cout << "Only find continguous segments? (y/n) ";
				cin >> yn;
				if (yn == 'y') continguous = true;
				processor.findLcsPairsIntervalsReverse(continguous);
				break;
			case '7':
				cout << "Only find continguous segments? (y/n) ";
				cin >> yn;
				if (yn == 'y') continguous = true;
				processor.findLcsPairsPitches(continguous);
				break;
			case '8':	
				processor.findRepeatedIntervalSubstrings();
				processor.findSupermaximalsIntervals(4,100);
				processor.findSupermaximalsContours(4,100);
				processor.findLcsPairsIntervals(false);
				processor.findLcsPairsPitches(false);
				processor.findLcsPairsIntervalsReverse(false);
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
		
		c.get_imusant_score()->accept(collection);
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
