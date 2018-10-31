setlocal

@rem =============win32 version====================

call "%VS100COMNTOOLS%\vsvars32.bat"


if /I "%1" == "noclean" (

devenv tpsocket.vcxproj /ReBuild "Debug" /Out ..\..\..\10-common\version\compileinfo\tpsocket_win32_2010_lib_d.txt
devenv tpsocket.vcxproj /ReBuild "Release" /Out ..\..\..\10-common\version\compileinfo\tpsocket_win32_2010_lib_r.txt

) else (

del /F /Q Debug\*.*
del /F /Q Release\*.*

devenv tpsocket.vcxproj /ReBuild "Debug" /Out ..\..\..\10-common\version\compileinfo\tpsocket_win32_2010_lib_d.txt
devenv tpsocket.vcxproj /ReBuild "Release" /Out ..\..\..\10-common\version\compileinfo\tpsocket_win32_2010_lib_r.txt

)


endlocal