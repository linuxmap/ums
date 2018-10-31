#!/bin/sh

if [ -f ./demotest.linux ]
then
rm -rf demotest.linux
fi


cd ./prj_linux

echo "make x86 exe"
./common.sh TARGET=exe ABI=x86 VERSION=release
sleep 1
./common.sh clean

sleep 1

cd ../
mv ../../10-common/version/release/linux/demotest.linux ./