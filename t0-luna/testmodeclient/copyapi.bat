@rem =============win32 version====================

del /q .\common\lib\debug\win32_2010\tptestapi.lib
del /q .\common\lib\debug\win32_2010\tptestapi.dll

del /q .\common\lib\release\win32_2010\tptestapi.lib
del /q .\common\lib\release\win32_2010\tptestapi.dll

copy /y ..\..\10-common\lib\debug\win32_2010\tptestapi.lib .\common\lib\debug\win32_2010\tptestapi.lib
copy /y ..\..\10-common\lib\debug\win32_2010\tptestapi.dll .\common\lib\debug\win32_2010\tptestapi.dll
copy /y ..\..\10-common\lib\release\win32_2010\tptestapi.lib .\common\lib\release\win32_2010\tptestapi.lib
copy /y ..\..\10-common\lib\release\win32_2010\tptestapi.dll .\common\lib\release\win32_2010\tptestapi.dll

del /q .\common\include\kdvtype.h
del /q .\common\include\osp.h
del /q .\common\include\tptestapi.h

copy /y ..\..\10-common\include\system1\kdvtype.h .\common\include\kdvtype.h
copy /y ..\..\10-common\include\platform\osp.h .\common\include\osp.h
copy /y ..\..\10-common\include\tp\tptestapi.h .\common\include\tptestapi.h
