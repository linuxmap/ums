#!/bin/sh
PROGDIR=`dirname $0`
PROGDIR=`cd $PROGDIR && pwd`

BUILD_CMD=${PROGDIR}/../../common/linux_build/mbt_build

export MOD_NAME=protobufmsg
export COMPILE_INFO_DIR=${PROGDIR}/../../../10-common/version/compileinfo
export MK_PATH_OF_STATICLIB=./protobufmsg.mk
export MK_PATH_OF_SHAREDLIB=./protobufmsgdll.mk

${BUILD_CMD} "$@"
