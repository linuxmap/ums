#!/bin/sh

devmgrservicenum=$(ps | grep devmgrservice | grep -v grep | wc -l)
regservernum=$(ps | grep regserver | grep -v grep | wc -l)


echo "devmgrservicenum" is $devmgrservicenum
echo "regservernum" is $regservernum
