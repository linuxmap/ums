setlocal

@rem =============win32 version====================

call "%VS100COMNTOOLS%\vsvars32.bat"


if /I "%1" == "noclean" (

devenv umssipadapter.vcxproj /ReBuild "Debug" /Out ..\..\..\10-common\version\compileinfo\umssipadapter_win32_debug_2010.txt
devenv umssipadapter.vcxproj /ReBuild "Release" /Out ..\..\..\10-common\version\compileinfo\umssipadapter_win32_release_2010.txt

) else (

del /F /Q Debug\*.*
del /F /Q Release\*.*

devenv umssipadapter.vcxproj /ReBuild "Debug" /Out ..\..\..\10-common\version\compileinfo\umssipadapter_win32_debug_2010.txt
devenv umssipadapter.vcxproj /ReBuild "Release" /Out ..\..\..\10-common\version\compileinfo\umssipadapter_win32_release_2010.txt
)


endlocal