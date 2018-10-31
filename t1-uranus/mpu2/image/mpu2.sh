#!/bin/sh
#set socket recv max buff size to 2M
echo 2097152 > /proc/sys/net/core/rmem_max
#set socket send max buff size to 2M
echo 2097152 > /proc/sys/net/core/wmem_max
cd /usr/bin/

cur_path=/usr/bin

if [ -f ${cur_path}/sbin-mpu2.tar.gz ]
then
rm -rf ${cur_path}/../sbin-mpu2.tar.gz
rm -rf ${cur_path}/../sbin/
mv ${cur_path}/sbin-mpu2.tar.gz  ${cur_path}/../
tar -zxvf ${cur_path}/../sbin-mpu2.tar.gz  -C ${cur_path}/../
rm -rf ${cur_path}/../sbin-mpu2.tar.gz
fi


./loadmodules_ti8168.sh
./logs &
./detectee &
