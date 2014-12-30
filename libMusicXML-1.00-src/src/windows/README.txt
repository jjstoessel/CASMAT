MusicXML library
----------------------------------------------------------------

The MusicXML library uses the Expat xml parser. Therefore you 
must get the Expat library and install it prior to compile
the MusicXML library.
The homepage for the Expat project is http://www.libexpat.org/.

You must also update to MusicXML project settings to add a 
reference to the Expat library, as well as to add an additional
include directory to the preprocessor directives in order to let 
the compiler locate the expat.h file.

----------------------------------------------------------------
IMPORTANT INFORMATION

The MusicXML library is compiled as a shared library (DLL). 
The project provided is a Microsoft Visual C++ 6.0 project
and makes use of the Multithreaded DLL runtime library (option /MD)
for the Release target and of the Debug Multithreaded DLL runtime
for the Debug target.
Due to potential errors passing CRT objects across DLL boundaries
(see Microsoft Knowledge Base - 190799 
at http://support.microsoft.com/default.aspx?scid=kb;EN-US;190799)
any application using this library MUST make use of the same runtime 
libraries. One way to ensure this compatibility is to compile
using Microsoft Visual C++ 6.0 with the same runtime option.
(see Project settings - C/C++ - Code generation)

Another way to solve the problem consists in linking client 
applications with a static version of the library.

