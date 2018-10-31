@echo off
pushd %~dp0

rem ����protocol buffer����������������c++ͷ�ļ���Դ�ļ������ƶ�����Ӧ·��
echo compiling c++...
mkdir tmp

protoc.win32 --cpp_out=./tmp pbmessage.proto
protoc.win32 --cpp_out=dllexport_decl=PROTOBUFMSG_API:./tmp enum.proto
protoc.win32 --cpp_out=dllexport_decl=PROTOBUFMSG_API:./tmp base.proto
protoc.win32 --cpp_out=dllexport_decl=PROTOBUFMSG_API:./tmp struct.proto

copy /Y .\tmp\pbmessage.pb.h ..\include\
copy /Y .\tmp\enum.pb.h ..\..\..\10-common\include\tp\protobufmsg\
copy /Y .\tmp\base.pb.h ..\..\..\10-common\include\tp\protobufmsg\
copy /Y .\tmp\struct.pb.h ..\..\..\10-common\include\tp\protobufmsg\

copy /Y .\tmp\pbmessage.pb.cc ..\source\
copy /Y .\tmp\enum.pb.cc ..\source\
copy /Y .\tmp\base.pb.cc ..\source\
copy /Y .\tmp\struct.pb.cc ..\source\

rd /s /q tmp

echo compiling c++ end!

popd

echo on