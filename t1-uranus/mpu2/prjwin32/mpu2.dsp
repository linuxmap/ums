# Microsoft Developer Studio Project File - Name="mpu2" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=mpu2 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "mpu2.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "mpu2.mak" CFG="mpu2 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "mpu2 - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "mpu2 - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "mpu2 - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\..\..\10-common\include\tp" /I "..\..\common\tp" /I "..\..\..\10-common\include\platform\dm816x" /I "..\include" /I "..\..\common\include" /I "..\..\..\10-Common\include\platform" /I "..\..\..\10-Common\include\mcu" /I "..\..\..\10-Common\include\system1" /I "..\..\..\10-Common\include\protocol" /I "..\..\..\10-Common\include\protocol\tp" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "_ENABLE_QUANTUM_PROJECT_" /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kdvlog.lib osplib.lib kdvsys.lib kdvmedianet.lib fcnet.lib enfc.lib Kdvencrypt.lib tinyxml.lib xmlengine.lib umsmsg.lib tpmsgmgr.lib umsapi.lib umsboard.lib mcueqpsimu.lib tpquantum.lib lanman.lib /nologo /subsystem:console /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"nafxcw.lib" /libpath:"..\..\..\10-common\lib\release\win32"

!ELSEIF  "$(CFG)" == "mpu2 - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\..\..\10-common\include\tp" /I "..\..\common\tp" /I "..\..\..\10-common\include\platform\dm816x" /I "..\include" /I "..\..\common\include" /I "..\..\..\10-Common\include\platform" /I "..\..\..\10-Common\include\mcu" /I "..\..\..\10-Common\include\system1" /I "..\..\..\10-Common\include\protocol" /I "..\..\..\10-Common\include\protocol\tp" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "_ENABLE_QUANTUM_PROJECT_" /YX /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kdvlog.lib osplib.lib kdvsys.lib kdvmedianet.lib fcnet.lib enfc.lib Kdvencrypt.lib tinyxml.lib xmlengine.lib umsmsg.lib tpmsgmgr.lib umsapi.lib umsboard.lib mcueqpsimu.lib tpquantum.lib lanman.lib /nologo /subsystem:console /debug /machine:I386 /nodefaultlib:"libcd.lib" /nodefaultlib:"nafxcwd.lib" /pdbtype:sept /libpath:"..\..\..\10-common\lib\debug\win32"
# SUBTRACT LINK32 /nodefaultlib

!ENDIF 

# Begin Target

# Name "mpu2 - Win32 Release"
# Name "mpu2 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\source\main.cpp
# End Source File
# Begin Source File

SOURCE=..\source\umsvmp.cpp
# End Source File
# Begin Source File

SOURCE=..\source\umsvmpinst.cpp
# End Source File
# Begin Source File

SOURCE=..\source\vmprcvchan.cpp
# End Source File
# Begin Source File

SOURCE=..\source\vmpsndchan.cpp
# End Source File
# Begin Source File

SOURCE=..\source\vmpstyleinfo.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE="..\..\..\10-common\include\tp\eventoutmpu2tp.h"
# End Source File
# Begin Source File

SOURCE=..\include\umsvmp.h
# End Source File
# Begin Source File

SOURCE=..\include\umsvmpinst.h
# End Source File
# Begin Source File

SOURCE=..\include\vmprcvchan.h
# End Source File
# Begin Source File

SOURCE=..\include\vmpsndchan.h
# End Source File
# Begin Source File

SOURCE=..\include\vmpstyleinfo.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
