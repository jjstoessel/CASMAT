/*
 *  IMUSANT_collectionvisitor.h
 *  imusant
 *
 *  Created by Jason Stoessel on 24/06/06.
 *  Copyright 2006 Jason Stoessel. All rights reserved.
 *
 *	This class visits an IMUSANT score and collects information that is 
 *	then ready to output (using another visitor class to be implemented).
 *	Data collected:
 *		- movement data, title, creators, originating data file
 *		- basic musical features: range, key, final, number of notes & rests, no. of alterations
 *		- interval segments, including matched instances (useful for "fingerprinting" individual pieces)
 *		- rhythm segments, including matched instances
 */
#ifndef __IMUSANT_COLLECTION_VISITOR__
#define __IMUSANT_COLLECTION_VISITOR__

#include <map>

#include "IMUSANT_interval_vector.h"
#include "IMUSANT_contour_symbol.h"
#include "IMUSANT_visitor.h"
#include "IMUSANT_pitch.h"
#include "IMUSANT_duration.h"
#include "IMUSANT_common.h"

#define NEW
//#define OLD

using namespace std;

namespace IMUSANT
{

    class IMUSANT_pitch_vector : public smartable, public vector<IMUSANT_pitch>
    {
    public:
        
        friend IMUSANT_SMARTP<IMUSANT_pitch_vector> new_IMUSANT_pitch_vector();
        
        vector<IMUSANT_pitch>& getPitches() { return *this; }
        
    };
    typedef IMUSANT_SMARTP<IMUSANT_pitch_vector> S_IMUSANT_pitch_vector;
    S_IMUSANT_pitch_vector new_IMUSANT_pitch_vector();
    
    class IMUSANT_rhythm_vector : public smartable, public vector<IMUSANT_duration>
    {
    public:
        friend IMUSANT_SMARTP<IMUSANT_rhythm_vector>  new_IMUSANT_rhythm_vector();
        
        vector<IMUSANT_duration>& getDurations() { return *this; }
        
    };
    typedef IMUSANT_SMARTP<IMUSANT_rhythm_vector> S_IMUSANT_rhythm_vector;
    S_IMUSANT_rhythm_vector new_IMUSTANT_rhythm_vector();
    
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

            const vector<S_IMUSANT_interval_vector>&    getPartwiseIntervalVectors() const {return fPartwiseIntervalVectors; }
            const vector<S_IMUSANT_contour>&            getPartwiseContourVectors() const {return fPartwiseContourVectors; }
            const vector<S_IMUSANT_pitch_vector>&       getPartwisePitchVectors() const { return fPartwisePitchVectors; }
            const vector<S_IMUSANT_rhythm_vector>&      getPartwiseRhythmVectors() const { return fPartwiseRhythmVectors; }
    
            const string& getMovementTitle() const { return fMovementTitle; }
            const string& getWorkTitle() const { return fWorkTitle; }
        
            void ignoreRepeatedPitches(bool ignore) { fIgnoreRepeatedPitches = ignore; }
        
        virtual void processCollections() {};
        
        protected:
            
        private:
        
            //local storage of vectors
            S_IMUSANT_interval_vector           fCurrentIntervalVector;
            S_IMUSANT_contour                   fCurrentMelodicContour;
            S_IMUSANT_pitch_vector              fCurrentPitchVector;
            S_IMUSANT_rhythm_vector             fCurrentRhythmVector;
        
            //storage of vectors of elements in each part
            vector<S_IMUSANT_interval_vector>   fPartwiseIntervalVectors;
            vector<S_IMUSANT_contour>           fPartwiseContourVectors;
            vector<S_IMUSANT_pitch_vector>      fPartwisePitchVectors;
            vector<S_IMUSANT_rhythm_vector>     fPartwiseRhythmVectors;
        
            string              fWorkTitle;
            string              fMovementTitle;
            string              fWorkNum;
            string              fMovementNum;
            STRPAIRVECTOR		fCreator;
            STRPAIRVECTOR		fRights;
            string				fScoreComments;
            string				fSource;
            string				fEditor;
            string				fDate;
            map<int,string>     fLyrics;
        

            // global flag to denote chords writing
            bool			fInChord;
            S_IMUSANT_note	fLastNote;
            long			fCurrentPartID;
            bool			fIgnoreRepeatedPitches;
    };

} //namespace IMUSANT
#endif
