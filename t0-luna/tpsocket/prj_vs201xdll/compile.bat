setlocal

@rem =============win32 version====================

call "%VS100COMNTOOLS%\vsvars32.bat"


if /I "%1" == "noclean" (

devenv tpsocketdll.vcxproj /ReBuild "Debug" /Out ..\..\..\10-common\version\compileinfo\tpsocketdll_win32_2010_dll_d.txt
devenv tpsocketdll.vcxproj /ReBuild "Release" /Out ..\..\..\10-common\version\compileinfo\tpsocketdll_win32_2010_dll_r.txt

) else (

del /F /Q Debug\*.*
del /F /Q Release\*.*

devenv tpsocketdll.vcxproj /ReBuild "Debug" /Out ..\..\..\10-common\version\compileinfo\tpsocketdll_win32_2010_dll_d.txt
devenv tpsocketdll.vcxproj /ReBuild "Release" /Out ..\..\..\10-common\version\compileinfo\tpsocketdll_win32_2010_dll_r.txt

)


endlocal