cd ./prjwin32

echo ========win32 version========

If  /I  "%1" NEQ "noclean"  ( del /F /Q Debug\*.* )
If  /I  "%1" NEQ "noclean"  ( del /F /Q Release\*.* )

echo ======tpaddrmgr win32 debug version======
nmake /NOLOGO /A /B /f tpaddrmgr.mak CFG="tpaddrmgr - Win32 Debug"   /x "nmakeError_d.log" > nmake_d.log
copy nmake_d.log/a + nmakeError_d.log/a "..\..\..\10-common\version\compileInfo\tpaddrmgr_win_d.txt" 
del  nmake_d.log
del  nmakeError_d.log

echo ======tpaddrmgr win32 release version====
nmake /NOLOGO /A /B /f tpaddrmgr.mak CFG="tpaddrmgr - Win32 Release"   /x "nmakeError_r.log" > nmake_r.log
copy nmake_r.log/a + nmakeError_r.log/a "..\..\..\10-common\version\compileInfo\tpaddrmgr_win_r.txt" 
del  nmake_r.log
del  nmakeError_r.log

cd ..


echo off 
echo =============Compile tpaddrmgr win32_2010 Begin====================
cd prjvs2010
call compile.bat
cd ..

echo =============Compile tpaddrmgr win32_2010 End====================
echo on