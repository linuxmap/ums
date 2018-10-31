# Microsoft Developer Studio Generated NMAKE File, Based on umseqp.dsp
!IF "$(CFG)" == ""
CFG=umseqp - Win32 Debug
!MESSAGE No configuration specified. Defaulting to umseqp - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "umseqp - Win32 Release" && "$(CFG)" != "umseqp - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "umseqp.mak" CFG="umseqp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "umseqp - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "umseqp - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "umseqp - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : "..\..\..\10-common\lib\release\win32\umseqp.lib"


CLEAN :
	-@erase "$(INTDIR)\adaptereqp.obj"
	-@erase "$(INTDIR)\audbaseqp.obj"
	-@erase "$(INTDIR)\audbashandler.obj"
	-@erase "$(INTDIR)\audiomixeqp.obj"
	-@erase "$(INTDIR)\audmixhandler.obj"
	-@erase "$(INTDIR)\baseqp.obj"
	-@erase "$(INTDIR)\eqpinst.obj"
	-@erase "$(INTDIR)\eqpinterface.obj"
	-@erase "$(INTDIR)\eqpmgr.obj"
	-@erase "$(INTDIR)\hdueqp.obj"
	-@erase "$(INTDIR)\hduhandler.obj"
	-@erase "$(INTDIR)\mcuboardmgr.obj"
	-@erase "$(INTDIR)\mcuinstdef.obj"
	-@erase "$(INTDIR)\mediatranseqp.obj"
	-@erase "$(INTDIR)\mpceqp.obj"
	-@erase "$(INTDIR)\mpu2tpeqp.obj"
	-@erase "$(INTDIR)\netbufeqp.obj"
	-@erase "$(INTDIR)\umseqp.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vmpeqp.obj"
	-@erase "..\..\..\10-common\lib\release\win32\umseqp.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\include" /I "..\..\common\tp" /I "..\..\..\10-common\include\protocol" /I "..\..\..\10-common\include\platform\\" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-common\include\tp" /I "..\..\..\10-Common\include\protocol\tp" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "_AFXDLL" /Fp"$(INTDIR)\umseqp.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\umseqp.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"..\..\..\10-common\lib\release\win32\umseqp.lib" 
LIB32_OBJS= \
	"$(INTDIR)\adaptereqp.obj" \
	"$(INTDIR)\audbaseqp.obj" \
	"$(INTDIR)\audbashandler.obj" \
	"$(INTDIR)\audiomixeqp.obj" \
	"$(INTDIR)\audmixhandler.obj" \
	"$(INTDIR)\baseqp.obj" \
	"$(INTDIR)\eqpinst.obj" \
	"$(INTDIR)\eqpinterface.obj" \
	"$(INTDIR)\eqpmgr.obj" \
	"$(INTDIR)\hdueqp.obj" \
	"$(INTDIR)\hduhandler.obj" \
	"$(INTDIR)\mcuboardmgr.obj" \
	"$(INTDIR)\mcuinstdef.obj" \
	"$(INTDIR)\mediatranseqp.obj" \
	"$(INTDIR)\mpceqp.obj" \
	"$(INTDIR)\mpu2tpeqp.obj" \
	"$(INTDIR)\netbufeqp.obj" \
	"$(INTDIR)\umseqp.obj" \
	"$(INTDIR)\vmpeqp.obj"

"..\..\..\10-common\lib\release\win32\umseqp.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "umseqp - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "..\..\..\10-common\lib\debug\win32\umseqp.lib"


CLEAN :
	-@erase "$(INTDIR)\adaptereqp.obj"
	-@erase "$(INTDIR)\audbaseqp.obj"
	-@erase "$(INTDIR)\audbashandler.obj"
	-@erase "$(INTDIR)\audiomixeqp.obj"
	-@erase "$(INTDIR)\audmixhandler.obj"
	-@erase "$(INTDIR)\baseqp.obj"
	-@erase "$(INTDIR)\eqpinst.obj"
	-@erase "$(INTDIR)\eqpinterface.obj"
	-@erase "$(INTDIR)\eqpmgr.obj"
	-@erase "$(INTDIR)\hdueqp.obj"
	-@erase "$(INTDIR)\hduhandler.obj"
	-@erase "$(INTDIR)\mcuboardmgr.obj"
	-@erase "$(INTDIR)\mcuinstdef.obj"
	-@erase "$(INTDIR)\mediatranseqp.obj"
	-@erase "$(INTDIR)\mpceqp.obj"
	-@erase "$(INTDIR)\mpu2tpeqp.obj"
	-@erase "$(INTDIR)\netbufeqp.obj"
	-@erase "$(INTDIR)\umseqp.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\vmpeqp.obj"
	-@erase "..\..\..\10-common\lib\debug\win32\umseqp.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\..\common\tp" /I "..\..\..\10-common\include\protocol" /I "..\..\..\10-common\include\platform\\" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-common\include\tp" /I "..\..\..\10-Common\include\protocol\tp" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "_AFXDLL" /Fp"$(INTDIR)\umseqp.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\umseqp.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"..\..\..\10-common\lib\debug\win32\umseqp.lib" 
LIB32_OBJS= \
	"$(INTDIR)\adaptereqp.obj" \
	"$(INTDIR)\audbaseqp.obj" \
	"$(INTDIR)\audbashandler.obj" \
	"$(INTDIR)\audiomixeqp.obj" \
	"$(INTDIR)\audmixhandler.obj" \
	"$(INTDIR)\baseqp.obj" \
	"$(INTDIR)\eqpinst.obj" \
	"$(INTDIR)\eqpinterface.obj" \
	"$(INTDIR)\eqpmgr.obj" \
	"$(INTDIR)\hdueqp.obj" \
	"$(INTDIR)\hduhandler.obj" \
	"$(INTDIR)\mcuboardmgr.obj" \
	"$(INTDIR)\mcuinstdef.obj" \
	"$(INTDIR)\mediatranseqp.obj" \
	"$(INTDIR)\mpceqp.obj" \
	"$(INTDIR)\mpu2tpeqp.obj" \
	"$(INTDIR)\netbufeqp.obj" \
	"$(INTDIR)\umseqp.obj" \
	"$(INTDIR)\vmpeqp.obj"

"..\..\..\10-common\lib\debug\win32\umseqp.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("umseqp.dep")
!INCLUDE "umseqp.dep"
!ELSE 
!MESSAGE Warning: cannot find "umseqp.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "umseqp - Win32 Release" || "$(CFG)" == "umseqp - Win32 Debug"
SOURCE=..\source\adaptereqp.cpp

"$(INTDIR)\adaptereqp.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\audbaseqp.cpp

"$(INTDIR)\audbaseqp.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\audbashandler.cpp

"$(INTDIR)\audbashandler.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\audiomixeqp.cpp

"$(INTDIR)\audiomixeqp.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\audmixhandler.cpp

"$(INTDIR)\audmixhandler.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\baseqp.cpp

"$(INTDIR)\baseqp.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\eqpinst.cpp

"$(INTDIR)\eqpinst.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\eqpinterface.cpp

"$(INTDIR)\eqpinterface.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\eqpmgr.cpp

"$(INTDIR)\eqpmgr.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\hdueqp.cpp

"$(INTDIR)\hdueqp.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\hduhandler.cpp

"$(INTDIR)\hduhandler.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\mcuboardmgr.cpp

"$(INTDIR)\mcuboardmgr.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\mcuinstdef.cpp

"$(INTDIR)\mcuinstdef.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\mediatranseqp.cpp

"$(INTDIR)\mediatranseqp.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\mpceqp.cpp

"$(INTDIR)\mpceqp.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\mpu2tpeqp.cpp

"$(INTDIR)\mpu2tpeqp.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\netbufeqp.cpp

"$(INTDIR)\netbufeqp.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\umseqp.cpp

"$(INTDIR)\umseqp.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\vmpeqp.cpp

"$(INTDIR)\vmpeqp.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

