# Microsoft Developer Studio Generated NMAKE File, Based on umsconfig.dsp
!IF "$(CFG)" == ""
CFG=umsconfig - Win32 Debug
!MESSAGE No configuration specified. Defaulting to umsconfig - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "umsconfig - Win32 Release" && "$(CFG)" != "umsconfig - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "umsconfig.mak" CFG="umsconfig - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "umsconfig - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "umsconfig - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "umsconfig - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : "..\..\..\10-common\lib\release\win32\umsconfig.lib"


CLEAN :
	-@erase "$(INTDIR)\cfgdata.obj"
	-@erase "$(INTDIR)\cfginstance.obj"
	-@erase "$(INTDIR)\crc.obj"
	-@erase "$(INTDIR)\displaydata.obj"
	-@erase "$(INTDIR)\persistfile.obj"
	-@erase "$(INTDIR)\rwnewcfgfile.obj"
	-@erase "$(INTDIR)\umsconfig.obj"
	-@erase "$(INTDIR)\umsconfigex.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "..\..\..\10-common\lib\release\win32\umsconfig.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\include" /I "..\..\common\tp" /I "..\..\..\10-common\include\platform\\" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-common\include\tp" /I "..\..\..\10-common\include\protocol" /I "..\..\..\10-Common\include\protocol\tp" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\umsconfig.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\umsconfig.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"..\..\..\10-common\lib\release\win32\umsconfig.lib" 
LIB32_OBJS= \
	"$(INTDIR)\cfgdata.obj" \
	"$(INTDIR)\cfginstance.obj" \
	"$(INTDIR)\crc.obj" \
	"$(INTDIR)\displaydata.obj" \
	"$(INTDIR)\persistfile.obj" \
	"$(INTDIR)\rwnewcfgfile.obj" \
	"$(INTDIR)\umsconfig.obj" \
	"$(INTDIR)\umsconfigex.obj"

"..\..\..\10-common\lib\release\win32\umsconfig.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "umsconfig - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "..\..\..\10-common\lib\debug\win32\umsconfig.lib"


CLEAN :
	-@erase "$(INTDIR)\cfgdata.obj"
	-@erase "$(INTDIR)\cfginstance.obj"
	-@erase "$(INTDIR)\crc.obj"
	-@erase "$(INTDIR)\displaydata.obj"
	-@erase "$(INTDIR)\persistfile.obj"
	-@erase "$(INTDIR)\rwnewcfgfile.obj"
	-@erase "$(INTDIR)\umsconfig.obj"
	-@erase "$(INTDIR)\umsconfigex.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "..\..\..\10-common\lib\debug\win32\umsconfig.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\..\common\tp" /I "..\..\..\10-common\include\platform\\" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-common\include\tp" /I "..\..\..\10-common\include\protocol" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\umsconfig.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\umsconfig.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"..\..\..\10-common\lib\debug\win32\umsconfig.lib" 
LIB32_OBJS= \
	"$(INTDIR)\cfgdata.obj" \
	"$(INTDIR)\cfginstance.obj" \
	"$(INTDIR)\crc.obj" \
	"$(INTDIR)\displaydata.obj" \
	"$(INTDIR)\persistfile.obj" \
	"$(INTDIR)\rwnewcfgfile.obj" \
	"$(INTDIR)\umsconfig.obj" \
	"$(INTDIR)\umsconfigex.obj"

"..\..\..\10-common\lib\debug\win32\umsconfig.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("umsconfig.dep")
!INCLUDE "umsconfig.dep"
!ELSE 
!MESSAGE Warning: cannot find "umsconfig.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "umsconfig - Win32 Release" || "$(CFG)" == "umsconfig - Win32 Debug"
SOURCE=..\source\cfgdata.cpp

"$(INTDIR)\cfgdata.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\cfginstance.cpp

"$(INTDIR)\cfginstance.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\crc.c

"$(INTDIR)\crc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\displaydata.cpp

"$(INTDIR)\displaydata.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\persistfile.cpp

"$(INTDIR)\persistfile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\rwnewcfgfile.cpp

"$(INTDIR)\rwnewcfgfile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\umsconfig.cpp

"$(INTDIR)\umsconfig.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\umsconfigex.cpp

"$(INTDIR)\umsconfigex.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

