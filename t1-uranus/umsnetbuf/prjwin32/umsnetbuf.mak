# Microsoft Developer Studio Generated NMAKE File, Based on umsnetbuf.dsp
!IF "$(CFG)" == ""
CFG=umsnetbuf - Win32 Debug
!MESSAGE No configuration specified. Defaulting to umsnetbuf - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "umsnetbuf - Win32 Release" && "$(CFG)" != "umsnetbuf - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "umsnetbuf.mak" CFG="umsnetbuf - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "umsnetbuf - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "umsnetbuf - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "umsnetbuf - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\umsnetbuf.exe"


CLEAN :
	-@erase "$(INTDIR)\nbdata.obj"
	-@erase "$(INTDIR)\umsnetbufcfg.obj"
	-@erase "$(INTDIR)\umsnetbufinst.obj"
	-@erase "$(INTDIR)\umsnetbufmain.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\umsnetbuf.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "..\include" /I "..\..\common\tp" /I "..\..\..\10-common\include\platform" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-Common\include\protocol" /I "..\..\..\10-Common\include\tp" /I "..\..\..\10-Common\include\protocol\tp" /I "..\..\..\10-common\include\cbb\tinyxml" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\umsnetbuf.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=osplib.lib kdvsys.lib xmlengine.lib umsmsg.lib tpmsgmgr.lib umsapi.lib kdvnetbuf.lib kdvlog.lib tinyxml.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\umsnetbuf.pdb" /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"nafxcw.lib" /out:"$(OUTDIR)\umsnetbuf.exe" /libpath:"..\..\..\10-common\lib\release\win32" 
LINK32_OBJS= \
	"$(INTDIR)\nbdata.obj" \
	"$(INTDIR)\umsnetbufcfg.obj" \
	"$(INTDIR)\umsnetbufinst.obj" \
	"$(INTDIR)\umsnetbufmain.obj"

"$(OUTDIR)\umsnetbuf.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "umsnetbuf - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\umsnetbuf.exe"


CLEAN :
	-@erase "$(INTDIR)\nbdata.obj"
	-@erase "$(INTDIR)\umsnetbufcfg.obj"
	-@erase "$(INTDIR)\umsnetbufinst.obj"
	-@erase "$(INTDIR)\umsnetbufmain.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\umsnetbuf.exe"
	-@erase "$(OUTDIR)\umsnetbuf.ilk"
	-@erase "$(OUTDIR)\umsnetbuf.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\..\common\tp" /I "..\..\..\10-common\include\platform" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-Common\include\protocol" /I "..\..\..\10-Common\include\tp" /I "..\..\..\10-Common\include\protocol\tp" /I "..\..\..\10-common\include\cbb\tinyxml" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\umsnetbuf.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=osplib.lib kdvsys.lib xmlengine.lib umsmsg.lib tpmsgmgr.lib umsapi.lib kdvnetbuf.lib kdvlog.lib tinyxml.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\umsnetbuf.pdb" /debug /machine:I386 /nodefaultlib:"libcd.lib" /nodefaultlib:"nafxcwd.lib" /out:"$(OUTDIR)\umsnetbuf.exe" /pdbtype:sept /libpath:"..\..\..\10-common\lib\debug\win32" 
LINK32_OBJS= \
	"$(INTDIR)\nbdata.obj" \
	"$(INTDIR)\umsnetbufcfg.obj" \
	"$(INTDIR)\umsnetbufinst.obj" \
	"$(INTDIR)\umsnetbufmain.obj"

"$(OUTDIR)\umsnetbuf.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("umsnetbuf.dep")
!INCLUDE "umsnetbuf.dep"
!ELSE 
!MESSAGE Warning: cannot find "umsnetbuf.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "umsnetbuf - Win32 Release" || "$(CFG)" == "umsnetbuf - Win32 Debug"
SOURCE=..\source\nbdata.cpp

"$(INTDIR)\nbdata.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\umsnetbufcfg.cpp

"$(INTDIR)\umsnetbufcfg.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\umsnetbufinst.cpp

"$(INTDIR)\umsnetbufinst.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\umsnetbufmain.cpp

"$(INTDIR)\umsnetbufmain.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

