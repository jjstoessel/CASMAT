/*

  Copyright (C) 2003  Grame
  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

  This file is provided as an example of the MusicXML Library use.
  It shows how to read and write xml files. It also gives a concrete
  example of how to browse and modify the memory representation of
  a score.
  
*/


#include <iostream>

#include "LibMusicXML.h"

using namespace std;
using namespace MusicXML;

//------------------------------------------------------------------------
//
// This is an example of a visitor implementation. Visitors allows
// to browse the memory representation of a score. Two basic visitors
// are provided by the library:
//  - a TRoutedVisitor which is a visitor that provides a path for 
//    traversing the score tree (see the library documentation for the
//    path description). 
//  - a TScoreVisitor which is a visitor that does nothing: objects
//    that derive from TScoreVisitor must implement a path for traversing
//    the score tree. This may be necessary only for non-standard way
//    of browsing the score. 
// The RawTransposer visitor has no special requirement concerning the path
// for traversing the tree and therefore derives from TRoutedVisitor.
// It is only interested in TNote objects and therefore, only overrides 
// the corresponding method.
//
//------------------------------------------------------------------------
class RawTransposer : public TRoutedVisitor {

    public:
		// constructor is initialized with the transposing interval
		RawTransposer(int interval) : fInterval(interval) {}
		virtual ~RawTransposer() {}
		void visite ( SNote& elt );

	private:
		int	fInterval;		// the transposing interval
};

//------------------------------------------------------------------------
// The raw transposition implementation.
//------------------------------------------------------------------------
void RawTransposer::visite (SNote& note) {
	// first get the note pitch element (it's a MusicXML pitch)
	SPitch pitch = note->pitch();
	// and next adds the transposing interval
	// the += operator affects the step and octave only (no accidental change)
	*pitch += fInterval;
}

//------------------------------------------------------------------------
int main (int argc, char * argv[]) 
{
    if (argc != 3) {
		cerr << "usage: " << argv[0] << " <interval> <file>" << endl;
		exit(1);
	}

	// transposing interval is readed from the command line
	int interval = atoi(argv[1]);
	// use of a TMusicXMLFile object to read and write xml files
	TMusicXMLFile file;
	// reads the file (file name is readed from the command line)
	SScore score = file.read(argv[2]);
	if (score) {
		if (interval) {
			// declares a RawTransposer object
			RawTransposer transposer(interval);
			// ask the score to accept the transposer
			score->accept(transposer);
		}
		// and finally writes the result on the standard output
		// 'cout' could be replaced by a file as well
		file.write (score, cout);
	}
	else cerr << "cannot read file \"" << argv[2] << "\"" << endl;
	return 0;
}


