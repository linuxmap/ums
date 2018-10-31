#!/bin/sh

echo "input paramis $1"

if [ $1 = "off" ]
then
	echo "off...."
	/usr/sbin/iptables -D INPUT -p tcp --dport 23 -j DROP
	/usr/sbin/iptables -A INPUT -p tcp --dport 23 -j DROP
elif [ $1 = "on" ]
then
	echo "on ...."
	/usr/sbin/iptables -D INPUT -p tcp --dport 23 -j DROP
else
	echo "param is error!"
fi


