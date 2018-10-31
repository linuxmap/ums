# Microsoft Developer Studio Project File - Name="tpmsgmgr" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=tpmsgmgr - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "tpmsgmgr.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "tpmsgmgr.mak" CFG="tpmsgmgr - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "tpmsgmgr - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "tpmsgmgr - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "tpmsgmgr"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "tpmsgmgr - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\include" /I "..\..\..\10-common\include\protocol" /I "..\..\..\10-common\include\platform\\" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-common\include\tp" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "_AFXDLL" /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\..\10-common\lib\release\win32\tpmsgmgr.lib"

!ELSEIF  "$(CFG)" == "tpmsgmgr - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\..\..\10-common\include\protocol" /I "..\..\..\10-common\include\platform\\" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-common\include\tp" /I "..\..\common\include" /I "..\..\..\10-common\include\mt" /I "..\..\..\t2-jupiter\common\include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "_AFXDLL" /YX /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\..\10-common\lib\debug\win32\tpmsgmgr.lib"

!ENDIF 

# Begin Target

# Name "tpmsgmgr - Win32 Release"
# Name "tpmsgmgr - Win32 Debug"
# Begin Group "source"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\source\msgmgr.cpp
# End Source File
# Begin Source File

SOURCE=..\source\tphandle.cpp
# End Source File
# Begin Source File

SOURCE=..\source\tplog.cpp
# End Source File
# Begin Source File

SOURCE=..\source\tplogmgr.cpp
# End Source File
# Begin Source File

SOURCE=..\source\tpmsg.cpp
# End Source File
# Begin Source File

SOURCE=..\source\tpobject.cpp
# End Source File
# Begin Source File

SOURCE=..\source\tptime.cpp
# End Source File
# End Group
# Begin Group "include"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE="..\..\..\10-common\include\tp\hashtable.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\10-common\include\tp\msgmgr.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\10-common\include\tp\tphandle.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\10-common\include\tp\tplog.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\10-common\include\tp\tplogmgr.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\10-common\include\tp\tpmsg.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\10-common\include\tp\tpobject.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\10-common\include\tp\tptime.h"
# End Source File
# End Group
# Begin Source File

SOURCE="..\..\..\10-common\include\protocol\xmlengine.h"
# End Source File
# End Target
# End Project
