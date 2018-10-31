echo off 
echo =============Compile umsmediatransnew win32_2010 Begin====================
cd prjvs2010
call compile.bat

copy /Y Debug\umsmediatransnew.exe ..\..\..\10-common\version\debug\win32_2010\umsmediatransnew.exe
copy /Y Release\umsmediatransnew.exe ..\..\..\10-common\version\release\win32_2010\umsmediatransnew.exe

cd ..

echo =============Compile umsmediatransnew win32_2010 End====================
echo on
