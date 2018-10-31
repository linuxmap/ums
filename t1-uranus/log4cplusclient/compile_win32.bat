echo off 
echo =============Compile log4cplusclient vs201x Begin====================
cd prj_vs201x
call compile.bat
cd ..

echo =============Compile log4cplusclient vs201x End====================
echo on

echo off 
echo =============Compile log4cplusclient vs201xdll Begin====================
cd prj_vs201xdll
call compile.bat
cd ..

echo =============Compile log4cplusclient vs201xdll End====================
echo on
