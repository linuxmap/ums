#!/bin/sh

#echo sh_name=$0
#echo param_num=$#
curpath=`pwd`
echo $curpath

file1=./startums.sh
file2=./stopums.sh
file13=./initums.sh
file3=../../../10-common/version/release/linux/umsmediatrans
file4=../../../10-common/lib/release/linux/libosp.so    
file5=../../../10-common/lib/release/linux/libtinyxml.so   
file6=../../../10-common/lib/release/linux/libdataswitch.so   
file7=../../../10-common/lib/release/linux/libkdcrypto.so 
file8=../../../10-common/lib/release/linux/libkdssl.so   
file9=../../../10-common/lib/release/linux/libkdvsrtp.so  
file15=../../../10-common/lib/release/linux/libkdvlog.so  
file16=../../../10-common/lib/release/linux/libkprop.so

file10=../tpums_x86/commonfunction.sh
file11=../tpums_x86/daemonrestart.sh
file14=../tpums_x86/modifyntpserver.sh
file17=../tpums_x86/downloadlog.sh
file18=../tpums_x86/modifyip.sh
file12=./ums_moudle.ini


for file in $file1 $file2 $file3 $file4 $file5 $file6 $file7 $file8 $file9 $file10 $file11 $file12 $file13 $file14 $file15 $file16 $file17 $file18
do
	if [ ! -f $file ]   
	then
		echo error : $file not exist
		exit 1
	fi
done

[ -f ./trm.bin ] && rm -rf ./trm.bin
[ -f ./tp_temp.tar.gz ] && rm -rf ./tp_temp.tar.gz
[ -d ./tp_temp ] && rm -rf ./tp_temp

mkdir tp_temp

for file in $file1 $file2 $file3 $file4 $file5 $file6 $file7 $file8 $file9 $file10 $file11 $file12 $file13 $file14 $file15 $file16 $file17 $file18
do
	cp -f $file ./tp_temp/
done


chmod -R 777 ./tp_temp

tar -zcf tp_temp.tar.gz ./tp_temp

cat x86_selfupdate.sh tp_temp.tar.gz > trm.bin
chmod 777 trm.bin
cp  trm.bin ../../../10-common/version/release/linux/trm.bin


[ -f ./trm.bin ] && rm -rf ./trm.bin
[ -f ./tp_temp.tar.gz ] && rm -rf ./tp_temp.tar.gz
[ -d ./tp_temp ] && rm -rf ./tp_temp
