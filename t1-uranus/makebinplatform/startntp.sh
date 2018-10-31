#!/bin/sh

#kill ntpd
ntpdnum=$(ps | grep ntpd | grep -v grep | wc -l)
if [ $ntpdnum -gt 0 ]
then
	ntpdid=$(ps | grep ntpd | grep -v grep | sed -n '1'p | sed -re 's/[^0-9]*([0-9]*).*$/\1/;' )
	echo "kill ntpd"
	kill -9 $ntpdid
fi

# get mpc ip from $1 
echo " input server ip is $1"

ipmatch='^([0-9]{1,2}|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\.([0-9]{1,2}|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\.([0-9]{1,2}|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\.([0-9]{1,2}|1[0-9][0-9]|2[0-4][0-9]|25[0-5])$'
serverip=$(echo "$1" | grep -E $ipmatch)

if [  -z $serverip ]
then
	serverip=127.0.0.1
	echo "input server ip error, set serverip : $serverip"
else
	echo "serverip is $serverip"
fi

echo "restrict -4 default kod notrap nomodify nopeer noquery
restrict -6 default kod notrap nomodify nopeer noquery" >/usr/conf/ntp.conf
if [ $serverip = 0.0.0.0 ]
then
	echo ""
elif [ $serverip = 127.0.0.1 ]
then
	echo ""
elif [ $serverip = 127.127.1.0 ]
then
	echo ""
else
	echo "server $serverip offset" >> /usr/conf/ntp.conf
	
	# start ntpdate
	echo "start ntpdate ...."
	/usr/bin/ntpdate $serverip &
fi

echo "server 127.127.1.0" >> /usr/conf/ntp.conf
echo "fudge 127.127.1.0 stratum 0" >> /usr/conf/ntp.conf
echo "restrict 127.0.0.1" >> /usr/conf/ntp.conf
echo "restrict ::1" >> /usr/conf/ntp.conf

if [ ! -f '/usr/conf/ntp.conf' ]
then
	touch /usr/conf/ntp.conf
	echo "create /usr/conf/ntp.conf"
fi

ntpdatenum=$(ps | grep ntpdate | grep -v grep | wc -l)
ntpdatetime=0
while [ $ntpdatenum -gt  0 ]
do
	let ntpdatetime++
	echo "ntpdate is runing, timer is $ntpdatetime"
	if [ $ntpdatetime -gt 20 ]
	then
		ntpdateid=$(ps | grep ntpdate | grep -v grep | sed -n '1'p | sed -re 's/[^0-9]*([0-9]*).*$/\1/;' )
		kill -9 $ntpdateid
		echo "over time , kill ntpdate"
		ntpdatenum=$(ps | grep ntpdate | grep -v grep | wc -l) 
	fi
	sleep 1
	ntpdatenum=$(ps | grep ntpdate | grep -v grep | wc -l)
done
echo "ntpdate is end"

ntpdnum=$(ps | grep ntpd | grep -v grep | wc -l)
if [ $ntpdnum -gt 0 ]
then
	ntpdid=$(ps | grep ntpd | grep -v grep | sed -n '1'p | sed -re 's/[^0-9]*([0-9]*).*$/\1/;' )
	echo "kill ntpd"
	kill -9 $ntpdid
fi

echo "start ntpd .... "
/usr/bin/ntpd &
