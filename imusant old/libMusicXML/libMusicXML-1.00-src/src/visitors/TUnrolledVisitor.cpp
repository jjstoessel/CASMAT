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

#include "TUnrolledVisitor.h"
#include "UTools.h"

using namespace MusicXML;

#define PRINT(x) { printf x; fflush(stdout); }
#define DBUG_Unrolled(x)  /* PRINT(x) */

namespace MusicXML 
{

//________________________________________________________________________
TUnrolledVisitor::TUnrolledVisitor(TNodeVisitor* visitor):TRolledVisitor(visitor){}
TUnrolledVisitor::~TUnrolledVisitor() {}

//________________________________________________________________________
void TUnrolledVisitor::visite(SPWMeasure& elt) 
{
      DBUG_Unrolled(("TUnrolledVisitor::SPWMeasure %ld\n",elt->getNumber()));
      TRolledVisitor::visite(elt);
}

/*
Strategy for unrolling: 

- there is a "begin section" measure pointer

- we look for repeat and ending measures
	- a repeat section is described by two repeat_begin and repeat_end pointers
	- the repeat_begin pointer will typically be the first measure, or an explicit "repeat forward" measure
	If the repeat_begin is not the first measure, the section before the found repeat_begin is added 

	- the repeat_end can be the measure just before the first "ending start" measure or an explicit "repeat backward" measure

	- an ending section is described by two ending_begin and ending_end pointers

- the repeat action is done when a "repeat backward" measure is encountered, and take in acount
	- first ending case
	- other ending cases 
	- normal repeat (not ending)

 
- the "begin section" measure pointer is reset

*/

void TUnrolledVisitor::visite(SPWPart& elt)
{
	vvector<SPWMeasure>::const_iterator begin,end,repeat_end,repeat_begin,ending_begin,ending_end,it;
  
	fVisitor->visiteEnter(elt);

	if (elt->measures().size() > 0) {
	
		fFirstMeasureIt = begin = elt->measures().begin();
		end = elt->measures().end();
		fCurMeasureIt = fBeginMeasureIt = fSegnoIt = fCodaIt = fFineIt = repeat_begin = fFirstMeasureIt;
		
		for (it = begin; it != end; it++) {
			
			fCurMeasureIt = it;
			SPWMeasure curMeasure = *it;
			curMeasure->accept(*this);
			
			// Look for the beginning of repeat section
			if (IsRepeatType(curMeasure,TRepeat::forward)) { 
				DBUG_Unrolled(("TUnrolledVisitor::IsRepeatStart\n"));
				repeat_begin = it;

				// Add section before repeat_begin
				AddSection(fBeginMeasureIt,repeat_begin-1);
				// Reset next section beginning pointer
				fBeginMeasureIt = fCurMeasureIt+1;
			}

			// Look for the beginning of ending section 
			if (IsEndingType(curMeasure,TEnding::start)) {
				ending_begin = it;
				// Look for the end of repeat section (ending case)
				if (GetEndingNum(curMeasure) == 1) {
					DBUG_Unrolled(("TUnrolledVisitor::IsEndingStart\n"));
					repeat_end = it-1;
				}	
			}	

			// Look for the end of repeat section (repeat case)	
			if (IsRepeatType(curMeasure,TRepeat::backward)) { 
				DBUG_Unrolled(("TUnrolledVisitor::IsRepeatStop\n"));
		
				// Look for the end of ending section (ending case)
				if (IsEndingType(curMeasure,TEnding::stop)) {
					DBUG_Unrolled(("TUnrolledVisitor::IsEndingStop\n"));
					ending_end = it;
			
					if (GetEndingNum(curMeasure) == 1){ // First ending case
						// Add the repeat section
						AddSection(repeat_begin,repeat_end);
						// Add the ending section
						AddSection(ending_begin,ending_end);

						// Do the repeat
						RepeatSection(repeat_begin,repeat_end);
						AddSection(repeat_begin,repeat_end);
					}else{ // All other ending cases
						// Add the ending section
						AddSection(ending_begin,ending_end);

						// Do the repeat
						RepeatSection(repeat_begin,repeat_end);
						AddSection(repeat_begin,repeat_end);
					}

				}else{
					repeat_end = it;
					
					// Add sections up to the repeat_backward
					AddSection(repeat_begin,repeat_end);

					// Do the repeat
					for (int i = 0; i < UTools::Max(1,GetRepeatTimes(curMeasure)-1); i++){ 
						RepeatSection(repeat_begin,repeat_end);
						AddSection(repeat_begin,repeat_end);
					}
				}

				// Reset next section beginning pointer
				fBeginMeasureIt = fCurMeasureIt+1;
			}		
		}

		/*
		If the score ends with a repeat measure, the corresponding section is already added,
		otherwise add the last section
		*/
		
		if (fBeginMeasureIt != end)
			AddSection(fBeginMeasureIt,fCurMeasureIt);
	}

    fVisitor->visiteLeave(elt);
}


//________________________________________________________________________________________________________________________
void TUnrolledVisitor::RepeatSection(vvector<SPWMeasure>::const_iterator begin, vvector<SPWMeasure>::const_iterator end)
{
    vvector<SPWMeasure>::const_iterator it, end1;
	
	// Repeat the [begin, end] section, thus the end test pointer is incremented
	end1 = end + 1;

	DBUG_Unrolled(("TUnrolledVisitor::RepeatSection  [%ld %ld[\n",(*begin)->getNumber(),(*end1)->getNumber()));
	  
	// Repeat from begin to end
	for (it = begin; it != end1; it++) {
        SPWMeasure measure = *it;
        measure->accept(*this);
    }
}

//________________________________________________________________________
bool TUnrolledVisitor::IsRepeatType(SMusicData& musicData, int type)
{
	SBarline barline;
	return ((barline = dynamic_cast<TBarline*>((TMusicData*)musicData)) 
			&& (barline->repeat() != 0)
			&& (barline->repeat()->getDirection() == type));
}

//________________________________________________________________________
bool TUnrolledVisitor::IsRepeatType(SPWMeasure& elt, int type)
{
	SMusicData musicData; 
	musicData = *elt->data().begin();  // First element of the measure
	if (IsRepeatType(musicData,type)) return true;
	musicData = *(elt->data().end()-1); // Last element of the measure
	if (IsRepeatType(musicData,type)) return true;
    return false;
}

//________________________________________________________________________
bool TUnrolledVisitor::IsEndingType(SMusicData& musicData, int type)
{
	SBarline barline;
	return ((barline = dynamic_cast<TBarline*>((TMusicData*)musicData)) 
			&& (barline->ending() != 0)
			&& (barline->ending()->getType() == type));
}

//________________________________________________________________________
bool TUnrolledVisitor::IsEndingType(SPWMeasure& elt, int type)
{   
	SMusicData musicData; 
	musicData = *elt->data().begin();  // First element of the measure
	if (IsEndingType(musicData,type)) return true;
	musicData = *(elt->data().end()-1); // Last element of the measure
	if (IsEndingType(musicData,type)) return true;
    return false;
}

//________________________________________________________________________
long TUnrolledVisitor::GetEndingNum(SPWMeasure& elt)
{
	SBarline barline;
  	SMusicData musicData = *elt->data().begin(); // First element of the measure
	return (barline = dynamic_cast<TBarline*>((TMusicData*)musicData)) ?  barline->ending()->getNum() : -1;
}

//________________________________________________________________________
long TUnrolledVisitor::GetRepeatTimes (SPWMeasure& elt)
{
	SBarline barline;
	SMusicData musicData = *(elt->data().end() - 1); // Last element of the measure
	return ((barline = dynamic_cast<TBarline*>((TMusicData*)musicData)) && (barline->repeat() != 0)) ?  barline->repeat()->getTimes() : 0;
}

//________________________________________________________________________________________________________________________
void TUnrolledVisitor::AddSection(vvector<SPWMeasure>::const_iterator begin, vvector<SPWMeasure>::const_iterator end)
{
	DBUG_Unrolled(("TUnrolledVisitor::AddSection \n"));
	DBUG_Unrolled(("TUnrolledVisitor::AddSection  [%ld %ld]\n",(*begin)->getNumber(),(*end)->getNumber()));

	fSectionList.push_back(make_pair((*begin)->getNumber(),(*end)->getNumber())); 
}

//________________________________________________________________________
void TUnrolledVisitor::visite(SSound& elt) 
{
	TRolledVisitor::visite(elt);
	
	if (elt->getSegno() != TSound::undefined) fSegnoIt = fCurMeasureIt;
	if (elt->getTocoda() != TSound::undefined) fCodaIt = fCurMeasureIt;
	if (elt->getFine() != TSound::undefined) fFineIt = fCurMeasureIt;
	
	if ((elt->getDalsegno() != TSound::undefined)||(elt->getDacapo() == YesNo::yes))  {
		DBUG_Unrolled(("TUnrolledVisitor:: segno to coda\n"));
		DBUG_Unrolled(("TUnrolledVisitor:: dacapo to coda\n"));

		/*
		To be improved : Coda and Fine signs are coded separately.
		(What happens if both sign appear in the score ??)
		*/
		
		if (fCodaIt != fFirstMeasureIt) {

			if (fSegnoIt != fFirstMeasureIt) {
				AddSection(fBeginMeasureIt,fSegnoIt-1);
				AddSection(fSegnoIt,fCodaIt);
				AddSection(fCodaIt+1,fCurMeasureIt);
			}else{
				AddSection(fBeginMeasureIt,fCodaIt);
				AddSection(fCodaIt+1,fCurMeasureIt);
			}

			// Add section corresponding to the repeated section
			AddSection(fSegnoIt,fCodaIt);
			
			// Reset next section beginning pointer
			fBeginMeasureIt = fCurMeasureIt+1;
		
			RepeatSection(fSegnoIt, fCodaIt); 

		}else if (fFineIt != fFirstMeasureIt) {

			if (fSegnoIt != fFirstMeasureIt) {
				AddSection(fBeginMeasureIt,fSegnoIt-1);
				AddSection(fSegnoIt,fFineIt);
				AddSection(fFineIt+1,fCurMeasureIt);
			}else{
				AddSection(fBeginMeasureIt,fFineIt);
				AddSection(fFineIt+1,fCurMeasureIt);
			}

			// Add section corresponding to the repeated section
			AddSection(fSegnoIt,fFineIt);
			
			// Reset next section beginning pointer
			fBeginMeasureIt = fCurMeasureIt+1;
		
			RepeatSection(fSegnoIt, fFineIt); 
		}		
	}
}

} // namespace MusicXML
