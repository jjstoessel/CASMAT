//
// Created by Jason Stoessel on 2019-04-05.
//

#include "IMUSANT_imusant_to_musicxml_visitor.h"
#include "libIMUSANT.h"

using namespace MusicXML2;
using namespace std;

namespace IMUSANT
{

IMUSANT_to_MusicXML_Visitor::IMUSANT_to_MusicXML_Visitor()
{
    factory_ = factoryOpen();
    assert(factory_);
}

IMUSANT_to_MusicXML_Visitor::~IMUSANT_to_MusicXML_Visitor()
{
    factoryClose(factory_);
}

void IMUSANT_to_MusicXML_Visitor::visit(S_IMUSANT_attributes &elt)
{

}

void IMUSANT_to_MusicXML_Visitor::visit(S_IMUSANT_barline &elt)
{
    const char* location = IMUSANT_barline::xmllocation(elt->getLocation()).c_str();
    const char* barstyle = IMUSANT_barline::xmlstyle(elt->getBarStyle()).c_str();
    const char* repeat = "";
    if (elt->repeat())
        IMUSANT_repeat::xml(elt->repeat()->getDirection()).c_str();
    TElement barline = factoryBarline(factory_, location, barstyle, repeat);
    factoryAddElement(factory_, current_measure_, barline);
}

void IMUSANT_to_MusicXML_Visitor::visit(S_IMUSANT_chord &elt)
{
    cerr << "Chord not implemented.";
}

void IMUSANT_to_MusicXML_Visitor::visit(S_IMUSANT_comment &elt)
{

}

void IMUSANT_to_MusicXML_Visitor::visit(S_IMUSANT_element &elt)
{

}

void IMUSANT_to_MusicXML_Visitor::visit(S_IMUSANT_lyric &elt)
{

}

void IMUSANT_to_MusicXML_Visitor::visit(S_IMUSANT_note &elt)
{
    int duration = elt->duration()->duration()*1024;
    const char* type = IMUSANT_duration::xmlv1(elt->duration()->duration()).c_str();

    if (elt->getType() == IMUSANT_NoteType::pitch)
    {
        const char* step = IMUSANT_pitch::xml(elt->pitch()->name()).c_str();
        float alter = elt->pitch()->getInflection();
        int octave = elt->pitch()->octave();
        current_note_ = factoryNote(factory_, step, alter, octave, duration, type);
    }
    else if (elt->getType() == IMUSANT_NoteType::rest)
    {
        current_note_ = factoryRest(factory_, duration, type);
    }

    factoryAddElement(factory_,current_measure_,current_note_);
}

void IMUSANT_to_MusicXML_Visitor::visit(S_IMUSANT_measure &elt)
{
    //current_measure_ = factoryMeasure(factory_, elt->getMeasureNum(), elt->getTime(), elt->getClef(), 0, elt->getKey(),0);
    current_measure_ = factoryMeasure(factory_, elt->getMeasureNum());
    factoryAddElement(factory_,current_part_,current_measure_);
    elt->elements().accept(*this);
}

void IMUSANT_to_MusicXML_Visitor::visit(S_IMUSANT_part &elt)
{
    current_part_id_ = elt->getID();
    current_part_ = factoryPart(factory_, current_part_id_.c_str());
    factoryAddPart(factory_,current_part_);
    elt->measures().accept(*this);
}

void IMUSANT_to_MusicXML_Visitor::visit(S_IMUSANT_partlist &elt)
{
    for (auto part = elt->parts().begin(); part != elt->parts().end(); part++)
    {
        TElement score_part = factoryScorepart(factory_, (*part)->getID().c_str(), (*part)->getPartName().c_str(),(*part)->getPartAbbrev().c_str());
        factoryAddPart(factory_, score_part);
    }
    elt->parts().accept(*this);
}

void IMUSANT_to_MusicXML_Visitor::visit(S_IMUSANT_score &elt)
{
    STRPAIRVECTOR rights = elt->getRights();

    for (auto i = rights.begin(); i!=rights.end(); i++)
        factoryRights(factory_, i->second.c_str(), i->first.c_str());
    for (auto j = elt->getCreator().begin(); j!=elt->getCreator().end(); j++)
        factoryCreator(factory_, j->second.c_str(), j->first.c_str());
    factoryHeader(factory_, elt->getWorkNum().c_str(), elt->getWorkTitle().c_str(), elt->getMovementNum().c_str(), elt->getMovementTitle().c_str());
    factoryEncoding(factory_, "IMUSANT");

    elt->partlist()->accept(*this);
}

} //namespace IMUSANT