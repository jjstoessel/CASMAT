
#ifndef __exports__
#define __exports__


#if defined(_WIN32) || defined(WIN32) || defined(__CYGWIN__) || defined(__MINGW32__) || defined(__BORLANDC__)

#define _NOEXCEPT noexcept

#pragma warning (disable : 4267)
#pragma warning (disable : 4275)
#pragma warning (disable : 4251)
#pragma warning (disable : 4786)

#ifdef MXMLEXPORT
#define EXP __declspec(dllexport)

#elif defined(MXMLSTATIC)
#define EXP

#else
#define EXP __declspec(dllimport)
#endif

#ifdef VXMLEXPORT
#define VEXP __declspec(dllexport)

#elif defined(VXMLSTATIC)
#define VEXP

#else
#define VEXP __declspec(dllimport)
#endif

#else

#define EXP
#define VEXP

#endif

#endif

