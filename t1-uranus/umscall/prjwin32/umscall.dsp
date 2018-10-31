# Microsoft Developer Studio Project File - Name="umscall" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=umscall - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "umscall.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "umscall.mak" CFG="umscall - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "umscall - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "umscall - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "umscall"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "umscall - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\include" /I "..\..\common\tp" /I "..\..\..\10-common\include\protocol" /I "..\..\..\10-common\include\platform\\" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-common\include\tp" /I "..\..\..\10-Common\include\protocol\tp" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "_AFXDLL" /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\..\10-common\lib\release\win32\umscall.lib"

!ELSEIF  "$(CFG)" == "umscall - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\..\common\tp" /I "..\..\..\10-common\include\protocol" /I "..\..\..\10-common\include\platform\\" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-common\include\tp" /I "..\..\..\10-common\include\protocol\tp" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "_AFXDLL" /YX /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\..\10-common\lib\debug\win32\umscall.lib"

!ENDIF 

# Begin Target

# Name "umscall - Win32 Release"
# Name "umscall - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\source\bandwidth.cpp
# End Source File
# Begin Source File

SOURCE=..\source\callinnerstruct.cpp
# End Source File
# Begin Source File

SOURCE=..\source\callmgr.cpp
# End Source File
# Begin Source File

SOURCE=..\source\callnodemgr.cpp
# End Source File
# Begin Source File

SOURCE=..\source\callprint.cpp
# End Source File
# Begin Source File

SOURCE=..\source\dataconfhandler.cpp
# End Source File
# Begin Source File

SOURCE=..\source\dsnodepool.cpp
# End Source File
# Begin Source File

SOURCE=..\source\dualmgr.cpp
# End Source File
# Begin Source File

SOURCE=..\source\getvidaud.cpp
# End Source File
# Begin Source File

SOURCE=..\source\nodefsm.cpp
# End Source File
# Begin Source File

SOURCE=..\source\pollmgr.cpp
# End Source File
# Begin Source File

SOURCE=..\source\procnodeds.cpp
# End Source File
# Begin Source File

SOURCE=..\source\putaud.cpp
# End Source File
# Begin Source File

SOURCE=..\source\selviewmgr.cpp
# End Source File
# Begin Source File

SOURCE=..\source\tvwallmgr.cpp
# End Source File
# Begin Source File

SOURCE=..\source\umsaudmix.cpp
# End Source File
# Begin Source File

SOURCE=..\source\umsbas.cpp
# End Source File
# Begin Source File

SOURCE=..\source\umsconfinst.cpp
# End Source File
# Begin Source File

SOURCE=..\source\umsdiscussnew.cpp
# End Source File
# Begin Source File

SOURCE=..\source\umseapu.cpp
# End Source File
# Begin Source File

SOURCE=..\source\umseqpservice.cpp
# End Source File
# Begin Source File

SOURCE=..\source\umsgetconfvidaud.cpp
# End Source File
# Begin Source File

SOURCE=..\source\querytmpalias.cpp
# End Source File
# Begin Source File

SOURCE=..\source\umsmcumgr.cpp
# End Source File
# Begin Source File

SOURCE=..\source\umsnetportmgr.cpp
# End Source File
# Begin Source File

SOURCE=..\source\umsreg.cpp
# End Source File
# Begin Source File

SOURCE=..\source\umsrollcall.cpp
# End Source File
# Begin Source File

SOURCE=..\source\umsstackinterface.cpp
# End Source File
# Begin Source File

SOURCE=..\source\umsvmp.cpp
# End Source File
# Begin Source File

SOURCE=..\source\vmpservicehandler.cpp
# End Source File
# End Group
# Begin Group "Head Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\include\bandwidth.h
# End Source File
# Begin Source File

SOURCE=..\include\callinnerstruct.h
# End Source File
# Begin Source File

SOURCE=..\include\callmgr.h
# End Source File
# Begin Source File

SOURCE=..\include\callnodemgr.h
# End Source File
# Begin Source File

SOURCE=..\include\dataconfhandler.h
# End Source File
# Begin Source File

SOURCE=..\include\dsnodepool.h
# End Source File
# Begin Source File

SOURCE=..\include\dualmgr.h
# End Source File
# Begin Source File

SOURCE=..\include\getvidaud.h
# End Source File
# Begin Source File

SOURCE=..\..\common\tp\innereventumsvmp.h
# End Source File
# Begin Source File

SOURCE=..\include\nodefsm.h
# End Source File
# Begin Source File

SOURCE=..\include\pollmgr.h
# End Source File
# Begin Source File

SOURCE=..\include\procnodeds.h
# End Source File
# Begin Source File

SOURCE=..\include\putaud.h
# End Source File
# Begin Source File

SOURCE=..\include\selviewmgr.h
# End Source File
# Begin Source File

SOURCE=..\include\tvwallmgr.h
# End Source File
# Begin Source File

SOURCE=..\include\umsaudmix.h
# End Source File
# Begin Source File

SOURCE=..\include\umsbas.h
# End Source File
# Begin Source File

SOURCE=..\..\common\tp\umscallinit.h
# End Source File
# Begin Source File

SOURCE=..\..\common\tp\umscommonstruct.h
# End Source File
# Begin Source File

SOURCE=..\include\umsconfinst.h
# End Source File
# Begin Source File

SOURCE=..\include\umsdiscussnew.h
# End Source File
# Begin Source File

SOURCE=..\include\umseapu.h
# End Source File
# Begin Source File

SOURCE=..\include\umseqpservice.h
# End Source File
# Begin Source File

SOURCE=..\include\umsgetconfvidaud.h
# End Source File
# Begin Source File

SOURCE=..\include\querytmpalias.h
# End Source File
# Begin Source File

SOURCE=..\include\umsmcumgr.h
# End Source File
# Begin Source File

SOURCE=..\include\umsnetportmgr.h
# End Source File
# Begin Source File

SOURCE=..\include\umsreg.h
# End Source File
# Begin Source File

SOURCE=..\include\umsrollcall.h
# End Source File
# Begin Source File

SOURCE=..\include\umsstackinterface.h
# End Source File
# Begin Source File

SOURCE=..\include\umsvmp.h
# End Source File
# Begin Source File

SOURCE=..\include\vmpserviecehandler.h
# End Source File
# End Group
# End Target
# End Project
