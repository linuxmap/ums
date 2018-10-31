#!/bin/sh
old_dir=$(pwd)
echo $old_dir
#log store in /usr/log path
[ -d /usr/log ] || mkdir /usr/log
cd /usr/log
export LD_LIBRARY_PATH=/tp/lib
/tp/log4cplusserver.linux "9999" "/tp/log4cplusserver.cfg" &
cd $old_dir
