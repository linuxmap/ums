#!/bin/sh

cd ./prj_linux

echo "make x86 dll"
./common_x86.sh TARGET=dll ABI=x86 VERSION=release
sleep 1
./common_x86.sh clean

sleep 1

echo "make x86 lib"
./common_x86.sh TARGET=lib ABI=x86 VERSION=release
sleep 1
./common_x86.sh clean

