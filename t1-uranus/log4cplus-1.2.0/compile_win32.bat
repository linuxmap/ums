echo off 
echo =============Compile log4cplus-1.2.0 vs201x Begin====================
cd prj_vs201x
call compile.bat
cd ..

echo =============Compile log4cplus-1.2.0 vs201x End====================
echo on

echo off 
echo =============Compile log4cplus-1.2.0 vs201xdll Begin====================
cd prj_vs201xdll
call compile.bat
cd ..

echo =============Compile log4cplus-1.2.0 vs201xdll End====================
echo on
