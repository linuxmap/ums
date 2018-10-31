# Microsoft Developer Studio Project File - Name="umsboard" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=umsboard - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "umsboard.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "umsboard.mak" CFG="umsboard - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "umsboard - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "umsboard - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "umsboard"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "umsboard - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\include" /I "..\..\common\include" /I "..\..\common\tp" /I "..\..\..\10-Common\include\platform\\" /I "..\..\..\10-Common\include\system1" /I "..\..\..\10-Common\include\mt" /I "..\..\..\10-Common\include\mcu" /I "..\..\..\10-Common\include\protocol" /I "..\..\..\10-Common\include\protocol\h323stack" /I "..\..\..\10-Common\include\nms1" /I "..\..\..\10-Common\include\tp" /I "..\..\cnapi\include" /I "..\..\..\10-common\include\protocol\tp" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\..\10-common\lib\release\win32\umsboard.lib"

!ELSEIF  "$(CFG)" == "umsboard - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\..\common\include" /I "..\..\common\tp" /I "..\..\..\10-Common\include\platform\\" /I "..\..\..\10-Common\include\system1" /I "..\..\..\10-Common\include\mt" /I "..\..\..\10-Common\include\mcu" /I "..\..\..\10-Common\include\protocol" /I "..\..\..\10-Common\include\protocol\h323stack" /I "..\..\..\10-Common\include\nms1" /I "..\..\..\10-Common\include\tp" /I "..\..\cnapi\include" /I "..\..\..\10-common\include\protocol\tp" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /Fp"Debug/umsbrd.pch" /YX /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\..\10-common\lib\debug\win32\umsboard.lib"

!ENDIF 

# Begin Target

# Name "umsboard - Win32 Release"
# Name "umsboard - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\source\umsboardcfg.cpp
# End Source File
# Begin Source File

SOURCE=..\source\umsboardinst.cpp
# End Source File
# End Group
# End Target
# End Project
