/*
 *  IMUSANT_collectionvisitor.h
 *  imusant
 *
 *  Created by Jason Stoessel on 24/06/06.
 *  Copyright 2006 Jason Stoessel. All rights reserved.
 *
 *	This class visits an IMUSANT score and collection information that is 
 *	then ready to output (using another visitor class to be implemented).
 *	Data collected:
 *		- movement data, title, creators, originating data file
 *		- basic musical features: range, key, final, number of notes & rests, no. of alterations
 *		- interval segments, including matched instances (useful for "fingerprinting" individual pieces)
 *		- rhythm segments, including matched instances
 */
#ifndef __IMUSANT_COLLECTION_VISITOR__
#define __IMUSANT_COLLECTION_VISITOR__


#include "IMUSANT_ivec_collection.h"
#include "IMUSANT_rvec_collection.h"
#include "IMUSANT_contour_symbol.h"
#include "IMUSANT_visitor.h"
#include "IMUSANT_pitch.h"

using namespace std;

namespace IMUSANT
{

class IMUSANT_pitch_vector : public smartable, public vector<IMUSANT_pitch> 
{
	public:
	
    friend SMARTP<IMUSANT_pitch_vector> new_IMUSANT_pitch_vector();
	
};
typedef SMARTP<IMUSANT_pitch_vector> S_IMUSANT_pitch_vector;

S_IMUSANT_pitch_vector new_IMUSANT_pitch_vector();
    
class VEXP IMUSANT_collection_visitor : public IMUSANT_visitor
{
	public:
					IMUSANT_collection_visitor();
		virtual		~IMUSANT_collection_visitor() {}
		
		void visit ( S_IMUSANT_attributes& elt );
		void visit ( S_IMUSANT_barline& );
		void visit ( S_IMUSANT_chord& elt );
		void visit ( S_IMUSANT_comment& elt );
		void visit ( S_IMUSANT_element& elt );
		void visit ( S_IMUSANT_lyric& elt );
		void visit ( S_IMUSANT_measure& elt );
		void visit ( S_IMUSANT_note& elt );
		void visit ( S_IMUSANT_part& elt );
		void visit ( S_IMUSANT_partlist& elt );
		void visit ( S_IMUSANT_score& elt );

		const S_IMUSANT_interval_vector& getIntervalVector() const { return fIntervalVector; } 
		const S_IMUSANT_rvec_collection& getRhythmVector() { return fRhythmCollection; } //reimpliment;
		const string& getMovementTitle() const { return fMovementTitle; }
        const string& getWorkTitle() const { return fWorkTitle; }
		const S_IMUSANT_contour&	getMelodicContour() const { return fMelodicContour; }
		const S_IMUSANT_pitch_vector& getPitchVector() { return fPitchVector; }
		
		void ignoreRepeatedPitches(bool ignore) { fIgnoreRepeatedPitches = ignore; }
	protected:
		
	private:
		
		void processCollections();
		
		//collection of interval vectors
		//S_IMUSANT_ivec_collection	fIntervalCollection;
		//collection of rhythm vectors
		S_IMUSANT_rvec_collection       fRhythmCollection;
		//local storage of segments
		S_IMUSANT_interval_vector       fIntervalVector;
		//local storage of melodic contour
		S_IMUSANT_contour               fMelodicContour;
		//local storage of pitches
		S_IMUSANT_pitch_vector          fPitchVector;
    
        string			fWorkTitle;
        string			fMovementTitle;
        vector<string>	fLyrics;

		
		// global flag to denote chords writing
		bool			fInChord;
		S_IMUSANT_note	fLastNote;
		long			fCurrentPartID;
		bool			fIgnoreRepeatedPitches;
};

} //namespace IMUSANT
#endif
