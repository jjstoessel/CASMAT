//
//  IMUSANT_mxmlv3_to_imusant_visitor.h
//  imusant
//
//  Created by Derrick Hill on 19/09/2015.
//
//  This class visits the nodes in a libMusicXML v3 score and translates
//  this into an IMUSANT representation.
//

#ifndef imusant_IMUSANT_mxmlv3_to_imusant_visitor_h
#define imusant_IMUSANT_mxmlv3_to_imusant_visitor_h

#include "IMUSANT_score.h"

#include "elements/typedefs.h"


using namespace MusicXML2;

namespace IMUSANT
{
    
    class IMUSANT_mxmlv3_to_imusant_visitor
    :
    public visitor<S_score_partwise>,
    public visitor<S_movement_title>,
    public visitor<S_movement_number>,
    public visitor<S_creator>,
    public visitor<S_score_part>,
    public visitor<S_part_name>,
    public visitor<S_part_abbreviation>,
    public visitor<S_part>
    {
        
    public:
        
        IMUSANT_mxmlv3_to_imusant_visitor();
        
        virtual ~IMUSANT_mxmlv3_to_imusant_visitor()
        {
        }
        
        S_IMUSANT_score get_imusant_score()
        {
            assert(fImusantScore!=0);
            return fImusantScore;
        }

    protected:
        
        virtual void visitStart( S_score_partwise& elt);
        virtual void visitStart( S_movement_title& elt);
        virtual void visitStart( S_movement_number& elt);
        virtual void visitStart( S_creator& elt);
        virtual void visitStart( S_score_part& elt);
        virtual void visitStart( S_part_name& elt);
        virtual void visitStart( S_part_abbreviation& elt);
        
        virtual void visitStart( S_part& elt);
        
    private:
        
        S_IMUSANT_score fImusantScore;
        
        S_IMUSANT_part fCurrentPart;
        
    };
}



#endif
