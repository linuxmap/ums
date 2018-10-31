#!/bin/sh

cd ./prj_linux

echo "make x86 epoll dll"
./common_epoll.sh TARGET=dll ABI=x86 VERSION=all
sleep 1
./common_epoll.sh clean

sleep 1

echo "make x86 epoll lib"
./common_epoll.sh TARGET=lib ABI=x86 VERSION=all
sleep 1
./common_epoll.sh clean

echo "make x86 select dll"
./common_select.sh TARGET=dll ABI=x86 VERSION=all
sleep 1
./common_select.sh clean

sleep 1

echo "make x86 select lib"
./common_select.sh TARGET=lib ABI=x86 VERSION=all
sleep 1
./common_select.sh clean

