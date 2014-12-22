/*
 *  TXML2IMUSANTVisitor.h
 *  imusant  - the Intertextual MUSic ANalysis Tool
 *	Project Supervisor: Dr Rex Eakins
 *
 *  Created by Jason Stoessel on 28/03/06.
 *  Copyright 2006 Jason Stoessel. All rights reserved.
 *
 */


#ifndef __TXML2IMUSANTVisitor__
#define __TXML2IMUSANTVisitor__

#include "exports.h"
#include "TNotation.h"
#include "TScorePartwise.h"
#include "TRoutedVisitor.h"
#include "TScanVisitor.h"
#include "TRational.h"
#include "IMUSANT_score.h"
#include "TNote.h"
#include "IMUSANT_pitch.h"
#include "IMUSANT_key.h"

#include <stack>

using namespace std;
using namespace MusicXML;

namespace IMUSANT
{

//type for collection of pitch/octave pair with accidental type
typedef map<pair<IMUSANT_pitch::type,unsigned short>,IMUSANT_accidental::accident> ACCIDENTALMAP;


/*!
\brief A score visitor to produce a imusant representation.
*/

class VEXP TXML2IMUSANTVisitor : public TRoutedVisitor, public smartable {


    public:
		TXML2IMUSANTVisitor(bool comments=true, bool checkStem=true, bool bar=false);
		virtual ~TXML2IMUSANTVisitor() {}

        VEXP friend SMARTP<TXML2IMUSANTVisitor> newXML2IMUSANTVisitor(bool comments, bool checkStem, bool bar);

		void visite ( SAccidental& elt );
		//void visite ( SArticulationElement& elt );
		//void visite ( SArticulations& elt );
		void visite ( SAttributes& elt );
		//void visite ( SBackup& elt );
		void visite ( SBarline& elt );
		//void visite ( SBeam& elt );
		//void visite ( SBracket& elt );
		void visite ( SChord& elt );
		void visite ( SClef& elt );
		//void visite ( SCoda& elt );
		void visite ( SCreator& elt );
		void visite ( SDirection& elt );
		void visite ( SDirectionType& elt );
		//void visite ( SDirective& elt );
		//void visite ( SDynamic& elt );
		//void visite ( SEncoding& elt );
		//void visite ( SEnding& elt );
		//void visite ( SFermata& elt );
		//void visite ( SForward& elt );
		//void visite ( SGraceNote& elt );
		void visite ( SGraphNote& elt );
		void visite ( SIdentification& elt );
		void visite ( SKey& elt );
		void visite ( SLyric& elt );
		//void visite ( SMetronome& elt );
		//void visite ( SMidiInstrument& elt );
		void visite ( SMultipleLyricPart& elt );
		//void visite ( SNotation& elt );
		void visite ( SNote& elt );
		//void visite ( SNoteHead& elt );
		//void visite ( SOctaveShift& elt );
		void visite ( SPWMeasure& elt );
		void visite ( SPWPart& elt );
		//void visite ( SPartGroup& elt );
		//void visite ( SPartList& elt );
		//void visite ( SPitch& elt );
		//void visite ( SRepeat& elt );
		//void visite ( SRest& elt );
		void visite ( SRights& elt );
		void visite ( SScoreHeader& elt );
		//void visite ( SScoreInstrument& elt );
		void visite ( SScorePart& elt );
		void visite ( SScorePartwise& elt );
		//void visite ( SSegno& elt );
		//void visite ( SSlur& elt );
		//void visite ( SSound& elt );
		//void visite ( SStrongAccent& elt );
		//void visite ( STie& elt );
		//void visite ( STimeModification& elt );
		void visite ( STimeSign& elt );
		//void visite ( STranspose& elt );
		//void visite ( STuplet& elt );
		//void visite ( STupletDesc& elt );
		//void visite ( SUnpitched& elt );
		//void visite ( SWavyLine& elt );
		//void visite ( SWedge& elt );
		void visite ( SWords& elt );
		void visite ( SWork& elt );
		
		S_IMUSANT_score&	getIMUSANTScore() { assert(fIMUSANTScore!=0); return fIMUSANTScore; }

	protected:
	
		long	fCurrentVoice;
		long	fCurrentDivision;
		bool	fMeasureEmpty;

	private:
		
		//bool checkgrace (const SNote& note);
		//bool checkcue 	(const SNote& note);
		//void checkstem 	(const SNote& note);
		
		void checkaccidental();
		
		S_IMUSANT_note IMUSANT_note (const SNote& note);
		
		void IMUSANT_partheader ( SScoreHeader& elt );

		// the root element: may be used to search for linked elements
		SScorePartwise		fScore;
		
		// this is for wedge element with stop attribute handling
		bool	fCrescPending;
		// this is used to scan a part as it may contain several staves and / or voices
		TScanVisitor	fScan;
		// a visitor used to scan the slurs and rewrite guido nested slurs (unnested in MusicXML)
		class SlursVisitor: public TRoutedVisitor {
			public:				
				int flag; int num;
				void visite ( SSlur& elt )	{ num++; flag |= elt->getType(); }
		} fSlurs;

        enum location { before, after };
        location fNotePass;
		long	fStaffPass;
		long	fStaffNum;
		long	fMeasNum;
		short	fNoteIndex;
		long	fCurrentStaff;
		int		fStemDirection; 
		
		TRational fCurTimeSign;
        
        SPartSummary fCurrentPart;

		bool	fInGrace;
		bool	fInChord;
		bool	fInCue;
		bool	fInRepeat;
		bool	fInTieSlur;
		bool	fBeamOpened;
		
		bool	fComments;
		bool	fCheckStem;
		
		vector<S_IMUSANT_note*>	fPreviousTieNoteList;
		//used to check is alterations are editorial
		ACCIDENTALMAP fPreviousAccidentals;
		//the IMUSANT Score storage class
		S_IMUSANT_score	fIMUSANTScore;
		//record of IMUSANT part currently in play
		S_IMUSANT_part	fCurrentIMUSANTPart;
		S_IMUSANT_note	fNote;
		S_IMUSANT_lyric fLyric;
		IMUSANT_key		fCurrentKey;
};
typedef SMARTP<TXML2IMUSANTVisitor> SXML2IMUSANTVisitor;

} //namespace IMUSANT
#endif
