/*
 *  IMUSANT_XMLFile.h
 *  imusant
 *
 *  Created by Jason Stoessel on 7/06/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __IMUSANT_XMLFile__
#define __IMUSANT_XMLFile__

#include "IMUSANT_score.h"
#include <iosfwd>
#include <string>

namespace IMUSANT
{

/*!
\brief provides IMUSANT_XML files reading and writing
*/
class EXP IMUSANT_XMLFile {
    public:
                 IMUSANT_XMLFile() {}
        virtual ~IMUSANT_XMLFile() {}
		
        S_IMUSANT_score	read (const string& file);
		
        bool	write (S_IMUSANT_score score, const string& file);
        bool	write (S_IMUSANT_score, std::ostream& os);
};

} //namespace IMUSANT
#endif
