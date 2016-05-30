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

class IMUSANT_chord : public IMUSANT_element
{
	public:
		enum sorttype { pitch, duration };
	
		friend SMARTP<IMUSANT_chord> new_IMUSANT_chord();
		
		void    accept(IMUSANT_visitor& visitor);
	
		void	add(const S_IMUSANT_note& note) { fChordNotes.push_back(note); }
	
		IMUSANT_vector<S_IMUSANT_note>& getNotes() { return fChordNotes; }
	
		void	sort(sorttype type = pitch);
		
		void	print(ostream& os) const;
        void    print_short(ostream& os) const;
	
	protected:
	
					IMUSANT_chord() {}
		virtual		~IMUSANT_chord() {}
	
		IMUSANT_vector<S_IMUSANT_note> fChordNotes;
    
        struct sortstruct
        {
            IMUSANT_chord* m;
            
            sortstruct(IMUSANT_chord* p) : m(p) {}
            bool operator() (S_IMUSANT_note a, S_IMUSANT_note b) { return *a < *b; }
    
        };
};
typedef SMARTP<IMUSANT_chord> S_IMUSANT_chord;


VEXP SMARTP<IMUSANT_chord> new_IMUSANT_chord();

} //namespace IMUSANT
#endif