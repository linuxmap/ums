#!/bin/sh
PROGDIR=`dirname $0`
PROGDIR=`cd $PROGDIR && pwd`

BUILD_CMD=${PROGDIR}/../../../t1-uranus/common/linux_build/mbt_build

export MOD_NAME=tpsocket_epoll
export COMPILE_INFO_DIR=${PROGDIR}/../../../10-common/version/compileinfo
export MK_PATH_OF_STATICLIB=./tpsocket_epoll.mk
export MK_PATH_OF_SHAREDLIB=./tpsocketdll_epoll.mk

${BUILD_CMD} "$@"
