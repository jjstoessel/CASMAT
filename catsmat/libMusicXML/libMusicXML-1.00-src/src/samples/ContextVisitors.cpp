/*

  Copyright (C) 2004  Grame
  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

  This file is provided as an example of the MusicXML Library use.
  It shows how to use the TRolledVisitor and TUnrolledVisitor
  that takes account of the score structural information.
  It also overrides the TMidiContextVisitor to show how to get
  contextual information (such as the current date) while
  visiting a score.
*/

#include "LibMusicXML.h"
#include "TMidiContextVisitor.h"
#include "TRolledVisitor.h"
#include "TUnrolledVisitor.h"

using namespace std;
using namespace MusicXML;

/*
	a visitor that maintains an index for note and rests and 
	provides access to the note context : pitch, velocity, date, duration
	Date and duration are expressed in ticks related 
	to a given TicksPerQuarter value

	The base class TMidiContextVisitor maintains the time 
	context and provides parameter access methods.
*/
class TContextVisitor : public TMidiContextVisitor {
    private:
		long fIndex; // an index to count the number of symbols : notes and rest
	    
    public:
        enum { kTPQ = 480 }; // the TicksPerQuarter value
		TContextVisitor() : TMidiContextVisitor(kTPQ), fIndex(0) {}
	 	virtual ~TContextVisitor() {}

		virtual void visiteEnter ( SNote& elt );        // we're only interested in notes and 
		virtual void visiteEnter ( SPWMeasure& elt );   // measures
};

/*
	When visiting a SNote node, all its parameters can be accessed : 
	pitch are MIDI values, date and duration are expressed in ticks 
	relative to a given TicksPerQuarter value
*/
void TContextVisitor::visiteEnter ( SNote& elt ) {
	if (elt->isCue()) return;     // Cue notes are ignored
	
    fIndex++; 
	switch(elt->getType()) {
	
	   case TNote::pitched:
            cout << "Note : Index = " << fIndex << " Pitch = " << getPitch(elt) << " Vel = " << getDynamics(elt)
                 << " Date = " << getDate() << " Duration = " << getFullDuration(elt) << endl;
            break;
        case TNote::rest: 
            cout << "Rest : Index = " << " Date = " << getDate() << " Duration = " << getFullDuration(elt) << endl;
            break; 
        case TNote::unpitched:
            break; 
    }
}

// measure numbers are available when visiting a SPWMeasure
void TContextVisitor::visiteEnter ( SPWMeasure& elt ) {
	cout << "Measure = " << elt->getNumber() << endl;
	TMidiContextVisitor::visiteEnter(elt); 
}

// Use a 'rolled' visitor that does not unwrap the score
void roll(SScore score) {
	TContextVisitor visitor;
	TRolledVisitor structureVisitor(&visitor);
	score->accept (structureVisitor);
}

// Use an 'unrolled' visitor that does unwrap the score
void unroll(SScore score) {
	TContextVisitor visitor;
	TUnrolledVisitor structureVisitor(&visitor);
	score->accept (structureVisitor);
}

int main (int argc, char * argv[])  {
    TMusicXMLFile file;
	for (int i=1; i<argc; i++) {
		SScore score = file.read(argv[i]);
		if (score) {
            cout << argv[i] << ": rolled score" << endl;
			roll(score);
            cout << argv[i] << ": unrolled score" << endl;
			unroll(score);
		}
		else cerr << "cannot read file \"" << argv[i] << "\"" << endl;
	}
    return 0;
}

