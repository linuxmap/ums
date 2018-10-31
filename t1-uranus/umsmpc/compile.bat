echo off 
echo =============Compile umsmpc Begin====================
cd prjwin32
call compile.bat

copy /Y Debug\umsmpc.exe ..\..\..\10-common\version\debug\win32\umsmpc.exe
copy /Y Release\umsmpc.exe ..\..\..\10-common\version\release\win32\umsmpc.exe

cd ..

echo =============Compile umsmpc End====================
echo on

echo off 
echo =============Compile umsmpc win32_2010 Begin====================
cd prjvs2010
call compile.bat

copy /Y Debug\umsmpc.exe ..\..\..\10-common\version\debug\win32_2010\umsmpc.exe
copy /Y Release\umsmpc.exe ..\..\..\10-common\version\release\win32_2010\umsmpc.exe

cd ..

echo =============Compile umsmpc win32_2010 End====================
echo on