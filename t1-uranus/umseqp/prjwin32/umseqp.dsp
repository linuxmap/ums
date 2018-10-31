# Microsoft Developer Studio Project File - Name="umseqp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=umseqp - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "umseqp.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "umseqp.mak" CFG="umseqp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "umseqp - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "umseqp - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "umseqp"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "umseqp - Win32 Release"

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
# ADD LIB32 /nologo /out:"..\..\..\10-common\lib\release\win32\umseqp.lib"

!ELSEIF  "$(CFG)" == "umseqp - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\..\common\tp" /I "..\..\..\10-common\include\protocol" /I "..\..\..\10-common\include\platform\\" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-common\include\tp" /I "..\..\..\10-Common\include\protocol\tp" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "_AFXDLL" /YX /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\..\10-common\lib\debug\win32\umseqp.lib"

!ENDIF 

# Begin Target

# Name "umseqp - Win32 Release"
# Name "umseqp - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\source\adaptereqp.cpp
# End Source File
# Begin Source File

SOURCE=..\source\audbaseqp.cpp
# End Source File
# Begin Source File

SOURCE=..\source\audbashandler.cpp
# End Source File
# Begin Source File

SOURCE=..\source\audiomixeqp.cpp
# End Source File
# Begin Source File

SOURCE=..\source\audmixhandler.cpp
# End Source File
# Begin Source File

SOURCE=..\source\baseqp.cpp
# End Source File
# Begin Source File

SOURCE=..\source\eqpinst.cpp
# End Source File
# Begin Source File

SOURCE=..\source\eqpinterface.cpp
# End Source File
# Begin Source File

SOURCE=..\source\eqpmgr.cpp
# End Source File
# Begin Source File

SOURCE=..\source\hdueqp.cpp
# End Source File
# Begin Source File

SOURCE=..\source\hduhandler.cpp
# End Source File
# Begin Source File

SOURCE=..\source\mcuboardmgr.cpp
# End Source File
# Begin Source File

SOURCE=..\source\mcuinstdef.cpp
# End Source File
# Begin Source File

SOURCE=..\source\mediatranseqp.cpp
# End Source File
# Begin Source File

SOURCE=..\source\mpceqp.cpp
# End Source File
# Begin Source File

SOURCE=..\source\mpu2tpeqp.cpp
# End Source File
# Begin Source File

SOURCE=..\source\netbufeqp.cpp
# End Source File
# Begin Source File

SOURCE=..\source\umseqp.cpp
# End Source File
# Begin Source File

SOURCE=..\source\vmpeqp.cpp
# End Source File
# End Group
# Begin Group "Head Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\include\adaptereqp.h
# End Source File
# Begin Source File

SOURCE=..\include\audbaseqp.h
# End Source File
# Begin Source File

SOURCE=..\include\audbashandler.h
# End Source File
# Begin Source File

SOURCE=..\include\audiomixeqp.h
# End Source File
# Begin Source File

SOURCE=..\include\audmixhandler.h
# End Source File
# Begin Source File

SOURCE=..\include\baseqp.h
# End Source File
# Begin Source File

SOURCE=..\include\eqpinst.h
# End Source File
# Begin Source File

SOURCE=..\..\common\tp\eqpinterface.h
# End Source File
# Begin Source File

SOURCE=..\include\eqpmgr.h
# End Source File
# Begin Source File

SOURCE=..\include\hdudef.h
# End Source File
# Begin Source File

SOURCE=..\include\hdueqp.h
# End Source File
# Begin Source File

SOURCE=..\include\hduhandler.h
# End Source File
# Begin Source File

SOURCE=..\include\mcuboardmgr.h
# End Source File
# Begin Source File

SOURCE=..\include\mcudef.h
# End Source File
# Begin Source File

SOURCE=..\include\mcuinstdef.h
# End Source File
# Begin Source File

SOURCE=..\include\mediatranseqp.h
# End Source File
# Begin Source File

SOURCE=..\include\mpceqp.h
# End Source File
# Begin Source File

SOURCE=..\include\mpu2tpeqp.h
# End Source File
# Begin Source File

SOURCE=..\include\netbufeqp.h
# End Source File
# Begin Source File

SOURCE=..\include\servicehandler.h
# End Source File
# Begin Source File

SOURCE=..\include\umseqp.h
# End Source File
# Begin Source File

SOURCE=..\include\vmpeqp.h
# End Source File
# End Group
# End Target
# End Project
