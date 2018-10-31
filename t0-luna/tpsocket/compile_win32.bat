echo off 
echo =============Compile unifysocket vs201x Begin====================
cd prj_vs201x
call compile.bat
cd ..
echo =============Compile unifysocket vs201x End====================

echo =============Compile unifysocket vs201xdll Begin====================
cd prj_vs201xdll
call compile.bat
cd ..
echo =============Compile unifysocket vs201xdll End====================
echo on