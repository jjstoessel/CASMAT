/*

  MusicXML Library
  Copyright (C) 2003  Grame

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  grame@grame.fr

*/

#include "xml.h"
#include <string>
#include <sstream>

using namespace MusicXML;

xmlendl *	xmlendl::fInstance = 0;

namespace MusicXML 
{
//______________________________________________________________________________
Sxmlattribute new_xmlattribute(string name, string value)
{ xmlattribute * o = new xmlattribute(name, value); assert(o!=0); return o; }
Sxmlattribute new_xmlattribute(string name, long value)
{ xmlattribute * o = new xmlattribute(name, value); assert(o!=0); return o; }
Sxmlattribute new_xmlattribute(string name, int value)
{ xmlattribute * o = new xmlattribute(name, (long)value); assert(o!=0); return o; }
Sxmlattribute new_xmlattribute(string name, float value)
{ xmlattribute * o = new xmlattribute(name, value); assert(o!=0); return o; }

//______________________________________________________________________________
Sxmlelement new_xmlelement(string name)
{ xmlelement * o = new xmlelement(name); assert(o!=0); return o; }
Sxmlelement new_xmlelement(string name, unsigned long val)
{ xmlelement * o = new xmlelement(name, val); assert(o!=0); return o; }
Sxmlelement new_xmlelement(string name, long val)
{ xmlelement * o = new xmlelement(name, val); assert(o!=0); return o; }
Sxmlelement new_xmlelement(string name, int val)
{ xmlelement * o = new xmlelement(name, val); assert(o!=0); return o; }
Sxmlelement new_xmlelement(string name, float val)
{ xmlelement * o = new xmlelement(name, val); assert(o!=0); return o; }
Sxmlelement new_xmlelement(string name, string val)
{ xmlelement * o = new xmlelement(name, val); assert(o!=0); return o; }
Sxmlheader new_xmlheader(int mode, string loc)
{ xmlheader * o = new xmlheader(mode, loc); assert(o!=0); return o; }
//______________________________________________________________________________
ostream& operator<< (ostream& os, const xmlendl& endl)
{
    endl.print(os);
    return os;
}

//______________________________________________________________________________
void xmlattribute::setName (const string& name) 		{ fName = name; }
void xmlattribute::setValue (const string& value) 		{ fValue = value; }
//______________________________________________________________________________
void xmlattribute::setValue (long value)
{
	stringstream s;
	s << value;
	s >> fValue;
}

//______________________________________________________________________________
void xmlattribute::setValue (float value)
{
	stringstream s;
	s << value;
	s >> fValue;
}

//______________________________________________________________________________
void xmlelement::setValue (int value)				{ setValue((long)value); }
void xmlelement::setValue (const string& value) 	{ fValue = value; }
void xmlelement::setName (const string& name) 		{ fName = name; }
//______________________________________________________________________________
void xmlelement::setValue (long value)
{
	stringstream s;
	s << value;
	s >> fValue;
}

//______________________________________________________________________________
void xmlelement::setValue (unsigned long value)
{
	stringstream s;
	s << value;
	s >> fValue;
}

//______________________________________________________________________________
void xmlelement::setValue (float value)
{
	stringstream s;
	s << value;
	s >> fValue;
}

//______________________________________________________________________________
void xmlattribute::print (ostream& os) const {
	os << getName() << "=\"" << getValue() << "\"";
}

//______________________________________________________________________________
ostream& operator<< (ostream& os, const Sxmlattribute& attr)
{
	attr->print(os);
	return os;
}

//______________________________________________________________________________
long xmlelement::add (const Sxmlattribute& attr)
{ 
	fAttributes.push_back(attr);
	return fAttributes.size()-1;
}
long xmlelement::add (const Sxmlelement& elt)
{ 
	fElements.push_back(elt);
	return fElements.size()-1;
}

//______________________________________________________________________________
void xmlelement::print (ostream& os) const
{
	xmlendl& end = xmlendl::get();
    vector<Sxmlattribute>::const_iterator attr; 
    vector<Sxmlelement>::const_iterator ielt;
	bool smallval = (getValue().size () < 32) && fElements.empty();

	os << end;
	os << "<" << getName();
    for (attr = attributes().begin(); attr != attributes().end(); attr++)
		os << " " << *attr;
    if (empty())
        os << "/>";
    else {
        os << ">";
        if (!smallval) end++;
    
        if (!getValue().empty()) {
            if (smallval) os << getValue();
            else os << end << getValue();
        }
    
        for (ielt = elements().begin(); ielt != elements().end(); ielt++)
            os << *ielt;
    
        if (!smallval) os << end--;
        os << "</" << getName() << ">";
    }
}

//______________________________________________________________________________
ostream& operator<< (ostream& os, const Sxmlelement& elt)
{
    elt->print (os);
	return os;
}

//______________________________________________________________________________
int xmlheader::fModeTbl[] = { partwise, timewise };	
string xmlheader::fModeStrings[] = { "partwise", "timewise" };
bimap<string, int> xmlheader::fMode2String(fModeStrings, fModeTbl, last);

//______________________________________________________________________________
const string xmlheader::scoreMode (int mode) 	{ return fMode2String[mode]; }
int	xmlheader::scoreMode (string mode) 			{ return fMode2String[mode]; }
void xmlheader::setMode (int mode)				{ fMode  = mode; }
void xmlheader::setLocation (const string& loc)	{ fLocation = loc; }

void xmlheader::print (ostream& os) const
{
	string mode = scoreMode(fMode);
	string umode = mode;
	umode[0] = (char)toupper(umode[0]);

	os 	<< "<?xml version=\"1.0\" standalone=\"no\"?>" << std::endl
		<< "<!DOCTYPE score-" << mode 
		<< " PUBLIC \"-//Recordare//DTD MusicXML " << MusicXMLVersion() 
		<< " " << umode << "//EN\" "
		<< "\"" << getLocation() << mode << ".dtd\">" << std::endl;
}

ostream& operator<< (ostream& os, const Sxmlheader& header)
{
    header->print(os);
	return os;
}

}
