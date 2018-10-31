echo off 
echo =============Compile protobufmsg vs201x Begin====================
cd prj_vs201x
call compile.bat
cd ..

echo =============Compile protobufmsg vs201x End====================
echo on

echo off 
echo =============Compile protobufmsg vs201xdll Begin====================
cd prj_vs201xdll
call compile.bat
cd ..

echo =============Compile protobufmsg vs201xdll End====================
echo on
