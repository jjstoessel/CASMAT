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

/* a replacement solution to expat */
#ifndef __Iexpat__
#define __Iexpat__

#include <vector>
#include <string>
#include "reader.h"

typedef char XML_Char;
typedef void (*XML_StartElementHandler)	(void *userData, const XML_Char *name, const XML_Char **atts);
typedef void (*XML_EndElementHandler)	(void *userData, const XML_Char *name);
typedef void (*XML_CharacterDataHandler)(void *userData, const XML_Char *s, int len);

class expatreader : public reader
{
	void *		fUserData;
	std::string	fCurElement;
	XML_StartElementHandler		fStartH;
	XML_EndElementHandler		fEndH;
	XML_CharacterDataHandler	fDataH;
	std::vector<std::string>	fAttributes;

		bool	callStartElement ();

	public:
				 expatreader(const XML_Char *encoding);
		virtual ~expatreader() {};

		bool	read(const char* file);
		void	setElementHandler (XML_StartElementHandler start, XML_EndElementHandler end)
																{ fStartH = start; fEndH = end; }
		void	setDataHandler (XML_CharacterDataHandler h)		{ fDataH = h; }
		void	setUserData (void * userData)					{ fUserData = userData; }
		
		bool	xmlDecl (const char* version, const char *encoding, bool standalone)		{ return true; }
		bool	docType (const char* start, bool status, const char *pub, const char *sys)	{ return true; }

		bool	newElement (const char* eltName);
		bool	newAttribute (const char* eltName, const char *val);
		void	setValue (const char* value);
		bool	endElement (const char* eltName);
		void	error (const char* s, int lineno);
};

typedef expatreader * XML_Parser;

#define XML_ParserCreate(encoding)					new expatreader(encoding)
#define XML_ParserFree(parser)						delete parser 
#define XML_SetElementHandler(parser, start, end)	parser->setElementHandler(start, end)
#define XML_SetCharacterDataHandler(parser, dh)		parser->setDataHandler(dh)
#define XML_SetUserData(parser, udata)				parser->setUserData(udata)


#endif
