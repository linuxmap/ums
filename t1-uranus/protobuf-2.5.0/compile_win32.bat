echo off 
echo =============Compile protobuf-2.5.0 vs201x Begin====================
cd prj_vs201x
call compile.bat
cd ..

echo =============Compile protobuf-2.5.0 vs201x End====================
echo on

echo off 
echo =============Compile protobuf-2.5.0 vs201xdll Begin====================
cd prj_vs201xdll
call compile.bat
cd ..

echo =============Compile protobuf-2.5.0 vs201xdll End====================
echo on
