# Microsoft Developer Studio Generated NMAKE File, Based on tpmsgmgr.dsp
!IF "$(CFG)" == ""
CFG=tpmsgmgr - Win32 Debug
!MESSAGE No configuration specified. Defaulting to tpmsgmgr - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "tpmsgmgr - Win32 Release" && "$(CFG)" != "tpmsgmgr - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "tpmsgmgr.mak" CFG="tpmsgmgr - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "tpmsgmgr - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "tpmsgmgr - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "tpmsgmgr - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : "..\..\..\10-common\lib\release\win32\tpmsgmgr.lib"


CLEAN :
	-@erase "$(INTDIR)\msgmgr.obj"
	-@erase "$(INTDIR)\tphandle.obj"
	-@erase "$(INTDIR)\tplog.obj"
	-@erase "$(INTDIR)\tplogmgr.obj"
	-@erase "$(INTDIR)\tpmsg.obj"
	-@erase "$(INTDIR)\tpobject.obj"
	-@erase "$(INTDIR)\tptime.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "..\..\..\10-common\lib\release\win32\tpmsgmgr.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\include" /I "..\..\..\10-common\include\protocol" /I "..\..\..\10-common\include\platform\\" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-common\include\tp" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "_AFXDLL" /Fp"$(INTDIR)\tpmsgmgr.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\tpmsgmgr.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"..\..\..\10-common\lib\release\win32\tpmsgmgr.lib" 
LIB32_OBJS= \
	"$(INTDIR)\msgmgr.obj" \
	"$(INTDIR)\tphandle.obj" \
	"$(INTDIR)\tplog.obj" \
	"$(INTDIR)\tplogmgr.obj" \
	"$(INTDIR)\tpmsg.obj" \
	"$(INTDIR)\tpobject.obj" \
	"$(INTDIR)\tptime.obj"

"..\..\..\10-common\lib\release\win32\tpmsgmgr.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "tpmsgmgr - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "..\..\..\10-common\lib\debug\win32\tpmsgmgr.lib"


CLEAN :
	-@erase "$(INTDIR)\msgmgr.obj"
	-@erase "$(INTDIR)\tphandle.obj"
	-@erase "$(INTDIR)\tplog.obj"
	-@erase "$(INTDIR)\tplogmgr.obj"
	-@erase "$(INTDIR)\tpmsg.obj"
	-@erase "$(INTDIR)\tpobject.obj"
	-@erase "$(INTDIR)\tptime.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "..\..\..\10-common\lib\debug\win32\tpmsgmgr.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\include" /I "..\..\..\10-common\include\protocol" /I "..\..\..\10-common\include\platform\\" /I "..\..\..\10-common\include\system1" /I "..\..\..\10-common\include\tp" /I "..\..\common\include" /I "..\..\..\10-common\include\mt" /I "..\..\..\t2-jupiter\common\include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "_AFXDLL" /Fp"$(INTDIR)\tpmsgmgr.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\tpmsgmgr.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"..\..\..\10-common\lib\debug\win32\tpmsgmgr.lib" 
LIB32_OBJS= \
	"$(INTDIR)\msgmgr.obj" \
	"$(INTDIR)\tphandle.obj" \
	"$(INTDIR)\tplog.obj" \
	"$(INTDIR)\tplogmgr.obj" \
	"$(INTDIR)\tpmsg.obj" \
	"$(INTDIR)\tpobject.obj" \
	"$(INTDIR)\tptime.obj"

"..\..\..\10-common\lib\debug\win32\tpmsgmgr.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("tpmsgmgr.dep")
!INCLUDE "tpmsgmgr.dep"
!ELSE 
!MESSAGE Warning: cannot find "tpmsgmgr.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "tpmsgmgr - Win32 Release" || "$(CFG)" == "tpmsgmgr - Win32 Debug"
SOURCE=..\source\msgmgr.cpp

"$(INTDIR)\msgmgr.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\tphandle.cpp

"$(INTDIR)\tphandle.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\tplog.cpp

"$(INTDIR)\tplog.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\tplogmgr.cpp

"$(INTDIR)\tplogmgr.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\tpmsg.cpp

"$(INTDIR)\tpmsg.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\tpobject.cpp

"$(INTDIR)\tpobject.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\source\tptime.cpp

"$(INTDIR)\tptime.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

