call C:\CCStudio_v3.3\DosRun.bat

echo "===================== compiling lib [dm647] ================"

cd ..\..\..\driver-svn\platform\20-cbb\platform\dm647\driver

call compile.bat

cd ..\..\..\..\..\..\

rem del /F /Q .\10-common\lib\release\ti_d647\*.lib
copy /Y .\driver-svn\platform\10-common\lib\cbb\platform\release\dm647\*.lib .\10-common\lib\release\ti_d647\

cd .\10-common\build\scripts_plt
