setlocal

@rem =============win32 version====================

call "%VS100COMNTOOLS%\vsvars32.bat"


if /I "%1" == "noclean" (

devenv umscall.vcxproj /ReBuild "Debug" /Out ..\..\..\10-common\version\compileinfo\umscall_win32_debug_2010.txt
devenv umscall.vcxproj /ReBuild "Release" /Out ..\..\..\10-common\version\compileinfo\umscall_win32_release_2010.txt

) else (

del /F /Q Debug\*.*
del /F /Q Release\*.*

devenv umscall.vcxproj /ReBuild "Debug" /Out ..\..\..\10-common\version\compileinfo\umscall_win32_debug_2010.txt
devenv umscall.vcxproj /ReBuild "Release" /Out ..\..\..\10-common\version\compileinfo\umscall_win32_release_2010.txt
)


endlocal