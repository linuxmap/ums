setlocal

@rem =============win32 version====================

call "%VS100COMNTOOLS%\vsvars32.bat"


if /I "%1" == "noclean" (

devenv log4cplusclientdll.vcxproj /ReBuild "Debug" /Out ..\..\..\10-common\version\compileinfo\log4cplusclientdll_win32_vs201x_dll_d.txt
devenv log4cplusclientdll.vcxproj /ReBuild "Release" /Out ..\..\..\10-common\version\compileinfo\log4cplusclientdll_win32_vs201x_dll_r.txt

) else (

del /F /Q Debug\*.*
del /F /Q Release\*.*

devenv log4cplusclientdll.vcxproj /ReBuild "Debug" /Out ..\..\..\10-common\version\compileinfo\log4cplusclientdll_win32_vs201x_dll_d.txt
devenv log4cplusclientdll.vcxproj /ReBuild "Release" /Out ..\..\..\10-common\version\compileinfo\log4cplusclientdll_win32_vs201x_dll_r.txt
)


endlocal