/*
 *  IMUSANT_visitor.h
 *  imusant  - the Intertextual MUSic ANalysis Tool
 *	Project Supervisor: Dr Rex Eakins
 *
 *  Created by Jason Stoessel on 22/03/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __IMUSANT_visitor__
#define __IMUSANT_visitor__

#include "exports.h"
#include "smartpointer.h"

#include <string>
#include <vector>

using namespace std;

namespace IMUSANT
{

//forward declarations
typedef IMUSANT_SMARTP<class IMUSANT_element>			S_IMUSANT_element;
typedef IMUSANT_SMARTP<class IMUSANT_note>				S_IMUSANT_note;
typedef IMUSANT_SMARTP<class IMUSANT_comment>			S_IMUSANT_comment;
typedef IMUSANT_SMARTP<class IMUSANT_attributes>	    S_IMUSANT_attributes;
typedef IMUSANT_SMARTP<class IMUSANT_score>				S_IMUSANT_score;
typedef IMUSANT_SMARTP<class IMUSANT_chord>				S_IMUSANT_chord;
typedef IMUSANT_SMARTP<class IMUSANT_measure>			S_IMUSANT_measure;
typedef IMUSANT_SMARTP<class IMUSANT_part>				S_IMUSANT_part;
typedef IMUSANT_SMARTP<class IMUSANT_partlist>			S_IMUSANT_partlist;
typedef IMUSANT_SMARTP<class IMUSANT_lyric>				S_IMUSANT_lyric;
typedef IMUSANT_SMARTP<class IMUSANT_barline>			S_IMUSANT_barline;

/*!
\brief an abstract generic IMUSANT visitor
*/
class IMUSANT_visitor {

    public:
		IMUSANT_visitor() {}
		virtual ~IMUSANT_visitor() {}

		virtual void visit ( S_IMUSANT_attributes& ) = 0;
		virtual void visit ( S_IMUSANT_barline& ) = 0;
		virtual void visit ( S_IMUSANT_chord& elt ) = 0;
		virtual void visit ( S_IMUSANT_comment& elt ) = 0;
		virtual void visit ( S_IMUSANT_element& elt ) = 0;
		virtual void visit ( S_IMUSANT_lyric& elt ) = 0;
		virtual void visit ( S_IMUSANT_measure& elt ) = 0;
		virtual void visit ( S_IMUSANT_note& elt ) = 0;
		virtual void visit ( S_IMUSANT_part& elt ) = 0;
		virtual void visit ( S_IMUSANT_partlist& elt ) = 0;
		virtual void visit ( S_IMUSANT_score& elt ) = 0;
		
};

/*!
\brief interface for visitable IMUSANT objects.
Can this be implemented as a template class with function?
*/
class IMUSANT_visitable {
	public:
        virtual void accept(IMUSANT_visitor& visitor) = 0;
};
/*! @} */

template <typename T> 
class IMUSANT_vector: public vector<T>, public IMUSANT_visitable {
    
    public:
        IMUSANT_vector() {}
        virtual ~IMUSANT_vector(){}
    
        void accept(IMUSANT_visitor& visitor) {
			typename vector<T>::iterator iter;
			for (iter = this->begin(); iter != this->end(); iter++) 
				(*iter)->accept(visitor);
		}
    
        void append(IMUSANT_vector<T> vector_to_append)
        {
            this->insert(this->end(), vector_to_append.begin(), vector_to_append.end());
        }
};

} //namespace IMUSANT
#endif
