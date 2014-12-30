# Microsoft Developer Studio Project File - Name="MusicXML" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=MusicXML - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MusicXML.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MusicXML.mak" CFG="MusicXML - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MusicXML - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MusicXML - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MusicXML - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ""
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MUSICXML_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "../../include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MXMLEXPORT" /D "VXMLEXPORT" /FR /YX /FD /Zm500 /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib /nologo /dll /machine:I386 /out:"../MusicXML.dll"

!ELSEIF  "$(CFG)" == "MusicXML - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ""
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MUSICXML_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "../../include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "MXMLEXPORT" /D "VXMLEXPORT" /YX /FD /GZ /Zm500 /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib /nologo /dll /debug /machine:I386 /out:"../MusicXML.dll" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "MusicXML - Win32 Release"
# Name "MusicXML - Win32 Debug"
# Begin Group "core"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\core\common.cpp
# End Source File
# Begin Source File

SOURCE=..\..\core\conversions.cpp
# End Source File
# Begin Source File

SOURCE=..\..\core\Iexpat.cpp
# End Source File
# Begin Source File

SOURCE=..\..\core\IMusicXMLReader.cpp
# End Source File
# Begin Source File

SOURCE=..\..\core\IMusicXMLVisitor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\core\smartpointer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\core\TArpeggiate.cpp
# End Source File
# Begin Source File

SOURCE=..\..\core\TAttributes.cpp
# End Source File
# Begin Source File

SOURCE=..\..\core\TBackupForward.cpp
# End Source File
# Begin Source File

SOURCE=..\..\core\TBarline.cpp
# End Source File
# Begin Source File

SOURCE=..\..\core\TChord.cpp
# End Source File
# Begin Source File

SOURCE=..\..\core\TClef.cpp
# End Source File
# Begin Source File

SOURCE=..\..\core\TDirection.cpp
# End Source File
# Begin Source File

SOURCE=..\..\core\TFiguredBass.cpp
# End Source File
# Begin Source File

SOURCE=..\..\core\THarmony.cpp
# End Source File
# Begin Source File

SOURCE=..\..\core\TIdentification.cpp
# End Source File
# Begin Source File

SOURCE=..\..\core\TKey.cpp
# End Source File
# Begin Source File

SOURCE=..\..\core\TMeasure.cpp
# End Source File
# Begin Source File

SOURCE=..\..\core\TMeasureStyle.cpp
# End Source File
# Begin Source File

SOURCE=..\..\core\TMidiDevice.cpp
# End Source File
# Begin Source File

SOURCE=..\..\core\TMidiInstrument.cpp
# End Source File
# Begin Source File

SOURCE=..\..\core\TMusicXMLFile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\core\TNotation.cpp
# End Source File
# Begin Source File

SOURCE=..\..\core\TNote.cpp
# End Source File
# Begin Source File

SOURCE=..\..\core\TOrnaments.cpp
# End Source File
# Begin Source File

SOURCE=..\..\core\TOtherDirections.cpp
# End Source File
# Begin Source File

SOURCE=..\..\core\TPart.cpp
# End Source File
# Begin Source File

SOURCE=..\..\core\TPartGroup.cpp
# End Source File
# Begin Source File

SOURCE=..\..\core\TPartList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\core\TPitch.cpp
# End Source File
# Begin Source File

SOURCE=..\..\core\TRational.cpp
# End Source File
# Begin Source File

SOURCE=..\..\core\TRoutedVisitor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\core\TScore.cpp
# End Source File
# Begin Source File

SOURCE=..\..\core\TScoreHeader.cpp
# End Source File
# Begin Source File

SOURCE=..\..\core\TScoreInstrument.cpp
# End Source File
# Begin Source File

SOURCE=..\..\core\TScorePart.cpp
# End Source File
# Begin Source File

SOURCE=..\..\core\TScorePartwise.cpp
# End Source File
# Begin Source File

SOURCE=..\..\core\TScoreTimewise.cpp
# End Source File
# Begin Source File

SOURCE=..\..\core\TSound.cpp
# End Source File
# Begin Source File

SOURCE=..\..\core\TStaffDetails.cpp
# End Source File
# Begin Source File

SOURCE=..\..\core\TTechnical.cpp
# End Source File
# Begin Source File

SOURCE=..\..\core\TTimeModification.cpp
# End Source File
# Begin Source File

SOURCE=..\..\core\TTimeSign.cpp
# End Source File
# Begin Source File

SOURCE=..\..\core\TTranspose.cpp
# End Source File
# Begin Source File

SOURCE=..\..\core\TWork.cpp
# End Source File
# Begin Source File

SOURCE=..\..\core\xml.cpp
# End Source File
# Begin Source File

SOURCE=..\..\core\xmllex.cpp
# End Source File
# Begin Source File

SOURCE=..\..\core\xmlparse.cpp
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\MusicXML.rc
# End Source File
# End Group
# Begin Group "visitors"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\visitors\guido.cpp
# End Source File
# Begin Source File

SOURCE=..\..\visitors\TMidiContextVisitor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\visitors\TRolledVisitor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\visitors\TScanVisitor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\visitors\TUnrolledVisitor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\visitors\TXML2GuidoVisitor.cpp
# End Source File
# End Group
# End Target
# End Project
