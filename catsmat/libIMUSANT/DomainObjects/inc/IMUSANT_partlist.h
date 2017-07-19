/*
 *  IMUSANT_partlist.h
 *  imusant - the Intertextual MUSic ANalysis Tool
 *	Project Supervisor: Dr Rex Eakins
 *
 *  Created by Jason Stoessel on 23/05/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef __IMUSANT_partlist__
#define __IMUSANT_partlist__

#include "IMUSANT_part.h"
#include <vector>

using namespace std;

namespace IMUSANT
{

class IMUSANT_partlist;
typedef IMUSANT_SMARTP<IMUSANT_partlist> 	S_IMUSANT_partlist;

class IMUSANT_partlist :  public smartable, public IMUSANT_visitable
{
    public:
		friend IMUSANT_SMARTP<IMUSANT_partlist> new_IMUSANT_partlist();
		friend	ostream& operator<<(ostream& os, S_IMUSANT_partlist& partlist);
		
		void					accept(IMUSANT_visitor& visitor);

        void					add(const S_IMUSANT_part& part) { fPartsList.push_back(part); }
		
		S_IMUSANT_part&			getPart(const string& ID);
		
        IMUSANT_vector<S_IMUSANT_part>& parts() 		{ return fPartsList; }
		
		void					print (ostream& os);
	
    protected:
        IMUSANT_partlist() {}
        virtual ~IMUSANT_partlist() {}
    private:
        IMUSANT_vector<S_IMUSANT_part> fPartsList; 
};

	typedef IMUSANT_SMARTP<IMUSANT_partlist> S_IMUSANT_partlist;
	IMUSANT_SMARTP<IMUSANT_partlist> new_IMUSANT_partlist();

} //namespace IMUSANT
#endif