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

#include "TRolledVisitor.h"

using namespace MusicXML;

namespace MusicXML 
{

//________________________________________________________________________
TRolledVisitor::TRolledVisitor(TNodeVisitor * visitor):fVisitor(visitor){}
TRolledVisitor::~TRolledVisitor() {}
     
//________________________________________________________________________
void TRolledVisitor::visite ( SAccidental& elt ) 
{
    fVisitor->visiteEnter(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SArticulationElement& elt ) 
{
    fVisitor->visiteEnter(elt);
    TRoutedVisitor::visite(elt);
    fVisitor->visiteLeave(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SArticulations& elt )
{
    fVisitor->visiteEnter(elt);
    TRoutedVisitor::visite(elt);
    fVisitor->visiteLeave(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SAttributes& elt ) 
{
     fVisitor->visiteEnter(elt);
     TRoutedVisitor::visite(elt);
     fVisitor->visiteLeave(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SBackup& elt ) 
{
     fVisitor->visiteEnter(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SBarline& elt ) 
{
     fVisitor->visiteEnter(elt);
     TRoutedVisitor::visite(elt);
     fVisitor->visiteLeave(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SBeam& elt ) 
{
     fVisitor->visiteEnter(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SBracket& elt ) 
{
     fVisitor->visiteEnter(elt);
     TRoutedVisitor::visite(elt);
     fVisitor->visiteLeave(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SChord& elt ) 
{
    fVisitor->visiteEnter(elt);
    TRoutedVisitor::visite(elt);
    fVisitor->visiteLeave(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SClef& elt ) 
{
     fVisitor->visiteEnter(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SCoda& elt ) 
{
     fVisitor->visiteEnter(elt);
     TRoutedVisitor::visite(elt);
     fVisitor->visiteLeave(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SCreator& elt ) 
{
     fVisitor->visiteEnter(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SDashes& elt ) 
{
     fVisitor->visiteEnter(elt);
     TRoutedVisitor::visite(elt);
     fVisitor->visiteLeave(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SDirection& elt )
{
     fVisitor->visiteEnter(elt);
     TRoutedVisitor::visite(elt);
     fVisitor->visiteLeave(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SDirectionType& elt ) 
{
     fVisitor->visiteEnter(elt);
     TRoutedVisitor::visite(elt);
     fVisitor->visiteLeave(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SDirective& elt ) 
{
     fVisitor->visiteEnter(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SDynamic& elt ) 
{
     fVisitor->visiteEnter(elt);
     TRoutedVisitor::visite(elt);
     fVisitor->visiteLeave(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SEncoding& elt ) 
{
     fVisitor->visiteEnter(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SEnding& elt ) 
{
     fVisitor->visiteEnter(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SExpression& elt ) 
{
     fVisitor->visiteEnter(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SFermata& elt )
{
     fVisitor->visiteEnter(elt);
     TRoutedVisitor::visite(elt);
     fVisitor->visiteLeave(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SForward& elt ) 
{
     fVisitor->visiteEnter(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SGraceNote& elt ) 
{
     fVisitor->visiteEnter(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SGraphNote& elt )
{
     fVisitor->visiteEnter(elt);
     TRoutedVisitor::visite(elt);
     fVisitor->visiteLeave(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SIdentification& elt ) 
{
     fVisitor->visiteEnter(elt);
     TRoutedVisitor::visite(elt);
     fVisitor->visiteLeave(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SKey& elt ) 
{
     fVisitor->visiteEnter(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SMeasure& elt ) 
{
     fVisitor->visiteEnter(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SMetronome& elt ) 
{
     fVisitor->visiteEnter(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SMidiDevice& elt ) 
{
     fVisitor->visiteEnter(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SMidiInstrument& elt ) 
{
     fVisitor->visiteEnter(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SNotation& elt ) 
{
     fVisitor->visiteEnter(elt);
     TRoutedVisitor::visite(elt);
     fVisitor->visiteLeave(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SNote& elt ) 
{
     fVisitor->visiteEnter(elt);
     TRoutedVisitor::visite(elt);
     fVisitor->visiteLeave(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SNoteHead& elt ) 
{
     fVisitor->visiteEnter(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SOctaveShift& elt ) 
{
     fVisitor->visiteEnter(elt);
     TRoutedVisitor::visite(elt);
     fVisitor->visiteLeave(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SPWMeasure& elt ) 
{
     fVisitor->visiteEnter(elt);
     TRoutedVisitor::visite(elt);
     fVisitor->visiteLeave(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SPWPart& elt )
{
     fVisitor->visiteEnter(elt);
     TRoutedVisitor::visite(elt);
     fVisitor->visiteLeave(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SPart& elt ) 
{   
     fVisitor->visiteEnter(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SPartGroup& elt ) 
{
     fVisitor->visiteEnter(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SPartList& elt ) 
{
     fVisitor->visiteEnter(elt);
     TRoutedVisitor::visite(elt);
     fVisitor->visiteLeave(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SPitch& elt ) 
{
     fVisitor->visiteEnter(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SRepeat& elt ) 
{
     fVisitor->visiteEnter(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SRest& elt ) 
{
     fVisitor->visiteEnter(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SRights& elt ) 
{
     fVisitor->visiteEnter(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SScoreHeader& elt ) 
{
     fVisitor->visiteEnter(elt);
     TRoutedVisitor::visite(elt);
     fVisitor->visiteLeave(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SScoreInstrument& elt ) 
{
     fVisitor->visiteEnter(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SScorePart& elt ) 
{
     fVisitor->visiteEnter(elt);
     TRoutedVisitor::visite(elt);
     fVisitor->visiteLeave(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SScorePartwise& elt ) 
{
     fVisitor->visiteEnter(elt);
     TRoutedVisitor::visite(elt);
     fVisitor->visiteLeave(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SScoreTimewise& elt ) 
{
     fVisitor->visiteEnter(elt);
     TRoutedVisitor::visite(elt);
     fVisitor->visiteLeave(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SSegno& elt ) 
{
     fVisitor->visiteEnter(elt);
     TRoutedVisitor::visite(elt);
     fVisitor->visiteLeave(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SSound& elt )
{
     fVisitor->visiteEnter(elt);
     TRoutedVisitor::visite(elt);
     fVisitor->visiteLeave(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SStrongAccent& elt ) 
{
     fVisitor->visiteEnter(elt);
     TRoutedVisitor::visite(elt);
     fVisitor->visiteLeave(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( STWMeasure& elt ) 
{
     fVisitor->visiteEnter(elt);
     TRoutedVisitor::visite(elt);
     fVisitor->visiteLeave(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( STWPart& elt ) 
{
     fVisitor->visiteEnter(elt);
     TRoutedVisitor::visite(elt);
     fVisitor->visiteLeave(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SSlur& elt ) 
{
     fVisitor->visiteEnter(elt);
     TRoutedVisitor::visite(elt);
     fVisitor->visiteLeave(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( STie& elt ) 
{
     fVisitor->visiteEnter(elt);
     TRoutedVisitor::visite(elt);
     fVisitor->visiteLeave(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( STimeModification& elt ) 
{
     fVisitor->visiteEnter(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( STimeSign& elt ) 
{
     fVisitor->visiteEnter(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( STranspose& elt ) 
{
     fVisitor->visiteEnter(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( STuplet& elt )
{
     fVisitor->visiteEnter(elt);
     TRoutedVisitor::visite(elt);
     fVisitor->visiteLeave(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( STupletDesc& elt ) 
{
     fVisitor->visiteEnter(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SUnpitched& elt ) 
{
     fVisitor->visiteEnter(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SWavyLine& elt)
{
     fVisitor->visiteEnter(elt);
     TRoutedVisitor::visite(elt);
     fVisitor->visiteLeave(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SWedge& elt ) 
{
     fVisitor->visiteEnter(elt);
     TRoutedVisitor::visite(elt);
     fVisitor->visiteLeave(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SWords& elt ) 
{
     fVisitor->visiteEnter(elt);
     TRoutedVisitor::visite(elt);
     fVisitor->visiteLeave(elt);
}

//________________________________________________________________________
void TRolledVisitor::visite ( SWork& elt ) 
{
     fVisitor->visiteEnter(elt);
}


} // namespace MusicXML
