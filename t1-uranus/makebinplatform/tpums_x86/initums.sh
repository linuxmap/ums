#!/bin/sh

#echo sh_name=$0
#echo param_num=$#

[ -d /usr/log ] || mkdir /usr/log
initumslog="/usr/log/initums.log"

#error exit
function exitfun()
{
	date >> $initumslog
	echo $1 >> $initumslog
	echo "tmm initums Error !" >> $initumslog
	exit 1
}

#define ums work path
ums_path="/tp"
#check ums_path
[ -d $ums_path ] || exitfun "$ums_path is not exist !"
#change ums_path to work path
old_dir=$(pwd)
echo $old_dir
cd $ums_path

#check startums.sh
[ -x $ums_path/startums.sh ] || exitfun "$ums_path/startums.sh is not executable !"
#startums
$ums_path/startums.sh "initums" &
echo "startums when power on OK !"

#back to old_path
cd $old_dir

exit 0
