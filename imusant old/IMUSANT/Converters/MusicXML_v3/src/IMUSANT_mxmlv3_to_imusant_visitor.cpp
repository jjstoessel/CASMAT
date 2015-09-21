//
//  IMUSANT_mxmlv3_to_imusant_visitor.cpp
//  imusant
//
//  Created by Derrick Hill on 19/09/2015.
//
//

#include <stdio.h>

#include "IMUSANT_mxmlv3_to_imusant_visitor.h"

namespace IMUSANT
{
    
#define debug(method) cout << "Visiting " << method << endl; fflush(stdout)

    
    IMUSANT_mxmlv3_to_imusant_visitor::
    IMUSANT_mxmlv3_to_imusant_visitor()
    {
        
        
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_score_partwise& elt)
    {
        debug("S_score_partwise");
        fImusantScore = new_IMUSANT_score();
    }
    
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_movement_title& elt)
    {
        debug("S_movement_title");
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_creator &elt)
    {
        debug("S_creator");
        STRPAIR creator;
        
        creator.first = elt->getAttributeValue("type");
        creator.second = elt->getValue();
        
        fImusantScore->addCreator(creator);
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_score_part& elt)
    {
        debug("S_score_part");

        assert(fImusantScore);
        
        S_IMUSANT_part part = new_IMUSANT_part();
        fCurrentPart = part;
        
        part->setID(elt->getAttributeValue("id"));
        
        fImusantScore->addPart(part);
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_part_name& elt)
    {
        debug("S_part_name");
        
        assert(fCurrentPart);
        
        fCurrentPart->setPartName(elt->getValue());
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_part_abbreviation& elt)
    {
        debug("S_part_abbreviation");
        
        assert(fCurrentPart);
        
        fCurrentPart->setPartAbbrev(elt->getValue());
    }
    
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_part& elt)
    {
        debug("S_part");
    }
        
}