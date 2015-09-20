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
    
#define debug // cout << "visitStart() in " << __FILE__ << " at line " << __LINE__ << endl; fflush(stdout)

    
    IMUSANT_mxmlv3_to_imusant_visitor::
    IMUSANT_mxmlv3_to_imusant_visitor()
    {
        
        
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_score_partwise& elt)
    {
        fImusantScore = new_IMUSANT_score();
    }
    
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_movement_title& elt)
    {
        debug;
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_creator &elt)
    {
        debug;
        STRPAIR creator;
        
        creator.first = elt->getAttributeValue("type");
        creator.second = elt->getValue();
        
        fImusantScore->addCreator(creator);
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_score_part& elt)
    {
        debug;
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_part_name& elt)
    {
        debug;
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_part& elt)
    {
        debug;
    }
        
}