#!/bin/sh

#echo sh_name=$0
#echo param_num=$#

#define start process fun
#param one "the process name including path"
#param two "the process param for starting"
start_process(){
	process_name=$1
	process_param=$2
	
	[ -z $process_name ] && return 1
	[ -x $process_name ] || return 1
	
	if [ -z $process_param ]
	then
		echo "start_process $process_name &"
		$process_name &
	else
		echo "start_process $process_name $process_param"
		$process_name $process_param
	fi
	return 0
}

#define kill process fun
#param one "the process pid"
kill_process(){
	kill_process_pid=$1

	[ -z $kill_process_pid ] && return 1
	[ "x$kill_process_pid" == "x0" ] && return 1

	kill -9 $kill_process_pid
	echo "kill $2 $kill_process_pid ok!"
	return 0
}

#define check process alive fun
#param one "the process name including path"
#return valule is the pid of the alive process
#NOTICE
#you should not add other output in this function
check_process_alive(){
	process_name=$1
	process_num=0
	process_pid=0
	
	[ -z $process_name ] && echo $process_pid && return 1
	
	process_num=$(ps -ef | grep $process_name | grep -v grep | wc -l)
	if [ "x$process_num" == "x0" ]
	then
		echo $process_pid;return 1
	fi
	process_pid=$(ps -ef | grep $process_name | grep -v grep | sed -n '1'p | sed -re 's/[^0-9]*([0-9]*).*$/\1/;')
	echo $process_pid;return 0
}

#define check and kill process fun
#param one "the process name including path"
check_and_kill_process(){
	process_txt=$1
	
	[ -z $process_txt ] && return 1
	
	process_pid=$(check_process_alive $process_txt)
	while [ "x$process_pid" != "x0" ]
	do
		kill_process "$process_pid" "$process_txt"
		process_pid=$(check_process_alive $process_txt)
	done
	return 0
}

#get value with key from config file
#param one filename
#param two key
#return value
function getvalue_withkey()
{
	key=$2
	cat $1 | while read line
	do
		need_ignore=$(echo "$line" | awk 'BEGIN{ret=0} /^#/{ret=1} /^$/{ret=1} END{print ret}')
		if [ $need_ignore -eq 1 ];then
			continue
		fi
		field=$(echo "$line" | awk -F= '{gsub(" |\t","",$1); print $1}')
		value=$(echo "$line" | awk 'gsub(/^ *| *$/,"",$0)' | awk -F= '{gsub("\t","",$2); print $2}')
		if [ "x$key" == "x$field" ];then	
			echo "$value"
			break
		fi	
	done
}

#check input ip is or not valid
#param one the input ip
#return 0 inputip is valid
#return 1 inputip is not valid
function checkinputip()
{
	inputip=$1
	inputip=`echo $inputip | grep -E "^([0-9]{1,3})\.([0-9]{1,3})\.([0-9]{1,3})\.([0-9]{1,3})$"`
	[ -z $inputip ] && return 1
	
	a=`echo $inputip|awk -F . '{print $1}'`
	b=`echo $inputip|awk -F . '{print $2}'`
	c=`echo $inputip|awk -F . '{print $3}'`
	d=`echo $inputip|awk -F . '{print $4}'`
	#echo $a $b $c $d

	for num in $a $b $c $d
	do
		if [ $num -gt 255 ] || [ $num -lt 0 ]    #每个数值必须在0-255之间
		then
			return 1
		fi
	done
	return 0
}

#modify ntp server ip in ntp.conf
#param one ntp.conf path
#param two ntp server ip
#return 0 modify ok, you should restart ntpd
#return 1 modify not ok, you should not restart ntpd
function modifyntpserverip()
{
	ntpconf=$1
	serverip=$2
	ntpconf_bk=""$1""_bk""
	ntpconf_modifyflag=""$1""_modifyflag""
	
	[ -w $ntpconf ] || return 1
	#check serverip
	checkinputip $serverip
	res=$?
	[ $res -eq 0 ] || return 1 
	
	[ "x0.0.0.0" == "x$serverip" ] && serverip="127.0.0.1"
	
	#creat ntpconf_bk
	[ -f $ntpconf_bk ] && rm -rf $ntpconf_bk
	touch $ntpconf_bk
	[ -f $ntpconf_modifyflag ] && rm -rf $ntpconf_modifyflag
	
	key="server"
	cat $1 | while read line
	do
		need_ignore=$(echo "$line" | awk 'BEGIN{ret=0} /^#/{ret=1} END{print ret}')
		if [ $need_ignore -eq 1 ];then
			echo $line >> $ntpconf_bk
			continue
		fi
		field=$(echo "$line" | awk '{print $1}')
		value=$(echo "$line" | awk '{print $2}')		
		if [ "x$key" == "x$field" ] && [ "x127.127.1.0" != "x$value" ] && [ "x$serverip" != "x$value" ];then
			touch $ntpconf_modifyflag
			echo "before line=$line"
			line=$(echo "$line" | awk '{gsub($2,"'$serverip'",$0); print $0}')
			echo "after line=$line"
		fi
		echo $line >> $ntpconf_bk
	done
	
	returnvalue=1
	if [ -f $ntpconf_modifyflag ];then
		#del old ntpconf
		rm -rf $ntpconf
		#rename
		mv -f $ntpconf_bk $ntpconf
		rm -rf $ntpconf_modifyflag
		returnvalue=0
	else
		rm -rf $ntpconf_bk
		returnvalue=1
	fi
	
#	echo "modifyntpserverip returnvalue=$returnvalue"
	return $returnvalue
}

#check and start keepalived app, then sleep 20 seconds
function checkandstartkeepalived()
{
	keepalivedpid=$(check_process_alive "keepalived")
	if [ "x$keepalivedpid" == "x0" ];then
#		echo "hello keepalived"
		service keepalived start
	fi
#	echo "keepalivedpid $keepalivedpid"
	sleep 20
}

