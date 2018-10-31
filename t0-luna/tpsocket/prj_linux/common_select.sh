#!/bin/sh
PROGDIR=`dirname $0`
PROGDIR=`cd $PROGDIR && pwd`

BUILD_CMD=${PROGDIR}/../../../t1-uranus/common/linux_build/mbt_build

export MOD_NAME=tpsocket_select
export COMPILE_INFO_DIR=${PROGDIR}/../../../10-common/version/compileinfo
export MK_PATH_OF_STATICLIB=./tpsocket_select.mk
export MK_PATH_OF_SHAREDLIB=./tpsocketdll_select.mk

${BUILD_CMD} "$@"
