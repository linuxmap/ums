# Microsoft Developer Studio Project File - Name="umsserver" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=umsserver - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "umsserver.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "umsserver.mak" CFG="umsserver - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "umsserver - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "umsserver - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "umsserver"
# PROP Scc_LocalPath "..\..\.."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "umsserver - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\include" /I "..\..\common\tp" /I "..\..\..\10-common\include\platform" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-Common\include\protocol" /I "..\..\..\10-Common\include\tp" /I "..\..\..\10-Common\include\protocol\sipstack" /I "..\..\..\10-common\include\protocol\tp" /I "..\..\..\10-common\include\cbb\license" /I "..\..\..\10-common\include\cbb\tinyxml" /I "..\..\..\10-common\include\snmp" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 osplib.lib kdvsys.lib xmlengine.lib kdvdatanet.lib Kdvencrypt.lib umsmsg.lib tpmsgmgr.lib kdvum.lib umscall.lib umsue.lib umsconfig.lib umsapi.lib templatecfg.lib umseqp.lib kdvaddrbook.lib kdvlog.lib tpaddrmgr.lib commonapi.lib tinyxml.lib lanman.lib /nologo /subsystem:console /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"nafxcw.lib" /libpath:"..\..\..\10-common\lib\release\win32"

!ELSEIF  "$(CFG)" == "umsserver - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\..\common\tp" /I "..\..\..\10-common\include\platform" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-Common\include\protocol" /I "..\..\..\10-Common\include\tp" /I "..\..\..\10-Common\include\protocol\sipstack" /I "..\..\..\10-common\include\protocol\tp" /I "..\..\..\10-common\include\cbb\license" /I "..\..\..\10-common\include\cbb\tinyxml" /I "..\..\..\10-common\include\snmp" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 osplib.lib kdvsys.lib xmlengine.lib kdvdatanet.lib Kdvencrypt.lib umsmsg.lib tpmsgmgr.lib kdvum.lib umscall.lib umsue.lib umsconfig.lib umsapi.lib templatecfg.lib umseqp.lib kdvaddrbook.lib kdvlog.lib tpaddrmgr.lib commonapi.lib tinyxml.lib lanman.lib /nologo /subsystem:console /debug /machine:I386 /nodefaultlib:"libcd.lib" /nodefaultlib:"nafxcwd.lib" /pdbtype:sept /libpath:"..\..\..\10-common\lib\debug\win32"

!ENDIF 

# Begin Target

# Name "umsserver - Win32 Release"
# Name "umsserver - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\source\handleboardservice.cpp
# End Source File
# Begin Source File

SOURCE=..\source\handlecallservice.cpp
# End Source File
# Begin Source File

SOURCE=..\source\handleconftemplateservice.cpp
# End Source File
# Begin Source File

SOURCE=..\source\handlehduservice.cpp
# End Source File
# Begin Source File

SOURCE=..\source\handlelicense.cpp
# End Source File
# Begin Source File

SOURCE=..\source\handleregservice.cpp
# End Source File
# Begin Source File

SOURCE=..\source\handletoolservice.cpp
# End Source File
# Begin Source File

SOURCE=..\source\testcommand.cpp
# End Source File
# Begin Source File

SOURCE=..\source\tpumsmain.cpp
# End Source File
# Begin Source File

SOURCE=..\source\umshdu.cpp
# End Source File
# Begin Source File

SOURCE=..\source\umsobject.cpp
# End Source File
# Begin Source File

SOURCE=..\source\umsserver.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\include\handleboardservice.h
# End Source File
# Begin Source File

SOURCE=..\include\handlecallservice.h
# End Source File
# Begin Source File

SOURCE=..\include\handleconftemplateservice.h
# End Source File
# Begin Source File

SOURCE=..\include\handlehduservice.h
# End Source File
# Begin Source File

SOURCE=..\include\handlelicense.h
# End Source File
# Begin Source File

SOURCE=..\include\handleregservice.h
# End Source File
# Begin Source File

SOURCE=..\include\handletoolservice.h
# End Source File
# Begin Source File

SOURCE="..\..\..\10-common\include\tp\tperrno.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\10-common\include\tp\tphdu.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\10-common\include\tp\tpsys.h"
# End Source File
# Begin Source File

SOURCE=..\include\umshdu.h
# End Source File
# Begin Source File

SOURCE=..\..\common\tp\umsinnerstruct.h
# End Source File
# Begin Source File

SOURCE=..\..\common\tp\umsinnertype.h
# End Source File
# Begin Source File

SOURCE=..\..\common\tp\umsobject.h
# End Source File
# Begin Source File

SOURCE=..\include\umsserver.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
