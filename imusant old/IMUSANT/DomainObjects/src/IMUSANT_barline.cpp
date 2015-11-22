/*
 *  IMUSANT_barline.cpp
 *  imusant
 *
 *  Created by Jason Stoessel on 18/06/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include "IMUSANT_barline.h"
namespace IMUSANT
{
    //ctor functions
    S_IMUSANT_ending new_IMUSANT_ending()
    { IMUSANT_ending* o = new IMUSANT_ending(); assert (o!=0); return o; }
    
    S_IMUSANT_repeat new_IMUSANT_repeat()
    { IMUSANT_repeat* o = new IMUSANT_repeat(); assert (o!=0); return o; }
    
    S_IMUSANT_barline new_IMUSANT_barline()
    { IMUSANT_barline* o = new IMUSANT_barline(); assert(o!=0); return o; }
    
    //===========================================================================+
    //IMUSANT_ending
    
    // convert a numeric start-stop value to a MusicXML string
    const string
    IMUSANT_ending::
    xml (IMUSANT_ending::type d)
    {
        string ret_val = "undefined";
        
        switch (d)
        {
            case undefined:
                ret_val = "undefined";
                break;
                
            case start:
                ret_val =  "start";
                break;
                
            case stop:
                ret_val =  "stop";
                break;
                
            default:
                ret_val =  "undefined";
                break;
        }
        
        return ret_val;

    }
    
    //! convert a MusicXML string to a numeric value
    IMUSANT_ending::type
    IMUSANT_ending::
    xml (const string str)
    {
        if (str.compare("undefined") == 0)
            return IMUSANT_ending::undefined;
        else if (str.compare("start") == 0)
            return IMUSANT_ending::start;
        else if (str.compare("stop") == 0)
            return IMUSANT_ending::stop;
        else
            return IMUSANT_ending::undefined;
    }
    
    void
    IMUSANT_ending::
    print (ostream& os) const
    {
        
        os << "<ENDING type=" << xml(getType()) << " number=" << getNumber() << " \\>" << endl;;
    }
    
    //==============================================================================
    //IMUSANT_repeat
    
   
    //! convert a numeric start-stop value to a MusicXML string
    const string
    IMUSANT_repeat::
    xml (IMUSANT_repeat::direction d)
    {
        string ret_val = "undefined";
        
        switch (d)
        {
            case undefined:
                ret_val = "undefined";
                break;
                
            case forward:
                ret_val =  "forward";
                break;
                
            case backward:
                ret_val =  "backward";
                break;
                
            default:
                ret_val =  "undefined";
                break;
        }
        
        return ret_val;
    }
    
    //! convert a MusicXML string to a numeric value
    IMUSANT_repeat::direction
    IMUSANT_repeat::
    xml (const string str)
    {
        if (str.compare("undefined") == 0)
            return IMUSANT_repeat::undefined;
        else if (str.compare("forward") == 0)
            return IMUSANT_repeat::forward;
        else if (str.compare("backward") == 0)
            return IMUSANT_repeat::backward;
        else
            return IMUSANT_repeat::undefined;
    }
    
    void
    IMUSANT_repeat::
    print (ostream& os) const
    {
        string direction = xml(getDirection());
        
        os << "<REPEAT direction=" << direction << " //>" << endl;
    }
    
    //==============================================================================
    //IMUSANT_barline
    
    void
    IMUSANT_barline::
    setLocation(location loc)
    {
        fLocation = loc;
    }
    
    void
    IMUSANT_barline::
    setBarStyle(type style)
    {
        fBarStyle = style;
    }
    
    
    const string
    IMUSANT_barline::
    xmllocation(location d)
    {
        string ret_val = "right";
        
        switch (d)
        {
            case right:
                ret_val = "right";
                break;
                
            case left:
                ret_val =  "left";
                break;
                
            case middle:
                ret_val =  "middle";
                break;
                
            default:
                ret_val =  "right";
                break;
        }
        
        return ret_val;
    }
    
    IMUSANT_barline::location
    IMUSANT_barline::
    xmllocation(const string str)
    {
        if (str.compare("right") == 0)
            return IMUSANT_barline::right;
        else if (str.compare("left") == 0)
            return IMUSANT_barline::left;
        else if (str.compare("middle") == 0)
            return IMUSANT_barline::middle;
        else
            return IMUSANT_barline::left;
    }
    
    const string
    IMUSANT_barline::xmlstyle(type d)
    {
        string ret_val = "none";
        
        switch (d)
        {
            case none:
                ret_val = "none";
                break;
                
            case regular:
                ret_val =  "regular";
                break;
                
            case dotted:
                ret_val =  "dotted";
                break;
                
            case heavy:
                ret_val =  "heavy";
                break;
                
            case light_light:
                ret_val =  "light-light";
                break;
                
            case light_heavy:
                ret_val =  "light-heavy";
                break;
                
            case heavy_light:
                ret_val =  "heavy-light";
                break;
                
            case heavy_heavy:
                ret_val =  "heavy-heavy";
                break;
                
            default:
                ret_val =  "none";
                break;
        }
        
        return ret_val;
    }
    
    IMUSANT_barline::type
    IMUSANT_barline::xmlstyle(const string str)
    {
        if (str.compare("none") == 0)
            return IMUSANT_barline::none;
        else if (str.compare("regular") == 0)
            return IMUSANT_barline::regular;
        else if (str.compare("dotted") == 0)
            return IMUSANT_barline::dotted;
        else if (str.compare("heavy") == 0)
            return IMUSANT_barline::heavy;
        else if (str.compare("light-light") == 0)
            return IMUSANT_barline::light_light;
        else if (str.compare("light-heavy") == 0)
            return IMUSANT_barline::light_heavy;
        else if (str.compare("heavy-light") == 0)
            return IMUSANT_barline::heavy_light;
        else if (str.compare("heavy-heavy") == 0)
            return IMUSANT_barline::heavy_heavy;
        else
            return IMUSANT_barline::none;
    }
    
    void
    IMUSANT_barline::
    accept(IMUSANT_visitor& visitor)
    {
        S_IMUSANT_barline sptr(this);
        visitor.visit(sptr);
    }
    
    void
    IMUSANT_barline::
    print_short(ostream& os) const
    {
        os << "<BARLINE location=" << xmllocation(getLocation()) << " style=" << xmlstyle(getBarStyle()) << "\\>" << endl;
    }
    
    void
    IMUSANT_barline::
    print (ostream& os) const
    {
        os << "<BARLINE location=" << xmllocation(getLocation()) << " style=" << xmlstyle(getBarStyle()) << "\\>" << endl;
        
        if (fEnding)
        {
            os << " " ;
            fEnding->print(os);
        }
        if (fRepeat)
        {
            os << " ";
            fRepeat->print(os);
        }
    }
    
}//namespace IMUSANT
