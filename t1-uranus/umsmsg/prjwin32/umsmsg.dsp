# Microsoft Developer Studio Project File - Name="umsmsg" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=umsmsg - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "umsmsg.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "umsmsg.mak" CFG="umsmsg - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "umsmsg - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "umsmsg - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "umsmsg"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "umsmsg - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\include" /I "..\..\common\tp" /I "..\..\..\10-common\include\protocol" /I "..\..\..\10-common\include\platform\\" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-common\include\tp" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "_AFXDLL" /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\..\10-common\lib\release\win32\umsmsg.lib"

!ELSEIF  "$(CFG)" == "umsmsg - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\..\common\tp" /I "..\..\..\10-common\include\protocol" /I "..\..\..\10-common\include\platform\\" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-common\include\tp" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "_AFXDLL" /YX /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\..\10-common\lib\debug\win32\umsmsg.lib"

!ENDIF 

# Begin Target

# Name "umsmsg - Win32 Release"
# Name "umsmsg - Win32 Debug"
# Begin Group "umsevent"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\common\tp\innereventregsrv.h
# End Source File
# Begin Source File

SOURCE=..\..\common\tp\innereventtvwall.h
# End Source File
# Begin Source File

SOURCE=..\..\common\tp\innereventumsagent.h
# End Source File
# Begin Source File

SOURCE=..\..\common\tp\innereventumsaudiomix.h
# End Source File
# Begin Source File

SOURCE=..\..\common\tp\innereventumsboard.h
# End Source File
# Begin Source File

SOURCE=..\..\common\tp\innereventumscall.h
# End Source File
# Begin Source File

SOURCE=..\..\common\tp\innereventumsconf.h
# End Source File
# Begin Source File

SOURCE=..\..\common\tp\innereventumshdu.h
# End Source File
# Begin Source File

SOURCE=..\..\common\tp\innereventumsmediads.h
# End Source File
# Begin Source File

SOURCE=..\..\common\tp\innereventumsmediatrans.h
# End Source File
# Begin Source File

SOURCE=..\..\common\tp\innereventumsmpc.h
# End Source File
# Begin Source File

SOURCE=..\..\common\tp\innereventumsmpu2.h
# End Source File
# Begin Source File

SOURCE=..\..\common\tp\innereventumsnetbuf.h
# End Source File
# Begin Source File

SOURCE=..\..\common\tp\innereventumsrec.h
# End Source File
# Begin Source File

SOURCE=..\..\common\tp\innereventumsserver.h
# End Source File
# Begin Source File

SOURCE=..\source\umsinnerevent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\tp\umsinnerevent.h
# End Source File
# Begin Source File

SOURCE=..\source\umsinnerstruct.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\tp\umsinnerstruct.h
# End Source File
# Begin Source File

SOURCE=..\..\common\tp\umsinnertype.h
# End Source File
# End Group
# Begin Group "commonmsg"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\..\..\10-common\include\tp\eventoutsipadapter.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\10-common\include\tp\eventoutumsaudiomix.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\10-common\include\tp\eventoutumsboard.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\10-common\include\tp\eventoutumscall.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\10-common\include\tp\eventoutumscfg.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\10-common\include\tp\eventoutumsconftemplate.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\10-common\include\tp\eventoutumseqp.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\10-common\include\tp\eventoutumshdu.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\10-common\include\tp\eventoutumshdu2.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\10-common\include\tp\eventoutumslogin.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\10-common\include\tp\eventoutumsmediatrans.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\10-common\include\tp\eventoutumsrec.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\10-common\include\tp\eventoutumsreg.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\10-common\include\tp\eventoutumstool.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\10-common\include\tp\eventtpsys.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\10-common\include\tp\eventumswithcms.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\10-common\include\tp\tpeventcomm.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\10-common\include\tp\tpstruct.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\10-common\include\tp\tptype.h"
# End Source File
# Begin Source File

SOURCE=..\..\common\tp\umscommonstruct.h
# End Source File
# Begin Source File

SOURCE="..\..\..\10-common\include\tp\umseventcomm.h"
# End Source File
# Begin Source File

SOURCE=..\source\umseventmgr.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\tp\umsoutevent.h
# End Source File
# Begin Source File

SOURCE=..\source\umsxmlstruct.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\tp\umsxmltype.h
# End Source File
# Begin Source File

SOURCE="..\..\..\10-common\include\tp\xmldefine.h"
# End Source File
# End Group
# Begin Group "umssipadapter"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\common\tp\innereventumssipadapter.h
# End Source File
# End Group
# Begin Group "service"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\..\..\10-common\include\tp\eventoutupdateservice.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\10-common\include\tp\tpserviceeventcommon.h"
# End Source File
# End Group
# End Target
# End Project
