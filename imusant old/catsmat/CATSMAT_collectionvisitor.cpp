/*
 *  IMUSANT_collectionvisitor.cpp
 *  imusant
 *
 *  Created by Jason Stoessel on 08/03/2015.
 *  Copyright 2015 Jason Stoessel. All rights reserved.
 *
 *	This class is a visitor to IMUSANT_score for the purposes of collecting musical data for further manipulation.
 *  It inherits from IMUSANT_collectionvisitor, and overrides for the relevant functions
 */

#include "CATSMAT_collectionvisitor.hpp"
#include "IMUSANT_chord.h"
#include "IMUSANT_measure.h"
#include "IMUSANT_part.h"
#include "IMUSANT_partlist.h"
#include "IMUSANT_score.h"
#include "IMUSANT_barline.h"
#include "search.h"
#include "suffixtree.h"
#include "iterator.h"

#include <algorithm>

using namespace std;
using namespace IMUSANT;
using namespace ns_suffixtree;

namespace CATSMAT
{
    
CATSMAT_collection_visitor::CATSMAT_collection_visitor()
{
}

#pragma mark IMUSANT_chord handler
void CATSMAT_collection_visitor::visit ( S_IMUSANT_chord& elt )
{
    cerr << "Chord is currently not handled in CATSMAT_collection_visitor." << endl;
    
    IMUSANT_collection_visitor::visit(elt);
}


#pragma mark IMUSANT_measure handler
void CATSMAT_collection_visitor::visit ( S_IMUSANT_measure& elt )
{
    fCPMatrix->set(elt->getTime());
    
	IMUSANT_collection_visitor::visit(elt);
}

#pragma mark IMUSANT_note handler

void CATSMAT_collection_visitor::visit ( S_IMUSANT_note& elt )
{
    fCPMatrix->add(*elt);

	IMUSANT_collection_visitor::visit(elt);
}
    
#pragma mark IMUSANT_part handler
void CATSMAT_collection_visitor::visit ( S_IMUSANT_part& elt )
{
    fCPMatrix->addpart();
	
    IMUSANT_collection_visitor::visit(elt);
}


#pragma mark IMUSANT_score handler
void CATSMAT_collection_visitor::visit ( S_IMUSANT_score& elt )
{
    fCPMatrix = CATSMAT::new_CATSMAT_cp_matrix();
    
    IMUSANT_collection_visitor::visit(elt);
    
}


} //namespace CATSMAT