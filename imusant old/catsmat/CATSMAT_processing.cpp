/*
 *  CATSMAT_processing.cpp
 *  catsmat
 *
 *  Created by Jason Stoessel on 12/03/15.
 *  Copyright 2015 the programmers. All rights reserved.
 *
 *  A file processing class for CATSMAT.
 */
#include <iostream>
#include <deque>
#include <boost/filesystem.hpp>

#include "CATSMAT_processing.hpp"
#include "TMusicXMLFile.h"
#include "IMUSANT_XMLFile.h"
#include "TXML2IMUSANTVisitor.h"
#include "IMUSANT_XMLVisitor.h"
#include "IMUSANT_XMLReader.h"
#include "TScore.h"
#include "CATSMAT_dyad_sequences.hpp"
#include "CATSMAT_dyadtuple_sequences.hpp"

#define MAX(X,Y) ( (X>Y)? (X) : (Y) )

using namespace std;
using namespace boost;

namespace CATSMAT
{

void CATSMAT_processing::process_directory_files(const filesystem::path& full_path)
{
	if (filesystem::is_directory( full_path ) )
	{
		filesystem::directory_iterator end;
		for (	filesystem::directory_iterator iter(full_path);
				iter != end;
				++iter )
		{
			add_file(*iter);
		}		
	}
}

void
CATSMAT_processing::add_file(const filesystem::path& path)
{
	TMusicXMLFile reader;
	string xml(".xml"), imusant(".ims");
	filesystem::path mutable_path = path;
	TXML2IMUSANTVisitor c;    
	IMUSANT_XMLFile ixml;
	map<int,vector<IMUSANT_interval> > intervalTable;
	int i = 1;
	
	try
	{
		if (!filesystem::is_directory(path))
		{
			if (filesystem::extension(path)==xml)
			{
				//convert first
				SScore score = reader.read((string&)path);
				if (score == NULL) {
					cerr << "Parse error in " << path.leaf() << endl;
					return;
				}
				//ensure unique ID
				while (find(IDs.begin(), IDs.end(), i)!=IDs.end()) i++;
				//error checking required!
				score->accept(c);
				collections[i].ignoreRepeatedPitches(false);
				c.getIMUSANTScore()->accept(collections[i]);
				
				IDs.push_back(i);
 
                //Here only for testing; could be placed in test unit or specific tool
                CATSMAT_dyad_sequences dyads;
                CATSMAT_dyadtuple_sequences tuples;
                
                collections[i].getCPMatrix()->Accept(dyads);
                //collections[i].getCPMatrix()->Accept(tuples);
                
                //cout << collections[i].getCPMatrix();
                
                //cout << dyads;
                
                dyads.find_repeated(4);
                
                //cout << tuples;
                
                //tuples.find_repeated_tuplet_sequences(3);
                
			}
			//check extension
			if (filesystem::extension(path)==imusant)
			{
				ixml.read((string&)mutable_path); //reader file
				//verify, catalogue to default directory
			}

		}
	}
	catch (const runtime_error& ex)
	{
		cerr << path.leaf() << " " << ex.what() << endl;
	}
}


} //namespace CATSMAT