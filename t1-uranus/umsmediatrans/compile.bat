echo off 
echo =============Compile umsmediatrans win32_2010 Begin====================
cd prjvs2010
call compile.bat

copy /Y Debug\umsmediatrans.exe ..\..\..\10-common\version\debug\win32_2010\umsmediatrans.exe
copy /Y Release\umsmediatrans.exe ..\..\..\10-common\version\release\win32_2010\umsmediatrans.exe

cd ..

echo =============Compile umsmediatrans win32_2010 End====================
echo on
