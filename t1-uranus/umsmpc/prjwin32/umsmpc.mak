# Microsoft Developer Studio Generated NMAKE File, Based on umsmpc.dsp
!IF "$(CFG)" == ""
CFG=umsmpc - Win32 Debug
!MESSAGE No configuration specified. Defaulting to umsmpc - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "umsmpc - Win32 Release" && "$(CFG)" != "umsmpc - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "umsmpc.mak" CFG="umsmpc - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "umsmpc - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "umsmpc - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "umsmpc - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\umsmpc.exe"


CLEAN :
	-@erase "$(INTDIR)\mpccfg.obj"
	-@erase "$(INTDIR)\umsmpcinst.obj"
	-@erase "$(INTDIR)\umsmpcmain.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\umsmpc.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "..\include" /I "..\..\common\tp" /I "..\..\..\10-common\include\platform" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-Common\include\tp" /I "..\..\..\10-Common\include\protocol" /I "..\..\..\10-Common\include\protocol\tp" /I "..\..\..\10-common\include\cbb\tinyxml" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\umsmpc.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\umsmpc.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=osplib.lib kdvsys.lib xmlengine.lib umsmsg.lib tpmsgmgr.lib umsapi.lib kdvlog.lib tinyxml.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\umsmpc.pdb" /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"nafxcw.lib" /out:"$(OUTDIR)\umsmpc.exe" /libpath:"..\..\..\10-common\lib\release\win32" 
LINK32_OBJS= \
	"$(INTDIR)\mpccfg.obj" \
	"$(INTDIR)\umsmpcinst.obj" \
	"$(INTDIR)\umsmpcmain.obj"

"$(OUTDIR)\umsmpc.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "umsmpc - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\umsmpc.exe"


CLEAN :
	-@erase "$(INTDIR)\mpccfg.obj"
	-@erase "$(INTDIR)\umsmpcinst.obj"
	-@erase "$(INTDIR)\umsmpcmain.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\umsmpc.exe"
	-@erase "$(OUTDIR)\umsmpc.ilk"
	-@erase "$(OUTDIR)\umsmpc.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\..\common\tp" /I "..\..\..\10-common\include\platform" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-Common\include\tp" /I "..\..\..\10-Common\include\protocol" /I "..\..\..\10-Common\include\protocol\tp" /I "..\..\..\10-common\include\cbb\tinyxml" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\umsmpc.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\umsmpc.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=osplib.lib kdvsys.lib xmlengine.lib umsmsg.lib tpmsgmgr.lib umsapi.lib kdvlog.lib tinyxml.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\umsmpc.pdb" /debug /machine:I386 /nodefaultlib:"libcd.lib" /nodefaultlib:"nafxcwd.lib" /out:"$(OUTDIR)\umsmpc.exe" /pdbtype:sept /libpath:"..\..\..\10-common\lib\debug\win32" 
LINK32_OBJS= \
	"$(INTDIR)\mpccfg.obj" \
	"$(INTDIR)\umsmpcinst.obj" \
	"$(INTDIR)\umsmpcmain.obj"

"$(OUTDIR)\umsmpc.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("umsmpc.dep")
!INCLUDE "umsmpc.dep"
!ELSE 
!MESSAGE Warning: cannot find "umsmpc.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "umsmpc - Win32 Release" || "$(CFG)" == "umsmpc - Win32 Debug"
SOURCE=..\source\mpccfg.cpp

"$(INTDIR)\mpccfg.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\umsmpcinst.cpp

"$(INTDIR)\umsmpcinst.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\umsmpcmain.cpp

"$(INTDIR)\umsmpcmain.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

