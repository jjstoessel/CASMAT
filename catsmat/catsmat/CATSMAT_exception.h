//
//  CATSMAT_exception.h
//  imusant
//
//  Created by Jason Stoesesl on 03/08/2016.
//
//

#ifndef catsmat_exception_h
#define catsmat_exception_h

#include <string>

using namespace std;

namespace IMUSANT
{
    
    class catsmat_runtime_error : public runtime_error
    {
        
    public:
        
        explicit catsmat_runtime_error (const string& what_arg)
            : runtime_error(what_arg)
        {
            m_what_arg = what_arg;
        }
        
        const char * what () const noexcept     //  _NOEXCEPT
        {
            string msg =
                "CATSMAT encountered a fatal error: "
                + m_what_arg;
            
            return msg.c_str();
        }
        
        virtual ~catsmat_runtime_error() throw() {}
    
    private:
        
        string m_what_arg;
    };
    
    class catsmat_logic_error : public logic_error
    {
    public:
        explicit catsmat_logic_error (const string& what_arg)
        : logic_error(what_arg)
        {
            m_what_arg = what_arg;
        }
        
        const char * what () const noexcept     //  _NOEXCEPT
        {
            string msg =
            "CATSMAT encountered a fatal error: "
            + m_what_arg;
            
            return msg.c_str();
        }
        
        virtual ~catsmat_logic_error() throw() {}
        
    private:
        
        string m_what_arg;
    };
    
}  // NAMESPACE

#endif
