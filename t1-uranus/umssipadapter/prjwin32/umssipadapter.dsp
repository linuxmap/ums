# Microsoft Developer Studio Project File - Name="umssipadapter" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=umssipadapter - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "umssipadapter.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "umssipadapter.mak" CFG="umssipadapter - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "umssipadapter - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "umssipadapter - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "umssipadapter"
# PROP Scc_LocalPath "..\..\.."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "umssipadapter - Win32 Release"

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
# ADD CPP /nologo /W3 /GX /O2 /I "..\include" /I "..\..\common\tp" /I "..\..\..\10-common\include\platform" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-Common\include\protocol" /I "..\..\..\10-Common\include\tp" /I "..\..\..\10-Common\include\protocol\sipstack" /I "..\..\..\10-Common\include\protocol\tp" /I "..\..\..\10-common\include\cbb\tinyxml" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "_ENABLE_QUANTUM_PROJECT_" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 bfcplib.lib tpquantum.lib OspDll.lib kdvsys.lib xmlengine.lib kdvdatanetlib.lib Kdvencrypt.lib umsmsg.lib tpmsgmgr.lib protocoladapter.lib umsapi.lib kdvlog.lib modulemananger.lib kdv323stacklib.lib kdv323adapterlib_tps.lib kdvcascade.lib kdv323modulelib.lib kdvsipstack2.lib kdvsipadapterlib2.lib kdvsipmodulelib2.lib lanman.lib tinyxml.lib zlibx.lib kpropx.lib kdvprotocommon.lib kdvsdp.lib quantumsock.lib /nologo /stack:0x1000000 /subsystem:console /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"nafxcw.lib" /nodefaultlib:"libcmt.lib" /libpath:"..\..\..\10-common\lib\release\win32"

!ELSEIF  "$(CFG)" == "umssipadapter - Win32 Debug"

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
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\..\common\tp" /I "..\..\..\10-common\include\platform" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-Common\include\protocol" /I "..\..\..\10-Common\include\tp" /I "..\..\..\10-Common\include\protocol\sipstack" /I "..\..\..\10-Common\include\protocol\tp" /I "..\..\..\10-common\include\cbb\tinyxml" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "_ENABLE_QUANTUM_PROJECT_" /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 bfcplib.lib tpquantum.lib OspDll.lib kdvsys.lib xmlengine.lib kdvdatanetlib.lib Kdvencrypt.lib umsmsg.lib tpmsgmgr.lib protocoladapter.lib umsapi.lib kdvlog.lib modulemananger.lib kdv323stacklib.lib kdv323adapterlib_tps.lib kdvcascade.lib kdv323modulelib.lib kdvsipstack2.lib kdvsipadapterlib2.lib kdvsipmodulelib2.lib lanman.lib tinyxml.lib zlibx.lib kpropx.lib kdvprotocommon.lib kdvsdp.lib quantumsock.lib /nologo /stack:0x1000000 /subsystem:console /debug /machine:I386 /nodefaultlib:"libcd.lib" /nodefaultlib:"nafxcwd.lib" /nodefaultlib:"libcmtd.lib" /pdbtype:sept /libpath:"..\..\..\10-common\lib\debug\win32"

!ENDIF 

# Begin Target

# Name "umssipadapter - Win32 Release"
# Name "umssipadapter - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\source\adaptercfg.cpp
# End Source File
# Begin Source File

SOURCE=..\source\umsdataconvet.cpp
# End Source File
# Begin Source File

SOURCE=..\source\umssipadapterinst.cpp
# End Source File
# Begin Source File

SOURCE=..\source\umssipadaptermain.cpp
# End Source File
# Begin Source File

SOURCE=..\source\umsstackinterface.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\include\adaptercfg.h
# End Source File
# Begin Source File

SOURCE=..\..\common\tp\innereventumssipadapter.h
# End Source File
# Begin Source File

SOURCE="..\..\..\10-common\include\tp\tpsys.h"
# End Source File
# Begin Source File

SOURCE=..\include\umsdataconvet.h
# End Source File
# Begin Source File

SOURCE=..\include\umssipadapterinst.h
# End Source File
# Begin Source File

SOURCE=..\include\umsstackinterface.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
