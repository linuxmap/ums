rem echo off 
rem echo =============Compile umssipadapter Begin====================
rem cd prjwin32
rem call compile.bat

rem copy /Y Debug\umssipadapter.exe ..\..\..\10-common\version\debug\win32\umssipadapter.exe
rem copy /Y Release\umssipadapter.exe ..\..\..\10-common\version\release\win32\umssipadapter.exe

rem cd ..

rem echo =============Compile umssipadapter End====================
rem echo on


echo off 
echo =============Compile umssipadapter win32_2010 Begin====================
cd prjvs2010
call compile.bat

copy /Y Debug\umssipadapter.exe ..\..\..\10-common\version\debug\win32_2010\umssipadapter.exe
copy /Y Release\umssipadapter.exe ..\..\..\10-common\version\release\win32_2010\umssipadapter.exe

cd ..

echo =============Compile umssipadapter win32_2010 End====================
echo on