/*
 *  IMUSANT_comment.h
 *  imusant - the Intertextual MUSic ANalysis Tool
 *	Project Supervisor: Dr Rex Eakins
 *
 *  Created by Jason Stoessel on 23/05/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef __IMUSANT_comment__
#define __IMUSANT_comment__

#include "IMUSANT_element.h"
#include <string>

using namespace std;

namespace IMUSANT
{

class VEXP IMUSANT_comment : public IMUSANT_element {
	public:
        VEXP friend SMARTP<IMUSANT_comment> new_IMUSANT_comment(string name);
        void accept(IMUSANT_visitor& visitor);
		void print(ostream& os);
	protected:
		IMUSANT_comment(string name) : fComment("\\"+name) {}
		virtual ~IMUSANT_comment() {}
	private:
		string fComment;
};
typedef SMARTP<IMUSANT_comment> S_IMUSANT_comment;

VEXP SMARTP<IMUSANT_comment> new_IMUSANT_comment(string name);
    
} //namespace IMUSANT
#endif