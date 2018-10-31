#!/bin/sh

#echo sh_name=$0
#echo param_num=$#

#define log path
log_path="/usr/log"
dst_log_path="/usr/umcwebclient"

log_name="tpums.log"
log_name_1="tpums.log.1"
log_name_2="tpums.log.2"

log_modifyip="modifyip.log"
log_restartums="restartums.log"
log_initums="initums.log"

log_tar_name="umslog.tar.gz"

#error exit
function exitfun()
{
	echo $1
	echo "ERROR: downloadlog fail!"
	exit 1
}

#check log_path
[ -d $log_path ] || exitfun "$log_path is not exist !"
[ -d $dst_log_path ] || exitfun "$dst_log_path is not exist !"

[ -f $log_path/$log_name ] || log_name=""
[ -f $log_path/$log_name_1 ] || log_name_1=""
[ -f $log_path/$log_name_2 ] || log_name_2=""

[ -f $log_path/$log_modifyip ] || log_modifyip=""
[ -f $log_path/$log_restartums ] || log_restartums=""
[ -f $log_path/$log_initums ] || log_initums=""

if [ -z $log_name ] && [ -z $log_name_1 ] && [ -z $log_name_2 ];then
	exitfun "umslog is not exist !"
fi

echo "begin downloadlog!"
	
#change log_path to work path
old_dir=$(pwd)
echo $old_dir
cd $log_path

[ -f $log_path/$log_tar_name ] && rm -rf $log_path/$log_tar_name
[ -f $dst_log_path/$log_tar_name ] && rm -rf $dst_log_path/$log_tar_name

tar -zcf $log_tar_name $log_name $log_name_1 $log_name_2 $log_modifyip $log_restartums $log_initums
cp $log_path/$log_tar_name $dst_log_path/

chmod 555 $dst_log_path/$log_tar_name

#back to old_path
cd $old_dir

echo "end downloadlog!"

exit 0