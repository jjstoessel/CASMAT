/*

  Copyright (C) 2003  Grame
  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

  This file is provided as an example of the MusicXML Library use.
  It shows how to build a memory representation of a score from scratch. 

*/


#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <math.h>


#ifdef WIN32
#include <windows.h>
#endif

#include "LibMusicXML.h"

using namespace MusicXML;

const string kPartID = "P1";
#define kDivision	4

// a simple function that return random numbers in the given range
int 		getrandom(int range);

// the 'scorepart' function builds a score-part MusicXML element
SScorePart 	scorepart();

// the 'makeheader' function builds the score header
void 		makeheader(SScoreHeader& header);

// creates a measure containing random notes
SPWMeasure 	makemeasure(unsigned long num);

// creates specific elements of the score first measure
void 		firstmeasure(SPWMeasure& m);

// creates a part containing 'count' measures
SPWPart 	makepart(int count);

// the function that creates and writes the score
void 		randomMusic(int measuresCount);

//------------------------------------------------------------------------
// a simple function that return random numbers in the given range
//------------------------------------------------------------------------
int getrandom(int range) {
	float f = (float)rand() / RAND_MAX;
	return (int)(f * range); 
}

//------------------------------------------------------------------------
// the 'scorepart' function builds a score-part MusicXML element
//------------------------------------------------------------------------
SScorePart scorepart() {
	
	SScorePart part = newScorePart(kPartID);// creates the score-part element
    part->setPartName ("Recorder");			// sets the part name

	// creates a score instrument
	SScoreInstrument instrument = newScoreInstrument ("I1");
	instrument->setName ("Recorder");		// sets the instrument name
	part->add(instrument);					// and adds the instrument to the part

	// creates a MIDI instrument
	SMidiInstrument midi = newMidiInstrument("I1");
	midi->setProgram (75);	// sets the MIDI program to the General MIDI program for the recorder
	part->add(midi);		// and adds the MIDI instrument to the part

	return part;
}

//------------------------------------------------------------------------
// the 'makeheader' function builds the score header
// the score header contains various information, including identification,
// parts list etc...
//------------------------------------------------------------------------
void makeheader(SScoreHeader& header) {
	// creates an identification element
	SIdentification id = newIdentification();
    	
	SCreator creator = newCreator ();		// creates a creator element
	creator->setType("Composer");			// sets the creator type
	creator->setName("Georg Chance");		// sets the creator name
	id->add(creator);						// adds the creator to the identification

    SEncoding ec = newEncoding();			// creates an encoding element
    ec->setSoftware ("MusicXML Library");	// sets the software name
	id->encoding() = ec;					// adds the encoding to the identification

    header->identification() = id;			// adds the identification to the header

	header->setMovementTitle ("Random Music");	// sets the movement title
    header->partList() = newPartList();			// creates a part list
	header->partList()->add (scorepart());		// and adds a new part to the part list
}


//------------------------------------------------------------------------
// creates specific elements of the score first measure
// the first measure is generally a special measure since it contains 
// elements like the clef, the time and key signatures etc...
//------------------------------------------------------------------------
void firstmeasure(SPWMeasure& m) {
    SAttributes attributes = newAttributes();	// creates new attributes

    SClef clef = newClef();					// creates a new clef
    clef->setSign(TClef::G);				// sets the clef sign
    clef->setLine(2);						// sets the clef line number
    attributes->add(clef);					// and adds the clef to the attributes

    STimeSign ts = newTimeSign();			// creates a new time signature
    ts->add (4, 4);							// sets the time signature to 4/4
    attributes->timeSign() = ts;			// and drop the time sign into the attributes

    // sets the attributes division: division is the MusicXML way to indicates how many 
	// divisions per quarter note are used to indicate a note's duration.
	attributes->setDivisions(kDivision);

    m->add (attributes);					// and adds the attributes to the measure
    
    SDirection dir = newDirection();		// creates a direction element
    SSound sound = newSound();				// creates a sound element
    long tempo = 120 + getrandom(40)-20;	// computes a random tempo value
    sound->setTempo (tempo);				// and sets the sound tempo
    dir->sound() = sound;					// and drop the sound element into the direction element
    
    SDirectionType dt = newDirectionType();	// creates a direction-type element
    SMetronome metro = newMetronome();		// creates a metronome element
    metro->setBeat (NoteType::quarter); 	// and sets the metronome to
    metro->setPerMinute (tempo); 			// quarter note = tempo
    dt->add(metro);							// adds the metronome to the direction-type element
    dir->add(dt);							// adds the direction-type to the direction element
    m->add (dir);							// and finally adds the direction to the measure
}


//------------------------------------------------------------------------
// creates a measure containing random notes
// the function takes the measure number as an argument
//------------------------------------------------------------------------
SPWMeasure makemeasure(unsigned long num) {
	// creates a new partwise measure
	SPWMeasure measure = newPWMeasure(num);

	if (num==1) {					// if it's the first measure
		firstmeasure(measure);		// creates specific elements of the first measure
	}
	for (int i=0; i<4; i++) {		// next adds 4 quarter notes
		SNote note = newNote(); 						// creates the note       
		SPitch pitch = newPitch();						// creates a pitch
        pitch->setStep(getrandom(7)+1);					// sets the pitch to a random value
        pitch->setOctave (4 + getrandom(2));			// sets the octave to a random value
		note->pitch() = pitch;							// and drops the pitch to the note
		note->setDuration (kDivision);					// sets the note duration to a quarter note
		note->graphics() = newGraphNote();				// creates the graphic elements of the note
		note->graphics()->setType (NoteType::quarter);	// and sets the graphic note type to quarter note
		measure->add (note);		// and finally adds the note to the measure
	}
	return measure;
}


//------------------------------------------------------------------------
// creates a part containing 'count' measures
//------------------------------------------------------------------------
SPWPart makepart(int count) {
	SPWPart part = newPWPart(kPartID);		// creates a new part
	for (int i=1; i<=count; i++)			// and 'count' times
		part->add (makemeasure(i));			// adds a new measure to the part
	return part;
}

//------------------------------------------------------------------------
// the function that creates and writes the score
//------------------------------------------------------------------------
void randomMusic(int measuresCount) {
	SScorePartwise score = newScorePartwise();		// creates a partwise score
	score->scoreHeader() = newScoreHeader();		// creates a score header and drops it to the score
	makeheader(score->scoreHeader());				// fills the score header
	score->add(makepart(measuresCount));			// adds a part to the score

	TMusicXMLFile f;
	f.write(score, cout);	// and finally writes the score to the standard output
}

int main (int argc, char * argv[]) {
	// if present, reads the measures count from the command line
	int count = (argc == 2) ? atoi(argv[1]) : 20;
	// sets the random numbers seed
	srand((unsigned)time(0));
	// computes and writes the score
	randomMusic(count);
    return 0;
}

