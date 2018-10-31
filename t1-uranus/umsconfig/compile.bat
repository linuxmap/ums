@rem =============win32 version====================

REM cd  PrjWin32

REM If  /I  "%1" NEQ "noclean"  ( del /F /Q Debug\*.* )
REM If  /I  "%1" NEQ "noclean"  ( del /F /Q Release\*.* )

REM echo ======umsconfig win32 debug version======  
REM nmake /NOLOGO /A /B /f umsconfig.mak CFG="umsconfig - Win32 Debug" /x nmakeError.log > ..\..\..\10-common\version\CompileInfo\umsconfig_win_d.txt

REM echo ======umsconfig win32 release version====== 
REM nmake /NOLOGO /A /B /f umsconfig.mak CFG="umsconfig - Win32 Release" /x nmakeError.log > ..\..\..\10-common\version\CompileInfo\umsconfig_win_r.txt


REM cd ..\

REM echo on

echo off 
echo =============Compile umsconfig win32_2010 Begin====================
cd prjvs2010
call compile.bat
cd ..

echo =============Compile umsconfig win32_2010 End====================
echo on