setlocal

@rem =============win32 version====================

call "%VS100COMNTOOLS%\vsvars32.bat"


if /I "%1" == "noclean" (

devenv tpmsgmgr.vcxproj /ReBuild "Debug" /Out ..\..\..\10-common\version\compileinfo\tpmsgmgr_win32_debug_2010.txt
devenv tpmsgmgr.vcxproj /ReBuild "Release" /Out ..\..\..\10-common\version\compileinfo\tpmsgmgr_win32_release_2010.txt

) else (

del /F /Q Debug\*.*
del /F /Q Release\*.*

devenv tpmsgmgr.vcxproj /ReBuild "Debug" /Out ..\..\..\10-common\version\compileinfo\tpmsgmgr_win32_debug_2010.txt
devenv tpmsgmgr.vcxproj /ReBuild "Release" /Out ..\..\..\10-common\version\compileinfo\tpmsgmgr_win32_release_2010.txt
)


endlocal