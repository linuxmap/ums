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
#begin stopums
#

############
#stop daemonrestart.sh
process_stop_txt="$ums_path/daemonrestart.sh"
check_and_kill_process $process_stop_txt


############
#stop ums all moudle
ums_moudle_name=$(getvalue_withkey $ums_path/ums_moudle.ini "ums_moudle_name")
ums_moudle_name=($ums_moudle_name)
length=${#ums_moudle_name[@]}

#stop the moudles by reverse
for((i=$length;i>0;i--));do
	process_stop_name="$ums_path/${ums_moudle_name[$i-1]}"
	check_and_kill_process $process_stop_name
done


#back to old_path
cd $old_dir

