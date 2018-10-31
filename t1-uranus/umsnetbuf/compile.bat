echo off 
REM echo =============Compile umsnetbuf Begin====================

REM cd prjwin32
REM call compile.bat

REM copy /Y Debug\umsnetbuf.exe ..\..\..\10-common\version\debug\win32\umsnetbuf.exe
REM copy /Y Release\umsnetbuf.exe ..\..\..\10-common\version\release\win32\umsnetbuf.exe

REM cd ..

REM echo =============Compile umsnetbuf End====================
REM echo on

REM echo off 
echo =============Compile umsnetbuf win32_2010 Begin====================
cd prjvs2010
call compile.bat

copy /Y Debug\umsnetbuf.exe ..\..\..\10-common\version\debug\win32_2010\umsnetbuf.exe
copy /Y Release\umsnetbuf.exe ..\..\..\10-common\version\release\win32_2010\umsnetbuf.exe

cd ..

echo =============Compile umsnetbuf win32_2010 End====================
echo on