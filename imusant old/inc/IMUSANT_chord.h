/*
 *  IMUSANT_chord.h
 *  imusant - the Intertextual MUSic ANalysis Tool
 *	Project Supervisor: Dr Rex Eakins
 *
 *  Created by Jason Stoessel on 23/05/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef __IMUSANT_chord__
#define __IMUSANT_chord__

#include "IMUSANT_note.h"
#include <vector>

using namespace std;

namespace IMUSANT
{

class VEXP IMUSANT_chord : public IMUSANT_element
{
	public:
		enum sorttype { pitch, duration };
	
		VEXP friend SMARTP<IMUSANT_chord> new_IMUSANT_chord();
		
		void accept(IMUSANT_visitor& visitor);
	
		void	add(const S_IMUSANT_note& note) { fChordNotes.push_back(note); }
	
		IMUSANT_vector<S_IMUSANT_note>& getNotes() { return fChordNotes; }
	
		void	sort(sorttype type);
		
		void	print(ostream& os);
	
	protected:
	
					IMUSANT_chord() {}
		virtual		~IMUSANT_chord() {}
	
		IMUSANT_vector<S_IMUSANT_note> fChordNotes;
};
typedef SMARTP<IMUSANT_chord> S_IMUSANT_chord;


VEXP SMARTP<IMUSANT_chord> new_IMUSANT_chord();

} //namespace IMUSANT
#endif