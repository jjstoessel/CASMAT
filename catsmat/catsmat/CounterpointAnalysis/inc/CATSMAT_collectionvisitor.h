/*
 *  CATSMAT_collectionvisitor.h
 *  catsmat
 *
 *  Created by Jason Stoessel on 08/03/2015.
 *  Copyright 2015 Jason Stoessel. All rights reserved.
 *
 *	This class visits an IMUSANT score and builds an in-memory representation
 *	of the score.
 *
 *	Data collected:
 *		- notes, segmented into durations representing contrapuntal blocks
 */
#ifndef __CATSMAT_COLLECTION_VISITOR__
#define __CATSMAT_COLLECTION_VISITOR__

#include "IMUSANT_collection_visitor.h"
#include "IMUSANT_contour_symbol.h"
#include "IMUSANT_visitor.h"
#include "IMUSANT_pitch.h"
#include "CATSMAT_cp_matrix.h"

using namespace std;

namespace CATSMAT
{
    
class VEXP CATSMAT_collection_visitor : public IMUSANT_collection_visitor
{
	public:
					CATSMAT_collection_visitor();
                    ~CATSMAT_collection_visitor() {}
		
		void visit ( S_IMUSANT_chord& elt );
		void visit ( S_IMUSANT_measure& elt );
        void visit ( S_IMUSANT_barline& );
		void visit ( S_IMUSANT_note& elt );
		void visit ( S_IMUSANT_part& elt );
		void visit ( S_IMUSANT_score& elt );
    
    //virtual bool is_a_canon() = 0; //virtual function until written!
    //const S_CATSMAT_cp_matrix getCPMatrix() { return fCPMatrix; }
    const S_CATSMAT_cp_matrix_visitable getCPMatrix() const { return fCPMatrix; }

    void processCollections();
    
	protected:
		
	private:
		
        //local storage of counterpoint matrix                                                  
        S_CATSMAT_cp_matrix_visitable    fCPMatrix;
    
};

} //namespace CATSMAT
#endif //__CATSMAT_COLLECTION_VISITOR__
