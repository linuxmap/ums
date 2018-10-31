# Microsoft Developer Studio Generated NMAKE File, Based on devmgrservice.dsp
!IF "$(CFG)" == ""
CFG=devmgrservice - Win32 Debug
!MESSAGE No configuration specified. Defaulting to devmgrservice - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "devmgrservice - Win32 Release" && "$(CFG)" != "devmgrservice - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "devmgrservice.mak" CFG="devmgrservice - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "devmgrservice - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "devmgrservice - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "devmgrservice - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\devmgrservice.exe"


CLEAN :
	-@erase "$(INTDIR)\devinfomgr.obj"
	-@erase "$(INTDIR)\devmgrservicecfgmgr.obj"
	-@erase "$(INTDIR)\devmgrserviceinst.obj"
	-@erase "$(INTDIR)\devmgrservicemain.obj"
	-@erase "$(INTDIR)\updatemgrhandle.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\devmgrservice.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "..\include" /I "..\..\common\tp" /I "..\..\..\10-common\include\platform" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-Common\include\tp" /I "..\..\..\10-Common\include\protocol" /I "..\..\..\10-Common\include\protocol\tp" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\devmgrservice.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\devmgrservice.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=osplib.lib kdvsys.lib xmlengine.lib umsmsg.lib tpmsgmgr.lib umsapi.lib kdvlog.lib tinyxml.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\devmgrservice.pdb" /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"nafxcw.lib" /out:"$(OUTDIR)\devmgrservice.exe" /libpath:"..\..\..\10-common\lib\release\win32" 
LINK32_OBJS= \
	"$(INTDIR)\devinfomgr.obj" \
	"$(INTDIR)\devmgrservicecfgmgr.obj" \
	"$(INTDIR)\devmgrserviceinst.obj" \
	"$(INTDIR)\devmgrservicemain.obj" \
	"$(INTDIR)\updatemgrhandle.obj"

"$(OUTDIR)\devmgrservice.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "devmgrservice - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\devmgrservice.exe"


CLEAN :
	-@erase "$(INTDIR)\devinfomgr.obj"
	-@erase "$(INTDIR)\devmgrservicecfgmgr.obj"
	-@erase "$(INTDIR)\devmgrserviceinst.obj"
	-@erase "$(INTDIR)\devmgrservicemain.obj"
	-@erase "$(INTDIR)\updatemgrhandle.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\devmgrservice.exe"
	-@erase "$(OUTDIR)\devmgrservice.ilk"
	-@erase "$(OUTDIR)\devmgrservice.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\..\common\tp" /I "..\..\..\10-common\include\platform" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-Common\include\tp" /I "..\..\..\10-Common\include\protocol" /I "..\..\..\10-Common\include\protocol\tp" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\devmgrservice.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\devmgrservice.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=osplib.lib kdvsys.lib xmlengine.lib umsmsg.lib tpmsgmgr.lib umsapi.lib kdvlog.lib tinyxml.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\devmgrservice.pdb" /debug /machine:I386 /nodefaultlib:"libcd.lib" /nodefaultlib:"nafxcwd.lib" /out:"$(OUTDIR)\devmgrservice.exe" /pdbtype:sept /libpath:"..\..\..\10-common\lib\debug\win32" 
LINK32_OBJS= \
	"$(INTDIR)\devinfomgr.obj" \
	"$(INTDIR)\devmgrservicecfgmgr.obj" \
	"$(INTDIR)\devmgrserviceinst.obj" \
	"$(INTDIR)\devmgrservicemain.obj" \
	"$(INTDIR)\updatemgrhandle.obj"

"$(OUTDIR)\devmgrservice.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("devmgrservice.dep")
!INCLUDE "devmgrservice.dep"
!ELSE 
!MESSAGE Warning: cannot find "devmgrservice.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "devmgrservice - Win32 Release" || "$(CFG)" == "devmgrservice - Win32 Debug"
SOURCE=..\source\devinfomgr.cpp

"$(INTDIR)\devinfomgr.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\devmgrservicecfgmgr.cpp

"$(INTDIR)\devmgrservicecfgmgr.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\devmgrserviceinst.cpp

"$(INTDIR)\devmgrserviceinst.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\devmgrservicemain.cpp

"$(INTDIR)\devmgrservicemain.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\updatemgrhandle.cpp

"$(INTDIR)\updatemgrhandle.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 
