
echo ========win32 version========

If  /I  "%1" NEQ "noclean"  ( del /F /Q Debug\*.* )
If  /I  "%1" NEQ "noclean"  ( del /F /Q Release\*.* )

echo ======umsnetbuf win32 debug version======
nmake /NOLOGO /A /B /f umsnetbuf.mak CFG="umsnetbuf - Win32 Debug" /x "nmakeError_d.log" > nmake_d.log
copy nmake_d.log/a + nmakeError_d.log/a "..\..\..\10-common\version\compileInfo\umsnetbuf_win_d.txt" 
del  nmake_d.log
del  nmakeError_d.log

echo ======umsnetbuf win32 release version====
nmake /NOLOGO /A /B /f umsnetbuf.mak CFG="umsnetbuf - Win32 Release"  /x "nmakeError_r.log" > nmake_r.log
copy nmake_r.log/a + nmakeError_r.log/a "..\..\..\10-common\version\compileInfo\umsnetbuf_win_r.txt" 
del  nmake_r.log
del  nmakeError_r.log
