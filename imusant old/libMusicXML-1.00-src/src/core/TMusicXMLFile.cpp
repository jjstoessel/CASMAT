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


#include "TMusicXMLFile.h"
#include "IMusicXMLReader.h"
#include "IMusicXMLVisitor.h"
#include <fstream>

using namespace std;
using namespace MusicXML;

namespace MusicXML 
{

//______________________________________________________________________________
SScore TMusicXMLFile::read(const string& file)
{
	TMusicXMLReader reader;
	return reader.Read(file.c_str());
}

//______________________________________________________________________________
bool TMusicXMLFile::write(SScore score, const string& file)
{
	ofstream os;
	os.open(file.c_str());
	bool ret = write (score, os);
	os.close();
	return ret;
}

//______________________________________________________________________________
bool TMusicXMLFile::write(SScore score, ostream& os)
{
	TMusicXMLVisitor v;
	if (score) {
		score->accept(v);
		os  << score->xmlheader()
			<< v.current()
			<< endl;
		return true;
	}
	return false;
}

}
