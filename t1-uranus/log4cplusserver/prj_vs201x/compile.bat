setlocal

@rem =============win32 version====================

call "%VS100COMNTOOLS%\vsvars32.bat"


if /I "%1" == "noclean" (

devenv log4cplusserver.vcxproj /ReBuild "Release" /Out ..\..\..\10-common\version\compileinfo\log4cplusserver_win32_vs201x_r.txt

) else (

del /F /Q Debug\*.*
del /F /Q Release\*.*

devenv log4cplusserver.vcxproj /ReBuild "Release" /Out ..\..\..\10-common\version\compileinfo\log4cplusserver_win32_vs201x_r.txt
)


endlocal