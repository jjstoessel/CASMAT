/*
 *  IMUSANT_part.h
 *  imusant - the Intertextual MUSic Analysis Tool
 *	Project Supervisor: Dr Rex Eakins
 *
 *  Created by Jason Stoessel on 23/05/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

/*!
\brief The part element
*/

#ifndef __IMUSANT_part__
#define __IMUSANT_part__

#include "smartclasses.h"
#include "IMUSANT_measure.h"

#include <string>

using namespace std;

namespace IMUSANT
{

class VEXP IMUSANT_part : public smartable, public IMUSANT_visitable 
{
	public:
		VEXP friend SMARTP<IMUSANT_part> new_IMUSANT_part();
		
		void	addMeasure(const S_IMUSANT_measure& measure) { fMeasures.push_back(measure); }
		
		const string& getPartName() { return fPartName; }
		const string& getPartAbbrev() { return fPartAbbrev; }
		const string& getID() { return fXMLID; }
		
		void	setPartName( const string& partName ) { fPartName = partName; }
		void	setPartAbbrev( const string& partAbbrev ) { fPartAbbrev = partAbbrev; }
		void	setVoiceCount(const long voiceCount) { fVoiceCount = voiceCount; } //test variable?
		void	setID( const string& ID) { fXMLID = ID; }
		
		S_IMUSANT_measure&	getCurrentMeasure() { return fMeasures.back(); }
		IMUSANT_vector<S_IMUSANT_measure> measures() { return fMeasures; }
    
        IMUSANT_vector<S_IMUSANT_note> notes();
		
		void	print(ostream& os);
		
		void accept(IMUSANT_visitor& visitor);
		
	protected:
				IMUSANT_part();
		virtual ~IMUSANT_part(){}
	private:
    
		IMUSANT_vector<S_IMUSANT_measure>	fMeasures;
		long	fVoiceCount = 0;
		string 					fPartName = "";
        string 					fPartAbbrev = "";
		string 					fXMLID = "";
};
typedef SMARTP<IMUSANT_part> S_IMUSANT_part;

VEXP SMARTP<IMUSANT_part> new_IMUSANT_part();
    
} //namespace IMUSANT
#endif