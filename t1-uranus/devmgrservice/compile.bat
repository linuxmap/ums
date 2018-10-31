echo off 

echo =============Compile devmgrservice win32_2010 Begin====================
cd prjvs2010
call compile.bat

copy /Y Debug\devmgrservice.exe ..\..\..\10-common\version\debug\win32_2010\devmgrservice.exe
copy /Y Release\devmgrservice.exe ..\..\..\10-common\version\release\win32_2010\devmgrservice.exe

cd ..

echo =============Compile devmgrservice win32_2010 End====================
echo on