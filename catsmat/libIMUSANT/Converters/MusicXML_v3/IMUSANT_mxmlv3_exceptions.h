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
    
    class MusicXML3_ElementNotImplemented : public runtime_error
    {
        
    public:
        
        explicit MusicXML3_ElementNotImplemented (const string& what_arg)
            : runtime_error(what_arg)
        {
            m_what_arg = what_arg;
        }
        
        const char * what () const _NOEXCEPT
        {
            string msg =
                "You are trying to use a MusicXML v3 element that has not been implemented: "
                + m_what_arg;
            
            return msg.c_str();
        }
        
        virtual ~MusicXML3_ElementNotImplemented() throw() {}
    
    private:
        
        string m_what_arg;
    };
    
    class MusicXML3_UnexpectedElement : public runtime_error
    {
        
    public:
        
        explicit MusicXML3_UnexpectedElement (const string& what_arg)
        : runtime_error(what_arg)
        {
            m_what_arg = what_arg;
        }
        
        const char * what () const  _NOEXCEPT
        {
            string msg =
            "Unexpected element in IMUSANT_mxmlv3_to_imusant_visitor.  Element is: "
            + m_what_arg;
            
            return msg.c_str();
        }
        
        virtual ~MusicXML3_UnexpectedElement() throw() {}
        
    private:
        
        string m_what_arg;
    };
    
    
}  // NAMESPACE

#endif
