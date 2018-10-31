@rem =============win32 version====================

REM cd  prjwin32

REM If  /I  "%1" NEQ "noclean"  ( del /F /Q Debug\*.* )
REM If  /I  "%1" NEQ "noclean"  ( del /F /Q Release\*.* )

REM echo ======umsboard win32 debug version======  
REM nmake /NOLOGO /A /B /f umsboard.mak CFG="umsboard - Win32 Debug" /x nmakeError.log > ..\..\..\10-common\version\CompileInfo\umsboard_win_d.txt

REM echo ======umsboard win32 release version====== 
REM nmake /NOLOGO /A /B /f umsboard.mak CFG="umsboard - Win32 Release" /x nmakeError.log > ..\..\..\10-common\version\CompileInfo\umsboard_win_r.txt


REM cd ..\

REM echo on

echo off 
echo =============Compile umsboard win32_2010 Begin====================
cd prjvs2010
call compile.bat
cd ..

echo =============Compile umsboard win32_2010 End====================
echo on
