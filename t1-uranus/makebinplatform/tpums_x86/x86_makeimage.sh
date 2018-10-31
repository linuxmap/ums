#!/bin/sh

#echo sh_name=$0
#echo param_num=$#
curpath=`pwd`
echo $curpath

file1=./startums.sh
file2=./stopums.sh
file44=./initums.sh

file3=../../../10-common/version/release/linux/umsserver_log4cplus
file4=../../../10-common/version/release/linux/umssipadapter_log4cplus
file5=../../../10-common/version/release/linux/umsmediatrans
file6=../../../10-common/version/release/linux/umsnetbuf
file7=../../../10-common/version/release/linux/log4cplusserver.linux

file8=../httpd-2.4.25-8000h/apache.tar.gz
file9=../../../10-common/version/release/linux/umcwebserver/umcwebserver.fcgi
file48=../../../10-common/version/release/linux/umcwebserver/httpd.conf
file10=./umcwebclient.tar

file11=../../../10-common/lib/release/linux/libosp.so
file12=../../../10-common/lib/release/linux/libkprop.so
file13=../../../10-common/lib/release/linux/libtinyxml.so

file14=../../../10-common/lib/release/linux/libkdvsipmodule2.so
file15=../../../10-common/lib/release/linux/libbfcp.so
file16=../../../10-common/lib/release/linux/libkdv323adapter.so
file17=../../../10-common/lib/release/linux/libkdvsdp.so
file18=../../../10-common/lib/release/linux/libkdvprotocommon.so
file19=../../../10-common/lib/release/linux/libkdvsipadapter2.so
file20=../../../10-common/lib/release/linux/libkdvsipstack2.so
file21=../../../10-common/lib/release/linux/libkdvdatanet.so
file22=../../../10-common/lib/release/linux/liblog4cplusclientdll.so

file33=../../../10-common/lib/release/linux/libdataswitch.so
file34=../../../10-common/lib/release/linux/libkdcrypto.so
file35=../../../10-common/lib/release/linux/libkdssl.so
file36=../../../10-common/lib/release/linux/libkdvsrtp.so

file37=../../../10-common/lib/release/linux/libevent_core.so
file38=../../../10-common/lib/release/linux/libevent_extra.so
file39=../../../10-common/lib/release/linux/libjansson.so
file40=../../../10-common/lib/release/linux/librabbitmqwrap.so
file41=../../../10-common/lib/release/linux/libevent_pthreads.so
file42=../../../10-common/lib/release/linux/libmysqlclient.so
file43=../../../10-common/lib/release/linux/librabbitmq_r.so

file46=../../../10-common/lib/release/linux/libkdvencrypt.so
file47=../../../10-common/lib/release/linux/librockey2.so
file54=../../../10-common/lib/release/linux/libkdvlog.so

file23=../../log4cplusserver/startlogserver.sh
file24=../../log4cplusserver/log4cplusserver.cfg
file25=../../umsserver/umsserverlog4cplus.cfg
file26=../../umssipadapter/umssipadapterlog4cplus.cfg

file27=../../../10-common/version/release/linux/regserver
file28=../../../10-common/version/release/linux/devmgrservice

file45=../../../10-common/version/release/linux/kdvgk_redhat_4.2

file29=./commonfunction.sh
file30=./daemonrestart.sh
file31=./modifyntpserver.sh
file32=./ums_moudle.ini

file49=./redis_add.sh
file50=./redis_del.sh
file51=./redis_show.sh

file52=./modifyip.sh
file53=./downloadlog.sh

[ -d ./umcwebclient ] && rm -rf ./umcwebclient
[ -f ./umcwebclient.tar ] && rm -rf ./umcwebclient.tar

cp -fr ../../../10-common/version/release/linux/umcwebclient ./
tar -cf umcwebclient.tar ./umcwebclient

for file in $file1 $file2 $file3 $file4 $file5 $file6 $file7 $file8 $file9 $file10 $file11 $file12 $file13 $file14 $file15 $file16 $file17 $file18 $file19 $file20 $file21 $file22 $file23 $file24 $file25 $file26 $file27 $file28 $file29 $file30 $file31 $file32 $file33 $file34 $file35 $file36 $file37 $file38 $file39 $file40 $file41 $file42 $file43 $file44 $file45 $file46 $file47 $file48 $file49 $file50 $file51 $file52 $file53 $file54
do
	if [ ! -f $file ]
	then
		echo error : $file not exist
		rm -rf umcwebclient
		rm -rf umcwebclient.tar
		exit 1
	fi
done

[ -f ./tmm.bin ] && rm -rf ./tmm.bin
[ -f ./tp_temp.tar.gz ] && rm -rf ./tp_temp.tar.gz
[ -d ./tp_temp ] && rm -rf ./tp_temp

mkdir tp_temp

for file in $file1 $file2 $file3 $file4 $file5 $file6 $file7 $file8 $file9 $file10 $file11 $file12 $file13 $file14 $file15 $file16 $file17 $file18 $file19 $file20 $file21 $file22 $file23 $file24 $file25 $file26 $file27 $file28 $file29 $file30 $file31 $file32 $file33 $file34 $file35 $file36 $file37 $file38 $file39 $file40 $file41 $file42 $file43 $file44 $file45 $file46 $file47 $file48 $file49 $file50 $file51 $file52 $file53 $file54                
do
	cp -f $file ./tp_temp/
done


chmod -R 777 ./tp_temp

tar -zcf tp_temp.tar.gz ./tp_temp

cat x86_selfupdate.sh tp_temp.tar.gz > tmm.bin
chmod 777 tmm.bin
cp  tmm.bin ../../../10-common/version/release/linux/tmm.bin

[ -d ./umcwebclient ] && rm -rf ./umcwebclient
[ -f ./umcwebclient.tar ] && rm -rf ./umcwebclient.tar
[ -f ./tmm.bin ] && rm -rf ./tmm.bin
[ -f ./tp_temp.tar.gz ] && rm -rf ./tp_temp.tar.gz
[ -d ./tp_temp ] && rm -rf ./tp_temp
