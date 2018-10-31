#!/bin/sh

#echo sh_name=$0
#echo param_num=$#

#add sh when power on
#param one poweron config file
#param two poweron sh
#return 0 ok
#return 1 error
function addshpoweron()
{
	poweronconf=$1
	poweronsh=$2
	
	[ -z $poweronconf ] && return 1
	[ -z $poweronsh ] && return 1
	
	[ -w $poweronconf ] || return 1
	
	poweronconf_existflag=""$poweronconf""_existflag""
	
	[ -f $poweronconf_existflag ] && rm -rf $poweronconf_existflag
	
	echo "poweronsh=$poweronsh"
	echo "poweronconf=$poweronconf"
	
	cat $1 | while read line
	do
		need_ignore=$(echo "$line" | awk 'BEGIN{ret=0} /^#/{ret=1} END{print ret}')
		if [ $need_ignore -eq 1 ];then
			continue
		fi
		value=$(echo "$line" | awk '{print $1}')	
		if [ "x$poweronsh" == "x$value" ];then
			touch $poweronconf_existflag
			break
		fi
	done
	
	if [ -f $poweronconf_existflag ];then
		echo "$poweronsh is exist in $poweronconf !"
		rm -rf $poweronconf_existflag
	else
		echo "add $poweronsh in $poweronconf !"
		echo "$poweronsh" >> $poweronconf
	fi
	
	chmod 755 $poweronconf
	
	return 0
}

#install user libpath
#param one user libpath
#param two user libpath conf file
function installuserlibpath()
{
	libpath=$1
	confpath=$2
	[ -z $libpath ] && return 0
	[ -z $confpath ] && return 0
	
	[ -f $confpath ] || touch $confpath
	echo "$libpath" > $confpath
	chmod 755 $confpath
	ldconfig
	return 0
}

#error exit
function exitfun()
{
	echo $1
	echo "ERROR: update ums fail!"
	exit 1
}

curpath=`pwd`
echo $curpath

#define ums work path
ums_path="/tp"


[ -f $curpath/tp_temp.tar.gz ] && rm -rf $curpath/tp_temp.tar.gz
[ -d $curpath/tp_temp ] && rm -rf $curpath/tp_temp
[ -d $ums_path ] || mkdir $ums_path
[ -d $ums_path/lib ] || mkdir $ums_path/lib
[ -x $ums_path/stopums.sh ] && . $ums_path/stopums.sh

echo "the update for tpums begin..."
sleep 2

#add ums start when power on
addshpoweron "/etc/rc.d/rc.local" "$ums_path/initums.sh"
ret=$?
if [ "x$ret" == "x0" ];then
	echo "add ums start when power on success !"
else
	echo "ERROR: add ums start when power on fail !"
fi

sed '1,/^#here/d' $0 > tp_temp.tar.gz
tar -zxf $curpath/tp_temp.tar.gz

# enter tp_tmp
cd $curpath/tp_temp
# copy ums to $ums_path
cp -rf ./*.so $ums_path/lib/
cp -rf ./regserver $ums_path/
cp -rf ./devmgrservice $ums_path/
cp -rf ./umsmediatrans $ums_path/
cp -rf ./umsnetbuf $ums_path/
cp -rf ./umsserver_log4cplus $ums_path/
cp -rf ./umssipadapter_log4cplus $ums_path/
cp -rf ./log4cplusserver.linux $ums_path/
cp -rf ./kdvgk_redhat_4.2 $ums_path/
cp -rf ./*.sh $ums_path/
cp -rf ./*.cfg $ums_path/
cp -rf ./*.ini $ums_path/

# copy apache to /usr
[ -d /usr/apache ] && rm -rf /usr/apache
[ -d /usr/umcwebclient ] && rm -rf /usr/umcwebclient
[ -f /usr/apache.tar.gz ] && rm -rf /usr/apache.tar.gz
[ -f /usr/umcwebclient.tar ] && rm -rf /usr/umcwebclient.tar
cp -rf ./apache.tar.gz /usr/
cp -rf ./umcwebclient.tar /usr/
# enter /usr
cd /usr
tar -zxf ./apache.tar.gz
tar -xf ./umcwebclient.tar
[ -f /usr/apache.tar.gz ] && rm -rf /usr/apache.tar.gz
[ -f /usr/umcwebclient.tar ] && rm -rf /usr/umcwebclient.tar

# back enter tp_tmp
cd $curpath/tp_temp
cp -rf ./umcwebserver.fcgi /usr/apache/cgi-bin/
[ -f ./httpd.conf ] && cp -rf ./httpd.conf /usr/apache/conf/

chmod -R 755 $ums_path
chmod -R 755 /usr/apache
chmod -R 555 /usr/umcwebclient

# back enter curpath
cd $curpath

[ -f $curpath/tp_temp.tar.gz ] && rm -rf $curpath/tp_temp.tar.gz
[ -d $curpath/tp_temp ] && rm -rf $curpath/tp_temp

#install umslibpath
installuserlibpath "$ums_path/lib" "/etc/ld.so.conf.d/tpums.conf"

echo "the update for tpums have successfully completed at $ums_path !"

exit
#here
