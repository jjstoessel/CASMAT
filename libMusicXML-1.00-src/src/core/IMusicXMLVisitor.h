/*
  Copyright © Grame 2003-2004

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.
    
    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.
    
    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Grame Research Laboratory, 9, rue du Garet 69001 Lyon - France
    research@grame.fr

*/

#ifndef __IMusicXMLVisitor__
#define __IMusicXMLVisitor__

#include <stack>

#include "TScoreVisitor.h"
#include "xml.h"

namespace MusicXML 
{

/*!
\internal
\brief A Visitor of MusicXML scores.

	TScoreVisitor implements the concept of visitors as defined in
	<e>Design Patterns - Elements of Reusable Object-Oriented Software</e>
	E. Gamma, R.Helm, R.Johnson, J.Vlissides - Addison-Wesley 1999
*/
class VEXP TMusicXMLVisitor : public TScoreVisitor {

    public:
		TMusicXMLVisitor();
		virtual ~TMusicXMLVisitor() {}

		void visite ( SAccidental& elt );
		void visite ( SAccidentalMark& elt );
		void visite ( SArpeggiate& elt );
		void visite ( SNonArpeggiate& elt );
		void visite ( SArticulationElement& elt );
		void visite ( SArticulations& elt );
		void visite ( SAttributes& elt );
		void visite ( SBackup& elt );
		void visite ( SBarline& elt );
		void visite ( SBass& elt );
		void visite ( SBeam& elt );
		void visite ( SBeatRepeat& elt );
		void visite ( SBendWithBar& elt );
		void visite ( SBend& elt );
		void visite ( SBracket& elt );
		void visite ( SChord& elt );
		void visite ( SClef& elt );
		void visite ( SCoda& elt );
		void visite ( SCreator& elt );
		void visite ( SDashes& elt );
		void visite ( SDegree& elt );
		void visite ( SDirection& elt );
		void visite ( SDirectionType& elt );
		void visite ( SDirective& elt );
		void visite ( SDynamic& elt );
		void visite ( SEncoding& elt );
		void visite ( SEnding& elt );
		void visite ( SExpression& elt );
		void visite ( SFeature& elt );
		void visite ( SFermata& elt );
		void visite ( SFigure& elt );
		void visite ( SFiguredBass& elt );
		void visite ( SFingering& elt );
		void visite ( SFootnote& elt );
		void visite ( SForward& elt );
		void visite ( SFrame& elt );
		void visite ( SFrameNote& elt );
		void visite ( SFunction& elt );
		void visite ( SGlissando& elt );
		void visite ( SGraceNote& elt );
		void visite ( SGraphNote& elt );
		void visite ( SGrouping& elt );
		void visite ( SHammerPull& elt );
		void visite ( SHarmonic& elt );
		void visite ( SHarmony& elt );
		void visite ( SHarmonyChord& elt );
		void visite ( SIdentification& elt );
		void visite ( SKey& elt );
		void visite ( SLevel& elt );
		void visite ( SLyric& elt );
		void visite ( SMetronome& elt );
		void visite ( SMeasureRepeat& elt );
		void visite ( SMeasureStyle& elt );
		void visite ( SMidiDevice& elt );
		void visite ( SMidiInstrument& elt );
		void visite ( SMiscField& elt );
		void visite ( SMiscId& elt );
		void visite ( SMordentOrnament& elt );
		void visite ( SMultipleLyricPart& elt );
		void visite ( SMultipleRest& elt );
		void visite ( SNotation& elt );
		void visite ( SNote& elt );
		void visite ( SNoteHead& elt );
		void visite ( SOctaveShift& elt );
		void visite ( SOrnament& elt );
		void visite ( SOrnaments& elt );
		void visite ( SOtherArticulation& elt );
		void visite ( SOtherDirection& elt );
		void visite ( SOtherDirections& elt );
		void visite ( SOtherNotation& elt );
		void visite ( SOtherOrnament& elt );
		void visite ( SPCData& elt );
		void visite ( SPWMeasure& elt );
		void visite ( SPWPart& elt );
		void visite ( SPartGroup& elt );
		void visite ( SPartList& elt );
		void visite ( SPedal& elt );
		void visite ( SPitch& elt );
		void visite ( SPrint& elt );
		void visite ( SRehearsal& elt );
		void visite ( SRepeat& elt );
		void visite ( SRest& elt );
		void visite ( SRights& elt );
		void visite ( SRoot& elt );
		void visite ( SScoreHeader& elt );
		void visite ( SScoreInstrument& elt );
		void visite ( SScorePart& elt );
		void visite ( SScorePartwise& elt );
		void visite ( SScoreTimewise& elt );
		void visite ( SSegno& elt );
		void visite ( SSlash& elt );
		void visite ( SSlur& elt );
		void visite ( SSlide& elt );
		void visite ( SStaffDetails& elt );
		void visite ( SStaffTuning& elt );
		void visite ( SSupport& elt );
		void visite ( SSound& elt );
		void visite ( SStrongAccent& elt );
		void visite ( STechnical& elt );
		void visite ( STechnicals& elt );
		void visite ( STWMeasure& elt );
		void visite ( STWPart& elt );
		void visite ( STie& elt );
		void visite ( STimeModification& elt );
		void visite ( STimeSign& elt );
		void visite ( STranspose& elt );
		void visite ( STrillOrnament& elt );
		void visite ( STuplet& elt );
		void visite ( STupletDesc& elt );
		void visite ( SUnpitched& elt );
		void visite ( SVoice& elt );
		void visite ( SWavyLine& elt );
		void visite ( SWedge& elt );
		void visite ( SWords& elt );
		void visite ( SWork& elt );

		void visite ( TOrientation* elt );
		void visite ( TPlacement* elt );
		void visite ( TPosition* elt );
		void visite ( TTrillSound* elt );
		void visite ( TBendSound* elt );
		void visite ( TFont* elt );
		void visite ( TPrintout* elt );
		void visite ( TEditorial* elt );
		void visite ( TBezier* elt );

		Sxmlelement& current ()			{ return fStack.top(); }

	private:
		void tieslur ( STieSlur& elt );
		void noteAttributes (SNote& note);
		void normalNote (SNote& note);
		void cueNote 	(SNote& note);
		void graceNote 	(SNote& note);

		void addFullNote(SNote& note);
		void addDuration(SNote& note);
		void addTies	(SNote& note);
		void addCommon	(SNote& note);

		void add (Sxmlelement& elt)		{ fStack.top()->add(elt); }
		void start (Sxmlelement& elt)	{ fStack.push(elt); }
		void push (Sxmlelement& elt)	{ add(elt); fStack.push(elt); }
		void pop ()						{ fStack.pop(); }

		std::stack<Sxmlelement>	fStack;
		// global flag to denote chords writing
		bool				fInChord;
};

} // namespace MusicXML


#endif
