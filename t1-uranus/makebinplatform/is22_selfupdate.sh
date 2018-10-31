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
if [ -f ${cur_path}/ntp.conf ]
then
mv  -f ${cur_path}/ntp.conf ${cur_path}/../conf/ntp.conf
fi

if [ -f ${cur_path}/is2.2-8548.tar.gz ]
then
rm -rf ${cur_path}/../is2.2-8548.tar.gz
rm -rf ${cur_path}/../sbin/
mv ${cur_path}/is2.2-8548.tar.gz  ${cur_path}/../
tar -zxvf ${cur_path}/../is2.2-8548.tar.gz  -C ${cur_path}/../
rm -rf ${cur_path}/../is2.2-8548.tar.gz
fi

/usr/bin/kdvlogserver &
sleep 1
/usr/bin/umsmediatrans &
sleep 1
/usr/bin/umssipadapter &
sleep 1
/usr/bin/umsnetbuf &
sleep 1
/usr/bin/is22_restartshell &
sleep 1
