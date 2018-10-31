setlocal

@rem =============win32 version====================

call "%VS100COMNTOOLS%\vsvars32.bat"


if /I "%1" == "noclean" (

devenv protobuf.vcxproj /ReBuild "Release" /Out ..\..\..\10-common\version\compileinfo\protobuf_win32_vs201x_lib_r.txt

) else (

del /F /Q Release\*.*

devenv protobuf.vcxproj /ReBuild "Release" /Out ..\..\..\10-common\version\compileinfo\protobuf_win32_vs201x_lib_r.txt
)


endlocal