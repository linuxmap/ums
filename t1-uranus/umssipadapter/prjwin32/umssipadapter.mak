# Microsoft Developer Studio Generated NMAKE File, Based on umssipadapter.dsp
!IF "$(CFG)" == ""
CFG=umssipadapter - Win32 Debug
!MESSAGE No configuration specified. Defaulting to umssipadapter - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "umssipadapter - Win32 Release" && "$(CFG)" != "umssipadapter - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "umssipadapter.mak" CFG="umssipadapter - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "umssipadapter - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "umssipadapter - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "umssipadapter - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\umssipadapter.exe"


CLEAN :
	-@erase "$(INTDIR)\adaptercfg.obj"
	-@erase "$(INTDIR)\umsdataconvet.obj"
	-@erase "$(INTDIR)\umssipadapterinst.obj"
	-@erase "$(INTDIR)\umssipadaptermain.obj"
	-@erase "$(INTDIR)\umsstackinterface.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\umssipadapter.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "..\include" /I "..\..\common\tp" /I "..\..\..\10-common\include\platform" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-Common\include\protocol" /I "..\..\..\10-Common\include\tp" /I "..\..\..\10-Common\include\protocol\sipstack" /I "..\..\..\10-Common\include\protocol\tp" /I "..\..\..\10-common\include\cbb\tinyxml" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "_ENABLE_QUANTUM_PROJECT_" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\umssipadapter.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=bfcplib.lib tpquantum.lib OspDll.lib kdvsys.lib xmlengine.lib kdvdatanetlib.lib Kdvencrypt.lib umsmsg.lib tpmsgmgr.lib protocoladapter.lib umsapi.lib kdvlog.lib modulemananger.lib kdv323stacklib.lib kdv323adapterlib_tps.lib kdvcascade.lib kdv323modulelib.lib kdvsipstack2.lib kdvsipadapterlib2.lib kdvsipmodulelib2.lib lanman.lib tinyxml.lib zlibx.lib kpropx.lib kdvprotocommon.lib kdvsdp.lib quantumsock.lib /nologo /stack:0x1000000 /subsystem:console /incremental:no /pdb:"$(OUTDIR)\umssipadapter.pdb" /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"nafxcw.lib" /nodefaultlib:"libcmt.lib" /out:"$(OUTDIR)\umssipadapter.exe" /libpath:"..\..\..\10-common\lib\release\win32" 
LINK32_OBJS= \
	"$(INTDIR)\adaptercfg.obj" \
	"$(INTDIR)\umsdataconvet.obj" \
	"$(INTDIR)\umssipadapterinst.obj" \
	"$(INTDIR)\umssipadaptermain.obj" \
	"$(INTDIR)\umsstackinterface.obj"

"$(OUTDIR)\umssipadapter.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "umssipadapter - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\umssipadapter.exe"


CLEAN :
	-@erase "$(INTDIR)\adaptercfg.obj"
	-@erase "$(INTDIR)\umsdataconvet.obj"
	-@erase "$(INTDIR)\umssipadapterinst.obj"
	-@erase "$(INTDIR)\umssipadaptermain.obj"
	-@erase "$(INTDIR)\umsstackinterface.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\umssipadapter.exe"
	-@erase "$(OUTDIR)\umssipadapter.ilk"
	-@erase "$(OUTDIR)\umssipadapter.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\..\common\tp" /I "..\..\..\10-common\include\platform" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-Common\include\protocol" /I "..\..\..\10-Common\include\tp" /I "..\..\..\10-Common\include\protocol\sipstack" /I "..\..\..\10-Common\include\protocol\tp" /I "..\..\..\10-common\include\cbb\tinyxml" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "_ENABLE_QUANTUM_PROJECT_" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\umssipadapter.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=bfcplib.lib tpquantum.lib OspDll.lib kdvsys.lib xmlengine.lib kdvdatanetlib.lib Kdvencrypt.lib umsmsg.lib tpmsgmgr.lib protocoladapter.lib umsapi.lib kdvlog.lib modulemananger.lib kdv323stacklib.lib kdv323adapterlib_tps.lib kdvcascade.lib kdv323modulelib.lib kdvsipstack2.lib kdvsipadapterlib2.lib kdvsipmodulelib2.lib lanman.lib tinyxml.lib zlibx.lib kpropx.lib kdvprotocommon.lib kdvsdp.lib quantumsock.lib /nologo /stack:0x1000000 /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\umssipadapter.pdb" /debug /machine:I386 /nodefaultlib:"libcd.lib" /nodefaultlib:"nafxcwd.lib" /nodefaultlib:"libcmtd.lib" /out:"$(OUTDIR)\umssipadapter.exe" /pdbtype:sept /libpath:"..\..\..\10-common\lib\debug\win32" 
LINK32_OBJS= \
	"$(INTDIR)\adaptercfg.obj" \
	"$(INTDIR)\umsdataconvet.obj" \
	"$(INTDIR)\umssipadapterinst.obj" \
	"$(INTDIR)\umssipadaptermain.obj" \
	"$(INTDIR)\umsstackinterface.obj"

"$(OUTDIR)\umssipadapter.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("umssipadapter.dep")
!INCLUDE "umssipadapter.dep"
!ELSE 
!MESSAGE Warning: cannot find "umssipadapter.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "umssipadapter - Win32 Release" || "$(CFG)" == "umssipadapter - Win32 Debug"
SOURCE=..\source\adaptercfg.cpp

"$(INTDIR)\adaptercfg.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\umsdataconvet.cpp

"$(INTDIR)\umsdataconvet.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\umssipadapterinst.cpp

"$(INTDIR)\umssipadapterinst.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\umssipadaptermain.cpp

"$(INTDIR)\umssipadaptermain.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\umsstackinterface.cpp

"$(INTDIR)\umsstackinterface.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

