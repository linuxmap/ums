#!/bin/sh

#echo sh_name=$0
#echo param_num=$#

redisclient="redis-cli"
redisip="127.0.0.1"
redisport=7379
password="KedaRedis16"


key=$1

echo "param 1 is key"
echo "key=$key"

#error exit
function exitfun()
{
	echo $1
	exit 1
}

which $redisclient
ret=$?
if [ "x$ret" != "x0" ]
then
	exitfun "$redisclient is not exist !"
fi

if [ -z $key ];then
	echo "key is null, show all key"
	$redisclient -h $redisip -p $redisport -a $password keys "*"
else
	echo "the value of $key is"
	$redisclient -h $redisip -p $redisport -a $password get "$key"
fi

