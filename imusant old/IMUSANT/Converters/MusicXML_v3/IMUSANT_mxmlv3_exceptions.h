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
        const char * what () const _NOEXCEPT
        {
            return "You are trying to use a MusicXML v3 element that has not been implemented.";
        }
    };
    
}  // NAMESPACE

#endif
