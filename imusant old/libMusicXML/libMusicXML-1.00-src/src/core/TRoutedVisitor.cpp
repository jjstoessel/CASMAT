/*
  Copyright © Grame 2003

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
    grame@grame.fr

*/

#include "TRoutedVisitor.h"
#include "LibMusicXML.h"

using namespace MusicXML;

namespace MusicXML 
{

//________________________________________________________________________
TRoutedVisitor::TRoutedVisitor(){}
TRoutedVisitor::~TRoutedVisitor(){}

//________________________________________________________________________
void TRoutedVisitor::visite ( SAccidentalMark& elt ) {
	elt->position().accept(*this);
	elt->placement().accept(*this);
}

//________________________________________________________________________
void TRoutedVisitor::visite ( SArpeggiate& elt ) {
	elt->position().accept(*this);
	elt->placement().accept(*this);
}

//________________________________________________________________________
void TRoutedVisitor::visite ( SNonArpeggiate& elt ) {
	elt->position().accept(*this);
	elt->placement().accept(*this);
}

//________________________________________________________________________
void TRoutedVisitor::visite ( SArticulationElement& elt ) {
	elt->position().accept(*this);
	elt->placement().accept(*this);
}

void TRoutedVisitor::visite ( SArticulations& elt ) { elt->articulations().accept(*this); }

//________________________________________________________________________
void TRoutedVisitor::visite ( SAttributes& elt ) 
{
	elt->editorial().accept(*this);
    if ((TKey *)elt->key()) 			elt->key()->accept(*this);
    if ((TTimeSign*)elt->timeSign()) 	elt->timeSign()->accept(*this);
    elt->clefs().accept(*this);
    if ((TTranspose *)elt->transpose()) 	elt->transpose()->accept(*this);
    if ((TDirective *)elt->directive()) 	elt->directive()->accept(*this);
}

//________________________________________________________________________
void TRoutedVisitor::visite ( SBarline& elt ) 
{
	elt->editorial().accept(*this);
    if ((TWavyLine*)elt->wavyLine()) 	elt->wavyLine()->accept(*this);
    if ((TSegno *)elt->segno()) 		elt->segno()->accept(*this);
    if ((TCoda *)elt->coda()) 			elt->coda()->accept(*this);
    if ((TFermata *)elt->fermata()) 	elt->fermata()->accept(*this);
    if ((TEnding *)elt->ending()) 		elt->ending()->accept(*this);
    if ((TRepeat *)elt->repeat()) 		elt->repeat()->accept(*this);
}

//________________________________________________________________________
void TRoutedVisitor::visite ( SBracket& elt )  { elt->position().accept (*this); }
void TRoutedVisitor::visite ( SCoda& elt )  { elt->position().accept (*this); }
void TRoutedVisitor::visite ( SChord& elt )  { elt->notes().accept (*this); }
void TRoutedVisitor::visite ( SDashes& elt ) { elt->position().accept (*this); }

//________________________________________________________________________
void TRoutedVisitor::visite ( SBendWithBar& elt )
{
    elt->position().accept(*this);
    elt->placement().accept(*this);
}

//________________________________________________________________________
void TRoutedVisitor::visite ( SBend& elt )
{
    elt->position().accept(*this);
    elt->placement().accept(*this);
    elt->bendSound().accept(*this);
}

//________________________________________________________________________
void TRoutedVisitor::visite ( SDirection& elt )
{
    elt->placement().accept(*this);
	elt->types().accept(*this);
	elt->editorial().accept(*this);
    if ((TSound *)elt->sound())
        elt->sound()->accept(*this);
}

//________________________________________________________________________
void TRoutedVisitor::visite ( SDirectionType& elt ) 
{
	elt->elements().accept(*this);
}

//________________________________________________________________________
void TRoutedVisitor::visite ( SDynamic& elt ) 
{
    elt->position().accept (*this);
    elt->placement().accept (*this);
}

//________________________________________________________________________
void TRoutedVisitor::visite ( SFiguredBass& elt ) 
{
    elt->position().accept(*this);
	elt->printout().accept (*this);
    elt->figures().accept(*this);
	elt->editorial().accept(*this);
}

//________________________________________________________________________
void TRoutedVisitor::visite ( SFingering& elt ) {
	elt->position().accept(*this);
	elt->placement().accept(*this);
	elt->font().accept(*this);
}

//________________________________________________________________________
void TRoutedVisitor::visite ( SFrame& elt ) {
	elt->frameNotes().accept(*this);
}

//________________________________________________________________________
void TRoutedVisitor::visite ( SFrameNote& elt ) {
	if (elt->fingering()) elt->fingering()->accept(*this);
}

//________________________________________________________________________
void TRoutedVisitor::visite ( SFermata& elt )   { elt->position().accept (*this); }
void TRoutedVisitor::visite ( SGlissando& elt ) { elt->position().accept(*this); }

//________________________________________________________________________
void TRoutedVisitor::visite ( SSlide& elt ) 
{
    elt->position().accept(*this);
    elt->bendSound().accept(*this);
}

//________________________________________________________________________
void TRoutedVisitor::visite ( SHarmonic& elt ) 
{
    elt->position().accept (*this);
    elt->placement().accept (*this);
}

//________________________________________________________________________
void TRoutedVisitor::visite ( SHarmony& elt )  { 
	elt->position().accept(*this);
	elt->placement().accept(*this);
	elt->getHarmonyChords().accept(*this);
	if (elt->frame())
		elt->frame()->accept(*this);
	elt->editorial().accept(*this);
}

//________________________________________________________________________
void TRoutedVisitor::visite ( SHarmonyChord& elt )  { 
	if (elt->getRootFunction()) elt->getRootFunction()->accept(*this);
	if (elt->getBass())			elt->getBass()->accept(*this);
	elt->getDegrees().accept(*this);
}

//________________________________________________________________________
void TRoutedVisitor::visite ( SRehearsal& elt ) {
    elt->position().accept (*this);
    elt->font().accept (*this);
}

//________________________________________________________________________
void TRoutedVisitor::visite ( SHammerPull& elt ) 
{
    elt->position().accept (*this);
    elt->placement().accept (*this);
    elt->font().accept (*this);
}

//________________________________________________________________________
void TRoutedVisitor::visite ( SGraphNote& elt )
{
	elt->printout().accept (*this);
	if ((TAccidental *)elt->accidental()) elt->accidental()->accept (*this);
	if ((TTimeModification *)elt->timemodification()) elt->timemodification()->accept (*this);
	if ((TNoteHead *)elt->notehead()) elt->notehead()->accept (*this);
	elt->beamList().accept(*this);
	elt->notationList().accept(*this);
}

//________________________________________________________________________
void TRoutedVisitor::visite ( SGrouping& elt )
{
	elt->getFeatures().accept(*this);
}

//________________________________________________________________________
void TRoutedVisitor::visite ( SIdentification& elt ) 
{
	elt->creators().accept(*this);
	elt->rights().accept(*this);
    if ((TEncoding *)elt->encoding())
		elt->encoding()->accept(*this);
}

//________________________________________________________________________
/*!
\todo route to the font associated to the text elements
*/
void TRoutedVisitor::visite ( SLyric& elt ) 
{
	elt->getMultipleParts().accept(*this);
	elt->editorial().accept(*this);
}

//________________________________________________________________________
void TRoutedVisitor::visite ( SMiscId& elt )  { elt->getFields().accept(*this); }
void TRoutedVisitor::visite ( SMeasureStyle& elt )  { elt->getStyle()->accept(*this); }
void TRoutedVisitor::visite ( SNotation& elt )  { 
	elt->editorial().accept(*this);
	elt->list().accept(*this); 
}

//________________________________________________________________________
void TRoutedVisitor::visite ( SNote& elt ) 
{
	elt->position().accept(*this);
	if (elt->graphics())
		elt->graphics()->printout().accept(*this);
	if ((TExpression *)elt->expression())
		elt->expression()->accept(*this);
	if ((elt->getStyle() == TNote::grace) && (TGraceNote *)elt->graceNote())
		elt->graceNote()->accept(*this);
	if((TPitch *)elt->pitch()) 
		elt->pitch()->accept (*this);
	if ((TGraphNote *)elt->graphics())
		elt->graphics()->accept (*this);
}

//________________________________________________________________________
void TRoutedVisitor::visite ( SOctaveShift& elt ) { elt->position().accept (*this); }
void TRoutedVisitor::visite ( SOrnament& elt ) {
    elt->position().accept (*this);
    elt->placement().accept (*this);
	elt->accidents().accept (*this);
}

//________________________________________________________________________
void TRoutedVisitor::visite ( SOrnaments& elt ) { elt->ornaments().accept (*this);}
void TRoutedVisitor::visite ( SPWMeasure& elt ) { elt->data().accept(*this); }
void TRoutedVisitor::visite ( SPWPart& elt ) { elt->measures().accept(*this); }
void TRoutedVisitor::visite ( SPartList& elt )  { elt->parts().accept(*this); }

//________________________________________________________________________
void TRoutedVisitor::visite ( SScoreHeader& elt ) 
{
	if ((TWork *)elt->work())
        elt->work()->accept(*this);
	if ((TIdentification *)elt->identification())
        elt->identification()->accept (*this);
    if ((TPartList *)elt->partList())
        elt->partList()->accept (*this);
}

//________________________________________________________________________
void TRoutedVisitor::visite ( SScorePart& elt ) 
{
    if ((TIdentification *)elt->identification())
        elt->identification()->accept(*this);
    elt->scoreInstruments().accept(*this);
    if ((TMidiDevice *)elt->mididevice())
        elt->mididevice()->accept(*this);
    elt->midiInstruments().accept(*this);
}

//________________________________________________________________________
void TRoutedVisitor::visite ( SScorePartwise& elt ) 
{
	if ((TScoreHeader *)elt->scoreHeader())
        elt->scoreHeader()->accept(*this);    
    elt->partList().accept(*this);
}

//________________________________________________________________________
void TRoutedVisitor::visite ( SScoreTimewise& elt ) 
{
	if ((TScoreHeader *)elt->scoreHeader())
        elt->scoreHeader()->accept(*this);    
    elt->measureList().accept(*this);
}

//________________________________________________________________________
void TRoutedVisitor::visite ( SSegno& elt ) { elt->position().accept(*this); }
void TRoutedVisitor::visite ( SStaffDetails& elt ) { elt->tuning().accept(*this); }
void TRoutedVisitor::visite ( SSound& elt ) { elt->instrumentList().accept(*this); }

//________________________________________________________________________
void TRoutedVisitor::visite ( SStrongAccent& elt )  {
	elt->position().accept(*this);
	elt->placement().accept(*this);
}

//________________________________________________________________________
void TRoutedVisitor::visite ( STWMeasure& elt ) { elt->parts().accept(*this); }
void TRoutedVisitor::visite ( STWPart& elt )	{ elt->data().accept(*this); }

//________________________________________________________________________
void TRoutedVisitor::visite ( SSlur& elt ) {
    elt->position().accept(*this);
    elt->placement().accept(*this);
    elt->orientation().accept(*this);
}

//________________________________________________________________________
void TRoutedVisitor::visite ( STechnical& elt ) 
{
    elt->position().accept (*this);
    elt->placement().accept (*this);
}

//________________________________________________________________________
void TRoutedVisitor::visite ( STechnicals& elt )  { elt->technicals().accept (*this); }

//________________________________________________________________________
void TRoutedVisitor::visite ( STie& elt ) {
    elt->position().accept(*this);
    elt->placement().accept(*this);
    elt->orientation().accept(*this);
}

//________________________________________________________________________
void TRoutedVisitor::visite ( STrillOrnament& elt) {
	elt->position().accept (*this);
	elt->placement().accept (*this);
    elt->trill().accept (*this);
}

//________________________________________________________________________
void TRoutedVisitor::visite ( STuplet& elt ) {
    elt->position().accept(*this);
    elt->placement().accept(*this);
    if ((TTupletDesc*)elt->actualDesc())  elt->actualDesc()->accept(*this);
    if ((TTupletDesc*)elt->normalDesc())  elt->normalDesc()->accept(*this);
}

//________________________________________________________________________
void TRoutedVisitor::visite ( SWedge& elt )		{ elt->position().accept (*this); }
void TRoutedVisitor::visite ( SWords& elt )		{ 
	elt->position().accept (*this);
	elt->font().accept (*this);
}

} // namespace MusicXML
