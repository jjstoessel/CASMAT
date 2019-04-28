//
// Created by Jason Stoessel on 2019-04-05.
//
#include <iomanip>
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
    if (elt->getLocation()!=IMUSANT_barline::undefined && elt->getBarStyle()!=IMUSANT_barline::none)
    {
        const char* location = NULL;
        const char* barstyle = NULL;
        const char* repeat = NULL;

        barstyle = IMUSANT_barline::xmlstyle(elt->getBarStyle()).c_str();
        location = IMUSANT_barline::xmllocation(elt->getLocation()).c_str();
        if (elt->repeat())
            IMUSANT_repeat::xml(elt->repeat()->getDirection()).c_str();

        TElement barline = factoryBarline(factory_, location, barstyle, repeat);
        factoryAddElement(factory_, current_measure_, barline);
    }
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

void IMUSANT_to_MusicXML_Visitor::visit(S_IMUSANT_duration &elt)
{
    int duration = elt->duration()*4*current_divisions_;
    TElement dur = factoryIntElement(factory_, k_duration,duration);
    factoryAddElement(factory_, current_note_, dur);
}

void IMUSANT_to_MusicXML_Visitor::visit(S_IMUSANT_note &elt)
{
    int duration = elt->duration()->GetSimplifiedDuration().duration()*4*current_divisions_;
    const char* type = nullptr;

    type = IMUSANT_duration::xmlv3(elt->duration()->duration()).c_str();

    //TO DO: handle ties(√?), tuplets, voices, stems, accidentals√, beaming here
    if (elt->getType() == IMUSANT_NoteType::pitch)
    {
        //create basic note
        const char* step = IMUSANT_pitch::xml(elt->pitch()->name()).c_str();
        float alter = elt->pitch()->getInflection();
        int octave = elt->pitch()->octave();

        current_note_ = factoryNote(factory_, step, alter, octave, duration, type);

        //handle dot(s)
        if (elt->duration()->dots())
        {
            for (int i = 0; i < elt->duration()->dots(); i++)
            {
                TElement dots = factoryElement(factory_,k_dot);
                factoryAddElement(factory_, current_note_, dots);
            }
        }

        //handle grace
        if (elt->getStyle() == IMUSANT_NoteStyle::grace)
        {
            TElement grace = factoryElement(factory_,k_grace);
            factoryAddElement(factory_, current_note_, grace);
        }

        //handle accidental
        if (elt->accidental()->getAccident()!=IMUSANT_accidental::none)
        {
            const char* accidental_name = IMUSANT_accidental::xml(elt->accidental()->getAccident()).c_str();
            TElement accidental = factoryStrElement(factory_, k_accidental, accidental_name);
            factoryAddElement(factory_, current_note_, accidental);
        }

        //handle ties
        TElement tie_start = nullptr;
        TElement tie_stop = nullptr;
        TElement tie_started = nullptr;
        TElement tie_stopped = nullptr;
        TAttribute start = factoryStrAttribute(factory_, "type", "start");
        TAttribute stop = factoryStrAttribute(factory_, "type", "stop");
        TAttribute started = factoryStrAttribute(factory_, "type", "start");
        TAttribute stopped = factoryStrAttribute(factory_, "type", "stop");

        if (elt->isTiedBothSides())
        {
            tie_stop = factoryElement(factory_, k_tie);
            factoryAddAttribute(factory_,tie_stop,stop);
            factoryAddElement(factory_,current_note_,tie_stop);
            tie_stopped = factoryElement(factory_, k_tied);
            factoryAddAttribute(factory_, tie_stopped, stopped);
            factoryNotation(factory_,current_note_,tie_stopped);

            tie_start = factoryElement(factory_, k_tie);
            factoryAddAttribute(factory_,tie_start,start);
            factoryAddElement(factory_,current_note_,tie_start);
            tie_started = factoryElement(factory_, k_tied);
            factoryAddAttribute(factory_, tie_started, started);
            factoryNotation(factory_,current_note_,tie_started);
        }
        else if (elt->isTiedPrevious())
        {
            tie_stop = factoryElement(factory_, k_tie);
            factoryAddAttribute(factory_,tie_stop,stop);
            factoryAddElement(factory_,current_note_,tie_stop);
            tie_stopped = factoryElement(factory_, k_tied);
            factoryAddAttribute(factory_, tie_stopped, stopped);
            factoryNotation(factory_,current_note_,tie_stopped);
        }
        else if (elt->isTiedNext())
        {
            tie_start = factoryElement(factory_, k_tie);
            factoryAddAttribute(factory_,tie_start,start);
            factoryAddElement(factory_,current_note_,tie_start);
            tie_started = factoryElement(factory_, k_tied);
            factoryAddAttribute(factory_, tie_started, started);
            factoryNotation(factory_,current_note_,tie_started);
        }

    }
    else if (elt->getType() == IMUSANT_NoteType::rest)
    {
        //factoryNote(TFactory f, const char* step, float alter, int octave, int duration, const char* type)
        //current_note_ = factoryNote(factory_, nullptr, 0, 0, duration, type); does not work for constructing a rest note element!
        current_note_ = factoryElement(factory_, MusicXML2::k_note);
        TElement rest = factoryRest(factory_, 0, 0);
        TElement type_elt = factoryStrElement(factory_,k_type,type);
        TElement dur = factoryIntElement(factory_, k_duration, duration);
        factoryAddElement(factory_, current_note_, dur);
        factoryAddElement(factory_, current_note_, rest);
        factoryAddElement(factory_, current_note_, type_elt);
    }

    factoryAddElement(factory_,current_measure_,current_note_);
}

void IMUSANT_to_MusicXML_Visitor::visit(S_IMUSANT_measure &elt)
{
    stringstream time, clef;
    int line = 0;
    int key = 0;
    const char* t_time;
    const char* t_clef;

    time.flush(); clef.flush();

    if (elt->getTime().isMeasured())
    {
        //resolve timeSign into text form
        vector<int> beat = elt->getTime().getDenominator();
        vector<int> beat_count = elt->getTime().getNumerator();
        if (beat.size() == 1 && beat_count.size() == 1)
        {
            time << beat_count[0] << "/" << beat[0] << ends;
        }
    }

    if (elt->getClef().isDefined())
    {
        //get clef info
        clef << setw(1);
        clef << elt->getClef().getSign();
        line = elt->getClef().getLine();
    }

    if (elt->getKey().isDefined())
    {
        key = elt->getKey().getFifths();
    }

    if ( !time.str().empty() || !clef.str().empty())
    {
        //factoryMeasureWithAttributes (TFactory f, int number, const char* time, const char* clef, int line, int key, int division)
        if (!time.str().empty())
            t_time = time.str().c_str();
        else
            t_time = nullptr;

        if (!clef.str().empty())
            t_clef = clef.str().c_str();
        else
            t_clef = nullptr;

        current_measure_ = factoryMeasureWithAttributes(factory_,
                                                        elt->getMeasureNum(),
                                                        t_time,
                                                        t_clef,
                                                        line,
                                                        key,
                                                        current_divisions_);
        current_time_ = time.str();
        current_clef_ = clef.str();
    }
    else
        current_measure_ = factoryMeasure(factory_, elt->getMeasureNum());

    factoryAddElement(factory_,current_part_,current_measure_);
    elt->elements().accept(*this);
}

void IMUSANT_to_MusicXML_Visitor::visit(S_IMUSANT_part &elt)
{
    current_part_id_ = elt->getID();
    current_part_ = factoryPart(factory_, current_part_id_.c_str());
    factoryAddPart(factory_,current_part_);
    current_divisions_ = elt->getDivisions();

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