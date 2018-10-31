#!/bin/sh

cd ./prj_linux

echo "make x86 dll"
./common.sh TARGET=dll ABI=x86 VERSION=release
sleep 1
./common.sh clean

sleep 1

echo "make x86 lib"
./common.sh TARGET=lib ABI=x86 VERSION=release
sleep 1
./common.sh clean

