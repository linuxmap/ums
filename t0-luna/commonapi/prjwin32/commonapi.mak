# Microsoft Developer Studio Generated NMAKE File, Based on commonapi.dsp
!IF "$(CFG)" == ""
CFG=commonapi - Win32 Debug
!MESSAGE No configuration specified. Defaulting to commonapi - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "commonapi - Win32 Release" && "$(CFG)" != "commonapi - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "commonapi.mak" CFG="commonapi - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "commonapi - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "commonapi - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "commonapi - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : "..\..\..\10-common\lib\release\win32\commonapi.lib"


CLEAN :
	-@erase "$(INTDIR)\commonapi.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "..\..\..\10-common\lib\release\win32\commonapi.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "..\include" /I "..\..\common\include" /I "..\..\common\tp" /I "..\..\..\10-Common\include\platform\\" /I "..\..\..\10-Common\include\system1" /I "..\..\..\10-Common\include\mt" /I "..\..\..\10-Common\include\mcu" /I "..\..\..\10-Common\include\protocol" /I "..\..\..\10-Common\include\protocol\h323stack" /I "..\..\..\10-Common\include\nms1" /I "..\..\..\10-Common\include\tp" /I "..\..\cnapi\include" /I "..\..\..\10-common\include\protocol\tp" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /Fp"$(INTDIR)\commonapi.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\commonapi.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"..\..\..\10-common\lib\release\win32\commonapi.lib" 
LIB32_OBJS= \
	"$(INTDIR)\commonapi.obj"

"..\..\..\10-common\lib\release\win32\commonapi.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "commonapi - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "..\..\..\10-common\lib\debug\win32\commonapi.lib"


CLEAN :
	-@erase "$(INTDIR)\commonapi.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "..\..\..\10-common\lib\debug\win32\commonapi.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\..\common\include" /I "..\..\common\tp" /I "..\..\..\10-Common\include\platform\\" /I "..\..\..\10-Common\include\system1" /I "..\..\..\10-Common\include\mt" /I "..\..\..\10-Common\include\mcu" /I "..\..\..\10-Common\include\protocol" /I "..\..\..\10-Common\include\protocol\h323stack" /I "..\..\..\10-Common\include\nms1" /I "..\..\..\10-Common\include\tp" /I "..\..\cnapi\include" /I "..\..\..\10-common\include\protocol\tp" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /Fp"$(INTDIR)\commonapi.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\commonapi.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"..\..\..\10-common\lib\debug\win32\commonapi.lib" 
LIB32_OBJS= \
	"$(INTDIR)\commonapi.obj"

"..\..\..\10-common\lib\debug\win32\commonapi.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("commonapi.dep")
!INCLUDE "commonapi.dep"
!ELSE 
!MESSAGE Warning: cannot find "commonapi.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "commonapi - Win32 Release" || "$(CFG)" == "commonapi - Win32 Debug"
SOURCE=..\source\commonapi.cpp

"$(INTDIR)\commonapi.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

