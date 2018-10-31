# Microsoft Developer Studio Generated NMAKE File, Based on umsmsg.dsp
!IF "$(CFG)" == ""
CFG=umsmsg - Win32 Debug
!MESSAGE No configuration specified. Defaulting to umsmsg - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "umsmsg - Win32 Release" && "$(CFG)" != "umsmsg - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
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
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "umsmsg - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : "..\..\..\10-common\lib\release\win32\umsmsg.lib"


CLEAN :
	-@erase "$(INTDIR)\umseventmgr.obj"
	-@erase "$(INTDIR)\umsinnerevent.obj"
	-@erase "$(INTDIR)\umsinnerstruct.obj"
	-@erase "$(INTDIR)\umsxmlstruct.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "..\..\..\10-common\lib\release\win32\umsmsg.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\include" /I "..\..\common\tp" /I "..\..\..\10-common\include\protocol" /I "..\..\..\10-common\include\platform\\" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-common\include\tp" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "_AFXDLL" /Fp"$(INTDIR)\umsmsg.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\umsmsg.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"..\..\..\10-common\lib\release\win32\umsmsg.lib" 
LIB32_OBJS= \
	"$(INTDIR)\umsinnerevent.obj" \
	"$(INTDIR)\umsinnerstruct.obj" \
	"$(INTDIR)\umseventmgr.obj" \
	"$(INTDIR)\umsxmlstruct.obj"

"..\..\..\10-common\lib\release\win32\umsmsg.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "umsmsg - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "..\..\..\10-common\lib\debug\win32\umsmsg.lib"


CLEAN :
	-@erase "$(INTDIR)\umseventmgr.obj"
	-@erase "$(INTDIR)\umsinnerevent.obj"
	-@erase "$(INTDIR)\umsinnerstruct.obj"
	-@erase "$(INTDIR)\umsxmlstruct.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "..\..\..\10-common\lib\debug\win32\umsmsg.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\..\common\tp" /I "..\..\..\10-common\include\protocol" /I "..\..\..\10-common\include\platform\\" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-common\include\tp" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "_AFXDLL" /Fp"$(INTDIR)\umsmsg.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\umsmsg.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"..\..\..\10-common\lib\debug\win32\umsmsg.lib" 
LIB32_OBJS= \
	"$(INTDIR)\umsinnerevent.obj" \
	"$(INTDIR)\umsinnerstruct.obj" \
	"$(INTDIR)\umseventmgr.obj" \
	"$(INTDIR)\umsxmlstruct.obj"

"..\..\..\10-common\lib\debug\win32\umsmsg.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("umsmsg.dep")
!INCLUDE "umsmsg.dep"
!ELSE 
!MESSAGE Warning: cannot find "umsmsg.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "umsmsg - Win32 Release" || "$(CFG)" == "umsmsg - Win32 Debug"
SOURCE=..\source\umsinnerevent.cpp

"$(INTDIR)\umsinnerevent.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\umsinnerstruct.cpp

"$(INTDIR)\umsinnerstruct.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\umseventmgr.cpp

"$(INTDIR)\umseventmgr.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\umsxmlstruct.cpp

"$(INTDIR)\umsxmlstruct.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

