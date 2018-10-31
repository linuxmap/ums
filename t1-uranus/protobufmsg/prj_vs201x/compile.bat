setlocal

@rem =============win32 version====================

call "%VS100COMNTOOLS%\vsvars32.bat"


if /I "%1" == "noclean" (

devenv protobufmsg.vcxproj /ReBuild "Release" /Out ..\..\..\10-common\version\compileinfo\protobufmsg_win32_vs201x_lib_r.txt

) else (

del /F /Q Release\*.*

devenv protobufmsg.vcxproj /ReBuild "Release" /Out ..\..\..\10-common\version\compileinfo\protobufmsg_win32_vs201x_lib_r.txt
)


endlocal