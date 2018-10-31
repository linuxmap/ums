@rem =============win32 version====================

cd  prjwin32

If  /I  "%1" NEQ "noclean"  ( del /F /Q Debug\*.* )
If  /I  "%1" NEQ "noclean"  ( del /F /Q Release\*.* )

echo ======mpu2tp win32 debug version======  
nmake /NOLOGO /A /B /f mpu2.mak CFG="mpu2 - Win32 Debug" /x nmakeError.log > ..\..\..\10-common\version\CompileInfo\mpu2_win_d.txt

echo ======mpu2tp win32 release version====== 
nmake /NOLOGO /A /B /f mpu2.mak CFG="mpu2 - Win32 Release" /x nmakeError.log > ..\..\..\10-common\version\CompileInfo\mpu2_win_r.txt

copy /Y Debug\mpu2.exe ..\..\..\10-common\version\debug\win32\mpu2-tp.exe
copy /Y Release\mpu2.exe ..\..\..\10-common\version\release\win32\mpu2-tp.exe

cd ..\

echo on
