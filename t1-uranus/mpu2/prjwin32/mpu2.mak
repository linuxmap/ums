# Microsoft Developer Studio Generated NMAKE File, Based on mpu2.dsp
!IF "$(CFG)" == ""
CFG=mpu2 - Win32 Debug
!MESSAGE No configuration specified. Defaulting to mpu2 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "mpu2 - Win32 Release" && "$(CFG)" != "mpu2 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "mpu2.mak" CFG="mpu2 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "mpu2 - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "mpu2 - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "mpu2 - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\mpu2.exe"


CLEAN :
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\umsvmp.obj"
	-@erase "$(INTDIR)\umsvmpinst.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vmprcvchan.obj"
	-@erase "$(INTDIR)\vmpsndchan.obj"
	-@erase "$(INTDIR)\vmpstyleinfo.obj"
	-@erase "$(OUTDIR)\mpu2.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "..\..\..\10-common\include\tp" /I "..\..\common\tp" /I "..\..\..\10-common\include\platform\dm816x" /I "..\include" /I "..\..\common\include" /I "..\..\..\10-Common\include\platform" /I "..\..\..\10-Common\include\mcu" /I "..\..\..\10-Common\include\system1" /I "..\..\..\10-Common\include\protocol" /I "..\..\..\10-Common\include\protocol\tp" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "_ENABLE_QUANTUM_PROJECT_" /Fp"$(INTDIR)\mpu2.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\mpu2.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kdvlog.lib osplib.lib kdvsys.lib kdvmedianet.lib fcnet.lib enfc.lib Kdvencrypt.lib tinyxml.lib xmlengine.lib umsmsg.lib tpmsgmgr.lib umsapi.lib umsboard.lib mcueqpsimu.lib tpquantum.lib lanman.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\mpu2.pdb" /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"nafxcw.lib" /out:"$(OUTDIR)\mpu2.exe" /libpath:"..\..\..\10-common\lib\release\win32" 
LINK32_OBJS= \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\umsvmp.obj" \
	"$(INTDIR)\umsvmpinst.obj" \
	"$(INTDIR)\vmprcvchan.obj" \
	"$(INTDIR)\vmpsndchan.obj" \
	"$(INTDIR)\vmpstyleinfo.obj"

"$(OUTDIR)\mpu2.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "mpu2 - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\mpu2.exe"


CLEAN :
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\umsvmp.obj"
	-@erase "$(INTDIR)\umsvmpinst.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\vmprcvchan.obj"
	-@erase "$(INTDIR)\vmpsndchan.obj"
	-@erase "$(INTDIR)\vmpstyleinfo.obj"
	-@erase "$(OUTDIR)\mpu2.exe"
	-@erase "$(OUTDIR)\mpu2.ilk"
	-@erase "$(OUTDIR)\mpu2.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "..\..\..\10-common\include\tp" /I "..\..\common\tp" /I "..\..\..\10-common\include\platform\dm816x" /I "..\include" /I "..\..\common\include" /I "..\..\..\10-Common\include\platform" /I "..\..\..\10-Common\include\mcu" /I "..\..\..\10-Common\include\system1" /I "..\..\..\10-Common\include\protocol" /I "..\..\..\10-Common\include\protocol\tp" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "_ENABLE_QUANTUM_PROJECT_" /Fp"$(INTDIR)\mpu2.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\mpu2.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kdvlog.lib osplib.lib kdvsys.lib kdvmedianet.lib fcnet.lib enfc.lib Kdvencrypt.lib tinyxml.lib xmlengine.lib umsmsg.lib tpmsgmgr.lib umsapi.lib umsboard.lib mcueqpsimu.lib tpquantum.lib lanman.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\mpu2.pdb" /debug /machine:I386 /nodefaultlib:"libcd.lib" /nodefaultlib:"nafxcwd.lib" /out:"$(OUTDIR)\mpu2.exe" /pdbtype:sept /libpath:"..\..\..\10-common\lib\debug\win32" 
LINK32_OBJS= \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\umsvmp.obj" \
	"$(INTDIR)\umsvmpinst.obj" \
	"$(INTDIR)\vmprcvchan.obj" \
	"$(INTDIR)\vmpsndchan.obj" \
	"$(INTDIR)\vmpstyleinfo.obj"

"$(OUTDIR)\mpu2.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("mpu2.dep")
!INCLUDE "mpu2.dep"
!ELSE 
!MESSAGE Warning: cannot find "mpu2.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "mpu2 - Win32 Release" || "$(CFG)" == "mpu2 - Win32 Debug"
SOURCE=..\source\main.cpp

"$(INTDIR)\main.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\umsvmp.cpp

"$(INTDIR)\umsvmp.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\umsvmpinst.cpp

"$(INTDIR)\umsvmpinst.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\vmprcvchan.cpp

"$(INTDIR)\vmprcvchan.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\vmpsndchan.cpp

"$(INTDIR)\vmpsndchan.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\vmpstyleinfo.cpp

"$(INTDIR)\vmpstyleinfo.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

