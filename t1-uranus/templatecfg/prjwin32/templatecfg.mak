# Microsoft Developer Studio Generated NMAKE File, Based on templatecfg.dsp
!IF "$(CFG)" == ""
CFG=templatecfg - Win32 Debug
!MESSAGE No configuration specified. Defaulting to templatecfg - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "templatecfg - Win32 Release" && "$(CFG)" != "templatecfg - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "templatecfg.mak" CFG="templatecfg - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "templatecfg - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "templatecfg - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "templatecfg - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : "..\..\..\10-common\lib\release\win32\templatecfg.lib"


CLEAN :
	-@erase "$(INTDIR)\tpcfgdata.obj"
	-@erase "$(INTDIR)\tpcfginstance.obj"
	-@erase "$(INTDIR)\tpconfig.obj"
	-@erase "$(INTDIR)\tpcrc.obj"
	-@erase "$(INTDIR)\tpinfo.obj"
	-@erase "$(INTDIR)\tppersistfile.obj"
	-@erase "$(INTDIR)\tprwnewcfgfile.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "..\..\..\10-common\lib\release\win32\templatecfg.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "..\include" /I "..\..\common\tp" /I "..\..\..\10-common\include\platform\\" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-common\include\tp" /I "..\..\..\10-common\include\protocol" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /Fp"$(INTDIR)\templatecfg.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\templatecfg.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"..\..\..\10-common\lib\release\win32\templatecfg.lib" 
LIB32_OBJS= \
	"$(INTDIR)\tpcfgdata.obj" \
	"$(INTDIR)\tpcfginstance.obj" \
	"$(INTDIR)\tpconfig.obj" \
	"$(INTDIR)\tpcrc.obj" \
	"$(INTDIR)\tpinfo.obj" \
	"$(INTDIR)\tppersistfile.obj" \
	"$(INTDIR)\tprwnewcfgfile.obj"

"..\..\..\10-common\lib\release\win32\templatecfg.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "templatecfg - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "..\..\..\10-common\lib\debug\win32\templatecfg.lib"


CLEAN :
	-@erase "$(INTDIR)\tpcfgdata.obj"
	-@erase "$(INTDIR)\tpcfginstance.obj"
	-@erase "$(INTDIR)\tpconfig.obj"
	-@erase "$(INTDIR)\tpcrc.obj"
	-@erase "$(INTDIR)\tpinfo.obj"
	-@erase "$(INTDIR)\tppersistfile.obj"
	-@erase "$(INTDIR)\tprwnewcfgfile.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "..\..\..\10-common\lib\debug\win32\templatecfg.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\..\common\tp" /I "..\..\..\10-common\include\platform\\" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-common\include\tp" /I "..\..\..\10-common\include\protocol" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "_AFXDLL" /Fp"$(INTDIR)\templatecfg.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\templatecfg.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"..\..\..\10-common\lib\debug\win32\templatecfg.lib" 
LIB32_OBJS= \
	"$(INTDIR)\tpcfgdata.obj" \
	"$(INTDIR)\tpcfginstance.obj" \
	"$(INTDIR)\tpconfig.obj" \
	"$(INTDIR)\tpcrc.obj" \
	"$(INTDIR)\tpinfo.obj" \
	"$(INTDIR)\tppersistfile.obj" \
	"$(INTDIR)\tprwnewcfgfile.obj"

"..\..\..\10-common\lib\debug\win32\templatecfg.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("templatecfg.dep")
!INCLUDE "templatecfg.dep"
!ELSE 
!MESSAGE Warning: cannot find "templatecfg.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "templatecfg - Win32 Release" || "$(CFG)" == "templatecfg - Win32 Debug"
SOURCE=..\source\tpcfgdata.cpp

"$(INTDIR)\tpcfgdata.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\tpcfginstance.cpp

"$(INTDIR)\tpcfginstance.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\tpconfig.cpp

"$(INTDIR)\tpconfig.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\tpcrc.c

"$(INTDIR)\tpcrc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\tpinfo.cpp

"$(INTDIR)\tpinfo.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\tppersistfile.cpp

"$(INTDIR)\tppersistfile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\tprwnewcfgfile.cpp

"$(INTDIR)\tprwnewcfgfile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

