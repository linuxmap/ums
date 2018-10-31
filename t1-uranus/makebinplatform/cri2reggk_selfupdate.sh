#!/bin/sh

# 参数定义

cur_path=/usr/bin

if [ -f ${cur_path}/kdvlog.ini ]
then
if [ -d ${cur_path}/../kdvlog/conf ]
then
rm -rf ${cur_path}/../kdvlog/conf
fi
mkdir ${cur_path}/../kdvlog/conf
mv ${cur_path}/kdvlog.ini ${cur_path}/../kdvlog/conf/
fi

tar_path=/usr/bin
if [ -f ${tar_path}/sbin-cri2.tar.gz ]
then
rm -rf ${tar_path}/../sbin-cri2.tar.gz
rm -rf ${tar_path}/../sbin/
mv ${tar_path}/sbin-cri2.tar.gz  ${tar_path}/../
tar -zxvf ${tar_path}/../sbin-cri2.tar.gz  -C ${tar_path}/../
rm -rf ${tar_path}/../sbin-cri2.tar.gz
fi


/usr/bin/kdvlogserver &
sleep 1
/usr/bin/kdvgk &
sleep 1
/usr/bin/regserver &
sleep 1
/usr/bin/devmgrservice &
sleep 1
/usr/bin/cri2reggk_restartshell &
sleep 1

