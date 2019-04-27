//
// Created by Jason Stoessel on 2019-04-05.
//

#ifndef IMUSANT_TO_MUSICXML_VISITOR_H
#define IMUSANT_TO_MUSICXML_VISITOR_H

#include "IMUSANT_score.h"
#include "IMUSANT_visitor.h"
#include "interface/libmusicxml.h"
#include "elements/elements.h"

using namespace MusicXML2;

namespace IMUSANT
{

class IMUSANT_to_MusicXML_Visitor: public IMUSANT_visitor
{
public:
    IMUSANT_to_MusicXML_Visitor();
    ~IMUSANT_to_MusicXML_Visitor();

    void visit(S_IMUSANT_attributes &elt);
    void visit(S_IMUSANT_barline &);
    void visit(S_IMUSANT_chord &elt);
    void visit(S_IMUSANT_comment &elt);
    void visit(S_IMUSANT_element &elt);
    void visit(S_IMUSANT_lyric &elt);
    void visit(S_IMUSANT_measure &elt);
    void visit(S_IMUSANT_note &elt);
    void visit(S_IMUSANT_part &elt);
    void visit(S_IMUSANT_partlist &elt);
    void visit(S_IMUSANT_score &elt);

    const TFactory    getFactory() { return factory_; }
protected:

private:
    TFactory factory_;
    std::string current_part_id_;
    TElement current_part_;
    TElement current_measure_;
    TElement current_note_;
};

}//namespace IMUSANT

#endif //IMUSANT_IMUSANT_TO_MUSICXML_VISITOR_H
