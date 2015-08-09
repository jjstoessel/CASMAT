/*
  Copyright © Grame 2006

  This library is free software; you can redistribute it and modify it under
  the terms of the GNU Library General Public License as published by the
  Free Software Foundation version 2 of the License, or any later version.

  This library is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public License
  for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

  Grame Research Laboratory, 9, rue du Garet 69001 Lyon - France
  research@grame.fr

*/

#ifdef WIN32
#pragma warning (disable : 4786)
#endif

#include <iostream>
#include "Iexpat.h"

extern "C" {
bool readfile (const char * file, reader * r);
}

using namespace std;
//____________________________________________________________________________________
expatreader::expatreader(const XML_Char *encoding)
	: fUserData(0), fStartH(0), fEndH(0), fDataH(0)
{
}


//____________________________________________________________________________________
bool expatreader::read(const char* file) 
{
	return readfile (file, this);
}

//____________________________________________________________________________________
bool expatreader::callStartElement ()
{
	int n = fAttributes.size();
	const char ** attrs = new const char*[n+1];
	if (!attrs) return false;
	for (int i=0; i<n; i+=2) {
		attrs[i]	= fAttributes[i].c_str();
		attrs[i+1]	= fAttributes[i+1].c_str();
	}
	attrs[n] = 0;
	fStartH (fUserData, fCurElement.c_str(), attrs);
#ifdef WIN32
	fCurElement = "";
#else
	fCurElement.clear();
#endif
	delete attrs;
	return true;
}

//____________________________________________________________________________________
bool expatreader::newElement (const char* eltName) 
{
	bool ret = true;
	if (!fCurElement.empty()) ret = callStartElement();
	fCurElement = eltName;
	fAttributes.clear();
	return ret;
}

//____________________________________________________________________________________
bool expatreader::newAttribute (const char* eltName, const char *val) 
{
	fAttributes.push_back(eltName);
	fAttributes.push_back(val);
	return true;
}

//____________________________________________________________________________________
void expatreader::setValue (const char* value) 
{
	bool ret = true;
	if (!fCurElement.empty()) ret = callStartElement();
	fDataH (fUserData, value, strlen(value));
}


//____________________________________________________________________________________
bool expatreader::endElement (const char* eltName) 
{
	bool ret = true;
	if (!fCurElement.empty()) ret = callStartElement();
	fEndH (fUserData, eltName);
	fAttributes.clear();
	return true;
}

//____________________________________________________________________________________
void expatreader::error (const char* s, int lineno) 
{
	cerr << s << " line " << lineno << endl;
}
