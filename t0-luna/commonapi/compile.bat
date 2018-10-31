@rem =============win32 version====================

cd  prjwin32

If  /I  "%1" NEQ "noclean"  ( del /F /Q Debug\*.* )
If  /I  "%1" NEQ "noclean"  ( del /F /Q Release\*.* )

echo ======commonapi win32 debug version======  
nmake /NOLOGO /A /B /f commonapi.mak CFG="commonapi - Win32 Debug" /x nmakeError.log > ..\..\..\10-common\version\CompileInfo\commonapi_win_d.txt

echo ======commonapi win32 release version====== 
nmake /NOLOGO /A /B /f commonapi.mak CFG="commonapi - Win32 Release" /x nmakeError.log > ..\..\..\10-common\version\CompileInfo\commonapi_win_r.txt


cd ..\

echo on


echo off 
echo =============Compile commonapi win32_2010 Begin====================
cd prjvs2010
call compile.bat
cd ..

echo =============Compile commonapi win32_2010 End====================
echo on