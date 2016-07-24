//
//  IMUSANT_mxmlv3_exceptions.h
//  imusant
//
//  Created by Derrick Hill on 24/07/2016.
//
//

#ifndef imusant_IMUSANT_mxmlv3_exceptions_h
#define imusant_IMUSANT_mxmlv3_exceptions_h

namespace IMUSANT
{
    
    struct MusicXML3_ElementNotImplemented : public std::exception
    {
        const char * what ()
        {
            return "This MusicXML v3 element has not been implemented.";
        }
    };
    
}  // NAMESPACE

#endif
