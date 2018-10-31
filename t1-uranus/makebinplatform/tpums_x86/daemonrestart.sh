#!/bin/sh

#echo sh_name=$0
#echo param_num=$#

#define ums work path
ums_path="/tp"

#check ums_path
[ -d $ums_path ] || exit 1

#check commonfunction.sh
[ -x $ums_path/commonfunction.sh ] || exit 1
. $ums_path/commonfunction.sh

#change ums_path to work path
old_dir=$(pwd)
echo $old_dir
cd $ums_path

#
#this is begin
#

sleep 5
echo "the daemonrestart.sh begin working..."

ums_moudle_name=$(getvalue_withkey $ums_path/ums_moudle.ini "ums_moudle_name")
ums_moudle_name=($ums_moudle_name)
length=${#ums_moudle_name[@]}
ums_moudle_check=0
checkfail=0
checknum=0

while true
do
	for((i=0;i<$length;i++));do
		process_check_name="$ums_path/${ums_moudle_name[$i]}"
		process_pid=$(check_process_alive $process_check_name)
		if [ "x$process_pid" != "x0" ];then
			ums_moudle_check[$i]=1
		else
			ums_moudle_check[$i]=0
			[ $checkfail -eq 0 ] && checkfail=1
		fi
	done
	
	[ $checkfail -eq 0 ] && sleep 3 && continue
	checkfail=0
	
	let checknum++ 
	[ $checknum -lt 2 ] && sleep 3 && continue
	checknum=0

	#install umslib_path
	export LD_LIBRARY_PATH="$ums_path/lib"
	
	[ -d /usr/log ] || mkdir /usr/log
	restartumslog="/usr/log/restartums.log"
	date >> $restartumslog	
	for((i=0;i<$length;i++));do
		process_start_name="$ums_path/${ums_moudle_name[$i]}"
		if [ ${ums_moudle_check[$i]} -eq 0 ];then
			start_process $process_start_name;
			echo "restart $process_start_name ret $? !" >> $restartumslog
			sleep 1;
		fi
	done
	
	break
done

############
#restart daemonrestart.sh
process_start_name="$ums_path/daemonrestart.sh"
start_process $process_start_name

#back to old_path
cd $old_dir

