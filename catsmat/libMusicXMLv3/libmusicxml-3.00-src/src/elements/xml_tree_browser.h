/*

  MusicXML Library
  Copyright (C) 2007  Grame

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
  research@grame.fr

*/

#ifndef __mxml2_xml_tree_browser__
#define __mxml2_xml_tree_browser__

#include "tree_browser.h"
#include "xml.h"

namespace MusicXML2 
{

/*!
\addtogroup MusicXML
@{
*/

//______________________________________________________________________________
class EXP xml_tree_browser : public tree_browser<xmlelement> 
{
	public:
				 xml_tree_browser(basevisitor* v) : tree_browser<xmlelement>(v) {}
		virtual ~xml_tree_browser() {}
		virtual void browse (xmlelement& t);
};

/*! @} */


}

#endif
