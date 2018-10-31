#!/bin/sh

if [ -f ../../10-common/version/release/linux/log4cplusserver.linux ]
then
rm -rf ../../10-common/version/release/linux/log4cplusserver.linux
fi

if [ -f ./log4cplusserver.linux ]
then
rm -rf log4cplusserver.linux
fi


cd ./prj_linux

echo "make x86 exe"
./common.sh TARGET=exe ABI=x86 VERSION=release
sleep 1
./common.sh clean

sleep 1

cd ../
cp ../../10-common/version/release/linux/log4cplusserver.linux ./