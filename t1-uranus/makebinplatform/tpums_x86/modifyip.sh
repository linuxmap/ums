#!/bin/sh

#param one is old ip
#param tow is new ip

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

[ -d /usr/log ] || mkdir /usr/log
modifyiplog="/usr/log/modifyip.log"

oldip=$1
newip=$2

#error exit
function exitfun()
{
	date >> $modifyiplog
	echo "old ip is $oldip, new ip is $newip." >> $modifyiplog
	echo $1 >> $modifyiplog
	echo "ERROR: modifyip fail!" >> $modifyiplog
	exit 1
}

#error exit
function exitokfun()
{
	date >> $modifyiplog
	echo "old ip is $oldip, new ip is $newip." >> $modifyiplog
	echo "SUCCESS: modifyip OK!" >> $modifyiplog
	exit 1
}

checkinputip $oldip
res=$?
[ $res -eq 0 ] || exitfun "old ip $oldip is not valid!"
checkinputip $newip
res=$?
[ $res -eq 0 ] || exitfun "new ip $newip is not valid!"

#run platform script
# to do...

[ -x /opt/config/luban_config/netconfig.sh ] && /opt/config/luban_config/netconfig.sh $oldip $newip

ret=$?
if [ "x$ret" == "x0" ];then
	exitokfun
else
	exitfun "ERROR: netconfig.sh  execute failed !"
fi


