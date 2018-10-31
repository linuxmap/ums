# Microsoft Developer Studio Generated NMAKE File, Based on umscall.dsp
!IF "$(CFG)" == ""
CFG=umscall - Win32 Debug
!MESSAGE No configuration specified. Defaulting to umscall - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "umscall - Win32 Release" && "$(CFG)" != "umscall - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "umscall.mak" CFG="umscall - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "umscall - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "umscall - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "umscall - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : "..\..\..\10-common\lib\release\win32\umscall.lib"


CLEAN :
	-@erase "$(INTDIR)\bandwidth.obj"
	-@erase "$(INTDIR)\callinnerstruct.obj"
	-@erase "$(INTDIR)\callmgr.obj"
	-@erase "$(INTDIR)\callnodemgr.obj"
	-@erase "$(INTDIR)\callprint.obj"
	-@erase "$(INTDIR)\dataconfhandler.obj"
	-@erase "$(INTDIR)\dsnodepool.obj"
	-@erase "$(INTDIR)\dualmgr.obj"
	-@erase "$(INTDIR)\getvidaud.obj"
	-@erase "$(INTDIR)\nodefsm.obj"
	-@erase "$(INTDIR)\pollmgr.obj"
	-@erase "$(INTDIR)\procnodeds.obj"
	-@erase "$(INTDIR)\putaud.obj"
	-@erase "$(INTDIR)\querytmpalias.obj"
	-@erase "$(INTDIR)\selviewmgr.obj"
	-@erase "$(INTDIR)\tvwallmgr.obj"
	-@erase "$(INTDIR)\umsaudmix.obj"
	-@erase "$(INTDIR)\umsbas.obj"
	-@erase "$(INTDIR)\umsconfinst.obj"
	-@erase "$(INTDIR)\umsdiscussnew.obj"
	-@erase "$(INTDIR)\umseapu.obj"
	-@erase "$(INTDIR)\umseqpservice.obj"
	-@erase "$(INTDIR)\umsgetconfvidaud.obj"
	-@erase "$(INTDIR)\umsmcumgr.obj"
	-@erase "$(INTDIR)\umsnetportmgr.obj"
	-@erase "$(INTDIR)\umsreg.obj"
	-@erase "$(INTDIR)\umsrollcall.obj"
	-@erase "$(INTDIR)\umsstackinterface.obj"
	-@erase "$(INTDIR)\umsvmp.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vmpservicehandler.obj"
	-@erase "..\..\..\10-common\lib\release\win32\umscall.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\include" /I "..\..\common\tp" /I "..\..\..\10-common\include\protocol" /I "..\..\..\10-common\include\platform\\" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-common\include\tp" /I "..\..\..\10-Common\include\protocol\tp" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "_AFXDLL" /Fp"$(INTDIR)\umscall.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\umscall.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"..\..\..\10-common\lib\release\win32\umscall.lib" 
LIB32_OBJS= \
	"$(INTDIR)\bandwidth.obj" \
	"$(INTDIR)\callinnerstruct.obj" \
	"$(INTDIR)\callmgr.obj" \
	"$(INTDIR)\callnodemgr.obj" \
	"$(INTDIR)\callprint.obj" \
	"$(INTDIR)\dataconfhandler.obj" \
	"$(INTDIR)\dsnodepool.obj" \
	"$(INTDIR)\dualmgr.obj" \
	"$(INTDIR)\getvidaud.obj" \
	"$(INTDIR)\nodefsm.obj" \
	"$(INTDIR)\pollmgr.obj" \
	"$(INTDIR)\procnodeds.obj" \
	"$(INTDIR)\putaud.obj" \
	"$(INTDIR)\selviewmgr.obj" \
	"$(INTDIR)\tvwallmgr.obj" \
	"$(INTDIR)\umsaudmix.obj" \
	"$(INTDIR)\umsbas.obj" \
	"$(INTDIR)\umsconfinst.obj" \
	"$(INTDIR)\umsdiscussnew.obj" \
	"$(INTDIR)\umseapu.obj" \
	"$(INTDIR)\umseqpservice.obj" \
	"$(INTDIR)\umsgetconfvidaud.obj" \
	"$(INTDIR)\querytmpalias.obj" \
	"$(INTDIR)\umsmcumgr.obj" \
	"$(INTDIR)\umsnetportmgr.obj" \
	"$(INTDIR)\umsreg.obj" \
	"$(INTDIR)\umsrollcall.obj" \
	"$(INTDIR)\umsstackinterface.obj" \
	"$(INTDIR)\umsvmp.obj" \
	"$(INTDIR)\vmpservicehandler.obj"

"..\..\..\10-common\lib\release\win32\umscall.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "umscall - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "..\..\..\10-common\lib\debug\win32\umscall.lib"


CLEAN :
	-@erase "$(INTDIR)\bandwidth.obj"
	-@erase "$(INTDIR)\callinnerstruct.obj"
	-@erase "$(INTDIR)\callmgr.obj"
	-@erase "$(INTDIR)\callnodemgr.obj"
	-@erase "$(INTDIR)\callprint.obj"
	-@erase "$(INTDIR)\dataconfhandler.obj"
	-@erase "$(INTDIR)\dsnodepool.obj"
	-@erase "$(INTDIR)\dualmgr.obj"
	-@erase "$(INTDIR)\getvidaud.obj"
	-@erase "$(INTDIR)\nodefsm.obj"
	-@erase "$(INTDIR)\pollmgr.obj"
	-@erase "$(INTDIR)\procnodeds.obj"
	-@erase "$(INTDIR)\putaud.obj"
	-@erase "$(INTDIR)\querytmpalias.obj"
	-@erase "$(INTDIR)\selviewmgr.obj"
	-@erase "$(INTDIR)\tvwallmgr.obj"
	-@erase "$(INTDIR)\umsaudmix.obj"
	-@erase "$(INTDIR)\umsbas.obj"
	-@erase "$(INTDIR)\umsconfinst.obj"
	-@erase "$(INTDIR)\umsdiscussnew.obj"
	-@erase "$(INTDIR)\umseapu.obj"
	-@erase "$(INTDIR)\umseqpservice.obj"
	-@erase "$(INTDIR)\umsgetconfvidaud.obj"
	-@erase "$(INTDIR)\umsmcumgr.obj"
	-@erase "$(INTDIR)\umsnetportmgr.obj"
	-@erase "$(INTDIR)\umsreg.obj"
	-@erase "$(INTDIR)\umsrollcall.obj"
	-@erase "$(INTDIR)\umsstackinterface.obj"
	-@erase "$(INTDIR)\umsvmp.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\vmpservicehandler.obj"
	-@erase "..\..\..\10-common\lib\debug\win32\umscall.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\..\common\tp" /I "..\..\..\10-common\include\protocol" /I "..\..\..\10-common\include\platform\\" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-common\include\tp" /I "..\..\..\10-common\include\protocol\tp" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "_AFXDLL" /Fp"$(INTDIR)\umscall.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\umscall.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"..\..\..\10-common\lib\debug\win32\umscall.lib" 
LIB32_OBJS= \
	"$(INTDIR)\bandwidth.obj" \
	"$(INTDIR)\callinnerstruct.obj" \
	"$(INTDIR)\callmgr.obj" \
	"$(INTDIR)\callnodemgr.obj" \
	"$(INTDIR)\callprint.obj" \
	"$(INTDIR)\dataconfhandler.obj" \
	"$(INTDIR)\dsnodepool.obj" \
	"$(INTDIR)\dualmgr.obj" \
	"$(INTDIR)\getvidaud.obj" \
	"$(INTDIR)\nodefsm.obj" \
	"$(INTDIR)\pollmgr.obj" \
	"$(INTDIR)\procnodeds.obj" \
	"$(INTDIR)\putaud.obj" \
	"$(INTDIR)\selviewmgr.obj" \
	"$(INTDIR)\tvwallmgr.obj" \
	"$(INTDIR)\umsaudmix.obj" \
	"$(INTDIR)\umsbas.obj" \
	"$(INTDIR)\umsconfinst.obj" \
	"$(INTDIR)\umsdiscussnew.obj" \
	"$(INTDIR)\umseapu.obj" \
	"$(INTDIR)\umseqpservice.obj" \
	"$(INTDIR)\umsgetconfvidaud.obj" \
	"$(INTDIR)\querytmpalias.obj" \
	"$(INTDIR)\umsmcumgr.obj" \
	"$(INTDIR)\umsnetportmgr.obj" \
	"$(INTDIR)\umsreg.obj" \
	"$(INTDIR)\umsrollcall.obj" \
	"$(INTDIR)\umsstackinterface.obj" \
	"$(INTDIR)\umsvmp.obj" \
	"$(INTDIR)\vmpservicehandler.obj"

"..\..\..\10-common\lib\debug\win32\umscall.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("umscall.dep")
!INCLUDE "umscall.dep"
!ELSE 
!MESSAGE Warning: cannot find "umscall.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "umscall - Win32 Release" || "$(CFG)" == "umscall - Win32 Debug"
SOURCE=..\source\bandwidth.cpp

"$(INTDIR)\bandwidth.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\callinnerstruct.cpp

"$(INTDIR)\callinnerstruct.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\callmgr.cpp

"$(INTDIR)\callmgr.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\callnodemgr.cpp

"$(INTDIR)\callnodemgr.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\callprint.cpp

"$(INTDIR)\callprint.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\dataconfhandler.cpp

"$(INTDIR)\dataconfhandler.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\dsnodepool.cpp

"$(INTDIR)\dsnodepool.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\dualmgr.cpp

"$(INTDIR)\dualmgr.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\getvidaud.cpp

"$(INTDIR)\getvidaud.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\nodefsm.cpp

"$(INTDIR)\nodefsm.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\pollmgr.cpp

"$(INTDIR)\pollmgr.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\procnodeds.cpp

"$(INTDIR)\procnodeds.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\putaud.cpp

"$(INTDIR)\putaud.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\querytmpalias.cpp

"$(INTDIR)\querytmpalias.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\selviewmgr.cpp

"$(INTDIR)\selviewmgr.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\tvwallmgr.cpp

"$(INTDIR)\tvwallmgr.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\umsaudmix.cpp

"$(INTDIR)\umsaudmix.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\umsbas.cpp

"$(INTDIR)\umsbas.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\umsconfinst.cpp

"$(INTDIR)\umsconfinst.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\umsdiscussnew.cpp

"$(INTDIR)\umsdiscussnew.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\umseapu.cpp

"$(INTDIR)\umseapu.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\umseqpservice.cpp

"$(INTDIR)\umseqpservice.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\umsgetconfvidaud.cpp

"$(INTDIR)\umsgetconfvidaud.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\umsmcumgr.cpp

"$(INTDIR)\umsmcumgr.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\umsnetportmgr.cpp

"$(INTDIR)\umsnetportmgr.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\umsreg.cpp

"$(INTDIR)\umsreg.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\umsrollcall.cpp

"$(INTDIR)\umsrollcall.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\umsstackinterface.cpp

"$(INTDIR)\umsstackinterface.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\umsvmp.cpp

"$(INTDIR)\umsvmp.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\vmpservicehandler.cpp

"$(INTDIR)\vmpservicehandler.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

