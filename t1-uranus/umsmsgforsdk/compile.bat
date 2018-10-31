echo off 
echo =============Compile umsmsg and tpmsg vs2010 Begin====================
cd ../umsmsg
call compile.bat

cd ../../t0-luna/tpmsgmgr
call compile.bat
cd ../../t1-uranus

echo =============Compile umsmsg and tpmsg vs2010 End====================
echo on
