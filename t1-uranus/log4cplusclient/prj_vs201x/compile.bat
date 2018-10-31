setlocal

@rem =============win32 version====================

call "%VS100COMNTOOLS%\vsvars32.bat"


if /I "%1" == "noclean" (

devenv log4cplusclient.vcxproj /ReBuild "Debug" /Out ..\..\..\10-common\version\compileinfo\log4cplusclient_win32_vs201x_lib_d.txt
devenv log4cplusclient.vcxproj /ReBuild "Release" /Out ..\..\..\10-common\version\compileinfo\log4cplusclient_win32_vs201x_lib_r.txt

) else (

del /F /Q Debug\*.*
del /F /Q Release\*.*

devenv log4cplusclient.vcxproj /ReBuild "Debug" /Out ..\..\..\10-common\version\compileinfo\log4cplusclient_win32_vs201x_lib_d.txt
devenv log4cplusclient.vcxproj /ReBuild "Release" /Out ..\..\..\10-common\version\compileinfo\log4cplusclient_win32_vs201x_lib_r.txt
)


endlocal