//
//  IMUSANT_mxmlv3_to_imusant_visitor.cpp
//  imusant
//
//  Created by Derrick Hill on 19/09/2015.
//
//

#include <stdio.h>
#include <stdlib.h>

#include "IMUSANT_mxmlv3_to_imusant_visitor.h"

namespace IMUSANT
{
    
#define debug(method) // cout << "Visiting " << method << endl; fflush(stdout)

    
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
        assert(fImusantScore);
        fImusantScore->setMovementTitle(elt->getValue());
    }
    
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_movement_number& elt)
    {
        debug("S_movement_number");
        assert(fImusantScore);
        fImusantScore->setMovementNum(elt->getValue());
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
        // The "part" element is outside the scope of the "score-part" element that we processed above.
        // Therefore whenever we encounter a "part" element we need to reset the fCurrentPart to
        // point to it.
        
        debug("S_part");
        
        string part_id = elt->getAttributeValue("id");
        
        if (! fImusantScore->getPartById(part_id, fCurrentPart))
        {
            throw "Unexpected part id in IMUSANT_mxmlv3_to_imusant_visitor::visitStart(S_part). Value is: " + part_id;
        }
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_measure& elt)
    {
        debug("S_measure");

        fCurrentMeasureNumber = elt->getAttributeLongValue("number", fCurrentMeasureNumber + 1);
        fCurrentNoteIndex = 0;  //reset on measure entry
        fCurrentAccidentals.clear(); //reset
        
        S_IMUSANT_measure measure = new_IMUSANT_measure();
        measure->setMeasureNum(fCurrentMeasureNumber);
        
        if (fImusantScore)  //assert that uberclass has been instantiated.
        {
            fCurrentPart->addMeasure(measure);
        }
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_key& elt)
    {
//        <key>
//          <fifths>0</fifths>
//          <mode>minor</mode>
//        </key>
        
        debug("S_key start");
        
        fInKeyElement = true;
        fCurrentKey = IMUSANT_key();
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitEnd( S_key& elt)
    {
        debug("S_key end");
        fInKeyElement = false;
        fCurrentPart->getCurrentMeasure()->setKey(fCurrentKey);
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_fifths& elt)
    {
        debug("S_fifths");
        if (fInKeyElement)
        {
            string fifths_value_str = elt->getValue();
            long int fifths_value_long = atol(fifths_value_str.c_str());
            fCurrentKey.setFifths(fifths_value_long);
        }
    }
    
    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_mode& elt)
    {
        debug("S_mode");
        if (fInKeyElement)
        {
            string mode_str = elt->getValue();
            IMUSANT_key::mode the_mode = IMUSANT_key::xmlmode(mode_str);
            fCurrentKey.setMode(the_mode);
        }
    }

    void
    IMUSANT_mxmlv3_to_imusant_visitor::
    visitStart( S_note& elt)
    {
      //  debug("S_note");
    }
    
    
}