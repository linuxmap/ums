# Microsoft Developer Studio Generated NMAKE File, Based on regserver.dsp
!IF "$(CFG)" == ""
CFG=regserver - Win32 Debug
!MESSAGE No configuration specified. Defaulting to regserver - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "regserver - Win32 Release" && "$(CFG)" != "regserver - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "regserver.mak" CFG="regserver - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "regserver - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "regserver - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "regserver - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\regserver.exe"


CLEAN :
	-@erase "$(INTDIR)\regoprdb.obj"
	-@erase "$(INTDIR)\regserver.obj"
	-@erase "$(INTDIR)\regstackin.obj"
	-@erase "$(INTDIR)\regstackout.obj"
	-@erase "$(INTDIR)\stackmsgconvert.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\regserver.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "..\include" /I "..\..\common\tp" /I "..\..\..\10-common\include\platform" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-Common\include\protocol" /I "..\..\..\10-Common\include\tp" /I "..\..\..\10-Common\include\protocol\sipstack" /I "..\..\..\10-common\include\cbb\tinyxml" /I "..\..\..\10-Common\include\protocol\tp" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "_ENABLE_QUANTUM_PROJECT_" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\regserver.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=osplib.lib kdvsys.lib xmlengine.lib kdvsipadapterlib.lib kdvdatanetlib.lib Kdvencrypt.lib kdvsipstacklib.lib umsmsg.lib tpmsgmgr.lib kdvlog.lib lanman.lib tinyxml.lib kdvprotocommon.lib tpquantum.lib umsapi.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\regserver.pdb" /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"nafxcw.lib" /out:"$(OUTDIR)\regserver.exe" /libpath:"..\..\..\10-common\lib\release\win32" 
LINK32_OBJS= \
	"$(INTDIR)\regserver.obj" \
	"$(INTDIR)\regstackin.obj" \
	"$(INTDIR)\regstackout.obj" \
	"$(INTDIR)\stackmsgconvert.obj" \
	"$(INTDIR)\regoprdb.obj"

"$(OUTDIR)\regserver.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "regserver - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\regserver.exe"


CLEAN :
	-@erase "$(INTDIR)\regoprdb.obj"
	-@erase "$(INTDIR)\regserver.obj"
	-@erase "$(INTDIR)\regstackin.obj"
	-@erase "$(INTDIR)\regstackout.obj"
	-@erase "$(INTDIR)\stackmsgconvert.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\regserver.exe"
	-@erase "$(OUTDIR)\regserver.ilk"
	-@erase "$(OUTDIR)\regserver.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\..\common\tp" /I "..\..\..\10-common\include\platform" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-Common\include\protocol" /I "..\..\..\10-Common\include\tp" /I "..\..\..\10-Common\include\protocol\sipstack" /I "..\..\..\10-common\include\cbb\tinyxml" /I "..\..\..\10-Common\include\protocol\tp" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "_ENABLE_QUANTUM_PROJECT_" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\regserver.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=osplib.lib kdvsys.lib xmlengine.lib kdvsipadapterlib.lib kdvdatanetlib.lib Kdvencrypt.lib kdvsipstacklib.lib umsmsg.lib tpmsgmgr.lib kdvlog.lib lanman.lib tinyxml.lib kdvprotocommon.lib tpquantum.lib umsapi.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\regserver.pdb" /debug /machine:I386 /nodefaultlib:"LIBCD.lib" /nodefaultlib:"nafxcwd.lib" /nodefaultlib:"LIBCMTD.lib" /out:"$(OUTDIR)\regserver.exe" /pdbtype:sept /libpath:"..\..\..\10-common\lib\debug\win32" 
LINK32_OBJS= \
	"$(INTDIR)\regserver.obj" \
	"$(INTDIR)\regstackin.obj" \
	"$(INTDIR)\regstackout.obj" \
	"$(INTDIR)\stackmsgconvert.obj" \
	"$(INTDIR)\regoprdb.obj"

"$(OUTDIR)\regserver.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("regserver.dep")
!INCLUDE "regserver.dep"
!ELSE 
!MESSAGE Warning: cannot find "regserver.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "regserver - Win32 Release" || "$(CFG)" == "regserver - Win32 Debug"
SOURCE=..\source\regserver.cpp

"$(INTDIR)\regserver.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\regstackin.cpp

"$(INTDIR)\regstackin.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\regstackout.cpp

"$(INTDIR)\regstackout.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\stackmsgconvert.cpp

"$(INTDIR)\stackmsgconvert.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\regoprdb.cpp

"$(INTDIR)\regoprdb.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

