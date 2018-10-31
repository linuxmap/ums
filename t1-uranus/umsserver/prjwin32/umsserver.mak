# Microsoft Developer Studio Generated NMAKE File, Based on umsserver.dsp
!IF "$(CFG)" == ""
CFG=umsserver - Win32 Debug
!MESSAGE No configuration specified. Defaulting to umsserver - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "umsserver - Win32 Release" && "$(CFG)" != "umsserver - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "umsserver.mak" CFG="umsserver - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "umsserver - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "umsserver - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "umsserver - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\umsserver.exe"


CLEAN :
	-@erase "$(INTDIR)\handleboardservice.obj"
	-@erase "$(INTDIR)\handlecallservice.obj"
	-@erase "$(INTDIR)\handleconftemplateservice.obj"
	-@erase "$(INTDIR)\handlehduservice.obj"
	-@erase "$(INTDIR)\handlelicense.obj"
	-@erase "$(INTDIR)\handleregservice.obj"
	-@erase "$(INTDIR)\handletoolservice.obj"
	-@erase "$(INTDIR)\testcommand.obj"
	-@erase "$(INTDIR)\tpumsmain.obj"
	-@erase "$(INTDIR)\umshdu.obj"
	-@erase "$(INTDIR)\umsobject.obj"
	-@erase "$(INTDIR)\umsserver.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\umsserver.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "..\include" /I "..\..\common\tp" /I "..\..\..\10-common\include\platform" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-Common\include\protocol" /I "..\..\..\10-Common\include\tp" /I "..\..\..\10-Common\include\protocol\sipstack" /I "..\..\..\10-common\include\protocol\tp" /I "..\..\..\10-common\include\cbb\license" /I "..\..\..\10-common\include\cbb\tinyxml" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\umsserver.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=osplib.lib kdvsys.lib xmlengine.lib Kdvencrypt.lib umsmsg.lib tpmsgmgr.lib kdvum.lib umscall.lib umsue.lib umsconfig.lib umsapi.lib templatecfg.lib umseqp.lib kdvaddrbook.lib kdvlog.lib tpaddrmgr.lib tinyxml.lib lanman.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\umsserver.pdb" /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"nafxcw.lib" /out:"$(OUTDIR)\umsserver.exe" /libpath:"..\..\..\10-common\lib\release\win32" 
LINK32_OBJS= \
	"$(INTDIR)\handleboardservice.obj" \
	"$(INTDIR)\handlecallservice.obj" \
	"$(INTDIR)\handleconftemplateservice.obj" \
	"$(INTDIR)\handlehduservice.obj" \
	"$(INTDIR)\handlelicense.obj" \
	"$(INTDIR)\handleregservice.obj" \
	"$(INTDIR)\handletoolservice.obj" \
	"$(INTDIR)\testcommand.obj" \
	"$(INTDIR)\tpumsmain.obj" \
	"$(INTDIR)\umshdu.obj" \
	"$(INTDIR)\umsobject.obj" \
	"$(INTDIR)\umsserver.obj"

"$(OUTDIR)\umsserver.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "umsserver - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\umsserver.exe" "$(OUTDIR)\umsserver.bsc"


CLEAN :
	-@erase "$(INTDIR)\handleboardservice.obj"
	-@erase "$(INTDIR)\handleboardservice.sbr"
	-@erase "$(INTDIR)\handlecallservice.obj"
	-@erase "$(INTDIR)\handlecallservice.sbr"
	-@erase "$(INTDIR)\handleconftemplateservice.obj"
	-@erase "$(INTDIR)\handleconftemplateservice.sbr"
	-@erase "$(INTDIR)\handlehduservice.obj"
	-@erase "$(INTDIR)\handlehduservice.sbr"
	-@erase "$(INTDIR)\handlelicense.obj"
	-@erase "$(INTDIR)\handlelicense.sbr"
	-@erase "$(INTDIR)\handleregservice.obj"
	-@erase "$(INTDIR)\handleregservice.sbr"
	-@erase "$(INTDIR)\handletoolservice.obj"
	-@erase "$(INTDIR)\handletoolservice.sbr"
	-@erase "$(INTDIR)\testcommand.obj"
	-@erase "$(INTDIR)\testcommand.sbr"
	-@erase "$(INTDIR)\tpumsmain.obj"
	-@erase "$(INTDIR)\tpumsmain.sbr"
	-@erase "$(INTDIR)\umshdu.obj"
	-@erase "$(INTDIR)\umshdu.sbr"
	-@erase "$(INTDIR)\umsobject.obj"
	-@erase "$(INTDIR)\umsobject.sbr"
	-@erase "$(INTDIR)\umsserver.obj"
	-@erase "$(INTDIR)\umsserver.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\umsserver.bsc"
	-@erase "$(OUTDIR)\umsserver.exe"
	-@erase "$(OUTDIR)\umsserver.ilk"
	-@erase "$(OUTDIR)\umsserver.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\..\common\tp" /I "..\..\..\10-common\include\platform" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-Common\include\protocol" /I "..\..\..\10-Common\include\tp" /I "..\..\..\10-Common\include\protocol\sipstack" /I "..\..\..\10-common\include\protocol\tp" /I "..\..\..\10-common\include\cbb\license" /I "..\..\..\10-common\include\cbb\tinyxml" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\umsserver.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\handleboardservice.sbr" \
	"$(INTDIR)\handlecallservice.sbr" \
	"$(INTDIR)\handleconftemplateservice.sbr" \
	"$(INTDIR)\handlehduservice.sbr" \
	"$(INTDIR)\handlelicense.sbr" \
	"$(INTDIR)\handleregservice.sbr" \
	"$(INTDIR)\handletoolservice.sbr" \
	"$(INTDIR)\testcommand.sbr" \
	"$(INTDIR)\tpumsmain.sbr" \
	"$(INTDIR)\umshdu.sbr" \
	"$(INTDIR)\umsobject.sbr" \
	"$(INTDIR)\umsserver.sbr"

"$(OUTDIR)\umsserver.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=osplib.lib kdvsys.lib xmlengine.lib Kdvencrypt.lib umsmsg.lib tpmsgmgr.lib kdvum.lib umscall.lib umsue.lib umsconfig.lib umsapi.lib templatecfg.lib umseqp.lib kdvaddrbook.lib kdvlog.lib tpaddrmgr.lib tinyxml.lib lanman.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\umsserver.pdb" /debug /machine:I386 /nodefaultlib:"libcd.lib" /nodefaultlib:"nafxcwd.lib" /out:"$(OUTDIR)\umsserver.exe" /pdbtype:sept /libpath:"..\..\..\10-common\lib\debug\win32" 
LINK32_OBJS= \
	"$(INTDIR)\handleboardservice.obj" \
	"$(INTDIR)\handlecallservice.obj" \
	"$(INTDIR)\handleconftemplateservice.obj" \
	"$(INTDIR)\handlehduservice.obj" \
	"$(INTDIR)\handlelicense.obj" \
	"$(INTDIR)\handleregservice.obj" \
	"$(INTDIR)\handletoolservice.obj" \
	"$(INTDIR)\testcommand.obj" \
	"$(INTDIR)\tpumsmain.obj" \
	"$(INTDIR)\umshdu.obj" \
	"$(INTDIR)\umsobject.obj" \
	"$(INTDIR)\umsserver.obj"

"$(OUTDIR)\umsserver.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("umsserver.dep")
!INCLUDE "umsserver.dep"
!ELSE 
!MESSAGE Warning: cannot find "umsserver.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "umsserver - Win32 Release" || "$(CFG)" == "umsserver - Win32 Debug"
SOURCE=..\source\handleboardservice.cpp

!IF  "$(CFG)" == "umsserver - Win32 Release"


"$(INTDIR)\handleboardservice.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "umsserver - Win32 Debug"


"$(INTDIR)\handleboardservice.obj"	"$(INTDIR)\handleboardservice.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\source\handlecallservice.cpp

!IF  "$(CFG)" == "umsserver - Win32 Release"


"$(INTDIR)\handlecallservice.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "umsserver - Win32 Debug"


"$(INTDIR)\handlecallservice.obj"	"$(INTDIR)\handlecallservice.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\source\handleconftemplateservice.cpp

!IF  "$(CFG)" == "umsserver - Win32 Release"


"$(INTDIR)\handleconftemplateservice.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "umsserver - Win32 Debug"


"$(INTDIR)\handleconftemplateservice.obj"	"$(INTDIR)\handleconftemplateservice.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\source\handlehduservice.cpp

!IF  "$(CFG)" == "umsserver - Win32 Release"


"$(INTDIR)\handlehduservice.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "umsserver - Win32 Debug"


"$(INTDIR)\handlehduservice.obj"	"$(INTDIR)\handlehduservice.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\source\handlelicense.cpp

!IF  "$(CFG)" == "umsserver - Win32 Release"


"$(INTDIR)\handlelicense.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "umsserver - Win32 Debug"


"$(INTDIR)\handlelicense.obj"	"$(INTDIR)\handlelicense.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\source\handleregservice.cpp

!IF  "$(CFG)" == "umsserver - Win32 Release"


"$(INTDIR)\handleregservice.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "umsserver - Win32 Debug"


"$(INTDIR)\handleregservice.obj"	"$(INTDIR)\handleregservice.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\source\handletoolservice.cpp

!IF  "$(CFG)" == "umsserver - Win32 Release"


"$(INTDIR)\handletoolservice.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "umsserver - Win32 Debug"


"$(INTDIR)\handletoolservice.obj"	"$(INTDIR)\handletoolservice.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 


SOURCE=..\source\testcommand.cpp

!IF  "$(CFG)" == "umsserver - Win32 Release"


"$(INTDIR)\testcommand.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "umsserver - Win32 Debug"


"$(INTDIR)\testcommand.obj"	"$(INTDIR)\testcommand.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\source\tpumsmain.cpp

!IF  "$(CFG)" == "umsserver - Win32 Release"


"$(INTDIR)\tpumsmain.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "umsserver - Win32 Debug"


"$(INTDIR)\tpumsmain.obj"	"$(INTDIR)\tpumsmain.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\source\umshdu.cpp

!IF  "$(CFG)" == "umsserver - Win32 Release"


"$(INTDIR)\umshdu.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "umsserver - Win32 Debug"


"$(INTDIR)\umshdu.obj"	"$(INTDIR)\umshdu.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\source\umsobject.cpp

!IF  "$(CFG)" == "umsserver - Win32 Release"


"$(INTDIR)\umsobject.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "umsserver - Win32 Debug"


"$(INTDIR)\umsobject.obj"	"$(INTDIR)\umsobject.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\source\umsserver.cpp

!IF  "$(CFG)" == "umsserver - Win32 Release"


"$(INTDIR)\umsserver.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "umsserver - Win32 Debug"


"$(INTDIR)\umsserver.obj"	"$(INTDIR)\umsserver.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 


!ENDIF 

