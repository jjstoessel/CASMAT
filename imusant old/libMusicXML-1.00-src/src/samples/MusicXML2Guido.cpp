/*
  Copyright © Grame 2003

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
  grame@rd.grame.fr
  
*/

#include "TMusicXMLFile.h"
#include "TXML2GuidoVisitor.h"
#include "TScore.h"

#include <iostream>

using namespace MusicXML;
using namespace std;


int main (int argc, char * argv[]) 
{
    TXML2GuidoVisitor c;    
    TMusicXMLFile reader;
	if (argc != 2) {
		cerr << "usage: musicXML2guido <xml file>" << endl;
		return 1;
	}
    SScore score = reader.read(argv[1]);
    if (score == NULL) {
        cerr << "Parse error" << endl;
        return 0;
    }
	score->accept(c);
	cout << c.current() << endl;
    return 0;
}

