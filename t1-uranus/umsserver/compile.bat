

echo off 
echo =============Compile umsserver win32_2010 Begin====================
cd prjvs2010
call compile.bat

copy /Y Debug\umsserver.exe ..\..\..\10-common\version\debug\win32_2010\umsserver.exe
copy /Y Release\umsserver.exe ..\..\..\10-common\version\release\win32_2010\umsserver.exe

cd ..

echo =============Compile umsserver win32_2010 End====================
echo on