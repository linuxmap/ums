#!/bin/sh

# 参数定义

tar_path=/usr/bin
if [ -f ${tar_path}/sbin-cri2.tar.gz ]
then
rm -rf ${tar_path}/../sbin-cri2.tar.gz
rm -rf ${tar_path}/../sbin/
mv ${tar_path}/sbin-cri2.tar.gz  ${tar_path}/../
tar -zxvf ${tar_path}/../sbin-cri2.tar.gz  -C ${tar_path}/../
rm -rf ${tar_path}/../sbin-cri2.tar.gz
fi


if [ -f /usr/bin/ntp.conf ]
then
mv  -f /usr/bin/ntp.conf /usr/conf/ntp.conf
fi

/usr/bin/umsmediatrans &
sleep 1