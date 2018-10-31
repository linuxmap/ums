#!/bin/sh

#param one is ntp ip

#check ntpd
which ntpd
res=$?
[ $res -eq 0 ] || exit 1

#check ntpconf
ntpconf="/etc/ntp.conf"
[ -w $ntpconf ] || exit 1

#check param one
[ -z $1 ] && exit 1

#check commonfunction.sh
[ -x /tp/commonfunction.sh ] || exit 1
. /tp/commonfunction.sh

#modify ntp server ip
modifyntpserverip $ntpconf $1
res=$?
echo "modifyntpserverip res=$res"

#restart ntp
[ $res -eq 0 ] && service ntpd restart

exit 0
