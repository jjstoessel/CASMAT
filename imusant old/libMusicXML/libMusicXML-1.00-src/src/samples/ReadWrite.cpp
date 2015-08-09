/*

  Copyright (C) 2003  Grame
  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

  This file is provided as an example of the MusicXML Library use.
  It shows how to read and write xml files.   
*/

#include <iostream>
#include <string>

#include "TMusicXMLFile.h"

using namespace std;
using namespace MusicXML;


int main (int argc, char * argv[]) 
{
	// use of a TMusicXMLFile object to read and write xml files
    TMusicXMLFile file;
	for (int i=1; i<argc; i++) {
		// reads the file (file name is readed from the command line)
		SScore score = file.read(argv[i]);
		if (score) {
			// and writes the readed score to the standard output
			// note that 'cout' could be replaced by a file name as well
			file.write (score, cout);
		}
		else {
			cerr << "cannot read file \"" << argv[i] << "\"" << endl;
		}
	}
    return 0;
}


