REM echo off 
REM echo =============Compile regserver Begin====================
REM cd prjwin32
REM call compile.bat
REM copy /Y Debug\regserver.exe ..\..\..\10-common\version\debug\win32\regserver.exe 
REM copy /Y Release\regserver.exe ..\..\..\10-common\version\release\win32\regserver.exe
REM cd ..
REM echo =============Compile regserver End====================
REM echo on

echo off 
echo =============Compile regserver win32_2010 Begin====================
cd prjvs2010
call compile.bat
copy /Y Debug\regserver.exe ..\..\..\10-common\version\debug\win32_2010\regserver.exe 
copy /Y Release\regserver.exe ..\..\..\10-common\version\release\win32_2010\regserver.exe
cd ..
echo =============Compile regserver win32_2010 End====================
echo on
