#!/bin/sh

# 参数定义

cur_path=/usr/bin
umc_path=/usr

if [ -f ${cur_path}/kdvlog.ini ]
then
if [ -d ${cur_path}/../kdvlog/conf ]
then
rm -rf ${cur_path}/../kdvlog/conf
fi
mkdir ${cur_path}/../kdvlog/conf
mv ${cur_path}/kdvlog.ini ${cur_path}/../kdvlog/conf/
fi


if [ -f ${cur_path}/sbin-mpc2.tar.gz ]
then
rm -rf ${cur_path}/../sbin-mpc2.tar.gz
rm -rf ${cur_path}/../sbin/
mv ${cur_path}/sbin-mpc2.tar.gz  ${cur_path}/../
tar -zxvf ${cur_path}/../sbin-mpc2.tar.gz  -C ${cur_path}/../
rm -rf ${cur_path}/../sbin-mpc2.tar.gz
fi

#cp ntp.conf 
if [ -f /usr/bin/ntp.conf ]
then
mv  -f /usr/bin/ntp.conf /usr/conf/ntp.conf
fi

/usr/bin/kdvlogserver &
sleep 1

#stl 动态库拷贝到lib下
mv /usr/bin/libstdc++.so.5 /usr/lib/
/usr/bin/umsserver &
sleep 1

# 解压webclient 放到/usr目录下
if [ -f ${cur_path}/umcwebclient.tar ]
then
if [ -d ${umc_path}/umcwebclient ]
then
rm -rf ${umc_path}/umcwebclient 
fi
tar xf ${cur_path}/umcwebclient.tar -C ${umc_path}/
rm -rf ${cur_path}/umcwebclient.tar
fi

# 解压apache
if [ -f ${cur_path}/apache.tar ]
then
tar xf ${cur_path}/apache.tar -C ${cur_path}/
# 将lib库拷贝到/usr/lib下
mkdir ${cur_path}/../lib
cp ${cur_path}/apache/lib/* ${cur_path}/../lib/
rm -f ${cur_path}/apache.tar
fi

# 将apache配置文件拷贝到 apache下
if [ -f ${cur_path}/httpd.conf ]
then
cp ${cur_path}/httpd.conf ${cur_path}/apache/conf/
rm -rf ${cur_path}/httpd.conf
fi

# 将umcwebserver.fcgi 放到 cgi下
if [ -f ${cur_path}/umcwebserver.fcgi ]
then
cp ${cur_path}/umcwebserver.fcgi ${cur_path}/apache/cgi-bin/
rm -rf ${cur_path}/umcwebserver.fcgi
fi

# 启动前删除logs下的pid文件，避免启动失败
rm -rf ${cur_path}/apache/logs/*.pid
chmod -R 777 ${cur_path}/apache
#启动apache
${cur_path}/apache/bin/apachectl start
