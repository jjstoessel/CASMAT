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

#include "CATSMAT_collectionvisitor.h"
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
    
    CATSMAT_collection_visitor::CATSMAT_collection_visitor() : fCPMatrix(NULL)
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
        fCPMatrix->setMeasureNumber(elt->getMeasureNum());
        
        IMUSANT_collection_visitor::visit(elt);
    }
    
    #pragma mark IMUSANT_barline handler
    void CATSMAT_collection_visitor::visit ( S_IMUSANT_barline& elt)
    {
        if (elt->getLocation()==IMUSANT_barline::left)
        {
            fCPMatrix->setCurrentLeftBarline(elt->getBarStyle());
        }
    }
    
    #pragma mark IMUSANT_note handler

    void CATSMAT_collection_visitor::visit ( S_IMUSANT_note& elt )
    {
        //we ignore non-printing objects
        if (elt->getStyle()!=IMUSANT_NoteStyle::hidden) {
            fCPMatrix->add(*elt);
        }

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
        if (fCPMatrix==nullptr)
        {
            fCPMatrix = new_CATSMAT_object<CATSMAT_cp_matrix>();
            fCPMatrix->set(elt);
            IMUSANT_collection_visitor::visit(elt);
        }
        //ensure CP Matrix is indexed correctly
        fCPMatrix->reindex();
    }
    
    void CATSMAT_collection_visitor::processCollections()
    {
        
    }


} //namespace CATSMAT
