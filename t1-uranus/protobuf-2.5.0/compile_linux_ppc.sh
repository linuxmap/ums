#!/bin/sh

cd ./prj_linux

echo "make 82xx dll"
./common_ppc.sh TARGET=dll ABI=ppc-82xx VERSION=release
sleep 1
./common_ppc.sh clean

sleep 1

echo "make 82xx lib"
./common_ppc.sh TARGET=lib ABI=ppc-82xx VERSION=release
sleep 1
./common_ppc.sh clean

echo "make 85xx dll"
./common_ppc.sh TARGET=dll ABI=ppc-85xx VERSION=release
sleep 1
./common_ppc.sh clean

sleep 1

echo "make 85xx lib"
./common_ppc.sh TARGET=lib ABI=ppc-85xx VERSION=release
sleep 1
./common_ppc.sh clean