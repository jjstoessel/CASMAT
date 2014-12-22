/*
 *  IMUSANT_XMLFile.cpp
 *  imusant
 *
 *  Created by Jason Stoessel on 7/06/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "IMUSANT_XMLFile.h"
#include "IMUSANT_XMLReader.h"
#include "IMUSANT_XMLVisitor.h"
#include <fstream>

using namespace std;

namespace IMUSANT
{

//______________________________________________________________________________
S_IMUSANT_score IMUSANT_XMLFile::read(const string& file)
{
	IMUSANT_XMLReader reader;
	return reader.Read(file.c_str());
}

//______________________________________________________________________________
bool IMUSANT_XMLFile::write(S_IMUSANT_score score, const string& file)
{
	ofstream os;
	os.open(file.c_str());
	bool ret = write (score, os);
	os.close();
	return ret;
}

//______________________________________________________________________________
bool IMUSANT_XMLFile::write(S_IMUSANT_score score, ostream& os)
{
	IMUSANT_XMLVisitor v;
	if (score) {
		score->accept(v);
		os  << "<?xml version=\"1.0\" standalone=\"no\"?>" << endl
			//the following in header is absolutely necessary
			<< "<!DOCTYPE IMUSANT-SCORE PUBLIC \"\" \"\">" << endl
			//<< score->xmlheader()
			<< v.current()
			<< endl;
		return true;
	}
	return false;
}

}//namespace IMUSANT
